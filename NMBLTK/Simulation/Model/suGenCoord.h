// suGenCoord.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2004 Stanford University
// All rights reserved.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suGenCoord_h__
#define __suGenCoord_h__
// INCLUDES
#include <NMBLTK/Simulation/rdSimulationDLL.h>
#include <NMBLTK/Tools/rdObject.h>
#include <NMBLTK/Tools/rdPropertyObj.h>
#include <NMBLTK/Tools/rdPropertyBool.h>

class suRange;
//=============================================================================
//=============================================================================
/*
 * A Class representing a Generalized Coordinate (Degree of freedom). 
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

class RDSIMULATION_API suGenCoord : public rdObject
{
protected:
	// PROPERTIES
	/** GenCoord range object */
	rdPropertyObj		_propGencoordRange;
	/** Flag to indicate if in degrees rather than radians.
	 * Translational DOFs should have this flag set to false
	 * to avoid incorrect conversion to radians. */
	rdPropertyBool		_propInDegrees;

	// REFERENCES
	suRange&			_range;
	bool&				_inDegrees;

public:
//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
	suGenCoord();
	suGenCoord(const suGenCoord &aGencoord);
	suGenCoord(DOMElement *aElement);
	virtual ~suGenCoord(void);
	virtual rdObject* copy(DOMElement *aElement) const;
	virtual rdObject* copy() const;

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
	suGenCoord& operator=(const suGenCoord &aGencoord);
	
private:
	void setNull();
	void setupProperties();

public:
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	const suRange &getRange() const;
	suRange &getRange();
	void setRange(const suRange &aRange);

	const bool getInDegrees() const;
	bool getInDegrees();
	void setInDegrees(const bool &aInDegrees);

};
#endif
