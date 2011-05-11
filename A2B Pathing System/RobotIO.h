///////////////////////////////////////////////////////////
//  RobotIO.h
//  Implementation of the Class RobotIO
//  Created on:      17-Apr-2011 5:23:27 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#ifndef ROBOTIO_H
#define ROBOTIO_H

#include "Robot.h"
#include "iRobotIO.h"

#include <list>
#include <boost/asio.hpp>
using std::list;

class RobotIO : public iRobotIO
{

public:
	RobotIO();
	virtual ~RobotIO();

	bool fillQueue(Path * Pathmsg);
	void receiveMessage();
	bool receiveCommand(RobotCommand com);
	bool sendCommand(RobotCommand cmd); // later make private
	void setRobot(Robot & rob);
	void SendQueue();
	bool openPort();
	bool closePort(); 

private:
	list<RobotCommand> m_msgQueue;
	Robot * m_robot;

	boost::asio::io_service m_io;
	boost::asio::serial_port m_port;

	int processRobotMessage(string msg);

};
#endif
