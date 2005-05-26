// rdControl.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2000-2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fc.anderson@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <NMBLTK/Simulation/rdSimulationDLL.h>
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Tools/rdProperty.h>
#include <NMBLTK/Tools/rdPropertyBool.h>
#include <NMBLTK/Tools/rdPropertyInt.h>
#include <NMBLTK/Tools/rdPropertyDbl.h>
#include <NMBLTK/Tools/rdIO.h>
#include "rdControl.h"


using namespace std;


//=============================================================================
// CONSTRUCTOR(S)
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
rdControl::~rdControl()
{
}
//_____________________________________________________________________________
/**
 * Default constructor.
 */
rdControl::rdControl(const char *aName) :
	_isModelControl( _propIsModelControl.getValueBool() ),
	_extrapolate( _propExtrapolate.getValueBool() ),
	_defaultMin( _propDefaultMin.getValueDbl() ),
	_defaultMax( _propDefaultMax.getValueDbl() )
{
	setNull();
	setName(aName);
}
//_____________________________________________________________________________
/**
 * Construct a control from an XML Element.
 *
 * @param aElement XML element.
 */
rdControl::rdControl(DOMElement *aElement) :
	rdObject(aElement),
	_isModelControl( _propIsModelControl.getValueBool() ),
	_extrapolate( _propExtrapolate.getValueBool() ),
	_defaultMin( _propDefaultMin.getValueDbl() ),
	_defaultMax( _propDefaultMax.getValueDbl() )
{
	setNull();
	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aControl Control to copy.
 */
rdControl::rdControl(const rdControl &aControl) :
	rdObject(aControl),
	_isModelControl( _propIsModelControl.getValueBool() ),
	_extrapolate( _propExtrapolate.getValueBool() ),
	_defaultMin( _propDefaultMin.getValueDbl() ),
	_defaultMax( _propDefaultMax.getValueDbl() )
{
	setNull();
	copyData(aControl);
}


//=============================================================================
// CONSTRUCTION/DESTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set the member variables to their NULL values.
 */
void rdControl::
setNull()
{
	//generateProperties();
	setupProperties();
	setType("rdControl");
}
//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void rdControl::
setupProperties()
{
	_propIsModelControl.setName("is_model_control");
	_propIsModelControl.setValue(true);
	_propertySet.append(&_propIsModelControl);

	_propExtrapolate.setName("extrapolate");
	_propExtrapolate.setValue(true);
	_propertySet.append(&_propExtrapolate);

	_propDefaultMin.setName("default_min");
	_propDefaultMin.setValue(0.0);
	_propertySet.append(&_propDefaultMin);

	_propDefaultMax.setName("default_max");
	_propDefaultMax.setValue(1.0);
	_propertySet.append(&_propDefaultMax);
}
//_____________________________________________________________________________
/**
 * Copy the member variables of the specified control.
 */
void rdControl::
copyData(const rdControl &aControl)
{
	_isModelControl = aControl._isModelControl;
	_extrapolate = aControl._extrapolate;
	_defaultMin = aControl._defaultMin;
	_defaultMax = aControl._defaultMax;
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
 * @return  Reference to the altered object.
 */
rdControl& rdControl::
operator=(const rdControl &aControl)
{
	// BASE CLASS
	rdObject::operator=(aControl);

	// DATA
	copyData(aControl);

	return(*this);
}


//=============================================================================
// GET AND SET
//=============================================================================
//-----------------------------------------------------------------------------
// IS MODEL CONROL
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set whether or not this control is a model control.  A model control is
 * a control that is expected by a model.  The number of model controls is
 * returned by a call to rdModel::getNX().  Controls that are not model
 * controls may be, for example, controls that are used to set up a
 * simulation.  Such examples might include an initial state of a model
 * (e.g., joint angle, joint angular velocity, ...) or the final time of
 * a siimulation.
 *
 * @param aTrueFalse If true, the control is treated as a model control.   If
 * false, the control is not treated as a model control.
 * @see rdModel::getNX()
 */
void rdControl::
setIsModelControl(bool aTrueFalse)
{
	_isModelControl = aTrueFalse;
}
//_____________________________________________________________________________
/**
 * Get whether or not this control is a model control.  A model control is
 * a control that is expected by a model.  The number of model controls is
 * returned by a call to rdModel::getNX().  Controls that are not model
 * controls may be, for example, controls that are used to set up a
 * simulation.  Such examples might include an initial state of a model
 * (e.g., joint angle, joint angular velocity, ...) or the final time of
 * a siimulation.
 *
 * @return True if this control is a model control, false otherwise.
 */
bool rdControl::
getIsModelControl() const
{
	return(_isModelControl);
}

//-----------------------------------------------------------------------------
// EXTRAPOLATE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set whether or not to extrapolate for control curve evaluations that
 * are outide the region of confidence for a control.
 *
 * @param aTrueFalse If true, extrapolate when needed and possible to
 * determine the value of the control curve.
 */
void rdControl::
setExtrapolate(bool aTrueFalse)
{
	_extrapolate = aTrueFalse;
}
//_____________________________________________________________________________
/**
 * Get whether or not to extrapolate for control curve evaluations that
 * are outide the region of confidence for a control.
 *
 * @return True if this control should use extrapolation when needed and
 * possible,
 */
bool rdControl::
getExtrapolate() const
{
	return(_extrapolate);
}

//-----------------------------------------------------------------------------
// DEFAULT PARAMETER MINIMUM
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the default minimum value of a control parameter.
 * The default minimum is used when no minimum value is specified.
 *
 * @param aMin Minimum value.
 */
void rdControl::
setDefaultParameterMin(double aMin)
{
	_defaultMin = aMin;
	if(_defaultMax < _defaultMin) {
		printf("rdControl.setDefaultParameterMin: ");
		printf("WARN- minimum is greater than maxium, setting max = min.\n");
		_defaultMax = _defaultMin;
	}
}
//_____________________________________________________________________________
/**
 * Get the default minimum value of a control parameter.
 * The default minimum is used when no minimum value is specified.
 *
 * @return Minimum value.
 */
double rdControl::
getDefaultParameterMin() const
{
	return(_defaultMin);
}

//-----------------------------------------------------------------------------
// DEFAULT PARAMETER MAXIMUM
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the default maximum value of a control parameter.
 * The default maximum is used when no maximum value is specified.
 *
 * @param aMax Maximum value.
 */
void rdControl::
setDefaultParameterMax(double aMax)
{
	_defaultMax = aMax;
	if(_defaultMin > _defaultMax) {
		printf("rdControl.setDefaultParameterMin: ");
		printf("WARN- maximum is less than minimum, setting min = max.\n");
		_defaultMin = _defaultMax;
	}
}
//_____________________________________________________________________________
/**
 * Get the default maximum value of a control parameter.
 * The default maximum is used when no maximum value is specified.
 *
 * @return Maximum value.
 */
double rdControl::
getDefaultParameterMax() const
{
	return(_defaultMax);
}

// Convenience methods
//_____________________________________________________________________________
/**
 * Get the first time where parameter is specified. Should be overriden by derived classes
 * that have a defined min time.
 *
 * @return 0.
 */
const double rdControl::getFirstTime() const
{
	string msg = "rdControl.getFirstTime: This method must be overriden.";
	throw(rdException(msg,__FILE__,__LINE__));
	return 0;
}
//_____________________________________________________________________________
/**
 * Get the last time where parameter is specified. Should be overriden by derived classes
 * that have a defined max time.
 *
 * @return 0.
 */
const double rdControl::getLastTime() const
{
	string msg = "rdControl.getLastTime: This method must be overriden.";
	throw(rdException(msg,__FILE__,__LINE__));
	return 1; 
}


//-----------------------------------------------------------------------------
// SIMPLIFY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Simplify the control (e.g., reduce the number of points in the control
 * curve) based on a set of specified properties.  Each implementation
 * is free to require whatever properties are needed to perform
 * the simplification.  Refer to the documentation in derived classes
 * to see what properties are required.
 *
 * @param aProperties Set of properties used to perform the simplify
 * operation.
 * @throw rdException This method does nothing.  It must be overriden
 * in derived classes.
 */
void rdControl::
simplify(const rdPropertySet &aProperties)
{
	string msg = "rdControl.simplify: This method must be overriden.";
	throw(rdException(msg,__FILE__,__LINE__));
}
