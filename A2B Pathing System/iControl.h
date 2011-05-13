///////////////////////////////////////////////////////////
//  iControl.h
//  Implementation of the Interface iControl
//  Created on:      17-Apr-2011 5:23:44 PM
//  Original author: nagisa.day
///////////////////////////////////////////////////////////

#if !defined(EA_388686E3_240C_45dc_A048_14103D41A076__INCLUDED_)
#define EA_388686E3_240C_45dc_A048_14103D41A076__INCLUDED_

#include "A2BDatabase.h"

class iControl
{

public:
	virtual ~iControl() {

	}

	virtual Mat * getEdgedImage() = 0;
	virtual bool endMission(int missionid) = 0;
	virtual void endThreads() =0;
	virtual void getImage() =0;
	virtual bool sendCommand() =0;
	virtual bool setDestination(Point dest) =0;
	virtual void startThreads() =0;
	virtual bool update() =0;
	virtual bool checkSavedQueries() = 0;
	virtual void saveQueriesToFile() = 0;
	virtual void clearRobot(int space, bool * obstMap, Point robPos) = 0;

};
#endif // !defined(EA_388686E3_240C_45dc_A048_14103D41A076__INCLUDED_)
