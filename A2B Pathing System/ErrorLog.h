///////////////////////////////////////////////////////////
//  ErrorLog.h
//  Implementation of the Class ErrorLog
//  Created on:      17-Apr-2011 5:25:03 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#if !defined(EA_EA19BD75_32E9_4974_B257_8A5C8BBFE800__INCLUDED_)
#define EA_EA19BD75_32E9_4974_B257_8A5C8BBFE800__INCLUDED_

#include <iostream>
using std::ostream;

class ErrorLog
{

public:
	ErrorLog();
	virtual ~ErrorLog();
	friend ostream &operator<<(ostream &stream, ErrorLog elog);
private:
	int m_camera;
	int m_code;
	int m_missionid;
	int m_robotid;
	int m_timestamp;
};
#endif // !defined(EA_EA19BD75_32E9_4974_B257_8A5C8BBFE800__INCLUDED_)
