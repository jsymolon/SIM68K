/*
 * extern.cpp
 *
 *  Created on: Aug 5, 2023
 *      Author: jsymolon
 */

#include "extern.h"

// problem w/ unique_ptr, SIM68K "new" doesn't recognize ...
MainFrame *mainframe;
LogCtrl *logWindow;

const wxColor &DEFAULT_CODE_COLOR = wxColour("wxBLACK");
const wxColor &DEFAULT_UNKNOWN_COLOR = wxColour("DARK OLIVE GREEN");
const wxColor &DEFAULT_DIRECTIVE_COLOR = wxColour("GREEN");
const wxColor &DEFAULT_COMMENT_COLOR = wxColour("BLUE");
const wxColor &DEFAULT_LABEL_COLOR = wxColour("PURPLE");
const wxColor &DEFAULT_STRUCTURE_COLOR = wxColour("MAROON");
const wxColor &DEFAULT_ERROR_COLOR = wxColour("RED");
const wxColor &DEFAULT_TEXT_COLOR = wxColour("AQUAMARINE");
const wxColor &DEFAULT_BACK_COLOR = wxColour("WHITE");

char NEW_PAGE_MARKER[] =
		"<------------------------------ PAGE ------------------------------>";
