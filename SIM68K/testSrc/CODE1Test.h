#ifndef TESTCODE1_H_
#define TESTCODE1_H_

#include "../src/OPCODES.H"
#include "gtest/gtest.h"

class CODE1Test : public ::testing::Test {

 public:
	CODE1Test() {
	     // You can do set-up work for each test here.
	  }

	  ~CODE1Test() override {
	     // You can do clean-up work that doesn't throw exceptions here.
	  }

	  // If the constructor and destructor are not enough for setting up
	  // and cleaning up each test, you can define the following methods:

	  void SetUp() override {
	     // Code here will be called immediately after the constructor (right
	     // before each test).
	  }

	  void TearDown() override {
	     // Code here will be called immediately after each test (right
	     // before the destructor).
	  }
};
#endif /* TESTCODE1_H_ */
