// rdGCVSplineSet.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2002 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef __rdGCVSplineSet_h__
#define __rdGCVSplineSet_h__


// INCLUDES
#include "rdTools.h"
#include "rdObject.h"
#include "rdFunctionSet.h"
#include "rdGCVSpline.h"
#include "rdStorage.h"


//=============================================================================
//=============================================================================
/**
 * A class for holding a set of generalized cross-validated splines.
 *
 * @see rdGCVSpline
 * @author Frank C. Anderson
 */
class RDTOOLS_API rdGCVSplineSet : public rdFunctionSet
{
//=============================================================================
// DATA
//=============================================================================
protected:

//=============================================================================
// METHODS
//=============================================================================
public:
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
	rdGCVSplineSet();
	rdGCVSplineSet(const char *aFileName);
	rdGCVSplineSet(int aDegree,rdStorage *aStore,double aErrorVariance=0.0);
	virtual ~rdGCVSplineSet();
private:
	void setNull();
	void construct(int aDegree,rdStorage *aStore,double aErrorVariance);

	//--------------------------------------------------------------------------
	// SET AND GET
	//--------------------------------------------------------------------------
public:
	rdGCVSpline* getGCVSpline(int aIndex);

	//--------------------------------------------------------------------------
	// UTILITY
	//--------------------------------------------------------------------------
	rdStorage* constructStorage(int aDerivOrder,double aDX=-1);

//=============================================================================
};	// END class rdGCVSplineSet
//=============================================================================
//=============================================================================

#endif  // __rdGCVSplineSet_h__
