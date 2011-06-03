///////////////////////////////////////////////////////////
//  RobotIO.cpp
//  Implementation of the Class RobotIO
//  Created on:      17-Apr-2011 5:23:27 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#include "RobotIO.h"
#include "iControl.h"
#include <opencv2/highgui/highgui.hpp>
using cv::waitKey;

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

// used for the bluetooth connection
using boost::asio::io_service;
using boost::asio::serial_port_base;
char BLUETOOTH_COM_PORT[] = "COM4";

typedef boost::asio::serial_port_base asio_serial;

const int NO_CONNECTION = -1;
 /*Commands:
 f b l r s*/

RobotIO::RobotIO() : m_robot(0),m_io(3), m_port(m_io, BLUETOOTH_COM_PORT), m_robotRtn(false), m_controller(0), m_canSend(true)	// open the bluetooth connection
{}

// setter for the control class
void RobotIO::setControl(iControl * cnt)
{
	m_controller = cnt;
}

// destructor for robotIO
RobotIO::~RobotIO()
{
	m_port.close();	// close the bluetooth connection
	delete m_robot;
	m_robot = 0;
}

// makes sure we can send to robot at this time
void RobotIO::setCanSend(bool lean)
{
	// set canSend bool
	m_caseSendLock.lock();
	m_canSend = lean;
	
	// clear the queue
	m_msgQueueLock.lock();
	m_msgQueue.clear();
	m_msgQueueLock.unlock();

	m_caseSendLock.unlock();
}

// checks if we can send to the robot
bool RobotIO::getCanSend()
{
	bool ean;

	m_caseSendLock.lock();
	ean = m_canSend;
	m_caseSendLock.unlock();
	
	return ean;
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
char RobotIO::receiveMessage()
{
	int rtn = 0;
	char buff;

	while(rtn == 0)
	{
		rtn = boost::asio::read(m_port, boost::asio::buffer(&buff,1));
	}

	return buff;
}

//	commProtocol() 
//
//	
//
//	In: None
//
//	Out: None
void RobotIO::commProtocol()
{
	bool a = true;

	m_msgQueueLock.lock();
	bool moreMessage = !m_msgQueue.empty();
	m_msgQueueLock.unlock();

	RobotCommand curCommand(0,0);
	char robotRtn = 0;
	bool sendAgain = true;

	// run forever
	while(a)
	{
		if(sendAgain)
		{
			if(moreMessage)
			{
				m_msgQueueLock.lock();
				curCommand = m_msgQueue.front();
				m_msgQueue.pop_front();
				m_msgQueueLock.unlock();

				// start mission code
				if(curCommand.getCode() == 'a')
				{
					sendPriorityCommand(curCommand);
					// end mission code
				}else if(curCommand.getCode() == 'z')
				{				
					sendPriorityCommand(curCommand);
				}else	// regular msg 
				{
					if(!sendCommand(curCommand))
					{
						a = false;
					}
				}
			}
		}

		robotRtn = receiveMessage();
		waitKey(1000);
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

		m_msgQueueLock.lock();
		if(m_msgQueue.empty())
		{
			//not a but somethign for the loop
			moreMessage = false;
		}
		m_msgQueueLock.unlock();

		m_msgCountLock.lock();
		if(m_msgCount == 0)
		{
			a = false;
		}
		m_msgCountLock.unlock();
	}

	m_controller->endMission(1);
}

//Takes a robot command object and then sends the char and integer to the robot.
bool RobotIO::sendCommand(RobotCommand cmd)
{
	bool rtn = false;

	//Checks if the connection is still open. If not will throw a exception.
	if( !m_port.is_open() )
	{
		throw NO_CONNECTION;
	}

	// if we have the robot io ready to send the the robot
	if(m_canSend)
	{
		rtn = true;

		//set the port options
		m_port.set_option( asio_serial::baud_rate( 9600 ) ); 
		m_port.set_option( asio_serial::flow_control( asio_serial::flow_control::none ) ); 
		m_port.set_option( asio_serial::parity( asio_serial::parity::none ) ); 
		m_port.set_option( asio_serial::stop_bits( asio_serial::stop_bits::one ) ); 
		m_port.set_option( asio_serial::character_size( 8 ) ); 
	
		std::string buff;	
		char * milisecsBuff = 0;	// the message we are going to send
		int milisecLeng = 0;	// keeps track of the length of the milisec

		// find how many mill
		for(int i = cmd.getMilisecs(); i > 0;milisecLeng++)
		{
			i = i/10;
		}

		milisecsBuff = new char[milisecLeng+1];

		// load the robot command
		buff.push_back('*'); //The starting handshake is a *
		buff.push_back(cmd.getCode()); //Next the robot expects a 'f','b','l','r' command
		itoa(cmd.getMilisecs(),milisecsBuff,10); //This converts the intager for how many miliseconds the robot should move into a stirng
		buff += milisecsBuff; //the string is then appended onto the buffer to be send to the robot
		buff.push_back('*'); //Because itoa give us a null terminated string we need to write over that null with a * so the robot knows when the command is over 

		// send it
		m_port.write_some(boost::asio::buffer(buff));
		// pop the sent command off

		delete []milisecsBuff;

		//when robot is not sending a message to us
		m_RtnLock.lock();
		m_robotRtn = false;
		m_RtnLock.unlock();

		// increment the message count
		m_msgCountLock.lock();
		++m_msgCount;
		m_msgCountLock.unlock();
	}

	return rtn;
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
		}
		catch(int e)
		{
			throw NO_CONNECTION;
		}
	}
}

//	startCommunication
//
//	begins the robot communication thread
//
//	in:	None
//
//	out: None
//
void RobotIO::startCommunication()
{

	// primes the communication
	m_msgQueueLock.lock();
	// queues start a mission code
	m_msgQueue.push_back(RobotCommand('a', 0));
	// queues end mission code
	m_msgQueue.push_front(RobotCommand('z', 0));
	m_msgQueueLock.unlock();

	// start the thread
	m_robotOut = boost::thread(boost::bind(&RobotIO::commProtocol, this));
}

//attemps to open the com port. 
bool RobotIO::openPort()
{
	if( !m_port.is_open() )
	{
		// opens the bluetooth connection to the robot
		m_port.open(BLUETOOTH_COM_PORT);
	
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

	m_RtnLock.lock();
	m_robotRtn = false;
	m_RtnLock.unlock();

	m_msgCountLock.lock();
	++m_msgCount;
	m_msgCountLock.unlock();
}