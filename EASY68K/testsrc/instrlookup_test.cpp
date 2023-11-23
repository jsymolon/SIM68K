#include "gtest/gtest.h"
#include "instlook.h"

const int linelen = 256;
// Conditionally Assemble one line of code
//char* instLookup(char *p, instruction *(*instPtrPtr), char *sizePtr,int *errorPtr)
TEST(instLookup_1, instrlook_test) {
	char p[linelen] = "CLR.L   D2";
	instruction *tablePtr;
	char size;
	int error = 0;
	char* x = instLookup(p, &tablePtr, &size, &error);
   EXPECT_EQ(x, &p[5]);
   // other way will not "match"
   std::string mn = tablePtr->mnemonic;
   EXPECT_EQ(mn,"CLR");
   EXPECT_EQ(4, size);
   EXPECT_EQ(0, error);
}

TEST(instLookup_2, instrlook_test) {
	char p[linelen] = "SIMHALT";
	instruction *tablePtr;
	char size;
	int error = 0;
	char* x = instLookup(p, &tablePtr, &size, &error);
   EXPECT_EQ(x, &p[7]);
   // other way will not "match"
   std::string mn = tablePtr->mnemonic;
   EXPECT_EQ(mn,"SIMHALT");
   EXPECT_EQ(0, size);
   EXPECT_EQ(0, error);
}

