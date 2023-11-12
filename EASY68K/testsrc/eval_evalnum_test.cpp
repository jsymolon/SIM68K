#include "gtest/gtest.h"
#include "eval.h"
#include <string>

// return the value of the operand at *p in numberPtr.
// refPtr set true if valid backwards reference.

//char* evalNumber(char *p, int *numberPtr, bool *refPtr, int *errorPt
TEST(evalnumber_1, evaltest) {
	const char *str = "-32767";
	//const_cast<char *>(str)
	int number = 0;
	bool ref = false;
	int error = 0;
	char* ret_p =  evalNumber(const_cast<char *>(str), &number, &ref, &error);
	EXPECT_EQ(number, -32767);
//
//	std::string s_out = std::string(dest);
//	EXPECT_EQ("ONE TWO THREE .PERIOD 'five',6,7 ", s_out);
	std::cout << ret_p;
}

TEST(evalnumber_2, evaltest) {
	const char *str = "$FF,";
	//const_cast<char *>(str)
	int number = 0;
	bool ref = false;
	int error = 0;
	char* ret_p =  evalNumber(const_cast<char *>(str), &number, &ref, &error);
	EXPECT_EQ(number, 255);
	EXPECT_EQ(ret_p, &str[3]);

	const char *str1 = "$FFFF";
	number = 0;
	ref = false;
	error = 0;
	ret_p =  evalNumber(const_cast<char *>(str1), &number, &ref, &error);
	EXPECT_EQ(number, 65535);

	const char *str2 = "#$FFFF";
	number = 0;
	ref = false;
	error = 0;
	ret_p =  evalNumber(const_cast<char *>(str2), &number, &ref, &error);
	EXPECT_EQ(number, 0);

	const char *str3 = "%11111111";
	number = 0;
	ref = false;
	error = 0;
	ret_p =  evalNumber(const_cast<char *>(str3), &number, &ref, &error);
	EXPECT_EQ(number, 255);
//
//	std::string s_out = std::string(dest);
//	EXPECT_EQ("ONE TWO THREE .PERIOD 'five',6,7 ", s_out);
//	std::cout << ret_p;
}

extern int loc;
constexpr int M32B = 32768;

TEST(evalnumber_loc, evaltest) {
	loc = M32B; // Set current assembly address to 8000
	const char *str = "* ";
	int number = 0;
	bool ref = false;
	int error = 0;
	char* ret_p =  evalNumber(const_cast<char *>(str), &number, &ref, &error);
	EXPECT_EQ(number, M32B);
	EXPECT_EQ(ret_p, &str[1]);

//
//	std::string s_out = std::string(dest);
//	EXPECT_EQ("ONE TWO THREE .PERIOD 'five',6,7 ", s_out);
//	std::cout << ret_p;
}

TEST(evalnumber_paren, evaltest) {
	const char *str = "(6+4)/2";
	int number = 0;
	bool ref = false;
	int error = 0;
	char* ret_p =  evalNumber(const_cast<char *>(str), &number, &ref, &error);
	EXPECT_EQ(number, 10);
	EXPECT_EQ(ret_p, &str[5]);

	const char *str1 = "(6+4/2)";
	number = 0;
	ref = false;
	error = 0;
	ret_p =  evalNumber(const_cast<char *>(str1), &number, &ref, &error);
	EXPECT_EQ(number, 8);
}

TEST(evalnumber_onesc, evaltest) {
	const char *str = "~127 ";
	int number = 0;
	bool ref = false;
	int error = 0;
	char* ret_p =  evalNumber(const_cast<char *>(str), &number, &ref, &error);
	EXPECT_EQ(number, -128);
	EXPECT_EQ(ret_p, &str[4]);
}
