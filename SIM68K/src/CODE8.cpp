/***************************** 68000 SIMULATOR ****************************

 File Name: CODE8.C
 Version: 1.0

 The instructions implemented in this file are the program control operations:

 Bcc, DBcc, Scc, BRA, BSR, JMP, JSR, RTE, RTR, RTS, NOP

 Modified by: Charles Kelly
 www.easy68k.com

 ***************************************************************************/

#include <stdio.h>
#include "extern.h"         /* contains global "extern" declarations */
#include "PROTO.H"

//-------------------------------------------------------------------------
// Branch on Condition Code (not just Carry Clear)
int32_t BCC() {
	uint32_t displacement;
	int32_t condition;

	displacement = inst & 0xff;
	if (displacement == 0) {
		utils->mem_request(&PC, WORD_MASK, &displacement);
		utils->from_2s_comp(displacement, WORD_MASK, &displacement);
	} else
		utils->from_2s_comp(displacement, BYTE_MASK, &displacement);

	condition = (inst >> 8) & 0x0f;

	// perform the BCC operation
	if (utils->check_condition(condition))      // If branch taken
			{
		PC = OLD_PC + displacement + 2;
		// displacement is relative to the end of the instruction word
		utils->inc_cyc(10);
	} else
		// Else, branch not taken
		utils->inc_cyc((inst & 0xff) ? 8 : 12); // if short branch utils->inc_cyc(8)

	return SUCCESS;
}

//-------------------------------------------------------------------------
// DBcc
// ck. Fixed bug, DBcc did not exit loop and was modifying the upper word
//     of the data register.
int32_t DBCC() {
	uint32_t displacement;
	int32_t reg;

	utils->mem_request(&PC, WORD_MASK, &displacement);
	utils->from_2s_comp(displacement, WORD_MASK, &displacement);
	reg = inst & 0x07;

	// perform the DBCC operation
	if (utils->check_condition((inst >> 8) & 0x0f))
		utils->inc_cyc(12);
	else {
		D[reg] = (D[reg] & ~WORD_MASK) | ((D[reg] - 1) & 0xFFFF);
		if ((D[reg] & 0xffff) == 0xFFFF)
			utils->inc_cyc(14);
		else {
			utils->inc_cyc(10);
			// displacement is relative to the end of the instruction word
			PC = OLD_PC + displacement + 2;
		}
	}

	return SUCCESS;
}

int32_t SCC() {
	int32_t condition;

	int32_t error = eff_addr(BYTE_MASK, DATA_ALT_ADDR, true);
	if (error)              // if address error
		return error;         // return error code

	/* perform the SCC operation */
	condition = (inst >> 8) & 0x0f;
	if (utils->check_condition(condition))
		utils->put(EA1, BYTE_MASK, BYTE_MASK);
	else
		utils->put(EA1, 0, BYTE_MASK);

	if ((inst & 0x0030) == 0)
		utils->inc_cyc(utils->check_condition(condition) ? 6 : 4);
	else
		utils->inc_cyc(8);

	return SUCCESS;
}

//-------------------------------------------------------------------------
// BRA
int32_t BRA() {
	uint32_t displacement;

	displacement = inst & 0xff;
	if (displacement == 0) {
		utils->mem_request(&PC, WORD_MASK, &displacement);
		utils->from_2s_comp(displacement, WORD_MASK, &displacement);
	} else
		utils->from_2s_comp(displacement, BYTE_MASK, &displacement);

	// perform the BRA operation
	PC = OLD_PC + displacement + 2;
	// displacement is relative to the end of the instructin word

	utils->inc_cyc(10);
	return SUCCESS;
}

int32_t BSR() {
	uint32_t displacement;

	displacement = inst & 0xff;
	if (displacement == 0) {
		utils->mem_request(&PC, WORD_MASK, &displacement);
		utils->from_2s_comp(displacement, WORD_MASK, &displacement);
	} else
		utils->from_2s_comp(displacement, BYTE_MASK, &displacement);

	// perform the BSR operation
	A[utils->a_reg(7)] -= 4;
	utils->put((uint32_t*) &memory->memory[A[utils->a_reg(7)]], PC, LONG_MASK);

	// set address to stop program execution if user selects "Step Over"
	if (sstep && stepToAddr == 0) {  // if "Step Over" mode
		trace = false;              // do not trace through subroutine
		stepToAddr = PC;
	}

	PC = OLD_PC + displacement + 2;
	// displacement is relative to the end of the instruction word

	utils->inc_cyc(18);
	return SUCCESS;
}

int32_t JMP() {
	int32_t error = eff_addr(WORD_MASK, CONTROL_ADDR, false);
	if (error)              // if address error
		return error;         // return error code

	/* perform the JMP operation */
	PC = (EA1 - (uint32_t*)&memory->memory[0]);

	switch (utils->eff_addr_code(inst, 0)) {
	case 0x02:
		utils->inc_cyc(8);
		break;
	case 0x05:
		utils->inc_cyc(10);
		break;
	case 0x06:
		utils->inc_cyc(14);
		break;
	case 0x07:
		utils->inc_cyc(10);
		break;
	case 0x08:
		utils->inc_cyc(12);
		break;
	case 0x09:
		utils->inc_cyc(10);
		break;
	case 0x0a:
		utils->inc_cyc(14);
		break;
	default:
		break;
	}

	return SUCCESS;
}

int32_t JSR() {
	int32_t error = eff_addr(WORD_MASK, CONTROL_ADDR, false);
	if (error)              // if address error
		return error;         // return error code

	// push the longword address immediately following PC on the system stack
	// then change the PC
	A[utils->a_reg(7)] -= 4;
	utils->put((uint32_t*)&memory->memory[A[utils->a_reg(7)]], PC, LONG_MASK);

	// set address to stop program execution if user selects "Step Over"
	if (sstep && stepToAddr == 0) {  // if "Step Over" mode
		trace = false;              // do not trace through subroutine
		stepToAddr = PC;
	}

	PC = (EA1 - (uint32_t*)&memory->memory[0]);

	switch (utils->eff_addr_code(inst, 0)) {
	case 0x02:
		utils->inc_cyc(16);
		break;
	case 0x05:
		utils->inc_cyc(18);
		break;
	case 0x06:
		utils->inc_cyc(22);
		break;
	case 0x07:
		utils->inc_cyc(18);
		break;
	case 0x08:
		utils->inc_cyc(20);
		break;
	case 0x09:
		utils->inc_cyc(18);
		break;
	case 0x0a:
		utils->inc_cyc(22);
		break;
	default:
		break;
	}

	return SUCCESS;

}

int32_t RTE() {
	uint32_t temp;

	if (!(SR & sbit))
		return (NO_PRIVILEGE);

	utils->mem_request(&A[8], WORD_MASK, &temp);
	SR = temp & WORD_MASK;
	utils->mem_request(&A[8], LONG_MASK, &PC);

	utils->inc_cyc(20);

	return SUCCESS;

}

int32_t RTR() {
	uint32_t temp;

	utils->mem_request(&A[utils->a_reg(7)], BYTE_MASK, &temp);
	SR = (SR & 0xff00) | (temp & 0xff);

	utils->mem_request(&A[utils->a_reg(7)], LONG_MASK, &PC);

	utils->inc_cyc(20);

	return SUCCESS;

}

int32_t RTS() {

	utils->mem_request(&A[utils->a_reg(7)], LONG_MASK, &PC);

	utils->inc_cyc(16);

	return SUCCESS;

}

int32_t NOP() {

	utils->inc_cyc(4);

	return SUCCESS;

}
