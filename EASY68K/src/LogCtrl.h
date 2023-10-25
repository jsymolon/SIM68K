#ifndef LOGCTRL_H_
#define LOGCTRL_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/scrolwin.h>

class LogCtrl: public wxTextCtrl {
private:
	wxFont m_font;
	wxColour m_backgroundColour = wxColour("WHITE");
	wxColour m_breakOpaqueColour = wxColour(0, 255, 0, wxALPHA_OPAQUE);
	wxColour m_breakTranColour = wxColour(0, 255, 0, wxALPHA_TRANSPARENT);
	wxColour m_fontColour = wxColour(0, 0, 0, wxALPHA_OPAQUE);
	wxColour m_gutterColour = wxColour("GREY");
	wxColour m_highlightColour = wxColour(0, 192, 255, wxALPHA_OPAQUE);
	wxSize virtSize = wxSize(100, 200);
	wxSize fontPixelSize;

public:
	LogCtrl(wxWindow *parent, wxWindowID id = wxID_ANY, const wxString &value =
			"", const wxPoint &pos = wxDefaultPosition, const wxSize &size =
			wxDefaultSize, long style = 0, const wxValidator &validator =
			wxDefaultValidator, const wxString &name = wxTextCtrlNameStr) :
			wxTextCtrl(parent, id, value, pos, size, style, validator, name) {

		wxFont m_font_l(10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL,
				wxFONTWEIGHT_BOLD);
		m_font = m_font_l;
		this->SetFont(m_font);
		fontPixelSize = m_font.GetPixelSize();
		SetBackgroundColour(*wxWHITE);
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

	// ------------------------------------------------------------------------------------------------
	void logMsg(const std::string &msg) {
		SetInsertionPointEnd();
		AppendText(msg);
		SetInsertionPointEnd();
		AppendText(wxT("\n"));
	}

	// ------------------------------------------------------------------------------------------------
	void logMsg(const char *msg) {
		SetInsertionPointEnd();
		std::string msgr;
		msgr.append(msg);
		msgr.append("\n");
		AppendText(msgr);
	}

	void SetScrollAndSize(int nLines);

};

#endif
