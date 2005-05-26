// rdPropertyObj.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdPropertyObj_h__
#define __rdPropertyObj_h__


// INCLUDES
#include "rdTools.h"
#include <string>
#include "rdObject.h"
#include "rdProperty.h"


//=============================================================================
//=============================================================================
/**
 * Class rdPropertyObj extends class rdProperty.  It consists of a pointer to
 * an object and the methods for accessing and modifying this object.
 *
 * @version 1.0
 * @author Frank C. Anderson
 */
class RDTOOLS_API rdPropertyObj : public rdProperty
{

//=============================================================================
// DATA
//=============================================================================
private:
	/** Value. */
	rdObject *_value;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdPropertyObj();
	rdPropertyObj(const std::string &aName,const rdObject &aValue);
	rdPropertyObj(const rdPropertyObj &aProperty);
	virtual rdProperty* copy() const;
	virtual ~rdPropertyObj();

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
	rdPropertyObj& operator=(const rdPropertyObj &aProperty);

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
public:
	// TYPE
	virtual const char* getTypeAsString() const;
	// VALUE
	virtual void setValue(const rdObject &aValue);
	virtual rdObject& getValueObj();
	virtual const rdObject& getValueObj() const;
	// VALUE as String
	virtual const std::string &toString();

//=============================================================================
};	// END of class rdPropertyObj
//=============================================================================
//=============================================================================

#endif //__rdPropertyObj_h__
