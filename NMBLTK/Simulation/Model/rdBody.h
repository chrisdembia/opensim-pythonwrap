// rdBody.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2000 Realistic Dynamics, Inc.
// All rights reserved.
//
// CONFIDENTIAL
//
// The material contain within this file is the sole property of
// Realistic Dynamics, Inc., and may not be read, copied, or distributed
// without the expressed writen consent of Realistic Dynamics, Inc.
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//============================================================================
#ifndef __rdBody_h__
#define __rdBody_h__

#include <NMBLTK/Tools/rdObject.h>
#include <NMBLTK/Simulation/rdSimulationDLL.h>
#include <NMBLTK/Tools/rdVisibleObject.h>
#include <NMBLTK/Tools/rdPropertyDbl.h>
#include <NMBLTK/Tools/rdPropertyDblArray.h>

#ifdef SWIG
	#ifdef RDSIMULATION_API
		#undef RDSIMULATION_API
		#define RDSIMULATION_API
	#endif
#endif

//=============================================================================
//=============================================================================
/**
 * A class which represents the physical parameters of a massive body.
 */
class RDSIMULATION_API rdBody  : public rdVisibleObject
{

//=============================================================================
// DATA
//=============================================================================
private:
	// PROPERTIES
	/** Mass properties */
	rdPropertyDbl			_propM;
	/** Moments of inertia */
	rdPropertyDblArray		_propI;
	/** Center of Mass of body relative to geometry's coordinate system */
	rdPropertyDblArray		_propCenterOfMass;

	// REFERENCES
	double&					_M;
	rdArray<double>&		_I;
	rdArray<double>&		_centerOfMass;
//=============================================================================
// METHODS
//=============================================================================
public:
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
	rdBody(double aM=1.0,double *aI=NULL);
	rdBody(const rdBody &aBody);
	rdBody(const std::string &aFileName);
	rdBody(DOMElement *aElement);
	virtual ~rdBody();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;
	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
#ifndef SWIG
	rdBody& operator=(const rdBody &aBody);
#endif
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	void setMass(double aM);
	double getMass();
	void setInertia(double *aI);
	void setInertia(double I1,double I2,double I3);
	void setInertia(double I1,double I2,double I3,
						double I12,double I23,double I31);
	void getInertia(double aI[6]);
	void getInertia(double aI[3][3]);
	void setCenterOfMass(const double aCenterOfMass[3]);
	void getCenterOfMass(double aCenterOfMass[3]) const;

	//--------------------------------------------------------------------------
	// SCALING
	//--------------------------------------------------------------------------
	void scaleBy(const double aScaleFactors[3]);
	//--------------------------------------------------------------------------
	// XML Support
	//--------------------------------------------------------------------------
	void setNull();
	void setupProperties();

};

#endif //__rdBody_h__
