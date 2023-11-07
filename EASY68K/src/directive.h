#ifndef DIRECTIVE_H_
#define DIRECTIVE_H_

int org(int, char*, char*, int*);
int section(int, char*, char*, int*);
int offset(int, char*, char*, int*);
int funct_end(int, char*, char*, int*);
int equ(int, char*, char*, int*);
int set(int, char*, char*, int*);
int dc(int, char *, char *, int*);
char* collect(char*, char*);
int dcb(int, char*, char*, int*);
int ds(int, char*, char*, int*);
int opt(int, char*, char*, int*);
int include(int, char*, char*, int*);
int incbin(int, char*, char*, int*);
int failError(int, char*, char*, int*);
int listOn(int, char*, char*, int*);
int listOff(int, char*, char*, int*);
int memory(int, char*, char*, int*);
int simhalt(int, char*, char*, int*);
int page(int, char*, char*, int*);

#endif
