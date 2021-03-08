// Austin Beggs CMSC 403 PROJECT 4

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "Givens.h"
#include <string.h>

_Bool passed;

_Bool isDelimiter(char ch);
void slice(const char *str, char *result, size_t start, size_t end);
void getToken(struct lexics *lex);
_Bool tokenizer(struct lexics *aLex, int *numLex, FILE *inf);



#endif

