///////////////////////////////////////////////////////////
//  ImageAcquisition.cpp
//  Implementation of the Class ImageAcquisition
//  Created on:      17-Apr-2011 5:22:52 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#include "ImageAcquisition.h"


#include <string>
using std::string;

//int const WEBCAM_ID = -1;

// ERRORS

int const NO_WEBCAM = -1;


ImageAcquisition::ImageAcquisition() : m_current_image(0)
{
	//m_capture.open( /*WEBCAM_ID*/ -1 );
	m_capture = cvCaptureFromCAM(-1);

	// doesn't work... try videoInput library?
//	cvSetCaptureProperty( m_capture, CV_CAP_PROP_FRAME_WIDTH, 1280 );
//	cvSetCaptureProperty( m_capture, CV_CAP_PROP_FRAME_HEIGHT, 720 );

	if (!m_capture)///*!m_capture.isOpened()*/)
	{
		throw NO_WEBCAM;
	}

}

ImageAcquisition::~ImageAcquisition()
{ }

Image * ImageAcquisition::getImage()
{
	delete m_current_image;

	Mat frame;
	//m_capture >> frame;
	frame = cvQueryFrame(m_capture);
	m_current_image = new Image( frame );

	return m_current_image;
}