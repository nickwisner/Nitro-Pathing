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
const int DEBUG_TURN = 2;

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
	int diff = 0;
	//how we currently have it the
	if(start.x > end.x)
	{
		//move left
			//turn left
			//move forward

		m_commands.push_back(*(new RobotCommand('l',DEBUG_TURN)));//NINTY_DEGREES))); //90 is wrong but whatever the time to turn 90 degrees is correct
		//so PIX_TO_MILISECONDS is some #define that is the number of miliseconds to to move 1 pixle
		
		diff = start.x - end.x;
		//this for-loop is completely for alpha testing. It is to check how many 'f'/'b' commands to push onto the vector because we cannot send miliseconds yet
		for(int i = 0; diff - 30 >= i && i <= diff + 30;)
		{
			m_commands.push_back( *(new RobotCommand('f',DEBUG_MOVE)));//((start.x - end.x)*SPACE_TO_MILISECONDS)))); 
			i += 100;
		}
		heading = 4;
	}else if(start.x < end.x)
	{
		//move right
			//turn right
			//move forward
		m_commands.push_back(/**( new */ RobotCommand('r',DEBUG_TURN));//);//NINTY_DEGREES)));
		
		diff = end.x - start.x;
		//this for-loop is completely for alpha testing. It is to check how many 'f'/'b' commands to push onto the vector because we cannot send miliseconds yet
		for(int i = 0; diff - 30 >= i && i <= diff + 30;)
		{
			m_commands.push_back( *(new RobotCommand('f',DEBUG_MOVE)));//((end.x - start.x)*SPACE_TO_MILISECONDS)))); 
			i += 100;
		}

		heading = 2;
	}else if(start.y > end.y)
	{
		diff = start.y - end.y;
		//move forward		
		//this for-loop is completely for alpha testing. It is to check how many 'f'/'b' commands to push onto the vector because we cannot send miliseconds yet
		for(int i = 0; diff - 30 >= i && i  <= diff + 30;)
		{
			m_commands.push_back( /**( new */ RobotCommand('f',DEBUG_MOVE));//););//((start.y - end.y)*SPACE_TO_MILISECONDS))));
			i += 100;
		}
		
	}else if(start.y < end.y)
	{

		diff = end.y - start.y;
		//move backward
		//this for-loop is completely for alpha testing. It is to check how many 'f'/'b' commands to push onto the vector because we cannot send miliseconds yet
		for(int i = 0; diff - 30 >= i && i  <= diff + 30;)
		{
			//move backward
			m_commands.push_back(/**( new */ RobotCommand('b',DEBUG_MOVE));//););//((end.y - start.y)*SPACE_TO_MILISECONDS))));
			i += 100;
		}
		
	}else
	{ /*Might be empty*/}
	
	
	return heading;
}
int PathVector::translateRight(Point start, Point end, int heading)
{
	int diff = 0;
	if(start.x > end.x)
	{
		diff = start.x - end.x;
		//this for-loop is completely for alpha testing. It is to check how many 'f'/'b' commands to push onto the vector because we cannot send miliseconds yet
		for(int i = 0; diff - 30 >= i && i <= diff + 30;)
		{
		
			//backward
			m_commands.push_back(/**( new */ RobotCommand('b',DEBUG_MOVE));//););//((end.x - start.x)*SPACE_TO_MILISECONDS))));		
			i += 100;
		}
			
	}else if(start.x < end.x)
	{

		diff = end.x - start.x;
		//this for-loop is completely for alpha testing. It is to check how many 'f'/'b' commands to push onto the vector because we cannot send miliseconds yet
		for(int i = 0; diff - 30 >= i && i <= diff + 30;)
		{
		
			//forward
			m_commands.push_back(/**( new */ RobotCommand('f',DEBUG_MOVE));//););//((end.x - start.x)*SPACE_TO_MILISECONDS)))); 
			i += 100;
		}
		
	}else if(start.y > end.y)
	{
		//move left
			//turn left
			//move forward
		m_commands.push_back(/**( new */ RobotCommand('l',DEBUG_TURN));//););//NINTY_DEGREES))); //90 is wrong but whatever the time to turn 90 degrees is correct
	
		diff = start.y - end.y;
		//this for-loop is completely for alpha testing. It is to check how many 'f'/'b' commands to push onto the vector because we cannot send miliseconds yet
		for(int i = 0; diff - 30 >= i && i <= diff + 30;)
		{
			//forward
			//so PIX_TO_MILISECONDS is some #define that is the number of miliseconds to to move 1 pixle
			m_commands.push_back(/**( new */ RobotCommand('f',DEBUG_MOVE));//););//((start.y - end.y)*SPACE_TO_MILISECONDS)))); 
			i += 100;
		}

		heading = 1;
	}else if(start.y < end.y)
	{
		//move right
			//turn right
			//move forward
		m_commands.push_back(/**( new */ RobotCommand('r',DEBUG_TURN));//););//NINTY_DEGREES)));
		
		
		diff = start.y - end.y;
		//this for-loop is completely for alpha testing. It is to check how many 'f'/'b' commands to push onto the vector because we cannot send miliseconds yet
		for(int i = 0; diff - 30 >= i && i <= diff + 30;)
		{
			//forward
			//so PIX_TO_MILISECONDS is some #define that is the number of miliseconds to to move 1 pixle
			
			m_commands.push_back(/**( new */ RobotCommand('f',DEBUG_MOVE));//););//((end.y - start.y)*SPACE_TO_MILISECONDS))));
			i += 100;
		}

		heading = 3;
	}else
	{ /*Might be empty*/}
	
	return heading;
}
int PathVector::translateBottom(Point start, Point end, int heading)
{
	int diff = 0;
	if(start.x > end.x)
	{
		//move right
			//turn right
			//move forward
		m_commands.push_back(/**( new */ RobotCommand('r',DEBUG_TURN));//););//NINTY_DEGREES)));
	
		diff = start.x - end.x;
		//this for-loop is completely for alpha testing. It is to check how many 'f'/'b' commands to push onto the vector because we cannot send miliseconds yet
		for(int i = 0; diff - 30 >= i && i <= diff + 30;)
		{
			//forward
			//so PIX_TO_MILISECONDS is some #define that is the number of miliseconds to to move 1 pixle
			
			m_commands.push_back(/**( new */ RobotCommand('f',DEBUG_MOVE));//););//((start.x - end.x)*SPACE_TO_MILISECONDS))));
			i += 100;
		}
		
		heading = 2;
		
	}else if(start.x < end.x)
	{
		//move left
			//turn left
			//move forward
		m_commands.push_back(/**( new */ RobotCommand('l',DEBUG_TURN));//););//NINTY_DEGREES))); //90 is wrong but whatever the time to turn 90 degrees is correct
		
		
		diff = end.x - start.x;
		//this for-loop is completely for alpha testing. It is to check how many 'f'/'b' commands to push onto the vector because we cannot send miliseconds yet
		for(int i = 0; diff - 30 >= i && i <= diff + 30;)
		{
			//forward
			//so PIX_TO_MILISECONDS is some #define that is the number of miliseconds to to move 1 pixle
			m_commands.push_back(/**( new */ RobotCommand('f',DEBUG_MOVE));//););//((end.x - start.x)*SPACE_TO_MILISECONDS)))); 
			i += 100;
		}
		
		heading = 4;
	}else if(start.y > end.y)
	{

		diff = start.y - end.y;
		//this for-loop is completely for alpha testing. It is to check how many 'f'/'b' commands to push onto the vector because we cannot send miliseconds yet
		for(int i = 0; diff - 30 >= i && i <= diff + 30;)
		{
			//move backward
			m_commands.push_back(/**( new */ RobotCommand('b',DEBUG_MOVE));//););//((start.y - end.y)*SPACE_TO_MILISECONDS))));
			i += 100;
		}
				
	}else if(start.y < end.y)
	{
		
		diff = end.y - start.y;
		//this for-loop is completely for alpha testing. It is to check how many 'f'/'b' commands to push onto the vector because we cannot send miliseconds yet
		for(int i = 0; diff - 30 >= i && i <= diff + 30;)
		{
			//move forward
			m_commands.push_back(/**( new */ RobotCommand('f',DEBUG_MOVE));//););//((end.y - start.y)*SPACE_TO_MILISECONDS))));
			i += 100;
		}
		
	}else
	{ /*Might be empty*/}
	
	return heading;
}
int PathVector::translateLeft(Point start, Point end, int heading)
{
	int diff = 0;
	if(start.x > end.x)
	{
		diff = start.x - end.x;
		//this for-loop is completely for alpha testing. It is to check how many 'f'/'b' commands to push onto the vector because we cannot send miliseconds yet
		for(int i = 0; diff - 30 >= i && i <= diff + 30;)
		{
			//move backward
			m_commands.push_back(/**( new */ RobotCommand('b', DEBUG_MOVE));//););//((start.x - end.x)*SPACE_TO_MILISECONDS))));
			//.push_back(RobotCommand('b',100);
			i += 100;
		}
	}else if(start.x < end.x)
	{

		diff = end.x - start.x;
		//this for-loop is completely for alpha testing. It is to check how many 'f'/'b' commands to push onto the vector because we cannot send miliseconds yet
		for(int i = 0; diff - 30 >= i && i <= diff + 30;)
		{
			//move forward
			m_commands.push_back(/**( new */ RobotCommand('f',DEBUG_MOVE));//););//((end.x - start.x)*SPACE_TO_MILISECONDS))));
			i += 100;
		}

	}else if(start.y > end.y)
	{
		//move right
			//turn right
			//move forward
		m_commands.push_back(/**( new */ RobotCommand('r',DEBUG_TURN));//););//NINTY_DEGREES)));
		
		diff = start.y - end.y;
		//this for-loop is completely for alpha testing. It is to check how many 'f'/'b' commands to push onto the vector because we cannot send miliseconds yet
		for(int i = 0; diff - 30 >= i && i <= diff + 30;)
		{
			//move forward
			m_commands.push_back(/**( new */ RobotCommand('f',DEBUG_MOVE));//););//((start.y - end.y)*SPACE_TO_MILISECONDS))));
			i += 100;
		}
		
		heading = 1;
		
	}else if(start.y < end.y)
	{
		//move left
			//turn left
			//move forward
		m_commands.push_back(/**( new */ RobotCommand('l',DEBUG_TURN));//););//NINTY_DEGREES))); //90 is wrong but whatever the time to turn 90 degrees is correct
		
		diff = end.y - start.y;
		//this for-loop is completely for alpha testing. It is to check how many 'f'/'b' commands to push onto the vector because we cannot send miliseconds yet
		for(int i = 0; diff - 30 >= i && i <= diff + 30;)
		{
			//move forward
			//so PIX_TO_MILISECONDS is some #define that is the number of miliseconds to to move 1 pixle
			m_commands.push_back(/**( new */ RobotCommand('f',DEBUG_MOVE));//););//((end.y - start.y)*SPACE_TO_MILISECONDS)))); 
			i += 100;
		}
		
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