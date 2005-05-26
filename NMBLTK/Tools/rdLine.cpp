// rdLine.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2002 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


#include "rdMath.h"
#include "rdMtx.h"
#include "rdLine.h"


//=============================================================================
// STATIC VARIABLES
//=============================================================================


//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
rdLine::~rdLine()
{
}

//_____________________________________________________________________________
/**
 * Construct a line from two points (P and P2).
 *
 * Point P is kept as the point through which the line passes, and P2 is used
 * to compute the direction of the line.  The direction of the line
 * points from P to P2.
 *
 * @param aPX X component of a point through which the line passes.
 * @param aPY Y component of a point through which the line passes.
 * @param aPZ Z component of a point through which the line passes.
 * @param aP2X X component of a second point through which the line passes.
 * @param aP2Y Y component of a second point through which the line passes.
 * @param aP2Z Z component of a second point through which the line passes.
 * @param aDirection Direction of the line specified as a unit vector.
 */
rdLine::rdLine(double aPX,double aPY,double aPZ,
					double aP2X,double aP2Y,double aP2Z)
{
	setNull();

	// TYPE
	setType("rdLine");

	// COMPUTE DIRECTION
	double direction[3];
	direction[0] = aP2X - aPX;
	direction[1] = aP2Y - aPY;
	direction[2] = aP2Z - aPZ;

	// MEMBER VARIABLES
	setPoint(aPX,aPY,aPZ);
	setDirection(_direction);
}

//_____________________________________________________________________________
/**
 * Construct a line from a point and a direction.
 *
 * @param aPX X component of a point through which the line passes.
 * @param aPY Y component of a point through which the line passes.
 * @param aPZ Z component of a point through which the line passes.
 * @param aDirection Direction of the line specified as a unit vector.
 */
rdLine::rdLine(double aPX,double aPY,double aPZ,const double aDirection[3])
{
	setNull();

	// TYPE
	setType("rdLine");

	// MEMBER VARIABLES
	setPoint(aPX,aPY,aPZ);
	setDirection(aDirection);
}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set NULL values for all member variables.
 */
void rdLine::
setNull()
{
	// POINT
	_point[0] = _point[1] = _point[2] = 0.0;

	// DIRECTION
	_direction[0] = 1.0;
	_direction[1] = 0.0;
	_direction[2] = 0.0;
}


//=============================================================================
// SET / GET
//=============================================================================
//-----------------------------------------------------------------------------
// POINT
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the point that the line passes through.
 *
 * @param aPX X component of a point through which the line passes.
 * @param aPY Y component of a point through which the line passes.
 * @param aPZ Z component of a point through which the line passes.
 */
void rdLine::
setPoint(double aPX,double aPY,double aPZ)
{
	_point[0] = aPX;
	_point[1] = aPY;
	_point[2] = aPZ;
}
//_____________________________________________________________________________
/**
 * Get the point that the line passes through.
 *
 * @param rPoint Point that the line passes through.
 */
void rdLine::
getPoint(double rPoint[3]) const
{
	if(rPoint==NULL) return;

	// POINT
	rPoint[0] = _point[0];
	rPoint[1] = _point[1];
	rPoint[2] = _point[2];
}

//-----------------------------------------------------------------------------
// DIRECTION
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the direction of the line.
 *
 * @param aDirection Direction of the line.
 */
void rdLine::
setDirection(const double aDirection[3])
{
	if(aDirection==NULL) return;

	// POINT
	_direction[0] = aDirection[0];
	_direction[1] = aDirection[1];
	_direction[2] = aDirection[2];

	// NORMALIZED
	double mag = rdMtx::Normalize(3,_direction,_direction);

	// ERROR CHECK
	if(mag<rdMath::ZERO) {
		printf("rdPlane.setNormal: WARN- plane normal is zero or very small.\n");
		printf("\tPlane normal may be ill defined.\n");
	}
}
//_____________________________________________________________________________
/**
 * Get the direction of the line.
 *
 * @param aDirection Direction of the line.
 */
void rdLine::
getDirection(double rDirection[3]) const
{
	if(rDirection==NULL) return;

	// POINT
	rDirection[0] = _direction[0];
	rDirection[1] = _direction[1];
	rDirection[2] = _direction[2];
}


//=============================================================================
// ANALYTIC GEOMETRY
//=============================================================================
//-----------------------------------------------------------------------------
// EVALUATE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Evaluate the line at a specified distance away from the specified
 * point of the line:
 *
 *    value = point + distance * direction
 *
 * @param aDistance Distance away from the specified point of this line
 * (see setPoint()).  aDistance may be positive or negative.
 * @param aValue Point value of the line at distance aDistance.
 */
void rdLine::
evaluate(double aDistance,double aValue[3]) const
{
	if(aValue==NULL) return;
	rdMtx::Multiply(1,3,_direction,aDistance,aValue);
	rdMtx::Add(1,3,_point,aValue,aValue);
}
