///////////////////////////////////////////////////////////
//  ImageAcquisition.cpp
//  Implementation of the Class ImageAcquisition
//  Created on:      17-Apr-2011 5:22:52 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#include "ImageAcquisition.h"
#include <boost/thread.hpp>


#include <string>
using std::string;

// ERRORS
int const NO_WEBCAM = -1;


ImageAcquisition::ImageAcquisition() : m_plainCur(0), m_edgeCur(0)
{
	m_capture = cvCaptureFromCAM(-1);

	if (!m_capture)
	{
		throw NO_WEBCAM;
	}
	
	m_obstMap = new bool[ROW_SIZE * COL_SIZE];
}

ImageAcquisition::~ImageAcquisition()
{ 
	delete [] m_obstMap;
}
void ImageAcquisition::getImages()
{
		// getImage news the image, but it also deletes its current image which is same address as m_plainImage here
	m_plainImage = m_imageacquisition->getImage();
	
	delete m_edgedImage; // createEdgedImage news the image but has no image to delete so we do it here
	m_edgedImage = ImageProcessor::createEdgedImage(m_plainImage);

	ImageProcessor::mapObstacles(*m_edgedImage, m_obstacleMap);
//	ImageProcessor::makeImageBorder(&(m_plainImage->mat()))
}
Mat ImageAcquisition::getPlain()
{
	return m_plainCur->clone();
}
Mat ImageAcquisition::getEdge()
{
	return m_edgeCur->clone();
}
bool* ImageAcquisition::getObstMap()
{//this is sad-face

	bool * tmp = new bool[ROW_SIZE * COL_SIZE];
	memcpy(tmp, m_obstMap, sizeof(bool)* (ROW_SIZE*COL_SIZE));
	
	return tmp;
}
Mat ImageAcquisition::getImage()
{
    delete m_plainCur;

    *m_plainCur = cvQueryFrame(m_capture);

    return m_plainCur->clone();
}