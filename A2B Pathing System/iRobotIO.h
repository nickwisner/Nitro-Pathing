///////////////////////////////////////////////////////////
//  iRobotIO.h
//  Implementation of the Interface iRobotIO
//  Created on:      17-Apr-2011 5:24:17 PM
//  Original author: nagisa.day
///////////////////////////////////////////////////////////


//#if !defined(EA_DBAB8A73_11ED_4c42_9DF2_D06E4B4F2123__INCLUDED_)
//#define EA_DBAB8A73_11ED_4c42_9DF2_D06E4B4F2123__INCLUDED_
#ifndef iROBOTIO_H
#define iROBOTIO_H

#include "Path.h"
#include "PathVector.h"
#include "RobotCommand.h"
//
//#define _WIN32_WINNT 0x0601

#include <boost/asio.hpp>
#include <boost/bind.hpp>

class iRobotIO
{

public:
	virtual ~iRobotIO() {

	}

	//Takes a Path object and iterates over the whole path taking out the robot commands as it goes
	virtual bool fillQueue(Path * pathMsg) =0;
		////Sends a command that is passed into the object
		//virtual bool sendCommand(RobotCommand cmd) =0;
		////Takes the string and returns int acting as a code telling the system  what to do
		//virtual int processRobotMessage(string msg) =0;
	//Gets called when the robot has send us a message
	virtual void receiveMessage() =0;
	//Makes a deep copy of the robot object that is passed in and sets it to m_robot
	virtual void setRobot(Robot & rob) =0;
	//Sends the whole queue of commands to the robot. 
		//In beta will be implemented that we will not send a message until the robot has send us a command back.
		//virtual void SendQueue()=0;
		////Attempts to open the com port
	virtual bool openPort() = 0;
	//attempts to close the com port
	virtual bool closePort() = 0;

	void transmitStart();

	void startMission();
	
	void endMission();

};
#endif // !defined(EA_DBAB8A73_11ED_4c42_9DF2_D06E4B4F2123__INCLUDED_)
