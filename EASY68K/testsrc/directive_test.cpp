#include "gtest/gtest.h"
#include "directive.h"

TEST(org, orgtest) {
      int c;
      EXPECT_EQ(0, c);
}

int main(int argc, char **argv) {
      ::testing::InitGoogleTest(&argc, argv);
      return RUN_ALL_TESTS();
}
