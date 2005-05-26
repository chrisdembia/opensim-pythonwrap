// rdIntegCallback.cpp
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
#include "rdIntegCallbackSet.h"
#include "rdIntegCallback.h"
#include <NMBLTK/Tools/rdPropertyInt.h>
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
rdIntegCallback::~rdIntegCallback()
{
}

//_____________________________________________________________________________
/**
 * Constructor.
 *
 * Note that this constructor adds the callback to the model.  Derived
 * classes should not also add themselves to the model.
 *
 * @param aModel Model to which the callback mthods apply.
 */
rdIntegCallback::rdIntegCallback(rdModel *aModel) :
	rdCallback(aModel),
	_stepInterval(_stepIntervalProp.getValueInt())
{
	// NULL
	setNull();
}
//_____________________________________________________________________________
/**
 * Copy Constructor.
 *
 */
rdIntegCallback::rdIntegCallback(const rdIntegCallback &aIntegCallback):
rdCallback(aIntegCallback),
	_stepInterval(_stepIntervalProp.getValueInt())
{
	setNull();
	*this = aIntegCallback;
}
//_____________________________________________________________________________
/**
 * Constructor from an xml file
 *
 */
rdIntegCallback::rdIntegCallback(const std::string &aFileName):
rdCallback(aFileName),
	_stepInterval(_stepIntervalProp.getValueInt())
{
	setNull();
	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Constructor from an xml element
 *
 */
rdIntegCallback::rdIntegCallback(DOMElement *aElement):
	rdCallback(aElement),
	_stepInterval(_stepIntervalProp.getValueInt())
{
	setNull();

	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Constructor from a clone
 *
 */
rdObject* rdIntegCallback::copy() const
{
	return(new rdIntegCallback(*this));
}
//_____________________________________________________________________________
/**
 * Virtual Constructor from an xml element
 *
 */
rdObject* rdIntegCallback::copy(DOMElement *aElement) const
{
	rdIntegCallback *c = new rdIntegCallback(aElement);
	*c = *this;
	c->updateFromXMLNode();
	return(c);
} 

//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set NULL values for member variables.
 */
void rdIntegCallback::
setNull()
{
	setupProperties();

	setType("rdIntegCallback");
	_stepInterval = 1;
}

//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void rdIntegCallback::
setupProperties()
{
	_stepIntervalProp.setName("StepInterval");
	_propertySet.append( &_stepIntervalProp );
}


//=============================================================================
// OPERATORS
//=============================================================================
//-----------------------------------------------------------------------------
// ASSIGNMENT
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Assign this object to the values of another.
 *
 * @return Reference to this object.
 */
rdIntegCallback& rdIntegCallback::
operator=(const rdIntegCallback &aObject)
{
	// BASE CLASS
	rdCallback::operator=(aObject);

	// Class Members
	setStepInterval(aObject.getStepInterval());

	return(*this);
}


//=============================================================================
// GET AND SET
//=============================================================================
//_____________________________________________________________________________
/**
 * Set the step interval.
 *
 * The step interval is used to specify how many integration steps must
 * go by before the rdIntegCallback::step() method is executed.
 * Specifically, unless the step number divided by the step interval
 * has no remainder (i.e., (step % stepInterval) == 0), the step
 * method is not executed.
 *
 * @param aStepInterval Step interval. Should be 1 or greater.
 */
void rdIntegCallback::
setStepInterval(int aStepInterval)
{
	_stepInterval = aStepInterval;
	if(_stepInterval<1) _stepInterval= 1;
}
//_____________________________________________________________________________
/**
 * Get the step interval.
 *
 * The step interval is used to specify how many integration steps must
 * go by before the rdIntegCallback::step() method is executed.
 * Specifically, unless the step number divided by the step interval
 * has no remainder (i.e., (step % stepInterval) == 0), the step
 * method is not executed.
 *
 * @return Step interval.
 */
int rdIntegCallback::
getStepInterval() const
{
	return(_stepInterval);
}


//=============================================================================
// CALLBACKS
//=============================================================================
//_____________________________________________________________________________
/**
 * This method is called at the beginning of an integration and is intended
 * to be used for any initializations that are necessary.
 *
 * Override this method in derived classes.
 *
 * @param aStep Number of integrations steps that have been completed.
 * @param aDT Size of the integration time step that will be attempted.
 * @param aT Current time in the integration.
 * @param aX Current control values.
 * @param aY Current states.
 * @param aClientData General use pointer for sending in client data.
 *
 * @return -1 on error, 0 otherwise.
 */
int rdIntegCallback::
begin(int aStep,double aDT,double aT,double *aX,double *aY,
	void *aClientData)
{
	//printf("rdIntegCallback.begin: %s.\n",getName());
	return (0);
}
//_____________________________________________________________________________
/**
 * This method is called after each successful integration time step and is
 * intended to be used for conducting analyses, driving animations, etc.
 *
 * Override this method in derived classes.
 *
 * @param aXPrev Control values at the previous time step.
 * @param aYPrev State values at the previous time step.
 * @param aStep Number of integrations steps that have been completed.
 * @param aDT Size of the time step that WAS just completed.
 * @param aT Current time in the integration.
 * @param aX Current control values.
 * @param aY Current states.
 * @param aClientData General use pointer for sending in client data.
 *
 * @return -1 on error, 0 otherwise.
 */
int rdIntegCallback::
step(double *aXPrev,double *aYPrev,int aStep,double aDT,double aT,
	double *aX,double *aY,void *aClientData)
{
	//printf("rdIntegCallback.step: %s.\n",getName());
	return (0);
}
//_____________________________________________________________________________
/**
 * This method is called after an integration has been completed and is
 * intended to be used for performing any finalizations necessary.
 *
 * Override this method in derived classes.
 *
 * @param aStep Number of integrations steps that have been completed.
 * @param aDT Size of the time step that WAS just completed.
 * @param aT Current time in the integration.
 * @param aX Current control values.
 * @param aY Current states.
 * @param aClientData General use pointer for sending in client data.
 *
 * @return -1 on error, 0 otherwise.
 */
int rdIntegCallback::
end(int aStep,double aDT,double aT,double *aX,double *aY,
	 void *aClientData)
{
	//printf("rdIntegCallback.end: %s.\n",getName());
	return(0);
}

