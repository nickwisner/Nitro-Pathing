///////////////////////////////////////////////////////////
//  iRobotIO.h
//  Implementation of the Interface iRobotIO
//  Created on:      17-Apr-2011 5:24:17 PM
//  Original author: nagisa.day
///////////////////////////////////////////////////////////


#if !defined(EA_DBAB8A73_11ED_4c42_9DF2_D06E4B4F2123__INCLUDED_)
#define EA_DBAB8A73_11ED_4c42_9DF2_D06E4B4F2123__INCLUDED_

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
	iRobotIO() {

	}

	virtual ~iRobotIO() {

	}

	virtual bool fillQueue(Path * pathMsg) =0;
	virtual bool sendCommand(RobotCommand cmd) =0;
	virtual int processRobotMessage(string msg) =0;
	virtual void receiveMessage() =0;
	virtual void setRobot(Robot & rob) =0;
	virtual void SendQueue()=0;
//might be for testing only. Probably remove before release
	virtual bool openPort() = 0;
	virtual bool closePort() = 0;

};
#endif // !defined(EA_DBAB8A73_11ED_4c42_9DF2_D06E4B4F2123__INCLUDED_)
