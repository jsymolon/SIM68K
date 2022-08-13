/***************************** 68000 SIMULATOR ****************************

 File Name: CODE3.C
 Version: 1.0

 The instructions implemented in this file are the integer arithmetic
 operations:

 ADD, ADDA, ADDI, ADDQ, ADDX, SUB, SUBA, SUBI, SUBQ, SUBX

 Modified by: Charles Kelly
 www.easy68k.com

 ***************************************************************************/

#include <stdio.h>
#include "extern.h"         /* contains global "extern" declarations */
#include "PROTO.H"

int32_t ADD() {
	int32_t addr_modes_mask; /* holds mask for use in 'eff_addr()' */
	int32_t reg; /* holds data register number */
	int32_t size; /* holds instruction size */
	int32_t error;

	/* compute addressing modes mask from appropriate bit in instruction WORD_MASK */
	addr_modes_mask = (inst & 0x0100) ? MEM_ALT_ADDR : ALL_ADDR;

	/* the following statement decodes the instruction size using */
	/* decode_size(), then decodes the effective address using eff_addr() */
	if (decode_size(&size)) 	// if size is bad then return 'bad instruction'
		return (BAD_INST);

	error = eff_addr(size, addr_modes_mask, true);
	if (error)              // if address error
		return error;         // return error code

	reg = (inst >> 9) & 0x0007; /* get data register number */

	/* now perform the addition according to instruction format */
	/* instruction bit 8 'on' means data register to effective-address */
	/* instruction bit 8 'off' means effective-address to data register */
	if (inst & 0x0100) {
		source = D[reg];
		dest = EV1;
		utils->put(EA1, source + dest, size); /* use 'put' to deposit result */
		utils->value_of(EA1, &result, size); /* set 'result' for use in 'cc_update' */
	} else {
		source = EV1; /* get source. 'EV1' was set in 'eff_addr()' */
		dest = D[reg]; /* get destination */
		utils->put(&D[reg], source + dest, size);
		result = D[reg]; /* set 'result' for use in 'cc_update()' */
	}

	/* update the condition codes */
	utils->cc_update(GEN, GEN, GEN, CASE_1, CASE_5, source, dest, result, size, 0);

	/* now update the cycle counter appropriately depending on the instruction */
	/* size and the instruction format */
	if (inst & 0x0100) {          // if (<ea>)+(<Dn>) --> <ea>
		utils->inc_cyc(((uint32_t)size == LONG_MASK) ? 12 : 8);
	} else {
		if ((uint32_t)size == LONG_MASK) {
			if ((!(inst & 0x0030)) || ((inst & 0x003f) == 0x003c))
				utils->inc_cyc(8);
			else
				utils->inc_cyc(6);
		} else {
			utils->inc_cyc(4);
		}
	}

	/* return 'success' */
	return SUCCESS;

}

int32_t ADDA() {
	int32_t size;
	int32_t reg;

	if (inst & 0x0100)
		size = LONG_MASK;
	else
		size = WORD_MASK;

	int32_t error = eff_addr(size, ALL_ADDR, true);
	if (error)              // if address error
		return error;         // return error code

	reg = (inst >> 9) & 0x0007;

	if (size == WORD_MASK)                          // ck 1/22/2003
		utils->sign_extend(EV1, WORD_MASK, &EV1);

	source = EV1;
	dest = A[utils->a_reg(reg)];

	//put (&A[utils->a_reg(reg)], source + dest, size);    CK 11/6/2002
	utils->put(&A[utils->a_reg(reg)], source + dest, LONG_MASK); // always uses 32bits of Areg

	if ((uint32_t)size == LONG_MASK) {
		if ((!(inst & 0x0030)) || ((inst & 0x003f) == 0x003c))
			utils->inc_cyc(8);
		else
			utils->inc_cyc(6);
	} else
		utils->inc_cyc(8);

	return SUCCESS;

}

//--------------------------------------------------------------------------
int32_t ADDI() {
	int32_t size;

	if (decode_size(&size))
		return (BAD_INST);			// bad instruction format

	utils->mem_request(&PC, size, &source);

	int32_t error = eff_addr(size, DATA_ALT_ADDR, true);
	if (error)              // if address error
		return error;         // return error code

	dest = EV1;
	utils->put(EA1, source + dest, size);
	utils->value_of(EA1, &result, size);
	utils->cc_update(GEN, GEN, GEN, CASE_1, CASE_5, source, dest, result, size, 0);

	if (inst & 0x0038) {
		utils->inc_cyc(((uint32_t)size == LONG_MASK) ? 20 : 12);
	} else {
		utils->inc_cyc(((uint32_t)size == LONG_MASK) ? 16 : 8);
	}
	return SUCCESS;
}

//----------------------------------------------------------------------------
int32_t ADDQ() {
	int32_t size;

	if (decode_size(&size))
		return (BAD_INST); /* bad size format */

	if ((inst & 0x38) == 0x8) /* if address reg direct, operation is int32_t */
		size = LONG_MASK;

	int32_t error = eff_addr(size, ALTERABLE_ADDR, true);
	if (error)              // if address error
		return error;         // return error code

	source = ((inst >> 9) & 0x07);
	if (source == 0) /* if source is '0', that corresponds to '8' */
		source = 8;

	dest = EV1;

	utils->put(EA1, source + dest, size);
	utils->value_of(EA1, &result, size);

	if (!((inst & 0x38) == 0x8)) /* if address reg direct, cc's not affected */
		utils->cc_update(GEN, GEN, GEN, CASE_1, CASE_5, source, dest, result, size, 0);

	switch (inst & 0x0038) {
	case 0x0:
		utils->inc_cyc(((uint32_t)size == LONG_MASK) ? 8 : 4);
		break;
	case 0x8:
		utils->inc_cyc(8);        // CK 12-17-2005
		break;
	default:
		utils->inc_cyc(((uint32_t)size == LONG_MASK) ? 12 : 8);
		break;
	}

	return SUCCESS;

}

//----------------------------------------------------------------------------
int32_t ADDX() {
	int32_t size;
	int32_t Rx, Ry, decrement = 1;

	if (decode_size(&size))
		return (BAD_INST);

	Ry = inst & 0x0007;         // source
	Rx = (inst >> 9) & 0x0007;  // destination

	// perform the ADDX operation
	if (inst & 0x0008) {        // -(Ay), -(Ax) addressing mode
		Rx = utils->a_reg(Rx);
		Ry = utils->a_reg(Ry);
		if (size == WORD_MASK)
			decrement = 2;
		if ((uint32_t)size == LONG_MASK)
			decrement = 4;
		A[Ry] -= decrement;
		utils->mem_req( A[Ry], size, &source);
		A[Rx] -= decrement;
		if (utils->mem_req( A[Rx], size, &dest) == BUS_ERROR)
			A[Rx] += decrement; // Bus Error on destination does not decrement An
		else {
			utils->put((uint32_t*) &memory->memory[A[Rx]], source + dest + ((SR & xbit) >> 4), size);
			utils->mem_req( A[Rx], size, &result);
		}
	} else        // Dy,Dx addressing mode
	{
		source = D[Ry] & size;
		dest = D[Rx] & size;
		utils->put(&D[Rx], source + dest + ((SR & xbit) >> 4), size);
		result = D[Rx] & size;
	}

	utils->cc_update(GEN, GEN, CASE_1, CASE_1, CASE_5, source, dest, result, size, 0);

	if ((uint32_t)size == LONG_MASK)
		utils->inc_cyc((inst & 0x0008) ? 30 : 8);
	else
		utils->inc_cyc((inst & 0x0008) ? 18 : 4);

	return SUCCESS;
}

//----------------------------------------------------------------------------
int32_t SUB() {
	int32_t addr_modes_mask, reg;
	int32_t size;

	addr_modes_mask = (inst & 0x0100) ? MEM_ALT_ADDR : ALL_ADDR;

	if (decode_size(&size))
		return (BAD_INST);	// bad instruction format

	int32_t error = eff_addr(size, addr_modes_mask, true);
	if (error)              // if address error
		return error;         // return error code

	reg = (inst >> 9) & 0x0007;

	if (inst & 0x0100) {
		source = D[reg] & size;
		dest = EV1 & size;
		utils->put(EA1, dest - source, size);
		utils->value_of(EA1, &result, size);
	} else {
		source = EV1 & size;
		dest = D[reg] & size;
		utils->put(&D[reg], dest - source, size);
		result = D[reg] & size;
	}

	utils->cc_update(GEN, GEN, GEN, CASE_2, CASE_6, source, dest, result, size, 0);

	if (inst & 0x0100) {
		utils->inc_cyc(((uint32_t)size == LONG_MASK) ? 12 : 8);
	} else {
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

//----------------------------------------------------------------------------
int32_t SUBA() {
	int32_t size;
	int32_t reg;

	if (inst & 0x0100)
		size = LONG_MASK;
	else
		size = WORD_MASK;

	int32_t error = eff_addr(size, ALL_ADDR, true);
	if (error)              // if address error
		return error;         // return error code

	reg = (inst >> 9) & 0x0007;

	if (size == WORD_MASK)                          // ck 1/22/2003
		utils->sign_extend(EV1, WORD_MASK, &EV1);

	source = EV1;
	dest = A[utils->a_reg(reg)];

	utils->put(&A[utils->a_reg(reg)], dest - source, LONG_MASK); // always uses 32bits of Areg

	if ((uint32_t)size == LONG_MASK) {
		if ((!(inst & 0x0030)) || ((inst & 0x003f) == 0x003c))
			utils->inc_cyc(8);
		else
			utils->inc_cyc(6);
	} else
		utils->inc_cyc(8);

	return SUCCESS;

}

//----------------------------------------------------------------------------
int32_t SUBI() {
	int32_t size;

	if (decode_size(&size))
		return (BAD_INST);		     // bad instruction format

	utils->mem_request(&PC, size, &source);

	int32_t error = eff_addr(size, DATA_ALT_ADDR, true);
	if (error)              // if address error
		return error;         // return error code

	dest = EV1;

	utils->put(EA1, dest - source, size);
	utils->value_of(EA1, &result, size);

	utils->cc_update(GEN, GEN, GEN, CASE_2, CASE_6, source, dest, result, size, 0);

	if (inst & 0x0038) {
		utils->inc_cyc(((uint32_t)size == LONG_MASK) ? 20 : 12);
	} else {
		utils->inc_cyc(((uint32_t)size == LONG_MASK) ? 16 : 8);
	}

	return SUCCESS;

}

//----------------------------------------------------------------------------
int32_t SUBQ() {
	int32_t size;

	if (decode_size(&size))
		return (BAD_INST); /* bad size format */

	if ((inst & 0x38) == 0x8) /* if address reg direct, operation is int32_t */
		size = LONG_MASK;

	int32_t error = eff_addr(size, ALTERABLE_ADDR, true);
	if (error)              // if address error
		return error;         // return error code

	source = ((inst >> 9) & 0x07);
	if (source == 0) /* if source is '0', that corresponds to '8' */
		source = 8;

	dest = EV1;

	utils->put(EA1, dest - source, size);
	utils->value_of(EA1, &result, size);

	if (!((inst & 0x38) == 0x8)) /* if address reg direct, cc's not affected */
		utils->cc_update(GEN, GEN, GEN, CASE_2, CASE_6, source, dest, result, size, 0);

	switch (inst & 0x0038) {
	case 0x0:
		utils->inc_cyc(((uint32_t)size == LONG_MASK) ? 8 : 4);
		break;
	case 0x8:
		utils->inc_cyc(8);        // CK 12-17-2005
		break;
	default:
		utils->inc_cyc(((uint32_t)size == LONG_MASK) ? 12 : 8);
		break;
	}

	return SUCCESS;

}

//----------------------------------------------------------------------------
int32_t SUBX() {
	int32_t size;
	int32_t Rx, Ry, decrement = 1;

	if (decode_size(&size))
		return (BAD_INST);

	Ry = inst & 0x0007;           // source
	Rx = (inst >> 9) & 0x0007;    // destination

	// perform the SUBX operation
	if (inst & 0x0008) {        // -(Ay),-(Ax) addressing mode
		Rx = utils->a_reg(Rx);
		Ry = utils->a_reg(Ry);
		if (size == WORD_MASK)
			decrement = 2;
		if ((uint32_t)size == LONG_MASK)
			decrement = 4;
		A[Ry] -= decrement;
		utils->mem_req(A[Ry], size, &source);
		A[Rx] -= decrement;
		if (utils->mem_req( A[Rx], size, &dest) == BUS_ERROR)
			A[Rx] += decrement; // Bus Error on destination does not decrement An
		else {
			utils->put((uint32_t*)&memory->memory[A[Rx]], dest - source - ((SR & xbit) >> 4), size);
			utils->mem_req( A[Rx], size, &result);
		}
	} else {      // Dy,Dx addressing mode
		source = D[Ry] & size;
		dest = D[Rx] & size;
		utils->put(&D[Rx], dest - source - ((SR & xbit) >> 4), size);
		result = D[Rx] & size;
	}

	utils->cc_update(GEN, GEN, CASE_1, CASE_2, CASE_6, source, dest, result, size, 0);

	if ((uint32_t)size == LONG_MASK)
		utils->inc_cyc((inst & 0x0008) ? 30 : 8);
	else
		utils->inc_cyc((inst & 0x0008) ? 18 : 4);

	return SUCCESS;

}
