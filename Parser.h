// Austin Beggs CMSC 403 PROJECT 4

#ifndef PARSER_H
#define PARSER_H

#include "Givens.h"
#include <stdlib.h>

struct lexics *globalLexics;
_Bool passed2;
int *index;
int *a;

int next_value();
int peek();
void match(int tok);

void function();
void header();
void body();
void arg_decl();
void statement_list();
void statement();
void while_loop();
void return_();
void assignment();
void expression();
void term();


_Bool parser(struct lexics *someLexics, int numberOfLexics);


#endif