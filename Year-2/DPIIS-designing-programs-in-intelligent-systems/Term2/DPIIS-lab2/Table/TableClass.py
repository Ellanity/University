import time
from xml.dom import minidom
import xml.sax

from Table.RecordClass import Record
from Table.ColumnClass import Column


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
        index = 0
        if title in self.columns:
            index = self.columns.index(title)

        for record in self.records:
            if record.element_get(title) is not None and \
                    record.element_get(title) == self.columns[index].data_convert(data):
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
                    self.table.column_add(type_of_data, title)
                if tag == 'element':
                    self.element = attributes[str(attributes.getNames()[0])]
                    self.record.append(self.element)
                    # convert element type
                    self.record[-1] = self.table.columns[len(self.record) - 1].data_convert(self.record[-1])

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
        self.title = file.split(".")[0]

    def record_change(self, record, title, new_element):
        record.element_change(title, new_element)

    def print(self):
        for record in self.records:
            print(record.elements)
        print("---------------------------------------")
