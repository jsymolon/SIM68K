/***************************** 68000 SIMULATOR ****************************

 File Name: CODE1.C
 Version: 1.0

 The instructions implemented in this file are the MOVE instructions:

 MOVE, MOVEP, MOVEA, MOVE_FR_SR, MOVE_TO_CCR, MOVE_TO_SR, MOVEM,
 MOVE_USP, MOVEQ

 Modified by: Charles Kelly
 www.easy68k.com

 ***************************************************************************/

#include <stdio.h>
#include "extern.h"         /* contains global "extern" declarations */
#include "PROTO.H"

/* the following two arrays specify the execution times of the MOVE
 instruction, for BYTE_MASK/WORD_MASK operands and for int32_t operands */

int32_t move_bw_times[12][9] = { 4, 4, 8, 8, 8, 12, 14, 12, 16, 4, 4, 8, 8, 8, 12, 14, 12, 16, 8, 8, 12, 12, 12, 16, 18, 16, 20, 8,
		8, 12, 12, 12, 16, 18, 16, 20, 10, 10, 14, 14, 14, 18, 20, 18, 22, 12, 12, 16, 16, 16, 20, 22, 20, 24, 14, 14, 18, 18, 18, 22,
		24, 22, 26, 12, 12, 16, 16, 16, 20, 22, 20, 24, 16, 16, 20, 20, 20, 24, 26, 24, 28, 12, 12, 16, 16, 16, 20, 22, 20, 24, 14,
		14, 18, 18, 18, 22, 24, 22, 26, 8, 8, 12, 12, 12, 16, 18, 16, 20 };

int32_t move_l_times[12][9] = { 4, 4, 12, 12, 12, 16, 18, 16, 20, 4, 4, 12, 12, 12, 16, 18, 16, 20, 12, 12, 20, 20, 20, 24, 26, 24,
		28, 12, 12, 20, 20, 20, 24, 26, 24, 28, 14, 14, 22, 22, 22, 26, 28, 26, 30, 16, 16, 24, 24, 24, 28, 30, 28, 32, 18, 18, 26,
		26, 26, 30, 32, 30, 34, 16, 16, 24, 24, 24, 28, 30, 28, 32, 20, 20, 28, 28, 28, 32, 34, 32, 36, 16, 16, 24, 24, 24, 28, 30,
		28, 32, 18, 18, 26, 26, 26, 30, 32, 30, 34, 12, 12, 20, 20, 20, 24, 26, 24, 28 };

/* the following two arrays specify the instruction execution times
 for the MOVEM instruction for memory-to-reg and reg-to-memory cases */

int32_t movem_t_r_times[11] = { 0, 0, 12, 12, 0, 16, 18, 16, 20, 16, 18 };

int32_t mover_t_m_times[11] = { 0, 0, 8, 0, 8, 12, 14, 12, 16, 0, 0 };

//----------------------------------------------------------------------------
int32_t MOVE() {
	int32_t size; /* 'size' holds the instruction size */
	int32_t src;
	int32_t dst; /* 'src' and 'dst' hold the addressing mode codes */
	/* for instruction execution time computation */

	/* MOVE has a different format for size field than all other instructions */
	/* so we can't use the 'decode_size' function */
	switch ((inst >> 12) & 0x03) {
	case 0x01:
		size = BYTE_MASK; /* bit pattern '01' */
		break;
	case 0x03:
		size = WORD_MASK; /* bit pattern '10' */
		break;
	case 0x02:
		size = LONG_MASK; /* bit pattern '11' */
		break;
	default:
		return (BAD_INST); /* bad size field */
	}

// the following gets the effective addresses for the source and destination operands
	int32_t error = eff_addr(size, ALL_ADDR, false);
	if (error)              // if address error
		return (error);         // return (error) code

	error = eff_addr(size, DATA_ALT_ADDR, false);
	if (error)              // if address error
		return (error);         // return (error) code

	dest = EV2; /* set 'dest' for use in 'cc_update' */

	utils->put(EA2, EV1, size); /* perform the move to '*EA2' */
	utils->value_of(EA2, &EV2, size); /* set 'EV2' for use in 'cc_update' */

	src = utils->eff_addr_code(inst, 0); /* get the addressing mode codes */
	dst = utils->eff_addr_code(inst, 6);

	if (static_cast<uint32_t>(size) == LONG_MASK) /* use the codes in instruction time computation */
		utils->inc_cyc(move_l_times[src][dst]);
	else
		utils->inc_cyc(move_bw_times[src][dst]);

	/* now update the condition codes */
	utils->cc_update(N_A, GEN, GEN, ZER, ZER, EV1, dest, EV2, size, 0);

	/* return the value for 'success' */
	return (SUCCESS);
}

//----------------------------------------------------------------------------
int32_t MOVEP() {
	int32_t address;
	int32_t Dx;
	int32_t disp;
	int32_t count;
	int32_t direction;
	int32_t reg;
	uint32_t temp;
	int32_t size;

	if ((inst & 0x100) == 0)      // ck v2.3
		return (BAD_INST);

	utils->mem_request(&PC, WORD_MASK, &temp);
	utils->from_2s_comp(temp, WORD_MASK, &temp);

	address = A[utils->a_reg(inst & 0x07)] + temp;

	direction = inst & 0x80;

	if (inst & 0x40) {
		size = LONG_MASK;
		count = 4;
	} else {
		size = WORD_MASK;
		count = 2;
	}

	reg = (inst >> 9) & 0x07;
	Dx = D[reg] & size;

	for (; count > 0; count--) {
		disp = 8 * (count - 1);
		if (direction)
			utils->mem_put(((Dx >> disp) & BYTE_MASK), address, BYTE_MASK);
		else {
			utils->mem_req(address, BYTE_MASK, &temp);
			switch (count) {
			case 4:
				D[reg] = (D[reg] & 0x00ffffff) | (temp * 0x1000000);
				break;
			case 3:
				D[reg] = (D[reg] & 0xff00ffff) | (temp * 0x10000);
				break;
			case 2:
				D[reg] = (D[reg] & 0xffff00ff) | (temp * 0x100);
				break;
			case 1:
				D[reg] = (D[reg] & 0xffffff00) | (temp);
				break;
			}
		}
		address += 2;
	}

	utils->inc_cyc((static_cast<uint32_t>(size) == LONG_MASK) ? 24 : 16);
	return (SUCCESS);
}

//----------------------------------------------------------------------------
int32_t MOVEA() {
	int32_t size;
	int32_t src;

	if (inst & 0x1000)
		size = WORD_MASK;
	else
		size = LONG_MASK;

	src = utils->eff_addr_code(inst, 0);
	if (size == WORD_MASK)
		utils->inc_cyc(move_bw_times[src][1]);
	else
		utils->inc_cyc(move_l_times[src][1]);

	int32_t error = eff_addr(size, ALL_ADDR, false);
	if (error)              // if address error
		return (error);         // return (error) code

	if (size == WORD_MASK)
		utils->sign_extend(EV1, WORD_MASK, &EV1);

	A[utils->a_reg((inst >> 9) & 0x07)] = EV1;

	return (SUCCESS);

}

//----------------------------------------------------------------------------
int32_t MOVE_FR_SR() {

	int32_t error = eff_addr(WORD_MASK, DATA_ALT_ADDR, true);
	if (error)              // if address error
		return (error);         // return (error) code

	utils->put(EA1, SR, WORD_MASK);
	utils->inc_cyc((inst & 0x0030) ? 8 : 6);
	return (SUCCESS);
}

//----------------------------------------------------------------------------
int32_t MOVE_TO_CCR() {
	int32_t error = eff_addr(WORD_MASK, DATA_ADDR, true);
	if (error)              // if address error
		return (error);         // return (error) code

	utils->put((uint32_t*) &SR, EV1, BYTE_MASK);
	utils->inc_cyc(12);

	return (SUCCESS);
}

//----------------------------------------------------------------------------
int32_t MOVE_TO_SR() {
	if (!(SR & sbit))
		return (NO_PRIVILEGE);

	int32_t error = eff_addr(WORD_MASK, DATA_ADDR, true);
	if (error)              // if address error
		return (error);         // return (error) code

	utils->put((uint32_t*) &SR, EV1, WORD_MASK);
	utils->inc_cyc(12);
	return (SUCCESS);
}

//------------------------------------------------------------------
// ck April 15, 2002 Fixed bug in MOVEM.L (A7)+/Dn-Dn
// CK 5-1-2007 bug fix when destination An is included in register list
int32_t MOVEM() {
	int32_t direction;
	int32_t addr_modes_mask;
	int32_t counter;
	int32_t addr_mode;
	int32_t displacement;
	int32_t address;
	int32_t total_displacement;
	uint32_t size;
	uint32_t mask_list;
	uint32_t temp;
	uint saveAn = A[utils->a_reg(inst & 0x7)]; // save possible destination (CK 5-1-2007)

	utils->mem_request(&PC, WORD_MASK, &mask_list);

	if (inst & 0x0040)
		size = LONG_MASK;
	else
		size = WORD_MASK;

	if ((direction = (inst & 0x0400)) != 0)
		addr_modes_mask = CONTROL_ADDR | bit_4;
	else
		addr_modes_mask = CONT_ALT_ADDR | bit_5;

	int32_t error = eff_addr(size, addr_modes_mask, false);
	if (error)              // if address error
		return (error);         // return (error) code

	address = (EA1 - (uint32_t*) &memory->memory[0]);
	total_displacement = address;

	if ((inst & 0x0038) != 0x20) {
		if (size == WORD_MASK)
			displacement = 2;
		else
			displacement = 4;
	} else {
		if (size == WORD_MASK)
			displacement = -2;
		else
			displacement = -4;
	}

	addr_mode = utils->eff_addr_code(inst, 0);

	if (direction)
		utils->inc_cyc(movem_t_r_times[addr_mode]);       // memory to registers
	else
		utils->inc_cyc(mover_t_m_times[addr_mode]);	// registers to memory

	for (counter = 0; counter < 16; counter++) {
		if (mask_list & (1 << counter)) {
			if (size == LONG_MASK)
				utils->inc_cyc(8);
			else
				utils->inc_cyc(4);
			if (direction) {                          // if memory to registers
				if (size == WORD_MASK) { // if size is WORD_MASK then sign-extend
					utils->mem_req(address, WORD_MASK, &temp);
					utils->sign_extend(temp, WORD_MASK, &temp);   // ck 8-10-2005
				} else
					// ck added this mem_req
					utils->mem_req(address, LONG_MASK, &temp);
				if (counter < 8)
					D[counter] = temp;
				else
					A[utils->a_reg(counter - 8)] = temp;
			} else {                                // else, registers to memory
				if ((inst & 0x38) == 0x20) {            // if -(An)
					if (counter < 8)
						if ((inst & 0x7) == (7 - counter)) // if writing destination An (CK 5-1-2007)
							utils->mem_put(saveAn, address, size);
						else
							utils->mem_put(A[utils->a_reg(7 - counter)], address, size);
					else
						utils->mem_put(D[15 - counter], address, size);
				} else {
					if (counter < 8)
						utils->mem_put(D[counter], address, size);
					else
						utils->mem_put(A[utils->a_reg(counter - 8)], address, size);
				}
			}
			address += displacement;
		}
	}
	//address -= displacement;    // CK 5-1-2007
	total_displacement = address - total_displacement;

	// if pre-decrement or post-increment modes then change the value
	// of the address register appropriately
	if (((inst & 0x38) == 0x20) || ((inst & 0x38) == 0x18)) {
		A[utils->a_reg(inst & 0x7)] = saveAn; // restore incase it was also destination
		A[utils->a_reg(inst & 0x7)] += total_displacement;
	}
	return (SUCCESS);

}

//----------------------------------------------------------------------------
int32_t MOVE_USP() {
	int32_t reg;

	if (!(SR & sbit))
		return (NO_PRIVILEGE); /* supervisor state not on */

	reg = inst & 0x7;
	if (reg == 7)
		reg = 8;

	if (inst & 0x8)
		A[reg] = A[7];
	else
		A[7] = A[reg];

	utils->inc_cyc(4);

	return (SUCCESS);

}

//----------------------------------------------------------------------------
int32_t MOVEQ() {
	int32_t reg;

	reg = (inst >> 9) & 0x7;
	source = inst & 0xff;
	dest = D[reg];

	/* the data register is sign extended to a longword */
	utils->sign_extend(source, BYTE_MASK, &D[reg]);
	utils->sign_extend(D[reg], WORD_MASK, &D[reg]);

	utils->cc_update(N_A, GEN, GEN, ZER, ZER, source, dest, D[reg], LONG_MASK, 0);
	utils->inc_cyc(4);
	return (SUCCESS);

}
