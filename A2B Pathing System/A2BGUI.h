///////////////////////////////////////////////////////////
//  A2BGUI.h
//  Implementation of the Class A2BGUI
//  Created on:      16-Apr-2011 4:18:50 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#ifndef A2BGUI_H
#define A2BGUI_H

#include "iControl.h"
#include "iGUI.h"

#include <Windows.h>

#include <string>
using std::string;

//void onMouse( int event, int x, int y, int, void * gui );

class A2BGUI : public iGUI
{
	friend class A2BMessageBox;

public:
	A2BGUI();
	virtual ~A2BGUI();

	void setControl(iControl * ctrl);
	void drawImage(Mat img);
	void drawPath(const vector<Point> & path, Mat * view);
	void endMission();
	int showError(const string & error, int type = BOX_OK);
	void markRobot(Point point);


	void setDest(int x, int y);
private:
	iControl * m_control;
	string m_window;
	bool m_showEdged;
	Mat m_view;

	//Test functoins
	void getCircularROI(int R, vector < int > & RxV);

	static void onMouse( int event, int x, int y, int, void * gui );

};

#endif
