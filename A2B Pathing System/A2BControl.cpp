///////////////////////////////////////////////////////////
//  A2BControl.cpp
//  Implementation of the Class A2BControl
//  Created on:      18-Apr-2011 7:33:31 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#include "A2BControl.h"

#include "RobotIO.h"

A2BControl::A2BControl() : m_robotio(0), m_imageacquisition(0), m_showPlainImage(true)
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
void A2BControl::endMission(int error)
{
	m_robotio->endMission();	
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

void A2BControl::sendCommand(RobotCommand r)
{
	if(r.getCode() == 'z')
	{
		m_robotio->sendPriorityCommand(r);
	}else if(r.getCode() == 'a')
	{
		m_robotio->sendPriorityCommand(r);
	}else
	{
		m_robotio->sendCommand(r);
	}
}


bool A2BControl::setDestination(Point dest)
{
	bool pathMade = true;
	Point robPos;
	bool robCheck = true;
	int n = -1;
	int spaceStart = 0;

	boost::this_thread::disable_interruption di;
	//change the first part setDestinatoin to be "findRobot"
	do
	{
		n++;
		//getImage();
		if(m_obstacleMap != 0)
			delete [] m_obstacleMap;


		m_obstacleMap = m_imageacquisition->getObstMap();
		m_edgedImage = m_imageacquisition->getEdge();
		m_plainImage = m_imageacquisition->getPlain();

		robPos = ImageProcessor::findRobot((&m_plainImage), m_pathing->getRobot());

		spaceStart = A2BUtilities::pixelToSpaceId(robPos.x, robPos.y);
		
		clearRobot(spaceStart, m_obstacleMap, robPos);
		
		m_gui->markRobot(robPos);

		if(n < 5)
			robCheck = !m_gui->showError("Is this the robot?",MB_YESNO);
		else
			return false;
	} // keep looping if they answer no
	while( robCheck );
	
	boost::this_thread::restore_interruption ri(di);

	if( !m_pathing->makePath(dest, spaceStart, m_obstacleMap) )
	{
		m_gui->showError("Cannot create a path to indicated destination.",MB_OK);
		pathMade = false;
	}
	else
	{
		m_robotio->fillQueue(m_pathing->getPath());
	}
	return pathMade;
}

void A2BControl::clearRobot(int robotCenter, bool * obstMap, Point robPos)
{
	//this is assuming that the robot is 11.25 cells long and wide. We will around it to 12 cells.
	//this is also assuming that the int passed in is the center cell of the robot.

	int topLeftSpace = (robotCenter - (9*ROW_SIZE)) - 9;
	int topRightSpace = (robotCenter - (9*ROW_SIZE)) + 9;
	int bottomRightSpace = (robotCenter + (9*ROW_SIZE)) + 9;
	int bottomLeftSpace = (robotCenter + (9*ROW_SIZE)) - 9;

	// This actually puts a big white square over the image.
	//m_gui->CoverRobot(Point(robPos.x - ROBOT_PX_X/2,robPos.y - ROBOT_PX_Y/2),Point(robPos.x + ROBOT_PX_X/2,robPos.y + ROBOT_PX_Y/2));


	for(int i = topRightSpace; i <= bottomRightSpace;)
	{
		for(int x = topLeftSpace; x <= topRightSpace; x++)
		{
			obstMap[x] = false;
			//the true is to set the space to not be a obstacle!
		}
		i += ROW_SIZE;
		//changing these should be fine BECAUSE i = topRightSpace only at the start.
		topLeftSpace += ROW_SIZE;
		topRightSpace += ROW_SIZE;
	}

	/* DEBUG: saving the grid in ascii format to out.txt for funs */
	/*std::ofstream file("out.txt", std::ios::app);
	if( file.is_open() )
	{
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
void A2BControl::startThreads() //change name!
{
	// getKey and all user interaction is what GUI should be handling.
	// Obviously not implemented the way we want to. We are having some thread issues,
	// since apparently OpenCV's camera cannot be in a different thread,
	// but stuff will be threaded later unless we have to do another workaround
	int key = 0;
	
	bool connection = true;

	try
	{
		m_imageacquisition = new ImageAcquisition;

		m_plainImage = m_imageacquisition->getPlain();
		m_edgedImage = m_imageacquisition->getEdge();

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
		m_robotio = new RobotIO;
	}
	catch(...)
	{
		// again, show error, quit out.
		m_gui->showError("Robot connection failure. Please turn robot on, then try again. ");
		key = 'q';

		connection = false;
	}

	//create a thread to handle updata.
	m_updatePath = boost::thread(boost::bind(&A2BControl::update, this));

	while(key != 'q')
	{
		key = 0;
		key = waitKey(500); // Get key input from user, poll every 500 ms

		switch(key)
		{
		case 's':
			if(m_pathing->isActive())
			{
				//this should also empty the queue and stop the mission probably
				m_robotio->eStop();
			}
			// Manual move forward
		/*case 'f':
			if(!m_pathing->isActive())
			{
				try
				{
					boost::this_thread::disable_interruption di;
					sendCommand(RobotCommand('z', 0));
					waitKey(10);
					sendCommand(RobotCommand('f', 1000));
					waitKey(10000);
					sendCommand(RobotCommand('a', 0));
					boost::this_thread::restore_interruption ri(di);
				}
				catch(int e)
				{
					m_gui->showError("Robot connection failure. Please turn robot on, then try again. ");
				}
			}
			break;

		//	// Manual turn left
		case 'l':
			if(!m_pathing->isActive())
			{
				try
				{
					boost::this_thread::disable_interruption di;
					sendCommand(RobotCommand('z', 0));
					waitKey(10);
					sendCommand(RobotCommand('l', 1000));
					waitKey(10000);
					sendCommand(RobotCommand('a', 0));
					boost::this_thread::restore_interruption ri(di);
				}
				catch(int e)
				{
					m_gui->showError("Robot connection failure. Please turn robot on, then try again. ");
				}
			}
			break;

		//	// Manual turn right
		case 'r':
			if(!m_pathing->isActive())
			{
				try
				{
					boost::this_thread::disable_interruption di;
					sendCommand(RobotCommand('z', 0));
					waitKey(10);
					sendCommand(RobotCommand('r', 1000));
					waitKey(10000);
					sendCommand(RobotCommand('a', 0));
					boost::this_thread::restore_interruption ri(di);
				}
				catch(int e)
				{
					m_gui->showError("Robot connection failure. Please turn robot on, then try again. ");
				}
			}
			break;

		//	// Manual move backwards
		case 'b':
			if(!m_pathing->isActive())
			{
				try
				{
					boost::this_thread::disable_interruption di;
					sendCommand(RobotCommand('z', 0));
					waitKey(10);
					sendCommand(RobotCommand('b', 10000));
					waitKey(10000);
					sendCommand(RobotCommand('a', 0));
					boost::this_thread::restore_interruption ri(di);
				}
				catch(int e)
				{
					m_gui->showError("Robot connection failure. Please turn robot on, then try again. ");
				}
			}
			break;*/

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
		m_edgedImage = m_imageacquisition->getEdge();
		m_plainImage = m_imageacquisition->getPlain();
		m_obstacleMap = m_imageacquisition->getObstMap();
		boost::this_thread::restore_interruption ri(di);

		if(m_pathing->isActive())
		{
			//run the map over it
			travle = m_pathing->validatePath(m_obstacleMap);

			//if a obstacle happends then return false.
			if(!travle)
			{
				Point robotPlace(0,0);
				int robotSpace = 0;
				//the path is broken repath!
				//shut down the drawing of the map.
				m_robotio->eStop();
				
				robotPlace = ImageProcessor::findRobot(&m_plainImage, m_pathing->getRobot());
				robotSpace = A2BUtilities::pixelToSpaceId(robotPlace.x, robotPlace.y);
				
				cnt = m_pathing->repath(robotSpace, m_obstacleMap);
				m_pathing->setActive(cnt);

				
				if(!cnt)
				{
					endMission(0); //assuming 0 is a failed to path end mission
				}

			}else
			{
				if(m_showPlainImage)
				{
					m_gui->drawPath(m_pathing->getPath()->getPathPoints(), &m_plainImage);
					m_gui->drawImage(m_plainImage);
				}else
				{
					m_gui->drawPath(m_pathing->getPath()->getPathPoints(), &m_edgedImage);
					m_gui->drawImage(m_edgedImage);
				}
			}
		}else
		{
			if(m_showPlainImage)
			{
				m_gui->drawImage(m_plainImage);
			}else
			{
				m_gui->drawImage(m_edgedImage);
			}
		}
	}
}