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
                button_table_box = BoxLayout()  # padding=10)
                button_table = Button(text=file_name)
                button_table.bind(on_release=self.open_table)
                button_table_box.add_widget(button_table)
                table_buttons_widget.add_widget(button_table_box)
        self.main_layout.add_widget(table_buttons_widget)

        # new table
        new_table = BoxLayout(padding=30)
        button_new_table = Button(text="Create new table")
        table_title = TextInput(text="Table_name", multiline=False)
        new_table.add_widget(table_title)
        new_table.add_widget(button_new_table)
        button_new_table.bind(on_release=self.create_new_table)
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
    def table_ui(self, obj=None):
        self.main_layout.clear_widgets()
        self.generate_table_widget()

        left_menu = BoxLayout(orientation='vertical')
        right_working_area = BoxLayout(orientation='vertical', size_hint=(4, 1))

        left_menu.add_widget(self.generate_table_tools_widget())
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

        button_table = Button(text="table")  # , size_hint_y=0.1)
        button_table.bind(on_release=self.table_ui)
        tools_widget.add_widget(button_table)

        button_save = Button(text="save")  # , size_hint_y=0.1)
        button_save.bind(on_release=self.generate_save_widget)
        tools_widget.add_widget(button_save)

        button_add_record = Button(text="record add")  # , size_hint_y=0.1)
        button_add_record.bind(on_release=self.generate_add_record_widget)
        tools_widget.add_widget(button_add_record)

        button_remove_record = Button(text="record remove")  # , size_hint_y=0.1)
        button_remove_record.bind(on_release=self.generate_remove_record_widget)
        tools_widget.add_widget(button_remove_record)

        button_search = Button(text="record search")  # , size_hint_y=0.1)
        button_search.bind(on_release=self.generate_search_record_widget)
        tools_widget.add_widget(button_search)

        button_change_record = Button(text="record change")  # , size_hint_y=0.1)
        button_change_record.bind(on_release=self.generate_change_record_widget)
        tools_widget.add_widget(button_change_record)

        button_add_column = Button(text="column add")  # , size_hint_y=0.1)
        button_add_column.bind(on_release=self.generate_add_column_widget)
        tools_widget.add_widget(button_add_column)

        button_remove_column = Button(text="column remove")  # , size_hint_y=0.1)
        button_remove_column.bind(on_release=self.generate_remove_column_widget)
        tools_widget.add_widget(button_remove_column)

        button_back = Button(text="<= back")  # , size_hint_y=0.1)
        button_back.bind(on_release=self.menu_choose_table)
        tools_widget.add_widget(button_back)

        return tools_widget

    # #################################
    # ###  implementation of tools  ###
    # #################################

    # SEARCH RECORD
    """
    ,______________________________,________,
    | column | element |           |        |
    |--------|---------|           |        |
    | column | element |    add    | search |
    |--------|---------| condition |        |
    |  ...   |   ...   |           |        |
    |________|_________|___________|________|
    """
    def generate_search_record_widget(self, obj=None):
        self.table_ui()

        search_record_widget = BoxLayout(size_hint_y=0.2)

        # several conditions
        conditions = BoxLayout(orientation='vertical', size_hint_x=4)

        # first condition
        condition = BoxLayout()
        condition.add_widget(TextInput(multiline=False, size_hint_x=1, text="column title"))
        condition.add_widget(TextInput(multiline=False, size_hint_x=1, text="element"))

        conditions.add_widget(condition)

        # buttons
        button_add_condition = Button(text="add_condition")
        button_add_condition.bind(on_release=self.table_tool_search_record_add_condition)

        button_remove = Button(text="search")
        button_remove.bind(on_release=self.table_tool_search_record)

        search_record_widget.add_widget(conditions)
        search_record_widget.add_widget(button_add_condition)
        search_record_widget.add_widget(button_remove)

        self.main_layout.children[0].add_widget(search_record_widget)

    def table_tool_search_record_add_condition(self, obj=None):
        condition = BoxLayout()
        condition.add_widget(TextInput(multiline=False, size_hint_x=1, text="column title"))
        condition.add_widget(TextInput(multiline=False, size_hint_x=1, text="element"))
        self.main_layout.children[0].children[0].children[2].add_widget(condition)
        pass

    def table_tool_search_record(self, obj=None):

        conditions = dict()
        for condition_box in self.main_layout.children[0].children[0].children[2].children:
            column_title = condition_box.children[1].text
            element = condition_box.children[0].text
            conditions[str(column_title)] = element

        found_records = list()
        first_condition = True

        for condition in conditions:

            #   condition    | conditions.get(condition)
            #  column_title  |         element

            suitable_records = self.table.record_find(condition, conditions.get(condition))
            if first_condition:
                found_records = suitable_records
                first_condition = False
            else:
                found_records = list(set(found_records) & set(suitable_records))

        all_records = self.table.records
        self.table.records = found_records
        self.table_ui()
        self.generate_search_record_widget()
        self.table.records = all_records

        # ### ---------------------------------------------------------------------------------------------
        # ### self.main_layout.children[0].children[0].children[2].children[0].children: # condition values
        # ### self.main_layout.children[0].children[0].children[2].children[0] # box with one condition
        # ### self.main_layout.children[0].children[0].children[2] # box with conditions boxes
        # ### self.main_layout.children[0].children[0] # record_remove_widget

    # ADD RECORD
    """
    ,__________,__________,_____,_______,
    | element1 | element2 | ... |  add  |
    |__________|__________|_____|_______|
    """
    def generate_add_record_widget(self, obj=None):
        self.table_ui()

        add_record_widget = BoxLayout(size_hint_y=0.1)
        for column in self.table.columns:
            add_record_widget.add_widget(TextInput(multiline=False, size_hint_x=1, text=""))
        button_find = Button(text="add")
        button_find.bind(on_release=self.table_tool_add_record)
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

    # SAVE TABLE
    """
    ,___________________,
    |  no working area  |
    |___________________|
    """
    def generate_save_widget(self, obj=None):
        self.table_ui()

        save_widget = BoxLayout(size_hint_y=0.1)
        save_widget.add_widget(Label(text="wait a second"))

        self.main_layout.children[0].add_widget(save_widget)
        self.table_tool_save()

    def table_tool_save(self, obj=None):
        self.table.save_to_xml()
        self.main_layout.children[0].children[0].children[0].text = "saved"

    # ADD COLUMN
    """
    ,______________,___________,________,
    | column title | type of   |        |
    | to add       | data      |  add   |
    |______________|___________|________|
    """
    def generate_add_column_widget(self, obj=None):
        self.table_ui()

        add_column_widget = BoxLayout(size_hint_y=0.1)
        add_column_widget.add_widget(TextInput(multiline=False, size_hint_x=1, text="column_title"))
        add_column_widget.add_widget(TextInput(multiline=False, size_hint_x=1, text="type of data [str/int]"))
        button_find = Button(text="add")
        button_find.bind(on_release=self.table_tool_add_column)
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

    # REMOVE COLUMN
    """
    ,______________,____________,
    | column title |            |
    | to remove    |   remove   |
    |______________|____________|
    """
    def generate_remove_column_widget(self, obj=None):
        self.table_ui()

        remove_column_widget = BoxLayout(size_hint_y=0.1)
        remove_column_widget.add_widget(TextInput(multiline=False, size_hint_x=1, text="column title"))
        button_find = Button(text="remove")
        button_find.bind(on_release=self.table_tool_remove_column)
        remove_column_widget.add_widget(button_find)

        self.main_layout.children[0].add_widget(remove_column_widget)

    def table_tool_remove_column(self, obj=None):
        # self.table_ui()
        column_title = self.main_layout.children[0].children[0].children[1].text
        self.table.column_remove(column_title)
        self.table_ui()
        self.generate_remove_column_widget()

    # REMOVE RECORD
    """
    ,_______________________________,________,
    | column | element |            |        |
    |--------|---------|            |        |
    | column | element |    add     |        |
    |--------|---------| condition  | remove |
    |  ...   |   ...   |            |        |
    |________|_________|____________|________|
    """
    def generate_remove_record_widget(self, obj=None):
        self.table_ui()


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
        button_add_condition.bind(on_release=self.table_tool_remove_record_add_condition)

        button_remove = Button(text="remove")
        button_remove.bind(on_release=self.table_tool_remove_record)

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

            suitable_records = self.table.record_find(condition, conditions.get(condition))
            if first_condition:
                records_to_remove = suitable_records
                first_condition = False
            else:
                records_to_remove = list(set(records_to_remove) & set(suitable_records))

        quantity_of_records_were_deleted = len(records_to_remove)
        for record in records_to_remove:
            self.table.record_remove(record)

        # ### ---------------------------------------------------------------------------------------------
        # ### self.main_layout.children[0].children[0].children[2].children[0].children: # condition values
        # ### self.main_layout.children[0].children[0].children[2].children[0] # box with one condition
        # ### self.main_layout.children[0].children[0].children[2] # box with conditions boxes
        # ### self.main_layout.children[0].children[0] # record_remove_widget

        self.table_ui()
        self.generate_remove_record_widget()

        info_text = "There are no records with the specified conditions"
        if quantity_of_records_were_deleted != 0:
            info_text = f"{quantity_of_records_were_deleted} records where deleted"
        self.open_popup(info_text)

    # CHANGE RECORD
    """
    ,______________________________,_________,________,
    | column | element |           | column  |        |
    |--------|---------|           | title   |        |
    | column | element | add       |_________| change |
    |--------|---------| condition |         |        |
    |  ...   |   ...   |           | element |        |
    |________|_________|___________|_________|________|
    """
    def generate_change_record_widget(self, obj=None):
        self.table_ui()

        change_record_widget = BoxLayout(size_hint_y=0.2)

        # several conditions
        conditions = BoxLayout(orientation='vertical', size_hint_x=1.5)

        # first condition
        condition = BoxLayout()
        condition.add_widget(TextInput(multiline=False, size_hint_x=1, text="column title"))
        condition.add_widget(TextInput(multiline=False, size_hint_x=1, text="element"))

        conditions.add_widget(condition)

        # buttons
        button_add_condition = Button(text="add\ncondition", size_hint_x=0.5)
        button_add_condition.bind(on_release=self.table_tool_change_record_add_condition)

        # field change record to condition
        replacement_info = BoxLayout(orientation='vertical')
        replacement_info.add_widget(TextInput(multiline=False, size_hint_x=1, text="column title to change"))
        replacement_info.add_widget(TextInput(multiline=False, size_hint_x=1, text="element to change"))

        button_remove = Button(text="change", size_hint_x=0.5)
        button_remove.bind(on_release=self.table_tool_change_record)

        change_record_widget.add_widget(conditions)
        change_record_widget.add_widget(button_add_condition)
        change_record_widget.add_widget(replacement_info)
        change_record_widget.add_widget(button_remove)

        self.main_layout.children[0].add_widget(change_record_widget)

    def table_tool_change_record_add_condition(self, obj=None):
        condition = BoxLayout()
        condition.add_widget(TextInput(multiline=False, size_hint_x=1, text="column title"))
        condition.add_widget(TextInput(multiline=False, size_hint_x=1, text="element"))
        self.main_layout.children[0].children[0].children[3].add_widget(condition)

    def table_tool_change_record(self, obj=None):

        conditions = dict()
        for condition_box in self.main_layout.children[0].children[0].children[3].children:
            column_title = condition_box.children[1].text
            element = condition_box.children[0].text
            conditions[str(column_title)] = element

        element_to_change = self.main_layout.children[0].children[0].children[1].children[0].text
        column_title_to_change = self.main_layout.children[0].children[0].children[1].children[1].text

        records_to_change = list()
        first_condition = True

        for condition in conditions:

            #   condition    | conditions.get(condition)
            #  column_title  |         element

            suitable_records = self.table.record_find(condition, conditions.get(condition))
            if first_condition:
                records_to_change = suitable_records
                first_condition = False
            else:
                records_to_change = list(set(records_to_change) & set(suitable_records))

        quantity_of_records_were_changed = len(records_to_change)
        for record in records_to_change:
            # print(record)
            self.table.record_change(record, column_title_to_change, element_to_change)

        self.table_ui()
        self.generate_change_record_widget()

        info_text = f"{quantity_of_records_were_changed} records where changed"
        self.open_popup(info_text)

    # OTHER TOOLS
    def open_popup(self, text):
        popup_layout = BoxLayout(orientation="vertical")
        button = Button(text='Close')
        label = Label(text=text)
        popup_layout.add_widget(label)
        popup_layout.add_widget(button)

        popup = Popup(title='Table ifo', content=popup_layout, size_hint=(0.5, 0.3))
        button.bind(on_release=popup.dismiss)
        popup.open()

    def build(self):
        return self.main_layout
