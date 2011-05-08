#include "A2BGUI.h"
#include "A2BMessageBox.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

#include <string>
using std::string;

// Message box types
int const BOX_OK = 0;
int const BOX_YESNO = 1;

// To check m_buttonPress against
int const ERR_BUTTON_NOT_PUSHED = -1;

// Just a unit used to make calculating positions/sizes easier
int const ERR_UNIT = 80;
// Padding between window/button edges and the text contained
int const ERR_PADDING = 10;

// How many characters can fit inside a messagebox on one line
int const ERR_MAXCHARS = 58;


// The message box
Point const ERR_RECT_START(ERR_UNIT*1, ERR_UNIT*2);
Point const ERR_RECT_END(ERR_UNIT*7,ERR_UNIT*4);

// OK Button
Point const ERR_OK_START(ERR_UNIT*3.5, ERR_RECT_START.y + ERR_UNIT*1.25);
Point const ERR_OK_END(ERR_OK_START.x + ERR_UNIT, ERR_OK_START.y + ERR_UNIT/2);

// YES Button
Point const ERR_YES_START(ERR_UNIT*2.5, ERR_RECT_START.y + ERR_UNIT*1.25);
Point const ERR_YES_END(ERR_YES_START.x + ERR_UNIT, ERR_YES_START.y + ERR_UNIT/2);

// NO Button
Point const ERR_NO_START(ERR_UNIT*4.5, ERR_RECT_START.y + ERR_UNIT*1.25);
Point const ERR_NO_END(ERR_NO_START.x + ERR_UNIT, ERR_NO_START.y + ERR_UNIT/2);


//Aquired from http://www.cplusplus.com/forum/beginner/19034/
vector<string> wordWrap( std::string str, size_t width = 55 ) 
{
	vector<string> wrapped;
	int currentSpace = 0;
	int prevSpace = 0;
    size_t curWidth = width;
 
	while( curWidth < str.length() ) 
	{
        std::string::size_type spacePos = str.rfind( ' ', curWidth );

		if( spacePos == std::string::npos )
            spacePos = str.find( ' ', curWidth );
        
		if( spacePos != std::string::npos ) 
		{
			prevSpace = currentSpace;
			currentSpace = spacePos;
			wrapped.push_back(str.substr(prevSpace, currentSpace));
            //str[ spacePos ] = '\n';
            curWidth = spacePos + width + 1;
        }
    }

	wrapped.push_back(str.substr(currentSpace, str.length()));

    return wrapped;
}

A2BMessageBox::A2BMessageBox(const string & m_window, Mat & image, const string & error, int type)
{
	// Dim the whole picture (nevermind, no alpha transparency)
//	rectangle(image,Point(0,0),Point(CAMERA_ROW_SIZE,CAMERA_COL_SIZE),
//		Scalar(0,0,0,(0.8)), CV_FILLED);

	// Draw outline of box
	rectangle(image, ERR_RECT_START, ERR_RECT_END, Scalar(200,200,200), 2);
	// Fill box with gray
	rectangle(image, ERR_RECT_START, ERR_RECT_END, Scalar(200,200,200), CV_FILLED);

	// check width of string
	if( error.size() > ERR_MAXCHARS )
	{
		vector<string> s = wordWrap(error, ERR_MAXCHARS);
		for( int i = 0; i < s.size(); i++ )
		{
			putText(image, s[i], Point(ERR_RECT_START.x + ERR_PADDING,ERR_RECT_START.y + ERR_PADDING*2 + (ERR_PADDING+5)*i),
				FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,0),1);
		}
	}
	else
	{
		// Write the error message inside the box
		putText(image, error, Point(ERR_RECT_START.x + ERR_PADDING,ERR_RECT_START.y + ERR_PADDING*2),
			FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,0),1);
	}
	
	if( type == BOX_OK )
	{
		// Draw OK button
		rectangle(image, ERR_OK_START, ERR_OK_END, Scalar(0,0,0), 2);

		putText(image, "OK", Point(ERR_OK_START.x + ERR_PADDING,ERR_OK_START.y + ERR_PADDING*2),
			FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,0));

		// This changes the mouse callback specially for the modal OK button
		// so it ignores everything but a click on the button.
		setMouseCallback( m_window, onMouseErrorOK, this );
	}
	else if( type == BOX_YESNO )
	{
		rectangle(image, ERR_YES_START, ERR_YES_END, Scalar(0,0,0), 2);
		rectangle(image, ERR_NO_START, ERR_NO_END, Scalar(0,0,0), 2);

		putText(image, "Yes", Point(ERR_YES_START.x + ERR_PADDING,ERR_YES_START.y + ERR_PADDING*2),
			FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,0));
		putText(image, "No", Point(ERR_NO_START.x + ERR_PADDING,ERR_NO_START.y + ERR_PADDING*2),
			FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,0));

		setMouseCallback( m_window, onMouseErrorYesNo, this );
	}
	else
	{
		assert(false); // means, this should never happen.
	}

	imshow(m_window, image);
	m_buttonPress = ERR_BUTTON_NOT_PUSHED;

	while(m_buttonPress == ERR_BUTTON_NOT_PUSHED)
	{
		waitKey(10);
	}
	setMouseCallback( m_window, A2BGUI::onMouse, this);
}

int A2BMessageBox::getButtonPress()
{
	return m_buttonPress;
}

void A2BMessageBox::onMouseErrorOK( int event, int x, int y, int, void * mbox )
{
	if( event == CV_EVENT_LBUTTONDOWN &&
		x > ERR_OK_START.x && y > ERR_OK_START.y &&	// past the top left corner
		x < ERR_OK_END.x &&	y < ERR_OK_END.y )		// before the bottom right corner
	{
		reinterpret_cast<A2BMessageBox*>(mbox)->m_buttonPress = 0;
	}
}

void A2BMessageBox::onMouseErrorYesNo( int event, int x, int y, int, void * mbox )
{
	if( event == CV_EVENT_LBUTTONDOWN &&
		x > ERR_YES_START.x && y > ERR_YES_START.y &&	// past the top left corner
		x < ERR_YES_END.x &&	y < ERR_YES_END.y )		// before the bottom right corner
	{
		reinterpret_cast<A2BMessageBox*>(mbox)->m_buttonPress = 1;
	}
	else if( event == CV_EVENT_LBUTTONDOWN &&
		x > ERR_NO_START.x && y > ERR_NO_START.y &&	// past the top left corner
		x < ERR_NO_END.x &&	y < ERR_NO_END.y )		// before the bottom right corner
	{
		reinterpret_cast<A2BMessageBox*>(mbox)->m_buttonPress = 0;
	}
}