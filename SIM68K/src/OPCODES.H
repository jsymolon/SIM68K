/***************************** 68000 SIMULATOR ****************************

 File Name: OPCODES.H
 Version: 1.0

 This file contains opcode values to decode 68000 instructions.  It is
 included in the file "run.c"

 ***************************************************************************/

extern int ORI(), ORI_TO_CCR(), ORI_TO_SR(), BIT_OP(), MOVEP(), ANDI(),
		ANDI_TO_CCR(), ANDI_TO_SR(), SUBI(), ADDI(), EORI(), EORI_TO_CCR(),
		EORI_TO_SR(), CMPI(), MOVEA(), MOVE(), NEGX(), MOVE_FR_SR(), CHK(),
		LEA(), CLR(), NEG(), MOVE_TO_CCR(), NOT(), MOVE_TO_SR(), NBCD(), SWAP(),
		PEA(), EXT(), MOVEM(), TST(), TAS(), ILLEGAL(), TRAP(), LINK(), UNLK(),
		MOVE_USP(), RESET(), NOP(), STOP(), RTE(), RTS(), TRAPV(), RTR(), JSR(),
		JMP(), ADDQ(), SCC(), DBCC(), SUBQ(), BCC(), BRA(), BSR(), MOVEQ(),
		OR(), DIVU(), SBCD(), DIVS(), SUB(), SUBA(), SUBX(), CMP(), CMPA(),
		EOR(), CMPM(), AND(), MULU(), ABCD(), EXG(), MULS(), ADD(), ADDA(),
		ADDX(), BIT_FIELD(), SHIFT_ROT(), LINE1010(), LINE1111();

extern int offsets[];

extern struct inst_rec {
	int mask;
	int val;
	char name[13];
} inst_arr[];

extern int (*names[])();
