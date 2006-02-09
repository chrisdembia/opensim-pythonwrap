// rdDerivCallback.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2002, 2003 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include "rdDerivCallback.h"


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
rdDerivCallback::~rdDerivCallback()
{
}

//_____________________________________________________________________________
/**
 * Default constructor.
 *
 * @param aModel Model to which the callback mthods apply.
 */
rdDerivCallback::rdDerivCallback(rdModel *aModel) :
	rdCallback(aModel)
{
	setNull();
}

//_____________________________________________________________________________
/**
 * Copy Constructor.
 *
 */
rdDerivCallback::rdDerivCallback(const rdDerivCallback &aDerivCallback):
rdCallback(aDerivCallback)
{
	setNull();
	*this = aDerivCallback;
}

//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set NULL values for member variables.
 */
void rdDerivCallback::
setNull()
{
	setType("rdDerivCallback");
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
rdDerivCallback& rdDerivCallback::
operator=(const rdDerivCallback &aObject)
{
	// BASE CLASS
	rdCallback::operator=(aObject);

	return(*this);
}

//=============================================================================
// GET AND SET
//=============================================================================


//=============================================================================
// CALLBACKS
//=============================================================================
//_____________________________________________________________________________
/**
 * This method is intended to be called from rdModel::deriv() after the
 * states of a model have been set (e.g., after rdModel::set() or
 * rdModel::setStates()).
 *
 * Override this method in derived classes.
 *
 * @param aT Current time in the simulation.
 * @param aX Current controls of the model.
 * @param aY Current states of the model
 */
void rdDerivCallback::
set(double aT,double *aX,double *aY)
{
	//printf("rdDerivCallback.set: %s.\n",getName());
}
//_____________________________________________________________________________
/**
 * This method is intended to be called from rdModel::deriv() after 
 * contact quantities have been computed (e.g., after
 * rdModel::computeContact()).
 *
 * Override this method in derived classes.
 *
 * @param aT Current time in the simulation.
 * @param aX Current controls of the model.
 * @param aY Current states of the model
 */
void rdDerivCallback::
computeContact(double aT,double *aX,double *aY)
{
	//printf("rdDerivCallback.computeContact: %s.\n",getName());
}
//_____________________________________________________________________________
/**
 * This method is intended to be called from rdModel::deriv() after 
 * contact forces have been applied (e.g., after
 * rdModel::applyContactForces()).
 *
 * Override this method in derived classes.
 *
 * @param aT Current time in the simulation.
 * @param aX Current controls of the model.
 * @param aY Current states of the model
 */
void rdDerivCallback::
applyContact(double aT,double *aX,double *aY)
{
	//printf("rdDerivCallback.applyContact: %s.\n",getName());
}
//_____________________________________________________________________________
/**
 * This method is intended to be called from rdModel::deriv() after 
 * actuation quantities have been computed (e.g., after
 * rdModel::computeActuation()).
 *
 * Override this method in derived classes.
 *
 * @param aT Current time in the simulation.
 * @param aX Current controls of the model.
 * @param aY Current states of the model
 */
void rdDerivCallback::
computeActuation(double aT,double *aX,double *aY)
{
	//printf("rdDerivCallback.computeActuation: %s.\n",getName());
}
//_____________________________________________________________________________
/**
 * This method is intended to be called from rdModel::deriv() after 
 * actuator forces have been applied (e.g., after
 * rdModel::applyActuatorForces()).
 *
 * Override this method in derived classes.
 *
 * @param aT Current time in the simulation.
 * @param aX Current controls of the model.
 * @param aY Current states of the model
 */
void rdDerivCallback::
applyActuation(double aT,double *aX,double *aY)
{
	//printf("rdDerivCallback.applyActuation: %s.\n",getName());
}
//_____________________________________________________________________________
/**
 * This method is intended to be called from rdModel::deriv() after 
 * derivatives of the model states have been computed (e.g., after
 * rdModel::computeAccelerations(), ...).
 *
 * Override this method in derived classes.
 *
 * @param aT Current time in the simulation.
 * @param aX Current controls of the model.
 * @param aY Current states of the model
 */
void rdDerivCallback::
computeDerivatives(double aT,double *aX,double *aY,double *aDY)
{
	//printf("rdDerivCallback.computeDerivatives: %s.\n",getName());
}
