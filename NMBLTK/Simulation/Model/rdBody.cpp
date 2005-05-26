// rdBody.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2000 Realistic Dynamics, Inc.
// All rights reserved.
//
// CONFIDENTIAL
//
// The material contain within this file is the sole property of
// Realistic Dynamics, Inc., and may not be read, copied, or distributed
// without the expressed writen consent of Realistic Dynamics, Inc.
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <math.h>
#include "rdBody.h"
#include <NMBLTK/Tools/rdPropertyDbl.h>
#include <NMBLTK/Tools/rdPropertyDblArray.h>


using namespace std;


//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Default constructor.
 */

rdBody::rdBody(double aM,double *aI):
rdVisibleObject(),
_M(_propM.getValueDbl()),
_I(_propI.getValueDblArray()),
_centerOfMass(_propCenterOfMass.getValueDblArray())
{
	setNull();

	// TYPE
	setType("rdBody");

	setMass(aM);
	setInertia(aI);

}
//_____________________________________________________________________________
/**
 * Construct an object from file.
 *
 * The object is constructed from the root element of the XML document.
 * The type of object is the tag name of the XML root element.
 *
 * @param aFileName File name of the document.
 */
rdBody::rdBody(const string &aFileName):
rdVisibleObject(aFileName),
_M(_propM.getValueDbl()),
_I(_propI.getValueDblArray()),
_centerOfMass(_propCenterOfMass.getValueDblArray())
{
	setNull();
	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aBody Body to copy.
 */
rdBody::rdBody(const rdBody &aBody) :
rdVisibleObject(aBody),
_M(_propM.getValueDbl()),
_I(_propI.getValueDblArray()),
_centerOfMass(_propCenterOfMass.getValueDblArray())
{
	setNull();

	// ASSIGN
	*this = aBody;
}

//_____________________________________________________________________________
/**
 * Construct a Body from an XML Element.
 *
 * @param aElement XML element.
 */
rdBody::rdBody(DOMElement *aElement) :
rdVisibleObject(aElement),
_M(_propM.getValueDbl()),
_I(_propI.getValueDblArray()),
_centerOfMass(_propCenterOfMass.getValueDblArray())
{
	setNull();

	updateFromXMLNode();
}

//_____________________________________________________________________________
/**
 * Destructor.
 */
rdBody::~rdBody()
{

}
//_____________________________________________________________________________
/**
 * Another incarnation of copy that's virtual.
 *
 * @param aElement XMLnode to construct body from.
 */

rdObject *rdBody::
copy() const
{
	return(new rdBody(*this));
}
//_____________________________________________________________________________
/**
 * Create object from DOMElement.
 *
 * @param aElement XMLnode to construct body from.
 */

rdObject* rdBody::
copy(DOMElement *aElement) const
{
	rdBody *b = new rdBody(aElement);
	*b = *this;
	b->updateFromXMLNode();
	return(b);
}

//_____________________________________________________________________________
/**
 * Set all member variables to their null or default values.
 */
void rdBody::
setNull()
{

	setupProperties();

}
//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void rdBody::
setupProperties()
{
	rdArray<double> zeroVector(0.0, 6);
	rdArray<double> zero3(0.0, 3);	
	
	_propertySet.append(&_propM);
	_propM.setName("Mass");
	_propM.setValue(1.0);

	_propertySet.append(&_propI);
	_propI.setName("Inertia");
	_propI.setValue(zeroVector);

	_propertySet.append(&_propCenterOfMass);
	_propCenterOfMass.setName("CenterOfMass");
	_propCenterOfMass.setValue(zero3);

}


//=============================================================================
// OPERATORS
//=============================================================================
//-----------------------------------------------------------------------------
// ASSIGNMENT
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Assign this object to the values of another.
 *
 * @return Reference to this object.
 */
rdBody& rdBody::
operator=(const rdBody &aObject)
{
	// BASE CLASS
	rdVisibleObject::operator=(aObject);

	// Class Members
	_M = (aObject._M);
	_I = (aObject._I);

	_centerOfMass = aObject._centerOfMass;

	return(*this);
}

//=============================================================================
// GET AND SET
//=============================================================================
//-----------------------------------------------------------------------------
// MASS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the mass.
 * The mass must be greater than or equal to zero.
 */
void rdBody::
setMass(double aM)
{
	_M = fabs(aM);
}
//_____________________________________________________________________________
/**
 * Get the mass.
 */
double rdBody::
getMass()
{
	return(_M);
}

//-----------------------------------------------------------------------------
// INERTIA SCALARS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the inertia scalars.
 *
 * The argument aI is assumed to point to a array of values which has as its
 * first six values I1, I2, I3, I12, I23, I31.
 *
 * If aI is NULL, then the inertia scalars are set to represent the inertia
 * matrix for a sphere of uniform density of the same mass as the body
 */
void rdBody::
setInertia(double *aI)
{
	int i;
	if(aI==NULL) {
		double I = (_M)*2.0/5.0;
		for(i=0;i<3;i++) _I[i] = I;
		for(i=3;i<6;i++) _I[i] = 0.0;
	} else {
		for(i=0;i<6;i++) _I[i] = aI[i];
	}
}
//_____________________________________________________________________________
/**
 * Set the inertia scalars.
 *
 * aI1, aI2, aI3 correspond to the moments of inertia.  It is assumed that
 * the products of inertia are 0.0.
 */
void rdBody::
setInertia(double aI1,double aI2,double aI3)
{
	_I[0] = aI1;
	_I[1] = aI2;
	_I[2] = aI3;
	_I[3] = 0.0;
	_I[4] = 0.0;
	_I[5] = 0.0;
}
//_____________________________________________________________________________
/**
 * Set the inertia scalars.
 */
void rdBody::
setInertia(double aI1,double aI2,double aI3,
	double aI12,double aI23,double aI31)
{
	_I[0] = aI1;
	_I[1] = aI2;
	_I[2] = aI3;
	_I[3] = aI12;
	_I[4] = aI23;
	_I[5] = aI31;
}
//_____________________________________________________________________________
/**
 * Get the inertia scalars.
 *
 * The argument aI is filled with the values aI1, aI2, aI3, aI12, aI23, aI31.
 */
void rdBody::
getInertia(double aI[6])
{
	int i;
	for(i=0;i<6;i++) aI[i]=_I[i];
}
//_____________________________________________________________________________
/**
 * Get the inertia scalars.
 *
 * The full scalar inertia matrix is contructed.
 */
void rdBody::
getInertia(double aI[3][3])
{
	// MOMENTS
	aI[0][0] = _I[0];
	aI[1][1] = _I[1];
	aI[2][2] = _I[2];

	// PRODUCTS
	aI[0][1] = aI[1][0] = _I[3];
	aI[1][2] = aI[2][1] = _I[4];
	aI[2][0] = aI[0][2] = _I[5];
}
//_____________________________________________________________________________
/**
 * Set Center of mass relative to geometry's CoordinateSystem.
 *
 */
void rdBody::
setCenterOfMass(const double aCenterOfMass[3])
{
	for(int i=0; i < 3; i++)
		_centerOfMass[i]=(aCenterOfMass[i]);
}
//_____________________________________________________________________________
/**
 * Get Center of mass relative to geometry's CoordinateSystem.
 *
 */
void rdBody::
getCenterOfMass(double aCenterOfMass[3]) const
{
	for(int i=0; i < 3; i++)
		aCenterOfMass[i] = _centerOfMass[i];
}
//--------------------------------------------------------------------------
// SCALING
//--------------------------------------------------------------------------
void rdBody::
scaleBy(const double aScaleFactors[3])
{
	// Scale center of mass
	for(int i=0; i < 3; i++)
		_centerOfMass[i] *= aScaleFactors[i];
	// Compute mass_scale based on Volume, assume fixed density
	double massScale = aScaleFactors[0]*aScaleFactors[1]*aScaleFactors[2];
	// Scale mass
	_M *= massScale;
	// Scale inertia vector
	double inertia[3][3];
	getInertia(inertia);
	for (int j=0;j<3;j++) {
		for (int k=0;k<3;k++) {
			inertia[j][k]*= massScale*aScaleFactors[j]*aScaleFactors[k];
		}
	}
	setInertia(inertia[0][0], inertia[1][1], inertia[2][2],
				 inertia[0][1],  inertia[1][2],  inertia[2][0]);
	// Scale geometry for display purposes
	setScaleFactors(aScaleFactors);


}
