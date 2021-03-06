///////////////////////////////////////////////////////////
//  iPathing.h
//  Implementation of the Interface iPathing
//  Created on:      27-Apr-2011 7:08:12 PM
//  Original author: nagisa.day
///////////////////////////////////////////////////////////

#if !defined(EA_5BBF50E8_6523_4062_9757_3EA4DDC611B0__INCLUDED_)
#define EA_5BBF50E8_6523_4062_9757_3EA4DDC611B0__INCLUDED_

/**
 * This interface is the abstract base class that Pathing inherits from
 */
class iPathing
{

public:
	iPathing() {

	}

	virtual ~iPathing() {

	}

	virtual bool deletePath() = 0;
	virtual bool makePath( int destSpace, int startSpace, bool * obstMap) = 0;
	virtual Path * getPath() =0;
	virtual bool isActive() =0;
	virtual bool repath() =0;
	virtual bool validatePath() =0;
	virtual Point getRobotPosition() =0;
	virtual bool setRobot( Robot & domoarigato) = 0;
	virtual	Robot * getRobot() = 0;
	virtual int getHeading() = 0;
	virtual void stopPath() = 0;

private:
	//virtual void translateToPath( vector<int> path) = 0;
};
#endif // !defined(EA_FECC720C_4C4F_43ca_A3DA_E4888F8279E3__INCLUDED_)
