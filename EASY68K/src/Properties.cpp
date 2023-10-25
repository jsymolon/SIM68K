/*
 * Properties.cpp
 *
 *  Created on: Jun 8, 2021
 *      Author: jsymolon
 */

#include "Properties.h"
#include <iostream>
#include <fstream>
#include <map>
#include <string>

#include <wx/filename.h>
#include <wx/dir.h>

//----------------------------------------------------------------------------------
//Properties::Properties() {}

//virtual ~Properties();
//Properties(const Properties& other) {};
//Properties& operator=(const Properties& other);

//----------------------------------------------------------------------------------
void Properties::load(const std::string_view propertypath) {
	if (!propertypath.empty()) {
		propsFolder = propertypath;
	}

	wxFileName cwd = wxFileName::GetCwd();
	wxString ps = wxFileName::GetPathSeparators();
	wxString fullpath = "";
	fullpath.Append(cwd.GetFullPath());
	fullpath.Append(ps);
	fullpath.Append(propsFileName);
	wxFileName propsfullpath = wxFileName(fullpath);
	if (!propsfullpath.FileExists()) {
		std::cerr << "Properties doesn't exist " << fullpath << " " << propsFileName;
		return;
	}
	if (!propsfullpath.IsFileReadable()) {
		std::cerr << "Properties isn't readable " << fullpath << " " << propsFileName;
		return;
	}

	// std::ifstream is RAII, i.e. no need to call close
	std::ifstream cFile;

	cFile.open(fullpath.c_str(), std::ifstream::in);
	if (cFile.is_open()) {
		std::string line;
		while (getline(cFile, line)) {
			line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
			if (line[0] == '#' || line.empty())
				continue;

			auto delimiterPos = line.find("=");
			auto name = line.substr(0, delimiterPos);
			auto value = line.substr(delimiterPos + 1);
			properties[name] = value;
		}
	} else {
		std::cerr << "Couldn't open config file for reading." << fullpath << " " << propsFileName;
	}
}

//----------------------------------------------------------------------------------
void Properties::save(void) {
	if (propsFolder.length() > 0) {

	}
}

//----------------------------------------------------------------------------------
std::string Properties::getString(std::string key, std::string defaultVal) {
	std::map<std::string, std::string>::iterator iter = properties.find(key);
	if (iter != properties.end()) {
		return (iter->second);
	}
	return (defaultVal);
}

//----------------------------------------------------------------------------------
int Properties::getInt(std::string key, int defaultVal) {
	std::string dVal = std::to_string(defaultVal);
	return (std::stoi(this->getString(key, dVal)));
}
