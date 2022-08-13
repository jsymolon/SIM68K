/*
 * NOTE: adapted from the SIM68K project
 *  Author: Charles Kelly
 *          www.easy68k.com
 *  Created on: May 17, 2021
 *      Author: jsymolon
 */

#ifndef SIM68K_H_
#define SIM68K_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class SIM68K : public wxApp {
public:
	SIM68K();
	virtual ~SIM68K();

	virtual bool OnInit();

};

DECLARE_APP(SIM68K)

#endif /* SIM68K_H_ */
