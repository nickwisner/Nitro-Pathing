#ifndef A2BUtilities_H
#define A2BUtilities_H

// camera pixel dimensions.  the image dimensions we are receiving
const int CAMERA_ROW_SIZE = 640;
const int CAMERA_COL_SIZE = 480;

// the width and height of our pathing grid spaces in pixels
const int GRID_SQUARE_SIZE = 16;

// the color code for white
const int CLEAR_VALUE = 255;

// the number of spaces per row in our pathing grid
const int ROW_SIZE = CAMERA_ROW_SIZE / GRID_SQUARE_SIZE;
// the number of spaces per column in our pathing grid
const int COL_SIZE = CAMERA_COL_SIZE / GRID_SQUARE_SIZE;

// the number of spaces in our grid
const int BOARD_SIZE = ROW_SIZE * COL_SIZE;

const string APPLICATION_NAME = "A2B Pathing System";

class A2BUtilities
{
public:
	// used to convert from pixel measurement to grid space id
	static int pixelToSpaceId( int x, int y)	 
	{
		return (y/GRID_SQUARE_SIZE)*ROW_SIZE + (x/GRID_SQUARE_SIZE);
	}
};

#endif