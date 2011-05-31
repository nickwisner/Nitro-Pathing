///////////////////////////////////////////////////////////
//  ErrorLog.cpp
//  Implementation of the Class ErrorLog
//  Created on:      17-Apr-2011 5:25:03 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#include "ErrorLog.h"
#include <string>
using std::string;


ErrorLog::ErrorLog(){

}

ErrorLog::ErrorLog(int code, int missionid, int camera, int robotid, string timestamp): m_code(code), m_missionid(missionid), m_camera(camera), m_robotid(robotid)
{
	m_timestamp = timestamp;
}


ErrorLog::~ErrorLog(){

}

// streams all of the private error log data
ostream &operator<<(ostream &stream, ErrorLog elog)
{
	stream << elog.m_missionid << " ";
	stream << elog.m_robotid << " ";
	stream << elog.m_camera << " ";
	stream << elog.m_code << " ";
	stream << elog.m_timestamp;	// built in '\n'

	return stream;
}