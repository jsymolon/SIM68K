/*
 * MemoryCtrl.h
 *
 *  Created on: Aug 14, 2021
 *      Author: jsymolon
 */

#ifndef MEMORYCTRL_H_
#define MEMORYCTRL_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/scrolwin.h>
#include <sstream>

class MemoryCtrl: public wxPanel {
private:
	wxScrolledWindow* internal;
	wxFont m_font;
	wxColour m_backgroundColour = wxColour("WHITE");
	wxColour m_fontColour = wxColour("BLACK");
	wxColour m_gutterColour = wxColour("GREY");
	wxColour m_highlightColour = wxColour(0, 192, 255, 64);
	int gutterWidth = 20; // how wide the gutter or breakpoint ind areas is
	int halfGutterWidth = 10; // 1/2 of above
	int halfFont = 5;
	float lineHeight = 12.0;
	wxSize fontPixelSize;
	wxSize virtSize = wxSize(100, 200);
	wxRect updateRect;
	int viewStartX = 0;
	int viewStartY = 0;
	int adjScrollPos = 3;

	unsigned int startline = 0;
	unsigned int endline = 0;

public:
	MemoryCtrl(void); // for testing
	MemoryCtrl(wxWindow *parent, wxWindowID id) : wxPanel(parent, wxID_ANY) {
//		//m_colour = wxColour("WHITE");
		wxFont m_font(10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
		fontPixelSize = m_font.GetPixelSize();
		this->SetBackColour(*wxRED);
		this->SetBackgroundColour(*wxRED);

		wxBoxSizer *topSizer = new wxBoxSizer( wxVERTICAL );
		internal = new wxScrolledWindow(this, id, wxDefaultPosition, wxDefaultSize, wxEXPAND);
		//		internal->SetFont(m_font);
		//		internal->SetScrollRate(fontPixelSize.x, fontPixelSize.y);
		//		internal->SetBackgroundColour(*wxBLUE);
		topSizer->Add(internal, 1, wxEXPAND | wxALL, 1);

//		topSizer->Add(	new wxTextCtrl( this, wxID_ANY, "My text.",
//				wxDefaultPosition, wxSize(100,60), wxTE_MULTILINE),
//		1, // make vertically stretchable
//		wxEXPAND| // make horizontally stretchable
//		wxALL, // and make border all around
//		10 );


		SetSizer(topSizer);
		topSizer->Fit(this);
		topSizer->SetSizeHints(this);
	}

	const wxFont& GetTextFont() const {
		return m_font;
	}
	void SetTextFont(const wxFont &font) {
		m_font = font;
		this->SetFont(font);
		fontPixelSize = font.GetPixelSize();
		SetVirtualSize(virtSize);
	}

	const wxColour& GetBackColour() const {
		return m_backgroundColour;
	}
	void SetBackColour(const wxColour &colour) {
		m_backgroundColour = colour;
	}

	const wxColour& GetFontColour() const {
		return m_fontColour;
	}
	void SetFontColour(const wxColour &colour) {
		m_fontColour = colour;
	}

	const wxColour& GetGutterColour() const {
		return m_gutterColour;
	}
	void SetGutterColour(const wxColour &colour) {
		m_gutterColour = colour;
	}

	void SetScrollAndSize(int nLines);

	void paintRect(wxDC &dc);

	void paintEvent(wxPaintEvent &evt);
	void paintNow();

	void render(wxDC &dc);

	void adjustScrollPos(void);

	void OnEraseBackGround(wxEraseEvent &event);
	std::string buildDataLine(unsigned long addr);

	DECLARE_EVENT_TABLE()
};

#endif /* MEMORYCTRL_H_ */
