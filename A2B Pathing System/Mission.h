///////////////////////////////////////////////////////////
//  Mission.h
//  Implementation of the Class Mission
//  Created on:      17-Apr-2011 5:25:13 PM
//  Original author: nagisa.day
///////////////////////////////////////////////////////////

#if !defined(EA_DD0DCADA_7B13_484e_AA28_BAAF28277D53__INCLUDED_)
#define EA_DD0DCADA_7B13_484e_AA28_BAAF28277D53__INCLUDED_

#include <opencv2/imgproc/imgproc.hpp>
using cv::Point;

class Mission
{

public:
	Mission();
	virtual ~Mission();

	int getID();
	bool setEndPoint(Point endPoint);

private:
	bool m_active;
	Point m_end;
	int m_endTime;
	int m_ID;
	int m_robotID;
	Point m_selected;
	Point m_start;
	int m_startTime;

};
#endif // !defined(EA_DD0DCADA_7B13_484e_AA28_BAAF28277D53__INCLUDED_)
