// DELETE THIS CONTENT IF YOU PUT COMBINED GRAMMAR IN Parser TAB
lexer grammar VIOLA;

// BINARY COMPARISON
AND : '&&' ;
OR : '||' ;
EQUALITY : '==' | '!=' | '>=' | '<=' ;
GREATER: '>' ;
LESS: '<' ;
NOT: '!' ;
COMPARISON: AND | OR | EQUALITY | GREATER | LESS;

// MATHEMATICAL EXPRESSIONS
ASSIGNMENT: '=' ;
ADDITION: '+' ;
MULTIPLICATION: '*' ;
SUBTRACTION: '-' ;
DIVISION: '/';
INCREMENT: '++' ;
DECREMENT: '--' ;

// PUNCTUATION MARKS
COMMA : ',' ;
DOT: '.' ;
COLON: ':';
SEMICOLON: ';' ;
QUOTATIONMARK: '"';
INLINECOMMENT: '//' ~[\r\n]* -> channel(HIDDEN) ;
// BLOCKCOMMENT: '\*' ~[\r\n]* '*/' -> channel (HIDDEN);

// BRACKETS
LPAREN : '(' ;
RPAREN : ')' ;
LCURLY : '{' ;
RCURLY : '}' ;
LSQUARE: '[' ;
RSQUARE: ']' ;

// RESERVED WORDS
RETURN: 'return' ;
TYPE: 'int' | 'char' | 'string' ;
VOID: 'void' ;
IF: 'if' ;
FOR: 'for' ;
ELSE: 'else' ; 
ELIF: 'elif' ; 
CASE: 'case' ;
WHILE: 'while' ;
SWITCH: 'switch' ;
FUNC: 'subr' ;
REF: 'ref' ;
FUNCRETURN: '->' ;


// STRING 
STRING: QUOTATIONMARK (~["\r\n] | '\\"')* QUOTATIONMARK;

// DEFAULT
// DEFAULT: .;
INT : [-]?[0-9]+ ;
ID: [a-zA-Z_][a-zA-Z_0-9]* ;
WS: [ \t\n\r\f]+ -> skip ;
NEWLINE : ('\r'? '\n') | '\n';
TAB : '\t';
// TEXT: ~[\\"]+ ;
