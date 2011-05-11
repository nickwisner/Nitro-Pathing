///////////////////////////////////////////////////////////
//  ImageAcquisition.cpp
//  Implementation of the Class ImageAcquisition
//  Created on:      17-Apr-2011 5:22:52 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#include "ImageAcquisition.h"


//#include <string>
//using std::string;

// ERRORS

int const NO_WEBCAM = -1;


ImageAcquisition::ImageAcquisition()
{
	m_capture = cvCaptureFromCAM(-1);

	if (!m_capture)
	{
		throw NO_WEBCAM;
	}

}

ImageAcquisition::~ImageAcquisition()
{ }

Mat ImageAcquisition::getImage()
{
	/* Delete if this works
	* //Mat frame;
	*
	* //frame = cvQueryFrame(m_capture);
	* //m_current_image = frame ;
	*/

	m_current_image = cvQueryFrame(m_capture);

	return m_current_image;
}