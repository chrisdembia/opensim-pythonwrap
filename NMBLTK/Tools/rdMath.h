// rdMath.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2000 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdMath_h__
#define __rdMath_h__


#include "rdTools.h"


class rdLine;
class rdPlane;


//=============================================================================
//=============================================================================
/**
 * This class provides basic math functions and constants.
 */
class RDTOOLS_API rdMath
{
//=============================================================================
// DATA
//=============================================================================
public:
	static const double PI;
	static const double RTD;
	static const double DTR;
	static const double SMALL;
	static const double ZERO;
	static const double NAN;
	static const double INFINITY;
	static const double MINUS_INFINITY;
	static const double PLUS_INFINITY;

//=============================================================================
// METHODS
//=============================================================================
public:

	//--------------------------------------------------------------------------
	// ARITHMATIC
	//--------------------------------------------------------------------------
	static double CopySign(double aMag,double aSign);
	static bool IsZero(double aValue);
	
	//--------------------------------------------------------------------------
	// EXPONENTIAL STEP FUNCTIONS
	//--------------------------------------------------------------------------
	static double SigmaUp(double tau,double to,double t);
	static double SigmaDn(double tau,double to,double t);

	//--------------------------------------------------------------------------
	// CURVE FITTING
	//--------------------------------------------------------------------------
	static int
		FitParabola(double aX1,double aY1,double aX2,double aY2,
		double aX3,double aY3,double *rC0,double *rC1,double *rC2);

	//--------------------------------------------------------------------------
	// GEOMETRY
	//--------------------------------------------------------------------------
	static int
		ComputeIntersection(const rdLine *aLine,const rdPlane *aPlane,
		double rPoint[3]);
	static void
		ComputeNormal(double aP1X,double aP1Y,double aP1Z,
		double aP2X,double aP2Y,double aP2Z,
		double aP3X,double aP3Y,double aP3Z,
		double rNormal[3]);


//=============================================================================
};	// END class rdMath
//=============================================================================
//=============================================================================

#endif // __rdMath_h__

