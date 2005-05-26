// rdSerializableObject2.h:
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fc.anderson@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdSerializableObject2_h__
#define __rdSerializableObject2_h__


// INCLUDES
#include <RD/Tools/rdTools.h>
#include <RD/Tools/rdObject.h>

//=============================================================================
//=============================================================================
/**
 * An object for mainly for testing XML serialization.
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class rdSerializableObject2 : public rdObject
{

//=============================================================================
// MEMBER DATA
//=============================================================================

//=============================================================================
// METHODS
//=============================================================================
public:
	rdSerializableObject2();
	rdSerializableObject2(const std::string &aFileName);
	rdSerializableObject2(DOMElement *aElement);
	rdSerializableObject2(const rdSerializableObject2 &aNode);
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;
private:
	void setNull();
	void setupSerializedMembers();

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
	rdSerializableObject2& operator=(const rdSerializableObject2 &aObject);


//=============================================================================
};	// END of class rdSerializableObject2
//=============================================================================
//=============================================================================

#endif // __rdSerializableObject2_h__
