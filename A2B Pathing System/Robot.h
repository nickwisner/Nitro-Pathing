///////////////////////////////////////////////////////////
//  Robot.h
//  Implementation of the Class Robot
//  Created on:      17-Apr-2011 5:14:48 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#include <opencv2/imgproc/imgproc.hpp>
using cv::Mat;

#ifndef ROBOT_H
#define ROBOT_H

class Robot
{

public:
	Robot(int brate, int distance_per_cycle, int len, int wid, Mat &symbol);
	~Robot();
	Robot & operator=( const Robot & cpy);
	Robot( const Robot & cpy);

	int baudrate();
	int distancePerCycle();
	int length();
	Mat peekSymbol();
	int width();

private:
	int m_baudrate;
	int m_distancepercycle;
	int m_length;
	Mat m_symbol;
	int m_width;

};
#endif