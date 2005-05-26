// rdFunctionSet.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2002, 2003 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


#ifndef __rdFunctionSet_h__
#define __rdFunctionSet_h__


// INCLUDES
#include "rdTools.h"
#include "rdObject.h"
#include "rdPropertyDbl.h"
#include "rdFunction.h"
#include "rdSet.h"

template class RDTOOLS_API rdSet<rdFunction>;

//=============================================================================
//=============================================================================
/**
 * A class for holding a set of functions.
 *
 * @see rdFunction
 * @author Frank C. Anderson
 */
class RDTOOLS_API rdFunctionSet : public rdSet<rdFunction>
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
	rdFunctionSet();
	rdFunctionSet(const std::string &aFileName);
	virtual ~rdFunctionSet();
private:
	void setNull();
	void setupProperties();

	//--------------------------------------------------------------------------
	// SET AND GET
	//--------------------------------------------------------------------------
public:
	void setMinX(double aMinX);
	double getMinX();
	void setMaxX(double aMaxX);
	double getMaxX();
	void setMinY(double aMinY);
	double getMinY();
	void setMaxY(double aMaxY);
	double getMaxY();
	void setMinZ(double aMinZ);
	double getMinZ();
	void setMaxZ(double aMaxZ);
	double getMaxZ();

	//--------------------------------------------------------------------------
	// EVALUATION
	//--------------------------------------------------------------------------
	virtual void updateSetBoundingBox();
	virtual void updateBoundingBox();
	virtual void updateBoundingBox(int aIndex);
	virtual double
		evaluate(int aIndex,int aDerivOrder,
		double aX=0.0,double aY=0.0,double aZ=0.0) const;
	virtual void
		evaluate(rdArray<double> &rValues,int aDerivOrder,
		double aX=0.0,double aY=0.0,double aZ=0.0) const;

//=============================================================================
};	// END class rdFunctionSet
//=============================================================================
//=============================================================================

#endif  // __rdFunctionSet_h__
