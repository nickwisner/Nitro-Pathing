///////////////////////////////////////////////////////////
//  Pathing.cpp
//  Implementation of the Class Pathing
//  Created on:      18-Apr-2011 8:27:43 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////


#include "Pathing.h"


Pathing::Pathing() : m_active(false), m_robot(0), m_path(0)
{
	m_dijk = new Dijkstra(ROW_SIZE, COL_SIZE);	// create our dijkstra map of a specified grid size
}

Pathing::~Pathing()
{
	delete m_path;
	delete m_dijk;
	delete m_robot;
}

/**
 * Deletes the current path and sets the path pointer to null.
 */
bool Pathing::deletePath(){

	return false;
}


/**
 * Returns the path pointer
 */
Path * Pathing::getPath()
{
	return  m_path;
}


/**
 * Returns whether it is active or not
 */
bool Pathing::isActive()
{
	return m_active;
}


/**		CALL INTO DIJKSTRA HERE! *************
 * Generates the path using given coordinates 
 */
bool Pathing::makePath(int destSpace, int startSpace, bool * obstMap)
{
	// create the vector of path points using dijkstra's
	vector<int> pathPoints = m_dijk->Start(startSpace, destSpace, obstMap);

	// if we found a valid path
	if(!pathPoints.empty())
	{
		// take out the extra points that are on the same vector
		pathPoints = gutPoints(pathPoints);

		// calculate the pixel location mapped to the grid points
		translateToPath(pathPoints);

		// the path is made so we are now actively pathing
		m_active = true;
	}
	else	// didn't find a valid path
	{
		m_active = false;
	}

	return m_active;
}

//Will take the vector of points and return another vector of points filled with only the vertexes of direction change
vector<int> Pathing::gutPoints(const vector<int> &pathPoints)
{
	int spaceDiff = pathPoints[1] - pathPoints[0];
	vector<int> newPath;

	// starting point
	newPath.push_back(pathPoints[0]);

	// for each point, compare it with the direction the previous point was heading
	for(int currPoint(1); currPoint < pathPoints.size(); currPoint++)
	{
		// going in a different direction
		if(!(pathPoints[currPoint] - pathPoints[currPoint-1] == spaceDiff))
		{
			// save the previous point
			newPath.push_back(pathPoints[currPoint-1]);

			// store the "direction"
			spaceDiff = pathPoints[currPoint] - pathPoints[currPoint-1];
		}
	}

	// get last point
	newPath.push_back(pathPoints[pathPoints.size()-1]);

	return newPath;
}

// not implemented yet (this should be ready in beta)
bool Pathing::repath()
{
	return false;
}

// define the robot we are using for the system
bool Pathing::setRobot( Robot & domoarigato)
{
	m_robot = new Robot(domoarigato);
	return true;
}

// getter for the robot used with the system
Robot * Pathing::getRobot()
{
	return m_robot;
}

// getter for the robot's current pixel location
Point Pathing::getRobotPosition()
{
	return m_robotpos;
}

/**
 * This checks the coordinates in the path vs the coordinates in m_obstacles
 * (vector<Obstacle>)
 */
// not implemented yet, just sending back dummy data
bool Pathing::validatePath()
{
	return false;
}

//takes a vector of ints, which represent the spaces [16x16 pixle squares] on the image, and then converts them into robot commands
void Pathing::translateToPath( vector<int> path)
{
	if( m_path != 0)
		delete m_path;

	if(!path.empty())
	{
		m_path = new Path;
		Edge e;
		PathVector * temp;
	
	// enum will be useful here (implement later)
	//assuming the robot is facing the top of the screen and that :
		// 1 = robot facing top
		// 2 = robot facing right
		// 3 = robot facing bottom
		// 4 = robot facing left

		int tempHeading = 1;
		//from the points to a bunch of pathvectors

		for(int i = 1; i < path.size(); i++)
		{
		
			//the first param of Point is x the second param of Point is y
			//the first is which column and the second is which row it is in
		
			//we dont delete this here because it should be deleted in path!!!
			//cuz they both have the same pointer
			//i-1 is the starting place and i is the end of the edge
			temp = new PathVector(Edge(Point((path[i-1]%ROW_SIZE)*GRID_SQUARE_SIZE, (path[i-1]/ROW_SIZE)*GRID_SQUARE_SIZE), Point((path[i]%ROW_SIZE)*GRID_SQUARE_SIZE, (path[i]/ROW_SIZE)*GRID_SQUARE_SIZE)), tempHeading);
			m_path->addVector(*temp);	
		}
	}
}

