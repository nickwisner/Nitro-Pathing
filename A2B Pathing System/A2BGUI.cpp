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

// for constants such as CAMERA_ROWSIZE
#include "A2BUtilities.h"

#include "RobotIO.h"


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

A2BGUI::A2BGUI() : m_control(0), m_view(CAMERA_COL_SIZE, CAMERA_ROW_SIZE,CV_64FC3,Scalar(0,0,0))
{
	m_window = APPLICATION_NAME;
	namedWindow(m_window, CV_WINDOW_KEEPRATIO);

	setMouseCallback( m_window, onMouse, this );
}

A2BGUI::~A2BGUI()
{
	cvDestroyAllWindows();
}

void A2BGUI::setControl(iControl * ctrl)
{
	m_control = ctrl;
}

void A2BGUI::drawImage(Mat img)
{
	m_view.release();
	m_view = img.clone();
	
	imshow(m_window, m_view);
}


void A2BGUI::drawPath(const vector<Point> & path, Mat * view)
{
	for(int i = 1; i < path.size();i++)
	{
		line(*view, path[i-1], path[i], Scalar(25,83,255),2,7);
	}
}


void A2BGUI::endMission()
{
}

int A2BGUI::showError(const string & error, int type)
{
	return MessageBox(0, LPCSTR(error.c_str()), LPCSTR("A2B Pathing System Error"), type);
}

void A2BGUI::markRobot(Point c)
{
	int R = 10;
	vector<int> RxV;
	getCircularROI(R, RxV);

	Mat_<Vec3b>& img = (Mat_<Vec3b>&)m_view; //3 channel pointer to image
    
	for( int dy = -R; dy <= R; dy++ )
	{
		int Rx = RxV[abs(dy)];
		for( int dx = -Rx; dx <= Rx; dx++ )
			img(c.y+dy, c.x+dx)[1] = 255;
	}
	
	drawImage(m_view);
	waitKey(1000);
}

void A2BGUI::getCircularROI(int R, vector < int > & RxV)
{
    RxV.resize(R+1);
    for( int y = 0; y <= R; y++ )
        RxV[y] = cvRound(sqrt((double)R*R - y*y));
}


void A2BGUI::setDest(int x, int y)
{
	m_control->setDestination(Point(x,y));
}