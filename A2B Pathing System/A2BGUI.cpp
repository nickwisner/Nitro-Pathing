///////////////////////////////////////////////////////////
//  A2BGUI.cpp
//  Implementation of the Class A2BGUI
//  Created on:      16-Apr-2011 4:18:53 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#include "A2BGUI.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

#include <string>
using std::string;
#include <vector>
using std::vector;

// for constants such as CAMERA_ROWSIZE
#include "A2BUtilities.h"

#include "RobotIO.h"


#define WIN32_LEAN_AND_MEAN
// for MessageBox
#include <Windows.h>


/************************** A2BGUI::onMouse ***************************
* The callback function for the window for A2BGUI.
* 
* This is a private static function. This needs to be static
* because it is a callback function, and since static functions
* cannot reference nonstatic members, it takes a pointer to itself
* in the last parameter which needs to be reinterpret_cast'ed from
* a void*. It works.
* 
* This currently only takes a left button click. That calls GUI's
* setDest at cursor x,y.
**********************************************************************/
void A2BGUI::onMouse( int event, int x, int y, int, void * gui )
{
	switch( event )
    {
    case CV_EVENT_LBUTTONDOWN: // click on pic, set destination.

		reinterpret_cast<iGUI*>(gui)->setDest(x,y);
        break;
    }
}

/************************** A2BGUI::A2BGUI() **************************
* The constructor. This initializes m_control to 0, and m_view to a
* size, channel type, and color. m_view is initialized this way so
* that if there are some sort of issues with getting an image from
* the camera, m_view still has a set size and can be displayed in
* the window without size weirdness. It should not even happen but
* just to be safe.
* 
* Here the window is created using OpenCV's highgui. The window is
* referenced by the title, m_window. The callback for the mouse
* over this window is set to the static method, onMouse.
**********************************************************************/
A2BGUI::A2BGUI() : m_control(0), m_view(CAMERA_COL_SIZE, CAMERA_ROW_SIZE,CV_64FC3,Scalar(0,0,0)), m_drawPath(false), m_foundRobot(false)
{
	m_window = APPLICATION_NAME;
	namedWindow(m_window);
	drawImage(m_view);
	setMouseCallback( m_window, onMouse, this );
}

// Our window is destroyed here.
// Mat's destructor automatically calls .release() so m_view is good to go
A2BGUI::~A2BGUI()
{
	cvDestroyAllWindows();
}

// Set control pointer.
void A2BGUI::setControl(iControl * ctrl)
{
	m_control = ctrl;
}

// Displays image in window
// ***** Perhaps it would work better with drawPath and markRobot if we
// split this into maybe setImage(Mat) and refresh(). Change later? *****
void A2BGUI::drawImage(Mat img)
{
	m_view.release();	// for every clone, should call release()
	m_view = img.clone();

	if(m_drawPath)
	{
		drawPath();
	}
	else if(m_foundRobot)
	{
		drawRobotMark();
	}
	imshow(m_window, m_view);
}

/************************** A2BGUI::drawPath **************************
* Takes a path, which is a vector of points. You would get this
* from the Path object's getPathPoints.
* Takes a Mat *, the image to draw to. Presumably you would call
* this method right before calling drawImage to display the same
* Mat to the window. This might be changed if drawImage is split.
* If we drawImage before and after drawing the path, there will be
* flicker.
* 
* Since path is a vector of points, this will "connect the dots"
* with lines. The Scalar is the color; should probably make that a
* const up at the top somewhere for easy changing.
**********************************************************************/
void A2BGUI::setPath(const vector<Point> & path)
{
	if(m_pathPoints.empty())
	{
		m_pathPoints = path;
	}
	else
	{
		m_pathPoints.clear();
		m_pathPoints = path;
	}
	m_drawPath = true;
}

void A2BGUI::drawPath()
{
	for(int i = 1; i < m_pathPoints.size(); i++)
	{
		line(m_view, m_pathPoints[i-1], m_pathPoints[i], Scalar(25,83,255),2,7);
	}
}

// Not sure if we'll even use this. But it talks to m_database, saying
// hey we're done, you can save off the mission to the DB now.
void A2BGUI::endMission()
{
	// Not implemented yet
}

// This returns 1 (true) if Yes button clicked. 0 (false) if No. 0 if it was just an OK box.
int A2BGUI::showError(const string & error, int type)
{
	int response = MessageBox(0, LPCSTR(error.c_str()), LPCSTR("A2B Pathing System Error"), type);
	return (response == IDYES ? 1 : 0);
}

// Puts a circle on Point c where the robot is thought to be.
void A2BGUI::markRobot(Point c)
{
	m_foundRobot = true;
	m_robotCenter = c;
}

void A2BGUI::drawRobotMark()
{
	int R = 10;
	vector<int> RxV;
	getCircularROI(R, RxV); // define circle

	Mat_<Vec3b>& img = (Mat_<Vec3b>&)m_view; //3 channel pointer to image
    
	for( int dy = -R; dy <= R; dy++ )
	{
		int Rx = RxV[abs(dy)];
		for( int dx = -Rx; dx <= Rx; dx++ )
			img(m_robotCenter.y+dy, m_robotCenter.x+dx)[1] = 255;	// set this coloring in that pixel
	}
}

// Define the circle. RxV is a vector of ints where the width (x) of the circle from the origin
// is saved off per [y]. This is taken from OpenCV's site.
void A2BGUI::getCircularROI(int R, vector < int > & RxV)
{
    RxV.resize(R+1);
    for( int y = 0; y <= R; y++ )
        RxV[y] = cvRound(sqrt((double)R*R - y*y));
}

// Sets the destination point, starts the pathing madness
void A2BGUI::setDest(int x, int y)
{
	m_control->setDestination(Point(x,y));
}

// not used
void A2BGUI::CoverRobot(Point a, Point b)
{
	cv::rectangle(m_view, a, b, Scalar(100,100,100),1,0);
	drawImage(m_view);	// refresh
	waitKey(100);
}

void A2BGUI::stopDrawingPath()
{
	m_drawPath = false;
}

void A2BGUI::stopMarkingRobot()
{
	m_foundRobot = false;
}