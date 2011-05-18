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
using std::list;

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

class RobotIO : public iRobotIO
{

	public:
		RobotIO();
		virtual ~RobotIO();


		//Takes a Path object and iterates over the whole path taking out the robot commands as it goes
		bool fillQueue(Path * Pathmsg);
		//Makes a deep copy of the robot object that is passed in and sets it to m_robot
		void setRobot(Robot & rob);
		//Trys to open the port if it is closed
		bool openPort();
		//Tries to close the port if it is open
		bool closePort(); 

		void transmitStart();
	
		void endMission();

		void eStop();
		//Sends a command that is passed into the object
		void sendCommand(RobotCommand cmd);
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

		void sendNextMessage();
		//Gets called when the robot has send us a message
		void receiveMessage();
		//void transmitEnd();
		
		void startMission();
	//	void sendPriorityCommand(RobotCommand cmd);
	//These data members and some of the functions that use
	//them should be put into a RobotComm class. Where RobotIO
	//Sets m_currCommand inside of RobotComm. But for now just
	//have them inside of RobotIO

		boost::mutex m_robotReplyLock;
		char m_robotReply;
	
		RobotCommand m_curCommand;
	
		boost::mutex m_curCommandLock;
		boost::mutex m_cmdQueueLock;

		boost::thread m_cmdSend;
		boost::thread m_cmdRecieve;

		boost::mutex m_recieveMsgLock;
		bool m_recieveMsg;

};
#endif
