import math

from SQLiteDataBaseClass import SQLiteDataBase


class AppModel:
    def __init__(self, database: SQLiteDataBase):
        self.database = database
        self.tables = []
        self.quantity_of_records_on_page = 9
        self.current_table_name = None
        self.current_page = 0
        self.current_columns = None
        self.current_records = None

    def start(self):
        self.getTables()
        self.changeCurrentTable(self.tables[0][0])

    def getTables(self, *args):
        query = "SELECT name FROM sqlite_master WHERE type ='table' AND name NOT LIKE 'sqlite_%';"
        self.tables = self.database.executeSQLiteQuery(query=query)

    def changeCurrentTable(self, table_name, *args):
        if table_name == self.current_table_name:
            return
        self.current_table_name = table_name
        self.current_page = 0
        self.current_columns = self.database.executeSQLiteQuery(f"PRAGMA table_info({self.current_table_name})")
        self.current_records = self.database.executeSQLiteQuery(f"SELECT * FROM {self.current_table_name}")

    def updateCurrentRecords(self):
        self.current_records = self.database.executeSQLiteQuery(f"SELECT * FROM {self.current_table_name}")

    def saveChangesInTable(self, *args):
        self.database.saveChanges()

    def nextPage(self, *args):
        if not self.current_table_name:
            return
        if self.current_page + 1 < math.ceil(len(self.current_records) / self.quantity_of_records_on_page):
            self.current_page += 1

    def previousPage(self, *args):
        if not self.current_table_name:
            return
        if self.current_page > 0:
            self.current_page -= 1

    def addNewRecord(self, *args):
        if not self.current_table_name:
            return
        columns_str = ""
        values_str = ""
        for index in range(0, len(self.current_columns)):
            value = f"{args[0][index].text}"
            try:
                if self.current_columns[index][2] == "INTEGER":
                        value = int(value)
                if self.current_columns[index][2] == "REAL":
                        value = float(value)
            except Exception as ex:
                print(ex)
                return
            value = f"'{value}'"
            values_str += f"{str(value)}, "
            columns_str += f"{self.current_columns[index][1]}, "
        values_str = values_str[0:-2]
        columns_str = columns_str[0:-2]
        query = f"INSERT INTO {self.current_table_name} ({columns_str}) VALUES({values_str});"
        self.database.executeSQLiteQuery(query=query)
        self.saveChangesInTable()
        self.updateCurrentRecords()

    def deleteRecord(self, *args):
        if not self.current_table_name:
            return
        conditions_str = ""
        for index in range(0, len(self.current_columns)):
            conditions_str += f"{self.current_columns[index][1]}='{args[0][index].text}' AND "
        query = f"DELETE FROM {self.current_table_name} WHERE {conditions_str[0: -5]};"
        self.database.executeSQLiteQuery(query=query)
        self.saveChangesInTable()
        self.updateCurrentRecords()

    def changeRecord(self, *args):
        if not self.current_table_name:
            return
        previous_data = args[1]
        if len(previous_data) == 0:
            return
        # conditions
        conditions_str = ""
        for index in range(0, len(previous_data)):
            conditions_str += f"{self.current_columns[index][1]}='{previous_data[index]}' AND "
        # change to
        change_str = ""
        for index in range(0, len(self.current_columns)):
            value = f"{args[0][index].text}"
            try:
                if self.current_columns[index][2] == "INTEGER":
                    value = int(value)
                if self.current_columns[index][2] == "REAL":
                    value = float(value)
            except Exception as ex:
                print(ex)
                return
            value = f"'{value}'"
            change_str += f"{self.current_columns[index][1]} = {value}, "
        query = f"UPDATE {self.current_table_name} SET {change_str[0: -2]} WHERE {conditions_str[0: -5]}"
        self.database.executeSQLiteQuery(query=query)
        self.saveChangesInTable()
        self.updateCurrentRecords()
