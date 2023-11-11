#include "gtest/gtest.h"
#include "assemble.h"
#include <string>

// Parameters:
//      instr = the string to tokenize
//      delim = string of delimiter characters
//              (spaces are not default delimiters)
//              period delimiters are included in the start of the next token
//      token[] = pointers to tokens
//      tokens = new string full of tokens
// Returns number of tokens extracted.
//int tokenize(char *instr, char *delim, char *token[], char *tokens)
const int N_TOKENS = 128;
TEST(tokenize1, assembletest) {
	const char *instr = "One Two Three .period 'five',6,7 ";
	const char *delim = " ,";
	char *token[N_TOKENS];
	char tokens[N_TOKENS];
	int qty = tokenize(const_cast<char *>(instr), const_cast<char *>(delim), token, tokens);
	EXPECT_EQ(7, qty);
	auto s_prev = ' ';
	for (auto i = 0; i<N_TOKENS; i++) {
		if (s_prev == '\0' && tokens[i] == '\0')
			break;
		s_prev = tokens[i];
		if (tokens[i] == '\0')
			tokens[i] = '\t';
	}
	std::string s_out = std::string(tokens);
	std::cout << s_out;
}

TEST(tokenize2, assembletest) {
	const char *instr = "ldiv:   movem.l d2-d3,-(sp)";
	const char *delim = " ,";
	char *token[N_TOKENS];
	char tokens[N_TOKENS];
	int qty = tokenize(const_cast<char*>(instr), const_cast<char*>(delim), token, tokens);
	EXPECT_EQ(4, qty);
	auto s_prev = ' ';
	for (auto i = 0; i<N_TOKENS; i++) {
		if (s_prev == '\0' && tokens[i] == '\0')
			break;
		s_prev = tokens[i];
		if (tokens[i] == '\0')
			tokens[i] = '\t';
	}
	std::string s_out = std::string(tokens);
	std::cout << s_out;
}
