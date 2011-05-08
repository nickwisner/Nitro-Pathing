// check for memory leaks
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <vector>

#include "A2BControl.h"
#include "A2BDatabase.h"
#include "A2BGUI.h"
#include "Pathing.h"
#include "ImageAcquisition.h"
#include "ImageProcessor.h"

using namespace cv;
using namespace std;


//int main(int ac, char** av)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// check for memory leaks
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	A2BControl ctrl;
	ctrl.startThreads();

	return 0;
}

