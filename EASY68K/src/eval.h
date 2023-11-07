#ifndef EVAL_H_
#define EVAL_H_

char* eval(char*, int*, bool*, int*);
char* evalNumber(char*, int*, bool*, int*);
int precedence(char);
int doOp(int, int, char, int*);

#endif
