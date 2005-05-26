// rdPropertyInt.cpp
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
#include "rdPropertyInt.h"


using namespace std;


//=============================================================================
// CONSTRUCTOR(S)
//=============================================================================
//_____________________________________________________________________________
/**
 * Constructor.
 */
rdPropertyInt::
rdPropertyInt(const string &aName,int aValue) :
rdProperty(rdProperty::Int,aName)
{
	_value = aValue;
}
//_____________________________________________________________________________
/**
 * Default Constructor.
 */
rdPropertyInt::
rdPropertyInt() :
rdProperty(rdProperty::Int,"IntPropertyName")
{
	_value = 0;
}
//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aProperty Property to be copied.
 */
rdPropertyInt::rdPropertyInt(const rdPropertyInt &aProperty) :
	rdProperty(aProperty)
{
	_value = aProperty.getValueInt();
}
//_____________________________________________________________________________
/**
 * Construct and return a copy of this property.
 * The property is allocated using the new operator, so the caller is
 * responsible for deleting the returned object.
 *
 * @return Copy of this property.
 */
rdProperty* rdPropertyInt::copy() const
{
	rdProperty *property = new rdPropertyInt(*this);
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
rdPropertyInt& rdPropertyInt::
operator=(const rdPropertyInt &aProperty)
{
	rdProperty::operator =(aProperty);
	_value = aProperty.getValueInt();
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
const char* rdPropertyInt::
getTypeAsString() const
{
	return("Int");
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
void rdPropertyInt::
setValue(int aValue)
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
int& rdPropertyInt::
getValueInt()
{
	return(_value);
}
//_____________________________________________________________________________
/**
 * Get a constant reference to the value of this property.
 *
 * @return Contant reference to the value of this property.
 */
const int& rdPropertyInt::
getValueInt() const
{
	return(_value);
}
//_____________________________________________________________________________
/**
 * Get a constant String represeting the value of this property.
 *
 * @return Constant String represeting the value of this property.
 */
const string &rdPropertyInt::
toString()
{
	char intString[32];
	sprintf(intString, "%d", _value);
	_valueString = string(intString);
	return (_valueString);
}
