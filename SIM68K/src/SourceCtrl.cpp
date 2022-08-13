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
EVT_PAINT(SourceCtrl::paintEvent)
EVT_ERASE_BACKGROUND(SourceCtrl::OnEraseBackGround)
END_EVENT_TABLE()

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

//----------------------------------------------------------------------------------
// we repaint in drawing, don't need to have separate one
void SourceCtrl::OnEraseBackGround(wxEraseEvent &event) {
}

//----------------------------------------------------------------------------------
// we repaint in drawing, don't need to have separate one
void SourceCtrl::adjustScrollPos(void) {
	// Figure out if the PC is w/in Viewport (if running)
	if (mainframe->isTracing()) {
		wxSize sz = GetClientSize();
		int vpstart = viewStartY / fontPixelSize.y;
		int vpend = (sz.y / fontPixelSize.y) + vpstart;
		int vpmid = vpend / 2;
		int sp = this->GetScrollPos(wxVERTICAL);
		int yPtPC = memory->getIndexOfSrcFromAddr(PC);
		if (yPtPC > 0) {
			// scroll window to put hightlight in middle, w/ little fuzz to
			// prevent scroll ALL the time, 1 big scroll once, vs little ones
			// every time
			//int moveScrollPos = (yPtPC - vpmid) / 2; // cut sensitivity "vibration"
			int moveScrollPos = sp;
			// check for the PC line outsize of the viewport, force scroll
			if (yPtPC < vpstart && vpstart > 0 && moveScrollPos > adjScrollPos)
				moveScrollPos -= adjScrollPos;
			if (yPtPC >= vpend)
				moveScrollPos += adjScrollPos;
			if (moveScrollPos != sp) {
				Scroll(0, moveScrollPos);
			}
			this->GetParent()->Layout();
			std::cout << "Scroll: PC:" << PC << " PC l:"<< yPtPC << " sp:" << sp << " s:" << vpstart << " m:" << vpmid << " e:" << vpend
					<< " moveScroll:" << moveScrollPos << " pixsz:" << fontPixelSize.y << "\n";
		}
	}
}

//----------------------------------------------------------------------------------
/*
 * Called by the system of by wxWidgets when the panel needs
 * to be redrawn. You can also trigger this call by
 * calling Refresh()/Update().
 */

void SourceCtrl::paintEvent(wxPaintEvent &evt) {
	wxPaintDC dc(this);
	// Find Out where the window is scrolled to
	GetViewStart(&viewStartX, &viewStartY);

	// Find out how much the scrollbar moves each unit in pixels
	int xUnit = 0, yUnit = 0;
	GetScrollPixelsPerUnit(&xUnit, &yUnit);
	viewStartX *= xUnit;
	viewStartY *= yUnit;

	// Get the update rect list
	wxRegionIterator upd(GetUpdateRegion());
	while (upd) {
		updateRect.x = upd.GetX() + viewStartX;
		updateRect.y = upd.GetY();
		updateRect.width = upd.GetW();
		updateRect.height = upd.GetH();
		startline = (updateRect.y + viewStartY) / fontPixelSize.y;
		endline = (updateRect.height / fontPixelSize.y) + startline + 1;
		endline = endline > memory->getNumberOfSourceLines() ? memory->getNumberOfSourceLines() : endline;
		startline = startline > endline ? endline : startline;
		// Repaint this rectangle
		//std::cout << "UR x:" << updateRect.x << " y:" << updateRect.y << " w:" << updateRect.width << " h:" << updateRect.height << "\n";
		paintRect(dc);
		upd++;
	}
	adjustScrollPos();
}

//----------------------------------------------------------------------------------
void SourceCtrl::paintRect(wxDC &dc) {
	unsigned int x = gutterWidth;
	unsigned int y = (startline * fontPixelSize.y) - viewStartY; // set y to int font lines
	//std::cout << "L s:" << startline << " e:" << endline << " ps:" << fontPixelSize.y << " y:" << y << "\n";

	// clear the update rect to background
	dc.SetBrush(wxBrush(m_backgroundColour));
	dc.SetPen(wxPen(m_backgroundColour));
	dc.DrawRectangle(updateRect);

	// add the gutter
	dc.SetBrush(wxBrush(m_gutterColour));
	dc.SetPen(wxPen(m_gutterColour));
	dc.DrawRectangle(updateRect.x, updateRect.y, gutterWidth, updateRect.height);

	wxBrush emptyBP = wxBrush(m_gutterColour);
	wxBrush setBP = wxBrush();
	wxBrush fontB = wxBrush(m_fontColour);
	dc.SetPen(wxPen(m_fontColour));

	for (unsigned int idx = startline; idx < endline; idx++) {
		std::string_view line = memory->getSourceLine(idx);
		// is this line a breakpoint-able line
		auto iter = memory->srcLineToAddr.find(idx);
		if (iter != memory->srcLineToAddr.end()) {
			// if !breakpoint set
			dc.SetBrush(emptyBP);
			dc.DrawCircle(0 + halfFont + 1, y + halfFont + 2, halfFont);
			// is this line ... PC hightlight ?
			if (iter->second == PC) {
				dc.SetBrush(wxBrush(m_highlightColour));
				dc.SetPen(wxPen(m_highlightColour));
				dc.DrawRectangle(updateRect.x + gutterWidth, y, updateRect.width - gutterWidth, fontPixelSize.y);
				dc.SetPen(wxPen(m_fontColour));
			}
		}
		dc.SetBrush(fontB);
		dc.SetTextForeground(m_fontColour);
		dc.DrawText(std::string(line).data(), x, y);
		dc.DrawLine(0, y, 50, y);
		y += fontPixelSize.y;
	}
}

//----------------------------------------------------------------------------------
/*
 * Alternatively, you can use a clientDC to paint on the panel
 * at any time. Using this generally does not free you from
 * catching paint events, since it is possible that e.g. the window
 * manager throws away your drawing when the window comes to the
 * background, and expects you will redraw it when the window comes
 * back (by sending a paint event).
 *
 * In most cases, this will not be needed at all; simply handling
 * paint events and calling Refresh() when a refresh is needed
 * will do the job.
 */
void SourceCtrl::paintNow() {
	wxClientDC dc(this);
	render(dc);
}

//----------------------------------------------------------------------------------
/*
 * Here we do the actual rendering. I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g. wxPaintDC or wxClientDC) is used.
 */
void SourceCtrl::render(wxDC &dc) {
	unsigned int x = 20;
	unsigned int y = 0;
	dc.DrawText(wxT("TEST"), x, y);
}
