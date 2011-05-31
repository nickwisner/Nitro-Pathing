///////////////////////////////////////////////////////////
//  DummyRobIO.cpp
//  Implementation of the Class DummyRobIO
//  Created on:      17-Apr-2011 5:23:27 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#include "DummyRobIO.h"

DummyRobIO::DummyRobIO() : m_robot(0)
{}

DummyRobIO::~DummyRobIO()
{
}


bool DummyRobIO::fillQueue(Path * Pathmsg)
{
	return true;
}


int DummyRobIO::processRobotMessage(string msg){

	return false;
}


char DummyRobIO::receiveMessage(){
	// not implemented
	return 0;
}


bool DummyRobIO::sendCommand(RobotCommand cmd)
{
	return true;
}


bool DummyRobIO::receiveCommand(RobotCommand com)
{
	return false;
}

void DummyRobIO::setRobot(Robot & rob)
{
	m_robot = new Robot(rob);
}

void DummyRobIO::SendQueue()
{
}

bool DummyRobIO::openPort()
{
	return false;
}
bool DummyRobIO::closePort()
{
	return false;
}