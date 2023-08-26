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

#endif /* EXTERN_H_ */
