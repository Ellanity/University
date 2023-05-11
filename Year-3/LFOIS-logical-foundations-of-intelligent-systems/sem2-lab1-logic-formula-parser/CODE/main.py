########################################################################
# Лабораторная работа #1 по дисциплине ЛОИС                            #
# Выполнена студентом группы 021703 БГУИР Поплавский Эльдар Эдуардович #
# Файл содержит парсер формул сокращенного языка логики                #
# 2023.02.17 v0.0.1                                                    #
########################################################################


from LogicFormulaParserClass import LogicFormulaParser


def main():
    pars = LogicFormulaParser()
    pars.__test_parser__()

    input_string = ""
    
    while input_string != "exit":
        input_string = input("enter formula: ")
        if input_string != "exit":
            print(pars.is_formula(input_string))
    """
    print(pars.is_formula(r"((P/\(Q\/R))->((P/\Q)\/R))"))
    for formula in pars.formulas.values():
        formula.print()
    """


if __name__ == "__main__":
    main()
