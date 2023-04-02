#include "CODE5Test.h"

#include "../src/extern.h"         /* contains global "extern" declarations */

//----------------------------------------------------------------------------------
//00001034  C101                      31          abcd d1,d0
TEST_F(CODE5Test,TestABCD) {
	inst = 0xC101;
	D[0] = 0xa5a5;
	D[2] = 0x0000;
	ABCD();
	EXPECT_EQ(D[0], 0xa507) << "ABCD";
}

//----------------------------------------------------------------------------------
//00001036  8101                      32          sbcd d1,d0
TEST_F(CODE5Test,TestSBCD) {
	inst = 0x8101;
	D[0] = 0xa5a5;
	D[2] = 0x0000;
	MOVE();
	EXPECT_EQ(D[0], 0xa5a5) << "SBCD";
}

//----------------------------------------------------------------------------------
//00001038  4800                      33          nbcd d0
TEST_F(CODE5Test,TestNBCD) {
	inst = 0x4800;
	D[0] = 0xa5a5;
	D[2] = 0x0000;
	MOVE();
	EXPECT_EQ(D[0], 0xa5a5) << "NBCD";
}
