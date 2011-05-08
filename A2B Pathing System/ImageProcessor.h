///////////////////////////////////////////////////////////
//  ImageProcessor.h
//  Implementation of the Class ImageProcessor
//  Created on:      17-Apr-2011 5:23:05 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#if !defined(EA_672BEF0F_5B16_4403_B3DD_EDEA07BC819F__INCLUDED_)
#define EA_672BEF0F_5B16_4403_B3DD_EDEA07BC819F__INCLUDED_

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

#include "Image.h"
#include <fstream>

#include "A2BUtilities.h"

#include "Robot.h"

class ImageProcessor
{

public:
	static Image * createEdgedImage(Image * image);
	static Point findRobot(Mat * room, Robot * bot);//(Image * image, Robot * robot);
	static bool isRegionClear(Image & image, Point point, int robotwidth);
	static void mapObstacles( Image & image, bool * obstacleGrid );
	
private:
	static bool allWhite( const Mat & square );

};
#endif // !defined(EA_672BEF0F_5B16_4403_B3DD_EDEA07BC819F__INCLUDED_)
