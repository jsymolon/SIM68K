#ifndef PANELCTRL_H_
#define PANELCTRL_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/textctrl.h>

class PanelCtrl: public wxPanel {
public:
	PanelCtrl(wxWindow *parent, wxWindowID id) : wxPanel(parent, id) {
		this->SetBackgroundColour(*wxRED);
		wxBoxSizer *topSizer = new wxBoxSizer( wxVERTICAL );
		topSizer->Add(	new wxTextCtrl( this, wxID_ANY, "My text.",
				wxDefaultPosition, wxSize(100,60), wxTE_MULTILINE),
		1, // make vertically stretchable
		wxEXPAND| // make horizontally stretchable
		wxALL, // and make border all around
		10 );
		SetSizer(topSizer);
		topSizer->Fit(this);
		topSizer->SetSizeHints(this);
	}


};

#endif
