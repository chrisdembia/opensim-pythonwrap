// rdLine.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2002 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdLine_h__
#define __rdLine_h__

// INCLUDES
#include "rdTools.h"
#include "rdObject.h"

//=============================================================================
//=============================================================================
/**
 * A class for representing a straight line.
 */
class RDTOOLS_API rdLine : public rdObject
{
//=============================================================================
// DATA
//=============================================================================
private:
	/** Point through which the line passes. */
	double _point[3];
	/** Unit vector specifying the direction of the line. */
	double _direction[3];

//=============================================================================
// METHODS
//=============================================================================
public:
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
	rdLine(double aP0X,double aP0Y,double aP0Z,
		double aP2X,double aP2Y,double aP2Z);
	rdLine(double aPX,double aPY,double aPZ,const double aDirection[3]);
	virtual ~rdLine();
private:
	void setNull();

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
public:
	void setPoint(double aPX,double aPY,double aPZ);
	void getPoint(double rPoint[3]) const;
	void setDirection(const double aDirection[3]);
	void getDirection(double rDirection[3]) const;

	//--------------------------------------------------------------------------
	// ANALYTIC GEOMETRY
	//--------------------------------------------------------------------------
	void evaluate(double aDistance,double rLineValue[3]) const;

//=============================================================================
};	// END class rdLine
//=============================================================================
//=============================================================================

#endif  // __rdLine_h__
