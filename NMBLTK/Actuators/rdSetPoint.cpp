// rdSetPoint.cpp
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
#include "rdSetPoint.h"


using namespace std;


//=============================================================================
// STATICS
//=============================================================================
const string rdSetPoint::YP0_NAME = "px";
const string rdSetPoint::YP1_NAME = "py";
const string rdSetPoint::YP2_NAME = "pz";


//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
rdSetPoint::~rdSetPoint()
{
}
//_____________________________________________________________________________
/**
 * Default constructor.
 * rdSetPoint has three pseudo-states, which are the coordinates of contact
 * PointA.  Derived classes should be aware of this.
 *
 * @param aBodyA Contact BodyA.
 * @param aBodyB Contact BodyB.
 * @param aNYP Number of pseudo-states (3, by default).
 */
rdSetPoint::rdSetPoint(int aBodyA,int aBodyB,int aNYP) :
	rdContactForce(aBodyA,aBodyB,aNYP),
	_ktp(_propKTP.getValueDbl()),
	_ktv(_propKTV.getValueDbl()),
	_mu(_propMU.getValueDbl())
{
	setNull();
}
//_____________________________________________________________________________
/**
 * Construct an actuator from an XML node.
 * rdSetPoint has three pseudo-states, which are the coordinates of contact
 * PointA.  Derived classes should be aware of this.
 *
 * @param aElement XML node representing this setpoint object.
 * @param aNYP Number of pseudo-states (3, by default).
 */
rdSetPoint::rdSetPoint(DOMElement *aElement,int aNYP) :
	rdContactForce(aElement,aNYP),
	_ktp(_propKTP.getValueDbl()),
	_ktv(_propKTV.getValueDbl()),
	_mu(_propMU.getValueDbl())
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
rdSetPoint::rdSetPoint(const rdSetPoint &aActuator) :
	rdContactForce(aActuator),
	_ktp(_propKTP.getValueDbl()),
	_ktv(_propKTV.getValueDbl()),
	_mu(_propMU.getValueDbl())
{
	setNull();

	// STIFFNESS
	setTangentialStiffness(aActuator.getTangentialStiffness());

	// VISCOSITY
	setTangentialViscosity(aActuator.getTangentialViscosity());

	// FRICTION
	setFriction(aActuator.getFriction());
}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set the data members of this actuator to their null values.
 */
void rdSetPoint::
setNull()
{
	setType("rdSetPoint");
	setupProperties();

	// FRICTION
	_mu = 0.0;
}
//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void rdSetPoint::
setupProperties()
{
	_propKTP.setName("tangential_stiffness");
	_propKTP.setValue(0.0);
	_propertySet.append( &_propKTP );

	_propKTV.setName("tangential_viscosity");
	_propKTV.setValue(0.0);
	_propertySet.append( &_propKTV );

	_propMU.setName("coefficient_of_friction");
	_propMU.setValue(0.0);
	_propertySet.append( &_propMU );
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
rdSetPoint& rdSetPoint::
operator=(const rdSetPoint &aSetPoint)
{
	// BASE CLASS
	rdContactForce::operator=(aSetPoint);

	// MEMBER VARIABLES
	_mu = aSetPoint.getFriction();
	_ktp = aSetPoint.getTangentialStiffness();
	_ktv = aSetPoint.getTangentialViscosity();

	return(*this);
}


//=============================================================================
// GET AND SET
//=============================================================================
//-----------------------------------------------------------------------------
// PSEUDOSTATES
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the number of pseudostates.
 *
 * @return Number of pseudostates (3 for an rdSetPoint actuator).
 */
int rdSetPoint::
getNYP() const
{
	return(3);
}
//_____________________________________________________________________________
/**
 * Get the name of a pseudostate.\n
 * Valid indices: 0-2
 *
 * @param aIndex Index of the pseudostate whose name is desired.
 * @throws rdException If aIndex is not valid.
 */
const string& rdSetPoint::
getPseudoStateName(int aIndex) const
{
	switch(aIndex) {
	case(0):
		return(YP0_NAME);
	case(1):
		return(YP1_NAME);
	case(2):
		return(YP2_NAME);
	default:
		string msg = "rdSetPoint.setPseudoState: ERR- index out of bounds.\n";
		msg += "Actuator ";
		msg += getName();
		msg += " of type ";
		msg += getType();
		msg += " has 3 pseudostates (indices 0-2 are valid).";
		throw( rdException(msg,__FILE__,__LINE__) );
	}
}
//_____________________________________________________________________________
/**
 * Get the index of a pseudostate of a specified name.\n
 * Valid names: px, py, pz
 *
 * @param aName Name of the pseudostate whose index is desired.
 * @return Index of the specified pseudostate.
 * @throws rdException If aName is not valid.
 */
int rdSetPoint::
getPseudoStateIndex(const string &aName) const
{
	if(aName==YP0_NAME) {
		return(0);
	} else if(aName==YP1_NAME) {
		return(1);
	} else if(aName==YP2_NAME) {
		return(2);
	} else {
		string msg = "rdSetPoint.getPseudoStateIndex: ERR- Actuator ";
		msg += getName();
		msg += " of type ";
		msg += getType();
		msg += " has no pseudostate by the name";
		msg += aName;
		msg += ".\n Valid names are ";
		msg += YP0_NAME + ", " + YP1_NAME + ", " + YP2_NAME + "."; 
		throw( rdException(msg,__FILE__,__LINE__) );
	}
	return(0);
}
//_____________________________________________________________________________
/**
 * Set the current values of the pseudostates.  The pseudo-states are the
 * coordinates of contact PointA.
 *
 * @param aYP Array of pseudostates.  aYP should have a size of 3.
 */
void rdSetPoint::
setPseudoStates(const double aYP[])
{
	setPointA(aYP);
}
//_____________________________________________________________________________
/**
 * Set the value of a pseudostate at a specified index.\n
 * Valid indices:  0-2
 *
 * @param aIndex Index of the pseudostate to be set.
 * @param aValue Value to which to set the pseudostate.
 * @throws rdException If aIndex is not valid.
 */
void rdSetPoint::
setPseudoState(int aIndex,double aValue)
{
	if((aIndex<0)||(aIndex>2)) {
		string msg = "rdSetPoint.setPseudoState: ERR- index out of bounds.\n";
		msg += "Actuator ";
		msg += getName();
		msg += " of type ";
		msg += getType();
		msg += " has 3 pseudostates (indices 0-2 are valid).";
		throw( rdException(msg,__FILE__,__LINE__) );
	}

	double pointA[3];
	getPointA(pointA);
	pointA[aIndex] = aValue;
	setPointA(pointA);
}
//_____________________________________________________________________________
/**
 * Set the value of a pseudostate of a specified name.\n
 * Valid names: px, py, pz
 *
 * @param aName Name of the pseudostate to be set.
 * @param aValue Value to which to set the pseudostate.
 * @throws rdException If aName is not valid.
 */
void rdSetPoint::
setPseudoState(const string &aName,double aValue)
{
	int index = getPseudoStateIndex(aName);
	setPseudoState(index,aValue);
}
//_____________________________________________________________________________
/**
 * Get the current values of the pseudostates.
 *
 * @param rYP Array of pseudostates.  The size of rYP should be 3.
 */
void rdSetPoint::
getPseudoStates(double rYP[]) const
{
	getPointA(rYP);
}
//_____________________________________________________________________________
/**
 * Get the value of a pseudostate at a specified index.\n
 *	Valid Indices: 0-2
 *
 * @param aIndex Index of the desired pseudostate.
 * @return Value of the desired pseudostate.
 * @throws rdException If aIndex is not valid.
 */
double rdSetPoint::
getPseudoState(int aIndex) const
{
	if((aIndex<0)||(aIndex>2)) {
		string msg = "rdSetPoint.setPseudoState: ERR- index out of bounds.\n";
		msg += "Actuator ";
		msg += getName();
		msg += " of type ";
		msg += getType();
		msg += " has 3 pseudostates (indices 0-2 are valid).";
		throw( rdException(msg,__FILE__,__LINE__) );
	}

	double pointA[3];
	getPointA(pointA);
	return(pointA[aIndex]);
}
//_____________________________________________________________________________
/**
 * Get the value of a pseudostate of a specified name.\n
 * Valid names: px, py, pz
 *
 * @param aName Name of the desired pseudostate.
 * @return Value of the desired pseudostate.
 * @throws rdException If aName is not valid.
 */
double rdSetPoint::
getPseudoState(const string &aName) const
{
	int index = getPseudoStateIndex(aName);
	return(getForce());
}

//-----------------------------------------------------------------------------
// TANGENTIAL IMPEDANCE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the stiffness of the spring in the plane tangent to the surface
 * normal.
 *
 * @return Tangent stiffness.
 */
double rdSetPoint::
getInstantaneousTangentialStiffness() const
{
	return _ktp;
}
//_____________________________________________________________________________
/**
 * Get the instantaneous viscosity of the contact element in the plane
 * tangent to the surface normal.
 *
 * @return Tangent viscosity.
 */
double rdSetPoint::
getInstantaneousTangentialViscosity() const
{
	return _ktv;
}

//-----------------------------------------------------------------------------
// STIFFNESS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set tangential stiffness.
 *
 * @param aKTP Tangential stiffness- must be positive.
 */
void rdSetPoint::
setTangentialStiffness(double aKTP)
{
	_ktp = aKTP;
	if(_ktp<0.0) _ktp=0.0;
}
//_____________________________________________________________________________
/**
 * Get tangential stiffness.
 *
 * @return Tangential stiffness.
 */
double rdSetPoint::
getTangentialStiffness() const
{
	//if(_force==0.0) return(0.0);  This line shouldn't be here? -- Clay
	return(_ktp);
}

//-----------------------------------------------------------------------------
// VISCOSITY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set tangential viscosity.
 *
 * @param aKTV Tangential viscosity- must be positive.
 */
void rdSetPoint::
setTangentialViscosity(double aKTV)
{
	_ktv = aKTV;
	if(_ktv<0.0) _ktv=0.0;
}
//_____________________________________________________________________________
/**
 * Get tangential viscosity.
 *
 * @return Tangential viscosity.
 */
double rdSetPoint::
getTangentialViscosity() const
{
	//if(_force==0.0) return(0.0);  This line shouldn't be here? -- Clay
	return(_ktv);
}

//-----------------------------------------------------------------------------
// FRICTION
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set friction coefficient.
 *
 * Sliding occurs when the tangential force exceeds the product of the
 * frictional coefficient and the normal force. 
 *
 * @param aMU Coefficient of Friction.  Must be positive.  If aMU is negative,
 * the fricition coefficient is set to 0.0.  A fricition coefficient greater
 * than 1.0 corresponds to stiction.
 */
void rdSetPoint::
setFriction(double aMU)
{
	_mu = aMU;
	if(_mu<0.0) _mu=0.0;
}
//_____________________________________________________________________________
/**
 * Get friction coefficient.
 *
 * @return Tangent viscosity.
 */
double rdSetPoint::
getFriction() const
{
	return(_mu);
}


//=============================================================================
// COMPUTATIONS
//=============================================================================
//_____________________________________________________________________________
/**
 * Update the pseudostates.
 *
 * Pseudostates are quantities that are not integrated but that depend on
 * the time history of an integration (e.g., spring set points).
 *
 * This method assumes that the model states are up-to-date (i.e., that
 * model->set(t,x,y) or a similar method has been called).
 *
 * rdSetPoint has three pseudostates that are the coordinates of the contact
 * point on BodyA.
 *
 * @see rdSetPoint::setPointA()
 */
void rdSetPoint::
updatePseudoStates()
{
	// COMPUTE ACTUATION
	computeActuation();

	// COMPUTE A NEW SET POINT
	double pA[3];
	bool changed = computeNewSetPoint(_fnMag,pA);
	if(changed) setPointA(pA);
}


//=============================================================================
// APPLICATION
//=============================================================================


//=============================================================================
// UTILITY
//=============================================================================
//_____________________________________________________________________________
/**
 * Compute the tangential contact force exerted on BodyB expressed in the
 * local frame of BodyA.  Note that because of damping, the tangential force
 * vector does not necessarily lie along the line directed from PointA to
 * PointB.
 *
 * This method returns the correction made to the tangential force
 * in order to maintain friction constraints.
 *
 * NOTE that this method neither sets the tangential force or friction
 * correction in base class rdForce (rdForce::_ftA and rdForce::_dfFric).
 * It is left to derived classes to set these member variables.
 *
 * This method does set the values of the elastic and viscous components
 * of the tangent force.  Corrections are not made to these quantities
 * to enforce frictional constraints.  Only the resultant tangential
 * force has been changed to satisfy friction constraints.
 *
 * @param aNormalForce Normal force currently exerted by the contact force.
 * The tangential force is not allowed to exceed the coefficient of
 * friction times the normal force.
 * @param rFT Total tangential force exerted on BodyA expressed in the
 * local frame of BodyA.
 * @param rDFFric Change in the force exerted on BodyA to enforce
 * friction constraints expressed in the local frame of BodyA
 * (i.e., rDFFric = rTangentForce - TangentForce(uncorrected), where
 * |rTangentForce| = mu * aNormalForce).  If no correction is needed
 * rDFFric = {0,0,0}.
 * @return Magnitude of the tangential force.
 */
double rdSetPoint::
computeTangentialForce(double aNormalForce,double rFT[3],
	double rDFFric[3])
{
	// ELASTIC FORCE
	double f = -_ktp * getTangentialDistance();
	rdMtx::Multiply(1,3,_tA,f,_ftp);

	// VISCOUS FORCE
	rdMtx::Multiply(1,3,_vtA,-_ktv,_ftv);

	// RESULTS
	rdMtx::Add(1,3,_ftv,_ftp,rFT);
	rDFFric[0] = rDFFric[1] = rDFFric[2] = 0.0;

	// LIMIT
	// ut = unit vector in the direction of the tangent force
	// df = change in tangential force to enforce friction constraints
	double df;
	double ut[3];
	double limit = _mu * fabs(aNormalForce);
	f = rdMtx::Normalize(3,rFT,ut);
	if(f>limit) {
		df = limit - f;
		f = limit;
		rdMtx::Multiply(1,3,ut,f,rFT);
		rdMtx::Multiply(1,3,ut,df,rDFFric);
	}

	return(f);
}
//_____________________________________________________________________________
/**
 * Compute the setpoint (PointA) so that it is consistent with the
 * displacement of PointB amd the elastic properties of the tangential spring.
 * The viscous properties are not considered in this calculation.
 *
 * @param aNormalForce Normal force.
 * @param rSetPoint Setpoint (PointA) in the local frame of BodyA.
 * @return True if a new set point was computed, False otherwise.
 */
bool rdSetPoint::
computeNewSetPoint(double aNormalForce,double rSetPoint[3]) const
{
	if(rSetPoint==NULL) return(false);

	// CHECK FOR ZERO STIFFNESS
	if(_ktp==0.0) {
		rdMtx::Add(1,3,&_pA[0],_rtA,rSetPoint);
		return(true);
	}

	// FORCE LIMIT
	double limit = _mu * fabs(aNormalForce);

	// ELASTIC FORCE
	double f = _ktp * getTangentialDistance();
	if(f<=limit) return(false);
	f = limit;

	// SETPOINT
	// dt = change in tangential distance
	// _tA = tangent displacement unit vector
	// _dtA = vector change needed to PointA
	// _pA = PointA
	double dt,dtA[3];
	dt = getTangentialDistance() - f/_ktp;
	rdMtx::Multiply(1,3,_tA,dt,dtA);
	rdMtx::Add(1,3,&_pA[0],dtA,rSetPoint);
	return(true);
}


//=============================================================================
// CHECK
//=============================================================================
//_____________________________________________________________________________
/**
 * Check that this force actuator has a valid set of states.
 */
bool rdSetPoint::
check() const
{
	bool status = rdContactForce::check();
	if(!status) return(false);

	// STIFFNESS
	if(_ktp<=0.0) {
		printf("rdSetPoint.check: WARN- tangential stiffness of %s ",getName().c_str());
		printf("is not positive: ktp = %lf\n",_ktp);
	}
	
	// VISCOSITY
	if(_ktv<=0.0) {
		printf("rdSetPoint.check: WARN- tangential viscosity of %s ",
			getName().c_str());
		printf("is not positive: ktv = %lf\n",_ktv);
	}

	// COEFFICIENT OF FRICTION
	if((_mu<0.0)||(_mu>1.0)) {
		printf("rdSetPoint.check: WARN- coeficient of friction of %s ",
			getName().c_str());
		printf("is outside normal range: mu = %lf\n",_mu);
	}

	return(true);
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
void rdSetPoint::
updateFromXMLNode()
{
	rdContactForce::updateFromXMLNode();
	setTangentialStiffness(_ktp);
	setTangentialViscosity(_ktv);
	setFriction(_mu);
}	
