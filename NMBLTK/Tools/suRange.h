// suRange.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2004 Stanford University
// All rights reserved.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suRange_h__
#define __suRange_h__
// INCLUDES
#include "rdTools.h"
#include "rdObject.h"
#include "rdPropertyDbl.h"

//=============================================================================
/*
 * A Class representing a range for a parameter or a generalized coordinate
 *
 * @author Ayman Habib
 * @version 1.0
 */
class RDTOOLS_API suRange : public rdObject
{
//=============================================================================
// DATA
//=============================================================================
protected:
	// PROPERTIES
	/** Min value */
	rdPropertyDbl		_propMin;
	/** Max value */
	rdPropertyDbl		_propMax;

	// REFERENCES
	double&				_min;
	double&				_max;

//=============================================================================
// METHODS
//=============================================================================
public:
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
	suRange();
	suRange(const suRange &aRange);
	suRange(DOMElement *aElement);
	virtual ~suRange(void);
	virtual rdObject* copy(DOMElement *aElement) const;
	virtual rdObject* copy() const;

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
#ifndef SWIG
	suRange& operator=(const suRange &aRange);
#endif	
private:
	void setNull();
	void setupProperties();

public:
	//--------------------------------------------------------------------------
	// SET AND GET
	//--------------------------------------------------------------------------
	const double getMin() const;
	void setMin(const double aMin);

	const double getMax() const;
	void setMax(const double aMax);


};
#endif
