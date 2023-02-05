import pygame
import math

DISPLAY_WIDTH = 800
DISPLAY_HEIGHT = 700
    
import sys
import os

def resource_path(relative_path):
    try:
    # PyInstaller creates a temp folder and stores path in _MEIPASS
        base_path = sys._MEIPASS
    except Exception:
        base_path = os.path.abspath(".")

    return os.path.join(base_path, relative_path)



class Line:
    def __init__(self):
        self.points = []
        self.color = []


class Model:
    def __init__(self):
        self.lines = [Line()]
        self.lines_cleared = [Line()]
        self.drawing = False 
        self.history = []
        self.tool = "pencil"
        
    def set_tool(self, tool):
        self.tool = tool
        
    def add_new_line(self):
        new_line = Line()
        self.lines.append(new_line)
    
    def add_new_line_cleared(self):
        new_line_cleared = Line()
        self.lines_cleared.append(new_line_cleared)
        
    def clear_point(self, point_coords, color_to_clear):
        points_to_remove = []
        for line_index in range(len(self.lines)):
            for point_to_remove in self.lines[line_index].points:
                if math.sqrt((point_coords[0] - point_to_remove[0][0]) ** 2 + (point_coords[1] - point_to_remove[0][1]) ** 2) < point_to_remove[1]:
                    points_to_remove.append(point_to_remove)    
        for point in points_to_remove:
            point[2] = color_to_clear #  self.view.background_color
            self.lines_cleared[(len(self.lines_cleared) - 1)].points.append(point)
    
    def finish_line(self):
        if len(self.lines) > 0:
            if len(self.lines[len(self.lines) - 1].points) > 0:
                self.lines[len(self.lines) - 1].color = self.lines[len(self.lines) - 1].points[0][2]
            
        self.drawing = False
        self.add_new_line()
        self.history.append("pencil")

    def finish_line_cleared(self):
        self.drawing = False
        self.add_new_line_cleared()
        self.history.append("eraser")

    def remove_last_line(self):
        try:
            choice = self.history.pop()
        except:
            return
        
        if choice == "pencil":
            try:
                self.lines.pop()
                self.lines.pop()
            except:
                pass
            self.lines.append(Line())
        elif choice == "eraser":
            try:
                self.lines_cleared.pop()
                points = self.lines_cleared.pop()
                for line in self.lines:
                    for point in points.points:
                        if point in line.points:
                            point[2] = line.color
            except:
                pass
            self.lines_cleared.append(Line())

    def clear(self):
        self.lines = [Line()]
        self.lines_cleared = [Line()]
        self.history = []


class View:
    def __init__(self, model, size):
        self.model = model
        self.screen = pygame.display.set_mode(size, pygame.RESIZABLE)
        pygame.display.set_caption("easy-paint")
        try:
            asset_url = resource_path("assets/chars/easy-paint.png")
            pygame.display.set_icon(pygame.image.load(asset_url))
        except Exception as ex:
            pass
        self.pencil_button = pygame.Rect(10, 10, 80, 30)
        self.eraser_button = pygame.Rect(100, 10, 80, 30)
        self.clear_button = pygame.Rect(190, 10, 80, 30)
        
        self.draw_color = (30, 30, 30)
        self.background_color = (255, 255, 255)
        self.draw_radius = 5

    def draw(self):
        self.screen.fill(self.background_color)

        pygame.draw.rect(self.screen, (200, 200, 200), self.pencil_button)
        font = pygame.font.Font(None, 20)
        text = font.render("Pencil", True, (0, 0, 0))
        self.screen.blit(text, (25, 20))

        pygame.draw.rect(self.screen, (200, 200, 200), self.eraser_button)
        text = font.render("Eraser", True, (0, 0, 0))
        self.screen.blit(text, (115, 20))

        pygame.draw.rect(self.screen, (200, 200, 200), self.clear_button)
        text = font.render("Clear", True, (0, 0, 0))
        self.screen.blit(text, (205, 20))

        self.draw_pencil()

    def draw_pencil(self):
        try:
            for line_index in range(len(self.model.lines)):
                for point_index in range(len(self.model.lines[line_index].points)-1):
                    point = self.model.lines[line_index].points[point_index]
                    if self.model.lines[line_index].color == point[2]:
                        pygame.draw.line(self.screen, point[2], point[0], self.model.lines[line_index].points[point_index + 1][0], point[1])
        except:
            pass
            
class Controller:
    def __init__(self, model, view):
        self.model = model
        self.view = view
        self.selected_tool = "pencil"  # Default tool is pencil

    def handle_event(self, event):
        if event.type == pygame.MOUSEBUTTONDOWN:
            if event.button == 1:
                # Check if pencil button was clicked
                if self.view.pencil_button.collidepoint(event.pos):
                    self.selected_tool = "pencil"
                    self.model.set_tool(self.selected_tool)
                # Check if eraser button was clicked
                elif self.view.eraser_button.collidepoint(event.pos):
                    self.selected_tool = "eraser"
                    self.model.set_tool(self.selected_tool)
                # Check if clear button was clicked
                elif self.view.clear_button.collidepoint(event.pos):
                    self.model.clear()
                else:
                    self.model.drawing = True
                    
        if event.type == pygame.MOUSEMOTION:
            if self.model.drawing is True:
                if self.selected_tool == 'pencil':
                    self.model.lines[len(self.model.lines) - 1].points.append([event.pos, self.view.draw_radius, self.view.draw_color])
                    self.model.lines[len(self.model.lines) - 1].color = self.view.draw_color
                if self.selected_tool == 'eraser':
                    self.model.clear_point(event.pos, self.view.background_color)
        
        elif event.type == pygame.MOUSEBUTTONUP:
            if self.selected_tool == "pencil":
                self.model.finish_line()
            if self.selected_tool == "eraser":
                self.model.finish_line_cleared()
        
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_b:
                self.selected_tool = "pencil"
                self.model.set_tool(self.selected_tool)
            elif event.key == pygame.K_e:
                self.selected_tool = "eraser"
                self.model.set_tool(self.selected_tool)
            elif event.key == pygame.K_c:
                self.model.clear()
            elif event.key == pygame.K_z and pygame.key.get_mods() & pygame.KMOD_LCTRL:
                if not self.model.drawing:
                    self.model.remove_last_line()
                    
            #elif event.key == pygame.KMOD_LSHIFT:
            #    self.model.lines.pop()
            #    self.model.drawing = True
                
        self.view.draw()


if __name__ == '__main__':
    pygame.init()
    clock = pygame.time.Clock()
    
    model = Model()
    view = View(model, (DISPLAY_WIDTH, DISPLAY_HEIGHT))
    controller = Controller(model, view)
    running = True

    while running:
        for event in pygame.event.get():
            controller.handle_event(event)
            if event.type == pygame.QUIT:
                running = False
                break
        clock.tick(100)
        # view.draw()
        pygame.display.update()

    pygame.quit()
    