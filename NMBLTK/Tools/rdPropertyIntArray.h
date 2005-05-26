// rdPropertyIntArray.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdPropertyIntArray_h__
#define __rdPropertyIntArray_h__


// INCLUDES
#include "rdTools.h"
#include <string>
#include "rdProperty.h"


//=============================================================================
//=============================================================================
/**
 * Class rdPropertyIntArray extends class rdProperty.  It consists of an
 * array of integers (i.e., rdArray<int>) and the methods for accessing
 * and modifying this array.
 *
 * @version 1.0
 * @author Frank C. Anderson
 */
class RDTOOLS_API rdPropertyIntArray : public rdProperty
{

//=============================================================================
// DATA
//=============================================================================
private:
	/** Array of integers. */
	rdArray<int> _array;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdPropertyIntArray();
	rdPropertyIntArray(const std::string &aName,
		const rdArray<int> &aArray);
	rdPropertyIntArray(const std::string &aName,
		int aSize,const int aArray[]);
	rdPropertyIntArray(const rdPropertyIntArray &aProperty);
	virtual rdProperty* copy() const;
	virtual ~rdPropertyIntArray() { };

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
	rdPropertyIntArray& operator=(const rdPropertyIntArray &aProperty);

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
public:
	// TYPE
	virtual const char* getTypeAsString() const;
	// VALUE
	virtual void setValue(const rdArray<int> &aArray);
	virtual void setValue(int aSize,const int aArray[]);
	virtual rdArray<int>& getValueIntArray();
	virtual const rdArray<int>& getValueIntArray() const;
	// VALUE as String
	virtual const std::string &toString();

//=============================================================================
};	// END of class rdPropertyIntArray
//=============================================================================
//=============================================================================

#endif //__rdPropertyIntArray_h__
