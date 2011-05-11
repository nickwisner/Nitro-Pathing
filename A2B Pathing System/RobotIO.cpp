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


int RobotIO::processRobotMessage(string msg){
	// not implemented
	return false;
}


void RobotIO::receiveMessage(){
	// not implemented
}


bool RobotIO::sendCommand(RobotCommand cmd)
{
	if( !m_port.is_open() )
	{
		throw NO_CONNECTION;
	}

	m_port.set_option( asio_serial::baud_rate( 9600 ) ); 
	m_port.set_option( asio_serial::flow_control( asio_serial::flow_control::none ) ); 
	m_port.set_option( asio_serial::parity( asio_serial::parity::none ) ); 
	m_port.set_option( asio_serial::stop_bits( asio_serial::stop_bits::one ) ); 
	m_port.set_option( asio_serial::character_size( 8 ) ); 
	
	std::string buff;	
	for( int i = 0; i < cmd.getCycles(); i++ )
	{
		// load the robot command
		buff.push_back(cmd.getCode());

		// send it
		boost::asio::async_write(m_port, boost::asio::buffer(buff), boost::bind(handle_write, boost::asio::placeholders::error,
			  boost::asio::placeholders::bytes_transferred));

		// pop the sent command off
		buff.pop_back();
	}
	
	return true;
}


bool RobotIO::receiveCommand(RobotCommand com)
{
	return false;
}

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

bool RobotIO::closePort()
{
	if( m_port.is_open() )
	{
		m_port.close();

		return true;
	}

	return false;
}