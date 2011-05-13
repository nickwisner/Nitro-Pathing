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


ImageAcquisition::ImageAcquisition()
{
//	VideoCapture m_cap(0);
	m_capture = cvCaptureFromCAM(-1);

	if (!m_capture)
	{
		throw NO_WEBCAM;
	}
	//if(!m_cap.isOpened());
	//{
	//	throw NO_WEBCAM;
	//}
	
	m_obstMap = new bool[ROW_SIZE * COL_SIZE];
	
	/*m_cap >>*/ m_plainCur = cvQueryFrame(m_capture);

	m_edgeCur = Mat(ImageProcessor::createEdgedImage(&m_plainCur).clone());

	ImageProcessor::mapObstacles(m_edgeCur, m_obstMap);

	m_imageUpdate = boost::thread(bind(&ImageAcquisition::getImages, this));

}

ImageAcquisition::~ImageAcquisition()
{
	m_imageUpdate.interrupt();
	m_imageUpdate.join();
	delete [] m_obstMap;
}
void ImageAcquisition::getImages()
{
	Mat temp;
	while(1)
	{
		temp = Mat(cvQueryFrame(m_capture)).clone();
		//boost::this_thread::disable_interruption di;
		// getImage news the image, but it also deletes its current image which is same address as m_plainImage here
		m_plainLock.lock();
		//while(!m_plainLock.try_lock())
		//	boost::this_thread::yield();
		/*m_cap >>*/ m_plainCur = temp;//Mat(cvQueryFrame(m_capture)).clone();
		m_plainLock.unlock();

		//while(!m_edgeLock.try_lock())
		//	boost::this_thread::yield();
		m_edgeLock.lock();
		 // createEdgedImage news the image but has no image to delete so we do it here
		m_edgeCur = Mat(ImageProcessor::createEdgedImage(&m_plainCur).clone());
		m_edgeLock.unlock();


		//while(!m_obstLock.try_lock())
		//	boost::this_thread::yield();
		m_obstLock.lock();
		ImageProcessor::mapObstacles(m_edgeCur, m_obstMap);
		m_obstLock.unlock();
		
		//boost::this_thread::restore_interruption ri(di);

		boost::this_thread::sleep(boost::posix_time::milliseconds(500));
	}
}
Mat ImageAcquisition::getPlain()
{
	//while(!m_plainLock.try_lock())
	//	boost::this_thread::yield();

	m_plainLock.lock();
	Mat t = m_plainCur.clone();
	m_plainLock.unlock();
	return t;
}
Mat ImageAcquisition::getEdge()
{
	//while(!m_edgeLock.try_lock())
	//	boost::this_thread::yield();
	m_edgeLock.lock();
	Mat t = m_edgeCur.clone();
	m_edgeLock.unlock();
	return t;
}
bool* ImageAcquisition::getObstMap()
{//this is sad-face
	//while(!m_obstLock.try_lock())
	//	boost::this_thread::yield();
	m_obstLock.lock();
	bool * tmp = new bool[ROW_SIZE * COL_SIZE];
	memcpy(tmp, m_obstMap, sizeof(bool)* (ROW_SIZE*COL_SIZE));
	m_obstLock.unlock();
	return tmp;
}