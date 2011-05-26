///////////////////////////////////////////////////////////
//  ErrorLog.cpp
//  Implementation of the Class ErrorLog
//  Created on:      17-Apr-2011 5:25:03 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#include "ErrorLog.h"


ErrorLog::ErrorLog(){

}



ErrorLog::~ErrorLog(){

}

// streams all of the private error log data
ostream &operator<<(ostream &stream, ErrorLog elog)
{
	stream << elog.m_timestamp << " ";
	stream << elog.m_code << " ";
	stream << elog.m_missionid << " ";
	stream << elog.m_robotid << " ";
	stream << elog.m_camera << " ";
	stream << std::endl;

	return stream;
}