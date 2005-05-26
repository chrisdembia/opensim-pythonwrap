// rdActuatedModel_SDFast.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2002 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdActuatedModel_SDFast_h__
#define __rdActuatedModel_SDFast_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include <NMBLTK/Tools/rdTools.h>
#include "rdSDFastDLL.h"
#include <NMBLTK/Simulation/Model/rdModel.h>
#include <NMBLTK/Simulation/Model/rdActuatorSet.h>
#include <NMBLTK/Simulation/Model/rdContactForceSet.h>
#include "rdSDFast.h"


//=============================================================================
//=============================================================================
/**
 * A class that supports actuation and contact functionality to rdSDFast
 * models.
 */
class RDSDFAST_API rdActuatedModel_SDFast : public rdSDFast
{
//=============================================================================
// DATA
//=============================================================================
protected:

private:
	/** Array of initial states. */
	rdArray<double> _yi;
	/** Array of initial pseudo-states. */
	rdArray<double> _ypi;

protected:
	rdActuatorSet _actuatorSet;
	rdContactForceSet _contactSet;
	
//=============================================================================
// METHODS
//=============================================================================
public:
	rdActuatedModel_SDFast(const rdActuatorSet *aActuators,
		const rdContactForceSet *aContacts);
	rdActuatedModel_SDFast(const std::string &aFileName,
							rdActuatorSet *aActuators,
							rdContactForceSet *aContacts);
	virtual ~rdActuatedModel_SDFast();
private:
	void setNull();
	virtual void init();
protected:
	/* Register types to be used when reading an rdActuatedModel_SDFast object from xml file. */
	static void RegisterTypes();

public:
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	// NUMBERS OF THINGS
	virtual int getNX() const;
	virtual int getNA() const;
	virtual int getNP() const;
	virtual int getNY() const;
	virtual int getNYP() const;

	// NAMES
	virtual std::string getActuatorName(int aIndex) const;
	virtual std::string getControlName(int aIndex) const;
	virtual std::string getStateName(int aIndex) const;
	virtual std::string getPseudoStateName(int aIndex) const;

	// INDICES
	virtual int getActuatorIndex(const std::string &aName) const;
	virtual int getControlIndex(const std::string &aName) const;
	virtual int getStateIndex(const std::string &aName) const;
	virtual int getPseudoStateIndex(const std::string &aName) const;

	// ACTUATOR AND CONTACT SETS
	rdActuatorSet* getActuatorSet();
	rdContactForceSet* getContactForceSet();

	// CONTROLS
	virtual void setControl(int aIndex,double aValue);
	virtual void setControl(const std::string &aName,double aValue);
	virtual void setControls(const double aX[]);
	virtual double getControl(const std::string &aName) const;
	virtual double getControl(int aIndex) const;
	virtual void getControls(double aX[]) const;

	// STATES
	virtual void setStates(const double aY[]);
	virtual void getStates(double rY[]) const;
	virtual double getState(int aIndex) const;
	virtual double getState(const std::string &aName) const;
	
	// PSEUDOSTATES
	virtual void setPseudoStates(const double aYP[]);
	virtual void getPseudoStates(double rYP[]) const;
	virtual double getPseudoState(int aIndex) const;
	virtual double getPseudoState(const std::string &aName) const;

	// INITIAL PSEUDO STATES
	virtual void setInitialPseudoStates(const double aYPI[]);
	virtual double getInitialPseudoState(int aIndex) const;
	virtual double getInitialPseudoState(const std::string &aName) const;
	virtual void getInitialPseudoStates(double rYPI[]) const;

	// INITIAL STATES
	virtual void setInitialStates(const double aYI[]);
	virtual double getInitialState(int aIndex) const;
	virtual double getInitialState(const std::string &aName) const;
	virtual void getInitialStates(double rYI[]) const;

	//--------------------------------------------------------------------------
	// ACTUATION
	//--------------------------------------------------------------------------
	virtual void computeActuation();
	virtual void computeActuatorStateDerivatives(double rDY[]);
	virtual void applyActuatorForce(int aID);
	virtual void applyActuatorForces();
	virtual void setActuatorForce(int aID,double aForce);
	virtual double getActuatorForce(int aID) const;
	virtual double getActuatorStress(int aID) const;
	virtual double getActuatorSpeed(int aID) const;
	virtual double getActuatorPower(int aID) const;
	//--------------------------------------------------------------------------
	// CONTACT
	//--------------------------------------------------------------------------
	virtual void
		computeContact();
	virtual void
		applyContactForce(int aID);
	virtual void
		applyContactForces();
	virtual int
		getContactBodyA(int aID) const;
	virtual int
		getContactBodyB(int aID) const;
	virtual void
		setContactPointA(int aID,const double aPoint[3]);
	virtual void
		getContactPointA(int aID,double rPoint[3]) const;
	virtual void
		setContactPointB(int aID,const double aPoint[3]);
	virtual void
		getContactPointB(int aID,double rPoint[3]) const;
	virtual void
		getContactForce(int aID,double rF[3])const;
	virtual void
		getContactNormalForce(int aID,double rFP[3],double rFV[3],double rF[3])
		const;
	virtual void
		getContactTangentForce(int aID,double rFP[3],double rFV[3],double rF[3])
		const;
	virtual void
		getContactStiffness(int aID,const double aDX[3],double rDF[3]) const;
	virtual void
		getContactViscosity(int aID,const double aDV[3],double rDF[3]) const;
	virtual void
		getContactFrictionCorrection(int aID,double rDFFric[3]) const;
	virtual double
		getContactForce(int aID) const;
	virtual double
		getContactSpeed(int aID) const;
	virtual double
		getContactPower(int aID) const;

	//--------------------------------------------------------------------------
	// OPTIMIZATION
	//--------------------------------------------------------------------------
	virtual void promoteControlsToStates(const double aX[],double aDT);

	//--------------------------------------------------------------------------
	// DERIVATIVES
	//--------------------------------------------------------------------------
	int deriv(double t,double *xt,double *y,double *dy);
	int deriv(double t,double *xt,double *y,double *dqdt,double *dudt);

	//--------------------------------------------------------------------------
	// CALLBACKS
	//--------------------------------------------------------------------------
	/* function has no implementation and is not virtual! void
		integStepCallback(double *xtPrev,double *yPrev,int i,double dt,
		 double t,double *x,double *y,void *cd);*/


//=============================================================================
};	// END of class rdActuatedModel_SDFast
//=============================================================================
//=============================================================================


#endif // #ifndef __rdActuatedModel_SDFast_h__
