/*
 * UTILS.h
 *
 *  Created on: Jun 13, 2021
 *      Author: jsymolon
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include "def.h"
#include "Memory.h"

extern bool ROMMap, ReadMap, ProtectedMap, InvalidMap;

class UTILS {
public:
	const std::string vformat(const char * const zcFormat, ...);

	int32_t to_2s_comp(uint32_t number, int32_t size, uint32_t *result);
	int32_t from_2s_comp(uint32_t number, int32_t size, uint32_t *result);
	int32_t sign_extend(int32_t number, int32_t size_from, uint32_t *result);
	void inc_cyc(int32_t num);
	int32_t eff_addr_code(int32_t inst, int32_t start);
	int32_t a_reg(int32_t reg_num);
	int32_t memoryMapCheck(maptype mapt, uint32_t loc, int32_t bytes);
	int32_t mem_put(int32_t data, uint32_t loc, int32_t size);
	int32_t mem_req(uint32_t loc, int32_t size, uint32_t *result);
	int32_t mem_request(uint32_t *loc, int32_t size, uint32_t *result);
	void put(uint32_t *dest, int32_t source, int32_t size);
	void value_of(uint32_t *EA, uint32_t *EV, int32_t size);
	int32_t cc_update(int32_t x, int32_t n, int32_t z, int32_t v, int32_t c, int32_t source, int32_t dest,
			int32_t result, int32_t sizeMask, int32_t shiftCount);
	int32_t check_condition(int32_t condition);

	uint8_t flip(uint8_t *n);
	uint8_t flip(uint8_t &n);

};

#endif /* UTILS_H_ */
