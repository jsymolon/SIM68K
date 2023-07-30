/*
 * Globals.cpp
 *
 *  Created on: Jun 4, 2021
 *      Author: jsymolon
 */

#include "extern.h"

// problem w/ unique_ptr, SIM68K "new" doesn't recognize ...
MainFrame *mainframe;

std::unique_ptr<Memory> memory = std::make_unique<Memory>();
std::unique_ptr<FileHandling> fileHandling = std::make_unique<FileHandling>();
std::unique_ptr<UTILS> utils = std::make_unique<UTILS>();
//wxTextCtrl *logWindow;
LogCtrl *logWindow;

// _____________________________________________________________________
// The following variables must remain together. put() and value_of()
// check the addresses of these variables to decide if an operation
// is being performed on a 68000 register or 68000 memory.
// 68000 registers
uint32_t D[D_REGS];
uint32_t A[A_REGS];
uint32_t PC;
uint16_t SR;
uint32_t global_temp;	// to hold an immediate data operand
uint32_t OLD_PC;         // previous PC
uint32_t *EA1;
uint32_t *EA2;
uint32_t EV1;
uint32_t EV2;
uint32_t source;
uint32_t dest;
uint32_t result;
int32_t sresult;
uint32_t inst; // get/put memory sus ... with int32_t inst?
// _____________________________________________________________________

uint32_t cycles;
int32_t trace;
int32_t sstep;
int32_t old_trace;
int32_t old_sstep;
int32_t exceptions;
bool bitfield;
bool simhalt_on;
bool halt;                   		// true, halts running program
bool stopInstruction;        		// true after running stop instruction

char lbuf[SREC_MAX];
char *wordptr[20]; 	// command buffers
char bpoints = 0;
uint32_t brkpt[100];
int32_t wcount;
uint32_t stepToAddr;             // Step Over stopping address
uint32_t runToAddr;              // runToCursor stopping address

int32_t errflg;

/* port structure is :{control,trans data,status,receive data} */
uint8_t port1[4] = { 0x00, 0, 0x82, 0 }; /* simulated 6850 port */
char p1dif = 0;

bool runMode;                // true when running 68000 program (not tracing)
bool runModeSave;

bool keyboardEcho;           // true, EASy68K input is echoed (default)
char pendingKey;             // pending key for char input
bool inputPrompt;            // true, display prompt during input (default)
bool inputLFdisplay;         // true, display LF on CR during input (default)

char inputBuf[256];          // simulator input buffer
int32_t inputSize;              // number of characters input
bool inputMode;              // true when getting keyboard input

FileStruct files[MAXFILES];     // array of file structures

// log output
char ElogFlag;          		// Execution log file setting
FILE *ElogFile;					// Execution Log file
char OlogFlag;          		// Output log file setting
FILE *OlogFile;					// Output Log file
bool logging;           		// true when logging
uint32_t logMemAddr; 		// log memory address
uint32_t logMemBytes; 	// log memory bytes

bool autoTraceInProgress;       // true when auto tracing

// Allocate array of breakpoints / expression groups.
// PC/Reg break points are in elements 0-49.  Addr => 50-99.
BPoint breakPoints[MAX_BPOINTS];
BPointExpr bpExpressions[MAX_BP_EXPR];
int32_t bpCountCond[MAX_BPOINTS];
int32_t regCount = 0;
int32_t addrCount = 0;
int32_t exprCount = 0;

// Allocate array of ints for building a break expression.
// Elements of infixExpr represent relative indexes into the
// breakPoints array or represent and_node, or_node, not_node.
int32_t infixExpr[MAX_LB_NODES];
int32_t postfixExpr[MAX_LB_NODES];
int32_t infixCount = 0;
int32_t postfixCount;
std::stack<int32_t> s_operator;

// Used to efficiently calculate which GUI buttons are availabe as
// the user builds a breakpoint expression.
bool mruOperand = false;
bool mruOperator = false;
int32_t parenCount = 0;

// Read and write flags so when breakpoints are tested for read/write
// access, we know if this instruction caused a respective read/write.
bool bpRead;
bool bpWrite;
uint32_t *readEA;
uint32_t *writeEA;

// Interrupt and Reset Control
bool hardReset;
int32_t irq;

// true if ChangeDisplaySettingsEx() and other multi monitor apis exist
bool MultimonitorAPIsExist;

// what screen to use for full screen output   0 = primary  1 and up = secondaries
unsigned char FullScreenMonitor;

// screen device to use for full screen output
char FullScreenDeviceName[32];

// true if directSound may be used
bool dsoundExist;

// Mouse
int32_t mouseX;
int32_t mouseY;
bool mouseLeft;
bool mouseRight;
bool mouseMiddle;
bool mouseDouble;
bool keyShift;
bool keyAlt;
bool keyCtrl;

int32_t mouseXUp;
int32_t mouseYUp;
bool mouseLeftUp;
bool mouseRightUp;
bool mouseMiddleUp;
bool mouseDoubleUp;
bool keyShiftUp;
bool keyAltUp;
bool keyCtrlUp;

int32_t mouseXDown;
int32_t mouseYDown;
bool mouseLeftDown;
bool mouseRightDown;
bool mouseMiddleDown;
bool mouseDoubleDown;
bool keyShiftDown;
bool keyAltDown;
bool keyCtrlDown;
int8_t mouseDownIRQ;
int8_t mouseUpIRQ;
int8_t mouseMoveIRQ;
int8_t keyDownIRQ;
int8_t keyUpIRQ;
