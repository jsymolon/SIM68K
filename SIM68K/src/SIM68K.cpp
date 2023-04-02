/*
 * SIM68K.cpp
 *
 *  Created on: May 17, 2021
 *      Author: jsymolon
 */

#include "SIM68K.h"
#include "MainFrame.h"
#include "extern.h"

#ifndef TESTINGON
IMPLEMENT_APP(SIM68K) // A macro that tells wxWidgets to create an instance of our application
#endif

SIM68K::SIM68K() {
}

SIM68K::~SIM68K() {
}

bool SIM68K::OnInit() {
	mainframe = new MainFrame(_("SIM68K"), wxDefaultPosition, wxSize(400, 600), this);
	mainframe->Show(true); // show the window
	SetTopWindow(mainframe); // and finally, set it as the main window
	return (true);
}
