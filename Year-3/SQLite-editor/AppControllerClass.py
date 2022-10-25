import math
from datetime import date, datetime

from SQLiteDataBaseClass import SQLiteDataBase


class AppController:
    def __init__(self, database: SQLiteDataBase):
        self.database = database
        self.tables = []
        self.quantity_of_records_on_page = 10
        self.current_table_name = None
        self.current_page = 0
        self.current_columns = None
        self.current_records = None
        self.additional_info = None

    def start(self):
        self.getTables()
        self.changeCurrentTable(self.tables[0][0])

    def getTables(self, *args):
        query = "SELECT name FROM sqlite_master WHERE type ='table' AND name NOT LIKE 'sqlite_%';"
        self.tables = self.database.executeSQLiteQuery(query=query)

    def changeCurrentTable(self, table_name, *args):
        self.additional_info = None
        if table_name == self.current_table_name:
            return
        self.current_table_name = table_name
        self.current_page = 0
        self.updateCurrentRecords()

    def updateCurrentRecords(self):
        self.current_columns = self.database.executeSQLiteQuery(f"PRAGMA table_info({self.current_table_name})")
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

    def getInfoAboutExhibition(self, *args):
        try:
            self.additional_info = None
            exhibition_id = int(args[0].text)
            query = f"SELECT SELECTED_ARTISTIC_WORKS_INFO.artistic_work_id, SELECTED_ARTISTIC_WORKS_INFO.name, SELECTED_ARTISTIC_WORKS_INFO.artistic_work_type_id, SELECTED_ARTISTIC_WORKS_INFO.date_of_creation," \
                    f" ARTISTS_INFO.artist_id, ARTISTS_INFO.name, ARTISTS_INFO.birth_date" \
                    f" FROM (SELECT ARTISTIC_WORKS_INFO.* FROM (SELECT DISTINCT artistic_work_id FROM \"exhibition_artistic_work\" WHERE \"exhibition_id\" = {exhibition_id}) AS ARTISTIC_WORKS_IDS" \
                    f" JOIN \"artistic_works\" as ARTISTIC_WORKS_INFO ON ARTISTIC_WORKS_IDS.artistic_work_id = ARTISTIC_WORKS_INFO.artistic_work_id) AS SELECTED_ARTISTIC_WORKS_INFO" \
                    f" JOIN \"artists\" AS ARTISTS_INFO ON SELECTED_ARTISTIC_WORKS_INFO.artist_id = ARTISTS_INFO.artist_id;"
            self.current_records = self.database.executeSQLiteQuery(query=query)
            self.current_columns = [(0, "artistic_work_id",),(1, "name",),(2, "artistic_work_type_id",),(3, "date_of_creation",),(4, "artist_id",),(5, "name",),(6, "age",),]
            self.current_page = 0

            # change artists birth to age
            today = date.today()
            for index in range(0, len(self.current_records)):
                self.current_records[index] = list(self.current_records[index])
                birth = datetime.strptime(self.current_records[index][6], '%d.%m.%Y')
                self.current_records[index][6] = str(today.year - birth.year - ((today.month, today.day) < (birth.month, birth.day)))

            # additional data
            record = self.database.executeSQLiteQuery(query=f"SELECT * FROM \"exhibitions\" WHERE \"exhibition_id\" = {exhibition_id}")
            self.additional_info = f"Exhibition Name:\n{record[0][1]}\nStart Date:\n{record[0][2]}"

        except Exception as ex:
            print(ex)
        return

    def getAllExhibitionsInCityNow(self, *args):
        try:
            self.additional_info = None
            query = f"SELECT EXHIBITIONS_INFO.exhibition_id, EXHIBITIONS_INFO.name, EXHIBITIONS_INFO.date, EXHIBITIONS_INFO.duration, address" \
                    f" FROM (SELECT exhibition_id, address FROM \"hall_exhibition\" AS HALL_EXHIBiTION_INFO" \
                    f" JOIN \"halls\" AS HALLS_INFO ON HALL_EXHIBiTION_INFO.hall_id = HALLS_INFO.hall_id WHERE city=\"{args[0].text}\") AS ADDRESSES" \
                    f" JOIN \"exhibitions\" AS EXHIBITIONS_INFO ON ADDRESSES.exhibition_id = EXHIBITIONS_INFO.exhibition_id;"
            self.current_records = self.database.executeSQLiteQuery(query=query)
            self.current_columns = [(0, "exhibition_id",), (1, "name",), (2, "date",),
                                    (3, "duration",), (4, "address",), ]
            self.current_page = 0

            # Leave only those exhibitions that are taking place now
            today = datetime.today()
            records_to_delete = []
            for record in self.current_records:
                start_date = datetime.strptime(record[2], '%d.%m.%Y')
                if not 0 < (today - start_date).days or not (today - start_date).days < int(record[3]):
                    records_to_delete.append(record)
            for record in records_to_delete:
                self.current_records.remove(record)

        except Exception as ex:
            print(ex)
        return
