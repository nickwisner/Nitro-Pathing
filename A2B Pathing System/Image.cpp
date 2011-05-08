///////////////////////////////////////////////////////////
//  Image.cpp
//  Implementation of the Class Image
//  Created on:      17-Apr-2011 5:13:34 PM
//  Original author: peter.finn
///////////////////////////////////////////////////////////

#include "Image.h"

#include <opencv2/core/core.hpp>

Image::Image()
{
}

Image::Image( Mat img ) : m_timestamp(0)
{
	m_image = img.clone();
	m_timestamp = getTickCount();
}

Image::~Image()
{ }


Image::Image( const Image & image )
{
	*this = image;
}
Image & Image::operator=( const Image & image )
{
	if( this != &image )
	{
		m_timestamp = image.m_timestamp;
		//If the Mat is invalid then this will probably break
		m_image.release();
		m_image = image.m_image.clone();
	}
	return *this;
}


int Image::age()
{
	return getTickCount() - m_timestamp;
}


Mat Image::mat()
{
	return m_image;
}

Mat Image::mat() const
{
	return m_image;
}

//void setMat( CvMat &m)
//{
//	Mat tmp = m;
//
//	m_image = tmp.clone();
//}
//void setMat( Mat &m)
//{
//	m_image = m.clone();
//}
