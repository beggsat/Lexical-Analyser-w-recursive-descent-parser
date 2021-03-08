// Austin Beggs CMSC 403 PROJECT 4

#include "Tokenizer.h"

_Bool passed = TRUE;

_Bool isDelimiter(char ch) { 
    if (ch == ' ' || ch == '\t' ||ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == ',' || ch == ';' || ch == '>' || ch == '\n' ||
        ch == '<' || ch == '=' || ch == '(' || ch == ')' || ch == '\0' ||
        ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == '!' )
        return (TRUE); 
    return (FALSE); 
} 

void slice(const char *str, char *result, size_t start, size_t end)
{
    strncpy(result, str + start, end - start);
}



void getToken(struct lexics *lex)
{
    char string[MY_CHAR_MAX];
    strcpy(string, lex->lexeme);

    //printf("%s\n", string);

    if (strcmp(string, "(") == 0) {
        lex->token = LEFT_PARENTHESIS;
    } 
    else if (strcmp(string, ")") == 0){
        lex->token = RIGHT_PARENTHESIS;
    }
    else if (strcmp(string, "{") == 0){
        lex->token = LEFT_BRACKET;
    }
    else if (strcmp(string, "}") == 0){
        lex->token = RIGHT_BRACKET;
    }
    else if (strcmp(string, "while") == 0){
        lex->token = WHILE_KEYWORD;
    }
    else if (strcmp(string, "return") == 0){
        lex->token = RETURN_KEYWORD;
    }
    else if (strcmp(string, "=") == 0){
        lex->token = EQUAL;
    }
    else if (strcmp(string, ",") == 0){
        lex->token = COMMA;
    }
    else if (strcmp(string, ";") == 0){
        lex->token = EOL;
    }
    else if (strcmp(string, "int") == 0 || strcmp(string, "void") == 0){
        lex->token = VARTYPE;
    }
    else if (validIdentifier(string) == TRUE){
        lex->token = IDENTIFIER;

    }//| * | != | == | %"
    else if (strcmp(string, "+") == 0 || strcmp(string, "*") == 0 || 
             strcmp(string, "!=") == 0 || strcmp(string, "==") == 0 || strcmp(string, "%") == 0){
        lex->token = BINOP;
    }
    else if (validNumber(string) == TRUE){
        lex->token = NUMBER;
    }
    else {
        printf("%s\n", "--------------FAILED TO FIND TOKEN: --------------------");
        printf("%s\n", string);
        passed = FALSE;
    }

    
}

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


       



_Bool tokenizer(struct lexics *aLex, int *numLex, FILE *inf){
	//array of type lexics, an int pointer representing the number of tokens in the input file, and a pointer to a FILE

   
   
    char input[MY_CHAR_MAX];
    char temp[MY_CHAR_MAX];
    memset(input, 0, MY_CHAR_MAX);
    memset(temp, 0, MY_CHAR_MAX);
    

    //read char from file
    /*
    while (temp[strlen(temp)-1] != '\n')
    {
        printf("test\n");
        fgets(temp, MY_CHAR_MAX, inf) != NULL;
        if (temp[strlen(temp)-1] == '\n'){
            printf("%s\n", "why isnt this working");
            printf("%s\n", temp);
            printf("%s\n", input);
            strcat(input, temp);
            printf("%s\n", input);
            fgets(temp, MY_CHAR_MAX, inf) != NULL;
        }
        printf("%s\n", temp);
        printf("%s\n", input);
        strcat(input, temp);
        printf("%s\n", input);
    }

    */
    
    while(fgets(temp, MY_CHAR_MAX, inf)) {
        strcat(input, temp);
    }

    printf("%s\n", "input: ");
    printf("%s\n", input);

    char currentChar;
    int loc = 0;

    //create lexemes, assign tokens
    //each lexeme a new lexics struct will be created
    int len = strlen( input );
    for (int i = 0; i < len; i++){
        //printing out chars as we go
        //printf("%c\n", input[i]);
        
        if (isDelimiter(input[i]) == TRUE){
            if (input[i] != ' ' && input[i] != '\n')
            {
                //case for character delimiter, getting lexeme before char delim
                if (isDelimiter(input[i-1]) == FALSE && input[i-1] != '\n'){ //&& input[i-1] != '\n'
                    
                    //getting rid of newline char (messing up the tokens)

                    
                

                    //printf("%s", "previous delimiter found:\n");
                    memset(temp, 0, MY_CHAR_MAX);
                    struct lexics newStruct;
                    slice(input, temp, loc, i); //slice from [loc to i]
                    strcpy(newStruct.lexeme , temp);
                    //printf("%s\n", newStruct.lexeme);
                    aLex[*numLex] = newStruct;
                    (*numLex)++;
                    //printf("%s\n", "break");

                    
                    
                }
                

               
                //printf("%s", "char delimiter found:\n");
                //do the current char delimiter its on
                memset(temp, 0, MY_CHAR_MAX);
                struct lexics newStruct;
                temp[0] = input[i];

                //special case for ! not capturing
                if (input[i] == '!'){
                    loc++;
                    i++;
                    temp[1] = input[i];
                }

                //special case for == not capturing
                if (input[i] == '=' && input[i+1] == '='){
                    loc++;
                    i++;
                    temp[1] = input[i];
                }


                strcpy(newStruct.lexeme , temp);
                //printf("%s\n", newStruct.lexeme);
                //token()
                aLex[*numLex] = newStruct;
                (*numLex)++;
                loc = i+1;
                //increment loc to next char (multiple spaces back to back)
                while (input[i+1] == ' ' || input[i+1] == '\n' || input[i+1] == '\t')
                {
                    //printf("space found, skipping\n");
                    loc++;
                    i++;
                }
                
                //printf("%s\n", "break");
            }
            else {

                //printf("%s", "whitespace delimiter found:\n");
                //whitespace delimiter

                memset(temp, 0, MY_CHAR_MAX);
                struct lexics newStruct;
                slice(input, temp, loc, i); //slice from [loc to i]
                strcpy(newStruct.lexeme , temp);
                aLex[*numLex] = newStruct;
                (*numLex)++;
                loc = i+1;
                //printf("%s\n", "break");
            }
        }   

        // case for 1 word lexes not capturing due to no delimiter
        if (*numLex == 0 && i == len-1){
            memset(temp, 0, MY_CHAR_MAX);
            struct lexics newStruct;
            slice(input, temp, loc, i+1); //slice from [loc to i]
            strcpy(newStruct.lexeme , temp);
            //printf("%s\n", newStruct.lexeme);
            aLex[*numLex] = newStruct;
            (*numLex)++;
        }
    }

   

    printf("%s\n", "done with lexes");

    //tokenize the lexems

    for(int i = 0; i < *numLex; i++){
		getToken(&aLex[i]);
	}

    printf("%s\n", "done setting tokens:");
    
    
    for(int i = 0; i < *numLex; i++){
        printf("%d  ",aLex[i].token);
        printf("%s\n",aLex[i].lexeme);
	}
    

    
    //tokenize lexeme, add token to lexics struct, then add to end of given lexics array

	return passed;	
}