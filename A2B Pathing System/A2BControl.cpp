///////////////////////////////////////////////////////////
//  A2BControl.cpp
//  Implementation of the Class A2BControl
//  Created on:      18-Apr-2011 7:33:31 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#include "A2BControl.h"

A2BControl::A2BControl() :m_plainImage(0),m_edgedImage(0),m_tUpdatePath(0), m_robotio(0), m_imageacquisition(0), m_showPlainImage(true)
{
	m_gui = new A2BGUI;
	m_gui->setControl(this);
	m_obstacleMap = new bool[ROW_SIZE * COL_SIZE];
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

bool A2BControl::checkSavedQueries()
{
	return false;
}


void A2BControl::edgeImage()
{
}


/**
 * error = 0 if reach destination. Use this to end a mission whatever the reason;
 * updates database, etc
 */
bool A2BControl::endMission(int error)
{
	return false;
}


void A2BControl::endThreads()
{
}


Image * A2BControl::getEdgedImage()
{
	return m_edgedImage;
}


bool A2BControl::runPath()
{
	return false;
}


void A2BControl::saveQueriesToFile()
{
}


bool A2BControl::sendCommand()
{
	return false;
}


bool A2BControl::setDestination(Point dest)
{
	Point robPos;
	bool robCheck = true;
	int n = -1;
	int spaceStart = 0;
	int spaceDest = 0;

	//change the first part setDestinatoin to be "findRobot"
	do
	{
		n++;
		getImage();
		m_gui->drawImage( (m_showPlainImage ? m_plainImage->mat() : m_edgedImage->mat()) );
	
		robPos = ImageProcessor::findRobot(&(m_plainImage->mat()), m_pathing->getRobot());
		spaceStart = A2BUtilities::pixelToSpaceId(robPos.x, robPos.y);
		spaceDest = A2BUtilities::pixelToSpaceId( dest.x,dest.y);
		clearRobot(spaceStart, m_obstacleMap, robPos);
		m_gui->markRobot(robPos);

		if(n < 5)
			robCheck = !m_gui->showError("Is this the robot?",BOX_YESNO);
		else
			return false;
	}						 // keep looping if they answer no
	while( robCheck );

	if( !m_pathing->makePath(spaceDest, spaceStart, m_obstacleMap) )
	{
		m_gui->showError("Cannot create a path to indicated destination.",BOX_OK);
	}
	else
	{
		m_robotio->fillQueue(m_pathing->getPath());

		// this is only for the alpha release... will be replaced by startmission message being sent
		try
		{
			m_robotio->SendQueue();
		}catch(int e)
		{
			m_gui->showError("Robot connection failure. Please turn robot on, then try again. ");
		}
	}
	return true;
}

#include <fstream>
void A2BControl::clearRobot(int robotCenter, bool * obstMap, Point robPos)
{
	//this is assuming that the robot is 11.25 cells long and wide. We will around it to 12 cells.
	//this is also assuming that the int passed in is the center cell of the robot.

	int topLeftSpace = (robotCenter - (9*ROW_SIZE)) - 9;
	int topRightSpace = (robotCenter - (9*ROW_SIZE)) + 9;
	int bottomRightSpace = (robotCenter + (9*ROW_SIZE)) + 9;
	int bottomLeftSpace = (robotCenter + (9*ROW_SIZE)) - 9;

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
	std::ofstream file("out.txt", std::ios::app);
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
	}
}
void A2BControl::startThreads()
{

	int key = 0;
	// getKey stuff is what GUI should be handling; put in thread later
	bool connection = true;

	try
	{
		m_imageacquisition = new ImageAcquisition;

		getImage();

		m_gui->drawImage( (m_showPlainImage ? m_plainImage->mat() : m_edgedImage->mat()) );

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
		m_gui->showError("Robot connection failure. Please turn robot on, then try again. ");
		key = 'q';
		connection = false;
	}

	// Number of cycles to send to robot for manual move demo
	int cycles = 2;

	while(key != 'q')
	{
		getImage();
		if(m_pathing->isActive())
		{
			m_gui->drawPath(m_pathing->getPath()->getPathPoints(), &m_plainImage->mat());
		}
		m_gui->drawImage( (m_showPlainImage ? m_plainImage->mat() : m_edgedImage->mat()) );
		
		key = waitKey(500);

		switch(key)
		{
		case 'f':
			try
			{
				m_robotio->sendCommand(RobotCommand('f', cycles));
			}
			catch(int e)
			{
				m_gui->showError("Robot connection failure. Please turn robot on, then try again. ");
			}
			break;
		case 'l':
			try
			{
				m_robotio->sendCommand(RobotCommand('l', cycles));
			}
			catch(int e)
			{
				m_gui->showError("Robot connection failure. Please turn robot on, then try again. ");
			}
			break;
		case 'r':
			try
			{
				m_robotio->sendCommand(RobotCommand('r', cycles));
			}
			catch(int e)
			{
				m_gui->showError("Robot connection failure. Please turn robot on, then try again. ");
			}
			break;
		case 'b':
			try
			{
				m_robotio->sendCommand(RobotCommand('b', cycles));
			}
			catch(int e)
			{
				m_gui->showError("Robot connection failure. Please turn robot on, then try again. ");
			}
			break;
		case 'i':
			createTestVector();
			break;
		case 'o':
			makeTestVector2();
			break;
		case 'p':
			makeTestVector3();
			break;
		case 'c':
			//this will connect or disconnect the port!
			if(connection)
				m_robotio->closePort();
			else
				m_robotio->openPort();
			
			connection = (connection) ? false : true;
			break;
		case 'e':
			m_gui->showError("This is a substantial error. Please regard.", BOX_OK);
			break;
		
		case 'z':
			if(m_gui->showError("Would you like to continue?", BOX_YESNO))
				m_gui->showError("Coolio",BOX_OK);
			else
				key = 'q';
			break;

		case 't':
			m_showPlainImage = (m_showPlainImage) ? false : true;
			break;
		}
	}
}


bool A2BControl::update()
{
	return false;
}

void A2BControl::getImage()
{
	// getImage news the image, but it also deletes its current image which is same address as m_plainImage here
	m_plainImage = m_imageacquisition->getImage();
	
	delete m_edgedImage; // createEdgedImage news the image but has no image to delete so we do it here
	m_edgedImage = ImageProcessor::createEdgedImage(m_plainImage);

	ImageProcessor::mapObstacles(*m_edgedImage, m_obstacleMap);
//	ImageProcessor::makeImageBorder(&(m_plainImage->mat()));
}
