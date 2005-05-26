// rdDerivCallbackSet.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include "rdDerivCallbackSet.h"


//=============================================================================
// STATICS
//=============================================================================


//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 * Note that the individual callbacks are not deleted by
 * this destructor.  To delete the callbacks, the caller must do so
 * individually, or the method rdCallback::deleteCallbacks() may be called.
 */
rdDerivCallbackSet::~rdDerivCallbackSet()
{
}
//_____________________________________________________________________________
/**
 * Construct an empty callback set for a model.
 */
rdDerivCallbackSet::rdDerivCallbackSet(rdModel *aModel) :
	rdCallbackSet(aModel)
{
	// NULL
	setNull();
}


//=============================================================================
// CONSTRUCTION AND DESTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set the data members of this actuator to their null values.
 */
void rdDerivCallbackSet::
setNull()
{
	// TYPE
	setType("rdDerivCallbackSet");
}


//=============================================================================
// GET AND SET
//=============================================================================
//_____________________________________________________________________________
/**
 * Get the callback at an index.  This method uses the method
 * rdArray::get() and casts the returned void pointer as an
 * rdIntegCallback.
 *
 * @param aIndex Array index of the callback to be returned.
 * @return Callback at index aIndex.
 */
rdDerivCallback* rdDerivCallbackSet::
getDerivCallback(int aIndex) const
{
	return((rdDerivCallback*)get(aIndex));
}


//=============================================================================
// CALLBACKS
//=============================================================================
//_____________________________________________________________________________
/**
 * This method is intended to be called from rdModel::deriv() after the
 * states of a model have been set (e.g., after rdModel::set() or
 * rdModel::setStates()).
 *
 * @param aT Current time in the simulation.
 * @param aX Current controls of the model.
 * @param aY Current states of the model
 */
void rdDerivCallbackSet::
set(double aT,double *aX,double *aY)
{
	int i;
	int size = getSize();
	rdDerivCallback *callback;
	for(i=0;i<size;i++) {
		callback = getDerivCallback(i);
		if(callback == NULL) continue;
		callback->set(aT,aX,aY);
	}
}
//_____________________________________________________________________________
/**
 * This method is intended to be called from rdModel::deriv() after 
 * actuation quantities have been computed (e.g., after
 * rdModel::computeActuation()).
 *
 * @param aT Current time in the simulation.
 * @param aX Current controls of the model.
 * @param aY Current states of the model
 */
void rdDerivCallbackSet::
computeActuation(double aT,double *aX,double *aY)
{
	int i;
	int size = getSize();
	rdDerivCallback *callback;
	for(i=0;i<size;i++) {
		callback = getDerivCallback(i);
		if(callback == NULL) continue;
		callback->computeActuation(aT,aX,aY);
	}
}
//_____________________________________________________________________________
/**
 * This method is intended to be called from rdModel::deriv() after 
 * actuator forces have been applied (e.g., after
 * rdModel::applyActuatorForces()).
 *
 * @param aT Current time in the simulation.
 * @param aX Current controls of the model.
 * @param aY Current states of the model
 */
void rdDerivCallbackSet::
applyActuation(double aT,double *aX,double *aY)
{
	int i;
	int size = getSize();
	rdDerivCallback *callback;
	for(i=0;i<size;i++) {
		callback = getDerivCallback(i);
		if(callback == NULL) continue;
		callback->applyActuation(aT,aX,aY);
	}
}
//_____________________________________________________________________________
/**
 * This method is intended to be called from rdModel::deriv() after 
 * contact quantities have been computed (e.g., after
 * rdModel::computeContact()).
 *
 * @param aT Current time in the simulation.
 * @param aX Current controls of the model.
 * @param aY Current states of the model
 */
void rdDerivCallbackSet::
computeContact(double aT,double *aX,double *aY)
{
	int i;
	int size = getSize();
	rdDerivCallback *callback;
	for(i=0;i<size;i++) {
		callback = getDerivCallback(i);
		if(callback == NULL) continue;
		callback->computeContact(aT,aX,aY);
	}
}
//_____________________________________________________________________________
/**
 * This method is intended to be called from rdModel::deriv() after 
 * contact forces have been applied (e.g., after
 * rdModel::applyContactForces()).
 *
 * @param aT Current time in the simulation.
 * @param aX Current controls of the model.
 * @param aY Current states of the model
 */
void rdDerivCallbackSet::
applyContact(double aT,double *aX,double *aY)
{
	int i;
	int size = getSize();
	rdDerivCallback *callback;
	for(i=0;i<size;i++) {
		callback = getDerivCallback(i);
		if(callback == NULL) continue;
		callback->applyContact(aT,aX,aY);
	}
}
//_____________________________________________________________________________
/**
 * This method is intended to be called from rdModel::deriv() after 
 * derivatives of the model states have been computed (e.g., after
 * rdModel::computeAccelerations(), ...).
 *
 * @param aT Current time in the simulation.
 * @param aX Current controls of the model.
 * @param aY Current states of the model
 */
void rdDerivCallbackSet::
computeDerivatives(double aT,double *aX,double *aY,double *aDY)
{
	int i;
	int size = getSize();
	rdDerivCallback *callback;
	for(i=0;i<size;i++) {
		callback = getDerivCallback(i);
		if(callback == NULL) continue;
		callback->computeDerivatives(aT,aX,aY,aDY);
	}
}
