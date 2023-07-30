#include "LogCtrl.h"
#include "extern.h"
#include <iterator>

//----------------------------------------------------------------------------------
void LogCtrl::SetScrollAndSize(int nLines) {
	// dont change x, set y to number of lines * fontheight
	virtSize.y = (nLines + 1) * fontPixelSize.y;
	SetVirtualSize(virtSize);
	SetScrollPos(wxVERTICAL, 0, false); //set scrollbar at top
	SetScrollbar(wxVERTICAL, 0, nLines + 1, nLines + 1); // 1st is visible lines, 2nd total
}
