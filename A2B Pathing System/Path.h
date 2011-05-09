///////////////////////////////////////////////////////////
//  Path.h
//  Implementation of the Class Path
//  Created on:      17-Apr-2011 5:14:22 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

//#if !defined(EA_E5B9E8A1_8074_41fc_940E_A5273EB81DA1__INCLUDED_)
//#define EA_E5B9E8A1_8074_41fc_940E_A5273EB81DA1__INCLUDED_
#ifndef __PATH_H
#define __PATH_H

#include <opencv2/imgproc/imgproc.hpp>
using cv::Point;

#include "PathVector.h"

#include <vector>
using std::vector;

class Path
{

public:
	Path();
	virtual ~Path();
	Path( const Path & cpy);
	Path& operator=(const Path & cpy);

	void addVector(PathVector vector);
	PathVector popVector();
	vector<Point> & getPathPoints();
	PathVector getPathVector(int i);
	int	getPathVSize();

private:
	vector<PathVector> m_path;
	vector<Point> m_pathPoints;
};
#endif //__PATH_H
// !defined(EA_E5B9E8A1_8074_41fc_940E_A5273EB81DA1__INCLUDED_)
