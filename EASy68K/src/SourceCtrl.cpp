#include "SourceCtrl.h"

#include "extern.h"
#include <iterator>

BEGIN_EVENT_TABLE(SourceCtrl, wxScrolledWindow)
// some useful events
/*
 EVT_MOTION(BasicDrawPane::mouseMoved)
 EVT_LEFT_DOWN(BasicDrawPane::mouseDown)
 EVT_LEFT_UP(BasicDrawPane::mouseReleased)
 EVT_RIGHT_DOWN(BasicDrawPane::rightClick)
 EVT_LEAVE_WINDOW(BasicDrawPane::mouseLeftWindow)
 EVT_KEY_DOWN(BasicDrawPane::keyPressed)
 EVT_KEY_UP(BasicDrawPane::keyReleased)
 EVT_MOUSEWHEEL(BasicDrawPane::mouseWheelMoved)
 */

// catch paint events
END_EVENT_TABLE()

//----------------------------------------------------------------------------------
SourceCtrl::SourceCtrl(wxWindow *parent, wxWindowID id) :
		wxScrolled<wxWindow>(parent, id) {
	//m_colour = wxColour("WHITE");
	wxFont m_font(10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL,
			wxFONTWEIGHT_BOLD);
	SetFont(m_font);
	fontPixelSize = m_font.GetPixelSize();
	halfFont = int((fontPixelSize.y - 4) / 2); // minus to fit the circle in font height
	//SetVirtualSize(virtSize);
	SetBackgroundColour(*wxRED);

	// Create a text control for editing
	editCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
			wxDefaultSize, wxTE_MULTILINE);

	wxBoxSizer *sizersw = new wxBoxSizer(wxVERTICAL);
	sizersw->Add(editCtrl, 1, wxEXPAND | wxALL);
	SetSizer(sizersw);
}

//----------------------------------------------------------------------------------
void SourceCtrl::SetScrollAndSize(int nLines) {
	// dont change x, set y to number of lines * fontheight
	virtSize.y = (nLines + 1) * fontPixelSize.y;
	SetVirtualSize(virtSize);
	SetScrollPos(wxVERTICAL, 0, false); //set scrollbar at top
	SetScrollbar(wxVERTICAL, 0, nLines + 1, nLines + 1); // 1st is visible lines, 2nd total
}

//----------------------------------------------------------------------------------
// some useful events
/*
 void SourceCtrl::mouseMoved(wxMouseEvent& event) {}
 void SourceCtrl::mouseDown(wxMouseEvent& event) {}
 void SourceCtrl::mouseWheelMoved(wxMouseEvent& event) {}
 void SourceCtrl::mouseReleased(wxMouseEvent& event) {}
 void SourceCtrl::rightClick(wxMouseEvent& event) {}
 void SourceCtrl::mouseLeftWindow(wxMouseEvent& event) {}
 void SourceCtrl::keyPressed(wxKeyEvent& event) {}
 void SourceCtrl::keyReleased(wxKeyEvent& event) {}
 */

void SourceCtrl::OnScroll(wxScrollWinEvent &event) {
	// Update the scroll position
	int scrollX = GetScrollPos(wxHORIZONTAL);
	int scrollY = GetScrollPos(wxVERTICAL);
	editCtrl->SetScrollPos(wxHORIZONTAL, scrollX);
	editCtrl->SetScrollPos(wxVERTICAL, scrollY);
}

//----------------------------------------------------------------------------------
// we repaint in drawing, don't need to have separate one
void SourceCtrl::adjustScrollPos(void) {
	// Figure out if the PC is w/in Viewport (if running)
	wxSize sz = GetClientSize();
	int vpstart = viewStartY / fontPixelSize.y;
	int vpend = (sz.y / fontPixelSize.y) + vpstart;
	int vpmid = vpend / 2;
	int sp = GetScrollPos(wxVERTICAL);
//		// scroll window to put hightlight in middle, w/ little fuzz to
//		// prevent scroll ALL the time, 1 big scroll once, vs little ones
//		// every time
//		//int moveScrollPos = (yPtPC - vpmid) / 2; // cut sensitivity "vibration"
//		int moveScrollPos = sp;
//		// check for the PC line outsize of the viewport, force scroll
//		if (yPtPC < vpstart && vpstart > 0 && moveScrollPos > adjScrollPos)
//			moveScrollPos -= adjScrollPos;
//		if (yPtPC >= vpend)
//			moveScrollPos += adjScrollPos;
//		if (moveScrollPos != sp) {
//			Scroll(0, moveScrollPos);
//		}
//		this->GetParent()->Layout();
//		std::cout << "Scroll: PC:" << PC << " PC l:" << yPtPC << " sp:" << sp << " s:" << vpstart << " m:" << vpmid << " e:" << vpend
//				<< " moveScroll:" << moveScrollPos << " pixsz:" << fontPixelSize.y << "\n";
}

//----------------------------------------------------------------------------------
void SetContent(wxString content) {

}

//----------------------------------------------------------------------------------
wxString GetContent(void) {
}

