# Generated from VIOLAParser.g4 by ANTLR 4.9.2
from antlr4 import *
if __name__ is not None and "." in __name__:
    from .VIOLAParser import VIOLAParser
else:
    from VIOLAParser import VIOLAParser

# This class defines a complete listener for a parse tree produced by VIOLAParser.
class VIOLAParserListener(ParseTreeListener):

    # Enter a parse tree produced by VIOLAParser#program.
    def enterProgram(self, ctx:VIOLAParser.ProgramContext):
        pass

    # Exit a parse tree produced by VIOLAParser#program.
    def exitProgram(self, ctx:VIOLAParser.ProgramContext):
        pass


    # Enter a parse tree produced by VIOLAParser#statement.
    def enterStatement(self, ctx:VIOLAParser.StatementContext):
        pass

    # Exit a parse tree produced by VIOLAParser#statement.
    def exitStatement(self, ctx:VIOLAParser.StatementContext):
        pass


    # Enter a parse tree produced by VIOLAParser#assignmentStatement.
    def enterAssignmentStatement(self, ctx:VIOLAParser.AssignmentStatementContext):
        pass

    # Exit a parse tree produced by VIOLAParser#assignmentStatement.
    def exitAssignmentStatement(self, ctx:VIOLAParser.AssignmentStatementContext):
        pass


    # Enter a parse tree produced by VIOLAParser#assignmentStatementArray.
    def enterAssignmentStatementArray(self, ctx:VIOLAParser.AssignmentStatementArrayContext):
        pass

    # Exit a parse tree produced by VIOLAParser#assignmentStatementArray.
    def exitAssignmentStatementArray(self, ctx:VIOLAParser.AssignmentStatementArrayContext):
        pass


    # Enter a parse tree produced by VIOLAParser#expression.
    def enterExpression(self, ctx:VIOLAParser.ExpressionContext):
        pass

    # Exit a parse tree produced by VIOLAParser#expression.
    def exitExpression(self, ctx:VIOLAParser.ExpressionContext):
        pass


    # Enter a parse tree produced by VIOLAParser#arithmeticExpressionSimple.
    def enterArithmeticExpressionSimple(self, ctx:VIOLAParser.ArithmeticExpressionSimpleContext):
        pass

    # Exit a parse tree produced by VIOLAParser#arithmeticExpressionSimple.
    def exitArithmeticExpressionSimple(self, ctx:VIOLAParser.ArithmeticExpressionSimpleContext):
        pass


    # Enter a parse tree produced by VIOLAParser#arithmeticExpressionInBinary.
    def enterArithmeticExpressionInBinary(self, ctx:VIOLAParser.ArithmeticExpressionInBinaryContext):
        pass

    # Exit a parse tree produced by VIOLAParser#arithmeticExpressionInBinary.
    def exitArithmeticExpressionInBinary(self, ctx:VIOLAParser.ArithmeticExpressionInBinaryContext):
        pass


    # Enter a parse tree produced by VIOLAParser#unarymath.
    def enterUnarymath(self, ctx:VIOLAParser.UnarymathContext):
        pass

    # Exit a parse tree produced by VIOLAParser#unarymath.
    def exitUnarymath(self, ctx:VIOLAParser.UnarymathContext):
        pass


    # Enter a parse tree produced by VIOLAParser#binarymath.
    def enterBinarymath(self, ctx:VIOLAParser.BinarymathContext):
        pass

    # Exit a parse tree produced by VIOLAParser#binarymath.
    def exitBinarymath(self, ctx:VIOLAParser.BinarymathContext):
        pass


    # Enter a parse tree produced by VIOLAParser#unaryArithmeticExpression.
    def enterUnaryArithmeticExpression(self, ctx:VIOLAParser.UnaryArithmeticExpressionContext):
        pass

    # Exit a parse tree produced by VIOLAParser#unaryArithmeticExpression.
    def exitUnaryArithmeticExpression(self, ctx:VIOLAParser.UnaryArithmeticExpressionContext):
        pass


    # Enter a parse tree produced by VIOLAParser#binaryArithmeticExpression.
    def enterBinaryArithmeticExpression(self, ctx:VIOLAParser.BinaryArithmeticExpressionContext):
        pass

    # Exit a parse tree produced by VIOLAParser#binaryArithmeticExpression.
    def exitBinaryArithmeticExpression(self, ctx:VIOLAParser.BinaryArithmeticExpressionContext):
        pass


    # Enter a parse tree produced by VIOLAParser#primaryExpression.
    def enterPrimaryExpression(self, ctx:VIOLAParser.PrimaryExpressionContext):
        pass

    # Exit a parse tree produced by VIOLAParser#primaryExpression.
    def exitPrimaryExpression(self, ctx:VIOLAParser.PrimaryExpressionContext):
        pass


    # Enter a parse tree produced by VIOLAParser#arrayAccess.
    def enterArrayAccess(self, ctx:VIOLAParser.ArrayAccessContext):
        pass

    # Exit a parse tree produced by VIOLAParser#arrayAccess.
    def exitArrayAccess(self, ctx:VIOLAParser.ArrayAccessContext):
        pass


    # Enter a parse tree produced by VIOLAParser#arrayDefineForm.
    def enterArrayDefineForm(self, ctx:VIOLAParser.ArrayDefineFormContext):
        pass

    # Exit a parse tree produced by VIOLAParser#arrayDefineForm.
    def exitArrayDefineForm(self, ctx:VIOLAParser.ArrayDefineFormContext):
        pass


    # Enter a parse tree produced by VIOLAParser#arraySliceForm.
    def enterArraySliceForm(self, ctx:VIOLAParser.ArraySliceFormContext):
        pass

    # Exit a parse tree produced by VIOLAParser#arraySliceForm.
    def exitArraySliceForm(self, ctx:VIOLAParser.ArraySliceFormContext):
        pass


    # Enter a parse tree produced by VIOLAParser#functionСall.
    def enterFunctionСall(self, ctx:VIOLAParser.FunctionСallContext):
        pass

    # Exit a parse tree produced by VIOLAParser#functionСall.
    def exitFunctionСall(self, ctx:VIOLAParser.FunctionСallContext):
        pass


    # Enter a parse tree produced by VIOLAParser#allTypesWithRefs.
    def enterAllTypesWithRefs(self, ctx:VIOLAParser.AllTypesWithRefsContext):
        pass

    # Exit a parse tree produced by VIOLAParser#allTypesWithRefs.
    def exitAllTypesWithRefs(self, ctx:VIOLAParser.AllTypesWithRefsContext):
        pass


    # Enter a parse tree produced by VIOLAParser#functionDefine.
    def enterFunctionDefine(self, ctx:VIOLAParser.FunctionDefineContext):
        pass

    # Exit a parse tree produced by VIOLAParser#functionDefine.
    def exitFunctionDefine(self, ctx:VIOLAParser.FunctionDefineContext):
        pass


    # Enter a parse tree produced by VIOLAParser#functionBody.
    def enterFunctionBody(self, ctx:VIOLAParser.FunctionBodyContext):
        pass

    # Exit a parse tree produced by VIOLAParser#functionBody.
    def exitFunctionBody(self, ctx:VIOLAParser.FunctionBodyContext):
        pass


    # Enter a parse tree produced by VIOLAParser#canBeReturned.
    def enterCanBeReturned(self, ctx:VIOLAParser.CanBeReturnedContext):
        pass

    # Exit a parse tree produced by VIOLAParser#canBeReturned.
    def exitCanBeReturned(self, ctx:VIOLAParser.CanBeReturnedContext):
        pass


    # Enter a parse tree produced by VIOLAParser#ifStatement.
    def enterIfStatement(self, ctx:VIOLAParser.IfStatementContext):
        pass

    # Exit a parse tree produced by VIOLAParser#ifStatement.
    def exitIfStatement(self, ctx:VIOLAParser.IfStatementContext):
        pass


    # Enter a parse tree produced by VIOLAParser#ifStatementFirstBlock.
    def enterIfStatementFirstBlock(self, ctx:VIOLAParser.IfStatementFirstBlockContext):
        pass

    # Exit a parse tree produced by VIOLAParser#ifStatementFirstBlock.
    def exitIfStatementFirstBlock(self, ctx:VIOLAParser.IfStatementFirstBlockContext):
        pass


    # Enter a parse tree produced by VIOLAParser#ifStatementElif.
    def enterIfStatementElif(self, ctx:VIOLAParser.IfStatementElifContext):
        pass

    # Exit a parse tree produced by VIOLAParser#ifStatementElif.
    def exitIfStatementElif(self, ctx:VIOLAParser.IfStatementElifContext):
        pass


    # Enter a parse tree produced by VIOLAParser#ifStatementElse.
    def enterIfStatementElse(self, ctx:VIOLAParser.IfStatementElseContext):
        pass

    # Exit a parse tree produced by VIOLAParser#ifStatementElse.
    def exitIfStatementElse(self, ctx:VIOLAParser.IfStatementElseContext):
        pass


    # Enter a parse tree produced by VIOLAParser#ifExpression.
    def enterIfExpression(self, ctx:VIOLAParser.IfExpressionContext):
        pass

    # Exit a parse tree produced by VIOLAParser#ifExpression.
    def exitIfExpression(self, ctx:VIOLAParser.IfExpressionContext):
        pass


    # Enter a parse tree produced by VIOLAParser#unaryif.
    def enterUnaryif(self, ctx:VIOLAParser.UnaryifContext):
        pass

    # Exit a parse tree produced by VIOLAParser#unaryif.
    def exitUnaryif(self, ctx:VIOLAParser.UnaryifContext):
        pass


    # Enter a parse tree produced by VIOLAParser#binaryif.
    def enterBinaryif(self, ctx:VIOLAParser.BinaryifContext):
        pass

    # Exit a parse tree produced by VIOLAParser#binaryif.
    def exitBinaryif(self, ctx:VIOLAParser.BinaryifContext):
        pass


    # Enter a parse tree produced by VIOLAParser#unaryIfExpression.
    def enterUnaryIfExpression(self, ctx:VIOLAParser.UnaryIfExpressionContext):
        pass

    # Exit a parse tree produced by VIOLAParser#unaryIfExpression.
    def exitUnaryIfExpression(self, ctx:VIOLAParser.UnaryIfExpressionContext):
        pass


    # Enter a parse tree produced by VIOLAParser#binaryIfExpression.
    def enterBinaryIfExpression(self, ctx:VIOLAParser.BinaryIfExpressionContext):
        pass

    # Exit a parse tree produced by VIOLAParser#binaryIfExpression.
    def exitBinaryIfExpression(self, ctx:VIOLAParser.BinaryIfExpressionContext):
        pass


    # Enter a parse tree produced by VIOLAParser#ifExpressionInBinary.
    def enterIfExpressionInBinary(self, ctx:VIOLAParser.IfExpressionInBinaryContext):
        pass

    # Exit a parse tree produced by VIOLAParser#ifExpressionInBinary.
    def exitIfExpressionInBinary(self, ctx:VIOLAParser.IfExpressionInBinaryContext):
        pass


    # Enter a parse tree produced by VIOLAParser#forStatement.
    def enterForStatement(self, ctx:VIOLAParser.ForStatementContext):
        pass

    # Exit a parse tree produced by VIOLAParser#forStatement.
    def exitForStatement(self, ctx:VIOLAParser.ForStatementContext):
        pass


    # Enter a parse tree produced by VIOLAParser#whileStatement.
    def enterWhileStatement(self, ctx:VIOLAParser.WhileStatementContext):
        pass

    # Exit a parse tree produced by VIOLAParser#whileStatement.
    def exitWhileStatement(self, ctx:VIOLAParser.WhileStatementContext):
        pass



del VIOLAParser