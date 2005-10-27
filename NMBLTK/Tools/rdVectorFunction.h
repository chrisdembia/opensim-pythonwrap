// rdVectorFunction.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2002 Realistic Dynamics, Inc.s
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdVectorFunction_h__
#define __rdVectorFunction_h__


// INCLUDES
#include "rdTools.h"
#include "rdObject.h"
#include "rdArray.h"



//=============================================================================
//=============================================================================
/**
 * An abstract class for representing a vector function.
 *
 * A vector function is a relation between some number of independent variables 
 * and some number of dependent values such that for any particular set of
 * independent variables the correct number of dependent variables is returned.
 * Values of the function and its derivatives
 * are obtained by calling the evaluate() method.  The curve may or may not
 * be finite or diferentiable; the evaluate method returns values between
 * rdMath::MINUS_INFINITY and rdMath::PLUS_INFINITY, or it returns rdMath::NAN
 * (not a number) if the curve is not defined.
 * Currently, functions of up to 3 variables (x,y,z) are supported.
 *
 * @author Frank C. Anderson and Saryn R. Goldberg
 */
class RDTOOLS_API rdVectorFunction : public rdObject
{
//=============================================================================
// DATA
//=============================================================================
protected:
	/** Number of independent variables */
	int _nX;
	/** Number of dependant variables */
	int _nY;
	/** Array containing minimum allowed values of the independent variables. */
	rdArray<double> _minX;
	/** Array containing maximum allowed values of the independent variables. */
	rdArray<double> _maxX;

//=============================================================================
// METHODS
//=============================================================================
public:
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
	rdVectorFunction();
	rdVectorFunction(int aNX, int aNY);
	rdVectorFunction(DOMElement *aElement);
	rdVectorFunction(const rdVectorFunction &aVectorFunction);
	virtual ~rdVectorFunction();
	virtual rdObject* copy() const = 0;
	virtual rdObject* copy(DOMElement *aElement) const = 0;
private:
	void setNull();
	void setEqual(const rdVectorFunction &aVectorFunction);

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
	rdVectorFunction& operator=(const rdVectorFunction &aVectorFunction);

	//--------------------------------------------------------------------------
	// SET AND GET
	//--------------------------------------------------------------------------
private:
	void setNX(int aNX);
	void setNY(int aNY);

public:
	int getNX() const;

	int getNY() const;

	void setMinX(const rdArray<double> &aMinX);
	const rdArray<double>& getMinX() const;
	void setMinX(int aXIndex, double aMinX);
	double getMinX(int aXIndex) const;

	void setMaxX(const rdArray<double> &aMaxX);
	const rdArray<double>& getMaxX() const;
	void setMaxX(int aXIndex, double aMaxX);
	double getMaxX(int aXIndex) const;
	
	//--------------------------------------------------------------------------
	// EVALUATE
	//--------------------------------------------------------------------------
	virtual void updateBoundingBox();
	virtual void evaluate(const double *aX,double *rY)=0;
	virtual void evaluate(const rdArray<double> &aX,rdArray<double> &rY)=0;
	virtual void evaluate(const rdArray<double> &aX,rdArray<double> &rY,
		const rdArray<int> &aDerivWRT)=0;

//=============================================================================
};	// END class rdVectorFunction
//=============================================================================
//=============================================================================

#endif  // __rdVectorFunction_h__
