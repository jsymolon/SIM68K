#include "hardware.h"
#include <cstdint>

//static const TColor clDrkMaroon = 0x02000040;
//static const unsigned long SWITCH_ADDR = 0xE0000A;

uint32_t seg7loc, LEDloc, switchLoc, pbLoc;
bool pbInit;
bool autoIRQ;
bool hardwareEnabled;
uint32_t ROMStart=0, ROMEnd=0, ReadStart=0, ReadEnd=0;
uint32_t ProtectedStart=0, ProtectedEnd=0, InvalidStart=0, InvalidEnd=0;
bool ROMMap=false, ReadMap=false, ProtectedMap=false, InvalidMap=false;
