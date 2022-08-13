#include "CODE2Test.h"

#include "../src/extern.h"         /* contains global "extern" declarations */

//----------------------------------------------------------------------------------
//C141      EXG     D0, D1
TEST_F(CODE2Test,TestEXG) {
	inst = 0xc141;
	D[0] = 0x1234;
	D[1] = 0x4567;
	EXG();
	EXPECT_EQ(D[0], 0x4567) << "EXG D->D";
}
//----------------------------------------------------------------------------------
//0000101A  47EA 0005                 19      LEA     5(A2), A3
TEST_F(CODE2Test,TestLEA) {
	inst = 0x47d2;
	PC = 0;
	memory->memory[PC] = 0x47;
	memory->memory[PC+1] = 0xea;
	memory->memory[PC+2] = 0x00;
	memory->memory[PC+3] = 0x05;
	PC = 2;
	A[2] = 0x0010;
	LEA();
	EXPECT_EQ(A[3], 0x0004) << "LEA (A)->A";
}
//----------------------------------------------------------------------------------
//4852      PEA     (A2)
TEST_F(CODE2Test,TestPEA) {
	inst = 0x4852;
	A[2] = 0x0010;
	uint32_t loc = 0x10;
	memory->memory[loc] = 0xa5;
	memory->memory[loc+1] = 0xa5;
	A[7] = 0x1004;
	PC = 0x6969;
	PEA();
	uint32_t memloc = 0x1002;
	uint32_t temp = memory->memory[memloc] & BYTE_MASK;
	temp = (temp << 8) | (memory->memory[memloc + 1] & BYTE_MASK);
	EXPECT_EQ(temp, 0x0004) << "PEA (A)";
}
//----------------------------------------------------------------------------------
//SP-4 ->SP; An->(SP); SP->An; SP+dn->SP
//4E51 000C LINK    A1, #12
TEST_F(CODE2Test,TestLINK) {
	inst = 0x3400;
	PC = 0;
	memory->memory[PC] = 0x4e;
	memory->memory[PC+1] = 0x51;
	memory->memory[PC+2] = 0x00;
	memory->memory[PC+3] = 0x0c;
	PC = 2;
	A[7] = 0x1020;
	A[1] = 0x0010;
	LINK();
	EXPECT_EQ(A[1], 0x0010) << "LINK A, #12";
	EXPECT_EQ(A[7], 0x1028) << "LINK SP, #12";
}
//----------------------------------------------------------------------------------
//4E59      UNLK    A1
TEST_F(CODE2Test,TestUNLK) {
	inst = 0x3400;
	D[0] = 0xa5a5;
	D[2] = 0x0000;
	MOVE();
	EXPECT_EQ(D[2], 0xa5a5) << "UNLK A";
}
