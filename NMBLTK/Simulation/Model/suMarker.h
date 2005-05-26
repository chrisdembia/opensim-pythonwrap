// suMarker.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2004 Stanford University
// All rights reserved.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suMarker_h__
#define __suMarker_h__
// INCLUDES
#include <NMBLTK/Simulation/rdSimulationDLL.h>
#include <NMBLTK/Tools/rdObject.h>
#include <NMBLTK/Tools/rdPropertyStr.h>
#include <NMBLTK/Tools/rdPropertyDblArray.h>
#include <NMBLTK/Tools/rdPropertyDbl.h>
#include <NMBLTK/Tools/rdVisibleObject.h>

//=============================================================================
//=============================================================================
/*
 * A Class representing a marker that lives on a SIMM model
 *
 * @author Ayman Habib
 * @version 1.0
 */
#ifdef SWIG
	#ifdef RDSIMULATION_API
		#undef RDSIMULATION_API
		#define RDSIMULATION_API
	#endif
#endif

class RDSIMULATION_API suMarker : public rdVisibleObject
{
protected:
	// PROPERTIES
	/** Location of marker in respective segment/body */
	rdPropertyDblArray	_propMarkerLocation;
	/** Name of Segment/Body on which marker lives */
	rdPropertyStr		_propReferenceSegmentName;
	/** Weight of marker to be used by Inverse Kinematics */
	rdPropertyDbl		_propMarkerWeight;

	// REFERENCES
	rdArray<double>&	_markerLocation;
	std::string&		_referenceSegmentName;
	double&				_markerWeight;

private:
	// Reference body/segment for the marker. Saved as an index since SDFast (and current model API) is index based
	int	_refSegmentForMarker;
public:
//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
	suMarker();
	suMarker(const suMarker &aMarker);
	suMarker(DOMElement *aElement);
	virtual ~suMarker(void);
	virtual rdObject* copy(DOMElement *aElement) const;
	virtual rdObject* copy() const;

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
#ifndef SWIG
	suMarker& operator=(const suMarker &aMarker);
#endif	
private:
	void setNull();
	void setupProperties();

public:
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	const double getWeight() const;
	void setWeight(const double aWeight);
	const std::string& getReferenceSegmentName() const;
	const int getRefSegment() const;
	void setRefSegment(const int aBodyIndex);
	void getLocation(rdArray<double>& aLocation) const;
	void setLocation(rdArray<double>& aLocation);
	// Scaling support 
	void scaleBy(rdArray<double>& aScales);
	virtual void update(const rdObject& aObject, rdEvent& aEvent);

};
#endif
