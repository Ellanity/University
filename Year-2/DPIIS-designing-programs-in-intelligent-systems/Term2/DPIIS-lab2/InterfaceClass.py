from Table.TableClass import Table
from kivy.app import App
from kivy.uix.label import Label
from kivy.uix.button import Button
from kivy.core.window import Window
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.gridlayout import GridLayout
from kivy.uix.textinput import TextInput

import os


# Window.size = (1200, 600)
Window.title = "Tables"


class Interface(App):

    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self.table = Table()
        self.main_layout = BoxLayout()
        self.menu_choose_table()

    # ### -------------------------- main_menu ui -------------------------
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

    def open_table(self, button):
        self.main_layout.clear_widgets()
        self.table.load_from_xml(str(button.text + ".xml"))
        self.table_ui()

    # ### ------------------------- table/tools ui -------------------------
    def table_ui(self, obj=None):
        self.main_layout.clear_widgets()
        self.generate_table_widget()
        """
        ,____________________________________________________________________,
        |   left menu   |                right working area                  |
        |---------------|----------,----------,----------,----------,--------|
        | > tool1       | ~column1 | ~column2 |   ...    |          |        |
        | ------------- |----------|----------|----------|----------|--------|
        | > tool2       | element1 | element2 |   ...    |          |        |
        | ------------- |----------|----------|----------|----------|--------|
        | ...           |   ...    |   ...    |   ...    |   ...    |  ...   |
        |               |          |          |          |          |        |
        |               |          |          |          |          |        |
        |               |          |          |          |          |        |
        |_______________|__________|__________|__________|__________|________|
        |               |           <<   <   current_page   >   >>           |
        |_______________|____________________________________________________|
        | <= back       |     the current tool for working with the table    |
        |_______________|____________________________________________________|
        
        """
        left_menu = BoxLayout(orientation='vertical')
        right_working_area = BoxLayout(orientation='vertical', size_hint=(4, 1))

        left_menu.add_widget(self.generate_table_tools_widget())
        right_working_area.add_widget(self.generate_table_widget())

        self.main_layout.add_widget(left_menu)
        self.main_layout.add_widget(right_working_area)

    # ### ---- table ----
    def generate_table_widget(self):
        pagination = False
        table_widget = GridLayout()

        if pagination:
            pass
        else:
            table_widget.cols = len(self.table.columns)
            for column in self.table.columns:
                column_title = Label(text=column.title) # text_size=(column_width, None))
                column_title.color = (100, 100, 100, 1)
                table_widget.add_widget(column_title)

            for record in self.table.records:
                for element in record.elements:
                    element_widget = Label(text=str(element)) #text_size=(column_width, None))
                    table_widget.add_widget(element_widget)

        return table_widget

    # ### ---- tools ----
    def generate_table_tools_widget(self):

        tools_widget = BoxLayout(orientation='vertical')

        button_table = Button(text="table", size_hint_y=0.1)
        button_table.bind(on_press=self.table_ui)
        tools_widget.add_widget(button_table)

        button_search = Button(text="search", size_hint_y=0.1)
        button_search.bind(on_press=self.generate_search_box_widget)
        tools_widget.add_widget(button_search)

        button_back = Button(text="<= back", size_hint_y=0.1)
        button_back.bind(on_press=self.menu_choose_table)
        tools_widget.add_widget(button_back)

        return tools_widget

    def generate_search_box_widget(self, obj=None):
        self.table_ui()

        search_box_widget = BoxLayout(size_hint_y=0.1)
        search_box_widget.add_widget(TextInput(multiline=False, size_hint_x=2, text="column title"))
        search_box_widget.add_widget(TextInput(multiline=False, size_hint_x=4, text="element"))
        button_find = Button(text="find")
        button_find.bind(on_press=self.table_tool_search)
        search_box_widget.add_widget(button_find)

        self.main_layout.children[0].add_widget(search_box_widget)
        # self.main_layout.children[0].add_widget(self.generate_search_box_widget())
        # return search_box_widget

    def table_tool_search(self, obj=None):
        # self.table_ui()
        column_title = self.main_layout.children[0].children[0].children[2].text
        element = self.main_layout.children[0].children[0].children[1].text


        # for record in self.table.record_find(column_title, element):
        #   print(record.elements)

        all_records = self.table.records
        if column_title != "" and element != "":
            self.table.records = self.table.record_find(column_title, element)
        self.table_ui()
        self.generate_search_box_widget()
        self.main_layout.children[0].children[0].children[2].text = column_title
        self.main_layout.children[0].children[0].children[1].text = element
        self.table.records = all_records


        """ print(column_title)
        if column_title in self.table.columns:
            index = self.table.columns.index(str(column_title))
            for record in self.table.records:
                if record[index] == self.table.columns[index].data_convert(element):
                    print(record)"""
        # print(self.main_layout.children[0].children[0].children[1].text)


        # self.main_layout.children[0].add_widget(self.generate_search_box_widget())


    def build(self):
        return self.main_layout
