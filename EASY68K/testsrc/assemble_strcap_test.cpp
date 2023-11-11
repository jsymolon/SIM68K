#include "gtest/gtest.h"
#include "assemble.h"
#include <string>

//int strcap(char *d, char *s)
TEST(strcap, assembletest) {
	const char *str = "One Two Three .period 'five',6,7 ";
	char dest[512];
	int status =  strcap(dest, const_cast<char *>(str));
	EXPECT_EQ(NORMAL, status);

	std::string s_out = std::string(dest);
	EXPECT_EQ("ONE TWO THREE .PERIOD 'five',6,7 ", s_out);
	//std::cout << s_out;
}
