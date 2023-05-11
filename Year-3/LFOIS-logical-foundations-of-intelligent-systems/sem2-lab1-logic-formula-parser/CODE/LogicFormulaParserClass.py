########################################################################
# Лабораторная работа #1 по дисциплине ЛОИС                            #
# Выполнена студентом группы 021703 БГУИР Поплавский Эльдар Эдуардович #
# Файл содержит парсер формул сокращенного языка логики                #
# 2023.02.17 v0.0.1                                                    #
########################################################################


class LogicFormulaParser:
    def __init__(self, test_parser=False):
        self.__init_syntax__()
        self.formulas = {}
        if test_parser:
            self.__test_parser__()

    def __init_syntax__(self):
        # Define the valid symbols for the abbreviated language of utterance logic
        self.constants = ('0', '1')
        self.latin_letters = set('ABCDEFGHIJKLMNOPQRSTUVWXYZ')
        self.zero_decimal = ('0', )
        self.negation = '!'
        self.conjunction = '/\\'
        self.disjunction = '\/'
        self.implication = '->'
        self.equivalence = '~'
        self.open_bracket_round = '('
        self.close_bracket_round = ')'
        # binary_connections must be not longer than 2 chars
        self.binary_connections = (self.conjunction, self.disjunction, self.implication, self.equivalence)

    class Formula:
        def __init__(self, name: str):
            self.name = name
            self.vertexes = []
            self.edges = []

        class Vertex:
            def __init__(self, index: int, content: str, vertex_type: str):
                self.index = index
                self.content = content
                self.vertex_type = vertex_type

        class Edge:
            def __init__(self, parent_index: int, child_index: int):
                self.parent_vertex_index = parent_index
                self.child_vertex_index = child_index

        def print(self):
            print(f"Formula: \"{self.name}\"",
                  "\nvertexes:", *[(vertex.index, vertex.vertex_type, vertex.content) for vertex in self.vertexes],
                  "\nedges:", *[(edge.parent_vertex_index, edge.child_vertex_index) for edge in self.edges])

    def is_formula(self, input_string, formula_name="", parent_index=-1):
        if formula_name == "":
            self.formulas[input_string] = (self.Formula(input_string))
            self.formulas[input_string].vertexes.append(self.Formula.Vertex(index=0, content="", vertex_type="root"))
            formula_name = input_string
            parent_index = 0
            if input_string == "":
                return False

        def delete_formula():
            if parent_index == 0:
                self.formulas.pop(input_string)

        def new_vertex(vertex_type):
            new_vertex_index_local = len(self.formulas[formula_name].vertexes)
            self.formulas[formula_name].vertexes.append(self.Formula.Vertex(index=new_vertex_index_local,
                                                                            content=input_string,
                                                                            vertex_type=vertex_type))
            self.formulas[formula_name].edges.append(self.Formula.Edge(parent_index=parent_index,
                                                                       child_index=new_vertex_index_local))
            return new_vertex_index_local

        # constant
        if input_string in self.constants:
            new_vertex(vertex_type="constant")
            return True

        # atomic_formula
        elif len(input_string) > 0 and input_string[0] in self.latin_letters:
            if len(input_string) > 1:
                delete_formula()
                return False
            new_vertex(vertex_type="atomic_formula")
            return True
        elif len(input_string) > 0 and \
                input_string[0] == self.open_bracket_round and input_string[-1] == self.close_bracket_round:
            # unary_complex_formula
            if input_string[1] == self.negation:  # or not have_binary_bounds:
                new_vertex_index = new_vertex(vertex_type="unary_complex_formula")
                if self.is_formula(input_string[2:-1], formula_name=formula_name, parent_index=new_vertex_index):
                    return True
                else:
                    delete_formula()
                    return False
            # binary_complex_formula
            else:
                brackets_round_counter = 0
                char_index = 1
                for char_ in input_string[1:-1]:
                    if char_ == self.open_bracket_round:
                        brackets_round_counter += 1
                    if char_ == self.close_bracket_round:
                        brackets_round_counter -= 1
                    # center found
                    if ((char_ in self.binary_connections) or
                        (char_ + input_string[char_index + 1]) in self.binary_connections) \
                            and brackets_round_counter == 0:
                        new_vertex_index = new_vertex(vertex_type="binary_complex_formula")
                        # parts_formulas_indexes = []
                        if char_ in self.binary_connections:
                            parts_formulas_indexes = [[1, char_index], [char_index + 1, -1]]
                        elif (char_ + input_string[char_index + 1]) in self.binary_connections:
                            parts_formulas_indexes = [[1, char_index], [char_index + 2, -1]]
                        else:
                            # print("Error: center not found")
                            delete_formula()
                            return False
                        if self.is_formula(input_string[parts_formulas_indexes[0][0]:parts_formulas_indexes[0][1]],
                                           formula_name=formula_name, parent_index=new_vertex_index) \
                            and self.is_formula(input_string[parts_formulas_indexes[1][0]:parts_formulas_indexes[1][1]],
                                                formula_name=formula_name, parent_index=new_vertex_index):
                            return True
                        else:
                            delete_formula()
                            return False
                    char_index += 1
                # formula not precessed
                delete_formula()
                return False
        else:
            delete_formula()
            return False

    class TestParserException(Exception):
        pass

    def __test_parser__(self):
        with open("tests.csv", "r") as tests_file:
            tests = tests_file.readlines()
            for test in tests:
                if test == "\n":
                    continue
                formula, answer_string = test[0:-1].split(",")
                test_answer: bool = True if answer_string == "True" else False
                try:
                    parser_answer = self.is_formula(formula)
                except Exception as ex:
                    print(f"TestParserError: test failed: {tests.index(test)} error: {ex}")
                if parser_answer != test_answer:
                    print(formula)
                    raise self.TestParserException(f"TestParserError: {tests.index(test)} "
                                                   f"test failed, parser answer: {parser_answer}, "
                                                   f"test answer: {test_answer}")
            self.formulas.clear()
