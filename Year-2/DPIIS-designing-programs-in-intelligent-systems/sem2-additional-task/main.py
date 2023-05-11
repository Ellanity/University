import pygame
import sys


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


class TicTackToe:

    def __init__(self):
        self.DISPLAY_WIDTH = 300
        self.DISPLAY_HEIGHT = self.DISPLAY_WIDTH + 100
        self.COUNT_OF_BUTTONS_IN_ROW = self.COUNT_OF_BUTTONS_IN_COLUMN = 3

        # window
        pygame.init()
        self.display = pygame.display.set_mode((self.DISPLAY_WIDTH, self.DISPLAY_HEIGHT))
        pygame.display.set_caption("TicTackToe")
        self.clock = pygame.time.Clock()

        # game states
        self.win = False
        self.restart = False
        self.buttons = list()
        self.init_buttons()
        self.step_items = ["X", "O"]
        self.step_item = self.step_items[0]

    def run(self):
        while True:
            try:
                for event in pygame.event.get():
                    if event.type == pygame.QUIT:
                        pygame.quit()
                        sys.exit()
                    if event.type == pygame.MOUSEBUTTONUP and event.button == 1:
                        self.action(event.pos, "click")

                if pygame.mouse.get_pressed()[0]:
                    self.action(pygame.mouse.get_pos(), "press")

                self.interface()

                # check game states
                self.check_win()
                if self.restart:
                    self.win = False
                    self.restart = False
                    self.buttons = list()
                    self.init_buttons()

            except Exception as ex:
                print(ex)

    def init_buttons(self):
        # GAME BUTTONS
        margin = 1
        game_button_width = game_button_height = (self.display.get_width() / self.COUNT_OF_BUTTONS_IN_ROW) - margin * 2
        for index in range(9):
            button_x = margin + (game_button_width + margin * 2) * (index % self.COUNT_OF_BUTTONS_IN_ROW)
            button_y = margin + (game_button_height + margin * 2) * int(index / self.COUNT_OF_BUTTONS_IN_COLUMN)
            button_image = pygame.Surface((game_button_width, game_button_height))

            game_button = Button(button_image, (button_x, button_y), "game")
            game_button.field_coords = ((index % self.COUNT_OF_BUTTONS_IN_ROW),
                                        int(index / self.COUNT_OF_BUTTONS_IN_COLUMN))
            self.buttons.append(game_button)

        # RESTART
        restart_button_width = self.display.get_width()
        restart_button_height = self.display.get_height() - self.display.get_width()
        restart_button_x = 0
        restart_button_y = self.display.get_height() - restart_button_height
        restart_button_image = pygame.Surface((restart_button_width, restart_button_height))

        restart_button = Button(restart_button_image, (restart_button_x, restart_button_y), "restart")
        self.set_button_item(restart_button, "restart")
        self.buttons.append(restart_button)

    def interface(self):
        for button in self.buttons:
            if button.disabled:
                color = button.image_color_disables
            elif button.pressed:
                color = button.image_color_press
            else:
                color = button.image_color_standard

            button.image.fill(color)
            self.set_button_item(button, button.item)
            self.display.blit(button.image, (button.position_x, button.position_y))

        pygame.display.flip()
        self.clock.tick(20)

    def action(self, position, action):
        for button in self.buttons:
            if button.rect.collidepoint(position):
                if action == "press":
                    button.pressed = True
                if action == "click":
                    if button.type_name == "restart":
                        self.restart = True
                        return
                    if not button.disabled:
                        self.set_button_item(button, self.step_item)
                        button.disabled = True
                        step_item_index = self.step_items.index(self.step_item) + 1
                        if step_item_index >= len(self.step_items):
                            step_item_index = 0
                        self.step_item = self.step_items[step_item_index]
            else:
                if action == "press":
                    button.pressed = False

    def set_button_item(self, button, item):
        button.item = item

        text_size = 30
        if button.type_name == "game":
            text_size = 70

        font = pygame.font.Font(None, text_size)
        text = font.render(button.item, True, button.color_for_item)

        pos_x_for_text = (button.image.get_width() - text.get_width()) / 2
        pos_y_for_text = (button.image.get_height() - text.get_height()) / 2

        button.image.blit(text, (pos_x_for_text, pos_y_for_text))

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
                for button in self.buttons:
                    if button.type_name == "game":
                        button.disabled = True
                for button in buttons:
                    button.color_for_item = (0, 255, 0)
                    self.set_button_item(button, button.item)


if __name__ == "__main__":
    TicTackToe().run()
