// rdPropertyBoolArray.cpp
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
#include "rdPropertyBoolArray.h"


using namespace std;


//=============================================================================
// CONSTRUCTOR(S)
//=============================================================================
//_____________________________________________________________________________
/**
 * Constructor.
 */
rdPropertyBoolArray::
rdPropertyBoolArray(const string &aName,
	const rdArray<bool> &aArray) :
	rdProperty(rdProperty::BoolArray,aName), _array(0)
{
	_array = aArray;
}
//_____________________________________________________________________________
/**
 * Default Constructor.
 */
rdPropertyBoolArray::
rdPropertyBoolArray() :
	rdProperty(rdProperty::BoolArray,"BoolArrayPropertyName"), _array(0)
{
}
//_____________________________________________________________________________
/**
 * Constructor.
 */
rdPropertyBoolArray::
rdPropertyBoolArray(const string &aName,
	int aSize,const bool aArray[]) :
	rdProperty(rdProperty::BoolArray,aName), _array(0)
{
	if(aSize<=0) return;
	if(aArray==NULL) return;
	_array.append(aSize,aArray);
}
//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aProperty Property to be copied.
 */
rdPropertyBoolArray::rdPropertyBoolArray(const rdPropertyBoolArray &aProperty) :
	rdProperty(aProperty), _array(0)
{
	_array = aProperty._array;
}
//_____________________________________________________________________________
/**
 * Construct and return a copy of this property.
 * The property is allocated using the new operator, so the caller is
 * responsible for deleting the returned object.
 *
 * @return Copy of this property.
 */
rdProperty* rdPropertyBoolArray::copy() const
{
	rdProperty *property = new rdPropertyBoolArray(*this);
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
rdPropertyBoolArray& rdPropertyBoolArray::
operator=(const rdPropertyBoolArray &aProperty)
{
	rdProperty::operator =(aProperty);
	_array = aProperty._array;
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
const char* rdPropertyBoolArray::
getTypeAsString() const
{
	return("BoolArray");
}

//-----------------------------------------------------------------------------
// VALUE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the value of this property.
 *
 * @param aArray Array to which this property is to be assigned.
 */
void rdPropertyBoolArray::
setValue(const rdArray<bool>& aArray)
{
	_array = aArray;
}
//_____________________________________________________________________________
/**
 * Set the value of this property.
 *
 * @param aSize Size of the specified array.
 * @param aValue Array to which this property is to be assigned.
 */
void rdPropertyBoolArray::
setValue(int aSize,const bool aArray[])
{
	_array.setSize(0);
	if(aSize<=0) return;
	if(aArray==NULL) return;
	_array.append(aSize,aArray);
}
//_____________________________________________________________________________
/**
 * Get a reference to the value of this property.  Note that the returned
 * reference can be used to change the value of this property.
 *
 * @return Reference to the value of this property.
 */
rdArray<bool>& rdPropertyBoolArray::
getValueBoolArray()
{
	return(_array);
}
//_____________________________________________________________________________
/**
 * Get a constant reference to the value of this property.
 *
 * @return Reference to the value of this property.
 */
const rdArray<bool>& rdPropertyBoolArray::
getValueBoolArray() const
{
	return(_array);
}
//_____________________________________________________________________________
/**
 * Get a constantString represeting the value of this property.
 *
 * @return Constant String represeting the value of this property.
 */
const string &rdPropertyBoolArray::
toString()
{
	string str = "(";
	for(int i=0; i < _array.getSize(); i++){
		str += (_array[i]?"True ":"False ");
	}
	str += ")";
	_valueString = str;
	return (_valueString);
}
