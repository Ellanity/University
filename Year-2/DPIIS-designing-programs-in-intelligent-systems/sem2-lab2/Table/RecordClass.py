class Record:

    elements = list()
    columns = list()

    def __init__(self, columns, elements):
        right_record = True
        if len(columns) == len(elements):
            for i in range(0, len(columns)):
                if columns[i].data_check(elements[i]) is False:
                    elements[i] = columns[i].data_convert(elements[i])
                    # right_record = False
                    # break

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

    def element_change(self, title, new_element):
        column = self.column_get(title)
        if column is not None:
            index = self.columns.index(column)
            self.elements[index] = new_element
            return True
        return False

    def create_xml_element(self, xml_file):
        xml_record = xml_file.createElement("record")
        for element in self.elements:
            index = self.elements.index(element)
            xml_element = xml_file.createElement("element")
            xml_element.setAttribute(str(self.columns[index].title), str(element))
            xml_record.appendChild(xml_element)
        return xml_record
