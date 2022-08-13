/*
 * Memory.h
 *
 *  Created on: May 31, 2021
 *      Author: jsymolon
 */

#ifndef MEMORY_H_
#define MEMORY_H_

// Holds the CPU's working space, source code listing and IO space
#include <string>
#include <vector>
#include <list>
#include <map>
#include <array>

// S rec
// +-------------------------//--------------------------//-----------------------+
// | type(2) | count(2) | address(4, 6, 8) |            data           | checksum |
// +-------------------------//--------------------------//-----------------------+
// type 2 char - S0 - S9
// count 2 char - hex - # char pairs
// address
// data 0 - 64
// checksum - 2 char
//S0 Record. The type of record is 'S0' (0x5330). The address field is unused and will be filled with zeros (0x0000). The header information within the data field is divided into the following subfields.
//        mname is char[20] and is the module name.
//        ver is char[2] and is the version number.
//        rev is char[2] and is the revision number.
//        description is char[0-36] and is a text comment
// S1 Record. type 'S1' (0x5331). The address field is a 2-byte address. The data field is composed of memory loadable data.
// S2 Record. type 'S2' (0x5332). The address field is a 3-byte address. The data field is composed of memory loadable data.
// S3 Record. type 'S3' (0x5333). The address field is a 4-byte address. The data field is composed of memory loadable data.
// S5 Record. type 'S5' (0x5335). The address field is a 2-byte value and contains the count of S1, S2, and S3 records previously transmitted. There is no data field.
// S7 Record. type 'S7' (0x5337). The address field contains the starting execution address and is intrepreted as 4-byte address. There is no data field.
// S8 Record. type 'S8' (0x5338). The address field contains the starting execution address and is intrepreted as 3-byte address. There is no data field.
// S9 Record. type 'S9' (0x5339). The address field contains the starting execution address and is intrepreted as 2-byte address. There is no data field.

class Memory {
protected:
	std::vector<std::string>sourceList; // holds the source listing (by line#)
	std::map<uint32_t, int32_t>addrToSrcLine; // holds the address that the source reps
	bool isLoaded = false;
	// c++20 constexpr std::string hexStr = "0123456789ABCDEF";
	static constexpr std::string_view hexStr = "0123456789ABCDEF";

public:
//	uint8_t memory[1024*1024*1]; // 0x007fffff
	uint8_t memory[32768]; // 0x007fffff
	std::map<int32_t, uint32_t>srcLineToAddr; // holds the filesrcline to address - allows ident of lines that breakpoints can be used

public:
	Memory() {};
	~Memory() {};

	bool isValidByte(char m, char n);
	uint8_t getByte(const std::string_view line, const int32_t idx);
	uint32_t getHexValue(const std::string_view line, int32_t idx, const int32_t length);

	void addSourceLine(const std::string_view line, int32_t fileLine);
	std::string_view getSourceLine(const uint32_t lineIdx);
	uint32_t getNumberOfSourceLines(void);

	void addSRec(const std::string_view line);
	uint32_t getIndexOfSrcFromAddr(const uint32_t addr);

	bool isSourceLoaded(void);
};

#endif /* MEMORY_H_ */
