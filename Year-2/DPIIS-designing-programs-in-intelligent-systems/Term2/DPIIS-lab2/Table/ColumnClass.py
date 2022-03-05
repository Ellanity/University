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

    def data_convert(self, data):
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
