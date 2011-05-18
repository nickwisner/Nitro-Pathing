///////////////////////////////////////////////////////////
//  iRobotIO.h
//  Implementation of the Interface iRobotIO
//  Created on:      17-Apr-2011 5:24:17 PM
//  Original author: nagisa.day
///////////////////////////////////////////////////////////


//#if !defined(EA_DBAB8A73_11ED_4c42_9DF2_D06E4B4F2123__INCLUDED_)
//#define EA_DBAB8A73_11ED_4c42_9DF2_D06E4B4F2123__INCLUDED_
#ifndef I_ROBOTIO_H//iROBOTIO_H
#define I_ROBOTIO_H//iROBOTIO_H

#include "Path.h"
#include "Robot.h"
//#define _WIN32_WINNT 0x0601

class iRobotIO
{

public:
	virtual ~iRobotIO() {

	}

	//Takes a Path object and iterates over the whole path taking out the robot commands as it goes
	virtual bool fillQueue(Path * Pathmsg) = 0;
	//Makes a deep copy of the robot object that is passed in and sets it to m_robot
	virtual void setRobot(Robot & rob) = 0;
	//Trys to open the port if it is closed
	virtual bool openPort() = 0;
	//Tries to close the port if it is open
	virtual bool closePort() = 0; 

	virtual void transmitStart() = 0;
	
	virtual void endMission() = 0;

	virtual void eStop() = 0;
	//Sends a command that is passed into the object
	virtual void sendCommand(RobotCommand cmd) = 0;
	
	virtual void sendPriorityCommand(RobotCommand cmd) = 0;
};
#endif
