/***************************** 68000 SIMULATOR ****************************

 File Name: CODE6.C
 Version: 1.0

 The instructions implemented in this file are the logical arithmetic
 operations:

 AND, ANDI, ANDI_TO_CCR, ANDI_TO_SR, OR, ORI, ORI_TO_CCR,
 ORI_TO_SR, EOR, EORI, EORI_TO_CCR, EORI_TO_SR, NOT

 Modified by: Charles Kelly
 www.easy68k.com

 ***************************************************************************/

#include <stdio.h>
#include "extern.h"         /* contains global "extern" declarations */
#include "PROTO.H"

int32_t AND() {
	int32_t addr_modes_mask, reg;
	int32_t size;

	addr_modes_mask = (inst & 0x0100) ? MEM_ALT_ADDR : DATA_ADDR;

	if (decode_size(&size))
		return (BAD_INST);	// bad instruction format

	int32_t error = eff_addr(size, addr_modes_mask, true);
	if (error)              // if address error
		return error;         // return error code

	reg = (inst >> 9) & 0x0007;

	if (inst & 0x0100) {
		source = D[reg] & size;
		dest = EV1 & size;
		utils->put(EA1, dest & source, size);
		utils->value_of(EA1, &result, size);
	} else {
		source = EV1 & size;
		dest = D[reg] & size;
		utils->put(&D[reg], dest & source, size);
		result = D[reg] & size;
	}

	utils->cc_update(N_A, GEN, GEN, ZER, ZER, source, dest, result, size, 0);

	if (inst & 0x0100)
		utils->inc_cyc(((uint32_t)size == LONG_MASK) ? 12 : 8);
	else {
		if ((uint32_t)size == LONG_MASK) {
			if ((!(inst & 0x0030)) || ((inst & 0x003f) == 0x003c))
				utils->inc_cyc(8);
			else
				utils->inc_cyc(6);
		} else {
			utils->inc_cyc(4);
		}
	}

	return SUCCESS;

}

int32_t ANDI() {
	int32_t size;

	if (decode_size(&size))
		return (BAD_INST); /* bad instruction format */

	utils->mem_request(&PC, size, &source);

	int32_t error = eff_addr(size, DATA_ALT_ADDR, true);
	if (error)              // if address error
		return error;         // return error code

	dest = EV1 & size;

	utils->put(EA1, source & dest, size);
	utils->value_of(EA1, &result, size);

	utils->cc_update(N_A, GEN, GEN, ZER, ZER, source, dest, result, size, 0);

	if (inst & 0x0038)
		utils->inc_cyc(((uint32_t)size == LONG_MASK) ? 20 : 12);
	else
		utils->inc_cyc(((uint32_t)size == LONG_MASK) ? 16 : 8);

	return SUCCESS;

}

int32_t ANDI_TO_CCR() {
	uint32_t temp;

	utils->mem_request(&PC, WORD_MASK, &temp);

	SR &= temp | 0xff00;

	utils->inc_cyc(20);

	return SUCCESS;

}

int32_t ANDI_TO_SR() {
	uint32_t temp;

	if (!(SR & sbit))
		return (NO_PRIVILEGE);

	utils->mem_request(&PC, WORD_MASK, &temp);
	SR &= temp;

	utils->inc_cyc(20);

	return SUCCESS;

}

int32_t OR() {
	int32_t size;
	int32_t mask, reg;

	mask = (inst & 0x0100) ? MEM_ALT_ADDR : DATA_ADDR;

	if (decode_size(&size))
		return (BAD_INST);	// bad instruction format

	int32_t error = eff_addr(size, mask, true);
	if (error)              // if address error
		return error;         // return error code

	reg = (inst >> 9) & 0x0007;

	if (inst & 0x0100) {
		source = D[reg] & size;
		dest = EV1 & size;
		utils->put(EA1, source | dest, size);
		utils->value_of(EA1, &result, size);
	} else {
		source = EV1 & size;
		dest = D[reg] & size;
		utils->put(&D[reg], source | dest, size);
		result = D[reg] & size;
	}

	utils->cc_update(N_A, GEN, GEN, ZER, ZER, source, dest, result, size, 0);

	if (inst & 0x0100)
		utils->inc_cyc(((uint32_t)size == LONG_MASK) ? 12 : 8);
	else {
		if ((uint32_t)size == LONG_MASK) {
			if ((!(inst & 0x0030)) || ((inst & 0x003f) == 0x003c))
				utils->inc_cyc(8);
			else
				utils->inc_cyc(6);
		} else
			utils->inc_cyc(4);
	}

	return SUCCESS;

}

//---------------------------------------------------------------------------
int32_t ORI() {
	int32_t size;
	int32_t error;

	if (decode_size(&size))
		return (BAD_INST);			// bad instruction format

	utils->mem_request(&PC, size, &source);

	error = eff_addr(size, DATA_ALT_ADDR, true);
	if (error)
		return (error);			// return error code

	dest = EV1 & size;

	utils->put(EA1, source | dest, size);
	utils->value_of(EA1, &result, size);

	utils->cc_update(N_A, GEN, GEN, ZER, ZER, source, dest, result, size, 0);

	if (inst & 0x0038) {
		utils->inc_cyc(((uint32_t)size == LONG_MASK) ? 20 : 12);
	} else {
		utils->inc_cyc(((uint32_t)size == LONG_MASK) ? 16 : 8);
	}

	return SUCCESS;

}

int32_t ORI_TO_CCR() {
	uint32_t temp;

	utils->mem_request(&PC, WORD_MASK, &temp);

	SR |= temp;

	utils->inc_cyc(20);

	return SUCCESS;

}

int32_t ORI_TO_SR() {
	uint32_t temp;

	if (!(SR & sbit))
		return (NO_PRIVILEGE);

	utils->mem_request(&PC, WORD_MASK, &temp);
	SR |= temp;

	utils->inc_cyc(20);

	return SUCCESS;

}

int32_t EOR() {
	int32_t size;
	int32_t reg;

	if (decode_size(&size))
		return (BAD_INST);	// bad instruction format

	int32_t error = eff_addr(size, DATA_ALT_ADDR, true);
	if (error)              // if address error
		return error;         // return error code

	reg = (inst >> 9) & 0x0007;

	source = D[reg] & size;
	dest = EV1 & size;

	utils->put(EA1, EV1 ^ D[reg], size);
	utils->value_of(EA1, &result, size);

	utils->cc_update(N_A, GEN, GEN, ZER, ZER, source, dest, result, size, 0);

	if (inst & 0x0038)
		utils->inc_cyc(((uint32_t)size == LONG_MASK) ? 12 : 8);
	else
		utils->inc_cyc(((uint32_t)size == LONG_MASK) ? 8 : 4);

	return SUCCESS;

}

int32_t EORI() {
	int32_t size;

	if (decode_size(&size))
		return (BAD_INST);	       // bad instruction format

	utils->mem_request(&PC, size, &source);

	int32_t error = eff_addr(size, DATA_ALT_ADDR, true);
	if (error)              // if address error
		return error;         // return error code

	dest = EV1 & size;

	utils->put(EA1, source ^ dest, size);
	utils->value_of(EA1, &result, size);

	utils->cc_update(N_A, GEN, GEN, ZER, ZER, source, dest, result, size, 0);

	if (inst & 0x0038) {
		utils->inc_cyc(((uint32_t)size == LONG_MASK) ? 20 : 12);
	} else {
		utils->inc_cyc(((uint32_t)size == LONG_MASK) ? 16 : 8);
	}

	return SUCCESS;

}

int32_t EORI_TO_CCR() {
	uint32_t temp;

	utils->mem_request(&PC, WORD_MASK, &temp);

	SR ^= temp;

	utils->inc_cyc(20);

	return SUCCESS;

}

int32_t EORI_TO_SR() {
	uint32_t temp;

	if (!(SR & sbit))
		return (NO_PRIVILEGE);

	utils->mem_request(&PC, WORD_MASK, &temp);
	SR ^= temp;

	utils->inc_cyc(20);

	return SUCCESS;

}

int32_t NOT() {
	int32_t size;

	if (decode_size(&size))
		return (BAD_INST);	// bad instruction format

	int32_t error = eff_addr(size, DATA_ALT_ADDR, true);
	if (error)              // if address error
		return error;         // return error code

	source = dest = EV1 & size;

	/* perform the NOT operation */
	utils->put(EA1, ~dest, size);
	utils->value_of(EA1, &result, size);

	utils->cc_update(N_A, GEN, GEN, ZER, ZER, source, dest, result, size, 0);

	if (inst & 0x0030) {
		utils->inc_cyc(((uint32_t)size == LONG_MASK) ? 12 : 8);
	} else {
		utils->inc_cyc(((uint32_t)size == LONG_MASK) ? 6 : 4);
	}

	return SUCCESS;

}

