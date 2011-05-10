///////////////////////////////////////////////////////////
//  Edge.cpp
//  Implementation of the Class Edge
//  Created on:      17-Apr-2011 5:13:49 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#include "Edge.h"


Edge::Edge() : m_start(Point(0,0)), m_end(Point(0,0))
{ }

Edge::Edge( Point start, Point end ) : m_start(start), m_end(end)
{ }

Edge::Edge( const Edge & cpy )
{
	*this = cpy;
}

Edge & Edge::operator=( const Edge & cpy )
{
	if(this != &cpy)
	{
		this->m_end = cpy.m_end;
		this->m_start = cpy.m_start;
	}
	return *this;
}
void Edge::setStart(Point start)
{
	m_start = start;
}
void Edge::setEnd(Point end)
{
	m_end = end;
}

Edge::~Edge()
{ }

Point Edge::getEnd()
{
	return  m_end;
}

Point Edge::getStart()
{
	return m_start;
}