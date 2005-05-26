// rdPropertyDblArray.cpp
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
#include "rdPropertyDblArray.h"


using namespace std;


//=============================================================================
// CONSTRUCTOR(S)
//=============================================================================
//_____________________________________________________________________________
/**
 * Constructor.
 */
rdPropertyDblArray::
rdPropertyDblArray(const string &aName,
	const rdArray<double> &aArray) :
	rdProperty(rdProperty::DblArray,aName), _array(0.0)
{
	_array = aArray;
}
//_____________________________________________________________________________
/**
 * Default Constructor.
 */
rdPropertyDblArray::
rdPropertyDblArray() :
	rdProperty(rdProperty::DblArray,"BoolArrayPropertyName"), _array(0.0)
{

}
//_____________________________________________________________________________
/**
 * Constructor.
 */
rdPropertyDblArray::
rdPropertyDblArray(const string &aName,
	int aSize,const double aArray[]) :
	rdProperty(rdProperty::DblArray,aName), _array(0.0)
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
rdPropertyDblArray::rdPropertyDblArray(const rdPropertyDblArray &aProperty) :
	rdProperty(aProperty), _array(0.0)
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
rdProperty* rdPropertyDblArray::copy() const
{
	rdProperty *property = new rdPropertyDblArray(*this);
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
rdPropertyDblArray& rdPropertyDblArray::
operator=(const rdPropertyDblArray &aProperty)
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
const char* rdPropertyDblArray::
getTypeAsString() const
{
	return("DblArray");
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
void rdPropertyDblArray::
setValue(const rdArray<double>& aArray)
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
void rdPropertyDblArray::
setValue(int aSize,const double aArray[])
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
rdArray<double>& rdPropertyDblArray::
getValueDblArray()
{
	return(_array);
}
//_____________________________________________________________________________
/**
 * Get a constant reference to the value of this property.
 *
 * @return Reference to the value of this property.
 */
const rdArray<double>& rdPropertyDblArray::
getValueDblArray() const
{
	return(_array);
}
//_____________________________________________________________________________
/**
 * Get value at specific index.
 *
 * @return Reference to the value of this property at specified index.
 */
double& rdPropertyDblArray::getDblValueAt(int aIndex) const
{
	return _array[aIndex];
}
//_____________________________________________________________________________
/**
 * Set value at specific index.
 *
 * 
 */
void rdPropertyDblArray::setDblValueAt(int aIndex, const double aDouble) const
{
	_array[aIndex] = aDouble;
}
//_____________________________________________________________________________
/**
 * Get the size of rdArray used by property.
 *
 * @return size of rdArray used by property.
 */
const int rdPropertyDblArray::getArraySize() const
{
	return _array.getSize();
}
//_____________________________________________________________________________
/**
 * Get a constant String represeting the value of this property.
 *
 * @return Constant String represeting the value of this property.
 */
const string &rdPropertyDblArray::
toString()
{
	string str = "(";
	char dbl[32];
	for(int i=0; i < _array.getSize(); i++){
		sprintf (dbl, "%lf\n", _array[i]);
		str += dbl;
	}
	str += ")";
	_valueString = str;
	return (_valueString);
}
