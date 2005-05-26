// rdPropertyStr.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdPropertyStr_h__
#define __rdPropertyStr_h__


// INCLUDES
#include "rdTools.h"
#include <string>
#include "rdProperty.h"


//=============================================================================
//=============================================================================
/**
 * Class rdPropertyInt extends class rdProperty.  It consists of a string
 * value and the methods for accessing and modifying this value.
 *
 * @version 1.0
 * @author Frank C. Anderson
 */
class RDTOOLS_API rdPropertyStr : public rdProperty
{

//=============================================================================
// DATA
//=============================================================================
private:
	/** Value. */
	std::string _value;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdPropertyStr();
	rdPropertyStr(const std::string &aName,
		const std::string &aValue);
	rdPropertyStr(const rdPropertyStr &aProperty);
	virtual rdProperty* copy() const;
	virtual ~rdPropertyStr() { };

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
	rdPropertyStr& operator=(const rdPropertyStr &aProperty);

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
public:
	// TYPE
	virtual const char* getTypeAsString() const;
	// VALUE
	virtual void setValue(const std::string &aValue);
	virtual std::string& getValueStr();
	virtual const std::string& getValueStr() const;
	// VALUE as String
	virtual const std::string &toString();

//=============================================================================
};	// END of class rdPropertyStr
//=============================================================================
//=============================================================================

#endif //__rdPropertyStr_h__
