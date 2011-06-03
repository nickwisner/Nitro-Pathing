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
	//This constructor will be called after the database gets all of the robot information 
	Robot(int brate, int distance_per_milisec, int len, int wid, Mat &symbol);
	//A deconstructor, nothing is newed so nothing is destroyed
	~Robot();
	//A operator= that makes a deep copy
	Robot & operator=( const Robot & cpy);
	//A copy constroctor that makes a deep copy
	Robot( const Robot & cpy);

	//Returns the baudrate
	int getBaudrate();
	//Return the distance the robot travels in 1 milisecond
	int getDistancePerMiliseconds();
	//Returns the length of the robot in pixles
	int getLength();
	//Returns the image of the robot to try and find inside of the camera image
	Mat peekSymbol();
	//returns the width of the robot in pixles.
	int getWidth();

private:
	//This is the tranfser rate of our bluetooth, called the baudrate
	int m_baudrate;
	//This is the distance the robot will move in 1 miliseconds
	int m_distancepermiliseconds;
	//This is the length of the robot in px
	int m_length;
	//This is the picture for the system to try and find the robot with on the inputed image
	Mat m_symbol;
	//The width of the robot in px
	int m_width;

};
#endif