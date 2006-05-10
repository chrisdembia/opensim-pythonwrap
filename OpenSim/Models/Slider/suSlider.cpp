// suSlider.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Authors:  Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <OpenSim/Tools/rdMath.h>
#include <OpenSim/Simulation/Model/Model.h>
#include <OpenSim/Simulation/Model/Springs.h>
#include <OpenSim/Simulation/SDFast/sdfast.h>
#include "suSlider.h"


//=============================================================================
// CONSTANTS
//=============================================================================


using namespace OpenSim;
static char* bNames[] = { "block" };
static char* qNames[] = { "X" };
static char* uNames[] = { "VX" };


//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
suSlider::~suSlider()
{
}
//_____________________________________________________________________________
/**
 * Default constructor.
 */
suSlider::suSlider(ActuatorSet *aActuators,ContactForceSet *aContacts) :
	ActuatedModel_SDFast(aActuators,aContacts)
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
void suSlider::
setNull()
{
}
//_____________________________________________________________________________
/**
 * Construct the valid initial states.
 */
void suSlider::
constructInitialStates()
{
	Array<double> yi(0.0,getNY());
	getInitialStates(&yi[0]);
	// specify any initial states...
	// yi[??] = ??;
	setInitialStates(&yi[0]);
}
//_____________________________________________________________________________
/**
 * Construct the names of the various components of the model.
 */
void suSlider::
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


