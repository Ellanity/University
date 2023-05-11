import math

from AppControllerClass import AppController
from functools import partial

from kivy.app import App
from kivy.uix.label import Label
from kivy.uix.button import Button
from kivy.uix.boxlayout import BoxLayout
from kivy.core.window import Window
from kivy.uix.textinput import TextInput

STYLES_SHEET = {
    "main": (54 / 255, 58 / 255, 64 / 255, 1),
    "button": (70 / 255, 70 / 255, 70 / 255, 1),
    "button-mode": (116 / 255, 129 / 255, 145 / 255, 1),
    "button-left-menu": (140 / 255, 163 / 255, 194 / 255, 1),
    "button-table-cell": (168 / 255, 168 / 255, 168 / 255, 1),
}

Window.size = (1000, 600)
Window.clearcolor = STYLES_SHEET["main"]
Window.Title = "DatabaseArts"


class AppInterface(App):

    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self.__controller = AppController()
        self.main_layout = BoxLayout()
        self.table_mode = 0

    def build(self):
        self.constructMainWidget()
        return self.main_layout

    def constructMainWidget(self):
        self.main_layout.clear_widgets()
        # buttons
        self.main_layout.add_widget(
            self.constructTablesButtonsWidget(BoxLayout(orientation='vertical', size_hint=(0.2, 1))))
        # table
        self.main_layout.add_widget(
            self.constructTableWidget(BoxLayout(orientation='vertical')))
        # tables settings
        self.main_layout.add_widget(
            self.constructTableSettingsWidget(BoxLayout(orientation='vertical', size_hint=(0.1, 1))))

    def constructTablesButtonsWidget(self, widget):
        # button to change display mode
        change_mode_button = Button(text=f"MODE: {self.table_mode}",
                                    background_color=STYLES_SHEET["button-mode"],
                                    halign="center", valign="middle", size_hint=(1, 0.1))
        change_mode_button.bind(size=change_mode_button.setter('text_size'))
        widget.add_widget(change_mode_button)
        # other buttons
        buttons = BoxLayout(orientation='vertical', size_hint=(1, 0.9))
        # buttons mode 0
        if self.table_mode == 0:
            # show buts of all types tabs (classes, entities, properties and other if needed)
            # in them add/edit/delete for every
            change_mode_button.bind(on_press=partial(self.changeTableDisplayMode, 1))
            # create buttons with tables names
            for table in self.__controller.tables:
                table_button = Button(text=table, background_color=STYLES_SHEET["button-left-menu"],
                                      halign="center", valign="middle")
                table_button.bind(size=table_button.setter('text_size'))
                button_callback_function = partial(self.widgetEventFunction, self.__controller.changeCurrentTable, table)
                table_button.bind(on_press=button_callback_function)
                buttons.add_widget(table_button)
        # buttons mode 0
        if self.table_mode == 1:
            change_mode_button.bind(on_press=partial(self.changeTableDisplayMode, 0))
            # special queries

            argument_input = TextInput(text="ARG", size_hint=(1, 0.2))
            # Exhibition Info
            buttons.add_widget(argument_input)
            first_query_name = "Starts from"
            special_query_button_first = Button(text=f"{first_query_name}\n[ARG=SUBSTR]",
                                                background_color=STYLES_SHEET["button-left-menu"],
                                                halign="center", valign="middle", size_hint=(1, 0.2))
            special_query_button_first.bind(on_press=partial(self.widgetEventFunction,
                                                             self.__controller.specialQueryFirst, argument_input))
            special_query_button_first.bind(size=special_query_button_first.setter('text_size'))
            # Halls in City Info

            second_query_name = "Object is"
            special_query_button_second = Button(text=f"{second_query_name}\n[ARG=OBJECT]",
                                                 background_color=STYLES_SHEET["button-left-menu"],
                                                 halign="center", valign="middle", size_hint=(1, 0.2))
            special_query_button_second.bind(on_press=partial(self.widgetEventFunction,
                                                              self.__controller.specialQuerySecond, argument_input))
            special_query_button_second.bind(size=special_query_button_second.setter('text_size'))
            # All Exhibitions Now Info

            third_query_name = "Subject Object"
            special_query_button_third = Button(text=f"{third_query_name}\n[ARG=SUBJ,OBJ]",
                                                background_color=STYLES_SHEET["button-left-menu"],
                                                halign="center", valign="middle", size_hint=(1, 0.2))
            special_query_button_third.bind(size=special_query_button_third.setter('text_size'))
            special_query_button_third.bind(on_press=partial(self.widgetEventFunction,
                                                             self.__controller.specialQueryThird, argument_input))

            buttons.add_widget(special_query_button_first)
            buttons.add_widget(special_query_button_second)
            buttons.add_widget(special_query_button_third)

            additional_info_label = Label(size_hint=(1, 0.4))
            
            if self.__controller.additional_info != "" and self.__controller.additional_info is not None:
                additional_info_label = Button(text=str(self.__controller.additional_info), size_hint=(1, 0.4),
                                               background_color=STYLES_SHEET["button-table-cell"],
                                               disabled=True, halign="center", valign="middle")
                additional_info_label.bind(size=additional_info_label.setter('text_size'))
            buttons.add_widget(additional_info_label)
            buttons.add_widget(BoxLayout())

        widget.add_widget(buttons)

        return widget

    def changeTableDisplayMode(self, new_mode, *args):
        self.table_mode = new_mode
        self.__controller.changeCurrentTable(table_name=self.__controller.current_table_name, change_anyway=True)
        self.updateTable()

    def constructTableWidget(self, widget):
        # if no table
        if not self.__controller.current_table_name:
            return widget

        # create columns names in top
        columns_widget = BoxLayout(size_hint=(1, 0.1))
        columns_widget.add_widget(Label(text="#", size_hint=(0.3, 1)))
        for column in self.__controller.current_columns:
            lab = Label(text=str(column), halign="center", valign="middle")
            lab.bind(size=lab.setter('text_size'))
            columns_widget.add_widget(lab)
        if self.table_mode == 0:
            columns_widget.add_widget(BoxLayout(size_hint=(0.25, 1)))
        widget.add_widget(columns_widget)

        # for changing record
        text_inputs = []
        previous_data_saver = []
        # create table (need kivymd?)
        page_records_widget = BoxLayout(orientation='vertical', size_hint=(1, 0.8))
        first_record_index = self.__controller.current_page * self.__controller.quantity_of_records_on_page
        for record_index in range(first_record_index, first_record_index + self.__controller.quantity_of_records_on_page):
            record_widget = BoxLayout(size_hint=(1, 0.9 / self.__controller.quantity_of_records_on_page))
            try:
                record_buttons = []
                # add number to record
                if self.__controller.current_records[record_index]:
                    if self.table_mode == 0:
                        num_button = Button(text=str(record_index + 1), size_hint=(0.3, 1),
                                            background_color=STYLES_SHEET["button"], halign="center",
                                            valign="middle")
                    else:
                        num_button = Button(text=str(record_index + 1), size_hint=(0.3, 1), disabled=True,
                                            background_color=STYLES_SHEET["button"], halign="center",
                                            valign="middle")
                    num_button.bind(size=num_button.setter('text_size'))
                    num_button.bind(on_press=partial(self.changeInputsToButtonsData, text_inputs, record_buttons,
                                                     previous_data_saver))
                    record_widget.add_widget(num_button)
                # show record
                # for data in self.__controller.current_records[record_index]:
                for index in range(len(self.__controller.current_records[record_index])):
                    data = self.__controller.current_records[record_index][index]
                    if self.__controller.current_columns[index] == "class":
                        but = Button(text=str(data), background_color=STYLES_SHEET["button-table-cell"],
                                     disabled=False, halign="center", valign="middle")
                        # but.bind(on_press=partial(self.__controller.changeCurrentTable, data, True))
                        but.bind(on_press=partial(self.widgetEventFunction, self.__controller.changeCurrentTable, data, True))
                    else:
                        but = Button(text=str(data), background_color=STYLES_SHEET["button-table-cell"],
                                     disabled=True, halign="center", valign="middle")
                    but.bind(size=but.setter('text_size'))
                    record_widget.add_widget(but)
                    record_buttons.append(but)
                # delete record
                if self.table_mode == 0:
                    but_del = Button(text="X", background_color=STYLES_SHEET["button"],
                                     halign="center", valign="middle", size_hint=(0.25, 1))
                    but_del.bind(size=but_del.setter('text_size'))
                    but_del.bind(on_press=partial(self.widgetEventFunction, self.__controller.deleteRecord,
                                                  record_buttons, self.__controller.current_table_name, True))
                    record_widget.add_widget(but_del)
            except Exception as ex:
                pass
            page_records_widget.add_widget(record_widget)
        widget.add_widget(page_records_widget)

        if self.__controller.current_table_name not in self.__controller.tables or \
                self.__controller.current_table_name not in self.__controller.tables_can_add_record:
            return widget

        create_new_record_widget = BoxLayout(size_hint=(1, 0.1))
        # create new record constructor
        if self.table_mode == 0:
            # create new record
            create_button = Button(text="+", size_hint=(0.3, 1), background_color=STYLES_SHEET["button"])
            create_new_record_widget.add_widget(create_button)
            for column in self.__controller.current_columns:
                new_text_input = TextInput(text=column)
                create_new_record_widget.add_widget(new_text_input)
                text_inputs.append(new_text_input)
            create_button.bind(on_press=partial(self.widgetEventFunction, self.__controller.addNewRecord, text_inputs,
                                                self.__controller.current_table_name, True))
            # change record
            disabled_change_button = False
            if self.__controller.current_table_name not in self.__controller.tables_can_change_record:
                disabled_change_button = True
            but_change = Button(text="//", background_color=STYLES_SHEET["button"],
                                halign="center", valign="middle", size_hint=(0.25, 1), disabled=disabled_change_button)
            but_change.bind(size=but_change.setter('text_size'))
            but_change.bind(
                on_press=partial(self.widgetEventFunction, self.__controller.changeRecord, text_inputs,
                                 previous_data_saver, self.__controller.current_table_name, True))
            if self.table_mode == 0:
                create_new_record_widget.add_widget(but_change)

        widget.add_widget(create_new_record_widget)
        return widget

    def changeInputsToButtonsData(self, inputs, buttons, previous_data_saver, *args):
        if len(inputs) != len(buttons):
            return
        previous_data_saver.clear()
        for index in range(0, len(inputs)):
            inputs[index].text = buttons[index].text
            previous_data_saver.append(buttons[index].text)

    def constructTableSettingsWidget(self, widget):
        # if no table
        if not self.__controller.current_table_name:
            return widget

        # create previous/next page widget
        page_widget = BoxLayout(orientation='vertical')
        # text
        num_pages = math.ceil(len(self.__controller.current_records)/ self.__controller.quantity_of_records_on_page)
        pages_text = f"Page\n{self.__controller.current_page + 1} / {num_pages}"
        if num_pages == 0:
            pages_text = "No pages"
        label_page = Label(text=pages_text, halign="center", valign="middle", size_hint=(1, 0.12))
        label_page.bind(size=label_page.setter('text_size'))
        page_widget.add_widget(label_page)
        # page_widget.add_widget(Label(text=f"Page: {self.__controller.current_page + 1}", size_hint=(1, 0.125)))
        # buttons
        buttons_page_widget = BoxLayout(size_hint=(1, 0.1))
        if self.__controller.current_page > 0:
            button_page_previous = Button(text="<", background_color=STYLES_SHEET["button"])
        else:
            button_page_previous = Button(text="<", background_color=STYLES_SHEET["button"],
                                          disabled=True)
        if self.__controller.current_page + 1 < \
                math.ceil(len(self.__controller.current_records) / self.__controller.quantity_of_records_on_page):
            button_page_next = Button(text=">", background_color=STYLES_SHEET["button"])
        else:
            button_page_next = Button(text=">", background_color=STYLES_SHEET["button"], disabled=True)
        # bind
        button_page_previous.bind(on_press=partial(self.widgetEventFunction, self.__controller.previousPage))
        button_page_next.bind(on_press=partial(self.widgetEventFunction, self.__controller.nextPage))

        buttons_page_widget.add_widget(button_page_previous)
        buttons_page_widget.add_widget(button_page_next)
        page_widget.add_widget(buttons_page_widget)
        # to fill empty space
        page_widget.add_widget(BoxLayout(size_hint=(1, 1)))
        widget.add_widget(page_widget)
        return widget

    def widgetEventFunction(self, button_callback_func, *args):
        if args is not None:
            button_callback_func(*args)
        else:
            button_callback_func()
        self.updateTable()

    def updateTable(self):
        self.constructMainWidget()
