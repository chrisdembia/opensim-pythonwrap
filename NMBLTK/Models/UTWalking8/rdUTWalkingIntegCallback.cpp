// rdUTWalkingIntegCallback.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include <iostream>
#include <string>
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include "rdUTWalkingIntegCallback.h"

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
rdUTWalkingIntegCallback::~rdUTWalkingIntegCallback()
{
}
//_____________________________________________________________________________
/**
 * Construct a derivative callback instance for perturbing actuator forces
 * during an integration.
 *
 * @param aModel Model for which actuator forces are to be perturbed.
 */
rdUTWalkingIntegCallback::
rdUTWalkingIntegCallback(rdUTWalking8 *aModel) :
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
void rdUTWalkingIntegCallback::
setNull()
{
	setType("rdUTWalkingIntegCallback");
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
int rdUTWalkingIntegCallback::
step(double *aXPrev,double *aYPrev,int aStep,double aDT,double aT,
	double *aX,double *aY,void *aClientData)
{
	//cout<<"rdUTWalkingIntegCallback::step ..."<<endl;

	// UPDATE THE PSEUDOSTATES
	rdUTWalking8 *model = (rdUTWalking8*)_model;

	// SET
	model->set(aT,aX,aY);

	// EXTRACT THE GENERALIZED COORDINATES AND SPEEDS
	double q[24],u[23];
	model->getCoordinates(q);
	model->getSpeeds(u);

	// COMPUTE THE SPRING FORCES
	double svel[rdUTWalking8_NS][3],spos[rdUTWalking8_NS][3];
	double sfrc[rdUTWalking8_NS][3];
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





