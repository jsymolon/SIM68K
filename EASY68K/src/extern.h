/*
 * extern.h
 *
 *  Created on: Aug 5, 2023
 *      Author: jsymolon
 */

#ifndef EXTERN_H_
#define EXTERN_H_

#include <memory>
//#include "FileHandling.h"
#include "LogCtrl.h"
#include "MainFrame.h"
//#include "Memory.h"
//#include "UTILS.h"
#include "Options.h"

extern MainFrame *mainframe;
//extern std::unique_ptr<FileHandling> fileHandling;
//extern std::unique_ptr<UTILS> utils;
extern LogCtrl *logWindow;
extern std::unique_ptr<Options> options;

extern const wxColor &DEFAULT_CODE_COLOR;
extern const wxColor &DEFAULT_UNKNOWN_COLOR;
extern const wxColor &DEFAULT_DIRECTIVE_COLOR;
extern const wxColor &DEFAULT_COMMENT_COLOR;
extern const wxColor &DEFAULT_LABEL_COLOR;
extern const wxColor &DEFAULT_STRUCTURE_COLOR;
extern const wxColor &DEFAULT_ERROR_COLOR;
extern const wxColor &DEFAULT_TEXT_COLOR;
extern const wxColor &DEFAULT_BACK_COLOR;

extern char NEW_PAGE_MARKER[];

const int32_t LINE_LENGTH = 256;
#include <string>
#include <stack>
#include <vector>
extern std::stack<int, std::vector<int> > stcStack;
extern std::stack<char, std::vector<char> > dbStack;
extern std::stack<std::string, std::vector<std::string> > forStack;

#endif /* EXTERN_H_ */
