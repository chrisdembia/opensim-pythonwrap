// rdContactForceSet.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2002-2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdContactForceSet_h__
#define __rdContactForceSet_h__

#include "rdModel.h"
#include "rdActuatorSet.h"
#include "rdContactForce.h"


//=============================================================================
//=============================================================================
/**
 * A class for holding and managing a set of contacts for a model.  A contact
 * is distinguished from a general actuator in that it has no states and
 * no controls.  However, a contact can have pseudostates (variables that
 * are not only a function of the states, but also of the time history
 * of the states).
 *
 * @author Frank C. Anderson
 * @version 1.0
 * @todo Implement a getNY() method.  Contact forces could have states, just
 * no controls.
 */
class RDSIMULATION_API rdContactForceSet : public rdActuatorSet 
{
//=============================================================================
// MEMBERS
//=============================================================================
protected:

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdContactForceSet();
	rdContactForceSet(const char *aFileName);
	virtual ~rdContactForceSet();
private:
	void setNull();
	void setupSerializedMembers();

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
public:
	// CONTACT
	bool append(rdContactForce *aContact);
	bool set(int aIndex,rdContactForce *aContact);

	//--------------------------------------------------------------------------
	// COMPUTATIONS
	//--------------------------------------------------------------------------
	void computeContact();
	void updatePseudoStates();

	//--------------------------------------------------------------------------
	// APPLICATION
	//--------------------------------------------------------------------------
	void apply();

	//--------------------------------------------------------------------------
	// CHECK
	//--------------------------------------------------------------------------
	bool check() const;

//=============================================================================
};	// END of class rdContactForceSet
//=============================================================================
//=============================================================================


#endif // __rdContactForceSet_h__


