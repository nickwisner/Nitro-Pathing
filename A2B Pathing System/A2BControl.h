///////////////////////////////////////////////////////////
//  A2BControl.h
//  Implementation of the Class A2BControl
//  Created on:      18-Apr-2011 7:33:30 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#if !defined(EA_195E1D47_A88C_41f4_B5DE_CFA89E8B5E58__INCLUDED_)
#define EA_195E1D47_A88C_41f4_B5DE_CFA89E8B5E58__INCLUDED_

#include <opencv2/imgproc/imgproc.hpp>
using cv::Point;

#include <opencv2/highgui/highgui.hpp>
#include "RobotIO.h"
#include "iPathing.h"
#include "iImageAcquisition.h"
#include "iDatabase.h"
#include "Image.h"
#include "Timer.h"
#include "iGUI.h"
#include "iControl.h"
#include "ImageProcessor.h"
#include "A2BUtilities.h"

//this might be breaking the interface boudierys but we dont think so
#include "A2BGUI.h"
#include "ImageAcquisition.h"
#include "A2BDatabase.h"
#include "Pathing.h"
#include "RobotIO.h"
///

#include "PathVector.h"
#include "RobotCommand.h"

class A2BControl : public iControl
{

public:
	A2BControl();
	virtual ~A2BControl();

	bool endMission(int error);
	void endThreads();
	void edgeImage();
	bool sendCommand();
	bool setDestination(Point dest);
	void startThreads();
	bool update();
	
	bool checkSavedQueries();
	Image * getEdgedImage();
	void saveQueriesToFile();
	void getImage();
	void clearRobot(int space, bool * obstMap, Point robPos);

	//delete this ish after testing.
void sendTestVector( vector<RobotCommand> blah)
{
	for(int i = 0; i < blah.size(); i++)
	{
		try
		{
			m_robotio->sendCommand(blah[i]);
		}
		catch(int e)
		{
			m_gui->showError("Robot connection failure. Please turn robot on, then try again. ");
			i = blah.size() + 1;
		}
	}
}

void createTestVector()
{
	vector<RobotCommand> test;
	test.push_back(RobotCommand('f', 2));
	test.push_back(RobotCommand('r',2));
	test.push_back(RobotCommand('f', 2));
	test.push_back(RobotCommand('l',2));
	test.push_back(RobotCommand('b', 1));
	test.push_back(RobotCommand('f',1));
	sendTestVector(test);
}

void makeTestVector2()
{
	int heading = 1;
	vector<RobotCommand> test;
	Edge e1(Point(1,1), Point(10,1));
	Edge e2(Point(10,1), Point(10,10));
	
	PathVector v1(e1, heading);
	PathVector v2(e2, heading);
	
	for(int i = v1.getCommandSize(); i > 0; i-- )
	{
		test.push_back(v1.popCommand());
	}
	for(int i = v2.getCommandSize(); i > 0; i-- )
	{
		test.push_back(v2.popCommand());
	}
	sendTestVector(test);
}
void makeTestVector3()
{
	int heading = 1;
	vector<RobotCommand> test;
	Edge e1(Point(10,1), Point(1,1));
	Edge e2(Point(1,1), Point(1,10));
	
	PathVector v1(e1, heading);
	PathVector v2(e2, heading);
	
	for(int i = v1.getCommandSize(); i > 0; i-- )
	{
		test.push_back(v1.popCommand());
	}
	for(int i = v2.getCommandSize(); i > 0; i-- )
	{
		test.push_back(v2.popCommand());
	}
	sendTestVector(test);
}


private:
	iGUI * m_gui; // Interface of the GUI through which to send image, path, and errors to display.
	iImageAcquisition * m_imageacquisition; // Interface through which we can get a picture from the camera.
	iPathing * m_pathing; // Interface through which we can generate a path with corresponding commands for the robot, etc.
	iRobotIO * m_robotio; // Interface through which we can send the path to queue commands, and tell when to send commands out to the robot.
	iDatabase * m_database; //Interface to update database through (missions, errors)
	
	Image * m_edgedImage; // Holds the image of the room with edge detecting effects on it.
	Image * m_plainImage; // The raw, unprocessed image of the floor. A "human" view of things.

	Timer * m_tUpdatePath; // This timer goes off when it is time to update the path, the picture, etc.

	bool * m_obstacleMap; // This bool array contains the place ment of open spaces and obsticle spaces. In terms of SPACE [ 8px X 8px ] 
	
	bool m_showPlainImage;
	bool restartPing();
	bool runPath();

};
#endif // !defined(EA_195E1D47_A88C_41f4_B5DE_CFA89E8B5E58__INCLUDED_)
