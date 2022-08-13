//---------------------------------------------------------------------------
//   Author: Charles Kelly
//           www.easy68k.com
//---------------------------------------------------------------------------
#ifndef DEF_H_
#define DEF_H_
#include <cstdint>

/***************************** 68000 SIMULATOR ****************************
 File Name: DEF.H
 This file contains definitions used in the simulator source files.
 ***************************************************************************/

// version info
const char TITLE[] = "EASy68K Simulator v5.20.0"; // ***** change both *****
const uint32_t VERSION = 0x00052001;    // ***** change both *****

// memory map types (bit flags which may be combined with OR logic)
enum maptype {
	Invalid = (1u << 0), Protected = (1u << 1), Read = (1u << 2),
	// no << 3
	Rom = (1u << 4)
};

// status register bitmasks

const uint32_t bit_1 = 0x0001;
const uint32_t bit_2 = 0x0002;
const uint32_t bit_3 = 0x0004;
const uint32_t bit_4 = 0x0008;
const uint32_t bit_5 = 0x0010;
const uint32_t bit_6 = 0x0020;
const uint32_t bit_7 = 0x0040;
const uint32_t bit_8 = 0x0080;
const uint32_t bit_9 = 0x0100;
const uint32_t bit_10 = 0x0200;
const uint32_t bit_11 = 0x0400;
const uint32_t bit_12 = 0x0800;

const uint32_t cbit = 0x0001;
const uint32_t vbit = 0x0002;
const uint32_t zbit = 0x0004;
const uint32_t nbit = 0x0008;
const uint32_t xbit = 0x0010;
const uint32_t intmsk = 0x0700;       // three bits
const uint32_t sbit = 0x2000;
const uint32_t tbit = 0x8000;

// misc
const uint32_t MEMSIZE = 0x01000000;   // 16 Meg address space
const uint32_t ADDRMASK = 0x00ffffff;

const uint32_t BYTE_MASK = 0xff;         // byte mask
const uint32_t WORD_MASK = 0xffff;       // word mask
const uint32_t LONG_MASK = 0xffffffff;   // uint32_t mask

const uint32_t D_REGS = 8;            // number of D registers
const uint32_t A_REGS = 9;            // number of A registers

// Possible addressing modes permitted by an instruction
// Each bit represents a different addressing mode.
// For example CONTROL_ADDR = 0x07e4 which means the following addressing
// modes are permitted.
// Imm d[PC,Xi] d[PC] Abs.L Abs.W d[An,Xi] d[An] -[An] [An]+ [An] An Dn
//  0      1      1     1     1      1       1     0     0     1   0  0
const uint32_t DATA_ADDR = 0x0ffd;
const uint32_t MEMORY_ADDR = 0x0ffc;
const uint32_t CONTROL_ADDR = 0x07e4;
const uint32_t ALTERABLE_ADDR = 0x01ff;
const uint32_t ALL_ADDR = 0x0fff;
const uint32_t DATA_ALT_ADDR = (DATA_ADDR & ALTERABLE_ADDR);
const uint32_t MEM_ALT_ADDR = (MEMORY_ADDR & ALTERABLE_ADDR);
const uint32_t CONT_ALT_ADDR = (CONTROL_ADDR & ALTERABLE_ADDR);

/* these are the instruction return codes */

const uint32_t SUCCESS = 0x0000;
const uint32_t BAD_INST = 0x0001;
const uint32_t NO_PRIVILEGE = 0x0002;
const uint32_t CHK_EXCEPTION = 0x0003;
//const uint32_t ILLEGAL_TRAP		= 0x0004;
const uint32_t STOP_TRAP = 0x0005;
const uint32_t TRAPV_TRAP = 0x0006;
const uint32_t TRAP_TRAP = 0x0007;
const uint32_t DIV_BY_ZERO = 0x0008;
const uint32_t USER_BREAK = 0x0009;
const uint32_t BUS_ERROR = 0x000A;
const uint32_t ADDR_ERROR = 0x000B;
const uint32_t LINE_1010 = 0x000C;
const uint32_t LINE_1111 = 0x000D;
const uint32_t TRACE_EXCEPTION = 0x000E;
const uint32_t ROM_MAP = 0x000F;
const uint32_t FAILURE = 0x1111;	// general failure

// these are the cases for condition code setting

const uint32_t N_A = 0;
const uint32_t GEN = 1;
const uint32_t ZER = 2;
const uint32_t UND = 3;
const uint32_t CASE_1 = 4;
const uint32_t CASE_2 = 5;
const uint32_t CASE_3 = 6;
const uint32_t CASE_4 = 7;
const uint32_t CASE_5 = 8;
const uint32_t CASE_6 = 9;
const uint32_t CASE_7 = 10;
const uint32_t CASE_8 = 11;
const uint32_t CASE_9 = 12;

// these are used in run.c

const uint32_t MODE_MASK = 0x0038;
const uint32_t REG_MASK = 0x0007;
const uint32_t FIRST_FOUR = 0xf000;

const uint32_t READ = 0xffff;
const uint32_t WRITE = 0x0000;

// conditions for BCC, DBCC, and SCC

const uint32_t COND_T = 0x00;
const uint32_t COND_F = 0x01;
const uint32_t COND_HI = 0x02;
const uint32_t COND_LS = 0x03;
const uint32_t COND_CC = 0x04;
const uint32_t COND_CS = 0x05;
const uint32_t COND_NE = 0x06;
const uint32_t COND_EQ = 0x07;
const uint32_t COND_VC = 0x08;
const uint32_t COND_VS = 0x09;
const uint32_t COND_PL = 0x0a;
const uint32_t COND_MI = 0x0b;
const uint32_t COND_GE = 0x0c;
const uint32_t COND_LT = 0x0d;
const uint32_t COND_GT = 0x0e;
const uint32_t COND_LE = 0x0f;

// file handling error codes
const short F_SUCCESS = 0;
const short F_EOF = 1;
const short F_ERROR = 2;
const short F_READONLY = 3;

const int MAXFILES = 8;         // maximun files that may be open at one time

struct FileStruct {
	FILE *fp;                     // file pointer
	char name[256];               // file name
};

// simulator log types
const uint32_t DISABLED = 0;
const uint32_t INSTRUCTION = 1;
const uint32_t REGISTERS = 2;
const uint32_t INST_REG_MEM = 3;
const uint32_t TEXTONLY = 1;

//////////////////////////////////
// DEBUG / Breakpoint definitions
//////////////////////////////////

const uint32_t MAX_BPOINTS = 100;
const uint32_t MAX_BP_EXPR = 50;
const uint32_t MAX_LB_NODES = 10;

// Define logical operator types
const uint32_t AND_OP = 0;
const uint32_t OR_OP = 1;

const uint32_t LPAREN = MAX_BPOINTS + OR_OP + 1;
const uint32_t RPAREN = LPAREN + 1;

// BPoint IDs are shared between PC/Reg and ADDR breakpoints.
// This constant is used to jump to the ADDR range.
// (It's ok to have unused breakPoints array elements .. see extern.h)
const uint32_t ADDR_ID_OFFSET = 50;

const uint32_t MAX_REG_ROWS = 50;
const uint32_t MAX_ADDR_ROWS = 50;
const uint32_t MAX_EXPR_ROWS = 50;

// Stored in fields of BPoint objects
const uint32_t PC_REG_TYPE = 0;
const uint32_t ADDR_TYPE = 1;

const uint32_t D0_TYPE_ID = 0;
const uint32_t D1_TYPE_ID = 1;
const uint32_t D2_TYPE_ID = 2;
const uint32_t D3_TYPE_ID = 3;
const uint32_t D4_TYPE_ID = 4;
const uint32_t D5_TYPE_ID = 5;
const uint32_t D6_TYPE_ID = 6;
const uint32_t D7_TYPE_ID = 7;
const uint32_t A0_TYPE_ID = 8;
const uint32_t A1_TYPE_ID = 9;
const uint32_t A2_TYPE_ID = 10;
const uint32_t A3_TYPE_ID = 11;
const uint32_t A4_TYPE_ID = 12;
const uint32_t A5_TYPE_ID = 13;
const uint32_t A6_TYPE_ID = 14;
const uint32_t A7_TYPE_ID = 15;
const uint32_t PC_TYPE_ID = 16;
const uint32_t DEFAULT_TYPE_ID = PC_TYPE_ID;

const uint32_t EQUAL_OP = 0;         // ==
const uint32_t NOT_EQUAL_OP = 1;     // !=
const uint32_t GT_OP = 2;            // >
const uint32_t GT_EQUAL_OP = 3;      // >=
const uint32_t LT_OP = 4;            // <
const uint32_t LT_EQUAL_OP = 5;      // <=
const uint32_t NA_OP = 6;            // NA
const uint32_t DEFAULT_OP = EQUAL_OP;

const uint32_t BYTE_SIZE = 0;
const uint32_t WORD_SIZE = 1;
const uint32_t LONG_SIZE = 2;
const uint32_t DEFAULT_SIZE = LONG_SIZE;

const uint32_t RW_TYPE = 0;
const uint32_t READ_TYPE = 1;
const uint32_t WRITE_TYPE = 2;
const uint32_t NA_TYPE = 3;
const uint32_t DEFAULT_TYPE = RW_TYPE;

const uint32_t EXPR_ON = 0;
const uint32_t EXPR_OFF = 1;

const uint32_t SREC_MAX = 515;       // maximum buffer size for S-Record

const uint32_t MAX_COMM = 16;        // maximum number of comm ports supported
const uint32_t MAX_SERIAL_IN = 256;  // maximum size of serial input buffer

//Default window locations and sizes.
const uint32_t FORM1_TOP = 100;          // Form1 Top
const uint32_t FORM1_LEFT = 100;         // Form1 Left
const uint32_t SIMIO_FORM_TOP = 300;     // SimIO Form Top
const uint32_t SIMIO_FORM_LEFT = 200;    // SimIO Form Left
const uint32_t MEMORY_FORM_TOP = 80;     // Memory Form Top
const uint32_t MEMORY_FORM_LEFT = 280;   // Memory Form Left
const uint32_t STACK_FORM_TOP = 200;     // Stack Form Top
const uint32_t STACK_FORM_LEFT = 40;     // Stack Form Left
const uint32_t STACK_FORM_HEIGHT = 538;  // Stack Form Height
const uint32_t HARDWARE_FORM_TOP = 100;  // Hardware Form Top
const uint32_t HARDWARE_FORM_LEFT = 240; // Hardware Form Left

#endif /* DEF_H_ */
