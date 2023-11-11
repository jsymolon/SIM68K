#include "gtest/gtest.h"
#include "error.h"
#include "asm.h"
#include "listing.h"
#include <string>
#include <cstdio>
#include <stdio.h>
#include <iostream>
#include <fstream>

extern FILE *listFile;

//int printError(FILE *outFile, int errorCode, int lineNum)
TEST(printerror_1, errortest) {
	char buffer[L_tmpnam];
	tmpnam(buffer);
	initList(buffer);
	int status = printError(listFile, 1, 1);
	finishList();
	EXPECT_EQ(NORMAL, status);
	std::ifstream tfile;
	tfile.open (buffer);
	std::string line;
	getline (tfile,line);
	tfile.close();
	std::string chkstr = std::string("00000000 Starting Address");
	EXPECT_TRUE(chkstr == line);
}

TEST(printerror_2, errortest) {
	char buffer[L_tmpnam];
	tmpnam(buffer);
	initList(buffer);
	finishList();
	int status = printError(NULL, EXCEPTION, 0);
	EXPECT_EQ(NORMAL, status);
	std::ifstream tfile;
	tfile.open (buffer);
	std::string line;
	getline (tfile,line);
	tfile.close();
	std::string chkstr = std::string("00000000 Starting Address");
	EXPECT_TRUE(chkstr == line);
}
