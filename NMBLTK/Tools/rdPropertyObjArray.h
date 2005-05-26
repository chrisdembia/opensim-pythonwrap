// rdPropertyObjArray.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdPropertyObjArray_h__
#define __rdPropertyObjArray_h__


// INCLUDES
#include "rdTools.h"
#include <string>
#include "rdArrayPtrs.h"
#include "rdProperty.h"


#ifndef UNIX
template class RDTOOLS_API rdArrayPtrs<rdObject>;
#endif


//=============================================================================
//=============================================================================
/**
 * Class rdPropertyObjArray extends class rdProperty.  It consists of an
 * array of rdObjects (i.e., rdArrayPtrs<rdObject>) and the methods for
 * accessing and modifying this array.
 *
 * @version 1.0
 * @author Frank C. Anderson
 */
class RDTOOLS_API rdPropertyObjArray : public rdProperty
{

//=============================================================================
// DATA
//=============================================================================
private:
	/** Array of objects. */
	rdArrayPtrs<rdObject> _array;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdPropertyObjArray();
	rdPropertyObjArray(const std::string &aName);
	rdPropertyObjArray(const std::string &aName,const rdArrayPtrs<rdObject> &aArray);
	rdPropertyObjArray(const std::string &aName,int aSize,const rdObject **aArray);
	rdPropertyObjArray(const rdPropertyObjArray &aProperty);
	virtual rdProperty* copy() const;
	virtual ~rdPropertyObjArray() { _array.setSize(0); };

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
	rdPropertyObjArray& operator=(const rdPropertyObjArray &aProperty);

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
public:
	// TYPE
	virtual const char* getTypeAsString() const;
	// VALUE
	virtual void setValue(int aSize,rdObject **aArray);
	virtual void setValue(const rdArrayPtrs<rdObject> &aArray);
	virtual rdArrayPtrs<rdObject>& getValueObjArray();
	virtual const rdArrayPtrs<rdObject>& getValueObjArray() const;
	// VALUE as String
	virtual const std::string &toString();

//=============================================================================
};	// END of class rdPropertyObjArray
//=============================================================================
//=============================================================================

#endif //__rdPropertyObjArray_h__
