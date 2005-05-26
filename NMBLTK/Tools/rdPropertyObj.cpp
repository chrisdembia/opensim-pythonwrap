// rdPropertyObj.cpp
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
#include "rdPropertyObj.h"


using namespace std;


//=============================================================================
// CONSTRUCTOR(S)
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
rdPropertyObj::~rdPropertyObj()
{
	if(_value!=NULL) { delete _value;  _value=NULL; }
}
//_____________________________________________________________________________
/**
 * Constructor.
 */
rdPropertyObj::
rdPropertyObj(const string &aName,const rdObject &aValue) :
rdProperty(rdProperty::Obj,aName)
{
	_value = aValue.copy();
	_value->setName(aName);
}
//_____________________________________________________________________________
/**
 * Default Constructor.
 */
rdPropertyObj::
rdPropertyObj() :
rdProperty(rdProperty::Obj,"Object")
{
	_value = 0;
}
//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aProperty Property to be copied.
 */
rdPropertyObj::rdPropertyObj(const rdPropertyObj &aProperty) :
	rdProperty(aProperty)
{
	_value = aProperty.getValueObj().copy();
}
//_____________________________________________________________________________
/**
 * Construct and return a copy of this property.
 * The property is allocated using the new operator, so the caller is
 * responsible for deleting the returned object.
 *
 * @return Copy of this property.
 */
rdProperty* rdPropertyObj::copy() const
{
	rdProperty *property = new rdPropertyObj(*this);
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
rdPropertyObj& rdPropertyObj::
operator=(const rdPropertyObj &aProperty)
{
	rdProperty::operator =(aProperty);
	if(_value!=NULL) { delete _value;  _value=NULL; }
	_value = aProperty.getValueObj().copy();
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
const char* rdPropertyObj::
getTypeAsString() const
{
	return("Obj");
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
void rdPropertyObj::
setValue(const rdObject &aValue)
{
	if(_value!=NULL) { delete _value;  _value=NULL; }
	_value = aValue.copy();
}
//_____________________________________________________________________________
/**
 * Get a reference to the value of this property.  Note that the returned
 * reference can be used to change the value of this property.
 *
 * @return Reference to the value of this property.
 */
rdObject& rdPropertyObj::
getValueObj()
{
	return((*_value));
}
//_____________________________________________________________________________
/**
 * Get a constant reference to the value of this property.
 *
 * @return Contant reference to the value of this property.
 */
const rdObject& rdPropertyObj::
getValueObj() const
{
	return((*_value));
}
//_____________________________________________________________________________
/**
 * Get a constant String represeting the value of this property.
 *
 * @return Constant String represeting the value of this property.
 */
const string &rdPropertyObj::
toString()
{
	_valueString = "(Object)";
	return (_valueString);
}
