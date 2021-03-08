# Lexical-Analyser-w-recursive-descent-parser

To compile on Linux / macOS:
gcc -std=c99 -o Analyzer.out Givens.c Parser.c Tokenizer.c Analyzer.c


Provided EBNF grammar: 

function 		--> header body
header 		--> VARTYPE IDENTIFIER LEFT_PARENTHESIS [arg-decl] RIGHT_PARENTHESIS
arg-decl		--> VARTYPE IDENTIFIER {COMMA VARTYPE IDENTIFIER}
body 			--> LEFT_BRACKET [statement-list] RIGHT_BRACKET
statement-list 	--> statement {statement}
statement 		--> while-loop | return | assignment | body
while-loop 		--> WHILE_KEYWORD LEFT_PARENTHESIS expression RIGHT_PARENTHESIS statement
return 		--> RETURN_KEYWORD expression EOL
assignment 		--> IDENTIFIER EQUAL expression EOL
expression 		--> term {BINOP term} | LEFT_PARENTHESIS expression RIGHT_PARENTHESIS
term 			--> IDENTIFIER | NUMBER 



Provided lexical structure: 

LEFT_PARENTHESIS 	--> (
RIGHT_PARENTHESIS 	--> )
LEFT_BRACKET 		--> {
RIGHT_BRACKET 		--> }
WHILE_KEYWORD 		--> while
RETURN_KEYWORD 	--> return
EQUAL 		 		--> =
COMMA				--> ,
EOL 					--> ;
VARTYPE 			--> int | void
IDENTIFIER 			--> [a-zA-Z][a-zA-Z0-9]*
BINOP 				--> + | * | != | == | %
NUMBER 				--> [0-9][0-9]*


Tokenizer.c will read characters from a given FILE variable and convert them into tokens. It will do so using a function defined as follows: 

_Bool tokenizer(struct lexics *aLex, int *numLex, FILE *inf);

Which takes an array of type lexics, an int pointer representing the number of tokens in the input file, and a pointer to a FILE. The tokenizer function will read characters from the given FILE parameter, creating lexemes and the associated tokens. Each time a lexeme is generated, a new lexics struct will be created and the lexeme added. The generated lexeme is then tokenized, the token is added to the generated lexics struct, the lexics struct is then added to the end of the given lexics array. (Note: another option is to generate lexemes first, then tokenize the generated lexemes) 

The given lexical structure is free format and the location of tokens in the text file does not affect their meaning. Alphanumeric lexemes will be delimited by both whitespace and by character lexemes. Because character lexemes are used as delimiters, they cannot be constructed one token at a time. Rather the next several tokens in the file will need to be examined to determine which (if any) character lexeme is present. 

Once the tokenization process is complete, the tokenizer function should return TRUE. If there occurs an error in the process, the function should return FALSE. 



Parser.c will implement a recursive decent parser based upon a provided EBNF grammar. It will do so using a function defined as follows: 

_Bool parser(struct lexics *someLexics, int numberOfLexics);

Which takes an array of type lexics and an int pointer representing the number of tokens in the given lexics array. The parser method must take the tokens (given in the array of lexics structs) and determine if they are legal in the language defined by the given grammar. The purpose of our parser is to apply the grammar rules and report any syntax errors. If no syntax errors are identified, parser returns TRUE, otherwise it returns FALSE.

Parser.c is a recursive decent predictive parser which utilizes single-symbol lookahead. If given a grammatically valid input, every token given must be parsed. If a syntax error is found, parsing does not need to continue. 

