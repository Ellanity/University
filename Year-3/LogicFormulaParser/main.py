from LogicFormulaParserClass import LogicFormulaParser


def main():
    pars = LogicFormulaParser()
    pars.__test_parser__()
    # usage example 1
    """
    input_string = ""
    
    while input_string != "exit":
        input_string = input("enter formula: ")
        if input_string != "exit":
            print(pars.is_formula(input_string))
    """
    # usage ecample 2 
    """
    print(pars.is_formula("((P&(Q|R))->((P&Q)|R))"))
    for formula in pars.formulas.values():
        formula.print()
    """


if __name__ == "__main__":
    main()
