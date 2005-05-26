// suHopper.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Authors:  Ines Barbosa and Clay Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <RD/Tools/rdMath.h>
#include <RD/Simulation/Model/rdModel.h>
#include <RD/Simulation/Model/rdSprings.h>
#include <RD/Simulation/SDFast/sdfast.h>
#include "suHopper.h"


//=============================================================================
// CONSTANTS
//=============================================================================

// NAMES
static char* bNames[] = { "trunk", "foot" };
static char* qNames[] = { "trunk_Y","leg_Y" };
static char* uNames[] = { "trunk_VY","leg_VY" };


//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
suHopper::~suHopper()
{
}
//_____________________________________________________________________________
/**
 * Default constructor.
 */
suHopper::suHopper(rdActuatorSet *aActuators,rdContactForceSet *aContacts) :
	rdActuatedModel_SDFast(aActuators,aContacts)
{
	setNull();

	// CONSTRUCT INITIAL STATES
	constructInitialStates();

	// CONSTRUCT NAMES
	constructNames();
}


//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Set member variables to their appropriate null values.
 */
void suHopper::
setNull()
{
}
//_____________________________________________________________________________
/**
 * Construct the valid initial states.
 */
void suHopper::
constructInitialStates()
{
	rdArray<double> yi(0.0,getNY());
	getInitialStates(&yi[0]);
	yi[0] = 1.0;
	yi[1] = -0.75;
	yi[2] = 0.0;
	yi[3] = 0.0;
	setInitialStates(&yi[0]);

}
//_____________________________________________________________________________
/**
 * Construct the names of the various components of the model.
 */
void suHopper::
constructNames()
{

	// BODIES
	int i;
	for(i=0;i<getNB();i++) setBodyName(i,bNames[i]);

	// Q
	for(i=0;i<getNQ();i++) setCoordinateName(i,qNames[i]);

	// U
	for(i=0;i<getNU();i++) setSpeedName(i,uNames[i]);
}


//=============================================================================
// GET AND SET
//=============================================================================


