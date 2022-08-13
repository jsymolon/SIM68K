#include "UTILS_effaddTest.h"
#include "../src/extern.h"         /* contains global "extern" declarations */

//----------------------------------------------------------------------------------
// test effaddr coding, position bit 0
TEST_F(UTILS_effaddTest,TestEffAddr1) {
   UTILS u;
   // take care of the mode = 7
   EXPECT_EQ(u.eff_addr_code(0x00000001, 0) , 0);
   EXPECT_EQ(u.eff_addr_code(0x00000009, 0) , 1);
   EXPECT_EQ(u.eff_addr_code(0x00000011, 0) , 2);
   EXPECT_EQ(u.eff_addr_code(0x00000019, 0) , 3);
   EXPECT_EQ(u.eff_addr_code(0x00000021, 0) , 4);
   EXPECT_EQ(u.eff_addr_code(0x00000029, 0) , 5);
   EXPECT_EQ(u.eff_addr_code(0x00000031, 0) , 6);
   // once mode > 6, "reg" field is used for timing
   EXPECT_EQ(u.eff_addr_code(0x00000007, 0) , 0);
   EXPECT_EQ(u.eff_addr_code(0x0000000f, 0) , 1);
   EXPECT_EQ(u.eff_addr_code(0x00000017, 0) , 2);
   EXPECT_EQ(u.eff_addr_code(0x0000001f, 0) , 3);
   EXPECT_EQ(u.eff_addr_code(0x00000027, 0) , 4);
   EXPECT_EQ(u.eff_addr_code(0x0000002f, 0) , 5);
   EXPECT_EQ(u.eff_addr_code(0x00000037, 0) , 6);
   EXPECT_EQ(u.eff_addr_code(0x0000003f, 0) , 12);
}

//----------------------------------------------------------------------------------
// test effaddr coding, position bit 6 "MOVE"
TEST_F(UTILS_effaddTest,TestEffAddr2) {
	   UTILS u;
	   // take care of the mode
	   EXPECT_EQ(u.eff_addr_code(0x000001c0, 6) , 7);
	   EXPECT_EQ(u.eff_addr_code(0x000003c0, 6) , 8);
	   EXPECT_EQ(u.eff_addr_code(0x000005c0, 6) , 9);
	   EXPECT_EQ(u.eff_addr_code(0x000007c0, 6) , 10);
	   EXPECT_EQ(u.eff_addr_code(0x000009c0, 6) , 11);
	   EXPECT_EQ(u.eff_addr_code(0x00000bc0, 6) , 12);
	   EXPECT_EQ(u.eff_addr_code(0x00000dc0, 6) , 12);
	   EXPECT_EQ(u.eff_addr_code(0x00000fc0, 6) , 12);
	   // once mode > 6, "reg" field is used for timing
	   EXPECT_EQ(u.eff_addr_code(0x00000000, 6) , 0);
	   EXPECT_EQ(u.eff_addr_code(0x00000040, 6) , 1);
	   EXPECT_EQ(u.eff_addr_code(0x00000080, 6) , 2);
	   EXPECT_EQ(u.eff_addr_code(0x000000c0, 6) , 3);
	   EXPECT_EQ(u.eff_addr_code(0x00000100, 6) , 4);
	   EXPECT_EQ(u.eff_addr_code(0x00000140, 6) , 5);
	   EXPECT_EQ(u.eff_addr_code(0x00000180, 6) , 6);
	   EXPECT_EQ(u.eff_addr_code(0x000001c0, 6) , 7);
}
