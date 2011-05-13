///////////////////////////////////////////////////////////
//  iControl.h
//  Implementation of the Interface iControl
//  Created on:      17-Apr-2011 5:23:44 PM
//  Original author: nagisa.day
///////////////////////////////////////////////////////////

#ifndef ICONTROL_H
#define ICONTROL_H

#include <opencv2/imgproc/imgproc.hpp>
using cv::Point;

class iControl
{

public:
	iControl() {

	}

	virtual ~iControl() {

	}

	virtual bool endMission(int missionid) =0;
	virtual void endThreads() =0;
	virtual bool setDestination(Point dest) =0;
	virtual void startThreads() =0;
	virtual bool update() =0;
	virtual bool checkSavedQueries() = 0;
	virtual void saveQueriesToFile() = 0;
	virtual void clearRobot(int space, bool * obstMap, Point robPos) = 0;

};
#endif
