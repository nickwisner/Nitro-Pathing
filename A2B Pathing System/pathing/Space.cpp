#include "Space.h"

// FIX CITY COMMENTS TO SPACE COMMENTS

/*************************************************************************
*
*		Constructors
*
*************************************************************************/
Space::Space()
{
}

Space::Space(int id, bool obstacle): m_id(id), m_obstacle(obstacle)
{
}

Space::~Space()
{
}

Space::Space(const Space &copy): m_id(copy.m_id), m_obstacle(copy.m_obstacle)
{
}

Space& Space::operator =(const Space &rhs)
{
	if(this != &rhs)
	{
		m_id = rhs.m_id;
	}

	return *this;
}
/*************************************************************************
*		End Constructors
*************************************************************************/

/*************************************************************************
*
*	Purpose:		Compares the names of the two cities.
*	Entry:			Requires a city to be passed in.
*	Exit:			Returns bool true if they are the same.
*
*************************************************************************/
bool Space::operator ==(const Space &rhs)
{
	bool rc = (m_id == rhs.m_id);
	return rc;
}

/*************************************************************************
*
*	Purpose:		Compares the names of the two cities.
*	Entry:			Requires a city to be passed in.
*	Exit:			Returns bool true if they are not the same.
*
*************************************************************************/
bool Space::operator!=(const Space &rhs)
{
	return (m_id != rhs.m_id);
}

/*************************************************************************
*
*	Purpose:		Returns the m_id of the city.
*	Entry:			Nothing.
*	Exit:			Returns a int of the m_id.
*
*************************************************************************/
int Space::GetId()
{
	return m_id;
}

/*************************************************************************
*
*	Purpose:		Sets the m_id of the city.
*	Entry:			String m_id to set the city m_id to.
*	Exit:			Returns nothing.
*
*************************************************************************/
void Space::SetId(int id)
{
	m_id = id;
}

bool Space::IsObstacle(void)
{
	return m_obstacle;
}

void Space::SetObstacle(bool obstacle)
{
	m_obstacle = obstacle;
}