#include "CODE1Test.h"

#include "../src/extern.h"         /* contains global "extern" declarations */

//----------------------------------------------------------------------------------
// 	00001000  3400                      11     MOVE.W D0,D2
TEST_F(CODE1Test,TestMOVERR) {
	inst = 0x3400;
	D[0] = 0xa5a5;
	D[2] = 0x0000;
	MOVE();
	EXPECT_EQ(D[2], 0xa5a5) << "MOV R->R";
}

//----------------------------------------------------------------------------------
// 00001002  3080                      12     MOVE.W D0,(A0)
TEST_F(CODE1Test,TestMOVERIR) {
	inst = 0x3080;
	D[0] = 0xa5b6;
	A[0] = 0x0008;
	MOVE();
	uint32_t memloc = 8;
	uint32_t temp = memory->memory[memloc] & BYTE_MASK;
	temp = (temp << 8) | (memory->memory[memloc + 1] & BYTE_MASK);
	EXPECT_EQ( temp , 0xa5b6) << "MOVE.W R->(A)";
}
//----------------------------------------------------------------------------------
// 00001004  31C0 1234                 13     MOVE.W D0,$1234
TEST_F(CODE1Test,TestMOVERMem) {
	inst = 0x31C0;
	D[0] = 0xa5b6;
	PC = 0;
	memory->memory[PC] = 0x31;
	memory->memory[PC+1] = 0xc0;
	memory->memory[PC+2] = 0x12;
	memory->memory[PC+3] = 0x34;
	PC = 2;
	MOVE();
	uint32_t memloc = 0x1234;
	uint32_t temp = memory->memory[memloc] & BYTE_MASK;
	temp = (temp << 8) | (memory->memory[memloc + 1] & BYTE_MASK);
	EXPECT_EQ( temp , 0xa5b6) << "MOVE.W R->$";
}
//----------------------------------------------------------------------------------
// 00001008  31FC 1234 4568            14     MOVE.W #$1234,$4568
TEST_F(CODE1Test,TestMOVEImmMem) {
	inst = 0x31FC;
	PC = 0;
	memory->memory[PC] = 0x31;
	memory->memory[PC+1] = 0xfc;
	memory->memory[PC+2] = 0x12;
	memory->memory[PC+3] = 0x34;
	memory->memory[PC+4] = 0x45;
	memory->memory[PC+5] = 0x68;
	PC = 2;
	MOVE();
	uint32_t memloc = 0x4568;
	uint32_t temp = memory->memory[memloc] & BYTE_MASK;
	temp = (temp << 8) | (memory->memory[memloc + 1] & BYTE_MASK);
	EXPECT_EQ( temp , 0x1234) << "MOVE.W #->$";
}
//----------------------------------------------------------------------------------
// 0000100E  33F8 1234 00008000        15     MOVE.W $1234,$8000
TEST_F(CODE1Test,TestMOVEMemMem) {
	inst = 0x33F8;
	PC = 0;
	memory->memory[PC] = 0x33;
	memory->memory[PC+1] = 0xf8;
	memory->memory[PC+2] = 0x12;
	memory->memory[PC+3] = 0x34;
	memory->memory[PC+4] = 0x00;
	memory->memory[PC+5] = 0x00;
	memory->memory[PC+6] = 0x80;
	memory->memory[PC+7] = 0x00;
	uint32_t loc = 0x1234;
	memory->memory[loc] = 0x12;
	memory->memory[loc+1] = 0x34;
	PC = 2;
	MOVE();
	uint32_t memloc = 0x8000;
	uint32_t temp = memory->memory[memloc] & BYTE_MASK;
	temp = (temp << 8) | (memory->memory[memloc + 1] & BYTE_MASK);
	EXPECT_EQ( temp , 0x1234) << "MOVE.W $->$";
}
