///////////////////////////////////////////////////////////
//  PathVector.cpp
//  Implementation of the Class PathVector
//  Created on:      17-Apr-2011 5:14:35 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#include "PathVector.h"
#include "A2BUtilities.h"
//We get 8.3 by assuming that there are 100 pixles in 1 foot. So by dividing 100/12 we get how many pixles in 1 inch
//const float SPACE_PER_INCH = 8.3*PIXELS_PER_SQUARE; //in 1 foot there is 100 pixels.

//this means that there are 14 px per inch, we then multiply that by 16 to find the squares per inch
const float SPACE_PER_INCH = 14.0/PIXELS_PER_SQUARE;
//in 1 second we move .5 of a foot
const int INCH_PER_SEC = 6;//inches 

const float SPACE_TO_MILLISECONDS = ((INCH_PER_SEC*SPACE_PER_INCH)/1000);
const int NINETY_DEGREES = 900;//956;

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

int PathVector::findTravelTime(float pixles_to_travel)
{
	float spaces_to_travel = pixles_to_travel/PIXELS_PER_SQUARE;
	float time_to_travel = spaces_to_travel/SPACE_TO_MILLISECONDS;

	return time_to_travel;
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
		m_commands.push_back(( RobotCommand('l',NINETY_DEGREES))); 

		//m_commands.push_back( RobotCommand('f',DEBUG_MOVE));
		m_commands.push_back( ( RobotCommand('f',findTravelTime(start.x - end.x)))); 

		heading = 4;
	}else if(start.x < end.x)
	{
		//move right
			//turn right
			//move forward
		//m_commands.push_back(RobotCommand('r',DEBUG_TURN));
		m_commands.push_back(RobotCommand('r',NINETY_DEGREES));
		
		//m_commands.push_back( RobotCommand('f',DEBUG_MOVE));
		m_commands.push_back( RobotCommand('f',findTravelTime(end.x - start.x))); 


		heading = 2;
	}else if(start.y > end.y)
	{
		//move forward		

		//m_commands.push_back( RobotCommand('f',DEBUG_MOVE));
		m_commands.push_back( RobotCommand('f',findTravelTime(start.y - end.y)));
		
	}else if(start.y < end.y)
	{
		//move backward
		//m_commands.push_back( RobotCommand('b',DEBUG_MOVE));
		m_commands.push_back( RobotCommand('b',findTravelTime(end.y - start.y)));
		
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
		m_commands.push_back( RobotCommand('b',findTravelTime(start.x - end.x)));
			
	}else if(start.x < end.x)
	{

		//forward
		//m_commands.push_back(RobotCommand('f',DEBUG_MOVE));
		m_commands.push_back(RobotCommand('f',findTravelTime(end.x - start.x))); 
		
	}else if(start.y > end.y)
	{
		//move left
			//turn left
			//move forward
		//m_commands.push_back( RobotCommand('l',DEBUG_TURN));
		m_commands.push_back( RobotCommand('l',NINETY_DEGREES)); //90 is wrong but whatever the time to turn 90 degrees is correct

		//forward
		//m_commands.push_back(RobotCommand('f',DEBUG_MOVE));
		m_commands.push_back(RobotCommand('f',findTravelTime(start.y - end.y)));
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
		m_commands.push_back( RobotCommand('f',findTravelTime(end.y - start.y)));

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
		m_commands.push_back( RobotCommand('f',findTravelTime(start.x - end.x)));

		
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
		m_commands.push_back( RobotCommand('f',findTravelTime(end.x - start.x)));

		heading = 4;
	}else if(start.y > end.y)
	{
		//move backward
		//m_commands.push_back( RobotCommand('b',DEBUG_MOVE));
		m_commands.push_back( RobotCommand('b',findTravelTime(start.y - end.y)));

	}else if(start.y < end.y)
	{

		//move forward
		//m_commands.push_back(RobotCommand('f',DEBUG_MOVE));//););
		m_commands.push_back(RobotCommand('l',findTravelTime(end.y - start.y)));

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
	int heading = 4;
	
	if(start.x < end.x)
	{

		//move backward
		//m_commands.push_back( RobotCommand('b', DEBUG_MOVE));
		m_commands.push_back( RobotCommand('b',findTravelTime(start.x - end.x)));

	}else if(start.x > end.x)
	{
		//move forward
		//m_commands.push_back(RobotCommand('f',DEBUG_MOVE));
		m_commands.push_back(RobotCommand('f',findTravelTime(end.x - start.x)));

	}else if(start.y > end.y)
	{
		//move right
			//turn right
			//move forward
		//m_commands.push_back(RobotCommand('r',DEBUG_TURN));
		m_commands.push_back(RobotCommand('r',NINETY_DEGREES));
		

		//move forward
		//m_commands.push_back( RobotCommand('f',DEBUG_MOVE));
		m_commands.push_back( RobotCommand('f',findTravelTime(start.y - end.y)));
		
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
		m_commands.push_back(RobotCommand('f',findTravelTime(end.y - start.y)));		
		
		heading = 3;
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