"""
# import library
from App import Application
import tkinter as tk

# root = Application(master=tk.Tk())
root = tk.Tk()
canvas = tk.Canvas(root, width=500, height=700, bg="Black", highlightthickness=0)
canvas.pack()
# root.resizable(False, False)

# Initiating EventHandler for taskbar icon
EventHandler = tk.Tk()
EventHandler.attributes("-alpha", 0.0)
EventHandler.lift()


# Minimize Button
def MinimizeClick():
    root.update_idletasks()
    root.overrideredirect(False)
    root.state('iconic')
    EventHandler.withdraw()


def OnIconClickReturnWindow(event):
    root.update_idletasks()
    root.overrideredirect(True)
    root.state('normal')
    EventHandler.deiconify()


Minimize = tk.Button(text='−', command=MinimizeClick)
Minimize.bind("<Map>", OnIconClickReturnWindow)
canvas.create_window(425, 24, window=Minimize, width=50, height=49)
Minimize.config(bg="#242424", fg="white", activebackground="black", justify="center", border="0")


# Button is pressed background changer
def MinimizePressedBackground(event):
    Minimize["background"] = "#242424"


def MinimizeBackground(event):
    Minimize["background"] = "#242424"


def MinimizeChangeColorOnButtonHover(event):
    Minimize.config(cursor="hand2")
    Minimize['background'] = "#63B8FF"


Minimize.bind("<ButtonPress-1>", MinimizePressedBackground)
Minimize.bind("<ButtonRelease-1>", MinimizeBackground)
Minimize.bind("<Leave>", MinimizeBackground)
Minimize.bind("<Enter>", MinimizeChangeColorOnButtonHover)


# Quit Button
def Quit():
    root.destroy()
    EventHandler.destroy()


Quit = tk.Button(text='×', command=Quit)
canvas.create_window(476, 24, window=Quit, width=50, height=49)
Quit.config(bg="#242424", fg="white", activebackground="black", justify="center", border="0")


# Button is pressed background changer

def QuitPressedBackground(event):
    Quit["background"] = "#242424"


def QuitBackground(event):
    Quit["background"] = "#242424"


def QuitChangeColorOnButtonHover(event):
    Quit.config(cursor="hand2")
    Quit['background'] = "#CF6679"


Quit.bind("<ButtonPress-1>", QuitPressedBackground)
Quit.bind("<ButtonRelease-1>", QuitBackground)
Quit.bind("<Leave>", QuitBackground)
Quit.bind("<Enter>", QuitChangeColorOnButtonHover)


# End of quit

# Close both
def CloseCalculator():
    root.destroy()
    EventHandler.destroy()
    EventHandler.protocol("WM_DELETE_WINDOWS CloseCalculator")


# loop
root.mainloop()

"""
from tkinter import *
from App import Application


def main():
    root = Tk()
    app = Application(master=root)
    app.mainloop()


if __name__ == "__main__":
    main()