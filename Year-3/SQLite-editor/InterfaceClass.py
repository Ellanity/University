import math

from AppModelClass import AppModel
from functools import partial

from kivy.app import App
from kivy.uix.label import Label
from kivy.uix.button import Button
from kivy.uix.boxlayout import BoxLayout
from kivy.core.window import Window
from kivy.uix.textinput import TextInput

Window.size = (1000, 600)
Window.clearcolor = (70/255, 80/255, 80/255, 1)
Window.Title = "DatabaseArts"


class Interface(App):

    def __init__(self, model: AppModel, **kwargs):
        super().__init__(**kwargs)
        self.model = model
        self.main_layout = BoxLayout()

    def build(self):
        self.constructMainWidget()
        return self.main_layout

    def constructMainWidget(self):
        self.main_layout.clear_widgets()
        self.main_layout.add_widget(self.constructTablesButtonsWidget(BoxLayout(orientation='vertical', size_hint=(.2, 1))))
        self.main_layout.add_widget(self.constructTableWidget(BoxLayout(orientation='vertical')))
        self.main_layout.add_widget(self.constructTableSettingsWidget(BoxLayout(orientation='vertical', size_hint=(.1, 1))))

    def constructTablesButtonsWidget(self, widget):
        # create buttons with tables names
        for table in self.model.tables:
            table_button = Button(text=table[0], background_color=(130/255, 160/255, 150/255, 1),
                                  halign="center", valign="middle")
            table_button.bind(size=table_button.setter('text_size'))
            button_callback_function = partial(self.widgetEventFunction, self.model.changeCurrentTable, table[0])
            table_button.bind(on_press=button_callback_function)
            widget.add_widget(table_button)
        return widget

    def constructTableWidget(self, widget):
        # if no table
        if not self.model.current_table_name:
            return widget

        # create columns names in top
        columns_widget = BoxLayout(size_hint=(1, 0.1))
        columns_widget.add_widget(Label(text="#", size_hint=(0.3, 1)))
        for column in self.model.current_columns:
            lab = Label(text=str(column[1]), halign="center", valign="middle")
            lab.bind(size=lab.setter('text_size'))
            columns_widget.add_widget(lab)
        columns_widget.add_widget(BoxLayout(size_hint=(0.25, 1)))
        widget.add_widget(columns_widget)

        text_inputs = []  # for changing record
        previous_data_saver = []  # for changing record
        # create table (need kivymd?)
        page_records_widget = BoxLayout(orientation='vertical', size_hint=(1, 0.8))
        first_record_index = self.model.current_page * self.model.quantity_of_records_on_page
        for record_index in range(first_record_index, first_record_index + self.model.quantity_of_records_on_page):
            record_widget = BoxLayout(size_hint=(1, 0.9/self.model.quantity_of_records_on_page))
            try:
                record_buttons = []
                # add number to record
                if self.model.current_records[record_index]:
                    num_button = Button(text=str(record_index + 1), size_hint=(0.3, 1), background_color=(120/255, 140/255, 140/255, 1), halign="center", valign="middle")
                    num_button.bind(size=num_button.setter('text_size'))
                    num_button.bind(on_press=partial(self.changeInputsToButtonsData, text_inputs, record_buttons, previous_data_saver))
                    record_widget.add_widget(num_button)
                # show record
                for data in self.model.current_records[record_index]:
                    but = Button(text=str(data), background_color=(120/255, 140/255, 140/255, 1), disabled=True, halign="center", valign="middle")
                    but.bind(size=but.setter('text_size'))
                    record_widget.add_widget(but)
                    record_buttons.append(but)
                # delete record
                but_del = Button(text="X", background_color=(100 / 255, 120 / 255, 120 / 255, 1),
                                 halign="center", valign="middle", size_hint=(0.25, 1))
                but_del.bind(size=but_del.setter('text_size'))
                but_del.bind(on_press=partial(self.widgetEventFunction, self.model.deleteRecord, record_buttons))
                record_widget.add_widget(but_del)
            except Exception as ex:
                pass
            page_records_widget.add_widget(record_widget)
        widget.add_widget(page_records_widget)

        # create new record
        create_new_record_widget = BoxLayout(size_hint=(1, 0.1))
        create_button = Button(text="+", size_hint=(0.3, 1), background_color=(100/255, 120/255, 120/255, 1))
        create_new_record_widget.add_widget(create_button)
        for column in self.model.current_columns:
            new_text_input = TextInput(text=column[1])
            create_new_record_widget.add_widget(new_text_input)
            text_inputs.append(new_text_input)
        create_button.bind(on_press=partial(self.widgetEventFunction, self.model.addNewRecord, text_inputs))
        # change record
        but_change = Button(text="//", background_color=(100 / 255, 120 / 255, 120 / 255, 1),
                            halign="center", valign="middle", size_hint=(0.25, 1))
        but_change.bind(size=but_change.setter('text_size'))
        but_change.bind(on_press=partial(self.widgetEventFunction, self.model.changeRecord, text_inputs, previous_data_saver))
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
        if not self.model.current_table_name:
            return widget

        # create previous/next page widget
        page_widget = BoxLayout(orientation='vertical')
        # text
        lab_page = Label(text=f"Page: {self.model.current_page + 1}",
                         halign="center", valign="middle", size_hint=(1, 0.125))
        lab_page.bind(size=lab_page.setter('text_size'))
        page_widget.add_widget(lab_page)
        # page_widget.add_widget(Label(text=f"Page: {self.model.current_page + 1}", size_hint=(1, 0.125)))
        # buttons
        buttons_page_widget = BoxLayout(size_hint=(1, 0.125))
        if self.model.current_page > 0:
            button_page_previous = Button(text="<", background_color=(100/255, 120/255, 120/255, 1))
        else:
            button_page_previous = Button(text="<", background_color=(100/255, 120/255, 120/255, 1), disabled=True)
        if self.model.current_page + 1 < \
                math.ceil(len(self.model.current_records) / self.model.quantity_of_records_on_page):
            button_page_next = Button(text=">", background_color=(100/255, 120/255, 120/255, 1))
        else:
            button_page_next = Button(text=">", background_color=(100/255, 120/255, 120/255, 1), disabled=True)
        # bind
        button_page_previous.bind(on_press=partial(self.widgetEventFunction, self.model.previousPage))
        button_page_next.bind(on_press=partial(self.widgetEventFunction, self.model.nextPage))

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
