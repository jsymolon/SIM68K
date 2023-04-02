#include "CODE6Test.h"

#include "../src/extern.h"         /* contains global "extern" declarations */

//----------------------------------------------------------------------------------
//00001008  C240                      13      and.w d0,d1
TEST_F(CODE6Test,TestAND) {
	inst = 0xC240;
	D[0] = 0xa5a5;
	D[1] = 0x00FF;
	AND();
	EXPECT_EQ(D[1], 0x00a5) << "AND";
}

//----------------------------------------------------------------------------------
//0000100A  0200 00FF                 14      andi.b #$f0, d0
TEST_F(CODE6Test,TestANDI) {
	inst = 0x0200;
	PC = 0;
	memory->memory[PC] = 0x02;
	memory->memory[PC + 1] = 0x00;
	memory->memory[PC + 2] = 0x00;
	memory->memory[PC + 3] = 0xf0;
	PC = 2;
	D[0] = 0xa5a5;
	ANDI();
	EXPECT_EQ(D[0], 0xa5a0) << "ANDI";
}

//----------------------------------------------------------------------------------
//0000100E  023C 00FE                 15      andi #$fe,ccr
TEST_F(CODE6Test,TestANDI_TO_CCR) {
	inst = 0x023C;
	PC = 0;
	memory->memory[PC] = 0x02;
	memory->memory[PC + 1] = 0x3c;
	memory->memory[PC + 2] = 0x00;
	memory->memory[PC + 3] = 0xfe;
	PC = 2;
	SR = 0x0003;
	ANDI_TO_CCR();
	EXPECT_EQ(SR, 0x002) << "ANDI_TO_CCR";
}

//----------------------------------------------------------------------------------
//00001012  027C 7FFE                 16      andi.w #$7ffe,sr
TEST_F(CODE6Test,TestANDI_TO_SR) {
	inst = 0x027c;
	PC = 0;
	memory->memory[PC] = 0x02;
	memory->memory[PC + 1] = 0x7c;
	memory->memory[PC + 2] = 0x7f;
	memory->memory[PC + 3] = 0xfe;
	PC = 2;
	SR = 0x7ff6;
	ANDI_TO_SR();
	EXPECT_EQ(D[0], 0xa5a0) << "ANDI_TO_SR";
}

//----------------------------------------------------------------------------------
//00001016  8240                      17      or.w d0,d1
TEST_F(CODE6Test,TestOR) {
	inst = 0x8240;
	D[0] = 0xa5a5;
	D[1] = 0x000f;
	OR();
	EXPECT_EQ(D[0], 0xa5a5) << "OR";
}

//----------------------------------------------------------------------------------
//00001018  0040 00FF                 18      ori.w #$00ff, d0
TEST_F(CODE6Test,TestORI) {
	inst = 0x0040;
	PC = 0;
	memory->memory[PC] = 0x00;
	memory->memory[PC + 1] = 0x40;
	memory->memory[PC + 2] = 0x00;
	memory->memory[PC + 3] = 0xff;
	PC = 2;
	D[0] = 0x00a5;
	ORI();
	EXPECT_EQ(D[0], 0xff) << "ORI";
}

//----------------------------------------------------------------------------------
//0000101C  003C 0001                 19      ori.b #$01,ccr
TEST_F(CODE6Test,TestORI_TO_CCR) {
	inst = 0x003c;
	PC = 0;
	memory->memory[PC] = 0x00;
	memory->memory[PC + 1] = 0x3c;
	memory->memory[PC + 2] = 0x00;
	memory->memory[PC + 3] = 0x01;
	PC = 2;
	SR = 0x7f7f;
	ORI_TO_CCR();
	EXPECT_EQ(D[0], 0xff) << "ORI_TO_CCR";
}

//----------------------------------------------------------------------------------
//00001020  007C 8001                 20      ori.w #$8001,sr
TEST_F(CODE6Test,TestORI_TO_SR) {
	inst = 0x007c;
	PC = 0;
	memory->memory[PC] = 0xC1;
	memory->memory[PC + 1] = 0x01;
	memory->memory[PC + 2] = 0x00;
	memory->memory[PC + 3] = 0x05;
	PC = 2;
	D[0] = 0xa5a5;
	D[2] = 0x0000;
	ORI_TO_SR();
	EXPECT_EQ(D[0], 0xa5a5) << "ORI_TO_SR";
}

//----------------------------------------------------------------------------------
//00001024  B141                      21      eor.w d0,d1
TEST_F(CODE6Test,TestEOR) {
	inst = 0xb141;
	D[0] = 0xa5a5;
	D[2] = 0x00ff;
	EOR();
	EXPECT_EQ(D[0], 0xa5a5) << "EOR";
}

//----------------------------------------------------------------------------------
//00001026  0A40 00FF                 22      eori.w #$00ff,d0
TEST_F(CODE6Test,TestEORI) {
	inst = 0x0a40;
	PC = 0;
	memory->memory[PC] = 0x0a;
	memory->memory[PC + 1] = 0x40;
	memory->memory[PC + 2] = 0x00;
	memory->memory[PC + 3] = 0xff;
	PC = 2;
	D[0] = 0xa5a5;
	EORI();
	EXPECT_EQ(D[0], 0xa55a) << "EORI";
}

//----------------------------------------------------------------------------------
//0000102A  0A3C 0001                 23      eori.b #$01,ccr
TEST_F(CODE6Test,TestEORI_TO_CCR) {
	inst = 0x0a3c;
	PC = 0;
	memory->memory[PC] = 0x0a;
	memory->memory[PC + 1] = 0x3c;
	memory->memory[PC + 2] = 0x00;
	memory->memory[PC + 3] = 0x01;
	PC = 2;
	SR = 0x7fff;
	EORI_TO_CCR();
	EXPECT_EQ(D[0], 0xa55a) << "EORI_TO_CC R";
}

//----------------------------------------------------------------------------------
//0000102E  0A7C 8001                 24      eori.w #$8001,sr
TEST_F(CODE6Test,TestEORI_TO_SR) {
	inst = 0x0a7c;
	PC = 0;
	memory->memory[PC] = 0x0a;
	memory->memory[PC + 1] = 0x7c;
	memory->memory[PC + 2] = 0x80;
	memory->memory[PC + 3] = 0x01;
	PC = 2;
	SR = 0x7fff;
	EORI_TO_SR();
	EXPECT_EQ(D[0], 0xa55a) << "EORI_TO_SR";
}

//----------------------------------------------------------------------------------
//00001032  4600                      25      not.w d0
TEST_F(CODE6Test,TestNOT) {
	inst = 0x4640;
	PC = 0;
	memory->memory[PC] = 0x46;
	memory->memory[PC + 1] = 0x00;
	PC = 2;
	D[0] = 0xa5a5;
	NOT();
	EXPECT_EQ(D[0], 0x5a5a) << "NOT";
}

