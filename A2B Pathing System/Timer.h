///////////////////////////////////////////////////////////
//  Timer.h
//  Implementation of the Class Timer
//  Created on:      17-Apr-2011 5:15:22 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#if !defined(EA_BF39D67E_F19D_4988_BB6A_B2E009FBE7C1__INCLUDED_)
#define EA_BF39D67E_F19D_4988_BB6A_B2E009FBE7C1__INCLUDED_

class Timer
{

public:
	Timer();
	virtual ~Timer();

	void onTick();
	void reset();

private:
	void *(m_action)();
	int m_millisecs;

};
#endif // !defined(EA_BF39D67E_F19D_4988_BB6A_B2E009FBE7C1__INCLUDED_)
