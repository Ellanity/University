import string
import PyPDF2 as PyPDF2
import nltk
from tkinter import filedialog, ttk
from tkinter import *
from PIL import ImageTk, Image

from WordStructures import *


STYLES_SHEET = {
    "BACKGROUND_COLOR": "#383838",
    "BUTTONS_COLOR": "#454546",
    "BUTTONS_BORDER_COLOR": "#454546",
    "BUTTONS_ACTIVE_COLOR": "#5b5b5c",
    "BUTTONS_TEXT_COLOR": "white",
    "BUTTONS_ACTIVE_TEXT_COLOR": "white",
    "ENTRY_COLOR": "#515151",
    "ENTRY_TEXT_COLOR": "white",
}
help_popup_counter = 0


class CustomTitleBar(Frame):
    def __init__(self, master, bg_color, *args, **kwargs):
        super().__init__(master, *args, **kwargs)
        # Define the style for the title bar
        self.config(bg=bg_color)

        class ButtonCustomTitleBar(Button):
            def __init__(self, parent, name, command, **kw):
                super().__init__(**kw)
                self.button_border = Frame(parent, highlightbackground=STYLES_SHEET["BUTTONS_BORDER_COLOR"],
                                           highlightthickness=2, bd=0, bg=bg_color)
                self.button = Button(self.button_border, text=name, command=command, font=("Arial", 11),
                                     bg=STYLES_SHEET["BUTTONS_COLOR"],
                                     fg=STYLES_SHEET["BUTTONS_TEXT_COLOR"],
                                     activeforeground=STYLES_SHEET["BUTTONS_ACTIVE_TEXT_COLOR"],
                                     activebackground=STYLES_SHEET["BUTTONS_ACTIVE_COLOR"])
                self.button.config(relief=FLAT, bd=0)

            def pack(self):
                self.button.pack(fill=BOTH, padx=20, pady=0)
                self.button_border.pack(side=RIGHT, padx=5, pady=2, fill=BOTH)

        def on_icon_click_return_window(event):
            self.master.update_idletasks()
            self.master.overrideredirect(True)
            self.master.state('normal')
            #
            self.master.attributes('-topmost', True)
            # self.master.attributes("-topmost", True)

        # ### Create the title bar elements
        # Load the icon image and resize it to fit the title bar height
        icon_size = 64
        self.icon = PhotoImage(file='icon.png').subsample(int(icon_size / 16) or 1)
        self.icon_label = Label(self, image=self.icon, background=bg_color)
        self.title_label = Label(self, text=master.title(), font=('Courier', 10), background=bg_color, foreground="white")
        self.min_button = ButtonCustomTitleBar(self, name='_', command=self.minimize_in_icon)
        # self.min_button.button.bind("<Map>", on_icon_click_return_window)
        self.max_button = ButtonCustomTitleBar(self, name='□', command=self.toggle_maximize)
        self.close_button = ButtonCustomTitleBar(self, name='X', command=master.destroy)

        # Initialize the window state to not maximized
        self.maximized = True
        # Pack the title bar elements
        self.icon_label.pack(side=LEFT, padx=5)
        self.title_label.pack(side=LEFT, padx=5)
        self.close_button.pack()
        self.max_button.pack()
        self.min_button.pack()

        # Bind mouse events to the title bar
        self.bind('<ButtonPress-1>', self.on_drag_start)
        self.bind('<B1-Motion>', self.on_drag_motion)

        # Keep track of the last position of the mouse
        self.last_x = 0
        self.last_y = 0

    def minimize_in_icon(self):
        return
        self.master.update_idletasks()
        self.master.overrideredirect(False)
        self.master.state('iconic')

    def toggle_maximize(self):
        return
        if self.maximized:
            self.master.state("normal")
            self.max_button.text='□'
            self.maximized = False
        else:
            self.master.state("zoomed")
            self.max_button.text = '|_|'  # '🗖'
            self.maximized = True

    def on_drag_start(self, event):
        return
        # Record the position of the mouse when dragging starts
        self.last_x = event.x
        self.last_y = event.y

    def on_drag_motion(self, event):
        return
        # Compute the new position of the window based on the mouse movement
        new_x = self.winfo_rootx() + event.x - self.last_x
        new_y = self.winfo_rooty() + event.y - self.last_y
        self.master.geometry(f"+{new_x}+{new_y}")


class Application(Frame):
    def __init__(self, master=None, **kwargs):
        super().__init__(master, **kwargs)
        self.master = master
        self.word_forms = WordForms()
        self.__initVariables__()
        self.__initUI__()

    def __initVariables__(self):
        self.last_state = "none"
        self.tags_dict = {}
        self.load_tags_from_file()


    def __initUI__(self):
        self.master.title("PDF Text Processor")
        self.master.state('zoomed')
        self.master.configure(background=STYLES_SHEET["ENTRY_COLOR"])
        self.master.iconbitmap(default="icon.ico")
        self.pack()

        # self.master.overrideredirect(True)
        # self.master.lift()
        # self.master.attributes("-topmost", True)

        # self.custom_titlebar = CustomTitleBar(self.master, STYLES_SHEET["ENTRY_COLOR"])
        # self.custom_titlebar.pack(side=TOP, fill="x")

        # content frame
        self.content = Frame(self.master)
        self.content.pack(fill=BOTH, expand=True)
        self.content.config(bg=STYLES_SHEET["BACKGROUND_COLOR"])

        # input text
        self.input_text_scrollbar = Scrollbar(self.content, orient='vertical')
        self.input_text_scrollbar.pack(side=RIGHT, fill='y')
        self.input_text = Text(self.content, yscrollcommand=self.input_text_scrollbar.set)
        self.input_text_scrollbar.config(command=self.input_text.yview)
        self.input_text.pack(side=RIGHT, fill=BOTH, expand=True)

        # output text
        self.output_text_scrollbar = Scrollbar(self.content, orient='vertical',
                                               bg=STYLES_SHEET["ENTRY_COLOR"],
                                               activebackground=STYLES_SHEET["BACKGROUND_COLOR"],
                                               highlightcolor=STYLES_SHEET["BACKGROUND_COLOR"])
        self.output_text_scrollbar.pack(side=RIGHT, fill='y')
        self.output_text = Text(self.content, yscrollcommand=self.output_text_scrollbar.set)
        self.output_text_scrollbar.config(command=self.output_text.yview)
        self.output_text.pack(side=RIGHT, fill=BOTH, expand=True)

        # ### Buttons
        class ButtonCustom:
            def __init__(self, parent, name, command):
                self.button_border = Frame(parent, highlightbackground=STYLES_SHEET["BUTTONS_BORDER_COLOR"],
                                           highlightthickness=5, bd=0)
                self.button = Button(self.button_border, text=name, command=command, font=("Arial", 11),
                                     bg=STYLES_SHEET["BUTTONS_COLOR"],
                                     fg=STYLES_SHEET["BUTTONS_TEXT_COLOR"],
                                     activeforeground=STYLES_SHEET["BUTTONS_ACTIVE_TEXT_COLOR"],
                                     activebackground=STYLES_SHEET["BUTTONS_ACTIVE_COLOR"])
                self.button.config(relief=FLAT, bd=0)

            def pack(self, **kw):
                self.button.pack(fill=BOTH, padx=0, pady=0)
                if len(kw) > 0:
                    self.button_border.pack(**kw)
                else:
                    self.button_border.pack(side=TOP, padx=5, pady=5, fill=BOTH)

        # load data from file
        self.load_file_button = ButtonCustom(self.content, "Load PDF File", self.load_file)
        self.load_file_button.pack()

        # process data
        self.process_button = ButtonCustom(self.content, "Process data", self.process_data)
        self.process_button.pack()

        # save in file
        self.save_button = ButtonCustom(self.content, "Save in file", self.save_data)
        self.save_button.pack()

        # filter
        self.pos_var = StringVar(self.content)
        self.pos_var.set('all')

        self.pos_options = ["all"] + [f"{k} - {v}" for k, v in self.tags_dict.items()]
        self.pos_options.insert(0, "all")

        self.style = ttk.Style(self)
        self.style.configure("TMenubutton", relief=FLAT, font=("Courier", 12), bd=0, highlightthickness=0,
                             arrowcolor=STYLES_SHEET["ENTRY_TEXT_COLOR"],
                             foreground=STYLES_SHEET["ENTRY_TEXT_COLOR"],
                             background=STYLES_SHEET["ENTRY_COLOR"])

        self.pos_menu = ttk.OptionMenu(self.content, self.pos_var, *self.pos_options)
        self.pos_menu.pack(side=TOP, padx=5, pady=5, fill=BOTH)
        self.pos_menu["menu"].config(relief=FLAT, bg=STYLES_SHEET["ENTRY_COLOR"],
                                     fg=STYLES_SHEET["ENTRY_TEXT_COLOR"], font=("Courier", 10),
                                     borderwidth=0, selectcolor="white")

        self.filter_button = ButtonCustom(self.content, "Filter",
                                          command=lambda: self.apply_filter(self.pos_var.get()))
        self.filter_button.pack()

        # search
        self.search_var = StringVar(self.content)
        self.search_entry = Entry(self.content, textvariable=self.search_var, font=("Courier", 12),
                                  bg=STYLES_SHEET["ENTRY_COLOR"], fg=STYLES_SHEET["ENTRY_TEXT_COLOR"])
        self.search_entry.pack(side=TOP, padx=5, pady=5, fill=BOTH)
        self.search_entry.configure(borderwidth=5, relief=FLAT)

        self.search_button = ButtonCustom(self.content, "Search word",
                                          command=lambda: self.do_search(self.search_var.get()))
        self.search_button.pack()

        # apply updates
        self.apply_updates_button = ButtonCustom(self.content, "Apply updates", self.update_word_forms)
        self.apply_updates_button.pack()

        # apply updates
        self.apply_updates_button = ButtonCustom(self.content, "Help", self.show_help_popup)
        self.apply_updates_button.pack(side=BOTTOM, padx=5, pady=5, fill=BOTH)

    def show_help_popup(self):
        global help_popup_counter
        if help_popup_counter >= 1:
            return
        help_popup_counter += 1

        # Create a new window
        self.help_popup = Toplevel(self.master)
        self.help_popup.configure(bg=STYLES_SHEET["BACKGROUND_COLOR"])
        self.popup_sizes = (660, 720)
        self.help_popup.geometry(f"{self.popup_sizes[0]}x{self.popup_sizes[1]}")
        # self.help_popup.geometry("660x720")
        self.help_popup.resizable(False, False)
        self.help_popup.title("PDF Text Processor - Help")
        # Create a canvas to hold the images and info
        canvas = Canvas(self.help_popup)
        canvas.config(bg=STYLES_SHEET["BACKGROUND_COLOR"])
        # Add a scrollbar to the canvas
        scrollbar = Scrollbar(self.help_popup, orient=VERTICAL, command=canvas.yview)
        scrollbar.pack(side=RIGHT, fill=Y)
        # Configure the canvas to use the scrollbar
        canvas.configure(yscrollcommand=scrollbar.set)
        # Create a frame to hold the images and info
        frame = Frame(canvas)
        frame.config(bg=STYLES_SHEET["BACKGROUND_COLOR"])
        # Add the frame to the canvas
        canvas.create_window((0, 0), window=frame, anchor='nw')

        class LabelHelpText:
            def __init__(self, master, text, **kw):
                if len(kw) > 0:
                    self.label = Label(master, text=text, **kw)
                else:
                    self.label = Label(master, text=text, wraplength=620, justify=LEFT, font=("Courier", 12),
                                       bg=STYLES_SHEET["BACKGROUND_COLOR"], fg=STYLES_SHEET["BUTTONS_TEXT_COLOR"])

            def pack(self, **kw):
                if len(kw) > 0:
                    self.label.pack(**kw)
                else:
                    self.label.pack(side=TOP, fill=BOTH, padx=5)

        class LabelHelpImage:
            def __init__(self, master, image_file_name, popup_sizes):
                self.image = Image.open(image_file_name)
                ratio = (popup_sizes[0] - 20) / self.image.size[0]
                self.image = self.image.resize((int(self.image.size[0] * ratio), int(self.image.size[1] * ratio)))
                self.photo = ImageTk.PhotoImage(self.image)
                self.label = Label(master, image=self.photo, bg=STYLES_SHEET["BACKGROUND_COLOR"])

            def pack(self):
                self.label.pack(side=TOP, fill=BOTH)

        texts = []
        with open("help.txt", "r", encoding="utf-8") as file:
            lines = file.readlines()
            for line in lines:
                if line[0] == "@":
                    if lines.index(line) != len(lines) - 1:
                        texts.append("\n")
                    else:
                        texts.append(texts.pop() + "\n\n")
                else:
                    texts.append(texts.pop() + line)

        # Add images and info to the frame
        # it is possible to combine this and the previous cycle
        # for optimization, but who needs it, do I? no.
        # But it can be beautiful if file will contains from
        # texts divided by tags of images paths like @images/image.png.
        if len(texts) > 0:
            self.images = []
            for text_index in range(len(texts)):
                try:
                    self.images.append(LabelHelpImage(frame, f"images/img-help-{text_index + 1}.png", self.popup_sizes))
                    self.images[text_index].pack()
                except Exception as ex:
                    pass
                self.text = LabelHelpText(frame, texts[text_index])
                self.text.pack()

        # Update the canvas scroll region to include the frame
        frame.update_idletasks()
        canvas.configure(scrollregion=canvas.bbox('all'))
        canvas.pack(fill=BOTH, expand=True)

        self.help_popup.protocol("WM_DELETE_WINDOW", lambda: self.close_help_popup(self.help_popup))

    def close_help_popup(self, popup):
        global help_popup_counter
        help_popup_counter -= 1
        popup.destroy()

    def load_tags_from_file(self):
        try:
            with open("tags.txt", "r", encoding="utf-8") as file:
                lines = file.readlines()
            self.tags_dict = {}
            for line in lines:
                key, value = line.strip().split("@")
                self.tags_dict[key] = value
        except Exception as ex:
            print(ex)

    def update_word_forms(self):
        self.last_state = "update_word_forms"
        text = self.output_text.get('1.0', END)
        lines = text.split("\n")
        for line in lines:
            try:
                word, tags, count = re.findall(r'(\w+) \((.+)\) - (\d+)', line)[0]
                tags = [t.strip() for t in re.split(r',\s*', tags)]
                if line[0] != "#":
                    self.word_forms.update(word, tags[0], tags[1], tags[2], tags[3], count)
                else:
                    self.word_forms.delete(word)
            except Exception as ex:
                pass
        self.word_forms.sort()
        self.update_output()

    def load_file(self):
        self.last_state = "load_file"
        filename = filedialog.askopenfilename(filetypes=[("PDF files", "*.pdf")])
        if filename:
            with open(filename, 'rb') as file:
                reader = PyPDF2.PdfReader(file)
                # noinspection PyProtectedMember
                num_pages = reader._get_num_pages()
                text = ""
                for page_index in range(num_pages):
                    page = reader.pages[page_index]
                    text += page.extract_text() + "\n\n\n"

                self.input_text.delete('1.0', END)
                self.input_text.insert('1.0', text)

    def process_data(self):
        self.last_state = "process_data"
        input_text = self.input_text.get(1.0, END)
        processed_text = input_text.lower().translate(str.maketrans("", "", string.punctuation))
        # words = nltk.word_tokenize(input_text)
        words = nltk.word_tokenize(processed_text)

        self.word_forms.clear()
        for word in words:
            pos = nltk.pos_tag([word])[0][1]
            self.word_forms.add(word, pos, '', '', '')

        self.word_forms.sort()  # call sort method before accessing sorted_forms attribute
        self.update_output()

    def save_data(self):
        self.last_state = "save_data"
        filename = filedialog.asksaveasfilename(defaultextension=".csv")
        if filename:
            self.word_forms.save(filename)

    def apply_filter(self, pos_filter):
        self.last_state = "filter_data"
        self.filtered_forms = []
        pos_filter = pos_filter.split(" - ")[0]
        for form in self.word_forms.sorted_forms:
            if pos_filter == 'all' or self.word_forms.tags[form].pos.startswith(pos_filter):
                self.filtered_forms.append(form)
        self.update_output()

    def do_search(self, search_string):
        self.last_state = "do_search"
        self.searched_forms = []
        for form in self.word_forms.sorted_forms:
            if search_string.lower() in form.lower():
                self.searched_forms.append(form)
        self.update_output()

    def update_output(self):
        self.output_text.delete(1.0, END)

        data_set = []
        if self.last_state == "do_search":  # hasattr(self, 'searched_forms'):
            data_set = self.searched_forms
        elif self.last_state == "filter_data":  # hasattr(self, 'filtered_forms'):
            data_set = self.filtered_forms
        else:
            self.word_forms.sort()
            data_set = self.word_forms.sorted_forms
        for form in data_set:
            tag = self.word_forms.tags[form]
            frequency = self.word_forms.forms[form]
            self.output_text.insert(END, f"{form} ({tag.pos}, {tag.gender}, {tag.number}, {tag.case}) - {frequency}\n")