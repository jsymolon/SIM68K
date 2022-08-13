/***************************** 68000 SIMULATOR ****************************

 File Name: PROTO.H
 Version: 1.0

 This file contains function prototype definitions for all functions
 in the program

 ***************************************************************************/

#ifndef PROTO_H_
#define PROTO_H_

int32_t MOVE(void);
int32_t MOVEP(void);
int32_t MOVEA(void);
int32_t MOVE_FR_SR(void);
int32_t MOVE_TO_CCR(void);
int32_t MOVE_TO_SR(void);
int32_t MOVEM(void);
int32_t MOVE_USP(void);
int32_t MOVEQ(void);
int32_t EXG(void);
int32_t LEA(void);
int32_t PEA(void);
int32_t LINK(void);
int32_t UNLK(void);
int32_t ADD(void);
int32_t ADDA(void);
int32_t ADDI(void);
int32_t ADDQ(void);
int32_t ADDX(void);
int32_t SUB(void);
int32_t SUBA(void);
int32_t SUBI(void);
int32_t SUBQ(void);
int32_t SUBX(void);
int32_t DIVS(void);
int32_t DIVU(void);
int32_t MULS(void);
int32_t MULU(void);
int32_t NEG(void);
int32_t NEGX(void);
int32_t CMP(void);
int32_t CMPA(void);
int32_t CMPI(void);
int32_t CMPM(void);
int32_t TST(void);
int32_t CLR(void);
int32_t EXT(void);
int32_t ABCD(void);
int32_t SBCD(void);
int32_t NBCD(void);
int32_t AND(void);
int32_t ANDI(void);
int32_t ANDI_TO_CCR(void);
int32_t ANDI_TO_SR(void);
int32_t OR(void);
int32_t ORI(void);
int32_t ORI_TO_CCR(void);
int32_t ORI_TO_SR(void);
int32_t EOR(void);
int32_t EORI(void);
int32_t EORI_TO_CCR(void);
int32_t EORI_TO_SR(void);
int32_t NOT(void);
int32_t SHIFT_ROT(void);
int32_t SWAP(void);
int32_t BIT_OP(void);
int32_t TAS(void);
int32_t BCC(void);
int32_t DBCC(void);
int32_t SCC(void);
int32_t BRA(void);
int32_t BSR(void);
int32_t JMP(void);
int32_t JSR(void);
int32_t RTE(void);
int32_t RTR(void);
int32_t RTS(void);
int32_t NOP(void);
int32_t CHK(void);
int32_t ILLEGAL(void);
int32_t RESET(void);
int32_t STOP(void);
int32_t TRAP(void);
int32_t TRAPV(void);
int32_t LINE1010();        //CK v2.3
int32_t LINE1111();        //CK v2.3

void at(int32_t y, int32_t x);
char chk_buf(void);
int32_t gethelp(void);
void home();
int32_t parse(char *str, char **ptrbuf, int32_t maxcnt);
int32_t runprog();
int32_t show_topics(void);

int32_t iswhite(char c, char *qflag);
int32_t decode_size(int32_t *result);
int32_t eff_addr(int32_t size, int32_t mask, bool add_times);
int32_t eff_addr_noread(int32_t size, int32_t mask, bool add_times);
int32_t exec_inst(void);
void exceptionHandler(int32_t, int32_t, int32_t);
void irqHandler();
void cmderr();
void setdis();
void scrshow();
int32_t mdis(void);
int32_t selbp(void);
int32_t dbpoint(void);
int32_t memread(int32_t loc, int32_t MASK);
int32_t memwrite(int32_t loc, int32_t value);
int32_t alter(void);
int32_t hex_to_dec(void);
int32_t dec_to_hex(void);
int32_t intmod(void);
int32_t portmod(void);
int32_t pcmod(void);
int32_t changemem(int32_t oldval, int32_t *result);
int32_t mmod(void);
int32_t regmod(char *regpntr, int32_t data_or_mem);

// file handling
void closeFiles(short *result);
void openFile(int32_t *fn, char *name, short *result);
void newFile(int32_t *fn, char *name, short *result);
void readFile(int32_t fn, char *buf, uint32_t *size, short *result);
void writeFile(int32_t fn, char *buf, uint32_t size, short *result);
void positionFile(int32_t fn, int32_t offset, short *result);
void closeFile(int32_t fn, short *result);
void deleteFile(char *buf, short *result);
int32_t loadSrec(char*);
void fileOp(int32_t *mode, char *fname, short *result);

int32_t clear(void);
char* getText(int32_t word, char *prompt);
int32_t same(char *str1, char *str2);
int32_t eval(char *string);
int32_t eval2(char *string, int32_t *result);
int32_t getval(int32_t word, char *prompt);
int32_t strcopy(char *str1, char *str2);
char* mkfname(char *cp1, char *cp2, char *outbuf);
int32_t pchange(char oldval);

void reg_put(int32_t *dest, int32_t source, int32_t size);

void windowLine();
void scrollWindow();
int32_t scan(char*, char*[], int32_t); /* scan up to maxcnt words in str */
void save_cursor();
void restore_cursor();
void initSim();
void finishSim();
void errmess(); /* error message for invalid input */
void startSim();
void DFcommand();        // shows register display
// TODO: FIX void __fastcall initPrint();
void haltSimulator();
int32_t memoryMapCheck(maptype mapt, uint32_t loc, int32_t bytes);

#endif /* PROTO_H_ */
