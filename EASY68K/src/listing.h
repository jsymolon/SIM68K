#ifndef LISTING_H_
#define LISTING_H_

int initList(char*);
int listLine(const char*, char[] = "\0");
int listLoc(void);
int listCond(bool);
int listError(char *lineNum, char *errMsg);
int listText(const char *text);
int listObj(int, int);
int finishList();

#endif
