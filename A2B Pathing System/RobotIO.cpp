///////////////////////////////////////////////////////////
//  RobotIO.cpp
//  Implementation of the Class RobotIO
//  Created on:      17-Apr-2011 5:23:27 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#include "RobotIO.h"
#include <opencv2/highgui/highgui.hpp>
using cv::waitKey;

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

// used for the bluetooth connection
using boost::asio::io_service;
using boost::asio::serial_port_base;

typedef boost::asio::serial_port_base asio_serial;

const int NO_CONNECTION = -1;
 /*Commands:
 f b l r*/

void handle_write(const boost::system::error_code&, // error
	size_t ) // bytes transferred
{
}

// COM4 is hardcoded at this point only because we are only testing from one computer that uses it.
// It will be changed later on
RobotIO::RobotIO() : m_robot(0),m_io(2), m_port(m_io, "COM4"), m_robotRtn(false)	// open the bluetooth connection
{
	sendPriorityCommand(RobotCommand('z', 0));
}

RobotIO::~RobotIO()
{
	sendPriorityCommand(RobotCommand('a',0));
	m_port.close();	// close the bluetooth connection
	delete m_robot;
	m_robot = 0;
}

//iterates over the path vector and pulls the messages out, then pushs them onto the message queue
bool RobotIO::fillQueue(Path * Pathmsg)
{
	bool filledQueue(true);	// the success of the method: were the commands able to be loaded?

	// the number of vectors in the path
	int size = Pathmsg->getPathVSize();

	// for each pathing vector
	for(int i = 0; i < size; i++)
	{

		PathVector v = Pathmsg->getPathVector(i);

		// how many commands implement this vector 
		// i.e. 3 spaces 90 degs left of the current direction would need 2 commands (left turn and move forward)
		int cmdSize = v.getCommandSize();

		// for each command in this vector
		for(int j = 0; j < cmdSize; j++)
		{
			m_msgQueue.push_back(v.popCommand());
		}
	}

	// no messages were put in queue? something must have happened...
	if(m_msgQueue.empty())
	{
		return false;
	}

	return filledQueue;
}

//Should be called to get the whole message the robot is sending
void RobotIO::receiveMessage()
{
	bool a  = true;
	m_receiveCnt = true;

	m_receiveLoopLock.lock();
	while(m_receiveCnt)
	{
		m_receiveLoopLock.unlock();
		while(m_robotRtn)
		{boost::this_thread::yield();}


		// Not sure if I should set all of options
		std::string buff;
		m_port.read_some(boost::asio::buffer(buff,1));
	
		m_rtnValueLock.lock();
		m_rtnValue = buff.front();
		m_rtnValueLock.unlock();
	
		m_RtnLock.lock();
		m_robotRtn = true;
		m_RtnLock.unlock();

		m_receiveLoopLock.lock();
	}
}
bool RobotIO::commProtocol()
{
	bool a = true;
	RobotCommand curCommand(0,0);
	char robotRtn = 0;
	bool sendAgain = true;
	while(a)
	{
		if(sendAgain)
		{
			m_msgQueueLock.lock();
			curCommand = m_msgQueue.front();
			m_msgQueue.pop_front();
			m_msgQueueLock.unlock();

			sendCommand(curCommand);

			//should no need to lock this cuz of the yield, but might be wrong. Check wiht jon later
			while(!m_robotRtn)
			{boost::this_thread::yield();}
		}
			m_rtnValueLock.lock();
			robotRtn = m_rtnValue;
			m_rtnValueLock.unlock();

		switch(robotRtn)
		{
			//lowercase means finished
			case 'a':
				//room for more messages
				sendAgain = true;
				m_msgCountLock.lock();
				--m_msgCount;
				m_msgCountLock.unlock();
				break;
			case 'c':
				//no room for more messages
				sendAgain = false;

				m_RtnLock.lock();
				m_robotRtn = true;
				m_RtnLock.unlock();

				m_msgCountLock.lock();
				--m_msgCount;
				m_msgCountLock.unlock();
				break;
			//upercase mean processed but not completed
			case 'A':
				//room for more messages
				sendAgain = true;
				break;
			case 'C':
				//no room for more messages
				sendAgain = false;

				m_RtnLock.lock();
				m_robotRtn = true;
				m_RtnLock.unlock();
				break;
			//means a error occured.
			case 'F':
				a = false;
				break;
		}

	}
	m_receiveLoopLock.lock();
	m_receiveCnt = false;
	m_receiveLoopLock.unlock();
	//going to clean up the thread mess here!
	m_robotIn.join();

}
//Takes a robot command object and then sends the char and integer to the robot.
	//With how it is currently implemented it just sends the char to the robot for the number of cycles we have.
	//This will hopefully be changed in beta
bool RobotIO::sendCommand(RobotCommand cmd)
{
	//Checks if the connection is still open. If not will throw a exception.
	if( !m_port.is_open() )
	{
		throw NO_CONNECTION;
	}

	//Everytime we send a message we reset the options, just in case.
	m_port.set_option( asio_serial::baud_rate( 9600 ) ); 
	m_port.set_option( asio_serial::flow_control( asio_serial::flow_control::none ) ); 
	m_port.set_option( asio_serial::parity( asio_serial::parity::none ) ); 
	m_port.set_option( asio_serial::stop_bits( asio_serial::stop_bits::one ) ); 
	m_port.set_option( asio_serial::character_size( 8 ) ); 
	
	std::string buff;	
	char * cyclesBuff = 0;
	int cycleLeng = 0;
	for(int i = cmd.getCycles(); i > 0;cycleLeng++)
	{
		i = i/10;
	}
	cyclesBuff = new char[cycleLeng+1];

	// load the robot command
	buff.push_back('*'); //The starting handshake is a *
	buff.push_back(cmd.getCode()); //Next the robot expects a 'f','b','l','r' command
	itoa(cmd.getCycles(),cyclesBuff,10); //This converts the intager for how many miliseconds the robot should move into a stirng
	buff += cyclesBuff; //the string is then appended onto the buffer to be send to the robot
	buff.push_back('*'); //Because itoa give us a null terminated string we need to write over that null with a * so the robot knows when the command is over 

	// send it
//	boost::asio::async_write(m_port, boost::asio::buffer(buff), boost::bind(handle_write, boost::asio::placeholders::error,
	//		boost::asio::placeholders::bytes_transferred));
	m_port.write_some(boost::asio::buffer(buff));
	// pop the sent command off

	waitKey(100);

	//buff.pop_back();

	delete []cyclesBuff;

	m_RtnLock.lock();
	m_robotRtn = false;
	m_RtnLock.unlock();

	m_msgCountLock.lock();
	++m_msgCount;
	m_msgCountLock.unlock();

	return true;
}

//Makes a deep copy of what is passed in and sets that to the m_robot datamember
void RobotIO::setRobot(Robot & rob)
{
	m_robot = new Robot(rob);
}

//// only here for alpha release
//// sends the entire command queue to robot
void RobotIO::SendQueue()
{
	while(m_msgQueue.size())
	{
		try
		{
			sendCommand(m_msgQueue.front());
			m_msgQueue.pop_front();

			waitKey(100);

		}catch(int e)
		{
			throw NO_CONNECTION;
		}
	}
}


void RobotIO::startCommunication()
{
	m_robotOut = boost::thread(boost::bind(&RobotIO::commProtocol, this));
	m_robotIn = boost::thread(boost::bind(&RobotIO::receiveMessage, this));

}

//attemps to open the com port. Should have error handing in here.
bool RobotIO::openPort()
{
	if( !m_port.is_open() )
	{
		// this hard code of COM4 is once again there... will be fixed to a global const soon and for release will most likely be in a config file
		m_port.open("COM8");	// opens the bluetooth connection to the robot
	
		return true;
	}

	return false;
}

//attemps to close the com port. Should have error handing in here.
bool RobotIO::closePort()
{
	if( m_port.is_open() )
	{
		m_port.close();

		return true;
	}

	return false;
}

void RobotIO::sendPriorityCommand(RobotCommand cmd)
{
	//Everytime we send a message we reset the options, just in case.
	m_port.set_option( asio_serial::baud_rate( 9600 ) ); 
	m_port.set_option( asio_serial::flow_control( asio_serial::flow_control::none ) ); 
	m_port.set_option( asio_serial::parity( asio_serial::parity::none ) ); 
	m_port.set_option( asio_serial::stop_bits( asio_serial::stop_bits::one ) ); 
	m_port.set_option( asio_serial::character_size( 8 ) ); 

	std::string buff;	

	// load the robot command
	buff = cmd.getCode();

	// send it
	m_port.write_some(boost::asio::buffer(buff));
//	boost::asio::async_write(m_port, boost::asio::buffer(buff),  boost::bind(handle_write, boost::asio::placeholders::error,
//			boost::asio::placeholders::bytes_transferred));

	// pop the sent command off
	buff.pop_back();
}