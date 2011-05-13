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

#include "A2BUtilities.h"

#include "RobotIO.h"
// not part of the class because onMouse needs to be not a member, or static
// but if it's static, can't call other member functions
void A2BGUI::onMouse( int event, int x, int y, int, void * gui )
{
	switch( event )
    {
		// click on pic, set destination.
    case CV_EVENT_LBUTTONDOWN:
		reinterpret_cast<iGUI*>(gui)->setDest(x,y);
        break;

		// temporarily, this? right click sends command?
	case CV_EVENT_RBUTTONDOWN:
		// send appropriate command
//		toggleImage();
		waitKey(1000); // if sending a command makes robot move for 1 second.
		break;
    }
}

A2BGUI::A2BGUI() : m_control(0), m_showEdged(false), m_view(CAMERA_COL_SIZE, CAMERA_ROW_SIZE,CV_64FC3,Scalar(0,0,0))
{
	m_window = "A2B Pathing System";
	namedWindow(m_window, CV_WINDOW_KEEPRATIO);
	//m_view = imread("640edged.jpg");

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

// We had a A2BMessageBox before which is why we have tests for it in Control
// WinAPI MessageBox >>>> rolling your ugly own
// This returns 1 (true) if Yes button clicked. 0 (false) if No. 0 if it was just an OK box.
int A2BGUI::showError(const string & error, int type)
{
	int response = MessageBox(0, LPCSTR(error.c_str()), LPCSTR("A2B Pathing System Error"), type);
	return (response == IDYES ? 1 : 0);
}

void A2BGUI::markRobot(Point c)
{
	//Point center(c.x,c.y);
	//cv::circle(m_view, Point(10,10), 5, Scalar(100,10,255),10);
//	cv::circle(m_view, Point(c.x,c.y), 5, Scalar(0,0,255));
	//cv::circle(&m_view, Point(c.x,c.y), 5, CV_RGB(255,255,0), 2);

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