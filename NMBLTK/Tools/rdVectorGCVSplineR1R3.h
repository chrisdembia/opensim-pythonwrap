// rdVectorGCVSplineR1R3.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2002
// All rights reserved.
//
// Authors: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef __rdVectorGCVSplineR1R3_h__
#define __rdVectorGCVSplineR1R3_h__


// INCLUDES
#include "rdTools.h"
#include "rdArray.h"
#include "rdVectorFunction.h"
#include "rdGCVSpline.h"


//template class RDTOOLS_API rdArray<double>;


//=============================================================================
//=============================================================================
/**
 * A class for representing a smooth function with a generalized
 * cross-validation spline.  Linear, cubic, qunitic, and heptic splines
 * are supported:
 *
 *    m (half-order)     order         degree         description
 *    1                    2             1              linear
 *    2                    4             3              cubic
 *    3                    6             5              quintic
 *    4                    8             7              heptic
 *
 * This class wraps the gcvspl.c source code written by D. Twisk in 1994,
 * which is based on the GCVSPL code written in Fortran by Woltring
 * in 1985_07_04.  This class was initially based on a spline class
 * authored by Darryl Thelen and Victor Ng; it has been rewritten to fit
 * into the Realistic Dynamics, Inc. software framework.
 *
 * See the following source for details on how the GCV spline is fit:
 * Woltring, H.J. (1986).  A Fortran package for generalized,
 * cross-validatory spline smoothing and differentiation.  Advances in
 * Engineering Software, Vol. 8, No. 2, 104-113.
 *
 * This class inherits from rdVectorFunction and so can be used as input to
 * any class requiring an rdVectorFuction as input.
 *
 * @author Frank C. Anderson
 */
class RDTOOLS_API rdVectorGCVSplineR1R3 : public rdVectorFunction
{
//=============================================================================
// DATA
//=============================================================================
private:
	/** Holds return value for evaluate */
	rdArray<double> _value;
protected:
	/** Spline containing 1st dependent variable data. */
	rdGCVSpline* _splineY0;
	/** Spline containing 2nd dependent variable data. */
	rdGCVSpline* _splineY1;
	/** Spline containing 3rd dependent variable data. */
	rdGCVSpline* _splineY2;

//=============================================================================
// METHODS
//=============================================================================
public:
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
	rdVectorGCVSplineR1R3();
	rdVectorGCVSplineR1R3(int aDegree,int aN,const double *aTimes,double *aY0Values,
		double *aY1Values,double *aY2Values,const char *aName=NULL,
		double aErrorVariance=0.0);
	rdVectorGCVSplineR1R3(DOMElement *aElement);
	rdVectorGCVSplineR1R3(const rdVectorGCVSplineR1R3 &aVectorSpline);
	virtual ~rdVectorGCVSplineR1R3();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;
private:
	void setNull();
	void setEqual(const rdVectorGCVSplineR1R3 &aSpline);

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
	rdVectorGCVSplineR1R3& operator=(const rdVectorGCVSplineR1R3 &aVectorSpline);

	//--------------------------------------------------------------------------
	// SET AND GET
	//--------------------------------------------------------------------------
	void setDegree(int aDegree);
public:
	rdGCVSpline* getSplineY0() const;
	rdGCVSpline* getSplineY1() const;
	rdGCVSpline* getSplineY2() const;

	//--------------------------------------------------------------------------
	// EVALUATION
	//--------------------------------------------------------------------------
	virtual void updateBoundingBox();
	virtual void evaluate(const double *aX,double *rY);
	virtual void evaluate(const rdArray<double> &aX,rdArray<double> &rY);
	virtual void evaluate(const rdArray<double> &aX,rdArray<double> &rY,
		const rdArray<int> &aDerivWRT);

//=============================================================================
};	// END class rdVectorGCVSplineR1R3
//=============================================================================
//=============================================================================

#endif  // __rdVectorGCVSplineR1R3_h__
