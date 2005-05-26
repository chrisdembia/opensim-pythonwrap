// rdCallbackSet.cpp
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
//#include <rdObject.h>
#include "rdCallbackSet.h"


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
rdCallbackSet::~rdCallbackSet()
{
}
//_____________________________________________________________________________
/**
 * Default constructor.
 */
rdCallbackSet::rdCallbackSet(rdModel *aModel)
{
	// NULL
	setNull();

	// MODEL
	_model = aModel;
}


//=============================================================================
// CONSTRUCTION AND DESTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set the data members of this actuator to their null values.
 */
void rdCallbackSet::
setNull()
{
	// TYPE
	setType("rdCallbackSet");

	// MODEL
	_model = NULL;
}


//=============================================================================
// GET AND SET
//=============================================================================
//-----------------------------------------------------------------------------
// MODEL
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get a pointer to the model which is actuated.
 *
 * @return Pointer to the model.
 */
rdModel* rdCallbackSet::
getModel()
{
	return(_model);
}

//-----------------------------------------------------------------------------
// ON & OFF
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set all the callbacks either on or off.
 *
 * @param aTrueFalse Arguement that, if true, results in all callbacks
 * being turned on; if false, all callbacks are turned off.
 */
void rdCallbackSet::
setOn(bool aTrueFalse)
{
	int i;
	rdCallback *callback;
	for(i=0;i<getSize();i++) {
		callback = get(i);
		if(callback==NULL) continue;
		callback->setOn(aTrueFalse);
	}
}
