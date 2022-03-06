from Table.TableClass import Table
from kivy.app import App
from kivy.uix.label import Label
from kivy.uix.button import Button
from kivy.core.window import Window
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.gridlayout import GridLayout
from kivy.uix.textinput import TextInput
from kivy.uix.popup import Popup


import os


# Window.size = (1200, 600)
Window.title = "Tables"


class Interface(App):

    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self.table = Table()
        self.main_layout = BoxLayout()
        self.menu_choose_table()

    # #########################################################################
    # ### -------------------------- main_menu ui ------------------------- ###
    # #########################################################################
    def menu_choose_table(self, obj=None):
        self.main_layout.clear_widgets()
        # self.table = Table()
        table_buttons_widget = BoxLayout()
        table_buttons_widget.orientation = 'vertical'

        # other tables
        for file in os.listdir():
            file_name = file.split(".")[0]
            file_expansion = file.split(".")[-1]
            if file_expansion == "xml":
                button_table_box = BoxLayout(padding=10)
                button_table = Button(text=file_name)
                button_table.bind(on_press=self.open_table)
                button_table_box.add_widget(button_table)
                table_buttons_widget.add_widget(button_table_box)
        self.main_layout.add_widget(table_buttons_widget)

        # new table
        new_table = BoxLayout(padding=30)
        button_new_table = Button(text="Create new table")
        table_title = TextInput(text="Table_name", multiline=False)
        new_table.add_widget(table_title)
        new_table.add_widget(button_new_table)
        button_new_table.bind(on_press=self.create_new_table)
        table_buttons_widget.add_widget(new_table)

    def create_new_table(self, obj=None):
        title = self.main_layout.children[0].children[0].children[1].text
        title = title.replace(' ', '')
        self.table = Table(title)
        self.table.save_to_xml()
        self.main_layout.clear_widgets()
        self.table_ui()

    def open_table(self, button):
        self.main_layout.clear_widgets()
        self.table.load_from_xml(str(button.text + ".xml"))
        self.table_ui()

    # ##########################################################################
    # ### ------------------------- table/tools ui ------------------------- ###
    # ##########################################################################
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
        # right_working_area.add_widget(Label(text="", size_hint_y=0.03))  # window for system info
        right_working_area.add_widget(self.generate_table_widget())

        self.main_layout.add_widget(left_menu)
        self.main_layout.add_widget(right_working_area)

    # #######################
    # ### ---- table ---- ###
    # #######################
    def generate_table_widget(self):
        pagination = False
        table_widget = GridLayout()

        if pagination:
            pass
        else:
            table_widget.cols = len(self.table.columns)
            for column in self.table.columns:
                column_title = Label(text=column.title)
                column_title.color = (100, 100, 100, 1)
                table_widget.add_widget(column_title)

            for record in self.table.records:
                for element in record.elements:
                    element_widget = Label(text=str(element))
                    table_widget.add_widget(element_widget)

        return table_widget

    # #######################
    # ### ---- tools ---- ###
    # #######################
    def generate_table_tools_widget(self):

        tools_widget = BoxLayout(orientation='vertical')

        button_table = Button(text="table", size_hint_y=0.1)
        button_table.bind(on_press=self.table_ui)
        tools_widget.add_widget(button_table)

        button_save = Button(text="save", size_hint_y=0.1)
        button_save.bind(on_press=self.generate_save_widget)
        tools_widget.add_widget(button_save)

        button_add_record = Button(text="add record", size_hint_y=0.1)
        button_add_record.bind(on_press=self.generate_add_record_widget)
        tools_widget.add_widget(button_add_record)

        button_remove_record = Button(text="remove record", size_hint_y=0.1)
        button_remove_record.bind(on_press=self.generate_remove_record_widget)
        tools_widget.add_widget(button_remove_record)

        button_add_column = Button(text="add column", size_hint_y=0.1)
        button_add_column.bind(on_press=self.generate_add_column_widget)
        tools_widget.add_widget(button_add_column)

        button_remove_column = Button(text="remove column", size_hint_y=0.1)
        button_remove_column.bind(on_press=self.generate_remove_column_widget)
        tools_widget.add_widget(button_remove_column)

        button_search = Button(text="search", size_hint_y=0.1)
        button_search.bind(on_press=self.generate_search_widget)
        tools_widget.add_widget(button_search)

        button_back = Button(text="<= back", size_hint_y=0.1)
        button_back.bind(on_press=self.menu_choose_table)
        tools_widget.add_widget(button_back)

        return tools_widget

    # #################################
    # ###  implementation of tools  ###
    # #################################

    # search
    def generate_search_widget(self, obj=None):
        self.table_ui()

        search_widget = BoxLayout(size_hint_y=0.1)
        search_widget.add_widget(TextInput(multiline=False, size_hint_x=2, text="column title"))
        search_widget.add_widget(TextInput(multiline=False, size_hint_x=4, text="element"))
        button_find = Button(text="find")
        button_find.bind(on_press=self.table_tool_search)
        search_widget.add_widget(button_find)

        self.main_layout.children[0].add_widget(search_widget)

    def table_tool_search(self, obj=None):
        # self.table_ui()
        column_title = self.main_layout.children[0].children[0].children[2].text
        element = self.main_layout.children[0].children[0].children[1].text

        all_records = self.table.records
        if column_title != "" and element != "":
            self.table.records = self.table.record_find(column_title, element)
        self.table_ui()
        self.generate_search_widget()
        self.main_layout.children[0].children[0].children[2].text = column_title
        self.main_layout.children[0].children[0].children[1].text = element
        self.table.records = all_records

    # add record
    def generate_add_record_widget(self, obj=None):
        self.table_ui()

        add_record_widget = BoxLayout(size_hint_y=0.1)
        for column in self.table.columns:
            add_record_widget.add_widget(TextInput(multiline=False, size_hint_x=1, text=""))
        button_find = Button(text="add")
        button_find.bind(on_press=self.table_tool_add_record)
        add_record_widget.add_widget(button_find)

        self.main_layout.children[0].add_widget(add_record_widget)

    def table_tool_add_record(self, obj=None):
        elements = list()
        for element in reversed(self.main_layout.children[0].children[0].children):
            elements.append(element.text)
        elements.pop()

        self.table.record_add(elements)
        self.table_ui()
        self.generate_add_record_widget()

    # save table
    def generate_save_widget(self, obj=None):
        self.table_ui()

        save_widget = BoxLayout(size_hint_y=0.1)
        save_widget.add_widget(Label(text="wait a second"))

        self.main_layout.children[0].add_widget(save_widget)
        self.table_tool_save()

    def table_tool_save(self, obj=None):
        self.table.save_to_xml()
        self.main_layout.children[0].children[0].children[0].text = "saved"

    # add column
    def generate_add_column_widget(self, obj=None):
        self.table_ui()

        add_column_widget = BoxLayout(size_hint_y=0.1)
        add_column_widget.add_widget(TextInput(multiline=False, size_hint_x=1, text="column_title"))
        add_column_widget.add_widget(TextInput(multiline=False, size_hint_x=1, text="type of data [str/int]"))
        button_find = Button(text="add")
        button_find.bind(on_press=self.table_tool_add_column)
        add_column_widget.add_widget(button_find)

        self.main_layout.children[0].add_widget(add_column_widget)

    def table_tool_add_column(self, obj=None):
        # self.table_ui()
        type_of_data = self.main_layout.children[0].children[0].children[1].text
        column_title = self.main_layout.children[0].children[0].children[2].text
        column_title = column_title.replace(' ', '_')

        if column_title != "":
            self.table.column_add(type_of_data, column_title)
        self.table_ui()
        self.generate_add_column_widget()

    # remove column
    def generate_remove_column_widget(self, obj=None):
        self.table_ui()

        remove_column_widget = BoxLayout(size_hint_y=0.1)
        remove_column_widget.add_widget(TextInput(multiline=False, size_hint_x=1, text="column title"))
        button_find = Button(text="remove")
        button_find.bind(on_press=self.table_tool_remove_column)
        remove_column_widget.add_widget(button_find)

        self.main_layout.children[0].add_widget(remove_column_widget)

    def table_tool_remove_column(self, obj=None):
        # self.table_ui()
        column_title = self.main_layout.children[0].children[0].children[1].text
        self.table.column_remove(column_title)
        self.table_ui()
        self.generate_remove_column_widget()

    # remove record
    def generate_remove_record_widget(self, obj=None):
        self.table_ui()

        """
        ,_____________________________,
        | column | element |          |
        |--------|---------|          |
        | column | element |          |
        |--------|---------|  remove  |
        |  ...   |   ...   |          |
        |------------------|          |
        |   add condition  |          |
        |__________________|__________|
        """

        remove_record_widget = BoxLayout(size_hint_y=0.2)

        # several conditions
        conditions = BoxLayout(orientation='vertical', size_hint_x=4)

        # first condition
        condition = BoxLayout()
        condition.add_widget(TextInput(multiline=False, size_hint_x=1, text="column title"))
        condition.add_widget(TextInput(multiline=False, size_hint_x=1, text="element"))

        conditions.add_widget(condition)

        # buttons
        button_add_condition = Button(text="add_condition")
        button_add_condition.bind(on_press=self.table_tool_remove_record_add_condition)

        button_remove = Button(text="remove")
        button_remove.bind(on_press=self.table_tool_remove_record)

        remove_record_widget.add_widget(conditions)
        remove_record_widget.add_widget(button_add_condition)
        remove_record_widget.add_widget(button_remove)

        self.main_layout.children[0].add_widget(remove_record_widget)

    def table_tool_remove_record_add_condition(self, obj=None):
        condition = BoxLayout()
        condition.add_widget(TextInput(multiline=False, size_hint_x=1, text="column title"))
        condition.add_widget(TextInput(multiline=False, size_hint_x=1, text="element"))
        self.main_layout.children[0].children[0].children[2].add_widget(condition)

    def table_tool_remove_record(self, obj=None):

        conditions = dict()
        for condition_box in self.main_layout.children[0].children[0].children[2].children:
            column_title = condition_box.children[1].text
            element = condition_box.children[0].text
            conditions[str(column_title)] = element

        records_to_remove = list()
        first_condition = True

        for condition in conditions:

            #   condition    | conditions.get(condition)
            #  column_title  |         element

            print(condition, conditions.get(condition))
            suitable_records = self.table.record_find(condition, conditions.get(condition))
            print(suitable_records)
            if first_condition:
                records_to_remove = suitable_records
                first_condition = False
            else:
                records_to_remove = list(set(records_to_remove) & set(suitable_records))

        quantity_of_records_were_deleted = len(records_to_remove)
        for record in records_to_remove:
            # print(record.elements)
            self.table.record_remove(record)

        # ### self.main_layout.children[0].children[0].children[2].children[0].children: # condition values
        # ### self.main_layout.children[0].children[0].children[2].children[0] # box with one condition
        # ### self.main_layout.children[0].children[0].children[2] # box with conditions boxes
        # ### self.main_layout.children[0].children[0] # record_remove_widget

        self.table_ui()
        self.generate_remove_record_widget()

        info_text = "There are no records with the specified conditions"
        if quantity_of_records_were_deleted != 0:
            info_text = f"{quantity_of_records_were_deleted} records where deleted"
            print(info_text)
        self.open_popup(info_text)

    def open_popup(self, text):
        popup_layout = BoxLayout(orientation="vertical")
        button = Button(text='Закрыть')
        label = Label(text=text)
        popup_layout.add_widget(label)
        popup_layout.add_widget(button)

        popup = Popup(title='Remove record', content=popup_layout, size_hint=(0.5, 0.3))
        button.bind(on_press=popup.dismiss)
        popup.open()

    def build(self):
        return self.main_layout
