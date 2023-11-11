#include "gtest/gtest.h"
#include "assemble.h"
#include <string>

//char* skipSpace(char *p)
TEST(skipSpace, assembletest) {
	const char *str = " .period";
	char *d = skipSpace(const_cast<char *>(str));
	EXPECT_EQ('.', *d);
}
