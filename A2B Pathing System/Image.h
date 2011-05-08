///////////////////////////////////////////////////////////
//  Image.h
//  Implementation of the Class Image
//  Created on:      17-Apr-2011 5:13:33 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#if !defined(EA_4D292A95_A0F8_4e44_BD35_D182F809AE35__INCLUDED_)
#define EA_4D292A95_A0F8_4e44_BD35_D182F809AE35__INCLUDED_

#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

class Image
{

public:
	Image();
	Image( Mat img );
	Image( const Image & image );
	Image & operator=( const Image & image );
	virtual ~Image();

	int age();
	Mat mat();
	Mat mat() const;

	/*void setMat( CvMat &m);
	void setMat( Mat &m);*/

private:
	Mat m_image;
	int m_timestamp;

};

#endif // !defined(EA_4D292A95_A0F8_4e44_BD35_D182F809AE35__INCLUDED_)
