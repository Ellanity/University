import pygame
import sys


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
# Model
#     The central component of the pattern.
#     It is the application's dynamic data
#     structure, independent of the user
#     interface. It directly manages the data,
#     logic and rules of the application.
# View
#     Any representation of information
#     such as a chart, diagram or table.
#     Multiple views of the same information
#     are possible, such as a bar chart
#     for management and a tabular view
#     for accountants.
# Controller
#     Accepts input and converts it to
#     commands for the model or view.


class TicTackToe:

    class Model:
        def __init__(self):
            self.step_items = ["X", "O"]
            self.win_coordinates = (
                (0, 1, 2), (3, 4, 5), (6, 7, 8),
                (0, 3, 6), (1, 4, 7), (2, 5, 8),
                (0, 4, 8), (2, 4, 6),
            )
            #
            self.win_coords = list()
            self.fields = ['' for _ in range(9)]
            self.step_item = self.step_items[0]

        def step(self, field_index):
            if len(self.win_coords) > 0:
                return

            if field_index > len(self.fields) - 1:
                self.restart()
                return

            if self.fields[field_index] != '':
                return

            self.fields[field_index] = self.step_item
            step_item_index = self.step_items.index(self.step_item) + 1
            if step_item_index >= len(self.step_items):
                step_item_index = 0
            self.step_item = self.step_items[step_item_index]
            self.check_win()

        def restart(self):
            self.win_coords.clear()
            self.fields.clear()
            self.fields = ['' for _ in range(9)]
            self.step_item = self.step_items[0]

        def check_win(self):
            items_set = lambda coords: [self.fields[coordinate] for coordinate in coords]
            for coordinates in self.win_coordinates:
                items = items_set(coordinates)
                if items.count('X') == 3 or items.count('O') == 3:
                    for coord in coordinates:
                        self.win_coords.append(coord)

            if len(self.win_coords) > 0:
                for field in self.fields:
                    field = " " if field == '' else field

        def get_fields(self):
            return self.fields

        def get_win_coords(self):
            return self.win_coords

    class Controller:
        def __init__(self):
            self.view = None
            self.model = None

        def set_view(self, view):
            self.view = view

        def set_model(self, model):
            self.model = model

        def get_fields(self):
            return self.model.get_fields()

        def get_win_coords(self):
            return self.model.get_win_coords()

        def step(self, field_index):
            self.model.step(field_index)

        def restart(self):
            self.model.restart()
            self.view.restart()

        def event_handler(self):
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    sys.exit()
                if event.type == pygame.MOUSEBUTTONUP and event.button == 1:
                    self.event(event.pos, "click")

            if pygame.mouse.get_pressed()[0]:
                self.event(pygame.mouse.get_pos(), "press")
                self.event(pygame.mouse.get_pos(), "impress")

        def event(self, position, action_type_name):
            for button in self.view.buttons:
                if button.rect.collidepoint(position):
                    if action_type_name == "press":
                        button.pressed = True
                    if action_type_name == "click":
                        button.disabled = True
                        self.step(button.field_index)
                        if button.field_index == 9:
                            self.restart()
                elif not button.rect.collidepoint(position):
                    if action_type_name == "impress":
                        button.pressed = False

    class View:
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
                self.win_color_for_item = (0, 255, 0)
                self.standard_color_for_item = (255, 255, 255)
                self.color_for_item = self.standard_color_for_item
                self.rect = pygame.Rect(self.position_x, self.position_y,
                                        self.image.get_width(), self.image.get_height())
                # states
                self.type_name = type_name
                self.disabled = False
                self.pressed = False

                self.field_index = None
                self.item = None

            def render(self, display):
                color = self.image_color_standard
                if self.disabled:
                    color = self.image_color_disables
                elif self.pressed:
                    color = self.image_color_press

                self.image.fill(color)
                self.set_content(self.item)
                display.blit(self.image, (self.position_x, self.position_y))

            def set_content(self, item):
                self.item = item

                text_size = 70 if self.type_name == "game" else 30
                font = pygame.font.Font(None, text_size)
                text = font.render(self.item, True, self.color_for_item)

                pos_x_for_text = (self.image.get_width() - text.get_width()) / 2
                pos_y_for_text = (self.image.get_height() - text.get_height()) / 2

                self.image.blit(text, (pos_x_for_text, pos_y_for_text))

        def __init__(self):
            self.controller = None
            # window
            self.DISPLAY_WIDTH = 300
            self.DISPLAY_HEIGHT = 400
            pygame.init()
            self.display = pygame.display.set_mode((self.DISPLAY_WIDTH, self.DISPLAY_HEIGHT))
            pygame.display.set_caption("TicTackToe")
            self.clock = pygame.time.Clock()
            # entities
            self.buttons = []
            self.init_buttons()

        def set_controller(self, controller):
            self.controller = controller

        def init_buttons(self):
            # GAME
            margin = 1
            game_button_width = game_button_height = (self.DISPLAY_WIDTH / 3) - margin * 2
            for index in range(9):
                button_x = margin + (game_button_width + margin * 2) * (index % 3)
                button_y = margin + (game_button_height + margin * 2) * int(index / 3)
                button_image = pygame.Surface((game_button_width, game_button_height))

                game_button = self.Button(button_image, (button_x, button_y), "game")
                game_button.field_index = index
                self.buttons.append(game_button)

            # RESTART
            restart_button_width = self.DISPLAY_WIDTH
            restart_button_height = self.DISPLAY_HEIGHT - self.DISPLAY_WIDTH
            restart_button_x = 0
            restart_button_y = self.DISPLAY_HEIGHT - restart_button_height
            restart_button_image = pygame.Surface((restart_button_width, restart_button_height))

            restart_button = self.Button(restart_button_image, (restart_button_x, restart_button_y), "restart")
            restart_button.set_content("restart")
            restart_button.field_index = 9
            self.buttons.append(restart_button)

        def render(self):
            fields_items = self.controller.get_fields()
            for index in range(9):
                self.buttons[index].set_content(fields_items[index])

            win_coords = self.controller.get_win_coords()
            for button in self.buttons:
                if len(win_coords) > 0:
                    if button.field_index in win_coords:
                        button.color_for_item = button.win_color_for_item
                    if button.field_index != 9:
                        button.disabled = True
                else:
                    button.color_for_item = button.color_for_item
                button.render(self.display)

            pygame.display.flip()
            self.clock.tick(20)

        def restart(self):
            self.buttons.clear()
            self.init_buttons()

    def __init__(self):
        self.model = self.Model()
        self.view = self.View()
        self.controller = self.Controller()
        # ###
        self.view.set_controller(self.controller)
        self.controller.set_view(self.view)
        self.controller.set_model(self.model)

    def run(self):
        while True:
            try:
                self.view.render()
                self.controller.event_handler()
            except Exception as ex:
                print(ex)


if __name__ == "__main__":
    TicTackToe().run()
