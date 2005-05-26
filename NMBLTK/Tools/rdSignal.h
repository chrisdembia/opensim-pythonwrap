// rdSignal.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2000 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdSignal_h__
#define __rdSignal_h__


#include "rdTools.h"
#include "rdArray.h"


//=============================================================================
//=============================================================================
/**
 * A class for signal processing.
 */
class RDTOOLS_API rdSignal
{
//=============================================================================
// DATA
//=============================================================================

//=============================================================================
// METHODS
//=============================================================================
public:
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
	//rdSignal();
	//virtual ~rdSignal();

	//--------------------------------------------------------------------------
	// FILTERS
	//--------------------------------------------------------------------------
	static int
		LowpassIIR(double aDeltaT,double aCutOffFrequency,
		int aN,double *aSignal,double *rFilteredSignal);
	static int
		LowpassFIR(int aOrder,double aDeltaT,double aCutoffFrequency,
		int aN,double *aSignal,double *rFilteredSignal);
	static int
		BandpassFIR(int aOrder,double aDeltaT,
		double aLowFrequency,double aHighFrequency,
		int aN,double *aSignal,double *aFilteredSignal);

	//--------------------------------------------------------------------------
	// PADDING
	//--------------------------------------------------------------------------
	static double*
		Pad(int aPad,int aN,const double aSignal[]);

	//--------------------------------------------------------------------------
	// POINT REDUCTION
	//--------------------------------------------------------------------------
	static int
		ReduceNumberOfPoints(double aDistance,
		rdArray<double> &rTime,rdArray<double> &rSignal);


	//--------------------------------------------------------------------------
	// CORE MATH
	//--------------------------------------------------------------------------
	static double sinc(double x);
	static double hamming(int k,int M);

//=============================================================================
};	// END class rdSignal
//=============================================================================
//=============================================================================

#endif  // __rdSignal_h__
