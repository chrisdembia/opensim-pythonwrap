// rdUTWalkingPrescribedIntegCallback.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include <iostream>
#include <string>
#include <OpenSim/Tools/rdMath.h>
#include <OpenSim/Simulation/Model/Model.h>
#include "rdUTWalkingPrescribedIntegCallback.h"



using namespace OpenSim;
using namespace std;


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
rdUTWalkingPrescribedIntegCallback::~rdUTWalkingPrescribedIntegCallback()
{
}
//_____________________________________________________________________________
/**
 * Construct a derivative callback instance for perturbing actuator forces
 * during an integration.
 *
 * @param aModel Model for which actuator forces are to be perturbed.
 */
rdUTWalkingPrescribedIntegCallback::
rdUTWalkingPrescribedIntegCallback(rdUTWalking8Prescribed *aModel) :
	IntegCallback(aModel)
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
void rdUTWalkingPrescribedIntegCallback::
setNull()
{
	setType("rdUTWalkingPrescribedIntegCallback");
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
 * pseudostates), drawing the model, etc.
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
int rdUTWalkingPrescribedIntegCallback::
step(double *aXPrev,double *aYPrev,int aStep,double aDT,double aT,
	double *aX,double *aY,void *aClientData)
{
	//cout<<"rdUTWalkingPrescribedIntegCallback::step ..."<<endl;

	// UPDATE THE PSEUDOSTATES
	rdUTWalking8Prescribed *model = (rdUTWalking8Prescribed*)_model;

	// SET
	model->set(aT,aX,aY);

	// EXTRACT THE GENERALIZED COORDINATES AND SPEEDS
	double q[24],u[23];
	model->getCoordinates(q);
	model->getSpeeds(u);

	// COMPUTE THE SPRING FORCES
	double svel[rdUTWalking8Prescribed_NS][3],spos[rdUTWalking8Prescribed_NS][3];
	double sfrc[rdUTWalking8Prescribed_NS][3];
	model->computeSpringPointKinematics(svel,spos);
	model->computeGroundForces(svel,spos,sfrc);

	// UPDATE THE HORIZONTAL SPRING ZEROS
	model->updateGroundZeros(svel,spos,sfrc);

	// LIMIT THE GROUND FORCES
	model->limitGroundForces(sfrc);

	// DRAW THE MODEL
	if(model->getDraw()) {
#ifdef UNIX
		if((aStep%20)==0) drawutwalking_(&aT,aX,aY,&sfrc[0][0],&spos[0][0]);
#endif
	}

	return(0);
}





