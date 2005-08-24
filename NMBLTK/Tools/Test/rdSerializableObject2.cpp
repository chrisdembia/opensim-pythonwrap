// rdSerializableObject2.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fc.anderson@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Tools/rdPropertyBool.h>
#include <NMBLTK/Tools/rdPropertyInt.h>
#include <NMBLTK/Tools/rdPropertyDbl.h>
#include <NMBLTK/Tools/rdPropertyStr.h>
#include <NMBLTK/Tools/rdPropertyObj.h>
#include <NMBLTK/Tools/rdPropertyIntArray.h>
#include <NMBLTK/Tools/rdPropertyDblArray.h>
#include <NMBLTK/Tools/rdPropertyStrArray.h>
#include <NMBLTK/Tools/rdPropertyObjArray.h>
#include "rdSerializableObject2.h"


using namespace std;


//=============================================================================
// STATIC CONSTANTS
//=============================================================================


//=============================================================================
// CONSTRUCTOR(S)
//=============================================================================
//_____________________________________________________________________________
/**
 * Default constructor.
 */
rdSerializableObject2::
rdSerializableObject2()
{
	setNull();
	setupSerializedMembers();
}
//_____________________________________________________________________________
/**
 * File constructor.
 */
rdSerializableObject2::
rdSerializableObject2(const string &aFileName) :
	rdObject(aFileName)
{
	setNull();
	setupSerializedMembers();
	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Construct a control node from an XML Element.
 *
 * @param aElement XML element.
 */
rdSerializableObject2::
rdSerializableObject2(DOMElement *aElement) :
	rdObject(aElement)
{
	setNull();
	setupSerializedMembers();
	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aObject Object to copy.
 */
rdSerializableObject2::
rdSerializableObject2(const rdSerializableObject2 &aObject)
{
	setNull();
	setupSerializedMembers();
	*this = aObject;
}
//_____________________________________________________________________________
/**
 * Construct and return a copy of this object.
 *
 * The object is allocated using the new operator, so the caller is
 * responsible for deleting the returned object.
 *
 * @return Copy of this object.
 */
rdObject* rdSerializableObject2::
copy() const
{
	rdSerializableObject2 *object = new rdSerializableObject2(*this);
	return(object);
}
//_____________________________________________________________________________
/**
 * Copy this control and modify the copy so that it is consistent
 * with a specified XML element node.
 *
 * The copy is constructed by first using the contructor for the DOMElement
 * in order to establish the relationship of the control with the
 * XML node.  Then, the assignment operator is used to set all member variables
 * of the copy to the values of this object.  Finally, the data members of
 * the copy are updated from the DOMElment using updateFromXMLNode().
 *
 * @param aElement XML element. 
 * @return Pointer to a copy of this actuator.
 */
rdObject* rdSerializableObject2::
copy(DOMElement *aElement) const
{
	// ESTABLISH RELATIONSHIP WITH XML NODE
	rdSerializableObject2 *node = new rdSerializableObject2(aElement);

	// ASSIGNMENT OPERATOR
	*node = *this;

	// UPDATE BASED ON NODE
	node->updateFromXMLNode();

	return(node);
}


//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Set NULL value for the member variables.
 */
void rdSerializableObject2::
setNull()
{
	setType("rdSerializableObject2");
}
//_____________________________________________________________________________
/**
 * Set up the serialized member variables.  This involves both generating
 * the properties and connecting them to the local pointers used to access
 * the serialized member variables.
 */
void rdSerializableObject2::
setupSerializedMembers()
{
	// Bool
	rdPropertyBool pBool("Test_Bool2",false);
	_propertySet.append(pBool.copy());

	// DblArray
	rdArray<double> dblArray(0.1);
	dblArray.setSize(3);
	rdPropertyDblArray pDblArray("Test_DblArray2",dblArray);
	_propertySet.append(pDblArray.copy());
}


//=============================================================================
// OPERATORS
//=============================================================================
//-----------------------------------------------------------------------------
// ASSIGNMENT
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Assignment operator.
 *
 * @return Reference to the altered object.
 */
rdSerializableObject2& rdSerializableObject2::
operator=(const rdSerializableObject2 &aObject)
{
	rdObject::operator=(aObject);
	return(*this);
}


//=============================================================================
// SET / GET
//=============================================================================


