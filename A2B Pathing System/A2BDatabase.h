///////////////////////////////////////////////////////////
//  A2BDatabase.h
//  Implementation of the Class A2BDatabase
//  Created on:      17-Apr-2011 5:24:52 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#if !defined(EA_D11EACC8_E9A2_4023_B545_34E8FB6B6577__INCLUDED_)
#define EA_D11EACC8_E9A2_4023_B545_34E8FB6B6577__INCLUDED_

#include "Mission.h"
#include "ErrorLog.h"
#include "iDatabase.h"

#include "Robot.h"

#include <vector>
using std::vector;

class A2BDatabase : public iDatabase
{

public:
	A2BDatabase();
	virtual ~A2BDatabase();
	Mission *m_Mission;
	ErrorLog *m_ErrorLog;

	int currentMission();
	bool endMission(Point end);
	void insertError(ErrorLog code);
	int startMission(Point start, Point dest);
	void error(ErrorLog err);
	Robot getRobot();
	void update(string query);

private:
	Mission m_currentMisson;
//	hconnection m_db;
	vector<ErrorLog> m_tempqueue;

	void initialization();

};
#endif // !defined(EA_D11EACC8_E9A2_4023_B545_34E8FB6B6577__INCLUDED_)
