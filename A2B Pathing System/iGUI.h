/************************** Interface: iGUI ***************************
* Defines an interface for the GUI of this application, A2BGUI.
* 
* setControl: Sets pointer to Control, since GUI depends on
*	Control.
* drawImage: Displays image inside the window.
* drawPath: Displays the path overlaying the image in the window.
* endMission: Called when user triggers manual abortion of the
*	robot mission!
* markRobot: Draws a mark overlaying the image on where the robot
*	is thought to be.
* setDest: Called when user indicates a destination point. Sends
*	point to Control.
* showError: Pops a message box with error. Basically, wraps WinAPI
*	MessageBox.
**********************************************************************/
#ifndef IGUI_H
#define IGUI_H

#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

#include "iControl.h"

#include <vector>
using std::vector;

#include <string>
using std::string;

class iGUI
{

public:
	iGUI() {

	}

	virtual ~iGUI() {

	}

	virtual void setControl(iControl * ctrl) = 0;
	virtual void drawImage(Mat image) =0;
	virtual void setPath( const vector<Point> & path) =0;
	virtual void endMission() =0;
	virtual void markRobot(Point point) =0;
	virtual void setDest(int x, int y) =0;
	//type value corresponds to MB_OK
	virtual int showError(const string & error, int type = 0) =0;
	virtual void stopDrawingPath() = 0;
	virtual void stopMarkingRobot() = 0;
	//rmv later
	virtual void CoverRobot(Point a, Point b) = 0;

};
#endif
