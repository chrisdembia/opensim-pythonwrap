// rdSetPoint.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2002-2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdSetPoint_h__
#define __rdSetPoint_h__

#include "rdActuators.h"
#include <NMBLTK/Tools/rdPropertyDbl.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include <NMBLTK/Simulation/Model/rdContactForce.h>


//=============================================================================
//=============================================================================
/**
 * A class that supports a contact force with a moving set point or spring
 * zero.  The set point moves on the body whose direction and surface
 * normal are active (BodyA).
 *
 * A set point has three pseudostates: the coordinates of contact PointA. 
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class RDACTUATORS_API rdSetPoint : public rdContactForce
{
//=============================================================================
// DATA
//=============================================================================
private:
	static const std::string YP0_NAME;
	static const std::string YP1_NAME;
	static const std::string YP2_NAME;
protected:
	// PROPERTIES
	/** Constant stiffness in the tangential direction. */
	rdPropertyDbl _propKTP;
	/** Constant viscosity in the tangential direction. */
	rdPropertyDbl _propKTV;
	/** Coefficient of friction. */
	rdPropertyDbl _propMU;

	// REFERENCES
	double &_ktp;
	double &_ktv;
	double &_mu;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdSetPoint(int aBodyA=0,int aBodyB=0,int aNYP=3);
	rdSetPoint(DOMElement *aElement,int aNYP=3);
	rdSetPoint(const rdSetPoint &aContact);
	virtual ~rdSetPoint();
private:
	void setNull();
	void setupProperties();
	

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
	rdSetPoint& operator=(const rdSetPoint &aSetPoint);

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	// PSEUDOSTATES
	virtual int getNYP() const;
	virtual const std::string& getPseudoStateName(int aIndex) const;
	virtual int getPseudoStateIndex(const std::string &aName) const;
	virtual void setPseudoStates(const double aX[]);
	virtual void setPseudoState(int aIndex,double aValue);
	virtual void setPseudoState(const std::string &aName,double aValue);
	virtual void getPseudoStates(double rX[]) const;
	virtual double getPseudoState(int aIndex) const;
	virtual double getPseudoState(const std::string &aName) const;
	// TANGENTIAL IMPEDANCE
	virtual double getInstantaneousTangentialStiffness() const;
	virtual double getInstantaneousTangentialViscosity() const;
	// TANGENTIAL STIFFNESS
	void setTangentialStiffness(double aKTP);
	double getTangentialStiffness() const;
	// TANGENTIAL VISCOSITY
	void setTangentialViscosity(double aKTV);
	double getTangentialViscosity() const;
	// COEFFICIENT OF FRICTION
	void setFriction(double aMU);
	double getFriction() const;

	//--------------------------------------------------------------------------
	// COMPUTATIONS
	//--------------------------------------------------------------------------
	virtual void updatePseudoStates();

	//--------------------------------------------------------------------------
	// APPLICATION
	//--------------------------------------------------------------------------


	//--------------------------------------------------------------------------
	// CHECK
	//--------------------------------------------------------------------------
	virtual bool check() const;

	//--------------------------------------------------------------------------
	// UTILITY
	//--------------------------------------------------------------------------
	double
		computeTangentialForce(double aNormalForce,double rTangentForce[3],
		double rDFFric[3]);
	bool
		computeNewSetPoint(double aTangentForce,double rSetPoint[3]) const;

	//--------------------------------------------------------------------------
	// XML
	//--------------------------------------------------------------------------
	virtual void updateFromXMLNode();

//=============================================================================
};	// END of class rdSetPoint
//=============================================================================
//=============================================================================

#endif // __rdSetPoint_h__


