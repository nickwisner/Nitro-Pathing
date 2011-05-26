///////////////////////////////////////////////////////////
//  A2BControl.cpp
//  Implementation of the Class A2BControl
//  Created on:      18-Apr-2011 7:33:31 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#include "A2BControl.h"

#include "RobotIO.h"

A2BControl::A2BControl() :m_tUpdatePath(0), m_robotio(0), m_imageacquisition(0), m_showPlainImage(true)
{
	m_gui = new A2BGUI;
	m_gui->setControl(this);

	//m_obstacleMap = new bool[ROW_SIZE * COL_SIZE];
	m_obstacleMap = 0;
	m_pathing = new Pathing;
	m_database = new A2BDatabase;
	m_pathing->setRobot( (m_database->getRobot()) );
}

A2BControl::~A2BControl()
{
	delete m_database;
	delete m_gui;
	delete m_pathing;
	delete m_imageacquisition;
	delete m_robotio;

	m_database = 0;
	m_gui = 0;
	m_pathing = 0;
	m_imageacquisition = 0;
	m_robotio = 0;

	delete [] m_obstacleMap;
	m_obstacleMap = 0;
}

/**
 * error = 0 if reach destination. Use this to end a mission whatever the reason;
 * this updates the database and so forth
 */
bool A2BControl::endMission(int error)
{
	if(error = 1)
	{
		m_pathing->stopPath();
	}
	return false;
}
void A2BControl::endThreads()
{
	// Not yet implemented. Once we have threads, we will kill
	// the threads in here and Control's destructor will call this.
}

bool A2BControl::runPath()
{
	// Not yet implemented. This is where we say
	// hey RobotIO, start sending those commands to the robot.
	// and m_robotio sends the robot to the destination successfully and we
	// return true instead of false.
	return false;
}


void A2BControl::saveQueriesToFile()
{
	// Not yet implemented. This was supposed to be where
	// queries that weren't saved to the database because there was some error
	// get saved to a file so that they get saved somewhere
	
	// but this is not a high priority at all.
}


bool A2BControl::checkSavedQueries()
{
	// similar to above, it checks for previously saved queries in file
	// and enters them to the database. or tries to again at least.

	// also very low priority
	return false;
}

bool A2BControl::sendCommand()
{
	// Not yet implemented. May or may not need this.
	// planned for this to send the next command in robotio's queue, like a pop
	return false;
}


bool A2BControl::setDestination(Point dest)
{
	bool * tmp = new bool[ROW_SIZE * COL_SIZE];
	Point robPos;
	int n = -1;
	int spaceStart = 0;
	int spaceDest = 0;

	//change the first part setDestinatoin to be "findRobot"

	bool foundrobot = true;
	for( int attempt = 0; attempt < 5 && !foundrobot; attempt++ )
	{
		m_obstLock.lock();
		memcpy(tmp, m_obstacleMap, sizeof(bool)* (ROW_SIZE*COL_SIZE));
		m_obstLock.unlock();

		m_plainLock.lock();
		robPos = ImageProcessor::findRobot((&m_plainImage), m_pathing->getRobot());
		m_plainLock.unlock();
		
		spaceStart = A2BUtilities::pixelToSpaceId(robPos.x, robPos.y);
		spaceDest = A2BUtilities::pixelToSpaceId( dest.x,dest.y);
		clearRobot(spaceStart, tmp, robPos);

		m_gui->markRobot(robPos);
		
		foundrobot = !m_gui->showError("Is this the robot?", MB_YESNO);
		// keep looping if they answer no. otherwise, exit loop
	}
	if( !foundrobot )
	{
		m_gui->showError("Cannot find the robot. Please locate the robot and verify it is in an area viewable by the camera.", MB_OK);
		return false;
	}

	m_gui->stopMarkingRobot();

	if( !m_pathing->makePath(spaceDest, spaceStart, tmp) )
	{
		m_gui->showError("Cannot create a path to indicated destination.",MB_OK);
	}
	else
	{
		m_robotio->fillQueue(m_pathing->getPath());

		
		m_gui->setPath(m_pathing->getPath()->getPathPoints());


		m_robotio->startCommunication();
		// this is only for the alpha release... will be replaced by startmission message being sent
		try
		{
			//this should call a method to send the data and listen data coming in aseconisly
			//m_robotio->SendQueue();
			
		}catch(int e)
		{
			m_gui->showError("Robot connection failure. Please turn robot on, then try again. ");
		}
	}

	//create a thread to handle updata.
//	m_updatePath = boost::thread(bind(&update, this));
	delete []tmp;
	return true;
}
void A2BControl::clearRobot(int robotCenter, bool * obstMap, Point robPos)
{

	//this is assuming that the robot is 11.25 cells long and wide. We will around it to 12 cells.
	//this is also assuming that the int passed in is the center cell of the robot.

	int topLeftSpace = (robotCenter - ((ROBOT_SIZE_SPACE/2)*ROW_SIZE)) - (ROBOT_SIZE_SPACE/2);
	int topRightSpace = (robotCenter - ((ROBOT_SIZE_SPACE/2)*ROW_SIZE)) + (ROBOT_SIZE_SPACE/2);
	int bottomRightSpace = (robotCenter + ((ROBOT_SIZE_SPACE/2)*ROW_SIZE)) + (ROBOT_SIZE_SPACE/2);
	int bottomLeftSpace = (robotCenter + ((ROBOT_SIZE_SPACE/2)*ROW_SIZE)) - (ROBOT_SIZE_SPACE/2);

	// checking to see if are bounds are inside the obstacle map

	// if going off map heading left
	if(robotCenter % ROW_SIZE < ROBOT_SIZE_SPACE / 2)
	{
		// check if heading off map north
		if(robotCenter - ROBOT_SIZE_SPACE/2*ROW_SIZE < 0)
		{
			topLeftSpace = 0;
		}
		else // room north but not west
		{
			topLeftSpace = robotCenter - ( (ROBOT_SIZE_SPACE/2*ROW_SIZE + robotCenter % ROW_SIZE));
		}

		// check if heading off map south
		if(robotCenter + ROBOT_SIZE_SPACE/2*ROW_SIZE >= BOARD_SIZE)
		{
			// bottom left space
			bottomLeftSpace = BOARD_SIZE - ROW_SIZE;
		}
		else // room south but not west
		{
			bottomLeftSpace = robotCenter + ((ROBOT_SIZE_SPACE/2)*ROW_SIZE) - robotCenter % ROW_SIZE;
		}
	}
	else	// room to the left
	{
		// check if heading off map north
		if(robotCenter - ROBOT_SIZE_SPACE/2*ROW_SIZE < 0)
		{
			// room left but not north
			topLeftSpace = robotCenter % ROW_SIZE - ROBOT_SIZE_SPACE/2;
		}

		// check if heading off map south
		if(robotCenter + ROBOT_SIZE_SPACE/2*ROW_SIZE >= BOARD_SIZE)
		{
			// room left but not south
			bottomLeftSpace = BOARD_SIZE - (ROW_SIZE - robotCenter % ROW_SIZE) - ROBOT_SIZE_SPACE/2;
		}

	}

	// if going off map heading east	
	if(robotCenter / ROW_SIZE < ( robotCenter + ROBOT_SIZE_SPACE/2) / ROW_SIZE)
	{
		// check if heading off map north
		if(robotCenter - ROBOT_SIZE_SPACE/2*ROW_SIZE < 0)
		{
			// top right space
			topRightSpace = ROW_SIZE - 1;
		}
		else	// room north but not east
		{
			topRightSpace = robotCenter - ROBOT_SIZE_SPACE/2*ROW_SIZE + (ROW_SIZE - robotCenter % ROW_SIZE - 1);
		}

		// check if heading off map south
		if(robotCenter + ROBOT_SIZE_SPACE/2*ROW_SIZE >= BOARD_SIZE)
		{
			// no room right or south so bottom right space
			bottomRightSpace = BOARD_SIZE - 1;
		}
		else // room south but not east
		{
			bottomRightSpace = robotCenter + ROBOT_SIZE_SPACE/2*ROW_SIZE + (ROW_SIZE - robotCenter % ROW_SIZE - 1);
		}

	}
	else // room to the east
	{
		// check if heading off map north
		if(robotCenter - ROBOT_SIZE_SPACE/2*ROW_SIZE < 0)
		{
			// room to the east but not to the north
			topRightSpace = robotCenter % ROW_SIZE + ROBOT_SIZE_SPACE/2;
		}

		// check if heading off map south
		if(robotCenter + ROBOT_SIZE_SPACE/2*ROW_SIZE >= BOARD_SIZE)
		{
			// room to the east but not tot he south
			bottomRightSpace = BOARD_SIZE - ROW_SIZE + robotCenter % ROW_SIZE + ROBOT_SIZE_SPACE/2;
		}

	}

	// This actually puts a big white square over the image.
	//m_gui->CoverRobot(Point(robPos.x - ((ROBOT_SIZE_SPACE/2)*PIXELS_PER_SQUARE),robPos.y - ((ROBOT_SIZE_SPACE/2)*PIXELS_PER_SQUARE)),Point(robPos.x + ((ROBOT_SIZE_SPACE/2)*PIXELS_PER_SQUARE),robPos.y + ((ROBOT_SIZE_SPACE/2)*PIXELS_PER_SQUARE)));

	// clear all of the robot spaces of obstacle marks
	for(int rowsCompleted(0); rowsCompleted < ROBOT_SIZE_SPACE; rowsCompleted++)
	{
		for(int currSpace(topLeftSpace + rowsCompleted*ROW_SIZE); currSpace <= topRightSpace + rowsCompleted*ROW_SIZE; currSpace++)
		{
			obstMap[currSpace] = false;
		}
	}

	/* DEBUG: saving the grid in ascii format to out.txt for funs */
/*	if( file.is_open() )
	{
	file << "CLEARED ROBOT\n";
		for( int i = 0; i < COL_SIZE; i++ )
		{
			for( int j = 0; j < ROW_SIZE; j++ )
			{
				file << (obstMap[i*ROW_SIZE + j] ? '`' : 'X');
			}
			file << '\n';
		}
		file << '\n';

		file.close();
	}*/
}
void A2BControl::startThreads()
{
	// getKey and all user interaction is what GUI should be handling.
	// Obviously not implemented the way we want to. We are having some thread issues,
	// since apparently OpenCV's camera cannot be in a different thread,
	// but stuff will be threaded later unless we have to do another workaround
	int key = 0;
	bool pathUpdate_start = false;
	bool connection = true;

	try
	{
		m_imageacquisition = new ImageAcquisition;

		m_plainImage = m_imageacquisition->getPlain();
		m_edgedImage = m_imageacquisition->getEdge();
		m_obstacleMap = m_imageacquisition->getObstMap();
		m_gui->drawImage( (m_showPlainImage ? m_plainImage : m_edgedImage) );
	}
	catch(int e)
	{
		//pop a message box telling the user that there is no camera connected
		//Quit out of the system.

		m_gui->showError("Camera not found. Please reconnect and try again.");
		key = 'q';
	}

	try
	{
		m_robotio = new RobotIO();//RobotIO();
		m_robotio->setControl((iControl*)this);
	}
	catch(...)
	{
		// again, show error, quit out.
		m_gui->showError("Robot connection failure. Please turn robot on, then try again. ");
		key = 'q';

		// Below is for DEBUG. Just to make the rest of it work since we often don't have robot running while deving
//		m_robotio = new DummyRobIO;

		connection = false;
	}

	if(key != 'q')
	{
		//create a thread to handle updata.
		m_updatePath = boost::thread(boost::bind(&A2BControl::update, this));
		pathUpdate_start = true;
	}

	while(key != 'q')
	{
		key = 0;	
		key = waitKey(500); // Get key input from user, poll every 500 ms


		switch(key)
		{
			// Manual move forward
		case 'f':
			if(!m_pathing->isActive())
			{
				try
				{
					m_robotio->sendCommand(RobotCommand('f', 1000));
				}
				catch(int e)
				{
					m_gui->showError("Robot connection failure. Please turn robot on, then try again. ");
				}
			}
			break;

			// Manual turn left
		case 'l':
			if(!m_pathing->isActive())
			{
				try
				{
					m_robotio->sendCommand(RobotCommand('l', 1000));
				}
				catch(int e)
				{
					m_gui->showError("Robot connection failure. Please turn robot on, then try again. ");
				}
			}
			break;

			// Manual turn right
		case 'r':
			if(!m_pathing->isActive())
			{
				try
				{
					m_robotio->sendCommand(RobotCommand('r', 1000));
				}
				catch(int e)
				{
					m_gui->showError("Robot connection failure. Please turn robot on, then try again. ");
				}
			}
			break;

			// Manual move backwards
		case 'b':
			if(!m_pathing->isActive())
			{
				try
				{
					m_robotio->sendCommand(RobotCommand('b', 1000));
				}
				catch(int e)
				{
					m_gui->showError("Robot connection failure. Please turn robot on, then try again. ");
				}
			}
			break;
			// This will connect or disconnect the port!
		case 'c':
			if(connection)
				m_robotio->closePort();
			else
				m_robotio->openPort();
			
			connection = (connection) ? false : true;
			break;

			// Test OK message box
		case 'e':
			m_gui->showError("This is a substantial error. Please regard.", MB_OK);
			break;
		
			// Test YES/NO message box
		case 'z':
			if(m_gui->showError("Would you like to continue?", MB_YESNO))
				m_gui->showError("Coolio",MB_OK);
			else
				key = 'q';
			break;

			// Toggle image
		case 't':
			m_showPlainImage = (m_showPlainImage) ? false : true;
			break;
		}
	}
	if(pathUpdate_start)
	{
		m_updatePath.interrupt();
		m_updatePath.join();
	}
}
// This will be the method that a thread will act on.
// This will, on a timer:
//		get image. if active, validate and draw path. display image.
void A2BControl::update()
{

		//for debugging only
	bool travle = true;
	bool cnt = true;
	while(1)
	{
		//get new image, edged image and obstacle array
		boost::this_thread::disable_interruption di;

		m_plainLock.lock();
		m_plainImage = m_imageacquisition->getPlain();
		m_plainLock.unlock();

		m_edgedImage = m_imageacquisition->getEdge();

		m_obstLock.lock();
		delete []m_obstacleMap;
		m_obstacleMap = m_imageacquisition->getObstMap();
		m_obstLock.unlock();

		boost::this_thread::restore_interruption ri(di);
		boost::this_thread::interruption_point();
		//if(m_pathing->isActive())
		//{
		//	//run the map over it
		//	travle = m_pathing->validatePath(m_obstacleMap);

		//	//if a obstacle happends then return false.
		//	if(!travle)
		//	{
		//		Point robotPlace(0,0);
		//		int robotSpace = 0;
		//		//the path is broken repath!
		//		//shut down the drawing of the map.
		//		m_robotio->eStop();
		//		
		//		robotPlace = ImageProcessor::findRobot(&m_plainImage, m_pathing->getRobot());
		//		robotSpace = A2BUtilities::pixelToSpaceId(robotPlace.x, robotPlace.y);
		//		
		//		cnt = m_pathing->repath(robotSpace, m_obstacleMap);
		//		m_pathing->setActive(cnt);

		//		
		//		if(!cnt)
		//		{
		//			endMission(0); //assuming 0 is a failed to path end mission
		//		}

		//	}else
		//	{
		//		if(m_showPlainImage)
		//		{
		//			m_gui->drawPath(m_pathing->getPath()->getPathPoints(), &m_plainImage);
		//			m_gui->drawImage(m_plainImage);
		//		}else
		//		{
		//			m_gui->drawPath(m_pathing->getPath()->getPathPoints(), &m_edgedImage);
		//			m_gui->drawImage(m_edgedImage);
		//		}
		//	}
		//}else
		//{\
		
		//will probably want to put a lock on this ish.
		if(!m_pathing->isActive())
		{
			m_gui->stopDrawingPath();
		}

		if(m_showPlainImage)
		{
			m_gui->drawImage(m_plainImage);
		}else
		{
			m_gui->drawImage(m_edgedImage);
		}
	}
}