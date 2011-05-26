/********************************************************************
* Constructors:
*	ErrorLogger() - The base constructor connects to the database.
*	
*	virtual ~ErrorLogger() - Closes the connection to the database.
* 
* Mutators:
*	Edge getEdge() - Returns a copy of m_edge
*	
*	int getCommandSize() - Returns the number of robot commands
*	inside of the list
*	
*	RobotCommand popCommand() - Returns the front of the robot
*	command list and then removes it from list.
*	
* 
* Methods:
*	int translateUp(Point start, Point end, int heading) - From the
*	start and end point ( in pixels ) and then translates them into a
*	robot command which it pushes onto the list. Returns a int which
*	should be caught back into heading. This function is only called
*	if the heading is 1. Meaning the robot is facing up.
**********************************************************************/

/*	CURRENTLY IMPLEMENTED AS A STUB FILE  */
#ifndef ERRORLOGGER_H
#define ERRORLOGGER_H

#include "Mission.h"
#include "ErrorLog.h"
#include "iDatabase.h"

#include "Robot.h"
#include <string>
#include <fstream>

#include <vector>
using std::vector;
using std::string;

class ErrorLogger : public iDatabase
{

public:
	ErrorLogger();
	virtual ~ErrorLogger();

	int getCurrentMission();
	
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
	string m_errFName;
	ofstream m_errStream;

};
#endif 