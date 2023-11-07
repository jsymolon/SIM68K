#ifndef STRUCTURED_H_
#define STRUCTURED_H_

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <cstring>

std::string getBcc(std::string cc, int mode, int orx);

void outCmpBcc(char *size, char *op1, char *cc, char *op2, char *op3,
		std::string label, int &error);
void assembleStc(const char *line);
std::string IntToHex(uint32_t value, int length);
int asmStructure(int, char*, char*, int*);

#endif
