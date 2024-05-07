grammar Expression;

// Parser rules
start: expression EOF;

expression
	: term expressionPrime
	;

expressionPrime
	: /* epsilon */
	| PLUS expression
	;

term
	: factor termPrime
	;

termPrime
	: /* epsilon */
	| TIMES term
	;

factor
	: NUMBER
	| PAR_OP expression PAR_CL
	;

// Lexer rules
PLUS: '+';
TIMES: '*';
NUMBER: [0-9]+;
PAR_OP: '(';
PAR_CL: ')';
WS: [ \r\n\t]+ -> skip;
