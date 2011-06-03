///////////////////////////////////////////////////////////
//  Robot.cpp
//  Implementation of the Class Robot
//  Created on:      17-Apr-2011 5:14:48 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#include "Robot.h"


Robot::Robot(int brate, int distance_per_milisec, int len, int wid, Mat &symbol)
	: m_baudrate(brate), m_distancepermiliseconds(distance_per_milisec), m_length(len), m_width(wid), m_symbol(symbol)
{ }

Robot::Robot( const Robot & cpy)
{
	*this = cpy;
}

Robot & Robot::operator=( const Robot & cpy)
{
	if(this != &cpy)
	{
		this->m_baudrate = cpy.m_baudrate;
		this->m_distancepermiliseconds = cpy.m_distancepermiliseconds;
		this->m_length = cpy.m_length;
		this->m_width = cpy.m_width;
		this->m_symbol = cpy.m_symbol;
	}
	return *this;
}

Robot::~Robot()
{}
//Returns the baudrate
int Robot::getBaudrate()
{
	return m_baudrate;
}

//Return the distance the robot travels in 1 milisecond
int Robot::getDistancePerMiliseconds()
{
	return m_distancepermiliseconds;
}
//Returns the length of the robot in pixles
int Robot::getLength()
{
	return m_length;
}

//Returns the image of the robot to try and find inside of the camera image
Mat Robot::peekSymbol()
{
	return m_symbol;
}

//returns the width of the robot in pixles.
int Robot::getWidth()
{
	return m_width;
}