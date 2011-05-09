///////////////////////////////////////////////////////////
//  RobotIO.h
//  Implementation of the Class RobotIO
//  Created on:      17-Apr-2011 5:23:27 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#if !defined(EA_1A44B8B9_1523_46b5_AE1A_A23DE6022DB9__INCLUDED_)
#define EA_1A44B8B9_1523_46b5_AE1A_A23DE6022DB9__INCLUDED_

#include "Robot.h"
#include "iRobotIO.h"

#include <list>
#include <boost/asio.hpp>
using std::list;

/**
 * fillQueue - take a path to fill the command queue. If queue isn't empty, empty
 * it first.
 */
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
#endif // !defined(EA_1A44B8B9_1523_46b5_AE1A_A23DE6022DB9__INCLUDED_)
