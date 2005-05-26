// rdPropertyBool.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdPropertyBool_h__
#define __rdPropertyBool_h__


// INCLUDES
#include "rdTools.h"
#include <string>
#include "rdProperty.h"


//=============================================================================
//=============================================================================
/**
 * Class rdPropertyBool extends class rdProperty.  It consists of a boolean
 * value and the methods for accessing and modifying this value.
 *
 * @version 1.0
 * @author Frank C. Anderson
 */
class RDTOOLS_API rdPropertyBool : public rdProperty
{

//=============================================================================
// DATA
//=============================================================================
private:
	/** Value. */
	bool _value;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdPropertyBool();
	rdPropertyBool(const std::string &aName,bool aValue);
	rdPropertyBool(const rdPropertyBool &aProperty);
	virtual rdProperty* copy() const;
	virtual ~rdPropertyBool() { };

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
	rdPropertyBool& operator=(const rdPropertyBool &aProperty);

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
public:
	// TYPE
	virtual const char* getTypeAsString() const;
	// VALUE
	virtual void setValue(bool aValue);
	virtual bool& getValueBool();
	virtual const bool& getValueBool() const;
	// VALUE as String
	virtual const std::string &toString();
//=============================================================================
};	// END of class rdPropertyBool
//=============================================================================
//=============================================================================

#endif //__rdPropertyBool_h__
