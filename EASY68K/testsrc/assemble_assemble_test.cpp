#include "gtest/gtest.h"
#include "assemble.h"

const int linelen = 256;
// Conditionally Assemble one line of code
//int assemble(char *line, int *errorPtr)
TEST(simple1, assembletest) {
	char instrStr[linelen] = ".period";
	int error = 0;
	int status = assemble(instrStr, &error);
   EXPECT_EQ(0, status);
}

TEST(simple2, assembletest) {
	char instrStr[linelen] = "     clr.l   d2";
	int error = 0;
	int status = assemble(instrStr, &error);
   EXPECT_EQ(0, status);
}

