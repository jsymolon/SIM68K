#include "CODE8Test.h"

#include "../src/extern.h"         /* contains global "extern" declarations */

//----------------------------------------------------------------------------------
//00001006  6500 0002                 13  l02:  bcs  l03
TEST_F(CODE8Test,TestBCC) {
	inst = 0x6500;
	PC = 0x1006;
	memory->memory[PC + 0] = 0x65;
	memory->memory[PC + 1] = 0x00;
	memory->memory[PC + 2] = 0x00;
	memory->memory[PC + 3] = 0x02;
	PC = PC + 2;
	BCC();
	EXPECT_EQ(PC, 0x100A) << "BCC";
}

//----------------------------------------------------------------------------------
//0000103E  55C8 0002                 28  l21:  dbcs  d0,l22
TEST_F(CODE8Test,TestDBCC) {
	inst = 0x55C8;
	PC = 0x103e;
	memory->memory[PC + 0] = 0x55;
	memory->memory[PC + 1] = 0xC8;
	memory->memory[PC + 2] = 0x00;
	memory->memory[PC + 3] = 0x02;
	PC = PC + 2;
	D[0] = 0xa5a5;
	DBCC();
	EXPECT_EQ(D[1], 0x00a5) << "DBCC";
}

//----------------------------------------------------------------------------------
//scc
TEST_F(CODE8Test,TestSCC) {
	inst = 0xC240;
	D[0] = 0xa5a5;
	D[1] = 0x00FF;
	SCC();
	EXPECT_EQ(D[1], 0x00ff) << "SCC";
}

//----------------------------------------------------------------------------------
//00001026  60F4                      27          bra     loop
TEST_F(CODE8Test,TestBRA) {
	inst = 0x60F4;
	PC = 0x1026;
	BRA();
	EXPECT_EQ(PC, 0xfffffff6) << "BRA";
}

//----------------------------------------------------------------------------------
//bsr
TEST_F(CODE8Test,TestBSR) {
	inst = 0xC240;
	D[0] = 0xa5a5;
	D[1] = 0x00FF;
	BSR();
	EXPECT_EQ(D[1], 0x00ff) << "BSR";
}

//----------------------------------------------------------------------------------
// 0000299C  4EF9 00002A30            258              jmp    ctxsw
TEST_F(CODE8Test,TestJMP) {
	inst = 0x4EF9;
	PC = 0x1000;
	memory->memory[PC + 0] = 0x4E;
	memory->memory[PC + 1] = 0xF9;
	memory->memory[PC + 2] = 0x00;
	memory->memory[PC + 3] = 0x00;
	memory->memory[PC + 4] = 0x2A;
	memory->memory[PC + 5] = 0x30;
	PC = PC + 2;
	JMP();
	EXPECT_EQ(PC, 0x0A8C) << "JMP";
}

//----------------------------------------------------------------------------------
// 00002996  4EB9 00002C34            257              jsr    segment7
TEST_F(CODE8Test,TestJSR) {
	inst = 0x4EB9;
	PC = 0x1000;
	memory->memory[PC + 0] = 0x4E;
	memory->memory[PC + 1] = 0xB9;
	memory->memory[PC + 2] = 0x00;
	memory->memory[PC + 3] = 0x00;
	memory->memory[PC + 4] = 0x2C;
	memory->memory[PC + 5] = 0x34;
	PC = PC + 2;
	JSR();
	EXPECT_EQ(PC, 0x0B0D) << "JSR";
}

//----------------------------------------------------------------------------------
//0000298C  4E73                     251              rte
TEST_F(CODE8Test,TestRTE) {
	inst = 0x4E73;
//	RTE();
//	EXPECT_EQ(D[1], 0x00a5) << "RTE";
}

//----------------------------------------------------------------------------------
//rtr
TEST_F(CODE8Test,TestRTR) {
	inst = 0xC240;
	D[0] = 0xa5a5;
	D[1] = 0x00FF;
//	RTR();
//	EXPECT_EQ(D[1], 0x00a5) << "RTR";
}

//----------------------------------------------------------------------------------
//00002A0E  4E75                     309              rts
TEST_F(CODE8Test,TestRTS) {
	inst = 0x4E75;
	// push return address
	A[7] = 0x1000;
	A[8] = 0x1000; // Supervisor
	A[utils->a_reg(7)] -= 4;
	utils->put((uint32_t*) &memory->memory[A[utils->a_reg(7)]], PC, LONG_MASK);
	RTS();
	EXPECT_EQ(PC, 0x0B0D) << "RTS";
}

//----------------------------------------------------------------------------------
//nop
TEST_F(CODE8Test,TestNOP) {
	inst = 0xC240;
	D[0] = 0xa5a5;
	D[1] = 0x00FF;
	NOP();
//	EXPECT_EQ(D[1], 0x00ff) << "NOP";
}
