///////////////////////////////////////////////////////////
//  Pathing.h
//  Implementation of the Class Pathing
//  Created on:      27-Apr-2011 5:12:10 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#ifndef PATHING_H
#define PATHING_H

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

	void deletePath();
	Path * getPath();
	bool isActive();
	void setActive(bool act);
	bool repath(int robotPos, bool * obstMap);
	bool makePath( Point destPoint, int startSpace, bool * obstMap);
	bool validatePath(bool * obstMap);
	Point getRobotPosition();
	
	bool setRobot(Robot & domoarigato);
	Robot * getRobot();

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
	
	vector<int> m_pathPoints;
	
	// turn the path points into pixel points and place in m_path
	void translateToPath( vector<int> path);

	// remove any unnecessary spaces in a space vector
	vector<int> gutPoints(const vector<int> & pathPoints);
};

#endif
