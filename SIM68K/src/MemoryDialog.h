/*
 * MemoryFrame.h
 *
 *  Created on: Aug 19, 2021
 *      Author: jsymolon
 */

#ifndef MEMORYDIALOG_H_
#define MEMORYDIALOG_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/sizer.h>

#include "MemoryCtrl.h"
#include <string>

class SIM68K;

class MemoryDialog: public wxDialog {
public:

	MemoryDialog(const wxString &title, const wxPoint &pos, const wxSize &size, SIM68K *sim68k);
	virtual ~MemoryDialog();

	void BuildFrame(wxBoxSizer *topsizer);
protected:
	SIM68K* sim68k;
	wxTextCtrl *fromCtrl;
	wxTextCtrl *toCtrl;
	wxTextCtrl *bytesCtrl;
	wxTextCtrl *addressCtrl;
	MemoryCtrl *memoryCtrl;
};

#endif /* MEMORYDIALOG_H_ */
