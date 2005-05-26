// rdController.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2000-2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fc.anderson@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include "rdController.h"


//=============================================================================
// STATICS
//=============================================================================
const int rdController::NAME_LENGTH = rdController_NAME_LENGTH;
const int rdController::DESCRIP_LENGTH = rdController_DESCRIP_LENGTH;


//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Default constructor.
 *
 * @param aModel Model that is to be controlled.
 */
rdController::rdController(rdModel *aModel)
{
	// NULL
	setNull();

	// MODEL
	_model = aModel;
}
//_____________________________________________________________________________
/**
 * Destructor.
 */
rdController::~rdController()
{

}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set NULL values for all member variables.
 */
void rdController::
setNull()
{
	// MODEL
	_model = NULL;

	// STATES
	_on = true;

	// NAME
	setName("UNKOWN");

	// DESCRIPTION
	setDescription("");

}


//=============================================================================
// GET AND SET
//=============================================================================
//-----------------------------------------------------------------------------
// MODEL
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get a pointer to the model on which this analysis is being performed.
 *
 * @return Pointer to the model.
 */
rdModel* rdController::
getModel()
{
	return(_model);
}

//-----------------------------------------------------------------------------
// ON/OFF
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Turn this analysis on or off.
 *
 * @param aTureFalse Turns analysis on if "true" and off if "false".
 */
void rdController::
setOn(bool aTrueFalse)
{
	_on = aTrueFalse;
}
//_____________________________________________________________________________
/**
 * Get whether or not this analysis is on.
 *
 * @return True if on, false if off.
 */
bool rdController::
getOn()
{
	return(_on);
}

//-----------------------------------------------------------------------------
// NAME
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the name of this controller.
 *
 * @param aName Name.
 */
void rdController::
setName(const char *aName)
{
	if(aName==NULL) {
		strcpy(_name,"");
	} else {
		strncpy(_name,aName,NAME_LENGTH-2);
	}
	_name[NAME_LENGTH-1] = NULL;
}
//_____________________________________________________________________________
/**
 * Get the name of this controller.
 *
 * @return Name.
 */
const char* rdController::
getName()
{
	return(_name);
}

//-----------------------------------------------------------------------------
// DESCRIPTION
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the description of this controller.
 *
 * @param aDescrip Description.
 */
void rdController::
setDescription(const char *aDescrip)
{
	if(aDescrip==NULL) {
		strcpy(_descrip,"");
	} else {
		strncpy(_descrip,aDescrip,DESCRIP_LENGTH-2);
	}
	_descrip[DESCRIP_LENGTH-1] = NULL;
}
//_____________________________________________________________________________
/**
 * Get the description of this controller.
 *
 * @return Description.
 */
const char* rdController::
getDescription()
{
	return(_descrip);
}


//=============================================================================
// CONTROL
//=============================================================================


