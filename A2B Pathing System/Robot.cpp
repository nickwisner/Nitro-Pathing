///////////////////////////////////////////////////////////
//  Robot.cpp
//  Implementation of the Class Robot
//  Created on:      17-Apr-2011 5:14:48 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#include "Robot.h"


Robot::Robot(int brate, int distance_per_cycle, int len, int wid, Image &symbol)
	: m_baudrate(brate), m_distancepercycle(distance_per_cycle), m_length(len), m_width(wid), m_symbol(symbol)
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
		this->m_distancepercycle = cpy.m_distancepercycle;
		this->m_length = cpy.m_length;
		this->m_width = cpy.m_width;
		this->m_symbol = Image(cpy.m_symbol.mat());
	}
	return *this;
}

Robot::~Robot()
{}

int Robot::baudrate()
{
	return m_baudrate;
}


int Robot::distancePerCycle()
{
	return m_distancepercycle;
}


int Robot::length()
{
	return m_length;
}


Image * Robot::peekSymbol()
{
	return &m_symbol;
}


int Robot::width()
{
	return m_width;
}