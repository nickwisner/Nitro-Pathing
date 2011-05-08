///////////////////////////////////////////////////////////
//  iGUI.h
//  Implementation of the Interface iGUI
//  Created on:      12-Apr-2011 4:56:35 AM
//  Original author: nagisa.day
///////////////////////////////////////////////////////////

#if !defined(EA_D23F979E_9CF4_4917_B058_F363BBC68D7E__INCLUDED_)
#define EA_D23F979E_9CF4_4917_B058_F363BBC68D7E__INCLUDED_

#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

#include "iControl.h"

#include <vector>
using std::vector;

#include <string>
using std::string;

extern int const BOX_OK;
extern int const BOX_YESNO;

class iGUI
{

public:
	iGUI() {

	}

	virtual ~iGUI() {

	}

	virtual void setControl(iControl * ctrl) = 0;
	virtual void drawImage(Mat image) =0;
	virtual void drawPath(const vector<Point> & Path, Mat * view) =0;
	virtual void endMission() =0;
	virtual void markRobot(Point point) =0;
	virtual void setDest(int x, int y) =0;
	virtual int showError(const string & error, int type = BOX_OK) =0;
	virtual bool toggleImage() =0;
	virtual void CoverRobot(Point topLeft, Point bottomRight) = 0;

};
#endif // !defined(EA_D23F979E_9CF4_4917_B058_F363BBC68D7E__INCLUDED_)
