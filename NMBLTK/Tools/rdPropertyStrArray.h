// rdPropertyStrArray.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdPropertyStrArray_h__
#define __rdPropertyStrArray_h__


// INCLUDES
#include "rdTools.h"
#include <string>
#include "rdProperty.h"


//=============================================================================
//=============================================================================
/**
 * Class rdPropertyStrArray extends class rdProperty.  It consists of an
 * array of strings (i.e., rdArray<string>) and the methods for accessing
 * and modifying this array.
 *
 * @version 1.0
 * @author Frank C. Anderson
 */
class RDTOOLS_API rdPropertyStrArray : public rdProperty
{

//=============================================================================
// DATA
//=============================================================================
private:
	/** Array of integers. */
	rdArray<std::string> _array;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdPropertyStrArray();
	rdPropertyStrArray(const std::string &aName,
		const rdArray<std::string> &aArray);
	rdPropertyStrArray(const std::string &aName,
		int aSize,const std::string aArray[]);
	rdPropertyStrArray(const rdPropertyStrArray &aProperty);
	virtual rdProperty* copy() const;
	virtual ~rdPropertyStrArray() { };

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
	rdPropertyStrArray& operator=(const rdPropertyStrArray &aProperty);

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
public:
	// TYPE
	virtual const char* getTypeAsString() const;
	// VALUE
	virtual void setValue(const rdArray<std::string> &aArray);
	virtual void setValue(int aSize,const std::string aArray[]);
	virtual rdArray<std::string>& getValueStrArray();
	virtual const rdArray<std::string>& getValueStrArray() const;
	// VALUE as String
	virtual const std::string &toString();

//=============================================================================
};	// END of class rdPropertyStrArray
//=============================================================================
//=============================================================================

#endif //__rdPropertyStrArray_h__
