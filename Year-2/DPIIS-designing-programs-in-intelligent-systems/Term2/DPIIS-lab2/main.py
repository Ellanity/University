import random
import time
from xml.dom import minidom
import xml.sax


class Column:

    title = str()
    type_of_data = str()
    available_types = ["str", "int"]
    default_data = {"str": "", "int": 0}

    def __init__(self, type_of_data, title):
        if type_of_data in self.available_types:
            self.type_of_data = type_of_data
        else:
            self.type_of_data = "str"
        self.title = str(title)

    def data_check(self, data):
        if self.type_of_data == "int":
            if type(data) is int:
                return True
        if self.type_of_data == "str":
            if type(data) is str:
                return True
        return False

    def data_converter(self, data):
        converted_data = data
        if self.type_of_data == "int":
            converted_data = int(data)
        if self.type_of_data == "str":
            converted_data = str(data)
        return converted_data

    def create_xml_element(self, xml_file):
        column = xml_file.createElement("column")
        column.setAttribute("title", str(self.title))
        column.setAttribute("type_of_data", str(self.type_of_data))
        return column


class Record:

    elements = list()
    columns = list()

    def __init__(self, columns, elements):
        right_record = True
        if len(columns) == len(elements):
            for i in range(0, len(columns)):
                if columns[i].data_check(elements[i]) is False:
                    right_record = False
                    break

        if right_record:
            self.elements = list(elements)
            self.columns = list(columns)

    def column_add(self, column):
        self.columns.append(column)
        self.elements.append(column.default_data.get(column.type_of_data))

    def column_get(self, title):
        for column in self.columns:
            if column.title == title:
                return column
        return None

    def column_remove(self, title):
        column = self.column_get(title)
        if column is not None:
            index = self.columns.index(column)
            del self.elements[index]
            self.columns.remove(column)
            return True
        return False

    def element_get(self, title):
        column = self.column_get(title)
        if column is not None:
            index = self.columns.index(column)
            return self.elements[index]
        return None

    def create_xml_element(self, xml_file):
        xml_record = xml_file.createElement("record")
        for element in self.elements:
            index = self.elements.index(element)
            xml_element = xml_file.createElement("element")
            xml_element.setAttribute(str(self.columns[index].title), str(element))
            xml_record.appendChild(xml_element)
        return xml_record


class Table:

    columns = list()
    records = list()
    title = str(f"table-{time.time()}")

    def __init__(self, title=None):
        if title is not None:
            self.title = title
        pass

    def column_add(self, type_of_data, title):
        new_column = Column(type_of_data, title)
        self.columns.append(new_column)
        for record in self.records:
            record.column_add(new_column)

    def column_get(self, title):
        for column in self.columns:
            if column.title == title:
                return column
        return None

    def column_remove(self, title):

        column = self.column_get(title)

        if column is not None:

            all_records_have_column = True
            for record in self.records:
                if record.column_get(title) is None:
                    all_records_have_column = False
                    break

            all_records_doesnt_have_column = True
            if all_records_have_column:
                for record in self.records:
                    removed = record.column_remove(title)
                    if not removed:
                        all_records_doesnt_have_column = False

            if all_records_doesnt_have_column:
                self.columns.remove(column)

    def record_add(self, elements):
        if len(elements) > 0:
            record = Record(self.columns, elements)
            if len(record.elements) == len(elements):
                self.records.append(record)

    def record_remove(self, record):
        self.records.remove(record)

    def record_find(self, title, data):
        relevant_records = list()
        for record in self.records:
            if record.element_get(title) is not None and \
                    record.element_get(title) == data:
                relevant_records.append(record)
        return relevant_records

    def save_to_xml(self):

        xml_file = minidom.Document()
        # add main table
        xml_table = xml_file.createElement('table')
        xml_table.setAttribute('title', self.title)
        xml_file.appendChild(xml_table)

        # add columns in table
        xml_columns = xml_file.createElement('columns')
        for column in self.columns:
            xml_column = column.create_xml_element(xml_file)
            xml_columns.appendChild(xml_column)
        xml_table.appendChild(xml_columns)

        # add records in table
        xml_records = xml_file.createElement('records')
        for record in self.records:
            xml_record = record.create_xml_element(xml_file)
            xml_records.appendChild(xml_record)
        xml_table.appendChild(xml_records)

        xml_str = xml_file.toprettyxml(indent="\t")
        save_path_file = f"{self.title}.xml"
        with open(save_path_file, "w") as f:
            f.write(xml_str)

    def load_from_xml(self, file):

        self.columns.clear()
        self.records.clear()

        class TableHandler(xml.sax.ContentHandler):

            def __init__(self, table):
                self.table = table
                self.CurrentData = ''
                self.record = list()
                self.element = tuple()

            # Call when an element starts
            def startElement(self, tag, attributes):
                # print("new tag:", tag)
                self.CurrentData = tag
                # if self.CurrentData == 'record':
                    # print("lol")
                if tag == 'column':
                    title = attributes['title']
                    type_of_data = attributes['type_of_data']
                    self.table.column_add(title, type_of_data)
                if tag == 'element':
                    self.element = attributes[str(attributes.getNames()[0])]
                    # print(self.element)
                    self.record.append(self.element)
                    # print(self.record)

            # Call when an elements ends
            def endElement(self, tag):
                if tag == 'record':
                    # print("record:", self.record)
                    self.table.record_add(self.record)
                    self.record.clear()
                self.CurrentData = ''

            # Call when a character is read
            """def characters(self, content):
                # print(content)
                if self.CurrentData == 'artist':
                    self.artist += content
                elif self.CurrentData == 'year':
                    self.year += content
                elif self.CurrentData == 'album':
                    self.album += content"""

        parser = xml.sax.make_parser()  # creating an XMLReader
        parser.setFeature(xml.sax.handler.feature_namespaces, 0)  # turning off namespaces
        handler = TableHandler(self)
        parser.setContentHandler(handler)  # overriding default ContextHandler
        parser.parse(file)

    def print(self):
        for record in self.records:
            print(record.elements)
        print("---------------------------------------")


def main():
    # create table
    table = Table("main")
    # fill table
    table.column_add("int", "id")
    table.column_add("str", "name")
    table.column_add("int", "age")
    table.column_add("int", "gender")
    table.column_add("str", "address")
    table.record_add((0, "admin", 10, 2, "pushkina dom kolotushkina"))
    table.record_add((1, "moderator1", 40, 1, "baker street 221b"))
    table.record_add((2, "moderator2", 35, 2, "baker street 221a"))
    table.record_add((3, "moderator3", 30, 1, "baker street 222b"))
    table.record_add((4, "moderator4", 25, 1, "baker street 222a"))
    # print table
    table.print()
    # save current info
    table.save_to_xml()
    # remove elements
    table.column_add("str", "lol")
    table.column_add("int", "zero")
    table.column_remove("age")
    table.column_remove("id")
    table.record_remove(table.records[0])
    table.record_remove(table.records[2])
    # print table
    table.print()
    # load info
    table.load_from_xml("main2.xml")
    # print table
    print("loaded:")
    table.print()
    # remove elements
    table.column_add("str", "lol")
    table.column_add("int", "zero")
    table.column_remove("age")
    table.column_remove("id")
    table.record_remove(table.records[0])
    table.record_remove(table.records[2])
    # print table
    table.print()


    # table.record_remove(random.choice(table.records))
    # for record in table.record_find("gender", 1):
    #     print(record.elements)

    # table.save_to_xml()

    pass


if __name__ == '__main__':
    main()