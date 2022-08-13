/*
 * FileHandling.cpp
 *
 *  Created on: May 31, 2021
 *      Author: jsymolon
 */

#include "FileHandling.h"
//#include <iosfwd>  // iostream forward - speed compile, .cpp only
#include <iostream>  // need cerr
#include <fstream>
#include <exception>
#include <stdexcept>

//----------------------------------------------------------------------------------
void FileHandling::loadProgramFile(const std::string_view filepath,
		std::unique_ptr<Memory> &mem) { // .L68 & S68
	size_t lastindex = filepath.find_last_of(".");
	std::string rawname = std::string(filepath.substr(0, lastindex));
	this->loadSourceFile(rawname + ".L68", mem);
	this->loadSRecFile(rawname + ".S68", mem);
}

//----------------------------------------------------------------------------------
void FileHandling::loadSourceFile(const std::string filepath,
		std::unique_ptr<Memory> &mem) { // .L68
	std::fstream l68;
	try {
		l68.open(filepath, std::ios::in);
		int fileLine = 0;
		if (!l68) {
			//TODO: error
			return;
		}
		std::string line;
		while (getline(l68, line)) {
			mem->addSourceLine(line, fileLine++);
		}
		l68.close();
	} catch (const std::exception &e) {
		std::cerr << "loadSourceFile:" << e.what();
	}
}

//----------------------------------------------------------------------------------
void FileHandling::loadSRecFile(const std::string filepath,
		std::unique_ptr<Memory> &mem) { // .S68
	std::fstream s68;
	try {
		s68.open(filepath, std::ios::in);
		if (!s68) {
			//TODO: error
			return;
		}
		std::string line;
		while (getline(s68, line)) {
			mem->addSRec(line);
		}
		s68.close();
	} catch (const std::exception &e) {
		std::cerr << "loadSRecFile:" << e.what();
	}
}
