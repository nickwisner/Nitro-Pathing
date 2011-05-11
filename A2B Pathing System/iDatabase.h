///////////////////////////////////////////////////////////
//  iDatabase.h
//  Implementation of the Interface iDatabase
//  Created on:      17-Apr-2011 5:25:23 PM
//  Original author: nagisa.day
///////////////////////////////////////////////////////////

#ifndef iDATABASE_H
#define DATABASE_H

#include <opencv2/imgproc/imgproc.hpp>
using cv::Point;

#include "Robot.h"
#include <string>
using std::string;
#include "ErrorLog.h"

class iDatabase
{

public:
	virtual ~iDatabase() {

	}
	virtual bool endMission(Point end) =0;
	virtual void error(ErrorLog err) =0;
	virtual Robot getRobot() =0;
	virtual int startMission(Point start, Point dest) =0;
	virtual void update(string query) =0;

};
#endif 
