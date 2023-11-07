#ifndef ASSEMBLE_H_
#define ASSEMBLE_H_

#include "asm.h"

int assembleFile(const char * fileName, const char * tempName, const char* workName) ;
int strcap(char*, char*);
char *skipSpace(char *);
int processFile(void);
int assemble(char *, int*);
int createCode(char *, int*);
char* fieldParse(char *p, opDescriptor *d, int *errorPtr);
int pickMask(int, flavor*, int*);
int tokenize(char *, char*, char*[], char*);


#endif
