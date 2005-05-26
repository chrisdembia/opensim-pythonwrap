// rdPropertyStrArray.cpp
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
#include "rdPropertyStrArray.h"


using namespace std;


//=============================================================================
// CONSTRUCTOR(S)
//=============================================================================
//_____________________________________________________________________________
/**
 * Constructor.
 */
rdPropertyStrArray::
rdPropertyStrArray(const string &aName,
	const rdArray<string> &aArray) :
	rdProperty(rdProperty::StrArray,aName), _array("")
{
	_array = aArray;
}
//_____________________________________________________________________________
/**
 * Default Constructor.
 */
rdPropertyStrArray::
rdPropertyStrArray() :
	rdProperty(rdProperty::StrArray,"StrArrayPropertyName"), _array("")
{
}
//_____________________________________________________________________________
/**
 * Constructor.
 */
rdPropertyStrArray::
rdPropertyStrArray(const string &aName,
	int aSize,const string *aArray) :
	rdProperty(rdProperty::StrArray,aName), _array("")
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
rdPropertyStrArray::rdPropertyStrArray(const rdPropertyStrArray &aProperty) :
	rdProperty(aProperty), _array("")
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
rdProperty* rdPropertyStrArray::copy() const
{
	rdProperty *property = new rdPropertyStrArray(*this);
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
rdPropertyStrArray& rdPropertyStrArray::
operator=(const rdPropertyStrArray &aProperty)
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
const char* rdPropertyStrArray::
getTypeAsString() const
{
	return("StrArray");
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
void rdPropertyStrArray::
setValue(const rdArray<string>& aArray)
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
void rdPropertyStrArray::
setValue(int aSize,const string *aArray)
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
rdArray<string>& rdPropertyStrArray::
getValueStrArray()
{
	return(_array);
}
//_____________________________________________________________________________
/**
 * Get a constant reference to the value of this property.
 *
 * @return Reference to the value of this property.
 */
const rdArray<string>& rdPropertyStrArray::
getValueStrArray() const
{
	return(_array);
}
//_____________________________________________________________________________
/**
 * Get a constant String represeting the value of this property.
 *
 * @return Constant String represeting the value of this property.
 */
const string &rdPropertyStrArray::
toString()
{
	_valueString = "(rdPropertyStrArray)";
	return (_valueString);

}
