/*
 * Memory.cpp
 *
 *  Created on: May 31, 2021
 *      Author: jsymolon
 */

#include "Memory.h"
#include <climits>
#include <iosfwd>  // iostream forward - speed compile, .cpp only
#include "extern.h"

//----------------------------------------------------------------------------------
bool Memory::isValidByte(char m, char n) {
	std::size_t found = hexStr.find(m);
	if (found == std::string::npos) {
		return (false); // char not in list
	}
	found = hexStr.find(n);
	if (found == std::string::npos) {
		return (false); // char not in list
	}
	return (true);
}

//----------------------------------------------------------------------------------
void Memory::addSourceLine(const std::string_view line, int32_t fileLine) {
	//line 1 = "starting address" - line is line of file not the source file line
	std::string s { line };
	size_t lastidx = s.size();
	sourceList.push_back(s);
	if (lastidx > LIST_BYTE_START) {
		// get address - 1st 8 chars
		std::string addrStr = "0x" + s.substr(0, 8);
		// code ... only register line if "code" there, 12 bytes+
		std::string codecheck = s.substr(10, 2);
		// want to skip any lines not starting with an address
		if (isValidByte(codecheck[0], codecheck[1])) {
			uint32_t addr = std::stoul(addrStr.c_str(), 0, 16);
			addrToSrcLine.insert( { addr, fileLine });
			//std::cout << "addSourceLine a:" << addr << " line:" << fileLine << " src:" << line << "\n";
			srcLineToAddr.insert( { fileLine, addr });
		}
	}
}

//----------------------------------------------------------------------------------
std::string_view Memory::getSourceLine(const uint32_t lineIdx) {
	if (sourceList.size() == 0 || sourceList.size() < lineIdx) {
		return (" ");
	}
	return (sourceList[lineIdx]);
}
//----------------------------------------------------------------------------------
uint32_t Memory::getNumberOfSourceLines(void) {
	return (sourceList.size());
}

//----------------------------------------------------------------------------------
uint8_t Memory::getByte(const std::string_view line, const int32_t idx) {
	uint8_t accum = 0;
	char c;
	uint8_t x = 0;
	for (int i = idx; i <= idx + 1; i++) {
		c = line[i];
		x = c - '0';
		if (x > HEX_VAL_9) {
			x -= HEX_GAP_9TOA;  // gap of A to 9
			if (x > HEX_VAL_16) {
				x -= HEX_GAP_aTOA; // gap of a to A
			}
		}
		accum <<= HEX_NIBBLE;
		accum += x;
	}
	return (accum);
}
//----------------------------------------------------------------------------------
uint32_t Memory::getHexValue(const std::string_view line, int32_t idx, const int32_t length) {
	uint32_t accum = 0;
	for (int i = 1; i <= length; i++) {
		accum = accum << HEX_BYTE;
		unsigned short iaccum = getByte(line, idx);
		idx += 2;
		accum += iaccum;
	}
	return (accum);
}

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
// +-------------------------//--------------------------//-----------------------+
// | type(2) | count(2) | address(4, 6, 8) |            data           | checksum |
// +-------------------------//--------------------------//-----------------------+
// Called from the FileHandler
void Memory::addSRec(const std::string_view line) {
	int idx = 2; // skip 1st two bytes "Sx"
	int count = getByte(line, idx);
	idx += 2;
	uint32_t addr = 0;
	switch (line[1]) {
	case '0': // header
		count = 0; // skip
		break;
	case '1': // addr 2 byte
		addr = getHexValue(line, idx, 2);
		idx += SREC_C2ADDR;
		break;
	case '2': // addr 3 byte
		addr = getHexValue(line, idx, SREC_B3ADDR);
		idx += SREC_C3ADDR;
		break;
	case '3': // addr 4 byte
		addr = getHexValue(line, idx, SREC_BiADDR);
		idx += SREC_CiADDR;
		break;
	case '5': // addr 2 byte, count of S1, S2, & S3 previously. no data
		addr = getHexValue(line, idx, 2);
		idx += SREC_C2ADDR;
		break;
	case '7': // starting exec addr 4 byte
		addr = getHexValue(line, idx, SREC_BiADDR);
		idx += SREC_CiADDR;
		count = 0; // skip
		PC = addr;
		startPC = addr;
		break;
	case '8': // starting exec addr 3 byte
		addr = getHexValue(line, idx, SREC_B3ADDR);
		idx += SREC_C3ADDR;
		count = 0; // skip
		PC = addr;
		startPC = addr;
		break;
	case '9': // starting exec addr 2 byte
		addr = getHexValue(line, idx, 2);
		idx += 2;
		count = 0; // skip
		PC = addr;
		startPC = addr;
		break;
	default:
		count = 0; // skip
		break;
	}
	std::cout << "\nline:" << line;
	std::cout << "src addr:" << addr;

	for (int i = 0; i < (count - 1); i++) {
		int8_t hexbyte = getHexValue(line, idx++, 1);
		idx++;
		std::cout << " " << hexbyte;
		memory[addr++] = hexbyte;
	}
	std::cout << "\n";
}

//----------------------------------------------------------------------------------
uint32_t Memory::getIndexOfSrcFromAddr(const uint32_t addr) {
	std::map<uint32_t, int>::iterator it;
	it = addrToSrcLine.find(addr);
	if (it == addrToSrcLine.end()) {
		return UINT_MAX;
	}
	return (it->second);
}

//----------------------------------------------------------------------------------
bool Memory::isSourceLoaded(void) {
	return (this->isLoaded);
}

//----------------------------------------------------------------------------------
void Memory::clearSource(void) {
	isLoaded = false;
	sourceList.clear();
	addrToSrcLine.clear();
	srcLineToAddr.clear();
}
