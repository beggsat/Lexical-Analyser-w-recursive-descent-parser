// Austin Beggs CMSC 403 PROJECT 4



#include "Parser.h"

/*
function        --> header body
header          --> VARTYPE IDENTIFIER LEFT_PARENTHESIS [arg-decl] RIGHT_PARENTHESIS
arg-decl        --> VARTYPE IDENTIFIER {COMMA VARTYPE IDENTIFIER }
body            --> LEFT_BRACKET [statement-list] RIGHT_BRACKET
statement-list  --> statement {statement}
statement       --> while-loop | return | assignment | body
while-loop      --> WHILE_KEYWORD LEFT_PARENTHESIS expression RIGHT_PARENTHESIS statement
return          --> RETURN_KEYWORD expression EOL
assignment      --> IDENTIFIER EQUAL expression EOL
expression      --> term {BINOP term} | LEFT_PARENTHESIS expression RIGHT_PARENTHESIS
term            --> IDENTIFIER | NUMBER 
*/

// 0    LEFT_PARENTHESIS    --> (
// 1    RIGHT_PARENTHESIS   --> )
// 2    LEFT_BRACKET        --> {
// 3    RIGHT_BRACKET       --> }
// 4    WHILE_KEYWORD       --> while
// 5    RETURN_KEYWORD      --> return
// 6    EQUAL               --> =
// 7    COMMA               --> ,
// 8    EOL                 --> ;
// 9    VARTYPE             --> int | void
// 10    IDENTIFIER          --> [a-zA-Z][a-zA-Z0-9]*
// 11    BINOP               --> + | * | != | == | %
// 12    NUMBER              --> [0-9][0-9]*

struct lexics *globalLexics;
_Bool passed2 = TRUE;
int *index;
int *a;


int next_value(){
	int lookahead = -1;
	
		
		
	lookahead = globalLexics[(*index)+1].token;
	(*index)++;
	int test = 0;
	test = globalLexics[*index].token;
	*a = test;
	//printf("a value: \n");
	//printf("%d\n", *a);
	
	return lookahead;
}

//see next value in array without incrementing in match
int peek(){

	return globalLexics[(*index)+1].token;
}



void match(int tok) {
  if (tok != next_value()){
	//printf("Error in match! \n");
	printf("Error in match! \n");
	passed2 = FALSE;
  } 
  
}



void function(){ 
	if (*a == 9){
		header();
		body();
	}
	else{
		printf("Parse Failed: invalid function \n");
		passed2 = FALSE;
	}
}


//VARTYPE IDENTIFIER LEFT_PARENTHESIS [arg-decl] RIGHT_PARENTHESIS
void header(){
	//printf("header a: ");
	//printf("%d\n", *a);
	//VARTYPE
	if (*a == 9){
		match(10);  // anything not ( here is wrong
		header();
	}
	//IDENTIFIER
	else if (*a == 10){
		match(0);	// anything not FUNC here is wrong
		header();
		
	}
	//LEFT_PARENTHESIS
	else if (*a == 0){//[arg-decl] and //RIGHT_PARENTHESIS
		if (peek() == 1){ //no arg decl
			match(1);
			header();
			//end of function
		}
		else{
			arg_decl();
			header();
		}
		  // anything not FUNC here is wrong
	}
	else if (*a == 1){
		//do nothing we are done in function
	}
	else{
		printf("Parse Failed: invalid function \n");
		passed2 = FALSE;
	}
	//[arg-decl] 
	//RIGHT_PARENTHESIS
}      

void arg_decl(){      
	//VARTYPE() 
	//IDENTIFIER()
	//{COMMA VARTYPE IDENTIFIER }

	//printf("arg a: ");
	//printf("%d\n", *a);
	//left par to VARTYPE
	if (*a == 0){
		match(9);  // anything not ( here is wrong
		arg_decl();
	}
	else if (*a == 9){
		
		match(10);  // anything not ( here is wrong
		arg_decl();
	}
	//IDENTIFIER
	else if (*a == 10){
		if (peek() == 7) //loop if theres a comma
		{
			match(7);
			arg_decl();
		}	
		else{
			//printf("done with argdec and header \n");
			match(1); //right parenthesis
		}
	}
	else if (*a == 7){//comma
		match(9);  // anything not ( here is wrong
		arg_decl();
	}
	else{
		printf("Parse Failed: invalid arg declaration \n");
		passed2 = FALSE;
	}


}

void body (){     
	//printf("body a: ");
	//printf("%d\n", *a);   
	//LEFT_BRACKET 
	//[statement-list] 
	//RIGHT_BRACKET
	if (*a == 1){//right parent to left bracket
		//printf("matched 2 in body \n");
		match(2);
		body();
	}
	if (*a == 2){
		if (peek() == 3) //check if theres a statement
		{
			match(3);
			body();
			
		}	
		else{
			//printf("went into statement list from body \n");
			statement_list();
			match(3);
			//printf("should be matching 3 here -------------------------- \n");
		}
	}
	else if (*a == 3 && peek() != 0){
		printf("Parse Failed: invalid body \n");
		passed2 = FALSE;
	}
	else if (*a == 3){
		//done with body
	}
	else{
		printf("Parse Failed: invalid body \n");
		passed2 = FALSE;
	}
}

void statement_list(){  
	statement();
}

void statement(){       

	//printf("statement a: ");
	//printf("%d\n", *a);

	//while-loop | return | assignment | body

	if (peek() == 4) //while loop
	{
		//printf("peek is 4 in while loop \n");
		match(4);
		while_loop();
		//printf("comes back here? \n");
		statement();

	}
	else if(peek() == 5) { //return statement
		match(5);
		return_();
		statement();
	}	
	else if(peek() == 10) { //assignment
		match(10);
		//printf("test test test test \n");
		assignment();
		statement();
	}	
	else if (peek() == 2) //left bracket
	{

		match(2);
		body();
		//printf("exited body recursion------------------------------\n");
		statement();

	}
	else if (*a == 8 || *a == 3){

		//done with statement
	}
//	else if (peek() == 3){
//		match(3);
//		statement();
//	}
//	else if (*a == 2){
//		printf("then here \n");
//		statement();
//	}
	else{
		passed2 = FALSE;
		printf("Parse Failed: invalid statement \n");
	}

}

void while_loop(){      
	//WHILE_KEYWORD 
	//LEFT_PARENTHESIS 
	//expression 
	//RIGHT_PARENTHESIS 
	//statement

	//printf("while a: ");
	//printf("%d\n", *a);

	if (*a == 4){//match LEFT_PARENTHESIS
		match(0);
		while_loop();
	}
	else if (*a == 0){//match LEFT_PARENTHESIS to right parenthesis
		expression();
		match(1);
		//printf("should be here------------------- \n");
		while_loop();
	}
	else if (*a == 1){//end of expression
		//printf("and then in here \n");
		statement();
	}
	else{
		printf("Parse Failed: invalid while \n");
		passed2 = FALSE;
	}
}

void return_(){     
	//printf("return a: ");
	//printf("%d\n", *a);
	//RETURN_KEYWORD already matched()
	if (*a == 5){//LEFT_PARENTHESIS
		expression();
		if (*a != 5){
			return_();
		}
		
	}
	else if (*a == 1 || *a == 10 || *a == 12){
		match(8); //eol
		return_();
	}
	else if (*a == 8){
		//done passed return
	}
	else{
		printf("Parse Failed: invalid return \n");
		passed2 = FALSE;
	}
	//expression 
	//EOL


}

void assignment(){      
	//IDENTIFIER 
	//EQUAL 
	//expression 
	//EOL
	//printf("assignment a: ");
	//printf("%d\n", *a);


	if (peek() == 8){//before identifier check
		//printf("matches the 8 here \n");
		match(8); //eol
		assignment();
	}
	else if (*a == 10){//equal
		match(6);
		assignment();
	}
	else if (*a == 6){//equal
		expression();
		match(8);
		assignment();
	}
	else if (*a == 8){
		//done passed return
	}
	else{
		printf("Parse Failed: invalid assignment \n");
		passed2 = FALSE;
	}

}

void expression(){      
	//term {BINOP term} | LEFT_PARENTHESIS expression RIGHT_PARENTHESIS
	//if (*a == 0){//LEFT_PARENTHESIS
	//}
	//printf("expression a: ");
	//printf("%d\n", *a);

	if (peek() == 0){//LEFT_parenthesis
		match(0);
		expression();
		match(1);
	}
	else if(*a == 11){ //binop
		term();
		expression();
	}
	else if (peek() == 10 || peek() == 12){//term
		//printf("going into term \n");
		term();
		if (peek() == 11){
			match(11); //binop
			expression();
		}
		
	}
	else if (*a == 10 || *a == 12){//term
		if (peek() == 1 || peek() == 8){
			//dont match 1 or 8 matched after expression ends
			//printf("fails here after matching i think \n");
		}
		else{
			match(11); //binop
			expression();
		}

	}
	else {
		printf("Parse Failed: invalid expression \n");
	   	passed2 = FALSE;
	}

}

void term(){
	//IDENTIFIER || NUMBER
   
	if (peek() == 10){
		match(10);
	}
	else if(peek() == 12){
		match(12);
	}
   	else{
		printf("Parse Failed: invalid term\n");
	   	passed2 = FALSE;
	}
   
   
} 


_Bool parser(struct lexics *someLexics, int numberOfLexics){
	
	globalLexics = someLexics;

	int zero = 0;
	index = &zero;

	//looping through tokens 1 by 1
	//while(temp < numberOfLexics-1){

		int test = 0;
		test = someLexics[*index].token;
		a = &test;


		//printf("%s\n", "current");
		//printf("%d\n",*a);
		
		//lookahead = next_value();
		//printf("%s\n", "lookahead");
		//printf("%d\n", lookahead);

		//printf("%s\n", "index");
		//printf("%d\n", *index);

		function();


		/*
		{
			if (lookahead != T_FUNC) { // anything not FUNC here is wrong
				printf("syntax error \n");
				exit(0);
			} else
				lookahead = yylex(); // global 'lookahead' holds next token
			ParseIdentifier();
		*/

		//temp++;

		if (passed2 == 1)
		{
			printf("Passed the parse\n") ;

		}
		else{
			printf("Failed parse\n") ;
		}

	//}

	return passed2;	
}
