///////////////////////////////////////////////////////////
//  Robot.h
//  Implementation of the Class Robot
//  Created on:      17-Apr-2011 5:14:48 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#ifndef ROBOT_H
#define ROBOT_H

#include "Image.h"

class Robot
{

public:
	Robot(int brate, int distance_per_cycle, int len, int wid, Image &symbol);
	~Robot();
	Robot & operator=( const Robot & cpy);
	Robot( const Robot & cpy);

	int baudrate();
	int distancePerCycle();
	int length();
	Image * peekSymbol();
	int width();

private:
	int m_baudrate;
	int m_distancepercycle;
	int m_length;
	Image m_symbol;
	int m_width;

};
#endif