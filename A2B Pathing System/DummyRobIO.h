#ifndef DUMMYROBIO_H
#define DUMMYROBIO_H

#include "Robot.h"
#include "iRobotIO.h"

#include <list>
using std::list;

class DummyRobIO : public iRobotIO
{

public:
	DummyRobIO();
	virtual ~DummyRobIO();

	bool fillQueue(Path * Pathmsg);
	void receiveMessage();
	bool receiveCommand(RobotCommand com);
	bool sendCommand(RobotCommand cmd); // later make private
	void setRobot(Robot & rob);
	void SendQueue();
	bool openPort();
	bool closePort(); 

private:
	list<RobotCommand> m_msgQueue;
	Robot * m_robot;

	int processRobotMessage(string msg);

};
#endif
