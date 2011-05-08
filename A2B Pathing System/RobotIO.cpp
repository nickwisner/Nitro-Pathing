///////////////////////////////////////////////////////////
//  RobotIO.cpp
//  Implementation of the Class RobotIO
//  Created on:      17-Apr-2011 5:23:27 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#include "RobotIO.h"
#include <opencv2/highgui/highgui.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
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

RobotIO::RobotIO() : m_robot(0), port(io, "COM4")
{}

RobotIO::~RobotIO()
{
	port.close();
}


bool RobotIO::fillQueue(Path * Pathmsg)
{
	//itterates over the path vector and pulls the messages out, then pushs them onto themessage queue

	//Pathmsg->popVector
	int size = Pathmsg->getPathVSize();

	for(int i = 0; i < size; i++)
	{
		PathVector v = Pathmsg->getPathVector(i);

		int cmdSize = v.getCommandSize();
		for(int j = 0; j < cmdSize; j++)
		{
			//this pop might be a temp garbage.
			m_msgQueue.push_back(v.popCommand());
		}
	}
	if(m_msgQueue.empty())
	{
		return false;
	}
	return true;
}


int RobotIO::processRobotMessage(string msg){

	return false;
}


void RobotIO::receiveMessage(){
	// not implemented
}


bool RobotIO::sendCommand(RobotCommand cmd)
{
	if( !port.is_open() )
	{
		throw NO_CONNECTION;
	}
	port.set_option( asio_serial::baud_rate( 9600 ) ); 
	port.set_option( asio_serial::flow_control( asio_serial::flow_control::none ) ); 
	port.set_option( asio_serial::parity( asio_serial::parity::none ) ); 
	port.set_option( asio_serial::stop_bits( asio_serial::stop_bits::one ) ); 
	port.set_option( asio_serial::character_size( 8 ) ); 
	
	std::string buff;	
	for( int i = 0; i < cmd.getCycles(); i++ )
	{
		buff.push_back(cmd.getCode());

		// send it
		boost::asio::async_write(port, boost::asio::buffer(buff), boost::bind(handle_write, boost::asio::placeholders::error,
			  boost::asio::placeholders::bytes_transferred));

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
		sendCommand(m_msgQueue.front());
		m_msgQueue.pop_front();

		waitKey(100);
	}
}