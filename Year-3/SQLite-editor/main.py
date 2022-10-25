from SQLiteDataBaseClass import SQLiteDataBase
from InterfaceClass import Interface
from AppModelClass import AppModel


class MainApp:

    def __init__(self):
        self.database = SQLiteDataBase()
        self.model = AppModel(self.database)
        self.interface = Interface(self.model)

    def run(self):
        self.model.start()
        self.interface.run()


if __name__ == '__main__':
    app = MainApp()
    app.run()
