/***************************** 68000 SIMULATOR ****************************

 File Name: EXTERN.H
 Version: 1.1

 This file contains all extern global variable definitions for the
 simulator program.  It is included in all modules other than the module
 "SIM68Ku.cpp" which contains the main() function.


 BE CAREFUL TO KEEP THESE DECLARATIONS IDENTICAL TO THE GLOBAL
 VARIABLE DECLARATIONS IN "VAR.H"

 NOTE: adapted from the SIM68K project
 //   Author: Charles Kelly
 //           www.easy68k.com

 ***************************************************************************/

#ifndef EXTERN_H_
#define EXTERN_H_
#include <memory>
#include <stack>
#include "BPoint.h"
#include "BPointExpr.h"
#include "def.h"
#include "FileHandling.h"
#include "Memory.h"
#include "MainFrame.h"
#include "UTILS.h"

extern MainFrame* mainframe;
extern std::unique_ptr<Memory> memory;
extern std::unique_ptr<FileHandling> fileHandling;
extern std::unique_ptr<UTILS> utils;
extern wxTextCtrl* logWindow;

extern uint32_t D[D_REGS], OLD_D[D_REGS], A[A_REGS], OLD_A[A_REGS];
extern uint32_t PC, OLD_PC;
extern uint16_t SR, OLD_SR;

extern char bpoints;
extern char lbuf[SREC_MAX], *wordptr[20];
extern uint32_t cycles;
extern uint32_t brkpt[100];			// brkpt[i] == addr
extern uint32_t stepToAddr;             // Step Over stopping address
extern uint32_t runToAddr;              // runToCursor stopping address

extern char p1dif;
extern char* gettext();
extern int32_t wcount;
extern uint8_t port1[4];
extern char p1dif;
extern int32_t errflg;
extern int32_t trace, sstep, old_trace, old_sstep, exceptions;
extern bool bitfield, simhalt_on;
extern bool halt;                   // true, halts running program
extern bool stopInstruction;        // true after running stop instruction

extern uint32_t inst;
extern uint32_t *EA1, *EA2;
extern uint32_t EV1, EV2;

extern uint32_t source, dest, result;

extern uint32_t global_temp; /* to hold an immediate data operand */

extern bool runMode;       // true when running 68000 program (not tracing)
extern bool runModeSave;

extern bool keyboardEcho;    // true, 68000 input is echoed (default)
extern char pendingKey;      // pending key for char input
extern bool inputPrompt;     // true, display prompt during input (default)
extern bool inputLFdisplay;     // true, display LF on CR during input (default)

extern char inputBuf[256];          // simulator input buffer
extern int32_t inputSize;              // number of characters input
extern bool inputMode;       // true during 68000 program input

extern FileStruct files[MAXFILES];     // array of file structures

// log output
extern char ElogFlag;           // log file setting
extern FILE *ElogFile;		// Log file
extern char OlogFlag;           // log file setting
extern FILE *OlogFile;		// Log file
extern bool logging;            // true when logging
extern uint32_t logMemAddr;         // log memory address
extern uint32_t logMemBytes;        // log memory bytes

extern bool autoTraceInProgress;        // true when auto tracing

// Allocate array of breakpoints / expression groups.
// PC/Reg break points are in elements 0-49.  Addr => 50-99.
extern BPoint breakPoints[MAX_BPOINTS];
extern BPointExpr bpExpressions[MAX_BP_EXPR];
extern int32_t bpCountCond[MAX_BPOINTS];
extern int32_t regCount;
extern int32_t addrCount;
extern int32_t exprCount;

// Allocate array of ints for building a break expression.
// Elements of infixExpr represent relative indexes into the
// breakPoints array or represent and_node, or_node, not_node.
extern int32_t infixExpr[MAX_LB_NODES];
extern int32_t postfixExpr[MAX_LB_NODES];
extern int32_t infixCount;
extern int32_t postfixCount;
extern std::stack<int32_t> s_operator;

// Used to efficiently calculate which GUI buttons are availabe as
// the user builds a breakpoint expression.
extern bool mruOperand;
extern bool mruOperator;
extern int32_t parenCount;

// Read and write flags so when breakpoints are tested for read/write
// access, we know if this instruction caused a respective read/write.
extern bool bpRead;
extern bool bpWrite;
extern uint32_t *readEA;
extern uint32_t *writeEA;

// Interrupt and Reset Control
extern bool hardReset;
extern int32_t irq;

// saves weather the ChangeDisplaySettingsEx() and other multi monitor apis exist
extern bool MultimonitorAPIsExist;

// what screen to use for full screen output   0 = primary  1 and up = secondaries
extern unsigned char FullScreenMonitor;

// screen device to use for full screen output
extern char FullScreenDeviceName[32];

// true if directSound may be used
extern bool dsoundExist;

// Mouse
extern int32_t mouseX, mouseY;
extern bool mouseLeft, mouseRight, mouseMiddle, mouseDouble;
extern bool keyShift, keyAlt, keyCtrl;

extern int32_t mouseXUp, mouseYUp;
extern bool mouseLeftUp, mouseRightUp, mouseMiddleUp, mouseDoubleUp;
extern bool keyShiftUp, keyAltUp, keyCtrlUp;

extern int32_t mouseXDown, mouseYDown;
extern bool mouseLeftDown, mouseRightDown, mouseMiddleDown, mouseDoubleDown;
extern bool keyShiftDown, keyAltDown, keyCtrlDown;
extern int8_t mouseDownIRQ, mouseUpIRQ, mouseMoveIRQ;
extern int8_t keyDownIRQ, keyUpIRQ;

extern int32_t seg7loc, LEDloc, switchLoc, pbLoc;
extern bool pbInit;
extern bool autoIRQ;
extern bool hardwareEnabled;
extern int32_t ROMStart, ROMEnd, ReadStart, ReadEnd;
extern int32_t ProtectedStart, ProtectedEnd, InvalidStart, InvalidEnd;
extern bool ROMMap, ReadMap, ProtectedMap, InvalidMap;

extern uint8_t keyDownCode;       // defined in simIOu, used by Trap #15,19
extern uint8_t keyUpCode;         // "
extern bool disableKeyCommands;
#endif /* EXTERN_H_ */
