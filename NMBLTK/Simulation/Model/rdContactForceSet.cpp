// rdContactForceSet.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2002-2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include <NMBLTK/Tools/rdIO.h>
#include <NMBLTK/Tools/rdPropertyObjArray.h>
#include "rdActuator.h"
#include "rdContactForceSet.h"


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
rdContactForceSet::~rdContactForceSet()
{
}
//_____________________________________________________________________________
/**
 * Default constructor.
 */
rdContactForceSet::rdContactForceSet()
{
	// NULL
	setNull();
}
//_____________________________________________________________________________
/**
 * Construct an actuator from file.
 *
 * @param aFileName Name of the file.
 */
rdContactForceSet::rdContactForceSet(const char *aFileName) :
	rdActuatorSet(aFileName)
{
	setNull();
	updateFromXMLNode();
}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set the data members of this actuator to their null values.
 */
void rdContactForceSet::
setNull()
{
	// TYPE
	setType("rdContactForceSet");

	// PROPERTIES
	setupSerializedMembers();
}
//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void rdContactForceSet::
setupSerializedMembers()
{
}


//=============================================================================
// SET OPERATIONS
//=============================================================================
//_____________________________________________________________________________
/**
 * Append a contact object on to the contact force set.  A copy is NOT made.
 *
 * @param aContact Contact force to be appended.
 * @return True if successful; false otherwise.
 */
bool rdContactForceSet::
append(rdContactForce *aContact)
{
	return( rdActuatorSet::append(aContact) );
}
//_____________________________________________________________________________
/**
 * Set the contact force at an index.  A copy is not made.  The contact force
 * previously set a the index is removed and, if the set is the memory owner,
 * deleted.
 *
 * @param aIndex Array index where the contact object is to be stored.  aIndex
 * should be in the range 0 <= aIndex <= getSize();
 * @param aContact Contact force to be set.
 * @return True if successful; false otherwise.
 */
bool rdContactForceSet::
set(int aIndex,rdContactForce *aContact)
{
	return( rdActuatorSet::set(aIndex,aContact) );
}


//=============================================================================
// COMPUTATIONS
//=============================================================================
//_____________________________________________________________________________
/**
 * For each contact, compute all necessary quantities.
 */
void rdContactForceSet::
computeContact()
{
	int i;
	rdActuator *act;
	for(i=0;i<getSize();i++) {
		act = get(i);
		if(act!=NULL) act->computeActuation();
	}
}
//_____________________________________________________________________________
/**
 * Update the pseudostates of all contact forces.  Pseudostates are quantities
 * that are not integrated but that depend on the time history of a
 * simulation (e.g., spring set points).
 */
void rdContactForceSet::
updatePseudoStates()
{
	int i;
	int size = getSize();
	rdActuator *contact;
	for(i=0;i<size;i++) {
		contact = get(i);
		if(contact!=NULL) contact->updatePseudoStates();
	}
}


//=============================================================================
// APPLICATION
//=============================================================================
//_____________________________________________________________________________
/**
 * For each contact, apply the force(s) (or torque(s)) to the model.
 */
void rdContactForceSet::
apply()
{
	int i;
	rdActuator *act;
	for(i=0;i<getSize();i++) {
		act = get(i);
		if(act!=NULL) act->apply();
	}
}


//=============================================================================
// CHECK
//=============================================================================
//_____________________________________________________________________________
/**
 * Check that all contacts are valid.
 */
bool rdContactForceSet::
check() const
{
	bool status=true;

	// LOOP THROUGH CONTACTS
	int i;
	rdActuator *act;
	for(i=0;i<getSize();i++) {
		act = get(i);
		if(act==NULL) continue;
		if(!act->check()) status = false;
	}

	return(status);
}
