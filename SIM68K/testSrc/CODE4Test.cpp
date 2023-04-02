#include "CODE4Test.h"

#include "../src/extern.h"         /* contains global "extern" declarations */

//----------------------------------------------------------------------------------
//00001000  81C1                      11          divs.w d1,d0   d1/d0
TEST_F(CODE4Test,TestDIVS) {
	inst = 0x81C1;
	PC = 0;
	D[1] = 0xFFFF8001;
	D[0] = 0x0002;
	DIVS();
	EXPECT_EQ(D[0], 0x00020000) << "DIVS";
}
//----------------------------------------------------------------------------------
//00001002  80C1                      12             divu.w d1,d0
TEST_F(CODE4Test,TestDIVU) {
	inst = 0x80C1;
	PC = 0;
	D[1] = 0xFFFF8001;
	D[0] = 0x0002;
	DIVU();
	EXPECT_EQ(D[0], 0x00020000) << "DIVU";
}

//----------------------------------------------------------------------------------
//00001004  C1C1                      13             muls.w d1,d0
TEST_F(CODE4Test,TestMULS) {
	inst = 0xC1C1;
	PC = 0;
	D[1] = 0xffff8001;
	D[0] = 0x0002;
	MULS();
	EXPECT_EQ(D[0], 0xffff0002) << "MULS";
}

//----------------------------------------------------------------------------------
//00001006  C0C1                      14             mulu.w d1,d0
TEST_F(CODE4Test,TestMULU) {
	inst = 0xC0C1;
	PC = 0;
	D[1] = 0xffff8001;
	D[0] = 0x0002;
	MULU();
	EXPECT_EQ(D[0], 0x00010002) << "MULU";
}

//----------------------------------------------------------------------------------
//00001008  4441                      15             neg d1
TEST_F(CODE4Test,TestNEG) {
	inst = 0x4441;
	PC = 0;
	D[1] = 0xffff8001;
	NEG();
	EXPECT_EQ(D[0], 0x00010002) << "NEG";
}

//----------------------------------------------------------------------------------
//0000100A  4041                      16             negx d1
TEST_F(CODE4Test,TestNEGX) {
	inst = 0x4041;
	PC = 0;
	D[1] = 0xffff8001;
	NEGX();
	EXPECT_EQ(D[0], 0x00010002) << "NEGX";
}

//----------------------------------------------------------------------------------
//0000100C  B041                      17             cmp.w d1,d0
TEST_F(CODE4Test,TestCMP) {
	inst = 0xB041;
	PC = 0;
	D[0] = 0x00010001;
	D[1] = 0x00010001;
	CMP();
	EXPECT_EQ(SR, 0x0014) << "CMP";
}

//----------------------------------------------------------------------------------
//0000100E  B0C9                      18             cmpa a1,a0
TEST_F(CODE4Test,TestCMPA) {
	inst = 0xB0C9;
	PC = 0;
	A[0] = 0x00010001;
	A[1] = 0x00010001;
	CMPA();
	EXPECT_EQ(SR, 0x0010) << "CMPA";
}

//----------------------------------------------------------------------------------
//00001010  0C40 00FF                 19             cmpi.w #255,d0
TEST_F(CODE4Test,TestCMPI) {
	inst = 0x0C40;
	PC = 0;
	D[0] = 0x000000FF;
	CMPI();
	EXPECT_EQ(SR, 0x0011) << "CMPI";
}

//----------------------------------------------------------------------------------
//00001014  B149                      20             cmpm (a1)+,(a0)+
TEST_F(CODE4Test,TestCMPM) {
	inst = 0xB149;
	PC = 0;
	memory->memory[PC] = 0x00;
	memory->memory[PC + 1] = 0x10;
	memory->memory[PC + 2] = 0x00;
	memory->memory[PC + 3] = 0x10;
	A[0] = 0x00000000;
	memory->memory[PC + 4] = 0x00;
	memory->memory[PC + 5] = 0x10;
	memory->memory[PC + 6] = 0x00;
	memory->memory[PC + 7] = 0x10;
	A[1] = 0x00000004;
	CMPM();
	EXPECT_EQ(SR, 0x0014) << "CMPM";
}

//----------------------------------------------------------------------------------
//00001016  4A40                      21             tst d0
TEST_F(CODE4Test,TestTST) {
	inst = 0x4A40;
	PC = 0;
	D[0] = 0x000000FF;
	TST();
	EXPECT_EQ(SR, 0x0010) << "TST";
}

//----------------------------------------------------------------------------------
//00001018  4250                      22             clr (a0)
TEST_F(CODE4Test,TestCLR) {
	inst = 0x4250;
	PC = 0;
	D[0] = 0xffffffff;
	CLR();
	EXPECT_EQ(D[0], 0xFFFFFFFF) << "CLR";
}

//----------------------------------------------------------------------------------
//0000101A  4880                      23             ext.w d0
TEST_F(CODE4Test,TestEXT) {
	inst = 0x4880;
	PC = 0;
	D[0] = 0x0000FFFF;
	EXT();
	EXPECT_EQ(D[0], 0x0000FFFF) << "EXT";
}
