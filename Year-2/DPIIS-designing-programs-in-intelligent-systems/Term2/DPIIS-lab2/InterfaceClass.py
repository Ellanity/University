from Table.TableClass import Table
from kivy.app import App
from kivy.uix.label import Label
from kivy.uix.button import Button
from kivy.core.window import Window
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.gridlayout import GridLayout

import os


# Window.size = (1200, 600)
Window.title = "Tables"


class Interface(App):

    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self.table = Table()
        self.main_layout = BoxLayout()
        self.menu_choose_table()
        self.table_widget = GridLayout()

    def open_table(self, button):
        self.main_layout.clear_widgets()
        self.table.load_from_xml(str(button.text + ".xml"))
        # print(self.table.title)
        # print(self.table.columns)
        # print(self.table.records)
        self.table_ui()

    def table_ui(self):
        # self.table.print()
        self.main_layout.clear_widgets()

        button_back = Button(text="<= back")
        button_back.bind(on_press=self.menu_choose_table)
        self.main_layout.add_widget(button_back)

        self.table_widget.clear_widgets()
        self.generate_table_widget()
        self.main_layout.add_widget(self.table_widget)

    def generate_table_widget(self):
        pagination = False
        # self.table_widget.row_default_height = 40
        # column_width = self.table_widget.width/len(self.table.columns)
        # print(column_width, self.table_widget.width, len(self.table.columns))
        if pagination:
            pass
        else:
            self.table_widget.cols = len(self.table.columns)
            for column in self.table.columns:
                column_title = Label(text=column.title) #, text_size=(column_width, None))
                column_title.color = (100, 100, 100, 1)
                self.table_widget.add_widget(column_title)

            for record in self.table.records:
                for element in record.elements:
                    element_widget = Label(text=str(element)) #, text_size=(column_width, None))
                    self.table_widget.add_widget(element_widget)

    def menu_choose_table(self, obj=None):
        self.main_layout.clear_widgets()
        # self.table = Table()
        table_buttons_widget = BoxLayout()
        table_buttons_widget.orientation = 'vertical'

        for file in os.listdir():
            file_name = file.split(".")[0]
            file_expansion = file.split(".")[-1]
            if file_expansion == "xml":
                table_button = Button(text=file_name)
                table_button.bind(on_press=self.open_table)
                table_buttons_widget.add_widget(table_button)
        self.main_layout.add_widget(table_buttons_widget)

    def build(self):
        return self.main_layout
