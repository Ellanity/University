from AppInterfaceClass import AppInterface


class MainApp:

    def __init__(self):
        self.__interface = AppInterface()

    def run(self):
        self.__interface.run()


if __name__ == '__main__':
    app = MainApp()
    app.run()
