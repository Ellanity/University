from Interface import ManagingElements


class DisplayingDiary:
    def __init__(self):
        self.__managing_elements = ManagingElements()

    def work(self):
        self.__managing_elements.window.mainloop()


if __name__ == '__main__':
    DisplayingDiary().work()
