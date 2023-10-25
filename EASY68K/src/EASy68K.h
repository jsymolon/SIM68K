/*
 * NOTE: adapted from the SIM68K project
 *  Author: Charles Kelly
 *          www.easy68k.com
 *  Created on: May 17, 2021
 *      Author: jsymolon
 */

#ifndef SRC_EASY68K_H_
#define SRC_EASY68K_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class EASy68K: public wxApp {
public:
	virtual bool OnInit();

};

DECLARE_APP(EASy68K)

#endif /* SRC_EASY68K_H_ */
