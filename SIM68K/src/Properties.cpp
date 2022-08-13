/*
 * Properties.cpp
 *
 *  Created on: Jun 8, 2021
 *      Author: jsymolon
 */

#include "Properties.h"

//----------------------------------------------------------------------------------
Properties::Properties() {
}

//----------------------------------------------------------------------------------
Properties::~Properties() {
}

//----------------------------------------------------------------------------------
void Properties::load(const std::string_view propertypath) {
	this->propsPath = propertypath;
    properties = toml::parseFile(this->propsPath);
    if (!properties.table) {
    	std::cerr << "Cannot parse property file " << properties.errmsg;
    	return;
    }
}

//----------------------------------------------------------------------------------
void Properties::save(void) {

}

//----------------------------------------------------------------------------------
std::string Properties::getString(std::string table, std::string key, std::string defaultVal) {
	auto section = properties.table->getTable(table);
	if (!section) {
		return defaultVal;
	}
	std::string value;
	bool ok;
	std::tie(ok, value) = section->getString(key);
	if (!ok) {
		return defaultVal;
	}
	return value;
}

//----------------------------------------------------------------------------------
int Properties::getInt(std::string table, std::string key, int defaultVal) {
	auto section = properties.table->getTable(table);
	if (!section) {
		return defaultVal;
	}
	int value;
	bool ok;
	std::tie(ok, value) = section->getInt(key);
	if (!ok) {
		return defaultVal;
	}
	return value;
}
