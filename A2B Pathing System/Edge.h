///////////////////////////////////////////////////////////
//  Edge.h
//  Implementation of the Class Edge
//  Created on:      17-Apr-2011 5:13:49 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#ifndef EDGE_H
#define EDGE_H

#include <opencv2/imgproc/imgproc.hpp>
using cv::Point;

class Edge
{

public:
	Edge();
	Edge( Point start, Point end );
	Edge( const Edge & cpy );
	Edge & operator=( const Edge & cpy );
	~Edge();

	Point getEnd();
	Point getStart();

	void setStart(Point start);
	void setEnd(Point end);

private:
	Point m_end;
	Point m_start;

};

#endif