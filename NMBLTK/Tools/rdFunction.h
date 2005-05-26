// rdFunction.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2002 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdFunction_h__
#define __rdFunction_h__


// INCLUDES
#include "rdTools.h"
#include "rdObject.h"
#include "rdPropertyDbl.h"


//=============================================================================
//=============================================================================
/**
 * An abstract class for representing a function.
 *
 * A function is a relation between independent variables and a dependent
 * value such that for any particular set of independent variables there is
 * only one unique dependent value.  Values of the function and its derivatives
 * are obtained by calling the evaluate() method.  The curve may or may not
 * be finite or diferentiable; the evaluate method returns values between
 * rdMath::MINUS_INFINITY and rdMath::PLUS_INFINITY, or it returns rdMath::NAN
 * (not a number) if the curve is not defined.
 * Currently, functions of up to 3 variables (x,y,z) are supported.
 *
 * @author Frank C. Anderson
 */
class RDTOOLS_API rdFunction : public rdObject
{
//=============================================================================
// DATA
//=============================================================================
protected:
	// PROPERTIES
	/** Minimum value of the x independent variable. */
	rdPropertyDbl _propMinX;
	/** Maximum value of the x independent variable. */
	rdPropertyDbl _propMaxX;
	/** Minimum value of the y independent variable. */
	rdPropertyDbl _propMinY;
	/** Maximum value of the y independent variable. */
	rdPropertyDbl _propMaxY;
	/** Minimum value of the z independent variable. */
	rdPropertyDbl _propMinZ;
	/** Maximum value of the z independent variable. */
	rdPropertyDbl _propMaxZ;

	// REFERENCES
	double &_minX;
	double &_maxX;
	double &_minY;
	double &_maxY;
	double &_minZ;
	double &_maxZ;

//=============================================================================
// METHODS
//=============================================================================
public:
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
	rdFunction();
	rdFunction(DOMElement *aElement);
	rdFunction(const rdFunction &aFunction);
	virtual ~rdFunction();
	virtual rdObject* copy() const = 0;
	virtual rdObject* copy(DOMElement *aElement) const = 0;
private:
	void setNull();
	void setupProperties();
	void setEqual(const rdFunction &aFunction);

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
	rdFunction& operator=(const rdFunction &aFunction);

	//--------------------------------------------------------------------------
	// SET AND GET
	//--------------------------------------------------------------------------
public:
	void setMinX(double aMinX);
	double getMinX() const;
	void setMaxX(double aMaxX);
	double getMaxX() const;
	void setMinY(double aMinY);
	double getMinY() const;
	void setMaxY(double aMaxY);
	double getMaxY() const;
	void setMinZ(double aMinZ);
	double getMinZ() const;
	void setMaxZ(double aMaxZ);
	double getMaxZ() const;

	//--------------------------------------------------------------------------
	// EVALUATE
	//--------------------------------------------------------------------------
	virtual void updateBoundingBox() = 0;
	virtual double
		evaluate(int aDerivOrder,double aX=0.0,double aY=0.0,double aZ=0.0) = 0;

//=============================================================================
};	// END class rdFunction
//=============================================================================
//=============================================================================

#endif  // __rdFunction_h__
