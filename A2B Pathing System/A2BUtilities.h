#ifndef A2BUtilities_H
#define A2BUtilities_H

#include <ctime>

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
const string CONFIG_FILE_NAME = "a2bconfig.cfg";
const string ERR_LOG_FILE_NAME = "a2bLog.log";

enum A2BError
{
	A2BERR_GENERIC_ERROR,
	A2BERR_CANNOT_FIND_ROBOT,
	A2BERR_NO_CAMERA,
	A2BERR_NO_ROBOT,
	A2BERR_NO_PATH
};

class A2BUtilities
{
public:
	// used to convert from pixel measurement to grid space id
	static int pixelToSpaceId( int x, int y)	 
	{
		return (y/PIXELS_PER_SQUARE)*ROW_SIZE + (x/PIXELS_PER_SQUARE);
	}

	static string GetTime()
	{
		time_t rawtime;
		struct tm * timeinfo;
		string currtime;
		time ( &rawtime );
		timeinfo = localtime ( &rawtime );
		currtime = asctime(timeinfo);
		int currpos(0);

		// for all spaces in the time
		while((currpos = currtime.find(' ')) != string::npos)
		{
		// take the spaces out of it and replace them with '-'
			currtime[currpos] = '-'; 
		}

		// remove the '\n' from the end of the string;
		//currtime[currtime.size()-1] = 0;

		return currtime;
	}
};

#endif