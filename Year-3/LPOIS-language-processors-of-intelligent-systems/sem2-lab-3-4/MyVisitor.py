from antlr4 import *
import re
from VIOLAParserVisitor import VIOLAParserVisitor
from VIOLAParser import VIOLAParser


class MyError(Exception):
    def __init__(self, msg):
        self.msg = msg

    def print_msg(self):
        print(self.msg)


class MyVisitor(VIOLAParserVisitor):

    main_dict = {}
    sub_dict = {}

    # Visit a parse tree produced by VIOLAParser#program.
    def visitProgram(self, ctx:VIOLAParser.ProgramContext):
        return self.visitChildren(ctx)

    # Visit a parse tree produced by VIOLAParser#statement.
    def visitStatement(self, ctx:VIOLAParser.StatementContext):
        return self.visitChildren(ctx)

    # Visit a parse tree produced by VIOLAParser#assignmentStatement.
    def visitAssignmentStatement(self, ctx: VIOLAParser.AssignmentStatementContext):
        return self.visitChildren(ctx)

    # Visit a parse tree produced by VIOLAParser#assignmentStatementArray.
    def visitAssignmentStatementArray(self, ctx: VIOLAParser.AssignmentStatementArrayContext):
        return self.visitChildren(ctx)

    # Visit a parse tree produced by VIOLAParser#expression.
    def visitExpression(self, ctx: VIOLAParser.ExpressionContext):
        return self.visitChildren(ctx)

    # Visit a parse tree produced by VIOLAParser#arithmeticExpressionSimple.
    def visitArithmeticExpressionSimple(self, ctx: VIOLAParser.ArithmeticExpressionSimpleContext):
        return self.visitChildren(ctx)

    # Visit a parse tree produced by VIOLAParser#arithmeticExpressionInBinary.
    def visitArithmeticExpressionInBinary(self, ctx: VIOLAParser.ArithmeticExpressionInBinaryContext):
        return self.visitChildren(ctx)

    # Visit a parse tree produced by VIOLAParser#unarymath.
    def visitUnarymath(self, ctx: VIOLAParser.UnarymathContext):
        return self.visitChildren(ctx)

    # Visit a parse tree produced by VIOLAParser#binarymath.
    def visitBinarymath(self, ctx: VIOLAParser.BinarymathContext):
        return self.visitChildren(ctx)

    # Visit a parse tree produced by VIOLAParser#unaryArithmeticExpression.
    def visitUnaryArithmeticExpression(self, ctx: VIOLAParser.UnaryArithmeticExpressionContext):
        return self.visitChildren(ctx)

    # Visit a parse tree produced by VIOLAParser#binaryArithmeticExpression.
    def visitBinaryArithmeticExpression(self, ctx: VIOLAParser.BinaryArithmeticExpressionContext):
        return self.visitChildren(ctx)

    # Visit a parse tree produced by VIOLAParser#primaryExpression.
    def visitPrimaryExpression(self, ctx: VIOLAParser.PrimaryExpressionContext):
        return self.visitChildren(ctx)

    # Visit a parse tree produced by VIOLAParser#arrayAccess.
    def visitArrayAccess(self, ctx: VIOLAParser.ArrayAccessContext):
        return self.visitChildren(ctx)

    # Visit a parse tree produced by VIOLAParser#arrayDefineForm.
    def visitArrayDefineForm(self, ctx: VIOLAParser.ArrayDefineFormContext):
        return self.visitChildren(ctx)

    # Visit a parse tree produced by VIOLAParser#arraySliceForm.
    def visitArraySliceForm(self, ctx: VIOLAParser.ArraySliceFormContext):
        return self.visitChildren(ctx)

    # Visit a parse tree produced by VIOLAParser#functionСall.
    def visitFunctionСall(self, ctx: VIOLAParser.FunctionСallContext):
        return self.visitChildren(ctx)

    # Visit a parse tree produced by VIOLAParser#allTypesWithRefs.
    def visitAllTypesWithRefs(self, ctx: VIOLAParser.AllTypesWithRefsContext):
        return self.visitChildren(ctx)

    # Visit a parse tree produced by VIOLAParser#functionDefine.
    def visitFunctionDefine(self, ctx: VIOLAParser.FunctionDefineContext):
        return self.visitChildren(ctx)

    # Visit a parse tree produced by VIOLAParser#functionBody.
    def visitFunctionBody(self, ctx: VIOLAParser.FunctionBodyContext):
        return self.visitChildren(ctx)

    # Visit a parse tree produced by VIOLAParser#canBeReturned.
    def visitCanBeReturned(self, ctx: VIOLAParser.CanBeReturnedContext):
        return self.visitChildren(ctx)

    # Visit a parse tree produced by VIOLAParser#ifStatement.
    def visitIfStatement(self, ctx: VIOLAParser.IfStatementContext):
        return self.visitChildren(ctx)

    # Visit a parse tree produced by VIOLAParser#ifStatementFirstBlock.
    def visitIfStatementFirstBlock(self, ctx: VIOLAParser.IfStatementFirstBlockContext):
        return self.visitChildren(ctx)

    # Visit a parse tree produced by VIOLAParser#ifStatementElif.
    def visitIfStatementElif(self, ctx: VIOLAParser.IfStatementElifContext):
        return self.visitChildren(ctx)

    # Visit a parse tree produced by VIOLAParser#ifStatementElse.
    def visitIfStatementElse(self, ctx: VIOLAParser.IfStatementElseContext):
        return self.visitChildren(ctx)

    # Visit a parse tree produced by VIOLAParser#ifExpression.
    def visitIfExpression(self, ctx: VIOLAParser.IfExpressionContext):
        return self.visitChildren(ctx)

    # Visit a parse tree produced by VIOLAParser#unaryif.
    def visitUnaryif(self, ctx: VIOLAParser.UnaryifContext):
        return self.visitChildren(ctx)

    # Visit a parse tree produced by VIOLAParser#binaryif.
    def visitBinaryif(self, ctx: VIOLAParser.BinaryifContext):
        return self.visitChildren(ctx)

    # Visit a parse tree produced by VIOLAParser#unaryIfExpression.
    def visitUnaryIfExpression(self, ctx: VIOLAParser.UnaryIfExpressionContext):
        return self.visitChildren(ctx)

    # Visit a parse tree produced by VIOLAParser#binaryIfExpression.
    def visitBinaryIfExpression(self, ctx: VIOLAParser.BinaryIfExpressionContext):
        return self.visitChildren(ctx)

    # Visit a parse tree produced by VIOLAParser#ifExpressionInBinary.
    def visitIfExpressionInBinary(self, ctx: VIOLAParser.IfExpressionInBinaryContext):
        return self.visitChildren(ctx)

    # Visit a parse tree produced by VIOLAParser#forStatement.
    def visitForStatement(self, ctx: VIOLAParser.ForStatementContext):
        return self.visitChildren(ctx)

    # Visit a parse tree produced by VIOLAParser#whileStatement.
    def visitWhileStatement(self, ctx: VIOLAParser.WhileStatementContext):
        return self.visitChildren(ctx)
