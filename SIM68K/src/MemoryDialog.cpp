#include "SourceCtrl.h"
#include <wx/sizer.h>

#include "MemoryDialog.h"
#include "PanelCtrl.h"

// ------------------------------------------------------------------------------------------------
MemoryDialog::~MemoryDialog() {
}

// ------------------------------------------------------------------------------------------------
MemoryDialog::MemoryDialog(const wxString &title, const wxPoint &pos, const wxSize &size, SIM68K *sim68k) :
		wxDialog((wxWindow*) NULL, -1, title, pos, size, wxRESIZE_BORDER) {
	this->sim68k = sim68k;

	addressCtrl = nullptr;
	bytesCtrl = nullptr;
	fromCtrl = nullptr;
	toCtrl = nullptr;

	wxBoxSizer *topsizer = new wxBoxSizer(wxVERTICAL);

	//BuildFrame(topsizer);
	// put in the scrolling area
	memoryCtrl = new MemoryCtrl(this, wxID_ANY);
	topsizer->Add(memoryCtrl, 0, wxEXPAND | wxALIGN_LEFT, 1);

//	PanelCtrl* panelCtrl = new PanelCtrl(this, wxID_ANY);
//	topsizer->Add(panelCtrl, wxEXPAND);

	SetSizer(topsizer);
	//Centre();
	Layout();
	Show();
}

// ------------------------------------------------------------------------------------------------
void MemoryDialog::BuildFrame(wxBoxSizer *topsizer) {
	wxBoxSizer *ctrlsizer1 = new wxBoxSizer(wxHORIZONTAL);

	wxStaticText *text1;
	ctrlsizer1->Add(text1 = new wxStaticText(this, wxID_ANY, "From: $"), 0);
	fromCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(100, -1), wxHSCROLL);
	ctrlsizer1->Add(fromCtrl, 0, wxALIGN_LEFT, 0);

	ctrlsizer1->Add(text1 = new wxStaticText(this, wxID_ANY, "To: $"), 0);
	toCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(100, -1), wxHSCROLL);
	ctrlsizer1->Add(toCtrl, 0, wxALIGN_LEFT, 0);

	ctrlsizer1->Add(text1 = new wxStaticText(this, wxID_ANY, "Byte: $"), 0);
	bytesCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(100, -1), wxHSCROLL);
	ctrlsizer1->Add(bytesCtrl, 0, wxALIGN_LEFT, 0);

	wxBoxSizer *ctrlsizer2 = new wxBoxSizer(wxHORIZONTAL);
	ctrlsizer1->Add(text1 = new wxStaticText(this, wxID_ANY, "Address: $"), 0);
	addressCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(100, -1), wxHSCROLL);
	ctrlsizer1->Add(addressCtrl, 0, wxALIGN_LEFT, 0);

	wxBoxSizer *outerctrlsizer = new wxBoxSizer(wxVERTICAL);

	outerctrlsizer->Add(ctrlsizer1, 0, wxALIGN_LEFT, 0);
	outerctrlsizer->Add(ctrlsizer2, 0, wxALIGN_LEFT, 0);

	topsizer->Add(outerctrlsizer, 0, wxALIGN_LEFT, 1);
	memoryCtrl = new MemoryCtrl(this, wxID_ANY);
	topsizer->Add(memoryCtrl, 0, wxALIGN_LEFT, 1);
}
