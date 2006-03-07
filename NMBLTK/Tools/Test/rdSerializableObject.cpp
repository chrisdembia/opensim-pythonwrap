// rdSerializableObject.cpp
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
#include "rdSerializableObject.h"
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
rdSerializableObject::
rdSerializableObject()
{
	setNull();
	setupSerializedMembers();
}
//_____________________________________________________________________________
/**
 * File constructor.
 */
rdSerializableObject::
rdSerializableObject(const string &aFileName) :
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
rdSerializableObject::rdSerializableObject(DOMElement *aElement) :
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
 * @param aControl Control to copy.
 */
rdSerializableObject::rdSerializableObject(const rdSerializableObject &aControl)
{
	setNull();
	setupSerializedMembers();
	*this = aControl;
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
rdObject* rdSerializableObject::
copy() const
{
	rdSerializableObject *object = new rdSerializableObject(*this);
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
rdObject* rdSerializableObject::
copy(DOMElement *aElement) const
{
	// ESTABLISH RELATIONSHIP WITH XML NODE
	rdSerializableObject *node = new rdSerializableObject(aElement);

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
void rdSerializableObject::
setNull()
{
	setType("rdSerializableObject");
}
//_____________________________________________________________________________
/**
 * Set up the serialized member variables.  This involves both generating
 * the properties and connecting them to the local pointers of the serialized
 * member variables.
 */
void rdSerializableObject::
setupSerializedMembers()
{
	int i;

	// Bool
	rdPropertyBool pBool("Test_Bool",true);
	pBool.setComment("Comment on a boolean");
	_propertySet.append(pBool.copy());

	// Int
	rdPropertyInt pInt("Test_Int",0);
	pInt.setComment("Comment on a Int");
	_propertySet.append(pInt.copy());

	// Dbl
	rdPropertyDbl pDbl("Test_Dbl",0.0);
	pDbl.setComment("Comment on a Double");
	_propertySet.append(pDbl.copy());

	// Str
	rdPropertyStr pStr("Test_Str","ABC");
	pStr.setComment("Comment on a String");
	_propertySet.append(pStr.copy());

	// Obj
	rdSerializableObject2 obj;
	rdPropertyObj pObj("Test_Obj",obj);
	pObj.setComment("Comment on an Object");
	_propertySet.append(pObj.copy());

	// IntArray
	rdArray<int> arrayInt(2);
	arrayInt.setSize(4);
	for(i=0;i<arrayInt.getSize();i++) arrayInt[i] = i;
	rdPropertyIntArray pIntArray("Test_IntArray",arrayInt);
	pIntArray.setComment("Comment on an int-array");
	_propertySet.append(pIntArray.copy());

	// DblArray
	rdArray<double> arrayDbl(0.0);
	arrayDbl.setSize(4);
	for(i=0;i<arrayDbl.getSize();i++) arrayDbl[i] = (double)i;
	rdPropertyDblArray pDblArray("Test_DblArray",arrayDbl);
	pDblArray.setComment("Comment on a Dbl-array");
	_propertySet.append(pDblArray.copy());

	// StrArray
	rdArray<string> arrayStr("");
	arrayStr.setSize(4);
	arrayStr[0] = "abc";
	arrayStr[1] = "def";
	arrayStr[2] = "ghi";
	arrayStr[3] = "jkl";
	rdPropertyStrArray pStrArray("Test_StrArray",arrayStr);
	pStrArray.setComment("Comment on a str-array");
	_propertySet.append(pStrArray.copy());

	// ObjArray
	rdArrayPtrs<rdObject> arrayObj;
	rdSerializableObject2 object;
	object.setName("Obj1");
	arrayObj.append(object.copy());
	object.setName("Obj2");
	arrayObj.append(object.copy());
	object.setName("Obj3");
	arrayObj.append(object.copy());
	rdPropertyObjArray pObjArray("Test_ObjArray",arrayObj);
	pObjArray.setComment("Comment on Object Array");
	_propertySet.append(pObjArray.copy());
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
rdSerializableObject& rdSerializableObject::
operator=(const rdSerializableObject &aObject)
{
	rdObject::operator=(aObject);
	return(*this);
}


//=============================================================================
// SERIALIZATION
//=============================================================================
//-----------------------------------------------------------------------------
// DEFAULT OBJECTS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Determine whether a specified object is a valid type for this
 * object.  This method returns true only for objects of type
 * rdSerializableObject2.
 *
 * @param aObject Object to be tested as valid or invalid.
 */
bool rdSerializableObject::
isValidDefaultType(const rdObject *aObject) const
{
	if(aObject==NULL) return(false);

	string type1 = "rdSerializableObject2";
	if(type1 == aObject->getType()) return(true);

	return(false);
}

