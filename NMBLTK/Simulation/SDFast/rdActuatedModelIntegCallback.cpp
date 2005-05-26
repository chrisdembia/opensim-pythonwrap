// rdActuatedModelIntegCallback.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <RD/Tools/rdMath.h>
#include <RD/Simulation/Model/rdModel.h>
#include <RD/Simulation/Model/rdContactForceSet.h>
#include <RD/Actuators/rdSetPoint.h>
#include "rdActuatedModel_SDFast.h"
#include "rdActuatedModelIntegCallback.h"


//=============================================================================
// CONSTANTS
//=============================================================================


//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
rdActuatedModelIntegCallback::~rdActuatedModelIntegCallback()
{
}
//_____________________________________________________________________________
/**
 * Construct a derivative callback instance for perturbing actuator forces
 * during an integration.
 *
 * @param aModel Model for which actuator forces are to be perturbed.
 */
rdActuatedModelIntegCallback::
rdActuatedModelIntegCallback(rdActuatedModel_SDFast *aModel) :
	rdIntegCallback(aModel)
{
	setNull();
}


//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Set member variables to approprate NULL values.
 */
void rdActuatedModelIntegCallback::
setNull()
{
	setType("rdActuatedModelIntegCallback");
}


//=============================================================================
// GET AND SET
//=============================================================================


//=============================================================================
// UTILITY
//=============================================================================


//=============================================================================
// CALLBACKS
//=============================================================================
//_____________________________________________________________________________
/**
 * Perform any necessary updates after each integration step (e.g., updating
 * pseudostates).
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
int rdActuatedModelIntegCallback::
step(double *aXPrev,double *aYPrev,int aStep,double aDT,double aT,
	double *aX,double *aY,void *aClientData)
{
	// UPDATE THE PSEUDOSTATES
	rdActuatedModel_SDFast *model = (rdActuatedModel_SDFast*)_model;
	rdContactForceSet *contactSet = model->getContactForceSet();
	model->set(aT,aX,aY);
	contactSet->updatePseudoStates();

	return(0);
}





