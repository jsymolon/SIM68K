/***************************** 68000 SIMULATOR ****************************

 File Name: RUN.C

 This file contains various routines to run a 68000 instruction.  These
 routines are :

 decode_size(), eff_addr(), runprog(), exec_inst(), exception()

 Modified by: Charles Kelly
 www.easy68k.com

 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "extern.h"        		// global declarations
#include "OPCODES.H"       		// opcode masks for decoding
#include "PROTO.H"
#include "UTILS.h"
//#include "SIM68Ku.h"
//#include "simIOu.h"
//#include "hardwareu.h"
//#include "logU.h"

#include <string>

//extern char buffer[256];  //used to form messages for display in window
bool trace_bit = false;

/**************************** int32_t decode_size() ****************************
 name       : int32_t decode_size (result)
 parameters : int32_t *result : the appropriate mask for the decoded size
 function   : decodes the size field in the instruction being processed
 and returns a mask to be used in instruction execution.
 For example, if the size field was "01" then the mask
 returned is WORD_MASK.
 ****************************************************************************/
int32_t decode_size(int32_t *result) {
	int32_t bits;

	/* the size field is always in bits 6 and 7 of the instruction word */
	bits = (inst >> 6) & 0x0003;

	switch (bits) {
	case 0:
		*result = BYTE_MASK;
		break;
	case 1:
		*result = WORD_MASK;
		break;
	case 2:
		*result = LONG_MASK;
		break;
	default:
		*result = 0;
	}

	if (*result != 0)       // ck 1-06-2006
		return SUCCESS;
	else
		return FAILURE;
}

/**************************** int32_t eff_addr() *******************************
 name       : int32_t eff_addr (size, mask, add_times)
 parameters : int32_t size : the appropriate size mask
 int32_t mask : the effective address modes mask to be used
 int32_t add_times : tells whether to increment the cycle counter
 (there are times when we don't want to)
 function   : eff_addr() decodes the effective address field in the current
 instruction, returns a pointer to the effective address
 either in EA1 or EA2, and returns the value at that
 location in EV1 or EV2.
 ****************************************************************************/

int32_t eff_addr(int32_t size, int32_t mask, bool add_times) {
	bool legal = false;
	int32_t error = SUCCESS, mode, reg, addr, move_operation;
	int32_t bwinc, linc;
	uint32_t ext;
	int32_t inc_size, ind_reg, disp;

	if ((((inst & 0xf000) == 0x1000) || ((inst & 0xf000) == 0x2000)
			|| ((inst & 0xf000) == 0x3000)) && (mask == DATA_ALT_ADDR))
		move_operation = true;    // move destination address
	else
		move_operation = false; // other effective address or move source address

	if (move_operation)
		addr = (inst >> 6) & 0x003f;
	else
		addr = inst & 0x003f;
	bwinc = linc = 0;
	if (move_operation) {		// reg and mode are reversed in MOVE dest EA
		reg = (addr & MODE_MASK) >> 3;
		mode = addr & REG_MASK;
	} else {
		mode = (addr & MODE_MASK) >> 3;
		reg = addr & REG_MASK;
	}

	switch (mode) {               // switch on effective address mode
	case 0:                                    // Dn
		if (mask & bit_1) {
			if (move_operation) { // choose EA2 in case of MOVE dest effective address
				EA2 = &D[reg];
				utils->value_of(EA2, &EV2, size);
			} else {
				EA1 = &D[reg];
				utils->value_of(EA1, &EV1, size);
			}
			bwinc = linc = 0;
			legal = true;
		}
		break;
	case 1:                                    // An
		if ((mask & bit_2) && size != BYTE_MASK) {
			reg = utils->a_reg(reg);
			if (move_operation) { // choose EA2 in case of MOVE dest effective address
				EA2 = &A[reg];
				utils->value_of(EA2, &EV2, size);
			} else {
				EA1 = &A[reg];
				utils->value_of(EA1, &EV1, size);
			}
			bwinc = linc = 0;
			legal = true;
		}
		break;
	case 2:                                    // [An]
		if (mask & bit_3) {
			reg = utils->a_reg(reg);
			if (move_operation) { // choose EA2 in case of MOVE dest effective address
				EA2 = (uint32_t*)&memory->memory[A[reg] & ADDRMASK];
				error = utils->mem_req(A[reg], size, &EV2);
			} else {
				EA1 = (uint32_t*)&memory->memory[A[reg] & ADDRMASK];
				error = utils->mem_req(A[reg], size, &EV1);
			}
			bwinc = 4;
			linc = 8;
			legal = true;
		}
		break;
	case 3:                                    // [An]+
		if (mask & bit_4) {
			if (size == BYTE_MASK)
				if (reg == 7)                    // if stack operation on byte
					inc_size = 2;            // force even address  ck 4-19-2002
				else
					inc_size = 1;
			else if (size == WORD_MASK)
				inc_size = 2;
			else
				inc_size = 4;
			reg = utils->a_reg(reg);               // set reg to 8 if Supervisor Stack
			if (move_operation) { // choose EA2 in case of MOVE dest effective address
				EA2 = (uint32_t*) &memory->memory[A[reg] & ADDRMASK];
				error = utils->mem_req(A[reg], size, &EV2);
			} else {
				EA1 = (uint32_t*) &memory->memory[A[reg] & ADDRMASK];
				error = utils->mem_req(A[reg], size, &EV1);
			}
			A[reg] = A[reg] + inc_size;
			bwinc = 4;
			linc = 8;
			legal = true;
		}
		break;
	case 4:                                    // -[An]
		if (mask & bit_5) {
			if (size == BYTE_MASK)
				if (reg == 7)                    // if stack operation on byte
					inc_size = 2;            // force even address  ck 4-19-2002
				else
					inc_size = 1;
			else if (size == WORD_MASK)
				inc_size = 2;
			else
				inc_size = 4;
			reg = utils->a_reg(reg);                // set reg to 8 if Supervisor Stack
			A[reg] = A[reg] - inc_size;
			if (move_operation) { // choose EA2 in case of MOVE dest effective address
				EA2 = (uint32_t*) &memory->memory[A[reg] & ADDRMASK];
				error = utils->mem_req(A[reg], size, &EV2);
			} else {
				EA1 = (uint32_t*) &memory->memory[A[reg] & ADDRMASK];
				error = utils->mem_req(A[reg], size, &EV1);
			}
			bwinc = 6;
			linc = 10;
			legal = true;
		}
		break;
	case 5:                                    // d[An]
		if (mask & bit_6) {
			reg = utils->a_reg(reg);
			utils->mem_request(&PC, WORD_MASK, &ext);
			utils->from_2s_comp(ext, WORD_MASK, (uint32_t *)&ext);
			if (move_operation) { // choose EA2 in case of MOVE dest effective address
				EA2 = (uint32_t*) &memory->memory[(A[reg] + ext) & ADDRMASK];
				error = utils->mem_req(A[reg] + ext, size, &EV2);
			} else {
				EA1 = (uint32_t*) &memory->memory[(A[reg] + ext) & ADDRMASK];
				error = utils->mem_req(A[reg] + ext, size, &EV1);
			}
			bwinc = 8;
			linc = 12;
			legal = true;
		}
		break;
	case 6:                                    // d[An, Xi]
		if (mask & bit_7) {
			reg = utils->a_reg(reg);
			// fetch extension word
			utils->mem_request(&PC, WORD_MASK, &ext);
			disp = ext & 0xff;
			utils->sign_extend(disp, BYTE_MASK, (uint32_t*)&disp);
			utils->from_2s_comp(disp, WORD_MASK, (uint32_t*)&disp);
			// get index register value
			if (ext & 0x8000)
				ind_reg = A[utils->a_reg((ext & 0x7000) >> 12)];
			else
				ind_reg = D[(ext & 0x7000) >> 12];
			// get correct length for index register
			if (!(ext & 0x0800)) {
				utils->sign_extend(ind_reg, WORD_MASK, (uint32_t*)&ind_reg);
				utils->from_2s_comp(ind_reg, LONG_MASK, (uint32_t*)&ind_reg);
			}
			if (move_operation) { // choose EA2 in case of MOVE dest effective address
				EA2 = (uint32_t*) &memory->memory[(A[reg] + disp + ind_reg) & ADDRMASK];
				error = utils->mem_req(A[reg] + disp + ind_reg, size, &EV2);
			} else {
				EA1 = (uint32_t*) &memory->memory[(A[reg] + disp + ind_reg) & ADDRMASK];
				error = utils->mem_req(A[reg] + disp + ind_reg, size, &EV1);
			}
			bwinc = 10;
			linc = 14;
			legal = true;
		}
		break;
	case 7:                    // Abs.W  Abs.L  d[PC]  d[PC, Xi]
		switch (reg) {
		case 0:                                // Abs.W
			if (mask & bit_8) {
				utils->mem_request(&PC, WORD_MASK, &ext); // get address from instruction
				if (ext >= 0x8000)  // if address is negative word  ck 1-11-2008
					ext = 0xFFFF0000 | ext; // sign extend (corrected ck 6-23-2009)
				if (move_operation) { // choose EA2 in case of MOVE dest effective address
					EA2 = (uint32_t*) &memory->memory[ext & ADDRMASK]; // get effective address
					error = utils->mem_req(ext, size, &EV2);         // read data
				} else {
					EA1 = (uint32_t*) &memory->memory[ext & ADDRMASK];
					error = utils->mem_req(ext, size, &EV1);
				}
				bwinc = 8;
				linc = 12;
				legal = true;
			}
			break;
		case 1:                                // Abs.L
			if (mask & bit_9) {
				utils->mem_request(&PC, LONG_MASK, &ext); //ck 8-23-02 WORD_MASK TO LONG
				if (move_operation) { // choose EA2 in case of MOVE dest effective address
					EA2 = (uint32_t*) &memory->memory[ext & ADDRMASK];
					error = utils->mem_req(ext, size, &EV2);
				} else {
					EA1 = (uint32_t*) &memory->memory[ext & ADDRMASK];
					error = utils->mem_req(ext, size, &EV1);
				}
				bwinc = 12;
				linc = 16;
				legal = true;
			}
			break;
		case 2:                                // d[PC]
			if (mask & bit_10) {
				utils->mem_request(&PC, WORD_MASK, &ext);
				utils->from_2s_comp(ext, WORD_MASK, (uint32_t*)&ext);
				if (move_operation) { // choose EA2 in case of MOVE dest effective address
					EA2 = (uint32_t*) &memory->memory[(PC + ext - 2) & ADDRMASK];
					error = utils->mem_req(PC + ext - 2, size, &EV2);
				} else {
					EA1 = (uint32_t*) &memory->memory[(PC + ext - 2) & ADDRMASK];
					error = utils->mem_req(PC + ext - 2, size, &EV1);
				}
				bwinc = 8;
				linc = 12;
				legal = true;
			}
			break;
		case 3:                                // d[PC, Xi]
			if (mask & bit_11) {
				// fetch extension word
				utils->mem_request(&PC, WORD_MASK, &ext);
				disp = ext & 0xff;
				utils->sign_extend(disp, BYTE_MASK, (uint32_t*)&disp);
				utils->from_2s_comp(disp, WORD_MASK, (uint32_t*)&disp);
				// get index register value
				if (ext & 0x8000)
					ind_reg = A[utils->a_reg((ext & 0x7000) >> 12)];
				else
					ind_reg = D[(ext & 0x7000) >> 12];
				// get correct length for index register
				if (!(ext & 0x0800)) {
					utils->sign_extend(ind_reg, WORD_MASK, (uint32_t*)&ind_reg);
					utils->from_2s_comp(ind_reg, LONG_MASK, (uint32_t*)&ind_reg);
				}
				ext = ext & 0x00ff;
				if (move_operation) { // choose EA2 in case of MOVE dest effective address
					EA2 = (uint32_t*) &memory->memory[(PC - 2 + disp + ind_reg) & ADDRMASK];
					error = utils->mem_req(PC - 2 + disp + ind_reg, size, &EV2);
				} else {
					EA1 = (uint32_t*) &memory->memory[(PC - 2 + disp + ind_reg) & ADDRMASK];
					error = utils->mem_req(PC - 2 + disp + ind_reg, size, &EV1);
				}
				bwinc = 10;
				linc = 14;
				legal = true;
			}
			break;
		case 4:                                // Imm
			if (mask & bit_12) {
				if ((size == BYTE_MASK) || (size == WORD_MASK))
					utils->mem_request(&PC, WORD_MASK, &ext);
				else
					utils->mem_request(&PC, LONG_MASK, &ext);
				global_temp = ext;
				if (move_operation) { // choose EA2 in case of MOVE dest effective address
					EA2 = (uint32_t*) &global_temp;
					utils->value_of(EA2, &EV2, size);
				} else {
					EA1 = (uint32_t*) &global_temp;
					utils->value_of(EA1, &EV1, size);
				}
				bwinc = 4;
				linc = 8;
				legal = true;
			}
			break;
		}
		break;
	}   	  // switch

	if (legal) {          // if legal instruction
		if (add_times) {
			if (size != LONG_MASK)
				utils->inc_cyc(bwinc);
			else
				utils->inc_cyc(linc);
		}
	} else
		return BAD_INST;    // ILLEGAL instruction
	return error;         // return error code
}

/**************************** int32_t eff_addr_noread() ***************************
 Same as eff_addr above but does not read from address. Used by LEA & PEA

 name       : int32_t eff_addr_noread (size, mask, add_times)
 parameters : int32_t size : the appropriate size mask
 int32_t mask : the effective address modes mask to be used
 int32_t add_times : tells whether to increment the cycle counter
 (there are times when we don't want to)
 description: decodes the effective address field in the current
 instruction, returns a pointer to the effective address
 either in EA1 or EA2.
 ****************************************************************************/
int32_t eff_addr_noread(int32_t size, int32_t mask, bool add_times) {
	int32_t mode, reg, legal, addr, move_operation;
	int32_t bwinc, linc;
	uint32_t ext, inc_size, ind_reg, *value, disp;

	if ((((inst & 0xf000) == 0x1000) || ((inst & 0xf000) == 0x2000)
			|| ((inst & 0xf000) == 0x3000)) && (mask == DATA_ALT_ADDR))
		move_operation = true;
	else
		move_operation = false;

	if (move_operation)
		addr = (inst >> 6) & 0x003f;
	else
		addr = inst & 0x003f;
	legal = false;
	bwinc = linc = 0;
	if (move_operation) { /* reg and mode are reversed in MOVE dest EA */
		reg = (addr & MODE_MASK) >> 3;
		mode = addr & REG_MASK;
	} else {
		mode = (addr & MODE_MASK) >> 3;
		reg = addr & REG_MASK;
	}

	switch (mode) {               // switch on effective address mode
	case 0:                                    // Dn
		if (mask & bit_1) {
			value = &D[reg];
			bwinc = linc = 0;
			legal = true;
		}
		break;
	case 1:                                    // An
		if (mask & bit_2) {
			reg = utils->a_reg(reg);
			value = &A[reg];
			bwinc = linc = 0;
			legal = true;
		}
		break;
	case 2:                                    // [An]
		if (mask & bit_3) {
			reg = utils->a_reg(reg);
			value = (uint32_t*) &memory->memory[A[reg] & ADDRMASK];
			bwinc = 4;
			linc = 8;
			legal = true;
		}
		break;
	case 3:                                    // [An]+
		if (mask & bit_4) {
			if (size == BYTE_MASK)
				if (reg == 7)                    // if stack operation on byte
					inc_size = 2;            // force even address  ck 4-19-2002
				else
					inc_size = 1;
			else if (size == WORD_MASK)
				inc_size = 2;
			else
				inc_size = 4;
			reg = utils->a_reg(reg);               // set reg to 8 if Supervisor Stack
			value = (uint32_t*) &memory->memory[A[reg] & ADDRMASK];
			A[reg] = A[reg] + inc_size;
			bwinc = 4;
			linc = 8;
			legal = true;
		}
		break;
	case 4:                                    // -[An]
		if (mask & bit_5) {
			if (size == BYTE_MASK)
				if (reg == 7)                    // if stack operation on byte
					inc_size = 2;            // force even address  ck 4-19-2002
				else
					inc_size = 1;
			else if (size == WORD_MASK)
				inc_size = 2;
			else
				inc_size = 4;
			reg = utils->a_reg(reg);                // set reg to 8 if Supervisor Stack
			A[reg] = A[reg] - inc_size;
			value = (uint32_t*) &memory->memory[A[reg] & ADDRMASK];
			bwinc = 6;
			linc = 10;
			legal = true;
		}
		break;
	case 5:                                    // d[An]
		if (mask & bit_6) {
			reg = utils->a_reg(reg);
			utils->mem_request(&PC, WORD_MASK, &ext);
			utils->from_2s_comp(ext, WORD_MASK, (uint32_t*)&ext);
			value = (uint32_t*) &memory->memory[(A[reg] + ext) & ADDRMASK];
			bwinc = 8;
			linc = 12;
			legal = true;
		}
		break;
	case 6:                                    // d[An, Xi]
		if (mask & bit_7) {
			reg = utils->a_reg(reg);
			// fetch extension word
			utils->mem_request(&PC, WORD_MASK, &ext);
			disp = ext & 0xff;
			utils->sign_extend(disp, BYTE_MASK, (uint32_t*)&disp);
			utils->from_2s_comp(disp, WORD_MASK, (uint32_t*)&disp);
			// get index register value
			if (ext & 0x8000)
				ind_reg = A[utils->a_reg((ext & 0x7000) >> 12)];
			else
				ind_reg = D[(ext & 0x7000) >> 12];
			// get correct length for index register
			if (!(ext & 0x0800)) {
				utils->sign_extend(ind_reg, WORD_MASK, (uint32_t*)&ind_reg);
				utils->from_2s_comp(ind_reg, LONG_MASK, (uint32_t*)&ind_reg);
			}
			value = (uint32_t*) (&memory->memory[(A[reg] + disp + ind_reg) & ADDRMASK]);
			bwinc = 10;
			linc = 14;
			legal = true;
		}
		break;
	case 7:                    // Abs.W  Abs.L  d[PC]  d[PC, Xi]
		switch (reg) {
		case 0:                                // Abs.W
			if (mask & bit_8) {
				utils->mem_request(&PC, WORD_MASK, &ext);
				value = (uint32_t*) &memory->memory[ext & ADDRMASK];
				bwinc = 8;
				linc = 12;
				legal = true;
			}
			break;
		case 1:                                // Abs.L
			if (mask & bit_9) {
				utils->mem_request(&PC, LONG_MASK, &ext); //ck 8-23-02 WORD_MASK TO LONG
				value = (uint32_t*) &memory->memory[ext & ADDRMASK];
				bwinc = 12;
				linc = 16;
				legal = true;
			}
			break;
		case 2:                                // d[PC]
			if (mask & bit_10) {
				utils->mem_request(&PC, WORD_MASK, &ext);
				utils->from_2s_comp(ext, WORD_MASK, (uint32_t*)&ext);
				value = (uint32_t*) &memory->memory[(PC + ext - 2) & ADDRMASK];
				bwinc = 8;
				linc = 12;
				legal = true;
			}
			break;
		case 3:                                // d[PC, Xi]
			if (mask & bit_11) {
				// fetch extension word
				utils->mem_request(&PC, WORD_MASK, &ext);
				disp = ext & 0xff;
				utils->sign_extend(disp, BYTE_MASK, (uint32_t*)&disp);
				utils->from_2s_comp(disp, WORD_MASK, (uint32_t*)&disp);
				// get index register value
				if (ext & 0x8000)
					ind_reg = A[utils->a_reg((ext & 0x7000) >> 12)];
				else
					ind_reg = D[(ext & 0x7000) >> 12];
				// get correct length for index register
				if (!(ext & 0x0800)) {
					utils->sign_extend(ind_reg, WORD_MASK, (uint32_t*)&ind_reg);
					utils->from_2s_comp(ind_reg, LONG_MASK, (uint32_t*)&ind_reg);
				}
				ext = ext & 0x00ff;
				value = (uint32_t*) (&memory->memory[(PC - 2 + disp + ind_reg) & ADDRMASK]);
				bwinc = 10;
				linc = 14;
				legal = true;
			}
			break;
		case 4:                                // Imm
			if (mask & bit_12) {
				if ((size == BYTE_MASK) || (size == WORD_MASK))
					utils->mem_request(&PC, WORD_MASK, &ext);
				else
					utils->mem_request(&PC, LONG_MASK, &ext);
				global_temp = ext;
				value = (uint32_t*)&global_temp;
				bwinc = 4;
				linc = 8;
				legal = true;
			}
			break;
		}
		break;
	}   	  // switch

	if (legal) {
		if (add_times) {
			if (size != LONG_MASK)
				utils->inc_cyc(bwinc);
			else
				utils->inc_cyc(linc);
		}
		if (move_operation) { // choose EA2 in case of MOVE dest effective address
			EA2 = value;
		} else {
			EA1 = value;
		}
		return SUCCESS;
	} else
		return FAILURE;       // return FAILURE if illegal addressing mode
}

/**************************** int32_t runprog() *******************************
 name       : int32_t runprog ()
 parameters : NONE
 function   : executes a program at PC specified or current PC if not
 specified.  this function is the outer loop of the
 running program.  it handles i/o interrupts, user
 (keyboard) interrupts, and calls the error routine if an
 illegal opcode is found.
 ****************************************************************************/
int32_t runprog() {
	int32_t i;
	char ch, *pc_str;

	halt = false;
	exec_inst();          // execute an instruction

	do {
		//TODO:
//		Application->ProcessMessages();
//		if (inputMode)
//			Sleep(10);        // don't hog the CPU while waiting for input
	} while (inputMode && runMode);

	if (errflg) {        // if illegal opcode in program initiate an exception
		halt = true;               // force halt
		//TODO: Form
//		Form1->Message->Lines->Add(
//				"Address or Bus error during exception processing. Execution halted");
	}

	// simple breakpoints
	for (i = 0; i < bpoints; i++) {
		if (PC == brkpt[i]) {
			// TODO: do error
//			Form1->Message->Lines->Add(str.sprintf("break point at %04x", PC));
//			trace = true;             // force trace mode
//			Form1->AutoTraceTimer->Enabled = false;
			//Form1->SetFocus();        // bring Form1 to top
		}
	}

	// if run to cursor address reached
	if (PC == runToAddr) {
		trace = true;             // force trace mode
		// TODO: do error
		//Form1->AutoTraceTimer->Enabled = false;
		runToAddr = 0;
	}

	// advanced breakpoints
	for (i = 0; i < exprCount; i++) {
		// Evaluate isBreak() for all expressions
		//if(true) {
		if (bpExpressions[i].isBreak()) {
			// TODO: do error
//			Form1->Message->Lines->Add(str.sprintf("break point at %04x", PC));
//			trace = true;             // force trace mode
//			Form1->AutoTraceTimer->Enabled = false;
			//Form1->SetFocus();        // bring Form1 to top
		}
	}

	if (sstep) {                  // if "Step Over" mode
		if (PC == stepToAddr) {     // if step address reached
			trace = true;             // force trace mode
			stepToAddr = 0;           // reset for next use
		}
	}

	OLD_PC = PC;	// update the OLD_PC

	if (trace || halt) {
		runMode = false;            // stop running if enabled
//		if (!stopInstruction)
//			Hardware->autoIRQoff(); // turn off auto interrupt timers unless STOP instruction ck 1-11-2008
//		if (simIO->fullScreen
//				&& Form1->Monitor->MonitorNum == FullScreenMonitor) {
//			simIO->fullScreen = false;
//			simIO->setupWindow();
//		}
//		scrshow();              // if trace is on then update the screen
//		if (halt)
//			Form1->setMenuTrace(); // set menu and toolbar to disable debug commands
//		else {
//			Form1->setMenuActive();   // enable debug commands
//		}

//		if (trace) {
//			if (!inputMode)           // if not doing user input
//				Form1->SetFocus();      //   bring Form1 to top
//		}
	}
	return 0;
}

// -----------------------------------------------------------------------
void logMemory() {
	// ----- if logging memory -----
	if (ElogFlag == INST_REG_MEM) { // if logging memory
		uint32_t addr = logMemAddr;         // address to log
		int32_t nRows = logMemBytes / 16; // how many rows to log

		fprintf(ElogFile, "\n");           // blank line
		// display memory by rows of 16 bytes
		for (int32_t r = 0; r < nRows; r++) {
			if (addr < 0 || addr >= MEMSIZE) // if invalid address
				fprintf(ElogFile, "%08X: Invalid Address", addr);
			else
				// valid address
				fprintf(ElogFile, "%08X: ", addr);
			// display 16 hex bytes of memory
			for (int32_t i = 0; i < 16; i++) {
				if (addr + i >= MEMSIZE) // if invalid address
					fprintf(ElogFile, "xx "); // is this necessary?
				else
					fprintf(ElogFile, "%02hX ",
							(unsigned char) memory->memory[(addr + i) & ADDRMASK]);
			}
			// display 16 bytes as ASCII
			for (int32_t i = 0; i < 16; i++) {
				if (addr + i >= MEMSIZE) // if invalid address
					fprintf(ElogFile, "-"); // is this necessary?
				else {
					if (memory->memory[(addr + i) & ADDRMASK] >= ' ') // if displayable char
						fprintf(ElogFile, "%c",
								memory->memory[(addr + i) & ADDRMASK]);
					else
						fprintf(ElogFile, "-");
				}
			}
			addr += 16;
			fprintf(ElogFile, "\n");         // new line
		}
	}
}

// -----------------------------------------------------------------------
void logRegisters() {
	// ----- if logging registers -----
	if (ElogFlag == REGISTERS
			|| ElogFlag == INST_REG_MEM) {
		fprintf(ElogFile, "\n");
		// output registers to log file
		fprintf(ElogFile,
				"D0=%08X D4=%08X A0=%08X A4=%08X    T_S__INT___XNZVC\n",
				D[0], D[4], A[0], A[4]);
		fprintf(ElogFile,
				"D1=%08X D5=%08X A1=%08X A5=%08X SR=",
				D[1], D[5], A[1], A[5]);
		for (int32_t j = 0; j < 16; j++) { // display each bit of SR
			if ((0x8000 >> j) & SR)
				fprintf(ElogFile, "1");
			else
				fprintf(ElogFile, "0");
		}
		fprintf(ElogFile,
				"\nD2=%08X D6=%08X A2=%08X A6=%08X US=%08X\n",
				D[2], D[6], A[2], A[6], A[7]);
		fprintf(ElogFile,
				"D3=%08X D7=%08X A3=%08X A7=%08X SS=%08X\n",
				D[3], D[7], A[3], A[utils->a_reg(7)], A[8]);
	}
}

/**************************** int32_t exec_inst() *****************************
 name       : int32_t exec_inst ()
 parameters : NONE
 function   : executes a single instruction at the location pointed
 to by PC.  it is called from runprog() and sets the
 flag "errflg" if an illegal opcode is detected so
 that runprog() terminates.  exec_inst() also takes
 care of handling the different kinds of exceptions
 that may occur.  If an instruction returns a different
 return code than "SUCCESS" then the appropriate
 exception is initiated, unless the "exceptions" flag
 is turned off by the user in which case the exception
 is not initiated and the program simply terminates and
 informs the user that an exception condition has occurred.
 ****************************************************************************/
int32_t exec_inst() {
	static int32_t start, finish, exec_result, i, intMask;
	static uint32_t temp;
	char buffer[512];

	// Reset read and write flags so when breakpoints are tested for read/write
	// access, we know if this instruction caused a respective read/write.
	bpRead = false;
	bpWrite = false;
	try {
		// if previous instruction caused bus or address error
		if (exec_result == ADDR_ERROR || exec_result == BUS_ERROR)
			errflg = true;            // default to halt simulator
		exec_result = utils->mem_request(&PC, WORD_MASK, (uint32_t*) &inst);
		if (!(exec_result)) {
			int32_t offsetidx = (inst & FIRST_FOUR) >> 12;
			start = offsets[offsetidx];
			finish = offsets[offsetidx + 1] - 1;

			for (i = start; i <= finish || exec_result == BAD_INST; i++) { // for all offsets
				if ((exec_result == BAD_INST) || ((inst & ~inst_arr[i].mask) == inst_arr[i].val)) {
					if (trace) {
						utils->mem_req(PC, WORD_MASK, &temp);
						if (inst == 0xFFFF && temp == 0xFFFF) // if SIMHALT command
							sprintf(buffer, "PC=%08x  Code=%04X  SIMHALT", PC - 2, inst);
						else
							sprintf(buffer, "PC=%08x  Code=%04X  %s", PC - 2, inst, inst_arr[i].name);
						mainframe->logMsg(buffer);

						if (logging) {
							logMemory();
							logRegisters();

							// ----- if logging instruction -----
							if (ElogFlag) {
								//TODO: Form1
//								if (Form1->lineToLog() == false) { // output instruction to log file
//									fprintf(ElogFile, buffer); // if source not present output limited info
//									fprintf(ElogFile, "\n");
//								}
								fflush(ElogFile); // write all bufferred data to file
							}
						} // end if logging
					}

					if (SR & tbit)                        // if trace bit set
						trace_bit = true;
					else
						trace_bit = false;

					if (exec_result != BAD_INST) {
						exec_result = (*(names[i]))(); // run the 68000 instruction
						mainframe->updateUI();
					}
					// if previous instruction caused address or bus error but this one did not
					if (errflg && (exec_result != ADDR_ERROR && exec_result != BUS_ERROR))
						errflg = false;              // don't halt the simulator

					//-------------------------------------------------------------------
					//------------------------ EXCEPTION PROCESSING ---------------------
					//-------------------------------------------------------------------
					if (exceptions) {          // if exception processing enabled
						OLD_PC = PC;                //ck 2.9.2
						switch (exec_result) { // these results prevent trace exception
						case BAD_INST:
							utils->inc_cyc(34);	// Illegal instruction
							OLD_PC -= 2;                    // ck 12-16-2005
							utils->mem_req(0x10, LONG_MASK, &PC);
							//TODO: exceptionHandler(1, 0, READ);
							break;
						case NO_PRIVILEGE:
							utils->inc_cyc(34); // Privileged violation
							utils->mem_req(0x20, LONG_MASK, &PC);
							//TODO:exceptionHandler(1, 0, READ);
							break;
						}
						intMask = 0xFF80 >> (7 - ((SR & intmsk) >> 8)) | 0x40;
//						if (irq & intMask)         // if IRQ
//							irqHandler();             // process IRQ
						if (trace_bit) {     // if trace exception enabled
							utils->inc_cyc(34);
							utils->mem_req(0x24, LONG_MASK, &PC);
							//TODO:exceptionHandler(2, 0, READ);
							OLD_PC = PC;              //ck 2.9.2
						}
						switch (exec_result) { // these results do not prevent trace exception
						case SUCCESS:
							break;
						case STOP_TRAP: 	        // STOP instruction
							//TODO: fix error
//							Form1->AutoTraceTimer->Enabled = false;
							halt = true;
							if (stopInstruction == false) {
								stopInstruction = true;
								//TODO: fix error
//								Form1->Message->Lines->Add(
//										"STOP instruction. Execution halted");
//								Form1->SetFocus();    // bring Form1 to top
//								scrshow();            // update the screen
							}
							break;
						case TRAP_TRAP:
							utils->inc_cyc(38);
							utils->mem_req(128 + (inst & 0x0f) * 4, LONG_MASK, &PC);
							//TODO: exceptionHandler(2, 0, READ);
							break;
						case DIV_BY_ZERO:
							utils->inc_cyc(42);
							utils->mem_req(0x14, LONG_MASK, &PC);
							//TODO: exceptionHandler(2, 0, READ);
							break;
						case CHK_EXCEPTION:
							utils->inc_cyc(44);
							utils->mem_req(0x18, LONG_MASK, &PC);
							//TODO: exceptionHandler(2, 0, READ);
							break;
						case TRAPV_TRAP:
							utils->inc_cyc(34);
							utils->mem_req(0x1C, LONG_MASK, &PC);
							//TODO: exceptionHandler(2, 0, READ);
							break;
						case TRACE_EXCEPTION:
							utils->inc_cyc(34);
							utils->mem_req(0x24, LONG_MASK, &PC);
							//TODO: exceptionHandler(2, 0, READ);
							break;
						case LINE_1010:
							utils->inc_cyc(34);
							utils->mem_req(0x28, LONG_MASK, &PC);
							//TODO: exceptionHandler(2, 0, READ);
							break;
						case LINE_1111:
							utils->inc_cyc(34);
							utils->mem_req(0x2C, LONG_MASK, &PC);
							//TODO: exceptionHandler(2, 0, READ);
							break;
						}
					} else {       // exception processing not enabled
						switch (exec_result) {
						case SUCCESS:
							break;
						case BAD_INST:
							halt = true;	// halt the program
							//TODO: fix error
//							Form1->Message->Lines->Add(
//									str.sprintf(
//											"Illegal instruction found at location %4x. Execution halted",
//											OLD_PC));
							break;
						case NO_PRIVILEGE:
							halt = true;
							//TODO: fix error
//							Form1->Message->Lines->Add(
//									str.sprintf(
//											"supervisor privilege violation at location %4x. Execution halted",
//											OLD_PC));
							break;
						case CHK_EXCEPTION:
							halt = true;
							//TODO: fix error
//							Form1->Message->Lines->Add(
//									str.sprintf(
//											"CHK exception occurred at location %4x. Execution halted",
//											OLD_PC));
							break;
						case STOP_TRAP:
							halt = true;
							//TODO: fix error
//							Form1->AutoTraceTimer->Enabled = false;
//							Form1->Message->Lines->Add(
//									str.sprintf(
//											"STOP instruction executed at location %4x. Execution halted",
//											OLD_PC));
//							Log->stopLogWithAnnounce();
//							Form1->SetFocus();    // bring Form1 to top
//							scrshow();            // update the screen
//							Hardware->disable();
							break;
						case TRAP_TRAP:
							halt = true;
							//TODO: fix error
//							Form1->Message->Lines->Add(
//									str.sprintf(
//											"TRAP exception occurred at location %4x. Execution halted",
//											OLD_PC));
							break;
						case TRAPV_TRAP:
							halt = true;
							//TODO: fix error
//							Form1->Message->Lines->Add(
//									str.sprintf(
//											"TRAPV exception occurred at location %4x. Execution halted",
//											OLD_PC));
							break;
						case DIV_BY_ZERO:
							halt = true;
							//TODO: fix error
//							Form1->Message->Lines->Add(
//									str.sprintf(
//											"Divide by zero occurred at location %4x. Execution halted",
//											OLD_PC));
							break;
						case ADDR_ERROR:
							halt = true;
							//TODO: fix error
//							Form1->Message->Lines->Add("Execution halted");
							break;
						case BUS_ERROR:
							halt = true;
							//TODO: fix error
//							Form1->Message->Lines->Add("Execution halted");
							break;
						case TRACE_EXCEPTION:
							halt = true;
							//TODO: fix error
//							Form1->Message->Lines->Add(
//									str.sprintf(
//											"Trace exception occurred at location %4x. Execution halted",
//											OLD_PC));
							break;
						case LINE_1010:
							halt = true;
							//TODO: fix error
//							Form1->Message->Lines->Add(
//									str.sprintf(
//											"Line 1010 Emulator exception occurred at location %4x. Execution halted",
//											OLD_PC));
							break;
						case LINE_1111:
							halt = true;
							//TODO: fix error
//							Form1->Message->Lines->Add(
//									str.sprintf(
//											"Line 1111 Emulator exception occurred at location %4x. Execution halted",
//											OLD_PC));
							break;
						default:
							halt = true;
							//TODO: fix error
//							Form1->Message->Lines->Add(
//									str.sprintf(
//											"Unknown execution error %4x occurred at location %4x. Execution halted",
//											exec_result, OLD_PC));
						}

						if (SR & tbit) {
							halt = true;
							//TODO: fix error
//							Form1->Message->Lines->Add(
//									str.sprintf(
//											"TRACE exception occurred at location %4x. Execution halted",
//											OLD_PC));
						}
					}
					break;        // break out of for loop
				}
				if (i == finish)
					exec_result = BAD_INST;
			} // end for

		} // end if
	} catch (...) {
		//TODO: fix error
//		Form1->AutoTraceTimer->Enabled = false;
//		sprintf(buffer,
//				"ERROR: An exception occurred in routine 'exec_inst'.\nPC=%08X  Code=%04X",
//				PC - 2, inst);
//		Application->MessageBox(buffer, "Error", MB_OK);
		trace = true;       // stop running programs
		sstep = false;
	}
	return 0;
}

/**************************** int32_t exceptionHandler () *****************************
 name       : int32_t exception (class, loc, r_w)
 parameters : int32_t class : class of exception to be taken
 int32_t loc : the address referenced in the case of an
 address or bus error
 int32_t r_w : in the case of an address or bus error, this
 tells whether the reference was a read or write
 function   : initiates exception processing by pushing the appropriate
 exception stack frame on the system stack and turning
 supervisor mode on and trace mode off.
 ****************************************************************************/
void exceptionHandler(int32_t clas, uint32_t loc, int32_t r_w) {
	int32_t infoWord;
	std::string str;

	// if SSP on odd address OR outside memory range
	if ((A[8] % 2) || (A[8] < 0) || ((uint32_t) A[8] > MEMSIZE)) {
		//TODO: fix error
//		Form1->AutoTraceTimer->Enabled = false;
//		Form1->Message->Lines->Add(
//				str.sprintf(
//						"Error during Exception Handler: SSP odd or outside memory space "));
//		Form1->Message->Lines->Add(str.sprintf("at location %4x", A[8]));
		trace = true;       // stop running programs
		sstep = false;
		return;
	}
	if ((clas == 1) || (clas == 2)) {
		A[8] -= 4; /* create the stack frame for class 1 and 2 exceptions */
		utils->put((uint32_t*) &memory->memory[A[8] & ADDRMASK], OLD_PC, LONG_MASK);
		A[8] -= 2;
		utils->put((uint32_t*) &memory->memory[A[8] & ADDRMASK], SR, WORD_MASK);
	} else { /* class 0 exception (address or bus error) */
		utils->inc_cyc(50); /* fifty clock cycles for the address or bus exception */
		A[8] -= 4; /* now create the exception stack frame */
		utils->put((uint32_t*) &memory->memory[A[8] & ADDRMASK], OLD_PC + 2, LONG_MASK); // OLD_PC+2 to match MECB
		A[8] -= 2;
		utils->put((uint32_t*) &memory->memory[A[8] & ADDRMASK], SR, WORD_MASK);
		A[8] -= 2;
		utils->put((uint32_t*) &memory->memory[A[8] & ADDRMASK], inst, WORD_MASK);
		A[8] -= 4;
		utils->put((uint32_t*) &memory->memory[A[8] & ADDRMASK], loc, LONG_MASK);
		A[8] -= 2;
		if (loc == OLD_PC + 2)       // if address exception reading instruction
			infoWord = 0x6;           // function code 110 Supervisor Program
		else
			// else data access error
			infoWord = 0x5;           // function code 101 Supervisor Data
		if (r_w == READ)
			infoWord |= 0x10;
		utils->put((uint32_t*) &memory->memory[A[8] & ADDRMASK], infoWord, WORD_MASK);/* push information word */
	}
	SR = SR | sbit; /* force processor into supervisor state */
	SR = SR & ~tbit; /* turn off trace mode */
	trace_bit = false;
}

//---------------------------------------------------------
void irqHandler() {
	exceptionHandler(2, (uint32_t)0, READ);
	SR &= 0xF8FF;                 // clear irq priority bits
	if (irq & 0x40) {             // if IRQ 7
		SR = SR | 0x700;	        // set priority level
		utils->mem_req(0x7C, LONG_MASK, &PC);
		irq &= 0x3F;                // clear irq request
	} else if (irq & 0x20) {      // if IRQ 6
		SR = SR | 0x600;	        // set priority level
		utils->mem_req(0x78, LONG_MASK, &PC);
		irq &= 0x1F;                // clear irq request
	} else if (irq & 0x10) {      // if IRQ 5
		SR = SR | 0x500;	        // set priority level
		utils->mem_req(0x74, LONG_MASK, &PC);
		irq &= 0x0F;                // clear irq request
	} else if (irq & 0x08) {      // if IRQ 4
		SR = SR | 0x400;	        // set priority level
		utils->mem_req(0x70, LONG_MASK, &PC);
		irq &= 0x07;                // clear irq request
	} else if (irq & 0x04) {      // if IRQ 3
		SR = SR | 0x300;	        // set priority level
		utils->mem_req(0x6C, LONG_MASK, &PC);
		irq &= 0x03;                // clear irq request
	} else if (irq & 0x02) {      // if IRQ 2
		SR = SR | 0x200;	        // set priority level
		utils->mem_req(0x68, LONG_MASK, &PC);
		irq &= 0x01;                // clear irq request
	} else if (irq & 0x01) {      // if IRQ 1
		SR = SR | 0x100;	        // set priority level
		utils->mem_req(0x64, LONG_MASK, &PC);
		irq &= 0x00;                // clear irq request
	}
	utils->inc_cyc(34);
}

//---------------------------------------------------------
// Halt Simulator
void haltSimulator() {
	//TODO: fix error
//	Form1->AutoTraceTimer->Enabled = false;
	trace = false;
	halt = true;
//	Hardware->disable();
//	Log->stopLogWithAnnounce();
}
