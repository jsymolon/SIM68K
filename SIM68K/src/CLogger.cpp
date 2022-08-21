#include "CLogger.h"
#include <time.h>
#include <stdio.h>
#include <stdarg.h>

const std::string CLogger::m_sFileName = "Log.txt";
CLogger *CLogger::m_pThis = NULL;
std::ofstream CLogger::m_Logfile;

//--------------------------------------------------------------------------------
CLogger::CLogger() {

}

//--------------------------------------------------------------------------------
const std::string CLogger::CurrentDateTime() {
	//time_t now = time(NULL);
	struct tm tstruct;
	char buf[LOGLINEMAX];
	//localtime_r(&tstruct, &now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
	return (buf);
}

//--------------------------------------------------------------------------------
CLogger* CLogger::GetLogger() {
	if (m_pThis == NULL) {
		m_pThis = new CLogger();
		m_Logfile.open(m_sFileName.c_str(), std::ios::out | std::ios::app);
	}
	return (m_pThis);
}

//--------------------------------------------------------------------------------
void CLogger::Log(const char *format, ...) {
	char *sMessage = NULL;
	int nLength = 0;
	va_list args;
	va_start(args, format);
	//  Return the number of characters in the string referenced the list of arguments.
	// _vscprintf doesn't count terminating '\0' (that's why +1)
	nLength = vprintf(format, args) + 1;
	sMessage = new char[nLength];
	vsprintf(sMessage, format, args);
	m_Logfile << CurrentDateTime() << ":\t";
	m_Logfile << sMessage << "\n";
	va_end(args);
	delete[] sMessage;
}

//--------------------------------------------------------------------------------
void CLogger::Log(const std::string &sMessage) {
	m_Logfile << CurrentDateTime() << ":\t";
	m_Logfile << sMessage << "\n";
}

//--------------------------------------------------------------------------------
CLogger& CLogger::operator<<(const std::string &sMessage) {
	m_Logfile << "\n" << CurrentDateTime() << ":\t";
	m_Logfile << sMessage << "\n";
	return (*this);
}
