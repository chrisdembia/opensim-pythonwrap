// rdSpline.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2000 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef __rdSpline_h__
#define __rdSpline_h__


// INCLUDES
#include "rdTools.h"

// DEFINES
#define RDSPLINE_MAXSIZE 2048


//=============================================================================
//=============================================================================
/**
 * A class for representing smooth functions with b-splines.
 */
class RDTOOLS_API rdSpline
{
//=============================================================================
// DATA
//=============================================================================
private:
	int _status;
	char _name[RDSPLINE_MAXSIZE];
	double _ti,_tf;
	int _order;
	int _nknots;
	int _ncoefs;
	double *_knots;
	double *_coefs;
	double *_tx;
	double *_b;

//=============================================================================
// METHODS
//=============================================================================
public:
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
	//rdSpline(const char *aName,double aTI,double aTF,int aOrder,
	// int aNKnots,double *aKnots,int aNCoefs,double *aCoefs);
	virtual ~rdSpline();
	rdSpline(const char* aFileName);
	rdSpline(FILE *aFP);
private:
	int initialize(FILE *aFP);
	void null();
	int checkFileStatus(int aStatus);

	//--------------------------------------------------------------------------
	// EVALUATION
	//--------------------------------------------------------------------------
public:
	int getKnotIndex(double x);
	double evaluate(double x);

	//--------------------------------------------------------------------------
	// PRINTING
	//--------------------------------------------------------------------------
	void print();

//=============================================================================
};	// END class rdSpline
//=============================================================================
//=============================================================================

#endif  // __rdSpline_h__
