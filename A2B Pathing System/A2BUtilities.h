#ifndef A2BUtilities_H
#define A2BUtilities_H

// camera pixel dimensions.  the image dimensions we are receiving
const int CAMERA_ROW_SIZE = 640;
const int CAMERA_COL_SIZE = 480;

// the width and height of our pathing grid spaces in pixels
const int PIXELS_PER_SQUARE = 8;

// the color code for white
const int CLEAR_VALUE = 255;

// the number of spaces per row in our pathing grid
const int ROW_SIZE = CAMERA_ROW_SIZE / PIXELS_PER_SQUARE;
// the number of spaces per column in our pathing grid
const int COL_SIZE = CAMERA_COL_SIZE / PIXELS_PER_SQUARE;

// the number of spaces in our grid
const int BOARD_SIZE = ROW_SIZE * COL_SIZE;

const int ROBOT_SIZE_PX = 176;

const int ROBOT_SIZE_SPACE = (ROBOT_SIZE_PX/PIXELS_PER_SQUARE) + 1;

const string APPLICATION_NAME = "A2B Pathing System";

class A2BUtilities
{
public:
	// used to convert from pixel measurement to grid space id
	static int pixelToSpaceId( int x, int y)	 
	{
		return (y/PIXELS_PER_SQUARE)*ROW_SIZE + (x/PIXELS_PER_SQUARE);
	}
};

#endif