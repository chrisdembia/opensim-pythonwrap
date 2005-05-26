// rdLinearSetPoint.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2002-2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include <NMBLTK/Tools/rdIO.h>
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Tools/rdMtx.h>
#include <NMBLTK/Tools/rdPropertyDbl.h>
#include "rdLinearSetPoint.h"


//=============================================================================
// STATICS
//=============================================================================


//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
rdLinearSetPoint::~rdLinearSetPoint()
{
}
//_____________________________________________________________________________
/**
 * Default constructor.
 */
rdLinearSetPoint::rdLinearSetPoint(int aBodyA,int aBodyB) :
	rdSetPoint(aBodyA,aBodyB),
	_knp(_propKNP.getValueDbl()),
	_knv(_propKNV.getValueDbl())
{
	// NULL
	setNull();
}
//_____________________________________________________________________________
/**
 * Construct an actuator from an XML element.
 *
 * @param aElement XML element.
 */
rdLinearSetPoint::rdLinearSetPoint(DOMElement *aElement) :
	rdSetPoint(aElement),
	_knp(_propKNP.getValueDbl()),
	_knv(_propKNV.getValueDbl())
{
	setNull();
	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aForce Force to be copied.
 */
rdLinearSetPoint::rdLinearSetPoint(const rdLinearSetPoint &aContact) :
	rdSetPoint(aContact),
	_knp(_propKNP.getValueDbl()),
	_knv(_propKNV.getValueDbl())
{
	setNull();

	// STIFFNESS
	setNormalStiffness(aContact.getNormalStiffness());

	// VISCOSITY
	setNormalViscosity(aContact.getNormalViscosity());
}
//_____________________________________________________________________________
/**
 * Copy this actuator and return a pointer to the copy.
 * The copy constructor for this class is used.
 *
 * @return Pointer to a copy of this actuator.
 */
rdObject* rdLinearSetPoint::
copy() const
{
	rdActuator *act = new rdLinearSetPoint(*this);
	return(act);
}
//_____________________________________________________________________________
/**
 * Copy this actuator and modify the copy so that it is consistent
 * with a specified XML element node.
 *
 * The copy is constructed by first using
 * rdForce::rdForce(DOMElement*,int,int) in order to establish the
 * relationship of the rdForce object with the XML node.  Then, the
 * assignment operator is used to set all data members of the copy to the
 * values of this rdForce object.  Finally, the data members of the copy are
 * updated using rdForce::updateObject().
 *
 * @param aElement XML element. 
 * @return Pointer to a copy of this actuator.
 */
rdObject* rdLinearSetPoint::
copy(DOMElement *aElement) const
{
	rdLinearSetPoint *act = new rdLinearSetPoint(aElement);
	*act = *this;
	act->updateFromXMLNode();
	return(act);
}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set the data members of this actuator to their null values.
 */
void rdLinearSetPoint::
setNull()
{
	setupProperties();
	setType("rdLinearSetPoint");
}
//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void rdLinearSetPoint::
setupProperties()
{
	_propKNP.setName("normal_stiffness");
	_propKNP.setValue(0.0);
	_propertySet.append( &_propKNP );

	_propKNV.setName("normal_viscosity");
	_propKNV.setValue(0.0);
	_propertySet.append( &_propKNV );
}


//=============================================================================
// OPERATORS
//=============================================================================
//-----------------------------------------------------------------------------
// ASSIGNMENT
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Assignment operator.
 *
 * @return Reference to this object.
 */
rdLinearSetPoint& rdLinearSetPoint::
operator=(const rdLinearSetPoint &aActuator)
{
	// BASE CLASS
	rdSetPoint::operator=(aActuator);

	// MEMBER VARIABLES
	_knp = aActuator.getNormalStiffness();
	_knv = aActuator.getNormalViscosity();

	return(*this);
}


//=============================================================================
// GET AND SET
//=============================================================================
//-----------------------------------------------------------------------------
// NORMAL IMPEDANCE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the stiffness of the spring in the direction normal to the surface.
 *
 * @return Normal stiffness.
 */
double rdLinearSetPoint::
getInstantaneousNormalStiffness() const
{
	return(_knp);
}
//_____________________________________________________________________________
/**
 * Get the instantaneous viscosity of the contact element in the direction
 * normal to the surface.
 *
 * @return Normal viscosity.
 */
double rdLinearSetPoint::
getInstantaneousNormalViscosity() const
{
	return(_knv);
}

//-----------------------------------------------------------------------------
// STIFFNESS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set normal stiffness.
 *
 * @param aKTP Normal stiffness- must be positive.
 */
void rdLinearSetPoint::
setNormalStiffness(double aKNP)
{
	_knp = aKNP;
	if(_knp<0) _knp=0.0;
}
//_____________________________________________________________________________
/**
 * Get normal stiffness.
 *
 * @return Normal stiffness.
 */
double rdLinearSetPoint::
getNormalStiffness() const
{
	return(_knp);
}

//-----------------------------------------------------------------------------
// VISCOSITY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set normal viscosity.
 *
 * @param aKTV Normal viscosity- must be positive.
 */
void rdLinearSetPoint::
setNormalViscosity(double aKNV)
{
	_knv = aKNV;
	if(_knv<0) _knv=0.0;
}
//_____________________________________________________________________________
/**
 * Get normal viscosity.
 *
 * @return Normal viscosity.
 */
double rdLinearSetPoint::
getNormalViscosity() const
{
	return(_knv);
}


//=============================================================================
// COMPUTATIONS
//=============================================================================
void rdLinearSetPoint::
computeActuation()
{
	// UPDATE SPRING POINTS
	updatePointA();
	updatePointB();
	
	// DISPLACEMENTS AND VELOCITIES
	computeDisplacements();
	computeVelocities();

	// NORMAL FORCE
	double fnp=0.0;
	double fnv=0.0;
	double d = getNormalDistance();
	if(d<=0.0) {
		fnp = -_knp*d;
		fnv = -_knv*getNormalSpeed();
	}
	_fnMag = fnp + fnv;
	rdMtx::Multiply(1,3,&_nA[0],fnp,_fnp);
	rdMtx::Multiply(1,3,&_nA[0],fnv,_fnv);
	rdMtx::Multiply(1,3,&_nA[0],_fnMag,_fn);

	// TANGENTIAL FORCE
	_ftMag = computeTangentialForce(_fnMag,_ft,_dfFric);

	// RESULTANT FORCE
	double fA[3],uA[3];
	rdMtx::Add(1,3,_fn,_ft,fA);
	double f = rdMtx::Normalize(3,fA,uA);
	rdMtx::Multiply(1,3,uA,-1.0,uA);
	if(f==0.0) {
		rdMtx::Add(1,3,_rtA,_rnA,uA);
		rdMtx::Normalize(3,uA,uA);
	}

	// FORCE AND DIRECTION
	setForce(f);
	setForceDirectionA(uA);

	// SPEED
	double v[3];
	rdMtx::Add(1,3,_vnA,_vtA,v);
	_speed = -rdMtx::DotProduct(3,uA,v);

	// BODY B
	computeForceDirectionForBodyB();
}


//=============================================================================
// APPLICATION
//=============================================================================


//=============================================================================
// CHECK
//=============================================================================
//_____________________________________________________________________________
/**
 * Check that this force actuator has a valid set of states.
 */
bool rdLinearSetPoint::
check() const
{
	bool status = rdSetPoint::check();

	return(status);
}


//=============================================================================
// XML
//=============================================================================
//-----------------------------------------------------------------------------
// UPDATE FROM XML NODE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Update this object based on its XML node.
 *
 * This method simply calls rdSetPoint::updateFromXMLNode() and then calls
 * a few methods in this class to ensure that variable members have been
 * set in a consistent manner.
 */
void rdLinearSetPoint::
updateFromXMLNode()
{
	rdSetPoint::updateFromXMLNode();
	setNormalStiffness(_knp);
	setNormalViscosity(_knv);
}	

