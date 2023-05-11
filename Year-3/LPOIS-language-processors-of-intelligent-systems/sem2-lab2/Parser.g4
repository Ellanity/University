parser grammar VIOLA;
options { tokenVocab=VIOLA; }

// parser rules
program: (functionDefine SEMICOLON)* (statement | INLINECOMMENT)* EOF;

statement: functionСall SEMICOLON
		 | functionBody
		 | ifStatement
		 | forStatement
		 | whileStatement
         | assignmentStatement SEMICOLON
         | assignmentStatementArray SEMICOLON
		 ;

// Assignment Statement
assignmentStatement: TYPE? ID (COMMA ID)+ ASSIGNMENT expression (COMMA expression)+  
                   | TYPE? ID ASSIGNMENT expression 
				   | TYPE ID
				   | unaryArithmeticExpression
                   ;
				   
assignmentStatementArray: (TYPE LSQUARE RSQUARE)? ID (COMMA ID)+ ASSIGNMENT primaryExpression (COMMA primaryExpression)+
                        | (TYPE LSQUARE RSQUARE)? ID ASSIGNMENT primaryExpression
						;
						
expression: arithmeticExpressionSimple | binaryArithmeticExpression;

arithmeticExpressionSimple: primaryExpression 
						  | unaryArithmeticExpression 
						  | binaryArithmeticExpression
						  ;

arithmeticExpressionInBinary: primaryExpression 
							| unaryArithmeticExpression
							;

unarymath: INCREMENT | DECREMENT;
binarymath: ADDITION | MULTIPLICATION | SUBTRACTION | DIVISION ;

unaryArithmeticExpression: unarymath primaryExpression
						 | functionСall
						 | primaryExpression unarymath;
						 // | primaryExpression;

binaryArithmeticExpression: (arithmeticExpressionInBinary | LPAREN arithmeticExpressionInBinary RPAREN) (binarymath (arithmeticExpressionInBinary | LPAREN arithmeticExpressionInBinary RPAREN))*;

primaryExpression: (LPAREN TYPE RPAREN)? 
				 ( functionСall
				 | ID
                 | INT
                 | STRING
                 | LPAREN expression RPAREN
                 | arrayAccess
				 | arrayDefineForm
				 );

arrayAccess: ID arraySliceForm;

arrayDefineForm: LSQUARE expression? (COMMA expression)+ RSQUARE?;

arraySliceForm: LSQUARE (expression | COLON expression | expression COLON expression) RSQUARE;

// Funcs
functionСall: ((ID | STRING) DOT)* ID LPAREN ((REF? primaryExpression | expression) (COMMA REF? primaryExpression | expression)*)? RPAREN (DOT ID LPAREN ((REF? primaryExpression | expression) (COMMA REF? primaryExpression | expression)*)? RPAREN)*;

// functionDefine: FUNC ID LPAREN (REF? (TYPE | (TYPE LSQUARE RSQUARE)?) ID)? (COMMA REF? (TYPE | (TYPE LSQUARE RSQUARE)?) ID)* RPAREN FUNCRETURN ((TYPE | (TYPE LSQUARE RSQUARE)?) | VOID);

allTypesWithRefs: REF? TYPE (LSQUARE RSQUARE)?; 

functionDefine: FUNC ID LPAREN ((allTypesWithRefs ID) (COMMA allTypesWithRefs ID)*)? RPAREN FUNCRETURN ((TYPE | (TYPE LSQUARE RSQUARE)) | VOID);

//(type([])? id (,type([])? id)*)?
// subr reverse(string input, int startIndex, int endIndex) -> string:

// functionBody: FUNC ID LPAREN (REF? (TYPE | (TYPE LSQUARE RSQUARE)?) ID)? (COMMA REF? (TYPE | (TYPE LSQUARE RSQUARE)?) ID)* RPAREN FUNCRETURN ((TYPE | (TYPE LSQUARE RSQUARE)?) | VOID) COLON TAB? (statement)* (TAB? RETURN canBeReturned);
functionBody: functionDefine COLON TAB? (statement)* (TAB? RETURN canBeReturned);

canBeReturned: ((primaryExpression | assignmentStatement | assignmentStatementArray) SEMICOLON) | SEMICOLON;

// If Statement
ifStatement: ifStatementFirstBlock ifStatementElif* ifStatementElse?;

ifStatementFirstBlock: IF LPAREN (ifExpression) RPAREN COLON (TAB? statement)+;

ifStatementElif: ELIF LPAREN ifExpression RPAREN COLON (TAB? statement)+;

ifStatementElse: ELSE COLON (TAB? statement)+;

ifExpression: unaryIfExpression
			| binaryIfExpression
			;

unaryif: NOT;
binaryif: AND | OR | EQUALITY | GREATER | LESS;

unaryIfExpression: unaryif primaryExpression | primaryExpression;

binaryIfExpression: (ifExpressionInBinary | LPAREN ifExpressionInBinary RPAREN) ((binarymath | binaryif) (ifExpressionInBinary | LPAREN ifExpressionInBinary RPAREN))*;

ifExpressionInBinary: primaryExpression 
					| unaryIfExpression
					| arithmeticExpressionInBinary
					;
					
// For Statement

forStatement: FOR LPAREN assignmentStatement SEMICOLON ifExpression SEMICOLON arithmeticExpressionSimple RPAREN COLON (TAB? statement)+;

// While Statement

whileStatement: WHILE LPAREN (ifExpression) RPAREN COLON (TAB? statement)+;