from antlr4 import *
# from antlr4 import ParseTreeWalker
from antlr4.error.ErrorListener import ErrorListener

from VIOLALexer import VIOLALexer
from VIOLAParser import VIOLAParser
from VIOLAParserListener import VIOLAParserListener
# from VIOLAParserVisitor import VIOLAParserVisitor
from MyVisitor import MyVisitor


class MyErrorListener(ErrorListener, VIOLAParserListener):
    def syntaxError(self, recognizer, offendingSymbol, line, column, msg, e):
        print(f"Syntax error at line {line} column {column}: {msg} - {e}")


def main():
    input_stream = FileStream("examples/ex0.txt")

    lexer = VIOLALexer(input_stream)
    stream = CommonTokenStream(lexer)
    parser = VIOLAParser(stream)

    parser.removeErrorListeners()
    listener = MyErrorListener()
    parser.addErrorListener(listener)

    tree = parser.program()
    # print(tree.toStringTree(recog=parser))

    visitor = MyVisitor()
    cil_code = visitor.visit(tree)
    # print('main',visitor.main_dict)
    print(visitor.main_dict)


if __name__ == '__main__':
    main()
