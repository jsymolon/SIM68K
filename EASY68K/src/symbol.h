#ifndef SYMBOL_H_
#define SYMBOL_H_

#include "asm.h"

void clearSymbols();
symbolDef* lookup(char *, int, int*);
int optCRE();
int hash(char *);
symbolDef* define(char *, int, bool, bool, int*);

#endif
