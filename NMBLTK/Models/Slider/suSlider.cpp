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
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include <NMBLTK/Simulation/Model/rdSprings.h>
#include <NMBLTK/Simulation/SDFast/sdfast.h>
#include "suSlider.h"


//=============================================================================
// CONSTANTS
//=============================================================================
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
suSlider::suSlider(rdActuatorSet *aActuators,rdContactForceSet *aContacts) :
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
	rdArray<double> yi(0.0,getNY());
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


