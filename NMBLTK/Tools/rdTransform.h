// rdTransform.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2004 Stanford University
// All rights reserved.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdTransform_h__
#define __rdTransform_h__

#include "rdTools.h"
#include "rdObject.h"

class rdMtx;
// CONSTANTS

//=============================================================================
//=============================================================================
/**
 * Class rdTransform is intended to represent transformations for rd platform
 *
 * @version 1.0
 * @author Ayman Habib
 */
class RDTOOLS_API rdTransform: public rdObject
{
public:
	enum AxisName {
		X=0, Y=1, Z=2, NoAxis=-1
	};
	// Translation is not accounted for here in RotationOrder
	// In all cases I've seen so far it's done either first or last
	// the caller routine is reponsible for making up this part of ordering
	// by calling functions in proper order.
	enum RotationOrder {	
		XYZ=0, XZY=1, YXZ=2, YZX=3, ZXY=4, ZYX=5
	};
	enum AnglePreference {
		Radians, Degrees
	};

//=============================================================================
// DATA
//=============================================================================
private:
	/** A 4x4 matrix representing the homogenized transformation */
	double	_matrix4[4][4];
	double	_angles[3];
protected:

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	// Default constructor returns identity transform
	rdTransform();
	// Copy constructor
	rdTransform(const rdTransform &aTransform);
	// Construct a transform to rotate around a vector with specified angle
	rdTransform(const double aAngle, double aVector[3]);
	virtual ~rdTransform();
	rdObject* copy() const;

private:
	void setNull();
	AxisName getRotationAxis(const int i, RotationOrder order);
	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
#ifndef SWIG
	rdTransform& operator=(const rdTransform &aTransform);
#endif
	/** Debugging */
	void printMatrix();
	//--------------------------------------------------------------------------
	// GET AND SET  
	//--------------------------------------------------------------------------
	void getPosition(double pos[3]) const;
	void setPosition(const double pos[3]);
	void getOrientation(double orientation[3]) const;
	void setOrientation(const double orientation[3]);
	void setIdentity();

	void rotate(const double r[3], const AnglePreference preference, const RotationOrder order);
	void rotateX(double r, const AnglePreference preference);
	void rotateY(double r, const AnglePreference preference);
	void rotateZ(double r, const AnglePreference preference);
	void rotateAxis(double r, const AnglePreference preference, const double axis[3]);
	void translateX(const double t);
	void translateY(const double t);
	void translateZ(const double t);
	void translate(const double t[3]);
	//--------------------------------------------------------------------------
	// XML
	//--------------------------------------------------------------------------
	virtual void setupSerializedMembers();

//=============================================================================
};	// END of class rdTransform
//=============================================================================
//=============================================================================

#endif //__rdTransform_h__
