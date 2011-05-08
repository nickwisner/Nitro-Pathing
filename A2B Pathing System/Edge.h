///////////////////////////////////////////////////////////
//  Edge.h
//  Implementation of the Class Edge
//  Created on:      17-Apr-2011 5:13:49 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#if !defined(EA_EB5B4313_AF62_4540_8607_AF31F1793B4A__INCLUDED_)
#define EA_EB5B4313_AF62_4540_8607_AF31F1793B4A__INCLUDED_

#include <opencv2/imgproc/imgproc.hpp>
using cv::Point;

class Edge
{

public:
	Edge();
	Edge( Point s, Point e);
	Edge( const Edge & cpy );
	Edge & operator=( const Edge & cpy );
	virtual ~Edge();

	Point getEnd();
	Point getStart();

	void setStart(Point start);
	void setEnd(Point end);

private:
	Point m_end;
	Point m_start;

};
#endif // !defined(EA_EB5B4313_AF62_4540_8607_AF31F1793B4A__INCLUDED_)
