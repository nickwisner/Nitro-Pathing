///////////////////////////////////////////////////////////
//  ImageAcquisition.h
//  Implementation of the Class ImageAcquisition
//  Created on:      17-Apr-2011 5:22:51 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

//#if !defined(EA_F06BFFF8_B909_48f9_B235_EE3F3D8C7005__INCLUDED_)
//#define EA_F06BFFF8_B909_48f9_B235_EE3F3D8C7005__INCLUDED_
#ifndef IMAGEACQ_H
#define IMAGEACQ_H

#include "iImageAcquisition.h"
#include <boost/thread.hpp>
#include "ImageProcessor.h"

/*
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv\cvaux.h>
#include <opencv\highgui.h>
#include <opencv\cxcore.h>

using namespace cv;
*/

class ImageAcquisition : public iImageAcquisition
{

	public:
		ImageAcquisition();
		virtual ~ImageAcquisition();

		Mat getPlain();
		Mat getEdge();
		bool* getObstMap();

	private:
		VideoCapture m_cap;

		Mat m_plainCur;
		Mat m_edgeCur;
		bool * m_obstMap;

		void getImages();
		CvCapture * m_capture;

		boost::mutex m_plainLock;
		boost::mutex m_edgeLock;
		boost::mutex m_obstLock;
		boost::mutex m_loopLock;

		bool m_updateLoop;

		boost::thread m_imageUpdate;

};
#endif // IMAGEACQ_H
