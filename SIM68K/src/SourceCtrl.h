#ifndef SOURCECTRL_H_
#define SOURCECTRL_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/scrolwin.h>
const uint8_t LINE_LEN = 50;

class SourceCtrl: public wxScrolled<wxWindow> {
private:
	wxFont m_font;
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
	SourceCtrl(wxWindow *parent, wxWindowID id = wxID_ANY, const wxPoint &pos = wxDefaultPosition,
			const wxSize &size = wxDefaultSize, long style =
			wxTAB_TRAVERSAL, const wxString &name = wxPanelNameStr) :
			wxScrolled(parent, id, pos, size, style | wxFULL_REPAINT_ON_RESIZE, name) {
		//m_colour = wxColour("WHITE");
		wxFont m_font(10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
		this->SetFont(m_font);
		fontPixelSize = m_font.GetPixelSize();
		halfFont = int((fontPixelSize.y - 4) / 2); // minus to fit the circle in font height
		SetVirtualSize(virtSize);
		SetScrollRate(fontPixelSize.x, fontPixelSize.y);
		SetBackgroundColour(*wxWHITE);

		//Connect(wxEVT_PAINT, wxPaintEventHandler(SourceCtrl::OnPaint));
	}

	const wxFont& GetTextFont() const {
		return (m_font);
	}
	void SetTextFont(const wxFont &font) {
		m_font = font;
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

	void paintRect(wxDC &dc);

	void paintEvent(wxPaintEvent &evt);
	void paintNow();

	void render(wxDC &dc);

	void adjustScrollPos(void);

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

	void OnEraseBackGround(wxEraseEvent &event);

DECLARE_EVENT_TABLE()
};

#endif
