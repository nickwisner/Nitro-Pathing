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
	m_currMissionID = 0;


	// read mission log
	// while not endoffile
		// currMissionID = mission id on current line

}

ErrorLogger::~ErrorLogger()
{}


int ErrorLogger::getCurrentMission()
{
	// return missionid
	return m_currMissionID;
}


bool ErrorLogger::endMission(int endspace)
{
	bool success(false);

	m_errStream.open(ERR_LOG_FILE_NAME, ios::app);


	// log the mission end with end point, mission id and time
	if( m_errStream.is_open() )
	{
		m_errStream << "END ";
		m_errStream << m_currMissionID;
		m_errStream << " ";
		m_errStream << endspace;
		m_errStream << " ";
		m_errStream << A2BUtilities::GetTime();

		m_errStream.close();
	}

	// return if we successfully logged it
	return success;
}


void ErrorLogger::insertError(ErrorLog code)
{
	m_errStream.open(ERR_LOG_FILE_NAME, ios::app); // appending data to end of file

	if( m_errStream.is_open() )
	{
		m_errStream << "ERR ";
		m_errStream << code;	// write the error line into the file

		m_errStream.close();
	}
}


int ErrorLogger::startMission(int start, int dest)
{
	// increment the current mission id
	m_currMissionID++;

	m_errStream.open(ERR_LOG_FILE_NAME, ios::app);

	if( m_errStream.is_open() )
	{
		m_errStream << "START ";
		m_errStream << start;
		m_errStream << " ";
		m_errStream << dest;
		m_errStream << " ";
		m_errStream << A2BUtilities::GetTime();

		m_errStream.close();
	}
	// create log of mission start including missionid, start point, destination point and time
	// open file for append writing
	// enter line

	// return the missionid
	return m_currMissionID;
}


void ErrorLogger::error(ErrorLog err)
{
	// insert error
	// needs a lock if we thread this
	m_errStream.open(ERR_LOG_FILE_NAME, ios::app); // appending data to end of file

	if( m_errStream.is_open() )
	{
		m_errStream << "ERR ";
		m_errStream << err;	// write the error line into the file

		m_errStream.close();
	}
}


Robot ErrorLogger::getRobot()
{
	return Robot(9600, 1, 50, 75, cv::imread("true_robot.png"));
}


void ErrorLogger::update(string query)
{
	;
}