#ifndef A2BUtilities_H
#define A2BUtilities_H

// map obstacles
const int CAMERA_ROW_SIZE = 640;
const int CAMERA_COL_SIZE = 480;

const int GRID_SQUARE_SIZE = 16;
const int CLEAR_VALUE = 255;
const int ROW_SIZE = CAMERA_ROW_SIZE / GRID_SQUARE_SIZE;
const int COL_SIZE = CAMERA_COL_SIZE / GRID_SQUARE_SIZE;
const int BOARD_SIZE = ROW_SIZE * COL_SIZE;

const string APPLICATION_NAME = "A2B Pathing System";

class A2BUtilities
{
public:
	static int pixelToSpaceId( int x, int y)
	{
		return (y/GRID_SQUARE_SIZE)*ROW_SIZE + (x/GRID_SQUARE_SIZE);
	}
};

#endif