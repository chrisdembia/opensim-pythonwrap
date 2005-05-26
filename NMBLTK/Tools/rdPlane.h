// rdPlane.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2002 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdPlane_h__
#define __rdPlane_h__

// INCLUDES
#include "rdTools.h"
#include "rdObject.h"

class rdLine;

//=============================================================================
//=============================================================================
/**
 * A class for representing a plane.
 */
class RDTOOLS_API rdPlane : public rdObject
{
//=============================================================================
// DATA
//=============================================================================
private:
	/** Point through which the plane passes. */
	double _point[3];
	/** Unit vector normal to the plane. */
	double _normal[3];

//=============================================================================
// METHODS
//=============================================================================
public:
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
	rdPlane(double aPX,double aPY,double aPZ,
		double aP2X,double aP2Y,double aP2Z,
		double aP3X,double aP3Y,double aP3Z);
	rdPlane(double aPX,double aPY,double aPZ,const double aNormal[3]);
	virtual ~rdPlane();
private:
	void setNull();

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
public:
	void setPoint(double aPX,double aPY,double aPZ);
	void getPoint(double rPoint[3]) const;
	void setNormal(const double aNormal[3]);
	void getNormal(double rNormal[3]) const;

	//--------------------------------------------------------------------------
	// ANALYTIC GEOMETRY
	//--------------------------------------------------------------------------
	int computeIntersection(const rdLine *aLine,double rPoint[3]) const;

//=============================================================================
};	// END class rdPlane
//=============================================================================
//=============================================================================

#endif  // __rdPlane_h__
