#include "MemoryTest.h"

#include <climits>

//----------------------------------------------------------------------------------
TEST_F(MemoryTest, TestMemoryByte) {
	std::unique_ptr<Memory> m = std::make_unique<Memory>();
	std::string line = "0a1B2C";
	int idx = 0;
	unsigned short gb = m->getByte(line, idx);
	EXPECT_EQ(gb, 0x0a) << "0x0a Byte";
	idx += 2;
	gb = m->getByte(line, idx);
	EXPECT_EQ(gb, 0x1b) << "0x1b Byte";
}

//----------------------------------------------------------------------------------
TEST_F(MemoryTest, TestMemoryWord) {
	std::unique_ptr<Memory> m = std::make_unique<Memory>();
	std::string line = "0a1B2C";
	int idx = 2;
	unsigned long gb = m->getHexValue(line, idx, 2);
	EXPECT_EQ( gb, 0x1b2c) << "0x1b2c Word";
}

//----------------------------------------------------------------------------------
TEST_F(MemoryTest, TestMemory24bits) {
	std::unique_ptr<Memory> m = std::make_unique<Memory>();
	std::string line = "0a1B2C";
	int idx = 0;
	unsigned long gb = m->getHexValue(line, idx, 3);
	EXPECT_EQ(gb , 0x0a1B2C) << "0x0a1B2C 24bit";
}

//----------------------------------------------------------------------------------
// no code
TEST_F(MemoryTest, TestAddSourceLine1) {
	std::unique_ptr<Memory> m = std::make_unique<Memory>();
	std::string line = "00001000                            11  START:";
	int lineIdx = 0;
	m->addSourceLine(line, lineIdx);
	std::string_view sline = m->getSourceLine(lineIdx);
	EXPECT_EQ(line.compare(sline) , 0) << "Blank source line";
}

//----------------------------------------------------------------------------------
// single word code
TEST_F(MemoryTest, TestAddSourceLine2) {
	std::unique_ptr<Memory> m = std::make_unique<Memory>();
	std::string line = "0000100E  5283                      17          addq.l  #1,d3";
	int lineIdx = 0;
	m->addSourceLine(line, lineIdx);
	std::string_view sline = m->getSourceLine(lineIdx);
	EXPECT_EQ(line.compare(sline), 0) << "Data source line";
}

//----------------------------------------------------------------------------------
TEST_F(MemoryTest, TestAddrSourceIdx1) {
	std::unique_ptr<Memory> m = std::make_unique<Memory>();
	std::string line = "00001000                            11  START:";
	int lineIdx = 0;
	m->addSourceLine(line, lineIdx);
	unsigned long addr = 0x00001000;
	unsigned int idx = m->getIndexOfSrcFromAddr(addr);
	EXPECT_EQ(idx , UINT_MAX) << "No code source line";
}

//----------------------------------------------------------------------------------
// single word code
TEST_F(MemoryTest, TestAddrSourceIdx2) {
	std::unique_ptr<Memory> m = std::make_unique<Memory>();
	std::string line = "0000100E  5283                      17          addq.l  #1,d3";
	int lineIdx = 0;
	m->addSourceLine(line, lineIdx);
	unsigned long addr = 0x0000100E;
	unsigned int idx = m->getIndexOfSrcFromAddr(addr);
	EXPECT_EQ( idx, 0) << "Data source line";
}
