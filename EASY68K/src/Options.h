/*
 * Options.h
 *
 *  Created on: Aug 25, 2023
 *      Author: jsymolon
 */

#ifndef OPTIONS_H_
#define OPTIONS_H_

struct Options {
	bool listFlag = true; // Gen list file
	bool autoSaveFlag = true; // auto save
	bool objFlag = true; // Gen S rec
	bool CEXflag = true; // Constants expanded
	bool BITflag = true; // Assemble BIT field
	bool CREflag = true; // Cross Reference
	bool MEXflag = true; // Macros expanded
	bool SEXflag = true; // Structured expanded
	bool WARflag = true; // Show Warnings

	// editor ops
	// font
	// font size
	// fixed tab
	// assembly / fixed
	// env - Auto indent
	// env - real tabs

	// colors
	// code, comment, directive, label, macro/other, structure, text, backgroud
	// text attr - bold, italic, underline
	// color preset ...
};

#endif /* OPTIONS_H_ */
