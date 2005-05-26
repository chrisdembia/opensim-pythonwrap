// rdIntegCallbackSet.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2003 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include "rdIntegCallbackSet.h"


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
rdIntegCallbackSet::~rdIntegCallbackSet()
{
}
//_____________________________________________________________________________
/**
 * Construct an empty callback set for a model.
 */
rdIntegCallbackSet::rdIntegCallbackSet(rdModel *aModel) :
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
void rdIntegCallbackSet::
setNull()
{
	// TYPE
	setType("rdIntegCallbackSet");

	// MODEL 
	//_model = NULL;
}


//=============================================================================
// GET AND SET
//=============================================================================
//-----------------------------------------------------------------------------
// INTEGRATION CALLBACK
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the callback at an index.  This method uses the method
 * rdArray::get() and casts the returned void pointer as an
 * rdIntegCallback.
 *
 * @param aIndex Array index of the callback to be returned.
 * @return Callback at index aIndex.
 */
rdIntegCallback* rdIntegCallbackSet::
getIntegCallback(int aIndex) const
{
	return((rdIntegCallback*)get(aIndex));
}


//=============================================================================
// CALLBACKS
//=============================================================================
//_____________________________________________________________________________
/**
 * Call the begin method for all integration callbacks.  This method is
 * called at the beginning of an integration and is intended to be used for
 * any initializations that are necessary.
 *
 * @param aStep Number of integrations steps that have been completed.
 * @param aDT Size of the integration time step that will be attempted.
 * @param aT Current time in the integration.
 * @param aX Current control values.
 * @param aY Current states.
 * @param aClientData General use pointer for sending in client data.
 */
void rdIntegCallbackSet::
begin(int aStep,double aDT,double aT,double *aX,double *aY,void *aClientData)
{
	int i;
	rdIntegCallback *callback;
	for(i=0;i<getSize();i++) {
		callback = getIntegCallback(i);
		if(callback == NULL) continue;
		callback->begin(aStep,aDT,aT,aX,aY,aClientData);
	}
}

//_____________________________________________________________________________
/**
 * Call the step method for all integration callbacks.  This method is called
 * after each successful integration time step and is intended to be used for
 * conducting analyses, driving animations, etc.
 *
 * @param aXPrev Control values at the previous time step.
 * @param aYPrev State values at the previous time step.
 * @param aStep Number of integrations steps that have been completed.
 * @param aDT Size of the time step that WAS just completed.
 * @param aT Current time in the integration.
 * @param aX Current control values.
 * @param aY Current states.
 * @param aClientData General use pointer for sending in client data.
 */
void rdIntegCallbackSet::
step(double *aXPrev,double *aYPrev,int aStep,double aDT,double aT,
	double *aX,double *aY,void *aClientData)
{
	int i;
	rdIntegCallback *callback;
	for(i=0;i<getSize();i++) {
		callback = getIntegCallback(i);
		if(callback == NULL) continue;
		callback->step(aXPrev,aYPrev,aStep,aDT,aT,aX,aY,aClientData);
	}
}

//_____________________________________________________________________________
/**
 * Call the end method for all integration callbacks.  This method is called
 * after an integration has been completed and is intended to be used for
 * performing any finalizations necessary.
 *
 * @param aStep Number of integrations steps that have been completed.
 * @param aDT Size of the time step that WAS just completed.
 * @param aT Current time in the integration.
 * @param aX Current control values.
 * @param aY Current states.
 * @param aClientData General use pointer for sending in client data.
 */
void rdIntegCallbackSet::
end(int aStep,double aDT,double aT,double *aX,double *aY,void *aClientData)
{
	int i;
	rdIntegCallback *callback;
	for(i=0;i<getSize();i++) {
		callback = getIntegCallback(i);
		if(callback == NULL) continue;
		callback->end(aStep,aDT,aT,aX,aY,aClientData);
	}
}


