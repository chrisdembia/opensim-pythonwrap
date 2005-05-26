// rdSprings.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2000 Realistic Dynamics, Inc.
// All rights reserved.
//
// CONFIDENTIAL
//
// The material contain within this file is the sole property of
// Realistic Dynamics, Inc., and may not be read, copied, or distributed
// without the expressed writen consent of Realistic Dynamics, Inc.
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdSprings_h__
#define __rdSprings_h__


// INCLUDES
#include "rdModel.h"


//=============================================================================
//=============================================================================
/**
 * A class which implements a set of static functions which model
 * the stress-strain properties of a number of different types of springs.
 *
 */
class RDSIMULATION_API rdSprings  
{

//=============================================================================
// DATA
//=============================================================================
private:

//=============================================================================
// METHODS
//=============================================================================
public:
	rdSprings();
	virtual ~rdSprings();

	//--------------------------------------------------------------------------
	// SPRINGS
	//--------------------------------------------------------------------------
	static double Damp(double kv,double v);
	static double Linear(double kx,double dx);
	static double Linear(double kx,double x0,double x);
	static double DampedLinear(double kv,double v,double kx,double x0,double x);
	static double ZeroForDampedLinear(double kv,double v,double kx,double x,
						double f);
	static double DisplacementOfDampedLinear(double kv,double v,double kx,double f);
	static double Quadratic(double kx,double dx);
	static double Quadratic(double kx,double x0,double x);
	static double DampedQuadratic(double kv,double v,double kx,double dx);
	static double DampedQuadratic(double kv,double v,double kx,double x0,double x);
	static double ExponentialBarrier(double v,double dx);
	static double ExponentialBarrier(double aG0,double aG1,double aG2,
						double aE0,double aE1,double aE2,
						double aKV,double aV,double aDX);
	static double ExponentialBarrierDX(double v,double dx);
	static double ExponentialBarrierDX(double aG0,double aG1,double aG2,
						double aE0,double aE1,double aE2,
						double aKV,double aV,double aDX);
	static double ExponentialBarrierDV(double v,double dx);
	static double ExponentialBarrierDV(double aG0,double aG1,double aG2,
						double aE0,double aE1,double aE2,
						double aKV,double aV,double aDX);
	static double oscillation(double delay,double t,double f);

//=============================================================================
};	// END class rdSprings
//=============================================================================
//=============================================================================


#endif //__rdSprings_h__
