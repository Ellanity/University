import pygame
import sys

DISPLAY_WIDTH = 300
DISPLAY_HEIGHT = 400


class Button(pygame.sprite.Sprite):
    def __init__(self, image, coords, type_name):
        super().__init__()
        # coords
        self.position_x = coords[0]
        self.position_y = coords[1]

        # image
        self.image = image
        self.image_color_standard = (96, 96, 96)
        self.image_color_press = (100, 140, 140)
        self.image_color_disables = (64, 64, 64)
        self.color_for_item = (255, 255, 255)
        self.rect = pygame.Rect(self.position_x, self.position_y, self.image.get_width(), self.image.get_height())

        # states
        self.type_name = type_name
        self.disabled = False
        self.pressed = False

        # for game
        self.field_coords = tuple()
        self.item = str()

    def disable(self):
        self.disabled = True

    def press(self):
        self.pressed = True

    def impress(self):
        self.pressed = False

    def render(self, display):
        self.fill_button()
        self.set_item(self.item)
        display.blit(self.image, (self.position_x, self.position_y))

    def set_field_coords(self, coords):
        self.field_coords = coords

    def set_item(self, item):
        self.item = item

        text_size = 30
        if self.type_name == "game":
            text_size = 70

        font = pygame.font.Font(None, text_size)
        text = font.render(self.item, True, self.color_for_item)

        pos_x_for_text = (self.image.get_width() - text.get_width()) / 2
        pos_y_for_text = (self.image.get_height() - text.get_height()) / 2

        self.image.blit(text, (pos_x_for_text, pos_y_for_text))

    def fill_button(self):
        if self.disabled:
            color = self.image_color_disables
        elif self.pressed:
            color = self.image_color_press
        else:
            color = self.image_color_standard

        self.image.fill(color)


class TicTackToe:

    #         ,-------,
    #    ,----| model |<____,
    #    |    !_______!     |
    # updates           manipulates
    #    |                  |
    #   \/                  |
    # ,------,         ,----------,
    # | view |         |controller|
    # !______!         !__________!
    #     |                /\
    #   sees   ,------,   uses
    #     \___>| user |____/
    #          !______!
    #
    
    # updates view
    class Model:
        def __init__(self):
            self.win = False
            self.restart = False
            self.buttons = list()
            self.init_buttons()
            self.step_items = ["X", "O"]
            self.step_item = self.step_items[0]

        def event(self, position, action):
            for button in self.buttons:
                if button.rect.collidepoint(position):
                    if action == "press":
                        button.press()
                    if action == "click":
                        if button.type_name == "restart":
                            self.restart = True
                            return
                        if not button.disabled:
                            button.set_item(self.step_item)
                            button.disable()
                            step_item_index = self.step_items.index(self.step_item) + 1
                            if step_item_index >= len(self.step_items):
                                step_item_index = 0
                            self.step_item = self.step_items[step_item_index]
                else:
                    if action == "press":
                        button.impress()

        def restart_game(self):
            self.win = False
            self.restart = False
            self.buttons = list()
            self.init_buttons()

        def init_buttons(self):
            # GAME BUTTONS
            game_button_width = game_button_height = DISPLAY_WIDTH / 3
            for index in range(9):
                button_x = game_button_width * (index % 3)
                button_y = game_button_height * int(index / 3)
                button_image = pygame.Surface((game_button_width, game_button_height))

                game_button = Button(button_image, (button_x, button_y), "game")
                game_button.set_field_coords(((index % 3), int(index / 3)))
                self.buttons.append(game_button)

            # RESTART
            restart_button_width = DISPLAY_WIDTH
            restart_button_height = DISPLAY_HEIGHT - DISPLAY_WIDTH
            restart_button_x = 0
            restart_button_y = DISPLAY_HEIGHT - restart_button_height
            restart_button_image = pygame.Surface((restart_button_width, restart_button_height))

            restart_button = Button(restart_button_image, (restart_button_x, restart_button_y), "restart")
            restart_button.set_item("restart")
            self.buttons.append(restart_button)

        def disable_all_game_buttons(self):
            for button in self.buttons:
                if button.type_name == "game":
                    button.disable()

        def check_win(self):
            win_coordinates = (
                ((0, 0), (0, 1), (0, 2)), ((1, 0), (1, 1), (1, 2)), ((2, 0), (2, 1), (2, 2)),  # X
                ((0, 0), (1, 0), (2, 0)), ((0, 1), (1, 1), (2, 1)), ((0, 2), (1, 2), (2, 2)),  # Y
                ((0, 0), (1, 1), (2, 2)), ((0, 2), (1, 1), (2, 0))  # D
            )

            # buttons for every set of coordinates
            buttons_set = lambda coords: [button for button in self.buttons if button.field_coords in coords]

            for coordinates in win_coordinates:
                buttons = buttons_set(coordinates)
                buttons_items = [button.item for button in buttons]

                if buttons_items.count('X') == 3 or buttons_items.count('O') == 3:
                    self.win = True
                    self.disable_all_game_buttons()
                    for button in buttons:
                        button.color_for_item = (0, 255, 0)
                        button.set_item(button.item)

    # user see it (display)
    class View:
        def __init__(self, model):
            self.model = model
            # window
            pygame.init()
            self.display = pygame.display.set_mode((DISPLAY_WIDTH, DISPLAY_HEIGHT))
            pygame.display.set_caption("TicTackToe")
            self.clock = pygame.time.Clock()

        def render(self):
            for button in self.model.buttons:
                button.render(self.display)

            pygame.display.flip()
            self.clock.tick(20)

    # user use to control model
    class Controller:
        def __init__(self, model):
            self.model = model

        def check_action(self):
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    sys.exit()
                if event.type == pygame.MOUSEBUTTONUP and event.button == 1:
                    self.model.event(event.pos, "click")

            if pygame.mouse.get_pressed()[0]:
                self.model.event(pygame.mouse.get_pos(), "press")

            self.model.check_win()

    def __init__(self):
        self.model = self.Model()
        self.view = self.View(self.model)
        self.controller = self.Controller(self.model)

    def run(self):
        while True:
            try:
                self.view.render()
                self.controller.check_action()
            except Exception as ex:
                print(ex)


if __name__ == "__main__":
    TicTackToe().run()
