// rdCallback.cpp
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
#include <NMBLTK/Tools/rdObject.h>
#include <NMBLTK/Tools/rdPropertyBool.h>
#include <NMBLTK/Tools/rdPropertyDbl.h>

#include "rdCallback.h"
#include "rdModel.h"

//=============================================================================
// STATICS
//=============================================================================


//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
rdCallback::~rdCallback()
{
}

//_____________________________________________________________________________
/**
 * Default constructor.
 *
 * @param aModel Model to which the callback mthods apply.
 */
rdCallback::rdCallback(rdModel *aModel):
	_on(_onProp.getValueBool()),
	_startTime(_startTimeProp.getValueDbl()),
	_endTime(_endTimeProp.getValueDbl())
{
	setNull();
	_model = aModel;
}
//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aCallback rdCallback to copy.
 */
rdCallback::rdCallback(const rdCallback &aCallback):
	rdObject(aCallback),
	_on(_onProp.getValueBool()),
	_startTime(_startTimeProp.getValueDbl()),
	_endTime(_endTimeProp.getValueDbl())
{
	setNull();
	*this = aCallback;
}
//_____________________________________________________________________________
/**
* Construct an object from file.
*
* The object is constructed from the root element of the XML document.
* The type of object is the tag name of the XML root element.
*
* @param aFileName File name of the document.
*/
rdCallback::rdCallback(const std::string &aFileName):
	rdObject(aFileName),
	_on(_onProp.getValueBool()),
	_startTime(_startTimeProp.getValueDbl()),
	_endTime(_endTimeProp.getValueDbl())
{
	setNull();
	updateFromXMLNode();
	_model = NULL;
}
//_____________________________________________________________________________
/**
* Construct an rdCallback from DOMElement.
*
* The object is constructed from the root element of the XML document.
* The type of object is the tag name of the XML root element.
*
* @param aFileName File name of the document.
*/
rdCallback::rdCallback(DOMElement *aElement):
	rdObject(aElement),
	_on(_onProp.getValueBool()),
	_startTime(_startTimeProp.getValueDbl()),
	_endTime(_endTimeProp.getValueDbl())
{
	setNull();
	updateFromXMLNode();
	_model = NULL;
}
//_____________________________________________________________________________
/**
 * Virtual copy constructor.
 */
rdObject* rdCallback::
copy() const
{
	return(new rdCallback(*this));
}

//_____________________________________________________________________________
/**
 * Create and return a copy 
 */
rdObject* rdCallback::
copy(DOMElement *aElement) const
{
	rdCallback *c = new rdCallback(aElement);
	*c = *this;
	c->updateFromXMLNode();
	return(c);
}
//=============================================================================
// CONSTRUCTION AND DESTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set NULL values for member variables.
 */
void rdCallback::
setNull()
{
	setType("rdCallback");
	setupProperties();
	_on = true;
	_model = NULL;
	_startTime = 0.0;
	_endTime = 1.0;
}

//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void rdCallback::
setupProperties()
{
	_onProp.setName("On");
	_propertySet.append(&_onProp);

	_startTimeProp.setName("StartTime");
	_propertySet.append(&_startTimeProp );

	_endTimeProp.setName("EndTime");
	_propertySet.append(&_endTimeProp );
}


//=============================================================================
// OPERATORS
//=============================================================================
//-----------------------------------------------------------------------------
// ASSIGNMENT
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Assignment operator.
 *
 * @return Reference to this object.
 */
rdCallback& rdCallback::
operator=(const rdCallback &aCallback)
{
	// BASE CLASS
	rdObject::operator=(aCallback);
	// Model
	_model = aCallback._model;
	// Status
	_on = aCallback._on;
	// Start/end times
	_startTime = aCallback._startTime;
	_endTime = aCallback._endTime;

	return(*this);
}

//=============================================================================
// GET AND SET
//=============================================================================
//-----------------------------------------------------------------------------
// MODEL
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get a pointer to the model for which this callback has been set.
 *
 * @return Pointer to the model.
 */
rdModel* rdCallback::
getModel() const
{
	return(_model);
}
//_____________________________________________________________________________
/**
 * Set a pointer to the model for which this callback has been set.
 *
 */
void rdCallback::
setModel(rdModel *aModel)
{
	_model=aModel;
}

//-----------------------------------------------------------------------------
// ON/OFF
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Turn this callback on or off.
 *
 * @param aTureFalse Turns analysis on if "true" and off if "false".
 */
void rdCallback::
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
bool rdCallback::
getOn() const
{
	return(_on);
}

//-----------------------------------------------------------------------------
// START TIME
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the time at which to begin executing the callback.  Note that the start
 * time should be specified in normalized time units, not in real time units.
 *
 * @param aStartTime Start time expressed in NORMALIZED time units.
 */
void rdCallback::
setStartTime(double aStartTime)
{
	_startTime = aStartTime;
}
//_____________________________________________________________________________
/**
 * Get the time at which to begin executing the callback, expressed in
 * normalized time units, not real time units.
 *
 * @return Start time expressed in NORMALIZED time units.
 */
double rdCallback::
getStartTime() const
{
	return(_startTime);
}

//-----------------------------------------------------------------------------
// END TIME
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the time at which to end executing the callback.  Note that the end time
 * should be specified in normalized time units, not in real time units.
 *
 * @param aEndTime Time at which the callback should end execution in
 * NORMALIZED time units.
 */
void rdCallback::
setEndTime(double aEndTime)
{
	_endTime = aEndTime;
}
//_____________________________________________________________________________
/**
 * Get the time at which to end executing the callback, expressed in
 * normalized time units, not real time units.
 *
 * @return End time expressed in NORMALIZED time units.
 */
double rdCallback::
getEndTime() const
{
	return(_endTime);
}

