// rdPropertyInt.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdPropertyInt_h__
#define __rdPropertyInt_h__


// INCLUDES
#include "rdTools.h"
#include <string>
#include "rdProperty.h"


//=============================================================================
//=============================================================================
/**
 * Class rdPropertyInt extends class rdProperty.  It consists of an integer
 * value and the methods for accessing and modifying this value.
 *
 * @version 1.0
 * @author Frank C. Anderson
 */
class RDTOOLS_API rdPropertyInt : public rdProperty
{

//=============================================================================
// DATA
//=============================================================================
private:
	/** Value. */
	int _value;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdPropertyInt();
	rdPropertyInt(const std::string &aName,int aValue);
	rdPropertyInt(const rdPropertyInt &aProperty);
	virtual rdProperty* copy() const;
	virtual ~rdPropertyInt() { };

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
	rdPropertyInt& operator=(const rdPropertyInt &aProperty);

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
public:
	// TYPE
	virtual const char* getTypeAsString() const;
	// VALUE
	virtual void setValue(int aValue);
	virtual int& getValueInt();
	virtual const int& getValueInt() const;
	// VALUE as String
	virtual const std::string &toString();

//=============================================================================
};	// END of class rdPropertyInt
//=============================================================================
//=============================================================================

#endif //__rdPropertyInt_h__
