// rdPropertyDbl.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdPropertyDbl_h__
#define __rdPropertyDbl_h__


// INCLUDES
#include "rdTools.h"
#include <string>
#include "rdProperty.h"


//=============================================================================
//=============================================================================
/**
 * Class rdPropertyDbl extends class rdProperty.  It consists of a double
 * value and the methods for accessing and modifying this value.
 *
 * @version 1.0
 * @author Frank C. Anderson
 */
class RDTOOLS_API rdPropertyDbl : public rdProperty
{

//=============================================================================
// DATA
//=============================================================================
private:
	/** Value. */
	double _value;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdPropertyDbl();
	rdPropertyDbl(const std::string &aName,double aValue);
	rdPropertyDbl(const rdPropertyDbl &aProperty);
	virtual rdProperty* copy() const;
	virtual ~rdPropertyDbl() { };

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
	rdPropertyDbl& operator=(const rdPropertyDbl &aProperty);

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
public:
	// TYPE
	virtual const char* getTypeAsString() const;
	// VALUE
	virtual void setValue(double aValue);
	virtual double& getValueDbl();
	virtual const double& getValueDbl() const;
	// VALUE as String
	virtual const std::string &toString();

//=============================================================================
};	// END of class rdPropertyDbl
//=============================================================================
//=============================================================================

#endif //__rdPropertyDbl_h__
