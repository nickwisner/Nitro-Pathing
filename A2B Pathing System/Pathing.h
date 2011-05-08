///////////////////////////////////////////////////////////
//  Pathing.h
//  Implementation of the Class Pathing
//  Created on:      27-Apr-2011 5:12:10 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#if !defined(EA_D0407D07_6312_42a3_A1E3_5C5826C06F18__INCLUDED_)
#define EA_D0407D07_6312_42a3_A1E3_5C5826C06F18__INCLUDED_

#include "Image.h"
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
 * This class contains all the functionanitly to create a path
 */
class Pathing : public iPathing
{

public:
	Pathing();
	virtual ~Pathing();

	bool deletePath();
	Path * getPath();
	bool isActive();
	bool repath();
	bool makePath( int destSpace, int startSpace, bool * obstMap);
	bool validatePath();
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

	// why is this commented out?
	//Path * makePath(Point destination);
	void translateToPath( vector<int> path);
	vector<int> gutPoints(const vector<int> & pathPoints);
};

#endif // !defined(EA_D0407D07_6312_42a3_A1E3_5C5826C06F18__INCLUDED_)


