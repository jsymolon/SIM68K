#ifndef SOURCEEDITCTRL_H_
#define SOURCEEDITCTRL_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/scrolwin.h>
const uint8_t LINE_LEN = 50;

class SourceEditCtrl: public wxScrolled<wxWindow> {
private:
	wxTextCtrl *editCtrl;

	wxColour m_backgroundColour = wxColour("WHITE");
	wxColour m_breakOpaqueColour = wxColour(0, 255, 0, wxALPHA_OPAQUE);
	wxColour m_breakTranColour = wxColour(0, 255, 0, wxALPHA_TRANSPARENT);
	wxColour m_fontColour = wxColour(0, 0, 0, wxALPHA_OPAQUE);
	wxColour m_gutterColour = wxColour("GREY");
	wxColour m_highlightColour = wxColour(0, 192, 255, wxALPHA_OPAQUE);
	int gutterWidth = 20; // how wide the gutter or breakpoint ind areas is
	int halfGutterWidth = 10; // 1/2 of above
	int halfFont = 5;
	float lineHeight = 12.0;
	wxSize fontPixelSize;
	int numberSrcLines = 1;
	wxSize virtSize = wxSize(100, 200);
	wxRect updateRect;
	int viewStartX = 0;
	int viewStartY = 0;
	int adjScrollPos = 3;

	unsigned int startline = 0;
	unsigned int endline = 0;

public:
	SourceEditCtrl(wxWindow *parent, wxWindowID id = wxID_ANY);

	const wxFont& GetTextFont() const {
		return (m_font);
	}
	void SetTextFont(const wxFont &font) {
		this->SetFont(font);
		fontPixelSize = font.GetPixelSize();
		SetVirtualSize(virtSize);
	}

	const wxColour& GetBackColour() const {
		return (m_backgroundColour);
	}
	void SetBackColour(const wxColour &colour) {
		m_backgroundColour = colour;
	}

	const wxColour& GetFontColour() const {
		return (m_fontColour);
	}
	void SetFontColour(const wxColour &colour) {
		m_fontColour = colour;
	}

	const wxColour& GetGutterColour() const {
		return (m_gutterColour);
	}
	void SetGutterColour(const wxColour &colour) {
		m_gutterColour = colour;
	}

	void SetScrollAndSize(int nLines);

	void OnScroll(wxScrollWinEvent &event);

	void adjustScrollPos(void);

	void SetContent(const wxString &content);

	wxString GetContent(void);

	// some useful events
	/*
	 void mouseMoved(wxMouseEvent& event);
	 void mouseDown(wxMouseEvent& event);
	 void mouseWheelMoved(wxMouseEvent& event);
	 void mouseReleased(wxMouseEvent& event);
	 void rightClick(wxMouseEvent& event);
	 void mouseLeftWindow(wxMouseEvent& event);
	 void keyPressed(wxKeyEvent& event);
	 void keyReleased(wxKeyEvent& event);
	 */

DECLARE_EVENT_TABLE()
};

#endif
