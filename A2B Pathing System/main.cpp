// check for memory leaks
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include "A2BControl.h"

using namespace cv;
using namespace std;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// check for memory leaks
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	A2BControl ctrl;
	ctrl.startThreads();

	return 0;
}