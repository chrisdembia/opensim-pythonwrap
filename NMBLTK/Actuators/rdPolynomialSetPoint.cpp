// rdPolynomialSetPoint.cpp
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
#include <RD/Tools/rdIO.h>
#include <RD/Tools/rdMath.h>
#include <RD/Tools/rdMtx.h>
#include <RD/Tools/rdPropertyDbl.h>
#include "rdPolynomialSetPoint.h"


using namespace std;


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
rdPolynomialSetPoint::~rdPolynomialSetPoint()
{
}
//_____________________________________________________________________________
/**
 * Default constructor.
 */
rdPolynomialSetPoint::rdPolynomialSetPoint(int aBodyA,int aBodyB) :
	rdSetPoint(aBodyA,aBodyB),
	_kNP(_propKNP.getValueDbl()),
	_kNV(_propKNV.getValueDbl()),
	_powNP(_propPowerNP.getValueDbl()),
	_powNV(_propPowerNV.getValueDbl())
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
rdPolynomialSetPoint::rdPolynomialSetPoint(DOMElement *aElement) :
	rdSetPoint(aElement),
	_kNP(_propKNP.getValueDbl()),
	_kNV(_propKNV.getValueDbl()),
	_powNP(_propPowerNP.getValueDbl()),
	_powNV(_propPowerNV.getValueDbl())
{
	setNull();
	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aContact Contact to be copied.
 */
rdPolynomialSetPoint::rdPolynomialSetPoint(const rdPolynomialSetPoint &aContact) :
	rdSetPoint(aContact),
	_kNP(_propKNP.getValueDbl()),
	_kNV(_propKNV.getValueDbl()),
	_powNP(_propPowerNP.getValueDbl()),
	_powNV(_propPowerNV.getValueDbl())
{
	setNull();

	// STIFFNESS
	setNormalStiffnessConstant(aContact.getNormalStiffnessConstant());

	// VISCOSITY
	setNormalViscosityConstant(aContact.getNormalViscosityConstant());

	// POWERS
	setStiffnessPower(aContact.getStiffnessPower());
	setViscosityPower(aContact.getViscosityPower());
}
//_____________________________________________________________________________
/**
 * Copy this actuator and return a pointer to the copy.
 * The copy constructor for this class is used.
 *
 * @return Pointer to a copy of this actuator.
 */
rdObject* rdPolynomialSetPoint::
copy() const
{
	rdActuator *act = new rdPolynomialSetPoint(*this);
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
rdObject* rdPolynomialSetPoint::
copy(DOMElement *aElement) const
{
	rdPolynomialSetPoint *act = new rdPolynomialSetPoint(aElement);
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
void rdPolynomialSetPoint::
setNull()
{
	setupProperties();
	setType("rdPolynomialSetPoint");

	// MEMBER VARIABLES
	_kNP = 0.0;
	_kNV = 0.0;
	_powNP = 1.0;
	_powNV = 1.0;
}
//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void rdPolynomialSetPoint::
setupProperties()
{
	_propKNP.setName("normal_stiffness");
	_propKNP.setValue(0.0);
	_propertySet.append( &_propKNP );

	_propKNV.setName("normal_viscosity");
	_propKNV.setValue(0.0);
	_propertySet.append( &_propKNV );

	_propPowerNP.setName("stiffness_power");
	_propPowerNP.setValue(0.0);
	_propertySet.append( &_propPowerNP );

	_propPowerNV.setName("viscosity_power");
	_propPowerNV.setValue(0.0);
	_propertySet.append( &_propPowerNV );
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
 * @param aActuator Actuator to which to set this actuator equal.
 * @return Reference to this object.
 */
rdPolynomialSetPoint& rdPolynomialSetPoint::
operator=(const rdPolynomialSetPoint &aActuator)
{
	// BASE CLASS
	rdSetPoint::operator=(aActuator);

	// MEMBER VARIABLES
	_kNP = aActuator.getNormalStiffnessConstant();
	_kNV = aActuator.getNormalViscosityConstant();
	_powNP = aActuator.getStiffnessPower();
	_powNV = aActuator.getViscosityPower();

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
double rdPolynomialSetPoint::
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
double rdPolynomialSetPoint::
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
void rdPolynomialSetPoint::
setNormalStiffnessConstant(double aKNP)
{
	_kNP = aKNP;
	if(_kNP<0) _kNP=0.0;
}
//_____________________________________________________________________________
/**
 * Get normal stiffness.
 *
 * @return Normal stiffness.
 */
double rdPolynomialSetPoint::
getNormalStiffnessConstant() const
{
	return(_kNP);
}

//-----------------------------------------------------------------------------
// VISCOSITY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set normal viscosity.
 *
 * @param aKNV Normal viscosity- must be positive.
 */
void rdPolynomialSetPoint::
setNormalViscosityConstant(double aKNV)
{
	_kNV = aKNV;
	if(_kNV<0) _kNV=0.0;
}
//_____________________________________________________________________________
/**
 * Get normal viscosity.
 *
 * @return Normal viscosity.
 */
double rdPolynomialSetPoint::
getNormalViscosityConstant() const
{
	return(_kNV);
}

//-----------------------------------------------------------------------------
// STIFFNESS POWER
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the power to which the normal displacement of the spring is raised.
 *
 * @param aPower Power to which the normal displacement of the spring is
 * raised.
 */
void rdPolynomialSetPoint::
setStiffnessPower(double aPower)
{
	_powNP = aPower;
}
//_____________________________________________________________________________
/**
 * Get the power to which the normal displacement of the spring is raised.
 *
 * @return Power to which the normal displacement of the spring is raised.
 */
double rdPolynomialSetPoint::
getStiffnessPower() const
{
	return(_powNP);
}

//-----------------------------------------------------------------------------
// VISCOSITY POWER
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the power to which the normal velocity of the spring is raised.
 *
 * @param aPower Power to which the normal velocity of the spring is raised.
 */
void rdPolynomialSetPoint::
setViscosityPower(double aPower)
{
	_powNV = aPower;
}
//_____________________________________________________________________________
/**
 * Get the power to which the normal velocity of the spring is raised.
 *
 * @return Power to which the normal velocity of the spring is raised.
 */
double rdPolynomialSetPoint::
getViscosityPower() const
{
	return(_powNV);
}



//=============================================================================
// COMPUTATIONS
//=============================================================================
//_____________________________________________________________________________
/**
 * Compute the spring forces.
 *
 * @todo The instantaneous viscosities and stiffnesses are no longer correct
 * because of the addition of the "c" coefficient.
 */
void rdPolynomialSetPoint::
computeActuation()
{
	// UPDATE SPRING POINTS
	updatePointA();
	updatePointB();
	
	// DISPLACEMENTS AND VELOCITIES
	computeDisplacements();
	computeVelocities();

	// NORMAL FORCE
	// Stiffness term
	double fnp = 0.0;
	double d = getNormalDistance();
	if(d<0.0) {
		d = fabs(d);
		fnp = _kNP * pow(d,_powNP);
	}
	// Viscosity term
	double fnv = 0.0;
	double fnvTmp = 0.0;
	double s = getNormalSpeed();
	if((fnp>0.0)&&(_powNV>0.0)) {
		fnvTmp = _kNV*pow(fabs(s),_powNV);
		fnvTmp = rdMath::CopySign(fnvTmp,-s);
		double c = rdMath::SigmaUp(4.0,20.0,fnp);
		fnv = c * fnvTmp;
		//cout<<"fnp,c,fnv="<<fnp<<", "<<c<<", "<<fnv<<endl;
	}
	_fnMag = fnp + fnv;
	if(_fnMag<0.0) _fnMag = 0.0;
	rdMtx::Multiply(1,3,&_nA[0],fnp,_fnp);
	rdMtx::Multiply(1,3,&_nA[0],fnv,_fnv);
	rdMtx::Multiply(1,3,&_nA[0],_fnMag,_fn);

	// INSTANTANEOUS NORMAL STIFFNESS
	_knp = 0.0;
	if(fnp!=0.0) {
		_knp = _kNP*_powNP*pow(d,_powNP-1.0)*(1.0 + fnvTmp);
	}

	// INSTANTANEOUS NORMAL VISCOSITY
	_knv = 0.0;
	if(fnp!=0.0) {
		_knv = fnp*_kNV*_powNV*pow(fabs(s),_powNV-1.0);
	}

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
bool rdPolynomialSetPoint::
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
 * This method simply calls rdObject::updateFromXMLNode() and then calls
 * a few methods in this class to ensure that variable members have been
 * set in a consistent manner.
 */
void rdPolynomialSetPoint::
updateFromXMLNode()
{
	rdSetPoint::updateFromXMLNode();

	setNormalStiffnessConstant(_kNP);
	setNormalViscosityConstant(_kNV);
	setStiffnessPower(_powNP);
	setViscosityPower(_powNV);
}	

