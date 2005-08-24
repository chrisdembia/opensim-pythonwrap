// suScale.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2004 Stanford University
// All rights reserved.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suScale_h__
#define __suScale_h__


#include "rdTools.h"
#include "rdObject.h"
#include "rdPropertyStr.h"
#include "rdPropertyDblArray.h"
#include "rdPropertyDbl.h"

//=============================================================================
/*
 * A Class representing scale factors for an object
 *
 * @author Ayman Habib
 * @version 1.0
 */
class RDTOOLS_API suScale : public rdObject
{
//=============================================================================
// DATA
//=============================================================================
protected:
	// PROPERTIES
	/** A list of 3 scale factors */
	rdPropertyDblArray	_propScaleFactors;
	/** Name of object to scale */
	rdPropertyStr		_propSegmentName;

	// REFERENCES
	rdArray<double>&	_scaleFactors;	
	std::string&		_segmentName;	

//=============================================================================
// METHODS
//=============================================================================
public:
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
	suScale();
	suScale(const suScale &aMarker);
	suScale(DOMElement *aElement);
	virtual ~suScale(void);
	virtual rdObject* copy(DOMElement *aElement) const;
	virtual rdObject* copy() const;

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
#ifndef SWIG
	suScale& operator=(const suScale &aMarker);
#endif	
private:
	void setNull();
	void setupProperties();

public:
	//--------------------------------------------------------------------------
	// SET AND GET
	//--------------------------------------------------------------------------
	void getScaleFactors(rdArray<double>& aScaleFactors) const;
	const std::string& getSegmentName() const;
	void setSegmentName(std::string& aSegmentName);
	void setScaleFactors(rdArray<double>& aScaleFactors);

};
#endif
