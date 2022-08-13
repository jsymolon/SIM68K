/*
 * FileHandling.h
 *
 *  Created on: May 31, 2021
 *      Author: jsymolon
 */

#ifndef FILEHANDLING_H_
#define FILEHANDLING_H_

#include <wx/string.h>

#include <string>
#include <string_view>
#include <list>

#include "Memory.h"
#include <memory>

class FileHandling {
public:
	FileHandling() {
	}
	;

	~FileHandling() {
	}
	;

	void loadProgramFile(const std::string_view filepath, std::unique_ptr<Memory>&mem); // .L68 & S68
	void loadSourceFile(const std::string filepath, std::unique_ptr<Memory>&mem); // .L68
	void loadSRecFile(const std::string filepath, std::unique_ptr<Memory>&mem); // .S68
};

#endif /* FILEHANDLING_H_ */
