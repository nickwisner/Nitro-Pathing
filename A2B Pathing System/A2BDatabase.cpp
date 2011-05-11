///////////////////////////////////////////////////////////
//  A2BDatabase.cpp
//  Implementation of the Class A2BDatabase
//  Created on:      17-Apr-2011 5:24:53 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#include "A2BDatabase.h"
#include <opencv2/highgui/highgui.hpp>


A2BDatabase::A2BDatabase()
{
	// initialize database here
}



A2BDatabase::~A2BDatabase()
{}


int A2BDatabase::currentMission(){

	return 0;
}


bool A2BDatabase::endMission(Point end){

	return false;
}


void A2BDatabase::initialization(){

}


void A2BDatabase::insertError(ErrorLog code){

}


int A2BDatabase::startMission(Point start, Point dest){

	return 0;
}


void A2BDatabase::error(ErrorLog err)
{
	// insert error
}


Robot A2BDatabase::getRobot()
{
	return Robot(9600, 1, 50, 75, cv::imread("true_robot.png"));
}


void A2BDatabase::update(string query)
{
	;
}