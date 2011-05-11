/**************************** Class: Edge *****************************
* Holds two points, a start and an end.
* 
* Methods: There are getters and setters for each point.
* 
* This is used in A2B Pathing to define the start and end point of
* a PathVector, which is aggregated by Path.
**********************************************************************/
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

	// Getters
	Point getEnd();
	Point getStart();

	// Setters
	void setStart(Point start);
	void setEnd(Point end);

private:
	Point m_end;
	Point m_start;

};

#endif