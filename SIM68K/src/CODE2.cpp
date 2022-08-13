/***************************** 68000 SIMULATOR ****************************

 File Name: CODE2.C
 Version: 1.0

 The instructions implemented in this file are the data movement instructions
 other than the MOVE instructions:

 EXG, LEA, PEA, LINK, UNLK

 Modified by: Charles Kelly
 www.easy68k.com

 ***************************************************************************/

#include <stdio.h>
#include "extern.h"         /* contains global "extern" declarations */
#include "PROTO.H"

//----------------------------------------------------------------------------
int32_t EXG() {
	int32_t temp_reg;
	int32_t Rx, Ry;

	Rx = (inst >> 9) & 0x07;
	Ry = inst & 0x07;
	switch ((inst >> 3) & 0x1f) {
	case 0x08:
		temp_reg = D[Rx];
		D[Rx] = D[Ry];
		D[Ry] = temp_reg;
		break;
	case 0x09:
		temp_reg = A[utils->a_reg(Rx)];
		A[utils->a_reg(Rx)] = A[utils->a_reg(Ry)];
		A[utils->a_reg(Ry)] = temp_reg;
		break;
	case 0x11:
		temp_reg = D[Rx];
		D[Rx] = A[utils->a_reg(Ry)];
		A[utils->a_reg(Ry)] = temp_reg;
		break;
	default:
		return (BAD_INST); /* bad op_mode field */
	}

	utils->inc_cyc(6);
	return SUCCESS;
}

//------------------------------------------------------------------------
//  LEA
//  ck. Changed size to BYTE_MASK to prevent address error when effective
//      address was odd and eff_addr called value_of.
int32_t LEA() {
	int32_t reg;

	reg = (inst >> 9) & 0x07;

	if (eff_addr_noread(BYTE_MASK, CONTROL_ADDR, false))
		return (BAD_INST);		// bad instruction format

	// perform the LEA operation
	A[utils->a_reg(reg)] = (EA1 - (uint32_t*) &memory->memory[0]);
	if ((inst & 0x003F) == 0x0038)  // if Abs.W   ck 2.9.3
		utils->sign_extend(A[utils->a_reg(reg)], WORD_MASK, &A[utils->a_reg(reg)]);

	switch (utils->eff_addr_code(inst, 0)) {
	case 0x02:
		utils->inc_cyc(4);
		break;
	case 0x05:
		utils->inc_cyc(8);
		break;
	case 0x06:
		utils->inc_cyc(12);
		break;
	case 0x07:
		utils->inc_cyc(8);
		break;
	case 0x08:
		utils->inc_cyc(12);
		break;
	case 0x09:
		utils->inc_cyc(8);
		break;
	case 0x0a:
		utils->inc_cyc(12);
		break;
	}
	return SUCCESS;
}

//----------------------------------------------------------------------------
int32_t PEA() {
	uint32_t ea;

	if (eff_addr_noread(LONG_MASK, CONTROL_ADDR, false))
		return (BAD_INST);		// bad instruction format

	// push the longword address computed by the
	// effective address routine onto the stack

	A[utils->a_reg(7)] -= 4;

	ea = (EA1 - (uint32_t*) &memory->memory[0]);
	if ((inst & 0x003F) == 0x0038)  // if Abs.W  ck 2.9.3
		utils->sign_extend(ea, WORD_MASK, &ea);

	utils->put((uint32_t*) &memory->memory[A[utils->a_reg(7)]], ea, LONG_MASK);

	switch (utils->eff_addr_code(inst, 0)) {
	case 0x02:
		utils->inc_cyc(12);
		break;
	case 0x05:
		utils->inc_cyc(16);
		break;
	case 0x06:
		utils->inc_cyc(20);
		break;
	case 0x07:
		utils->inc_cyc(16);
		break;
	case 0x08:
		utils->inc_cyc(20);
		break;
	case 0x09:
		utils->inc_cyc(16);
		break;
	case 0x0a:
		utils->inc_cyc(20);
		break;
	}
	return SUCCESS;
}

//----------------------------------------------------------------------------
int32_t LINK() {
	uint32_t reg;
	uint32_t temp, displacement;

	reg = inst & 0x07;

	utils->mem_request(&PC, WORD_MASK, &temp);
	utils->from_2s_comp(temp, WORD_MASK, &displacement);

	// perform the LINK operation
	A[utils->a_reg(7)] -= 4;
	utils->put((uint32_t*) &memory->memory[A[utils->a_reg(7)]], A[reg], LONG_MASK);
	A[reg] = A[utils->a_reg(7)];
	A[utils->a_reg(7)] = A[utils->a_reg(7)] + displacement;

	utils->inc_cyc(16);

	return SUCCESS;

}

//----------------------------------------------------------------------------
int32_t UNLK() {
	int32_t reg;

	reg = inst & 0x07;

	A[utils->a_reg(7)] = A[reg];
	utils->mem_req(A[utils->a_reg(7)], LONG_MASK, &A[reg]);
	A[utils->a_reg(7)] += 4;

	utils->inc_cyc(12);

	return SUCCESS;

}

