// rdPropertyObjArray.cpp
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
#include "rdPropertyObjArray.h"
#include "rdObject.h"


using namespace std;


//=============================================================================
// CONSTRUCTOR(S)
//=============================================================================
//_____________________________________________________________________________
/**
 * Default constructor.
 *
 * Construct an empty object-array property without a name.
 */
rdPropertyObjArray::
rdPropertyObjArray() :
	rdProperty(rdProperty::ObjArray,"")
{
	_array.setSize(0);
}
//_____________________________________________________________________________
/**
 * Constructor.
 *
 * Construct an empty object-array property with a specified name.
 *
 * @param aName Name of the object array.
 */
rdPropertyObjArray::
rdPropertyObjArray(const string &aName) :
	rdProperty(rdProperty::ObjArray,aName)
{
	_array.setSize(0);
}
//_____________________________________________________________________________
/**
 * Constructor.
 *
 * Construct an object-array property with a specified name initialized to
 * a specified array of objects.  Note that copies of the objects in the
 * specified array are made.
 *
 * @param aName Name of the object array.
 * @param aArray Array used to initialize the object array.
 */
rdPropertyObjArray::
rdPropertyObjArray(const string &aName,const rdArrayPtrs<rdObject> &aArray) :
	rdProperty(rdProperty::ObjArray,aName)
{
	_array = aArray;
}
//_____________________________________________________________________________
/**
 * Constructor.
 */
rdPropertyObjArray::
rdPropertyObjArray(const string &aName,
	int aSize,const rdObject **aArray) :
	rdProperty(rdProperty::ObjArray,aName)
{
	if(aSize<=0) return;
	if(aArray==NULL) return;
	for(int i=0;i<aSize;i++) {
		_array.append( aArray[i]->copy() );
	}
}
//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aProperty Property to be copied.
 */
rdPropertyObjArray::rdPropertyObjArray(const rdPropertyObjArray &aProperty) :
	rdProperty(aProperty)
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
rdProperty* rdPropertyObjArray::copy() const
{
	rdProperty *property = new rdPropertyObjArray(*this);
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
rdPropertyObjArray& rdPropertyObjArray::
operator=(const rdPropertyObjArray &aProperty)
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
const char* rdPropertyObjArray::
getTypeAsString() const
{
	return("ObjArray");
}

//-----------------------------------------------------------------------------
// VALUE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the value of this property.
 *
 * @param aArray Array to which this property is to be assigned.  Note
 * that copies of the objects in the specified array are NOT made.
 */
void rdPropertyObjArray::
setValue(const rdArrayPtrs<rdObject>& aArray)
{
	_array = aArray;
}
//_____________________________________________________________________________
/**
 * Set the value of this property.
 *
 * @param aSize Size of the specified array.
 * @param aValue Array to which this property is to be assigned.  Note
 * that copies of the objects in the specified array are NOT made.
 */
void rdPropertyObjArray::
setValue(int aSize,rdObject** aArray)
{
	_array.setSize(0);
	if(aSize<=0) return;
	if(aArray==NULL) return;
	for(int i=0;i<aSize;i++) {
		_array.append(aArray[i]);
		aArray++;
	}
}
//_____________________________________________________________________________
/**
 * Get a reference to the value of this property.  Note that the returned
 * reference can be used to change the value of this property.
 *
 * @return Reference to the value of this property.
 */
rdArrayPtrs<rdObject>& rdPropertyObjArray::
getValueObjArray()
{
	return(_array);
}
//_____________________________________________________________________________
/**
 * Get a constant reference to the value of this property.
 *
 * @return Reference to the value of this property.
 */
const rdArrayPtrs<rdObject>& rdPropertyObjArray::
getValueObjArray() const
{
	return(_array);
}
//_____________________________________________________________________________
/**
 * Get a constant String represeting the value of this property.
 *
 * @return Constant String represeting the value of this property.
 */
const string &rdPropertyObjArray::
toString()
{
	_valueString = "(Array of objects)";
	return (_valueString);
}
