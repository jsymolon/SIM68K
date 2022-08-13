#include "MemoryCtrlTest.h"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <climits>
#include "../src/extern.h"
#include "../src/MemoryCtrl.h"


//----------------------------------------------------------------------------------
// test the display line - note that GCC doesn't support std::format yet
TEST_F(MemoryCtrlTest,TestMemoryDisplayAlgo) {
	std::ostringstream outstream;
	int values[16] = { 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56 };
//	out << sprintf(out.str(), "%08X:", 0);
	//	for (auto& x : values) {
//		out << sprintf(out.str(), "%02X ", x);
//	}
	auto size = std::snprintf(nullptr, 0u, "%p:" );
	std::string outaddr(size, ' ');
	std::sprintf(&outaddr[0], "%08X:", 0);
	outstream << outaddr;

	size = std::snprintf(nullptr, 0u, "%p " );
	for (auto& x : values) {
		std::string outb(size, ' ');
		std::sprintf(&outb[0], "%02X ", x);
		outstream << outb;
	}

	outstream << " ";

	size = std::snprintf(nullptr, 0u, "%p " );
	for (auto& x : values) {
		std::string outc(size, ' ');
		std::sprintf(&outc[0], "%c ", x);
		outstream << outc;
	}

	std::string out = outstream.str();
	//std::cout << "TestMemoryDisplayAlgo:" << out;
}

//----------------------------------------------------------------------------------
// test the display line - note that GCC doesn't support std::format yet
TEST_F(MemoryCtrlTest,TestMemoryDisplayLine) {
	unsigned long addr = 0;
	unsigned short val = 0x41;
	for (auto x = addr; x<addr+16; x++) {
		memory->memory[x] = val++;
	}
	MemoryCtrl* mc = new MemoryCtrl();
	std::string out = mc->buildDataLine(addr);
	std::string testData = "00000000:41 42 43 44 45 46 47 48 49 4A 4B 4C 4D 4E 4F 50 ABCDEFGHIJKLMNOP";
	EXPECT_EQ(testData.compare(out), 0) << "Memory Display Line";
}
