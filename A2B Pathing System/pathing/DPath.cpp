#include "DPath.h"

/*************************************************************************
*
*		Constructors
*
*************************************************************************/
DPath::DPath(): m_id(0)
{
}

DPath::DPath(int id): m_id(id)
{
}

DPath::~DPath()
{
}

DPath::DPath(const DPath &copy): m_id(copy.m_id)
{
}

DPath& DPath::operator =(const DPath &rhs)
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
*	Purpose:		Compares the names of the two highways.
*	Entry:			Requires a DPath to be passed in.
*	Exit:			Returns bool true if they are the same.
*
*************************************************************************/
bool DPath::operator ==(const DPath &rhs)
{
	bool rc = (m_id == rhs.m_id);
	return rc;
}

/*************************************************************************
*
*	Purpose:		Compares the names of the two highways.
*	Entry:			Requires a DPath to be passed in.
*	Exit:			Returns bool true if they are not the same.
*
*************************************************************************/
bool DPath::operator!=(const DPath &rhs)
{
	return (m_id != rhs.m_id);
}

/*************************************************************************
*
*	Purpose:		Returns the name of the DPath.
*	Entry:			Nothing.
*	Exit:			Returns a string of the name.
*
*************************************************************************/
int DPath::GetId()
{
	return m_id;
}

/*************************************************************************
*
*	Purpose:		Sets the name of the DPath.
*	Entry:			String name to set the DPath name to.
*	Exit:			Returns nothing.
*
*************************************************************************/
void DPath::SetId(int id)
{
	m_id = id;
}