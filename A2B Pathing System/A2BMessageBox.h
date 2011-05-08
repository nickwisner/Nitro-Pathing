#ifndef A2BMESSAGEBOX_H
#define A2BMESSAGEBOX_H

#include "A2BUtilities.h"

// Message Box types
extern int const BOX_OK;
extern int const BOX_YESNO;

class A2BMessageBox
{
public:
	A2BMessageBox(const string & window, Mat & image, const string & error, int type);
//	~A2BMessageBox();

	int getButtonPress();

private:
	int m_buttonPress;

	static void onMouseErrorOK( int event, int x, int y, int, void * mbox );
	static void onMouseErrorYesNo( int event, int x, int y, int, void * mbox );
};

#endif