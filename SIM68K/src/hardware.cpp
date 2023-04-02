#include "hardware.h"
#include <cstdint>

//static const TColor clDrkMaroon = 0x02000040;
//static const unsigned long SWITCH_ADDR = 0xE0000A;

uint32_t seg7loc;
uint32_t LEDloc;
uint32_t switchLoc;
uint32_t pbLoc;
bool pbInit;
bool autoIRQ;
bool hardwareEnabled;
uint32_t ROMStart = 0;
uint32_t ROMEnd = 0;
uint32_t ReadStart = 0;
uint32_t ReadEnd = 0;
uint32_t ProtectedStart = 0;
uint32_t ProtectedEnd = 0;
uint32_t InvalidStart = 0;
uint32_t InvalidEnd = 0;
bool ROMMap = false;
bool ReadMap = false;
bool ProtectedMap = false;
bool InvalidMap = false;
