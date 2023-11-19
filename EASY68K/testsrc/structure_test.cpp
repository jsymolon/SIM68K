#include "gtest/gtest.h"
#include "structured.h"
#include <string>

//std::string IntToHex(uint32_t value, int length)
TEST(inttohex, structuretest) {
	std::string val = IntToHex(32767, 8);
	EXPECT_EQ("0x00007fff", val);

	std::string s_out = std::string(val);
	EXPECT_EQ("0x00007fff", s_out);
	//std::cout << s_out;
}
