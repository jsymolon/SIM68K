#ifndef BUILD_H_
#define BUILD_H_

#include "asm.h"

int move(int, int, opDescriptor*, opDescriptor*, int*);
int zeroOp(int, int, opDescriptor*, opDescriptor*, int*);
int oneOp(int, int, opDescriptor*, opDescriptor*, int*);
int arithReg(int, int, opDescriptor*, opDescriptor*, int*);
int arithAddr(int, int, opDescriptor*, opDescriptor*, int*);
int bitField(int, int, opDescriptor*, opDescriptor*, int*);
int immedInst(int, int, opDescriptor*, opDescriptor*, int*);
int quickMath(int, int, opDescriptor*, opDescriptor*, int*);
int movep(int, int, opDescriptor*, opDescriptor*, int*);
int moves(int, int, opDescriptor*, opDescriptor*, int*);
int moveReg(int, int, opDescriptor*, opDescriptor*, int*);
int staticBit(int, int, opDescriptor*, opDescriptor*, int*);
int movec(int, int, opDescriptor*, opDescriptor*, int*);
int trap(int, int, opDescriptor*, opDescriptor*, int*);
int branch(int, int, opDescriptor*, opDescriptor*, int*);
int moveq(int, int, opDescriptor*, opDescriptor*, int*);
int immedToCCR(int, int, opDescriptor*, opDescriptor*, int*);
int immedWord(int, int, opDescriptor*, opDescriptor*, int*);
int dbcc(int, int, opDescriptor*, opDescriptor*, int*);
int scc(int, int, opDescriptor*, opDescriptor*, int*);
int shiftReg(int, int, opDescriptor*, opDescriptor*, int*);
int exg(int, int, opDescriptor*, opDescriptor*, int*);
int twoReg(int, int, opDescriptor*, opDescriptor*, int*);
int oneReg(int, int, opDescriptor*, opDescriptor*, int*);
int moveUSP(int, int, opDescriptor*, opDescriptor*, int*);
int link_ins(int, int, opDescriptor*, opDescriptor*, int*);


#endif
