/************************* Class: PathVector **************************
*  PathVector.h
*  Implementation of the Class PathVector
*  Created on:      17-Apr-2011 5:14:35 PM
*  Original author: peter.finn
*
* Constructors:
*	PathVector() - The base constructor creating a empty list of
*	robot commands and using a base constructor of Edge.
*	
*	PathVector( Edge e, int & heading) - This constructor is the most
*	used because it also translates the Edge that is entered into
*	robot commands. Should break this functionality out of the
*	constructor.
*	
*	PathVector( const PathVector & cpy) - This constructor makes a
*	deep cpy of the robot commands (m_commands ) and also the
*	starting and ending point ( m_edge )
*	
*	virtual ~PathVector() - This clears out the message command and
*	calls the deconstructor of edge.
* 
* Mutators:
*	Edge getEdge() - Returns a copy of m_edge
*	
*	int getCommandSize() - Returns the number of robot commands
*	inside of the list
*	
*	RobotCommand popCommand() - Returns the front of the robot
*	command list and then removes it from list.
*	
* 
* Methods:
*	int translateUp(Point start, Point end, int heading) - From the
*	start and end point ( in pixels ) and then translates them into a
*	robot command which it pushes onto the list. Returns a int which
*	should be caught back into heading. This function is only called
*	if the heading is 1. Meaning the robot is facing up.
*	
*	int translateBottom(Point start, Point end, int heading) - From
*	the start and end point ( in pixels ) and then translates them
*	into a robot command which it pushes onto the list. Returns a int
*	which should be caught back into heading. This function is only
*	called if the heading is 3. Meaning the robot is facing down.
*	
*	int translateRight(Point start, Point end, int heading) - From
*	the start and end point ( in pixels ) and then translates them
*	into a robot command which it pushes onto the list. Returns a int
*	which should be caught back into heading. This function is only
*	called if the heading is 2. Meaning the robot is facing right.
*	
*	int translateLeft(Point start, Point end, int heading) - From the
*	start and end point ( in pixels ) and then translates them into a
*	robot command which it pushes onto the list. Returns a int which
*	should be caught back into heading. This function is only called
*	if the heading is 4. Meaning the robot is facing left.
**********************************************************************/

#ifndef __PATH_VECTOR
#define __PATH_VECTOR

#include "Edge.h"
#include "RobotCommand.h"

#include <vector>
using std::vector;

#include <list>
using std::list;

class PathVector
{

public:
	PathVector();
	PathVector( Edge e, int & heading );
	PathVector( const PathVector & cpy);
	PathVector & operator=(const PathVector & cpy);
	virtual ~PathVector();

	// Getters
	Edge getEdge();
	RobotCommand popCommand();
	int getCommandSize();

private:
	//A list to hold all of the robotCommand to complete this part of the path
	list<RobotCommand> m_commands; 
	//The starting and ending point in pixels that represent where the robot will start and where it should end
	Edge m_edge;

	int findTravelTime(float diff);

	//These four functions take the starting and ending place in pixles and pushes a robot command 
	//(that will get the robot from the starting place to the ending place) into the list of robot commands/
	int translateUp(Point start, Point end);
	int translateBottom(Point start, Point end);
	int translateRight(Point start, Point end);
	int translateLeft(Point start, Point end);

};
#endif
