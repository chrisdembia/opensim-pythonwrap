// rdPropertyBoolArray.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdPropertyBoolArray_h__
#define __rdPropertyBoolArray_h__


// INCLUDES
#include "rdTools.h"
#include <string>
#include "rdProperty.h"


//=============================================================================
//=============================================================================
/**
 * Class rdPropertyBoolArray extends class rdProperty.  It consists of an
 * array of booleans (i.e., rdArray<bool>) and the methods for accessing
 * and modifying this array.
 *
 * @version 1.0
 * @author Frank C. Anderson
 */
class RDTOOLS_API rdPropertyBoolArray : public rdProperty
{

//=============================================================================
// DATA
//=============================================================================
private:
	/** Array of booleans. */
	rdArray<bool> _array;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdPropertyBoolArray();
	rdPropertyBoolArray(const std::string &aName,
		const rdArray<bool> &aArray);
	rdPropertyBoolArray(const std::string &aName,
		int aSize,const bool aArray[]);
	rdPropertyBoolArray(const rdPropertyBoolArray &aProperty);
	virtual rdProperty* copy() const;
	virtual ~rdPropertyBoolArray() { };

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
	rdPropertyBoolArray& operator=(const rdPropertyBoolArray &aProperty);

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
public:
	// TYPE
	virtual const char* getTypeAsString() const;
	// VALUE
	virtual void setValue(const rdArray<bool> &aArray);
	virtual void setValue(int aSize,const bool aArray[]);
	virtual rdArray<bool>& getValueBoolArray();
	virtual const rdArray<bool>& getValueBoolArray() const;
	// VALUE as String
	virtual const std::string &toString();

//=============================================================================
};	// END of class rdPropertyBoolArray
//=============================================================================
//=============================================================================

#endif //__rdPropertyBoolArray_h__
