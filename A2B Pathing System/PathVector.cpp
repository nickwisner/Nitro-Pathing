///////////////////////////////////////////////////////////
//  PathVector.cpp
//  Implementation of the Class PathVector
//  Created on:      17-Apr-2011 5:14:35 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#include "PathVector.h"

const float INCH_TO_SPACE = .53; //in 1 foot there is 100 pixels.
const int INCH_TO_SEC = 6;//inches //in 1 second we move .5 of a foot
//This #define might be wrong!
const float SPACE_TO_MILISECONDS = (INCH_TO_SEC/(INCH_TO_SPACE*1000)); //INCH_TO_SPACE * INCH_TO_SEC * 1000; //* .0001 or /.0001 ???
const int NINTY_DEGREES = 956;

//for debugging
const int DEBUG_MOVE = 2;
const int DEBUG_TURN = 1;

PathVector::PathVector(){

}



PathVector::~PathVector()
{

}

PathVector::PathVector( Edge e, int & heading)
{
	Point start = e.getStart();
	Point end = e.getEnd();
	m_edge.setStart(start);
	m_edge.setEnd(end);
	
	
	//The question is hwo do we make sure that shit is facing the way we want it too.
		
	/*
		I thnk my logic in this is wrong. We need a robot heading i think?
		//So all of this code is assuming that the robot is facing the top of the screen when it turs on
	*/

	//assuming the robot is facing the top of the screen and that :
	// 1 = robot facing top
	// 2 = robot facing right
	// 3 = robot facing bottom
	// 4 = robot facing left
	switch( heading)
	{
		case 1:
			heading = translateUp(start, end, heading);
			break;
		case 2:
			heading = translateRight(start, end, heading);
			break;
		case 3:
			heading = translateBottom(start, end, heading);
			break;
		case 4:
			heading = translateLeft(start, end, heading);
			break;

	}
}

PathVector::PathVector( const PathVector & cpy)
{
	
	*this = cpy;
}

PathVector & PathVector::operator=(const PathVector & cpy)
{

	if( this != &cpy)
	{
		this->m_angle = cpy.m_angle;
		this->m_commands = cpy.m_commands;
		this->m_edge = cpy.m_edge;
	}

	return *this;
}

int PathVector::translateUp(Point start, Point end, int heading)
{	
	//how we currently have it the
	if(start.x > end.x)
	{
		//move left
			//turn left
			//move forward
		m_commands.push_back(*(new RobotCommand('l',DEBUG_TURN)));//NINTY_DEGREES))); //90 is wrong but whatever the time to turn 90 degrees is correct
		//so PIX_TO_MILISECONDS is some #define that is the number of miliseconds to to move 1 pixle
		
		
		//number of pixles * pixles_to_inches * miliseconds_to_pixles
		m_commands.push_back( *(new RobotCommand('f',DEBUG_MOVE)));//((start.x - end.x)*SPACE_TO_MILISECONDS)))); 
		heading = 4;
	}else if(start.x < end.x)
	{
		//move right
			//turn right
			//move forward
		m_commands.push_back(/**( new */ RobotCommand('r',DEBUG_TURN));//);//NINTY_DEGREES)));
		m_commands.push_back(/**( new */ RobotCommand('f',DEBUG_MOVE));//););//((end.x - start.x)*SPACE_TO_MILISECONDS))));
		heading = 2;
	}else if(start.y > end.y)
	{
		//move forward
		m_commands.push_back( /**( new */ RobotCommand('f',DEBUG_MOVE));//););//((start.y - end.y)*SPACE_TO_MILISECONDS))));
		
	}else if(start.y < end.y)
	{
		//move backward
		m_commands.push_back(/**( new */ RobotCommand('b',DEBUG_MOVE));//););//((end.y - start.y)*SPACE_TO_MILISECONDS))));
		
	}else
	{ /*Might be empty*/}
	
	
	return heading;
}
int PathVector::translateRight(Point start, Point end, int heading)
{
	if(start.x > end.x)
	{
		//backward
		m_commands.push_back(/**( new */ RobotCommand('b',DEBUG_MOVE));//););//((end.x - start.x)*SPACE_TO_MILISECONDS))));		
	}else if(start.x < end.x)
	{
		//forward
		m_commands.push_back(/**( new */ RobotCommand('f',DEBUG_MOVE));//););//((start.x - end.x)*SPACE_TO_MILISECONDS)))); 

	}else if(start.y > end.y)
	{
		//move left
			//turn left
			//move forward
		m_commands.push_back(/**( new */ RobotCommand('l',DEBUG_TURN));//););//NINTY_DEGREES))); //90 is wrong but whatever the time to turn 90 degrees is correct
		//so PIX_TO_MILISECONDS is some #define that is the number of miliseconds to to move 1 pixle
		m_commands.push_back(/**( new */ RobotCommand('f',DEBUG_MOVE));//););//((start.y - end.y)*SPACE_TO_MILISECONDS)))); 
		heading = 1;
	}else if(start.y < end.y)
	{
		//move right
			//turn right
			//move forward
		m_commands.push_back(/**( new */ RobotCommand('r',DEBUG_TURN));//););//NINTY_DEGREES)));
		m_commands.push_back(/**( new */ RobotCommand('f',DEBUG_MOVE));//););//((end.y - start.y)*SPACE_TO_MILISECONDS))));
		heading = 3;
	}else
	{ /*Might be empty*/}
	
	return heading;
}
int PathVector::translateBottom(Point start, Point end, int heading)
{
	if(start.x > end.x)
	{
			//move right
			//turn right
			//move forward
		m_commands.push_back(/**( new */ RobotCommand('r',DEBUG_TURN));//););//NINTY_DEGREES)));
		m_commands.push_back(/**( new */ RobotCommand('f',DEBUG_MOVE));//););//((start.x - end.x)*SPACE_TO_MILISECONDS))));
		heading = 2;
		
	}else if(start.x < end.x)
	{
		//move left
			//turn left
			//move forward
		m_commands.push_back(/**( new */ RobotCommand('l',DEBUG_TURN));//););//NINTY_DEGREES))); //90 is wrong but whatever the time to turn 90 degrees is correct
		//so PIX_TO_MILISECONDS is some #define that is the number of miliseconds to to move 1 pixle
		m_commands.push_back(/**( new */ RobotCommand('f',DEBUG_MOVE));//););//((end.x - start.x)*SPACE_TO_MILISECONDS)))); 
		heading = 4;
	}else if(start.y > end.y)
	{
			//move backward
		m_commands.push_back(/**( new */ RobotCommand('b',DEBUG_MOVE));//););//((start.y - end.y)*SPACE_TO_MILISECONDS))));

		
	}else if(start.y < end.y)
	{
		//move forward
		m_commands.push_back(/**( new */ RobotCommand('f',DEBUG_MOVE));//););//((end.y - start.y)*SPACE_TO_MILISECONDS))));
		
	}else
	{ /*Might be empty*/}
	
	return heading;
}
int PathVector::translateLeft(Point start, Point end, int heading)
{
	if(start.x > end.x)
	{
			//move backward
		m_commands.push_back(/**( new */ RobotCommand('b', DEBUG_MOVE));//););//((start.x - end.x)*SPACE_TO_MILISECONDS))));
			//.push_back(RobotCommand('b',100);

		
	}else if(start.x < end.x)
	{
		//move forward
		m_commands.push_back(/**( new */ RobotCommand('f',DEBUG_MOVE));//););//((end.x - start.x)*SPACE_TO_MILISECONDS))));
	}else if(start.y > end.y)
	{
			//move right
			//turn right
			//move forward
		m_commands.push_back(/**( new */ RobotCommand('r',DEBUG_TURN));//););//NINTY_DEGREES)));
		m_commands.push_back(/**( new */ RobotCommand('f',DEBUG_MOVE));//););//((start.y - end.y)*SPACE_TO_MILISECONDS))));
		heading = 1;
		
	}else if(start.y < end.y)
	{
			//move left
			//turn left
			//move forward
		m_commands.push_back(/**( new */ RobotCommand('l',DEBUG_TURN));//););//NINTY_DEGREES))); //90 is wrong but whatever the time to turn 90 degrees is correct
		//so PIX_TO_MILISECONDS is some #define that is the number of miliseconds to to move 1 pixle
		m_commands.push_back(/**( new */ RobotCommand('f',DEBUG_MOVE));//););//((end.y - start.y)*SPACE_TO_MILISECONDS)))); 
		heading = 2;
		
	}else
	{ /*Might be empty*/}
	
	return heading;
}




float PathVector::getAngle(){

	return 0;
}


Edge PathVector::getEdge()
{
	return m_edge;
}
int PathVector::getCommandSize()
{
	return m_commands.size();
}


RobotCommand PathVector::popCommand()
{
	

	RobotCommand r(m_commands.front());
	
	m_commands.pop_front();
	
	//m_commands.erase(0);
	return r;
}