// rdGCVSpline.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2002
// All rights reserved.
//
// Authors: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef __rdGCVSpline_h__
#define __rdGCVSpline_h__


// INCLUDES
#include "rdTools.h"
#include <string>
#include "rdArray.h"
#include "rdPropertyInt.h"
#include "rdPropertyDbl.h"
#include "rdPropertyDblArray.h"
#include "rdFunction.h"


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
 * This class inherits from rdFunction and so can be used as input to
 * any class requiring an rdFuction as input.
 *
 * @author Frank C. Anderson
 */
class RDTOOLS_API rdGCVSpline : public rdFunction
{
//=============================================================================
// MEMBER VARIABLES
//=============================================================================
protected:
	// PROPERTIES
	/** Half order of the spline (degree+1)/2. */
	rdPropertyInt _propHalfOrder;
	/** Error variance for the data and spline fit.  The smoothing factor
	p is computed based on the error variance. */
	rdPropertyDbl _propErrorVariance;
	/** Array of values for the independent variables (i.e., the spline knot
	sequence).  This array must be monotonically increasing. */
	rdPropertyDblArray _propX;
	/** Array of weight values, one for each data point. */
	rdPropertyDblArray _propWeights;
	/** Spline coefficients. */
	rdPropertyDblArray _propCoefficients;
	/** Work array for construction of the spline. */
	rdPropertyDblArray _propWk;

	// REFERENCES
	/** Reference to the value of the HalfOrder property. */
	int &_halfOrder;
	/** Reference to the value of the ErrorVariance property. */
	double &_errorVariance;
	/** Reference to the value of the X property. */
	rdArray<double> &_x;
	/** Reference to the value of the Weights property. */
	rdArray<double> &_weights;
	/** Reference to the value of the Coefficients property. */
	rdArray<double> &_coefficients;
	/** Reference to the value of the Wk property. */
	rdArray<double> &_wk;


	/** Work array for evaluating the spline. */
	rdArray<double> _workEval;
	/** Knot index used to fascilitate finding the appropriate knot during
	an evaluation. */
	int _knotIndex;


//=============================================================================
// METHODS
//=============================================================================
public:
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
	rdGCVSpline();
	rdGCVSpline(int aDegree,int aN,const double *aTimes,const double *aValues,
		const std::string &aName="",double aErrorVariance=0.0);
	rdGCVSpline(DOMElement *aElement);
	rdGCVSpline(const rdGCVSpline &aSpline);
	virtual ~rdGCVSpline();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;
private:
	void setNull();
	void setupProperties();
	void setEqual(const rdGCVSpline &aSpline);

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
	rdGCVSpline& operator=(const rdGCVSpline &aSpline);

	//--------------------------------------------------------------------------
	// SET AND GET
	//--------------------------------------------------------------------------
	void setDegree(int aDegree);
public:
	int getDegree() const;
	int getOrder() const;
	int getHalfOrder() const;
	int getSize() const;
	double getMinX() const;
	double getMaxX() const;
	const rdArray<double>& getX() const;
	int getNW() const;
	const double* getWorkArray();
	const rdArray<double>& getCoefficients() const;

	//--------------------------------------------------------------------------
	// EVALUATION
	//--------------------------------------------------------------------------
	virtual void updateBoundingBox();
	virtual double
		evaluate(int aDerivOrder,double aX=0.0,double aY=0.0,double aZ=0.0);

//=============================================================================
};	// END class rdGCVSpline
//=============================================================================
//=============================================================================

#endif  // __rdGCVSpline_h__
