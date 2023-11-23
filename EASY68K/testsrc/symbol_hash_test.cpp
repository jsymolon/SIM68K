#include "gtest/gtest.h"
#include "symbol.h"
#include <string>

// Return index for array of pointers to linked lists
// Returns 0 to MAXHASH inclusive based on first character of symbol.
//int hash(char *symbol)
//symbolDef* define(char *sym, int value, bool pass2, bool check, int *errorPtr);
//		Symbol
//		Found				  Returned
//		In	Create	  Action	  Error
//		Table?	Flag	  Taken		  Code
//		------	------    --------------  -----------
//		  N		FALSE     None		  UNDEFINED
//		  N		true      Symbol created  OK
//      Y		FALSE     None		  OK
//		  Y		true      None		  MULTIPLE_DEFS
//
const int linelen = 256;

TEST(lookup, symboltest) {
	char str[linelen] = ".period";
	int error = 0;
	symbolDef* symd = lookup(str, true, &error);
	std::string s_out = std::string(symd->name);
	EXPECT_EQ(":period", s_out);
}

TEST(def_lookup, symboltest) {
	char str[linelen] = ".label";
	int error = 0;
	symbolDef* symd = define(str, 5, false, true, &error);
	std::string s_out = std::string(symd->name);
	EXPECT_EQ(":label", s_out);

	symbolDef* syml = lookup(str, false, &error);

	s_out = std::string(syml->name);
	EXPECT_EQ(":label", s_out);
	EXPECT_EQ(5, syml->value);
}
