// rdPropertySet.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdPropertySet_h__
#define __rdPropertySet_h__


// INCLUDES
#include "rdTools.h"
#include "rdArrayPtrs.h"
#include "rdProperty.h"


#ifdef SWIG
	#ifdef RDTOOLS_API
		#undef RDTOOLS_API
		#define RDTOOLS_API
	#endif
#endif

#ifndef SWIG
#ifdef WIN32
template class RDTOOLS_API rdArrayPtrs<rdProperty>;
#endif
#endif

//=============================================================================
//=============================================================================
/**
 * A property set is simply a set of properties.  It provides methods for
 * adding, removing, and retrieving properties from itself.
 *
 * @version 1.0
 * @author Frank C. Anderson
 * @see rdProperty
 */
class RDTOOLS_API rdPropertySet  
{

//=============================================================================
// DATA
//=============================================================================
public:
	/** Set of properties. */
	rdArrayPtrs<rdProperty> _array;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdPropertySet();
	rdPropertySet(const rdPropertySet &aSet);
	virtual ~rdPropertySet() { _array.setSize(0); };

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
#ifndef SWIG
	friend std::ostream& operator<<(std::ostream &aOut,
															const rdPropertySet &aSet) {
		aOut << "\nProperty Set:\n";
		for(int i=0;i<aSet.getSize();i++) aOut << *aSet.get(i) << "\n";
		return(aOut);
	}
#endif
	//--------------------------------------------------------------------------
	// ACCESS
	//--------------------------------------------------------------------------
public:
	// Empty?
	bool isEmpty() const;
	// Number of properties
	int getSize() const;
	// Get
	virtual rdProperty* get(int i);
#ifndef SWIG
	virtual const rdProperty* get(int i) const;
#endif
	virtual rdProperty* get(const std::string &aName);
#ifndef SWIG
	virtual const rdProperty* get(const std::string &aName) const;
#endif
	// Append
	virtual void append(rdProperty *aProperty);
	// Remove
	virtual void remove(const std::string &aName);
	// Clear
	virtual void clear();

//=============================================================================
};	// END of class rdPropertySet
//=============================================================================
//=============================================================================

#endif //__rdPropertySet_h__
