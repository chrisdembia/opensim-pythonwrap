// rdTransformChangeEvent.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2005- Stanford University
// All rights reserved.
// This class represents an encapsulation of a change in xforms. 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdTransformChangeEvent_h__
#define __rdTransformChangeEvent_h__

#include "rdTools.h"
#include "rdEvent.h"

#ifdef SWIG
	#ifdef RDTOOLS_API
		#undef RDTOOLS_API
		#define RDTOOLS_API
	#endif
#endif

//=============================================================================
//=============================================================================
/**
 */

class RDTOOLS_API rdTransformChangeEvent: public rdEvent
{

//=============================================================================
// DATA
//=============================================================================
public:
//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	virtual ~rdTransformChangeEvent();
	rdTransformChangeEvent(const rdObject& aSource);

//=============================================================================
};	// END of class rdTransformChangeEvent
//=============================================================================
//=============================================================================

#endif //__rdTransformChangeEvent_h__
