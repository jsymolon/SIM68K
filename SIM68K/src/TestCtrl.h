#ifndef TESTCTRL_H_
#define TESTCTRL_H_

#include "wx/wx.h"
#include <wx/scrolwin.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <iostream>

class TestCtrl: public wxScrolledWindow {
public:
	TestCtrl(wxWindow *parent, wxWindowID id) :
			wxScrolledWindow(parent, id) {
		wxBoxSizer *topsizer = new wxBoxSizer(wxVERTICAL);
		wxBoxSizer *sizer_horiz = new wxBoxSizer(wxHORIZONTAL);
		wxStaticText *lbOutputImage = new wxStaticText(this, wxID_ANY, wxT("Output file name"));
		wxTextCtrl *leOutputImage = new wxTextCtrl(this, wxID_ANY, wxT("Output file name"));
		sizer_horiz->Add(lbOutputImage, 1, wxEXPAND);
		sizer_horiz->Add(leOutputImage, 6, wxEXPAND);
		topsizer->Add(sizer_horiz, 0, wxEXPAND);

		topsizer->SetSizeHints(this);
		this->SetSizer(topsizer);

		// this part makes the scrollbars show up
		this->FitInside();		// ask the sizer about the needed size
		this->SetScrollRate(5, 5);
	}

};

#endif /* TESTCTRL_H_ */
