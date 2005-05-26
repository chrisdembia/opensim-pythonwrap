// rdPolynomialSetPoint.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2002-2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdPolynomialSetPoint_h__
#define __rdPolynomialSetPoint_h__

#include "rdActuators.h"
#include <NMBLTK/Tools/rdPropertyDbl.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include "rdSetPoint.h"


//=============================================================================
//=============================================================================
/**
 * Contact modeled with a polynomal spring in the normal direction and
 * a moving set point in the tangential plane.
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class RDACTUATORS_API rdPolynomialSetPoint : public rdSetPoint
{

//=============================================================================
// DATA
//=============================================================================
protected:
	// PROPERTIES
	/** Normal stiffness constant.  This constant is not to be confused with
	the instantaneous stiffness. */
	rdPropertyDbl _propKNP;
	/** Normal viscosity constant.  This constant is not to be confused with
	the instantaneous viscosity. */
	rdPropertyDbl _propKNV;
	/** Stiffness power- power to which normal spring displacement is raised.
	The power is 1.0 by default. */
	rdPropertyDbl _propPowerNP;
	/** Viscosity power- power to which normal spring velocity is raised.
	The power is 1.0 by default. */
	rdPropertyDbl _propPowerNV;

	// REFERENCES
	double &_kNP;
	double &_kNV;
	double &_powNP;
	double &_powNV;


	/** Instantaneous stiffness in the normal direction. */
	double _knp;
	/** Instantaneous viscosity in the normal direction. */
	double _knv;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdPolynomialSetPoint(int aBodyA=0,int aBodyB=0);
	rdPolynomialSetPoint(DOMElement *aElement);
	rdPolynomialSetPoint(const rdPolynomialSetPoint &aContact);
	virtual ~rdPolynomialSetPoint();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;
private:
	void setNull();
	void setupProperties();
	

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
	rdPolynomialSetPoint& operator=(const rdPolynomialSetPoint &aActuator);

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	// NORMAL IMPEDANCE
	virtual double getInstantaneousNormalStiffness() const;
	virtual double getInstantaneousNormalViscosity() const;
	// NORMAL STIFFNESS
	void setNormalStiffnessConstant(double aKNP);
	double getNormalStiffnessConstant() const;
	// NORMAL VISCOSITY
	void setNormalViscosityConstant(double aKNV);
	double getNormalViscosityConstant() const;
	// STIFFNESS POWER
	void setStiffnessPower(double aPower);
	double getStiffnessPower() const;
	// VISCOSITY POWER
	void setViscosityPower(double aPower);
	double getViscosityPower() const;

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
};	// END of class rdPolynomialSetPoint
//=============================================================================
//=============================================================================

#endif // __rdPolynomialSetPoint_h__


