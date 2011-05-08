///////////////////////////////////////////////////////////
//  ImageProcessor.cpp
//  Implementation of the Class ImageProcessor
//  Created on:      17-Apr-2011 5:23:05 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#include "ImageProcessor.h"
// edging
const int EDGE_THRESH = 30;

Image * ImageProcessor::createEdgedImage(Image * image)
{
	Mat frame = image->mat();
//	frame.copyTo(em);
	Mat gray, edge, cedge;

	cvtColor(frame, gray, CV_RGB2GRAY);
	blur(gray, edge, Size(3,3));
	Canny(edge, edge, EDGE_THRESH, EDGE_THRESH*3, 3);
	cedge = Scalar::all(0);
	frame.copyTo(cedge, edge);
	threshold(cedge, cedge, EDGE_THRESH, 255, CV_THRESH_BINARY_INV);

	Image * edged = new Image(cedge);

	return edged;
}

Point ImageProcessor::findRobot(Mat * room, Robot * robot)//(Image * image, Robot * robot)
{
	Point robotPos;
	
	// because I changed the function params. Need robot wid/len, so.
	Mat bot = robot->peekSymbol()->mat().clone();
	
	Mat rtn((room->rows - bot.rows) + 1, (room->cols - bot.cols) + 1,DataType<float>::type); 
	
	matchTemplate(*(room), bot, rtn, CV_TM_SQDIFF);

	Point robotLoc;//(0,0);
	robotLoc.x = 0; robotLoc.y = 0;
	double minVal = 0;

	minMaxLoc(rtn, &minVal,(double *)0,&robotLoc,(Point *)0,Mat());
	
	robotPos.x = robotLoc.x;// * (size of robot image in pixels));//what this should be is the position it is in with relation to the rtn Mat * the size of the robot pic in pixles
	robotPos.y = robotLoc.y;

	;

	// Assume robot is facing "up" or "down"
	robotPos.x += robot->width() / 2;
	robotPos.y += robot->length() / 2;

	return robotPos;
}

void ImageProcessor::mapObstacles( Image & image, bool * obstacleGrid )
{
	Mat square;
	Mat img = image.mat();
	for( int rowid = 0; rowid < COL_SIZE; rowid++ )
	{
		for( int colid = 0; colid < ROW_SIZE; colid++ )
		{
			square = img(Rect(colid*GRID_SQUARE_SIZE, rowid*GRID_SQUARE_SIZE, GRID_SQUARE_SIZE, GRID_SQUARE_SIZE));

			obstacleGrid[rowid*ROW_SIZE + colid] = !(allWhite(square) ? true : false);
		}
	}


}

bool ImageProcessor::allWhite( const Mat & square )
{
	bool white = true;
	for( int i = 0; i < square.rows && white; i++ )
	{
		for( int j = 0; j < square.cols && white; j++ )
		{
			if( square.data[i*square.cols + j] != (uchar)255 )
				white = false;
		}
	}
	return white;
}