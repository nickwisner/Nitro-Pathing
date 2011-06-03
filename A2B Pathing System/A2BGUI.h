/*************************** Class: A2BGUI ****************************
* The main purpose of A2BGUI is to create a window and display
* images in it to show the user what the camera/system is seeing,
* and to let the user click inside the window to indicate where the
* robot should go.
**********************************************************************/
#ifndef A2BGUI_H
#define A2BGUI_H

#include "iControl.h"
#include "iGUI.h"

#include <string>
using std::string;



class A2BGUI : public iGUI
{

public:
	// Creates window
	A2BGUI();
	// Destroys window
	virtual ~A2BGUI();

	// set m_control
	void setControl(iControl * ctrl);
	// Displays image inside the window.
	void drawImage(Mat img);
	void setPath( const vector<Point> & path);
	
	// Called when user triggers manual abortion of the robot mission!
	void endMission();
	// Pops a message box with error. Basically, wraps WinAPI MessageBox.
	//type value corresponds to MB_OK
	int showError(const string & error, int type = 0);
	// Draws a mark overlaying the image on where the robot is thought to be.
	void markRobot(Point point);
	//Called when user indicates a destination point. Sends point to Control.
	void setDest(int x, int y);

	void stopDrawingPath();
	void stopMarkingRobot();

	//rmv later
	void CoverRobot(Point a, Point b);
private:
	iControl * m_control;	// pointer to Control, used for setDest, etc
	string m_window;		// name of the window, also used to reference window
	Mat m_view;				// the image shown in the window; deep copied from source

	// Displays the path overlaying the image in the window.
	void drawPath();

	// Used for markRobot, finds the area inside the circle to make colored.
	void getCircularROI(int R, vector < int > & RxV);

	// The callback for mouse events on window
	static void onMouse( int event, int x, int y, int, void * gui );

	void drawRobotMark();

	bool m_drawPath;
	bool m_foundRobot;
	vector<Point> m_pathPoints;
	Point m_robotCenter;
};

#endif
