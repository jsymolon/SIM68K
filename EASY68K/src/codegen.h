#ifndef CODEGEN_H_
#define CODEGEN_H_

#include "asm.h"

int output(int, int);
int effAddr(opDescriptor*);
int extWords(opDescriptor*, int, int*);

#endif
