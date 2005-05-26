// rdPropertyDblArray.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdPropertyDblArray_h__
#define __rdPropertyDblArray_h__


// INCLUDES
#include "rdTools.h"
#include <string>
#include "rdProperty.h"


//=============================================================================
//=============================================================================
/**
 * Class rdPropertyDblArray extends class rdProperty.  It consists of an
 * array of doubles (i.e., rdArray<double>) and the methods for accessing
 * and modifying this array.
 *
 * @version 1.0
 * @author Frank C. Anderson
 */
class RDTOOLS_API rdPropertyDblArray : public rdProperty
{

//=============================================================================
// DATA
//=============================================================================
private:
	/** Array of integers. */
	rdArray<double> _array;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdPropertyDblArray();
	rdPropertyDblArray(const std::string &aName,
		const rdArray<double> &aArray);
	rdPropertyDblArray(const std::string &aName,
		int aSize,const double aArray[]);
	rdPropertyDblArray(const rdPropertyDblArray &aProperty);
	virtual rdProperty* copy() const;
	virtual ~rdPropertyDblArray() { };

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
	rdPropertyDblArray& operator=(const rdPropertyDblArray &aProperty);

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
public:
	// TYPE
	virtual const char* getTypeAsString() const;
	// VALUE
	virtual void setValue(const rdArray<double> &aArray);
	virtual void setValue(int aSize,const double aArray[]);
	virtual rdArray<double>& getValueDblArray();
	virtual const rdArray<double>& getValueDblArray() const;
	// VALUE as String
	virtual const std::string &toString();
	// VALUE primitive
	virtual double& getDblValueAt(int aIndex) const;
	virtual void setDblValueAt(int aIndex, const double aDouble) const;
	virtual const int getArraySize() const;


//=============================================================================
};	// END of class rdPropertyDblArray
//=============================================================================
//=============================================================================

#endif //__rdPropertyDblArray_h__
