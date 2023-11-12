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
