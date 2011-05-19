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


	//Takes a Path object and iterates over the whole path taking out the robot commands as it goes
	bool fillQueue(Path * Pathmsg);
	//Gets called when the robot has send us a message
	void receiveMessage();
	//Sends a command that is passed into the object
	bool sendCommand(RobotCommand cmd); // later make private //maybe in beta
	//Makes a deep copy of the robot object that is passed in and sets it to m_robot
	void setRobot(Robot & rob);
	//Sends the whole queue of commands to the robot. 
		//In beta will be implemented that we will not send a message until the robot has send us a command back.	
	void SendQueue();
	//Trys to open the port if it is closed
	bool openPort();
	//Tries to close the port if it is open
	bool closePort(); 
	void sendPriorityCommand(RobotCommand cmd);
private:
	//Hold all of the commands to complete the path
	list<RobotCommand> m_msgQueue;
	//A pointer to the robot so aquire its baudrate and other usefull information
	Robot * m_robot;

	//A boost object required to open communication with the robot
	boost::asio::io_service m_io;
	//A boost object required to do serial port communication
	boost::asio::serial_port m_port;

	//takes a string that is the message the robot send us and then returns a int code telling the sytem what to do next
	int processRobotMessage(string msg);

};
#endif
