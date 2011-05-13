///////////////////////////////////////////////////////////
//  iImageAcquisition.h
//  Implementation of the Interface iImageAcquisition
//  Created on:      18-Apr-2011 7:34:06 PM
//  Original author: nagisa.day
///////////////////////////////////////////////////////////

#ifndef iIMAGEACQ_H
#define iIMAGEACQ_H

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv\cvaux.h>
#include <opencv\highgui.h>
#include <opencv\cxcore.h>

using namespace cv;

class iImageAcquisition
{

public:
	iImageAcquisition() {

	}

	virtual ~iImageAcquisition() {

	}

	virtual Mat getPlain() = 0;
	virtual Mat getEdge() = 0;
	virtual bool* getObstMap() = 0;

};
#endif //iIMAGEACQ_H