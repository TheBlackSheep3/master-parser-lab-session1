grammar Expresison;

// Parser rules
expression
	: term plus expression
	| term
	;

term
	: factor times term
	| factor
	;

factor
	: number
	| par_op expression par_cl
	;

// Lexer rules
plus: '+';
times: '*';
number: [1-9][0-9]+;
par_op: '(';
par_cl: ')';
whitespace: [ \r\n\t]+ -> skip;
