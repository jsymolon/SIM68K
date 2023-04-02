#include "CODE3Test.h"

#include "../src/extern.h"         /* contains global "extern" declarations */

//----------------------------------------------------------------------------------
//00001000  D078 2000                 11      add.w $2000,d0
TEST_F(CODE3Test,TestADD) {
	inst = 0xd078;
	PC = 0;
	memory->memory[PC] = 0xd0;
	memory->memory[PC + 1] = 0x78;
	memory->memory[PC + 2] = 0x20;
	memory->memory[PC + 3] = 0x00;
	PC = 2;
	memory->memory[0x2000] = 0x01;
	memory->memory[0x2000] = 0x01;
	D[0] = 0x1234;
	ADD();
	EXPECT_EQ(D[0], 0x1334) << "ADD $->D";
}
//----------------------------------------------------------------------------------
//00001004  D2FC 0100                 12      adda.w #256,a1
TEST_F(CODE3Test,TestADDA) {
	inst = 0xd2fc;
	PC = 0;
	memory->memory[PC] = 0xd2;
	memory->memory[PC + 1] = 0xfc;
	memory->memory[PC + 2] = 0x01;
	memory->memory[PC + 3] = 0x00;
	PC = 2;
	ADDA();
	EXPECT_EQ(A[1], 272) << "ADDA #->A";
}
//----------------------------------------------------------------------------------
//00001008  0641 0100                 13      addi.w #256,d1
TEST_F(CODE3Test,TestADDI) {
	inst = 0x0641;
	PC = 0;
	memory->memory[PC] = 0x06;
	memory->memory[PC + 1] = 0x41;
	memory->memory[PC + 2] = 0x01;
	memory->memory[PC + 3] = 0x00;
	PC = 2;
	ADDI();
	EXPECT_EQ(D[1], 4916) << "ADDI #->D";
}
//----------------------------------------------------------------------------------
//0000100C  5442                      14      addq.w #2,d2
TEST_F(CODE3Test,TestADDQ) {
	inst = 0x92fc;
	PC = 0;
	memory->memory[PC] = 0x92;
	memory->memory[PC + 1] = 0xfc;
	PC = 2;
	ADDQ();
	EXPECT_EQ(D[0], 4916) << "ADDQ #->D";
}
//----------------------------------------------------------------------------------
//0000100E  D541                      15      addx.w d1,d2
TEST_F(CODE3Test,TestADDX) {
	inst = 0xd541;
	PC = 0;
	memory->memory[PC] = 0xd5;
	memory->memory[PC + 1] = 0x41;
	PC = 2;
	ADDX();
	EXPECT_EQ(D[2], 47321) << "ADDX D->D";
}
//----------------------------------------------------------------------------------
//00001010  0440 0100                 16      sub.w  #256, d0
TEST_F(CODE3Test,TestSUB) {
	inst = 0x0440;
	PC = 0;
	memory->memory[PC] = 0x04;
	memory->memory[PC + 1] = 0x40;
	memory->memory[PC + 2] = 0x01;
	memory->memory[PC + 3] = 0x00;
	PC = 2;
	SUB();
	EXPECT_EQ(D[0], 4916) << "SUB #->D";
}
//----------------------------------------------------------------------------------
//00001014  92FC 0100                 17      suba.w #256, a1
TEST_F(CODE3Test,TestSUBA) {
	inst = 0x92fc;
	PC = 0;
	memory->memory[PC] = 0x92;
	memory->memory[PC + 1] = 0xfc;
	memory->memory[PC + 2] = 0x01;
	memory->memory[PC + 3] = 0x00;
	PC = 2;
	SUBA();
	EXPECT_EQ(A[1], 0x0010) << "SUBA #->a";
}
//----------------------------------------------------------------------------------
//00001018  0441 0100                 18      subi.w #256, d1
TEST_F(CODE3Test,TestSUBI) {
	inst = 0x0441;
	PC = 0;
	memory->memory[PC] = 0x04;
	memory->memory[PC + 1] = 0x41;
	memory->memory[PC + 2] = 0x01;
	memory->memory[PC + 3] = 0x00;
	PC = 2;
	SUBI();
	EXPECT_EQ(D[1], 4660) << "SUBI #->D";
}
//----------------------------------------------------------------------------------
//0000101C  5542                      19      subq.w #2,d2
TEST_F(CODE3Test,TestSUBQ) {
	inst = 0x5541;
	PC = 0;
	memory->memory[PC] = 0x55;
	memory->memory[PC + 1] = 0x41;
	PC = 2;
	SUBQ();
	EXPECT_EQ(D[2], 42405) << "SUBQ #->D";
}
//----------------------------------------------------------------------------------
//0000101E  9541                      20      subx.w d1,d2
TEST_F(CODE3Test,TestSUBX) {
	inst = 0x9541;
	PC = 0;
	memory->memory[PC] = 0x95;
	memory->memory[PC + 1] = 0x41;
	PC = 2;
	SUBX();
	EXPECT_EQ(D[2], 37747) << "SUBX D->D";
}
