///////////////////////////////////////////////////////////
//  PathVector.h
//  Implementation of the Class PathVector
//  Created on:      17-Apr-2011 5:14:35 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

//#if !defined(EA_D8F473F6_2161_4aaa_A9F0_5C1F1D364CD8__INCLUDED_)
//#define EA_D8F473F6_2161_4aaa_A9F0_5C1F1D364CD8__INCLUDED_
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
	PathVector( Edge e, int & heading);
	PathVector( const PathVector & cpy);
	PathVector & operator=(const PathVector & cpy);
	virtual ~PathVector();

	float getAngle();
	Edge getEdge();
	RobotCommand popCommand();

	int getCommandSize();

private:
	float m_angle;
	list<RobotCommand> m_commands; //used to be a vector
	Edge m_edge;

	int translateUp(Point start, Point end, int heading);
	int translateBottom(Point start, Point end, int heading);
	int translateRight(Point start, Point end, int heading);
	int translateLeft(Point start, Point end, int heading);


};
#endif // !defined(EA_D8F473F6_2161_4aaa_A9F0_5C1F1D364CD8__INCLUDED_)
