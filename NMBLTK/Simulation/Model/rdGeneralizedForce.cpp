// rdGeneralizedForce.cpp
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
#include <RD/Tools/rdPropertyInt.h>
#include "rdGeneralizedForce.h"


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
rdGeneralizedForce::~rdGeneralizedForce()
{
	if(_utmp!=NULL) { delete[] _utmp;  _utmp=NULL; }
}
//_____________________________________________________________________________
/**
 * Default constructor.
 */
rdGeneralizedForce::rdGeneralizedForce(int aQID,int aNX,int aNY,int aNYP) :
	rdActuator(aNX,aNY,aNYP),
	_qID(_propQID.getValueInt())
{
	// NULL
	setNull();

	// MEMBER VARIABLES
	_qID = aQID;
}
//_____________________________________________________________________________
/**
 * Construct the actuator from an XML element.
 *
 * @param aElement XML element.
 * @param aNX Number of controls.
 * @param aNY Number of states.
 * @param aNYP Number of pseudo-states.
 */
rdGeneralizedForce::
rdGeneralizedForce(DOMElement *aElement,int aNX,int aNY,int aNYP):
	rdActuator(aNX,aNY,aNYP,aElement),
	_qID(_propQID.getValueInt())
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
rdGeneralizedForce::rdGeneralizedForce(const rdGeneralizedForce &aGenForce) :
	rdActuator(aGenForce),
	_qID(_propQID.getValueInt())
{
	setNull();
	setQID(aGenForce.getQID());
}
//_____________________________________________________________________________
/**
 * Copy this actuator and return a pointer to the copy.
 * The copy constructor for this class is used.
 *
 * @return Pointer to a copy of this actuator.
 */
rdObject* rdGeneralizedForce::
copy() const
{
	rdActuator *act = new rdGeneralizedForce(*this);
	return(act);
}
//_____________________________________________________________________________
/**
 * Copy this actuator and modify the copy so that it is consistent
 * with a specified XML element node.
 *
 * The copy is constructed by first using
 * rdGeneralizedForce::rdGeneralizedForce(DOMElement*,int,int) in order to establish the
 * relationship of the rdGeneralizedForce object with the XML node.  Then, the
 * assignment operator is used to set all data members of the copy to the
 * values of this rdGeneralizedForce object.  Finally, the data members of the copy are
 * updated using rdGeneralizedForce::updateFromXMLNode().
 *
 * @param aElement XML element. 
 * @return Pointer to a copy of this actuator.
 */
rdObject* rdGeneralizedForce::
copy(DOMElement *aElement) const
{
	rdGeneralizedForce *act = new
		rdGeneralizedForce(aElement,getNX(),getNY(),getNYP());
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
void rdGeneralizedForce::
setNull()
{
	setType("rdGeneralizedForce");
	setupProperties();

	// APPLIES FORCE
	_appliesForce = true;

	// MEMBER VARIABLES
	_utmp = NULL;
	_qID = -1;
}
//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void rdGeneralizedForce::
setupProperties()
{
	_propQID.setName("QID");
	_propQID.setValue(-1);
	_propertySet.append( &_propQID );
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
 * @return  aQID ID (or number, or index) of the generalized coordinate.
 */
rdGeneralizedForce& rdGeneralizedForce::
operator=(const rdGeneralizedForce &aGenForce)
{
	// BASE CLASS
	rdActuator::operator =(aGenForce);

	// MEMBER VARIABLES
	setQID(aGenForce.getQID());

	return(*this);
}


//=============================================================================
// GET AND SET
//=============================================================================
//-----------------------------------------------------------------------------
// QID
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the generalized coordinate to which the generalized force is applied.
 *
 * @param aQID ID (or number, or index) of the generalized coordinate.
 */
void rdGeneralizedForce::
setQID(int aQID)
{
	_qID = aQID;
}
//_____________________________________________________________________________
/**
 * Get the ID of the generalized coordinate to which the generalized force
 * is applied.
 *
 * @param aID Body ID.
 */
int rdGeneralizedForce::
getQID() const
{
	return(_qID);
}


//=============================================================================
// COMPUTATIONS
//=============================================================================
//_____________________________________________________________________________
/**
 * Compute all quantities necessary for applying the actuator force to the
 * model.
 */
void rdGeneralizedForce::
computeActuation()
{
	if(_model==NULL) return;

	// SPEED
	_speed = _model->getSpeed(_qID);

	// FORCE
	double force = getControl(0) * _optimalForce;
	setForce(force);
}


//=============================================================================
// APPLICATION
//=============================================================================
//_____________________________________________________________________________
/**
 * Apply the actuator force to BodyA and BodyB.
 */
void rdGeneralizedForce::
apply()
{
	if(_model==NULL) return;
	if(isQIDValid()) _model->applyGeneralizedForce(_qID,_force);
}


//=============================================================================
// CHECK
//=============================================================================
//_____________________________________________________________________________
/**
 * Check that this generalized force actuator is valid.
 *
 * @return True if valid, false if invalid.
 */
bool rdGeneralizedForce::
check() const
{
	if(!rdActuator::check()) return(false);

	// QID
	if(!isQIDValid()) {
		printf("rdGeneralizedForce.check: ERROR- %s actuates ",
			getName().c_str());
		printf("an invalid generalized coordinate (%d).\n",getQID());
		return(false);
	}

	return(true);
}
//_____________________________________________________________________________
/**
 * Is the.
 */
bool rdGeneralizedForce::
isQIDValid() const
{
	if(_model==NULL) return(false);
	if((_qID>=0)&&(_qID<_model->getNU())) return(true);
	return(false);
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
void rdGeneralizedForce::
updateFromXMLNode()
{
	rdActuator::updateFromXMLNode();
	setQID(_qID);
	setOptimalForce(_optimalForce);
}	

