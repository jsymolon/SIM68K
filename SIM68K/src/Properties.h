/*
 * Properties.h
 *
 *  Created on: Jun 8, 2021
 *      Author: jsymolon
 *
 *  Based on TOML - Tom's Obvious Minimal Language
 */

#ifndef PROPERTIES_H_
#define PROPERTIES_H_

#include <string>
#include <map>

namespace PROPERTIES {
static inline const std::string TABLE_SOURCE = "source";
static inline const std::string SOURCE_FONT_NAME = "fontname";
static inline const std::string SOURCE_FONT_SIZE = "fontsize";
static inline const std::string SOURCE_FONT_WEIGHT = "fontweight";
static inline const std::string SOURCE_FONT_COLOR = "fontcolor";
static inline const std::string SOURCE_BACKGROUND_COLOR = "backgroundcolor";
static inline const std::string SOURCE_GUTTER_COLOR = "guttercolor";
static inline const std::string SOURCE_DIV_COLOR = "divcolor";
static inline const std::string SOURCE_BP_ACTIVE = "bp_active";
static inline const std::string SOURCE_BP_INACTIVE = "bp_inactive";
static inline const std::string SOURCE_CODE_HIGHLIGHT = "code_highlight";
}

class Properties {
protected:
	// per https://en.wikipedia.org/wiki/Filesystem_Hierarchy_Standard
	std::string propsFolder = "SIM68K/";
	std::string propsFileName = "SIM68K.properties";
	std::map<std::string, std::string> properties;

	typedef std::map<std::string, std::string>::iterator map_iterator;

public:
	//Properties(){ std::map<std::string, std::string> properties; };
	//virtual ~Properties();
	//Properties(const Properties& other) {};
	//Properties& operator=(const Properties& other);

	void load(const std::string_view propertypath);
	void save(void);
	std::string getString(std::string key, std::string defaultVal);
	int getInt(std::string key, int defaultVal);
};

#endif /* PROPERTIES_H_ */
