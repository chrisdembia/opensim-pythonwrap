// rdPropertyIntArray.cpp
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
#include "rdPropertyIntArray.h"


using namespace std;


//=============================================================================
// CONSTRUCTOR(S)
//=============================================================================
//_____________________________________________________________________________
/**
 * Constructor.
 */
rdPropertyIntArray::
rdPropertyIntArray(const string &aName,
	const rdArray<int> &aArray) :
	rdProperty(rdProperty::IntArray,aName), _array(0)
{
	_array = aArray;
}
//_____________________________________________________________________________
/**
 * Default Constructor.
 */
rdPropertyIntArray::
rdPropertyIntArray() :
	rdProperty(rdProperty::IntArray,"IntArrayPropertyName"), _array(0)
{
}
//_____________________________________________________________________________
/**
 * Constructor.
 */
rdPropertyIntArray::
rdPropertyIntArray(const string &aName,
	int aSize,const int aArray[]) :
	rdProperty(rdProperty::IntArray,aName), _array(0)
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
rdPropertyIntArray::rdPropertyIntArray(const rdPropertyIntArray &aProperty) :
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
rdProperty* rdPropertyIntArray::copy() const
{
	rdProperty *property = new rdPropertyIntArray(*this);
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
rdPropertyIntArray& rdPropertyIntArray::
operator=(const rdPropertyIntArray &aProperty)
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
const char* rdPropertyIntArray::
getTypeAsString() const
{
	return("IntArray");
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
void rdPropertyIntArray::
setValue(const rdArray<int>& aArray)
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
void rdPropertyIntArray::
setValue(int aSize,const int aArray[])
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
rdArray<int>& rdPropertyIntArray::
getValueIntArray()
{
	return(_array);
}
//_____________________________________________________________________________
/**
 * Get a constant reference to the value of this property.
 *
 * @return Reference to the value of this property.
 */
const rdArray<int>& rdPropertyIntArray::
getValueIntArray() const
{
	return(_array);
}
//_____________________________________________________________________________
/**
 * Get a constant String represeting the value of this property.
 *
 * @return Constant String represeting the value of this property.
 */
const string &rdPropertyIntArray::
toString()
{
	string str = "(";
	char intString[32];
	for(int i=0; i < _array.getSize(); i++){
		sprintf(intString, "%d ", _array[i]);
		str += string(intString);
	}
	str += ")";
	_valueString = str;
	return (_valueString);
}
