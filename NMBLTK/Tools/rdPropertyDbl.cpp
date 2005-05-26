// rdPropertyDbl.cpp
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
#include "rdPropertyDbl.h"


using namespace std;

//=============================================================================
// CONSTRUCTOR(S)
//=============================================================================
//_____________________________________________________________________________
/**
 * Constructor.
 */
rdPropertyDbl::
rdPropertyDbl(const string &aName,double aValue) :
	rdProperty(rdProperty::Dbl,aName)
{
	_value = aValue;
}
//_____________________________________________________________________________
/**
 * Default constructor.
 */
rdPropertyDbl::
rdPropertyDbl() :
	rdProperty(rdProperty::Dbl,"DblPropertyName")
{
	_value = 0.0;
}
//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aProperty Property to be copied.
 */
rdPropertyDbl::rdPropertyDbl(const rdPropertyDbl &aProperty) :
	rdProperty(aProperty)
{
	_value = aProperty.getValueDbl();
}
//_____________________________________________________________________________
/**
 * Construct and return a copy of this property.
 * The property is allocated using the new operator, so the caller is
 * responsible for deleting the returned object.
 *
 * @return Copy of this property.
 */
rdProperty* rdPropertyDbl::copy() const
{
	rdProperty *property = new rdPropertyDbl(*this);
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
rdPropertyDbl& rdPropertyDbl::
operator=(const rdPropertyDbl &aProperty)
{
	rdProperty::operator =(aProperty);
	_value = aProperty.getValueDbl();
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
const char* rdPropertyDbl::
getTypeAsString() const
{
	return("Dbl");
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
void rdPropertyDbl::
setValue(double aValue)
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
double& rdPropertyDbl::
getValueDbl()
{
	return(_value);
}
//_____________________________________________________________________________
/**
 * Get a constant reference to the value of this property.
 *
 * @return Constant reference to the value of this property.
 */
const double& rdPropertyDbl::
getValueDbl() const
{
	return(_value);
}
//_____________________________________________________________________________
/**
 * Get a constant String represeting the value of this property.
 *
 * @return Constant String represeting the value of this property.
 */
const string &rdPropertyDbl::
toString()
{
	char dbl[32];
	sprintf(dbl, "%lf", _value);
	_valueString = string(dbl);
	return (_valueString);
}
