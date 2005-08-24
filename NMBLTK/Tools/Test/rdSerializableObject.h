// rdSerializableObject.h:
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fc.anderson@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdSerializableObject_h__
#define __rdSerializableObject_h__


// INCLUDES
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Tools/rdObject.h>

//extern template class RDTOOLS_API rdArray<double>;

//=============================================================================
//=============================================================================
/**
 * An object for mainly for testing XML serialization.
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class rdSerializableObject : public rdObject
{

//=============================================================================
// MEMBER DATA
//=============================================================================

//=============================================================================
// METHODS
//=============================================================================
public:
	rdSerializableObject();
	rdSerializableObject(const std::string &aFileName);
	rdSerializableObject(DOMElement *aElement);
	rdSerializableObject(const rdSerializableObject &aNode);
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;
private:
	void setNull();
	void setupSerializedMembers();

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
	rdSerializableObject& operator=(const rdSerializableObject &aObject);

	//--------------------------------------------------------------------------
	// XML SERIALIZATION
	//--------------------------------------------------------------------------
	virtual bool isValidDefaultType(const rdObject *aObject) const;

//=============================================================================
};	// END of class rdSerializableObject
//=============================================================================
//=============================================================================

#endif // __rdSerializableObject_h__
