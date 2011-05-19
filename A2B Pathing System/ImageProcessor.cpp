///////////////////////////////////////////////////////////
//  ImageProcessor.cpp
//  Implementation of the Class ImageProcessor
//  Created on:      17-Apr-2011 5:23:05 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#include "ImageProcessor.h"
// edging
const int EDGE_THRESH = 30;

// Takes plain image, returns edged image
// change this fn prototype to just take a ref.
Mat ImageProcessor::createEdgedImage(Mat * image)
{
	Mat frame = *image;
	Mat gray, edge, cedge; // temp mats

	cvtColor(frame, gray, CV_RGB2GRAY); // grayscale it
	
	blur(gray, edge, Size(3,3));	// prepare for canny edge detection
	Canny(edge, edge, EDGE_THRESH, EDGE_THRESH*3, 3); // save canny to edge
	cedge = Scalar::all(0);
	frame.copyTo(cedge, edge);
	threshold(cedge, cedge, EDGE_THRESH, 255, CV_THRESH_BINARY_INV); // make it white and black

	return cedge; // edged image, in color
}

Point ImageProcessor::findRobot(Mat * room, Robot * robot)
{
	Point robotPos;
	
	// load picture of robot into "bot"
	Mat bot = robot->peekSymbol().clone();
	
	// Needed for matchTemplate, which finds the robot picture inside the bigger pic
	Mat rtn((room->rows - bot.rows) + 1, (room->cols - bot.cols) + 1,DataType<float>::type); 
	
	//A openCV algorithm that will fill rtn with itegers where the minimum point is where the robot is found
	matchTemplate(*(room), bot, rtn, CV_TM_SQDIFF);


	Point robotLoc;
	robotLoc.x = 0; robotLoc.y = 0; // Point robotLoc(0,0) wasn't working for some reason
	double minVal = 0;

	minMaxLoc(rtn, &minVal,(double *)0,&robotLoc,(Point *)0,Mat());
	
	//what this should be is the position it is in with relation to the rtn Mat * the size of the robot pic in pixels
	robotPos.x = robotLoc.x;
	robotPos.y = robotLoc.y;

	// Assume robot is facing "up" or "down"
	robotPos.x += robot->getWidth() / 2;
	robotPos.y += robot->getLength() / 2;

	return robotPos;
}

// Fills obstacleGrid (one-dim array of size COL_SIZE * ROW_SIZE) with bools
// trues in the sea of falses. true means there's an obstacle.
void ImageProcessor::mapObstacles( Mat & image, bool * obstacleGrid )
{
	Mat square;
	Mat img = image;
	for( int rowid = 0; rowid < COL_SIZE; rowid++ )
	{
		for( int colid = 0; colid < ROW_SIZE; colid++ )
		{
			// the little square from the image that defines 1 "space" or cell of the big image
			square = img(Rect(colid*PIXELS_PER_SQUARE, rowid*PIXELS_PER_SQUARE, PIXELS_PER_SQUARE, PIXELS_PER_SQUARE));

			// set false if no obstacles there (all white).
			// so if anything in the little square is black, there's the edge of an obstacle.
			obstacleGrid[rowid*ROW_SIZE + colid] = !allWhite(square);
		}
	}
}

// Returns true if everything is white here.
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

//Should make a white boarder around the image. This is in hopes that matchTemplate will not attempt to find the robot outside of the image.
//Currently not implemented.
bool ImageProcessor::makeImageBorder(Mat* image)
{
	// white out top and bottom rows
	for(int x(0); x < CAMERA_ROW_SIZE; x++)
	{
		// white out top line of image
		image->data[0 + x] = 255; // 255 = white

		// white out bottom line of image
		image->data[(CAMERA_COL_SIZE-1)*CAMERA_ROW_SIZE + x] = 255; // 255 = white
	}

	// white out left and right columns
	for(int y(0); y < CAMERA_COL_SIZE; y++)
	{
		// white out leftmost line of image
		image->data[y*CAMERA_ROW_SIZE + 0] = 255;

		// white out rightmost line of image
		image->data[y*CAMERA_ROW_SIZE + CAMERA_ROW_SIZE - 1] = 255;
	}

	return true;
}
