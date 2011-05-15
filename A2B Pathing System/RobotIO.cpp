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
RobotIO::RobotIO() : m_robot(0), m_port(m_io, "COM4")	// open the bluetooth connection
{}

RobotIO::~RobotIO()
{
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

//Should get a string from receiveMessage then process it. Returning a int telling the system what it should do based of the integer.
int RobotIO::processRobotMessage(string msg){
	// not implemented
	return false;
}

//Should be called to get the whole message the robot is sending
void RobotIO::receiveMessage(){
	// not implemented
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
	buff[0] = '*'; //The starting handshake is a *
	buff.push_back(cmd.getCode()); //Next the robot expects a 'f','b','l','r' command
	itoa(cmd.getCycles(),cyclesBuff,10); //This converts the intager for how many miliseconds the robot should move into a stirng
	buff += cyclesBuff; //the string is then appended onto the buffer to be send to the robot
	buff[buff.length()] = '*'; //Because itoa give us a null terminated string we need to write over that null with a * so the robot knows when the command is over 

	// send it
	boost::asio::async_write(m_port, boost::asio::buffer(buff), boost::bind(handle_write, boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));

	// pop the sent command off
	buff.pop_back();

	delete []cyclesBuff;

	return true;
}

//Makes a deep copy of what is passed in and sets that to the m_robot datamember
void RobotIO::setRobot(Robot & rob)
{
	m_robot = new Robot(rob);
}

// only here for alpha release
// sends the entire command queue to robot
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

//attemps to open the com port. Should have error handing in here.
bool RobotIO::openPort()
{
	if( !m_port.is_open() )
	{
		// this hard code of COM4 is once again there... will be fixed to a global const soon and for release will most likely be in a config file
		m_port.open("COM4");	// opens the bluetooth connection to the robot
	
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