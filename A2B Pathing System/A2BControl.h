///////////////////////////////////////////////////////////
//  A2BControl.h
//  Implementation of the Class A2BControl
//  Created on:      18-Apr-2011 7:33:30 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#ifndef A2BCONTROL_H
#define A2BCONTROL_H

#include <opencv2/imgproc/imgproc.hpp>
using cv::Point;
using cv::Mat;

#include <opencv2/highgui/highgui.hpp>
#include "RobotIO.h"
#include "iPathing.h"
#include "iImageAcquisition.h"
#include "iDatabase.h"
#include "Timer.h"
#include "iGUI.h"
#include "iControl.h"
#include "ImageProcessor.h"
#include "A2BUtilities.h"


#include "A2BGUI.h"
#include "ImageAcquisition.h"
#include "A2BDatabase.h"
#include "Pathing.h"
#include "RobotIO.h"

#include "PathVector.h"
#include "RobotCommand.h"

class A2BControl : public iControl
{

public:
	A2BControl();
	virtual ~A2BControl();
	
	//Ends the mission with a pass or fail code entered in
	bool endMission(int error);
	//joins all threads and ends them
		//Not implemented
	void endThreads();
	//Finds the robot, and makes the path
		//Then sends the path to robotio and sends the whole queue of messages to the robot
	bool setDestination(Point dest);
	//Starts up all threads
		//Not implimented
	void startThreads();
	//Will update the image and check the path
		//Not implimented
	void update();
	
	//checks to see if there are any save queueres
		//Not implimented
	bool checkSavedQueries();
	//Saves the queries off to a flat file
		//Not implimented
	void saveQueriesToFile();
	//sets all of the false (obsticles) on the bool array for where the robot is
		//AKA makes the robot no longer a obsticle in the bool array
	void clearRobot(int space, bool * obstMap, Point robPos);

private:
	iGUI * m_gui; // Interface of the GUI through which to send image, path, and errors to display.
	iImageAcquisition * m_imageacquisition; // Interface through which we can get a picture from the camera.
	iPathing * m_pathing; // Interface through which we can generate a path with corresponding commands for the robot, etc.
	iRobotIO * m_robotio; // Interface through which we can send the path to queue commands, and tell when to send commands out to the robot.
	iDatabase * m_database; //Interface to update database through (missions, errors)
	
	Mat m_edgedImage; // Holds the image of the room with edge detecting effects on it.
	Mat m_plainImage; // The raw, unprocessed image of the floor. A "human" view of things.

	Timer * m_tUpdatePath; // This timer goes off when it is time to update the path, the picture, etc.
	
	//Dont know if we need a mutex
//	boost::mutex m_obstLock;

	boost::thread m_updatePath;

	boost::mutex m_obstLock;
	boost::mutex m_plainLock;

	bool * m_obstacleMap; // This bool array contains the place ment of open spaces and obsticle spaces. In terms of SPACE [ 8px X 8px ] 
	
	bool m_showPlainImage; // whether to send plain image to GUI (true), or edged (false)

	bool runPath();
	bool sendCommand();
};
#endif
