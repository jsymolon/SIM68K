#include "gtest/gtest.h"
#include "assemble.h"

const int linelen = 256;
// Conditionally Assemble one line of code
//int createCode(char *capLine, int *errorPtr)
TEST(createcode, assembletest) {
	char instrStr[linelen] = "     CLR.L   D2";
	int error = 0;
	int status = createCode(instrStr, &error);
   EXPECT_EQ(0, status);
}

