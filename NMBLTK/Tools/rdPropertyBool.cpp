// rdPropertyBool.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//============================================================================
// INCLUDES
//============================================================================
#include "rdPropertyBool.h"


using namespace std;


//=============================================================================
// CONSTRUCTOR(S)
//=============================================================================
//_____________________________________________________________________________
/**
 * Constructor.
 */
rdPropertyBool::
rdPropertyBool(const string &aName,bool aValue) :
rdProperty(rdProperty::Bool,aName)
{
	_value = aValue;
}
//_____________________________________________________________________________
/**
 * Default Constructor.
 */
rdPropertyBool::
rdPropertyBool() :
rdProperty(rdProperty::Bool,"BoolPropertyName")
{
	_value = false;
}
//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aProperty Property to be copied.
 */
rdPropertyBool::rdPropertyBool(const rdPropertyBool &aProperty) :
	rdProperty(aProperty)
{
	_value = aProperty.getValueBool();
}
//_____________________________________________________________________________
/**
 * Construct and return a copy of this property.
 * The property is allocated using the new operator, so the caller is
 * responsible for deleting the returned object.
 *
 * @return Copy of this property.
 */
rdProperty* rdPropertyBool::copy() const
{
	rdProperty *property = new rdPropertyBool(*this);
	return(property);
}


//=============================================================================
// OPERATORS
//=============================================================================
//-----------------------------------------------------------------------------
// ASSIGNMENT
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Assign this property to another.
 *
 * @param aProperty Property to which to assign this property.
 * @return Reference to this property.
 */
rdPropertyBool& rdPropertyBool::
operator=(const rdPropertyBool &aProperty)
{
	rdProperty::operator =(aProperty);
	_value = aProperty.getValueBool();
	return(*this);
}


//=============================================================================
// GET AND SET
//=============================================================================
//-----------------------------------------------------------------------------
// TYPE AS STRING
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the type of this property as a string.
 *
 * @return Type of the property.
 */
const char* rdPropertyBool::
getTypeAsString() const
{
	return("Bool");
}

//-----------------------------------------------------------------------------
// VALUE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the value of this property.
 *
 * @param aValue Value to which this property is assigned.
 */
void rdPropertyBool::
setValue(bool aValue)
{
	_value = aValue;
}
//_____________________________________________________________________________
/**
 * Get a reference to the value of this property.  Note that the returned
 * reference can be used to change the value of this property.
 *
 * @return Reference to the value of this property.
 */
bool& rdPropertyBool::
getValueBool()
{
	return(_value);
}
//_____________________________________________________________________________
/**
 * Get a constant reference to the value of this property.
 *
 * @return Contant reference to the value of this property.
 */
const bool& rdPropertyBool::
getValueBool() const
{
	return(_value);
}
//_____________________________________________________________________________
/**
 * Get a String represeting the value of this property.
 *
 * @return Constant reference to a String represeting the value of this property.
 */
const string &rdPropertyBool::
toString()
{
	_valueString = _value? "True" : "False";
	return (_valueString);
}
