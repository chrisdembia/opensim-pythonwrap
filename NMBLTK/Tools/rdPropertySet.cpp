// rdPropertySet.cpp
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
#include "rdPropertySet.h"
#include "rdPropertyInt.h"

using namespace std;


//=============================================================================
// CONSTRUCTOR(S)
//=============================================================================
//_____________________________________________________________________________
/**
 * Constructor.
 */
rdPropertySet::rdPropertySet()
{
	_array.setMemoryOwner(false);
}
//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aSet Set of properties to be copied.
 */
rdPropertySet::rdPropertySet(const rdPropertySet &aSet)
{
	_array = aSet._array;
	_array.setMemoryOwner(false);

}


//=============================================================================
// OPERATORS
//=============================================================================
//-----------------------------------------------------------------------------
// OUTPUT (<<)
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Implementation of the output operator.
 *
 * @param aOut Output stream.
 * @param aArray Array to be output.
 * @return Reference to the output stream.
ostream&
operator<<(ostream &aOut,const rdPropertySet &aSet)
{
	aOut << "\nProperty Set:\n";

	int i;
	for(i=0;i<aSet.getSize();i++)  {
		aOut << aSet.get(i) << "\n";
	}

	return(aOut);
}
 */


//=============================================================================
// EMPTY?
//=============================================================================
//_____________________________________________________________________________
/**
 * Determine whether or not this property set is empty.
 *
 * @returns True if empty; false otherwise.
 */
bool rdPropertySet::
isEmpty() const
{
	if(_array.getSize()<=0) return(true);
	return(false);
}


//=============================================================================
// SIZE
//=============================================================================
//_____________________________________________________________________________
/**
 * Get the number of properties in the set, or, equivalently, the size of
 * the property set.
 *
 * @returns Size or number of properties in this set.
 */
int rdPropertySet::
getSize() const
{
	return(_array.getSize());
}


//=============================================================================
// GET
//=============================================================================
//_____________________________________________________________________________
/**
 * Get a reference to a property by index.
 *
 * @param aIndex Index of the property to get.
 * @throws rdException if the index is out of bounds.
 */
rdProperty* rdPropertySet::
get(int aIndex)
{
	// NO SUCH PROPERTY - THROW EXCEPTION
	if((aIndex<0)||(aIndex>=_array.getSize())) {
		string msg = "rdPropertySet.get(int): Index is out of bounds.";
		throw rdException(msg,__FILE__,__LINE__);
	}

	return(_array[aIndex]);
}
//_____________________________________________________________________________
/**
 * Get a constant reference to a property by index.
 *
 * @param aIndex Index of the property to get.
 * @throws rdException if the index is out of bounds.
 */
const rdProperty* rdPropertySet::
get(int aIndex) const
{
	// NO SUCH PROPERTY - THROW EXCEPTION
	if((aIndex<0)||(aIndex>=_array.getSize())) {
		string msg = "rdPropertySet.get(int): Index is out of bounds.";
		throw rdException(msg,__FILE__,__LINE__);
	}

	return(_array[aIndex]);
}
//_____________________________________________________________________________
/**
 * Get the first property in the set that has a specified name.
 *
 * @param aName Name of the property to get.
 * @throws rdException if there is no such property.
 */
rdProperty* rdPropertySet::
get(const string &aName)
{
	int i;
	rdPropertyInt prop(aName,0);
	for(i=0;i<_array.getSize();i++) {
		if((*_array[i]) == prop) return(_array[i]);
	}
		
	// NO SUCH PROPERTY - THROW EXCEPTION
	string msg = "rdPropertySet.get: No property named " + aName;
	throw rdException(msg,__FILE__,__LINE__);
}
//_____________________________________________________________________________
/**
 * Get the first property in the set that has a specified name.
 *
 * @param aName Name of the property to get.
 * @throws rdException if there is no such property.
 */
const rdProperty* rdPropertySet::
get(const string &aName) const
{
	int i;
	rdPropertyInt prop(aName,0);
	for(i=0;i<_array.getSize();i++) {
		if((*_array[i]) == prop) return(_array[i]);
	}
		
	// NO SUCH PROPERTY - THROW EXCEPTION
	string msg = "rdPropertySet.get: No property named " + aName;
	throw rdException(msg,__FILE__,__LINE__);
}


//=============================================================================
// APPEND
//=============================================================================
//_____________________________________________________________________________
/**
 * Append a property to the set.
 *
 * @param aProperty Property to be appended.  Note that a copy is NOT made.
 */
void rdPropertySet::
append(rdProperty *aProperty)
{
	_array.append(aProperty);
}


//=============================================================================
// REMOVE
//=============================================================================
//_____________________________________________________________________________
/**
 * Remove the first property in the set that has a specified name.
 *
 * @param aName Name of the property to remove.
 * @throws rdException if there is no such property.
 */
void rdPropertySet::
remove(const string &aName)
{
	int i;
	rdPropertyInt prop(aName,0);
	for(i=0;i<_array.getSize();i++) {
		if((*_array[i]) == prop) {
			_array.remove(i);
			return;
		}
	}
		
	// NO SUCH PROPERTY - THROW EXCEPTION
	string msg = "rdPropertySet.get: No property named " + aName;
	throw rdException(msg,__FILE__,__LINE__);
}


//=============================================================================
// CLEAR
//=============================================================================
//_____________________________________________________________________________
/**
 * Clear this property set of all properties.
 */
void rdPropertySet::
clear()
{
	_array.setSize(0);
	_array.trim();
}
