#include "CODE9Test.h"

#include "../src/extern.h"         /* contains global "extern" declarations */

//----------------------------------------------------------------------------------
//
TEST_F(CODE9Test,TestCHK) {
	inst = 0x6500;
	PC = 0x1006;
	memory->memory[PC + 0] = 0x65;
	memory->memory[PC + 1] = 0x00;
	memory->memory[PC + 2] = 0x00;
	memory->memory[PC + 3] = 0x02;
	PC = PC + 2;
	CHK();
	//EXPECT_EQ(PC, 0x100A) << "CHK";
	//TODO: CHK
}
//----------------------------------------------------------------------------------
//
TEST_F(CODE9Test,TestILLEGAL) {
	inst = 0x6500;
	PC = 0x1006;
	memory->memory[PC + 0] = 0x65;
	memory->memory[PC + 1] = 0x00;
	memory->memory[PC + 2] = 0x00;
	memory->memory[PC + 3] = 0x02;
	PC = PC + 2;
	ILLEGAL();
	//EXPECT_EQ(PC, 0x100A) << "ILLEGAL";
	//TODO: ILLEGAL
}

//----------------------------------------------------------------------------------
//
TEST_F(CODE9Test,TestRESET) {
	inst = 0x6500;
	PC = 0x1006;
	memory->memory[PC + 0] = 0x65;
	memory->memory[PC + 1] = 0x00;
	memory->memory[PC + 2] = 0x00;
	memory->memory[PC + 3] = 0x02;
	PC = PC + 2;
	RESET();
	//EXPECT_EQ(PC, 0x100A) << "RESET";
	//TODO: RESET
}

//----------------------------------------------------------------------------------
//
TEST_F(CODE9Test,TestSTOP) {
	inst = 0x6500;
	PC = 0x1006;
	memory->memory[PC + 0] = 0x65;
	memory->memory[PC + 1] = 0x00;
	memory->memory[PC + 2] = 0x00;
	memory->memory[PC + 3] = 0x02;
	PC = PC + 2;
	STOP();
	//EXPECT_EQ(PC, 0x100A) << "STOP";
	//TODO: STOP
}

//----------------------------------------------------------------------------------
//
TEST_F(CODE9Test,TestTRAP) {
	inst = 0x6500;
	PC = 0x1006;
	memory->memory[PC + 0] = 0x65;
	memory->memory[PC + 1] = 0x00;
	memory->memory[PC + 2] = 0x00;
	memory->memory[PC + 3] = 0x02;
	PC = PC + 2;
	TRAP();
	//EXPECT_EQ(PC, 0x100A) << "TRAP";
	//TODO: TRAP
}

//----------------------------------------------------------------------------------
//
TEST_F(CODE9Test,TestTRAPV) {
	inst = 0x6500;
	PC = 0x1006;
	memory->memory[PC + 0] = 0x65;
	memory->memory[PC + 1] = 0x00;
	memory->memory[PC + 2] = 0x00;
	memory->memory[PC + 3] = 0x02;
	PC = PC + 2;
	TRAPV();
	//EXPECT_EQ(PC, 0x100A) << "TRAPV";
	//TODO: TRAPV
}

//----------------------------------------------------------------------------------
//
TEST_F(CODE9Test,TestLINE1010) {
	inst = 0x6500;
	PC = 0x1006;
	memory->memory[PC + 0] = 0x65;
	memory->memory[PC + 1] = 0x00;
	memory->memory[PC + 2] = 0x00;
	memory->memory[PC + 3] = 0x02;
	PC = PC + 2;
	LINE1010();
	//EXPECT_EQ(PC, 0x100A) << "LINE1010";
	//TODO: LINE1010
}

//----------------------------------------------------------------------------------
//
TEST_F(CODE9Test,TestLINE1111) {
	inst = 0x6500;
	PC = 0x1006;
	memory->memory[PC + 0] = 0x65;
	memory->memory[PC + 1] = 0x00;
	memory->memory[PC + 2] = 0x00;
	memory->memory[PC + 3] = 0x02;
	PC = PC + 2;
	LINE1111();
	//EXPECT_EQ(PC, 0x100A) << "LINE1111";
	//TODO: LINE1111
}
