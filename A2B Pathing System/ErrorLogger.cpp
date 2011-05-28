///////////////////////////////////////////////////////////
//  ErrorLogger.cpp
//  Implementation of the Class ErrorLogger
//  Created on:      17-Apr-2011 5:24:53 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#include "ErrorLogger.h"
#include "A2BUtilities.h"
#include <opencv2/highgui/highgui.hpp>

using std::ios;

ErrorLogger::ErrorLogger()
{
	m_errFName = ERR_LOG_FILE_NAME;

	// get last mission id from mission log
}

ErrorLogger::~ErrorLogger()
{}


int ErrorLogger::getCurrentMission()
{
	// return missionid
	return 0;
}


bool ErrorLogger::endMission(Point end)
{
	// log the mission end with end point, mission id and time
	// return if we successfully logged it
	return false;
}


void ErrorLogger::insertError(ErrorLog code)
{
	m_errStream.open(ERR_LOG_FILE_NAME, ios::app); // appending data to end of file

	if( m_errStream.is_open() )
	{
		m_errStream << code;	// write the error line into the file

		m_errStream.close();
	}
}


int ErrorLogger::startMission(Point start, Point dest)
{
	// increment the current mission id
	// create log of mission start including missionid, start point, destination point and time
	// return the missionid
	return 0;
}


void ErrorLogger::error(ErrorLog err)
{
	// insert error
	// needs a lock if we thread this
}


Robot ErrorLogger::getRobot()
{
	return Robot(9600, 1, 50, 75, cv::imread("true_robot.png"));
}


void ErrorLogger::update(string query)
{
	;
}