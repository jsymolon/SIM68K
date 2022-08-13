
#ifndef UTILS_EFFADDTEST_H_
#define UTILS_EFFADDTEST_H_

#include "../src/UTILS.h"

#include "gtest/gtest.h"

class UTILS_effaddTest : public ::testing::Test {

 public:
	UTILS_effaddTest() {
	     // You can do set-up work for each test here.
	  }

	  ~UTILS_effaddTest() override {
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
#endif /* UTILS_EFFADDTEST_H_ */
