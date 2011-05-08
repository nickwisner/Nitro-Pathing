///////////////////////////////////////////////////////////
//  iImageAcquisition.h
//  Implementation of the Interface iImageAcquisition
//  Created on:      18-Apr-2011 7:34:06 PM
//  Original author: nagisa.day
///////////////////////////////////////////////////////////

#if !defined(EA_98DE6B47_8533_4c9c_AE0F_D47013670227__INCLUDED_)
#define EA_98DE6B47_8533_4c9c_AE0F_D47013670227__INCLUDED_

#include "Image.h"

class iImageAcquisition
{

public:
	iImageAcquisition() {

	}

	virtual ~iImageAcquisition() {

	}

	virtual Image * getImage() =0;

};
#endif // !defined(EA_98DE6B47_8533_4c9c_AE0F_D47013670227__INCLUDED_)
