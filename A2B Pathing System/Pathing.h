///////////////////////////////////////////////////////////
//  Pathing.h
//  Implementation of the Class Pathing
//  Created on:      27-Apr-2011 5:12:10 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#ifndef PATHING_H
#define PATHING_H

#ifndef __MYWINSOCK2_H
#define __MYWINSOCK2_H
#pragma push_macro("_WINSOCKAPI_")
// We clear _WINSOCKAPI_ to avoid preprocessor warnings about
// multiple definitions of the _WINSOCKAPI_ macro, as winsock2.h will
// attempt to #define _WINSOCKAPI_ itself.
#undef _WINSOCKAPI_
#include <boost/asio/detail/socket_types.hpp>
#pragma pop_macro("_WINSOCKAPI_")
#endif // __MYWINSOCK2_H

#include "Robot.h"
#include "Path.h"
#include "ImageProcessor.h"
#include "iPathing.h"

#include "pathing/Dijkstra.h"

#include <opencv2/imgproc/imgproc.hpp>
using cv::Point;
#include <opencv2/highgui/highgui.hpp>
#include "A2BUtilities.h"
/**
 * This class contains all the functionality to create a path
 */
class Pathing : public iPathing
{

public:
	Pathing();
	~Pathing();

	bool deletePath();
	Path * getPath();
	bool isActive();
	bool repath();
	bool makePath( int destSpace, int startSpace, bool * obstMap);
	bool validatePath();
	Point getRobotPosition();
	int getHeading();
	void stopPath();
	bool setRobot(Robot & domoarigato);
	Robot * getRobot();
	void setStop(bool lean);
	bool getStop();

private:
	/**
	 * If this is true, the a path is currently being generated or traveled.
	 */
	bool m_active;
	/**
	 * This holds the coordinates to the desired destination.
	 */
	Point m_destination;
	/**
	 * The path for this system is stored right here. Null if there is no path.
	 */
	Path * m_path;
	/**
	 * The width of the robot in inches.
	 */
	Robot * m_robot;
	/**
	 * Holds the robot's current position in the picture.
	 */
	Point m_robotpos;

	// current pathing program
	Dijkstra * m_dijk;

	int m_heading;

	// turn the path points into pixel points and place in m_path
	void translateToPath( vector<int> path);

	// remove any unnecessary spaces in a space vector
	vector<int> gutPoints(const vector<int> & pathPoints);
};

#endif
