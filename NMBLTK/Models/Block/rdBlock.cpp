// rdBlock.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2000 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
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
#include <RD/Simulation/Model/rdBody.h>
#include "rdBlock.h"
#include <RD/Simulation/Control/rdControlConstant.h>
#include <RD/Simulation/Control/rdControlLinear.h>
#include <RD/Simulation/Control/rdControlLinearNode.h>
#include <RD/Simulation/Control/rdControlSet.h>
#include <RD/Simulation/Model/rdForce.h>
#include <RD/Simulation/Model/rdGeneralizedForce.h>

using namespace std;


//=============================================================================
// CONSTANTS
//=============================================================================

// NAMES
static char* bNames[] = { "block" };
static char* qNames[] = { "X","Y","Z","E1","E2","E3","E4" };
static char* uNames[] = { "VX","VY","VZ","VOx","VOy","VOz" };


//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
rdBlock::~rdBlock()
{
	// Bodies allocated in constructBodies will be released in ~rdModel
}
//_____________________________________________________________________________
/**
 * Default constructor.
 *
 */
rdBlock::rdBlock(rdActuatorSet *aActuators,rdContactForceSet *aContacts) :
	rdActuatedModel_SDFast(aActuators, aContacts)
{
	setNull();

	// CONSTRUCT INITIAL STATES
	constructInitialStates();

	constructGeometry();

	// CONSTRUCT NAMES
	constructNames();

	setName("Block");
	setType("rdBlock");

	// Code added here so that when the model is displayed
	// body xforms are well defined.
	double *iStates= new double[getNY()];
	getInitialStates(iStates);
	setStates(iStates);
	delete[] iStates;
}

//_____________________________________________________________________________
/**
 * Constructor from an XML Document
 */
rdBlock::rdBlock(const string &aFileName,
							rdActuatorSet *aActuators,
							rdContactForceSet *aContacts) :
rdActuatedModel_SDFast(aFileName, aActuators, aContacts)
{
	setNull();

	updateFromXMLNode();

	// INITIAL STATES
	constructInitialStates();

	constructGeometry();

	setModelDescriptionFileName(aFileName);
}
//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Set member variables to their appropriate null values.
 */
void rdBlock::
setNull()
{
}
//_____________________________________________________________________________
/**
 * Construct the valid initial states.
 */
void rdBlock::
constructInitialStates()
{
	rdArray<double> yi(0.0,getNY());
	getInitialStates(&yi[0]);
	yi[1] = 0.1;
	yi[6] = 1.0;
	yi[7] = 1.0;
	setInitialStates(&yi[0]);
}
//_____________________________________________________________________________
/**
 * Construct the names of the various components of the model.
 */
void rdBlock::
constructNames()
{

	// BODIES
	int i;
	for(i=0;i<getNB();i++) {
		setBodyName(i,bNames[i]);
		// Actual body has been constructed by constructBodies()
		if (i!=getGroundID())
			getBody(i)->setName(bNames[i]);
	}

	// Q
	for(i=0;i<getNQ();i++) setCoordinateName(i,qNames[i]);

	// U
	for(i=0;i<getNU();i++) setSpeedName(i,uNames[i]);
}

//_____________________________________________________________________________
/**
 * Read system description and fill in data to describe visible properties of model.
 */
void rdBlock::
constructGeometry()
{
	// Body Geometry abd preferences
	for(int i=0;i<getNB();i++) {
		// Actual body has been constructed by constructBodies()
		if (i!=getGroundID()){
			getBody(i)->setNumGeometryFiles(1);
			// This's specific to my env. we'll have to make it more flexible
			// for example by providing a default directory or having path
			// relative to some env. var $RDI_INSTALL
			getBody(i)->setGeometryFileName(0, "C://Work//Geometry//Cube.vtp");
		}
	}
}
//=============================================================================
// Register Types: registers the types of objects that will be used by the 
// rdBlock Model so that it can be read and written to xml files (serialized)
//=============================================================================

void rdBlock::
RegisterTypes()
{
	/* This list should be broken so that
	 * 1. a Model doesn't have to be loaded before we load Actuators, Contacts, ...
	 * 2. rdBlock registers only classes it defines (rdBlock()) everything else
	 *	  would be registered in a base class and is done by calling inherited::RegisterTypes()
	 * 3. Plugins will define new types so they should use the mechanism in 2. for encapsulation.
	 */
	rdActuatedModel_SDFast::RegisterTypes();
	rdObject::RegisterType(rdBlock());
	rdObject::RegisterType(rdControlConstant());
	rdObject::RegisterType(rdControlLinearNode());
	rdObject::RegisterType(rdControlLinear());
	rdObject::RegisterType(rdControlSet());
	rdObject::RegisterType(rdForce());
	rdObject::RegisterType(rdGeneralizedForce());

}
