// rdLinearSetPoint.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2002-2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdLinearSetPoint_h__
#define __rdLinearSetPoint_h__

#include "rdActuators.h"
#include <RD/Tools/rdPropertyDbl.h>
#include <RD/Simulation/Model/rdModel.h>
#include "rdSetPoint.h"


//=============================================================================
//=============================================================================
/**
 * Contact modeled with a linear spring in the vertical direction and
 * a moving set point to model friction.
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class RDACTUATORS_API rdLinearSetPoint : public rdSetPoint
{
//=============================================================================
// MEMBERS
//=============================================================================
	// PROPERTIES
	/** Constant stiffness in the normal direction. */
	rdPropertyDbl _propKNP;
	/** Constant viscosity in the normal direction. */\
	rdPropertyDbl _propKNV;

	// REFERENCES
	double &_knp;
	double &_knv;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdLinearSetPoint(int aBodyA=0,int aBodyB=0);
	rdLinearSetPoint(DOMElement *aElement);
	rdLinearSetPoint(const rdLinearSetPoint &aContact);
	virtual ~rdLinearSetPoint();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;
private:
	void setNull();
	void setupProperties();
	

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
	rdLinearSetPoint& operator=(const rdLinearSetPoint &aActuator);

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	// NORMAL IMPEDANCE
	virtual double getInstantaneousNormalStiffness() const;
	virtual double getInstantaneousNormalViscosity() const;
	// NORMAL STIFFNESS
	void setNormalStiffness(double aKNP);
	double getNormalStiffness() const;
	// NORMAL VISCOSITY
	void setNormalViscosity(double aKNV);
	double getNormalViscosity() const;

	//--------------------------------------------------------------------------
	// COMPUTATIONS
	//--------------------------------------------------------------------------
	virtual void computeActuation();

	//--------------------------------------------------------------------------
	// APPLICATION
	//--------------------------------------------------------------------------


	//--------------------------------------------------------------------------
	// CHECK
	//--------------------------------------------------------------------------
	virtual bool check() const;

	//--------------------------------------------------------------------------
	// XML
	//--------------------------------------------------------------------------
	virtual void updateFromXMLNode();

//=============================================================================
};	// END of class rdLinearSetPoint
//=============================================================================
//=============================================================================

#endif // __rdLinearSetPoint_h__


