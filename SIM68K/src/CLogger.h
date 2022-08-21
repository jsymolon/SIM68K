/*
 * CLogger.h
 *
 *  Class to encapsulate the log to text window and to a file
 */

#ifndef CLOGGER_H_
#define CLOGGER_H_

#include <fstream>
#include <iostream>
#include <cstdarg>
#include <string>

#define LOGLINEMAX 80

class CLogger {
public:
	void Log(const std::string &sMessage);
	void Log(const char *format, ...);
	CLogger& operator<<(const std::string &sMessage);
	static CLogger* GetLogger();
	static const std::string CurrentDateTime();
private:
	CLogger();
	CLogger(const CLogger&) {
	}
	; // copy constructor is private
	CLogger& operator=(const CLogger&) {
		return (*this);
	}
	;  // assignment operator is private
	static const std::string m_sFileName;
	static CLogger *m_pThis;
	static std::ofstream m_Logfile;
};

#endif /* CLOGGER_H_ */
