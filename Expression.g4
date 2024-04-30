grammar Expression;

// Parser rules
expression
	: term PLUS expression
	| term
	;

term
	: factor TIMES term
	| factor
	;

factor
	: NUMBER
	| PAR_OP expression PAR_CL
	;

// Lexer rules
PLUS: '+';
TIMES: '*';
NUMBER: [1-9][0-9]+;
PAR_OP: '(';
PAR_CL: ')';
WS: [ \r\n\t]+ -> skip;
