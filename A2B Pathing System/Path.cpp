///////////////////////////////////////////////////////////
//  Path.cpp
//  Implementation of the Class Path
//  Created on:      17-Apr-2011 5:14:23 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#include "Path.h"
#include "Edge.h"

Path::Path()
{
/*	m_pathPoints.push_back(Point(75,10));
	m_pathPoints.push_back(Point(85,10));
	m_pathPoints.push_back(Point(85,15));
	m_pathPoints.push_back(Point(95,20));
	m_pathPoints.push_back(Point(50,10));
	m_pathPoints.push_back(Point(175,90));
	m_pathPoints.push_back(Point(75,10));*/
}



Path::~Path(){

}

int Path::getPathVSize()
{
	return m_path.size();
}

void Path::addVector(PathVector vector)
{
	if(m_pathPoints.empty())
	{
		m_pathPoints.push_back(vector.getEdge().getStart());
			//Point(vector.getEdge().getStart().x,vector.getEdge().getStart().y));
		m_pathPoints.push_back(vector.getEdge().getEnd());
			//Point(vector.getEdge().getEnd().x, vector.getEdge().getEnd().y));
	}else
	{
		m_pathPoints.push_back(vector.getEdge().getEnd());
			//Point(vector.getEdge().getEnd().x,vector.getEdge().getEnd().y));
	}

	m_path.push_back(vector);
}

PathVector Path::getPathVector(int i)
{
	return m_path[i];

}
PathVector Path::popVector()
{
	//this this is not used
	PathVector p;
	return p;
}

vector<Point> & Path::getPathPoints()
{
	return m_pathPoints;
}

Path::Path( const Path & cpy)
{
	*this = cpy;
}
Path& Path::operator=(const Path & cpy)
{
	if(this != &cpy)
	{
		this->m_path = cpy.m_path;
		this->m_pathPoints = cpy.m_pathPoints;
	}

	return *this;
}