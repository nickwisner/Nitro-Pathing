///////////////////////////////////////////////////////////
//  PathVector.cpp
//  Implementation of the Class PathVector
//  Created on:      17-Apr-2011 5:14:35 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#include "PathVector.h"

const double INCH_TO_SPACE = .53; //in 1 foot there is 100 pixels.
const int INCH_TO_SEC = 6;//inches //in 1 second we move .5 of a foot

//This might be wrong!
const float SPACE_TO_MILLISECONDS = (INCH_TO_SEC/(INCH_TO_SPACE*1000));
const int NINETY_DEGREES = 956;

//for debugging
const int DEBUG_MOVE = 2;
const int DEBUG_TURN = 2;

PathVector::PathVector()
{	}
PathVector::~PathVector()
{	
	m_commands.clear();
	m_edge.~Edge();
}

PathVector::PathVector( Edge e, int & heading) : m_edge(e)
{
	Point start = e.getStart(),
		end = e.getEnd();

	// 1 = robot facing top
	// 2 = robot facing right
	// 3 = robot facing bottom
	// 4 = robot facing left
	switch( heading)
	{
		case 1:
			heading = translateUp(start, end);
			break;
		case 2:
			heading = translateRight(start, end);
			break;
		case 3:
			heading = translateBottom(start, end);
			break;
		case 4:
			heading = translateLeft(start, end);
			break;
		default:
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
		this->m_commands = cpy.m_commands;
		this->m_edge = cpy.m_edge;
	}

	return *this;
}

/**************************** translateUp *****************************
* Purpose:
*	This method is called when the robot is in the position that if
*	it moved forward it would move to the top of the screen. It
*	translates the start and end point into a robot command. It does
*	this by finding the distance between the two pixels and then
*	converts it to the amount of milliseconds the motors must be on
*	for the robot to make it to the end point.
* 
* Entry:
*	Two points in terms of pixels. They represent where the robot
*	will start at this command and where it should end at the end of
*	the command.
* 
* Exit:
*	This function returns the way the robot will be facing after the
*	command is completed.
**********************************************************************/
int PathVector::translateUp(Point start, Point end)
{	
	int diff = 0;
	int heading = 1;
	//how we currently have it the
	if(start.x > end.x)
	{
		//move left
			//turn left
			//move forward

		//DEBUG_TURN is only to be used until we can have the robot take multiple parameters
		//m_commands.push_back(RobotCommand('l',DEBUG_TURN));
		m_commands.push_back(*(new RobotCommand('l',NINETY_DEGREES))); 

		//m_commands.push_back( RobotCommand('f',DEBUG_MOVE));
		m_commands.push_back( *(new RobotCommand('f',((start.x - end.x)*SPACE_TO_MILLISECONDS)))); 

		heading = 4;
	}else if(start.x < end.x)
	{
		//move right
			//turn right
			//move forward
		//m_commands.push_back(RobotCommand('r',DEBUG_TURN));
		m_commands.push_back(RobotCommand('r',NINETY_DEGREES));
		
		//m_commands.push_back( RobotCommand('f',DEBUG_MOVE));
		m_commands.push_back( RobotCommand('f',((end.x - start.x)*SPACE_TO_MILLISECONDS))); 


		heading = 2;
	}else if(start.y > end.y)
	{
		//move forward		

		//m_commands.push_back( RobotCommand('f',DEBUG_MOVE));
		m_commands.push_back( RobotCommand('f',((start.y - end.y)*SPACE_TO_MILLISECONDS)));
		
	}else if(start.y < end.y)
	{
		//move backward
		//m_commands.push_back( RobotCommand('b',DEBUG_MOVE));
		m_commands.push_back( RobotCommand('b',((end.y - start.y)*SPACE_TO_MILLISECONDS)));
		
	}else
	{ /*Might be empty*/}
	
	
	return heading;
}

/*************************** translateRight ***************************
* Purpose:
*	This method is called when the robot is in the position that if
*	it moved forward it would move to the right of the screen. It
*	translates the start and end point into a robot command. It does
*	this by finding the distance between the two pixels and then
*	converts it to the amount of milliseconds the motors must be on
*	for the robot to make it to the end point.
* 
* Entry:
*	Two points in terms of pixels. They represent where the robot
*	will start at this command and where it should end at the end of
*	the command.
* 
* Exit:
*	This function returns the way the robot will be facing after the
*	command is completed.
**********************************************************************/
int PathVector::translateRight(Point start, Point end)
{
	int diff = 0;
	int heading = 2;
	
	if(start.x > end.x)
	{

		//backward
		//m_commands.push_back( RobotCommand('b',DEBUG_MOVE));
		m_commands.push_back( RobotCommand('b',((end.x - start.x)*SPACE_TO_MILLISECONDS)));		
			
	}else if(start.x < end.x)
	{

		//forward
		//m_commands.push_back(RobotCommand('f',DEBUG_MOVE));
		m_commands.push_back(RobotCommand('f',((end.x - start.x)*SPACE_TO_MILLISECONDS))); 
		
	}else if(start.y > end.y)
	{
		//move left
			//turn left
			//move forward
		//m_commands.push_back( RobotCommand('l',DEBUG_TURN));
		m_commands.push_back( RobotCommand('l',NINETY_DEGREES)); //90 is wrong but whatever the time to turn 90 degrees is correct

		//forward
		//m_commands.push_back(RobotCommand('f',DEBUG_MOVE));
		m_commands.push_back(RobotCommand('f',((start.y - end.y)*SPACE_TO_MILLISECONDS))); 
		heading = 1;
	}else if(start.y < end.y)
	{
		//move right
			//turn right
			//move forward
		//m_commands.push_back( RobotCommand('r',DEBUG_TURN));
		m_commands.push_back( RobotCommand('r',NINETY_DEGREES));
		
		//forward
		//m_commands.push_back( RobotCommand('f',DEBUG_MOVE));
		m_commands.push_back( RobotCommand('f',((end.y - start.y)*SPACE_TO_MILLISECONDS)));

		heading = 3;
	}else
	{ /*Might be empty*/}
	
	return heading;
}
/************************** translateBottom ***************************
* Purpose:
*	This method is called when the robot is in the position that if
*	it moved forward it would move to the bottom of the screen. It
*	translates the start and end point into a robot command. It does
*	this by finding the distance between the two pixels and then
*	converts it to the amount of milliseconds the motors must be on
*	for the robot to make it to the end point.
* 
* Entry:
*	Two points in terms of pixels. They represent where the robot
*	will start at this command and where it should end at the end of
*	the command.
* 
* Exit:
*	This function returns the way the robot will be facing after the
*	command is completed.
**********************************************************************/
int PathVector::translateBottom(Point start, Point end)
{
	int diff = 0;
	int heading = 3;
	
	if(start.x > end.x)
	{
		//move right
			//turn right
			//move forward
		//m_commands.push_back(RobotCommand('r',DEBUG_TURN));
		m_commands.push_back(RobotCommand('r',NINETY_DEGREES));
	
		//forward
		//m_commands.push_back( RobotCommand('f',DEBUG_MOVE));
		m_commands.push_back( RobotCommand('f',((start.x - end.x)*SPACE_TO_MILLISECONDS)));

		
		heading = 2;
		
	}else if(start.x < end.x)
	{
		//move left
			//turn left
			//move forward
		//m_commands.push_back(RobotCommand('l',DEBUG_TURN));
		m_commands.push_back(RobotCommand('l',NINETY_DEGREES)); 

		//forward
		//m_commands.push_back( RobotCommand('f',DEBUG_MOVE));
		m_commands.push_back( RobotCommand('f',((end.x - start.x)*SPACE_TO_MILLISECONDS))); 
		
		heading = 4;
	}else if(start.y > end.y)
	{
		//move backward
		//m_commands.push_back( RobotCommand('b',DEBUG_MOVE));
		m_commands.push_back( RobotCommand('b',((start.y - end.y)*SPACE_TO_MILLISECONDS)));
	
	}else if(start.y < end.y)
	{

		//move forward
		//m_commands.push_back(RobotCommand('f',DEBUG_MOVE));//););
		m_commands.push_back(RobotCommand('f',((end.y - start.y)*SPACE_TO_MILLISECONDS)));

	}else
	{ /*Might be empty*/}
	
	return heading;
}
/*************************** translateLeft ****************************
* Purpose:
*	This method is called when the robot is in the position that if
*	it moved forward it would move to the leftof the screen. It
*	translates the start and end point into a robot command. It does
*	this by finding the distance between the two pixels and then
*	converts it to the amount of milliseconds the motors must be on
*	for the robot to make it to the end point.
* 
* Entry:
*	Two points in terms of pixels. They represent where the robot
*	will start at this command and where it should end at the end of
*	the command.
* 
* Exit:
*	This function returns the way the robot will be facing after the
*	command is completed.
**********************************************************************/
int PathVector::translateLeft(Point start, Point end)
{
	int diff = 0;
	int heading = 4;
	
	if(start.x > end.x)
	{
		diff = start.x - end.x;

		//move backward
		//m_commands.push_back( RobotCommand('b', DEBUG_MOVE));
		m_commands.push_back( RobotCommand('b',((start.x - end.x)*SPACE_TO_MILLISECONDS)));

	}else if(start.x < end.x)
	{

		diff = end.x - start.x;

		//move forward
		//m_commands.push_back(RobotCommand('f',DEBUG_MOVE));
		m_commands.push_back(RobotCommand('f',((end.x - start.x)*SPACE_TO_MILLISECONDS)));


	}else if(start.y > end.y)
	{
		//move right
			//turn right
			//move forward
		//m_commands.push_back(RobotCommand('r',DEBUG_TURN));
		m_commands.push_back(RobotCommand('r',NINETY_DEGREES));
		

		//move forward
		//m_commands.push_back( RobotCommand('f',DEBUG_MOVE));
		m_commands.push_back( RobotCommand('f',((start.y - end.y)*SPACE_TO_MILLISECONDS)));

		
		heading = 1;
		
	}else if(start.y < end.y)
	{
		//move left
			//turn left
			//move forward
		//m_commands.push_back(RobotCommand('l',DEBUG_TURN));
		m_commands.push_back(RobotCommand('l',NINETY_DEGREES));

		//move forward
		//m_commands.push_back(RobotCommand('f',DEBUG_MOVE));
		m_commands.push_back(RobotCommand('f',((end.y - start.y)*SPACE_TO_MILLISECONDS))); 
		
		heading = 2;
	}else
	{ /*Might be empty*/}
	
	return heading;
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

	return r;
}