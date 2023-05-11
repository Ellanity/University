########################################################################
# Лабораторная работа #1 по дисциплине ЛОИС                            #
# Выполнена студентом группы 021703 БГУИР Поплавский Эльдар Эдуардович #
# Файл содержит реализацию терминального интерфейса для работы         #
# с парсером                                                           #
#                                                                      #
# 2023.02.17 v0.0.1                                                    #
########################################################################


from LogicFormulaParserClass import LogicFormulaParser
from LogicFormulaResolverClass import LogicFormulaResolver


def main():
    pars = LogicFormulaParser()
    pars.__test_parser__()
    resolver = LogicFormulaResolver()
    resolver.__test_resolver__()

    input_string = ""
    
    while input_string != "exit":
        input_string = input("enter formula: ")
        if input_string != "exit":
            if pars.is_formula(input_string):
                print(resolver.formula_is_generally_valid(pars.formulas[input_string]))
    """
    # ### Debug tests
    print(pars.is_formula(r"1"))
    # print(pars.is_formula(r"((P/\(Q\/R))->((P/\Q)\/R))"))
    # print(pars.is_formula(r"((P/\(!S))->(Q\/R))"))
    for formula in pars.formulas.values():
        # formula.print()
        table = resolver.resolve_formula_truth_table(formula)
        # print(table)
        print(resolver.formula_is_generally_valid(formula))
    """


if __name__ == "__main__":
    main()
