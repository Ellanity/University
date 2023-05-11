"""
# Contains with methods, that understand interface
"""

import math
from AppModelClass import AppModel


class AppController:
    def __init__(self):
        self.tables = []
        self.tables_can_add_record = []
        self.tables_can_change_record = []
        self.current_table_name = None

        self.current_page = 0
        self.quantity_of_records_on_page = 9
        self.current_columns = None
        self.current_records = None

        self.additional_info = ""

        self.__model = AppModel()
        self.start()

    def start(self):
        self.getTables()
        self.changeCurrentTable(self.tables[0])

    def getTables(self, *args):
        _ = args
        # customize here only if you sure what you do (need change all other classes too)
        self.tables = ["triples", "individuals", "classes", "data properties",
                       "object properties", "annotation properties", "properties"]
        self.tables_can_add_record = ["individuals", "classes", "object properties"]
        self.tables_can_change_record = ["individuals", "classes", "object properties"]

    def changeCurrentTable(self, table_name, change_anyway=False, *args):
        _ = args
        if table_name == self.current_table_name and not change_anyway:
            return
        table_changed_status = self.updateCurrentRecords(table_name)
        if table_changed_status:
            self.current_table_name = table_name
            self.current_page = 0

    def updateCurrentRecords(self, table_name, *args):
        _ = args
        table_changed_status = False
        # need define self.current_columns and self.current_records by table_name
        if table_name == "individuals":
            self.current_columns = ["individual", "class"]
            self.current_records = self.__model.getIndividualsAll()
            table_changed_status = True
        elif table_name == "classes":
            self.current_columns = ["class"]
            self.current_records = self.__model.getClasses()
            table_changed_status = True
        elif table_name == "data properties":
            self.current_columns = ["data property"]
            self.current_records = self.__model.getDataPropertiesAll()
            table_changed_status = True
        elif table_name == "object properties":
            self.current_columns = ["object property"]
            self.current_records = self.__model.getObjectPropertiesAll()
            table_changed_status = True
        elif table_name == "annotation properties":
            self.current_columns = ["annotation property"]
            self.current_records = self.__model.getAnnotationPropertiesAll()
            table_changed_status = True
        elif table_name == "datatypes":
            self.current_columns = ["datatype"]
            self.current_records = self.__model.getDatatypesAll()
            table_changed_status = True
        elif table_name == "triples":
            self.current_columns = ["first", "relation", "second"]
            self.current_records = self.__model.getAllTriples()
            table_changed_status = True
        elif table_name == "properties":
            self.current_columns = ["property"]
            self.current_records = self.__model.getDatatypesAll()
            table_changed_status = True
        elif table_name not in self.tables:
            try:
                print(f"try to find: {table_name}")
                self.current_columns = ["individual", "class"]
                self.current_records = self.__model.getIndividualsByClass(class_iri=table_name)
                table_changed_status = True
            except Exception as ex:
                print(f"No such class in ontology. error: {ex}")
        return table_changed_status

    def nextPage(self, *args):
        _ = args
        if not self.current_table_name:
            return
        if self.current_page + 1 < math.ceil(len(self.current_records) / self.quantity_of_records_on_page):
            self.current_page += 1

    def previousPage(self, *args):
        _ = args
        if not self.current_table_name:
            return
        if self.current_page > 0:
            self.current_page -= 1

    def currentTableChange(self, table_name):
        table_changed_status = self.updateCurrentRecords(table_name)
        if table_changed_status:
            self.current_table_name = table_name

    def addNewRecord(self, *args):
        table_name = args[1]
        change_anyway = args[2]
        if table_name == self.current_table_name and not change_anyway:
            return

        # get input
        values = []
        for index in range(0, len(self.current_columns)):
            value = f"{args[0][index].text}"
            values.append(str(value))

        # all queries
        try:
            if self.current_table_name == "individuals":
                self.__model.addIndividualByClass(individual_iri=values[0], class_iri=values[1])
            elif self.current_table_name == "classes":
                self.__model.addClass(class_iri=values[0])
            elif self.current_table_name == "triples":
                self.__model.addTriple(iri_first=values[0], iri_relation=values[1], iri_second=values[2])
        except Exception as ex:
            print(ex)

        # end adding
        self.currentTableChange(table_name)

    def deleteRecord(self, *args):
        table_name = args[1]
        change_anyway = args[2]
        if table_name == self.current_table_name and not change_anyway:
            return
        # get input
        values = []
        for index in range(0, len(self.current_columns)):
            value = f"{args[0][index].text}"
            values.append(str(value))

        # all queries
        try:
            if self.current_table_name == "individuals":
                self.__model.deleteIndividualIri(individual_iri=values[0])
            elif self.current_table_name == "classes":
                self.__model.deleteClass(class_iri=values[0])
            elif table_name == "triples":
                self.__model.deleteTriple(iri_first=values[0], iri_relation=values[1], iri_second=values[2])

        except Exception as ex:
            print(ex)

        # end deleting
        self.currentTableChange(table_name)

    def changeRecord(self, *args):
        table_name = args[2]
        change_anyway = args[3]

        if table_name == self.current_table_name and not change_anyway:
            return

        # get input
        previous_data = args[1]
        if len(args[0]) != len(previous_data) or len(previous_data) == 0:
            return

        # change to
        values = []
        previous_values = []
        for index in range(0, len(self.current_columns)):
            value = f"{args[0][index].text}"
            values.append(str(value))
            previous_value = args[1][index]
            previous_values.append(str(previous_value))

        # all queries
        try:
            if self.current_table_name == "individuals":
                new_iri = values[0]
                old_iri = previous_values[0]
                self.__model.updateIndividualIri(new_iri=new_iri, old_iri=old_iri)
            elif self.current_table_name == "classes":
                new_iri = values[0]
                old_iri = previous_values[0]
                self.__model.updateClass(new_iri=new_iri, old_iri=old_iri)
        except Exception as ex:
            print(ex)

        # end changing
        self.currentTableChange(table_name)

    # SPECIAL
    def specialQueryFirst(self, *args):
        try:
            self.additional_info = f"All vertexes, that starts from \"{args[0].text}\""
            self.current_records = self.__model.specialQueryFirst(args)
            self.current_table_name = "All vertexes"
            self.current_columns = ["vertex"]
            self.current_page = 0
        except Exception as ex:
            print(ex)

    def specialQuerySecond(self, *args):
        try:
            self.additional_info = f"Object is \"{args[0].text}\""
            self.current_records = self.__model.specialQuerySecond(args)
            self.current_table_name = "Triples with object"
            self.current_columns = ["subject", "relation", "object"]
            self.current_page = 0
        except Exception as ex:
            print(ex)

    def specialQueryThird(self, *args):
        try:
            self.additional_info = f"Subject is \"{args[0].text.split(',')[0]}\" " \
                                   f"and Object is \"{args[0].text.split(',')[1]}\""
            self.current_records = self.__model.specialQueryThird(args)
            self.current_table_name = "Triples with object and subject"
            self.current_columns = ["subject", "relation", "object"]
            self.current_page = 0
        except Exception as ex:
            print(ex)
