// rdActuator.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2002, 2003 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdActuator_h__
#define __rdActuator_h__


#include "rdModel.h"
#include <NMBLTK/Tools/rdObject.h>
#include <NMBLTK/Tools/rdPropertyDbl.h>


//=============================================================================
//=============================================================================
/**
 * An abstract class for representing an actuator (e.g., a torque motor,
 * muscle, ...).
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
#ifdef SWIG
	#ifdef RDSIMULATION_API
		#undef RDSIMULATION_API
		#define RDSIMULATION_API
	#endif
#endif

class RDSIMULATION_API rdActuator : public rdObject
{

//=============================================================================
// DATA
//=============================================================================
public:
	static const double LARGE;

protected:
	// PROPERTIES
	/** Cross-sectional area of the actuator. */
	rdPropertyDbl _propArea;
	/** Minimum force (or torque) that this actuator can apply. */
	rdPropertyDbl _propMinForce;
	/** Maximum force (or torque) that this actuator can apply. */
	rdPropertyDbl _propMaxForce;
	/** Optimal force. */
	rdPropertyDbl _propOptimalForce;

	// REFERENCES
	double &_area;
	double &_minForce;
	double &_maxForce;
	double &_optimalForce;

	/** Model which the actuator actuates. */
	rdModel *_model;

	/** Flag indicating whether the actuator applies a force or a torque. */
	bool _appliesForce;
	/** Force (or torque) magnitude that is applied to the model. */
	double _force;
	/** Speed of actuator (linear or angular). */
	double _speed;

private:
	/** Excitation (control 0). */
	double _x;


//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdActuator(int aNX,int aNY,int aNYP);
	rdActuator(int aNX,int aNY,int aNYP,DOMElement *aElement);
	rdActuator(const rdActuator &aActuator);
	virtual ~rdActuator();
	virtual rdObject* copy() const = 0;
	virtual rdObject* copy(DOMElement *aElement) const = 0;
private:
	void setNull();
	void setupProperties();
	
	void constructControls();
	void constructStates();
	void constructPseudoStates();

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
#ifndef SWIG
	rdActuator& operator=(const rdActuator &aActuator);
#endif
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
protected:
	void setControlName(int aIndex,const char *aName);
	void setStateName(int aIndex,const char *aName);
	void setPseudoStateName(int aIndex,const char *aName);
public:
	// MODEL
	void setModel(rdModel *aModel);
	rdModel* getModel() const;
	// CONTROLS
	virtual int getNX() const;
	virtual const std::string getControlName(int aIndex) const;
	virtual int getControlIndex(const std::string &aName) const;
	virtual void setControl(int aIndex,double aValue);
	virtual void setControl(const std::string &aName,double aValue);
	virtual void setControls(const double aX[]);
	virtual double getControl(int aIndex) const;
	virtual double getControl(const std::string &aName) const;
	virtual void getControls(double rX[]) const;
	// STATES
	virtual int getNY() const;
	virtual const std::string& getStateName(int aIndex) const;
	virtual int getStateIndex(const std::string &aName) const;
	virtual void setState(int aIndex,double aValue);
	virtual void setState(const std::string &aName,double aValue);
	virtual void setStates(const double aY[]);
	virtual double getState(int aIndex) const;
	virtual double getState(const std::string &aName) const;
	virtual void getStates(double rY[]) const;
	// PSEUDOSTATES
	virtual int getNYP() const;
	virtual const std::string& getPseudoStateName(int aIndex) const;
	virtual int getPseudoStateIndex(const std::string &aName) const;
	virtual void setPseudoState(int aIndex,double aValue);
	virtual void setPseudoState(const std::string &aName,double aValue);
	virtual void setPseudoStates(const double aY[]);
	virtual double getPseudoState(int aIndex) const;
	virtual double getPseudoState(const std::string &aName) const;
	virtual void getPseudoStates(double rY[]) const;
	// AREA
	void setArea(double aArea);
	double getArea() const;
	// FORCE
protected:
	void setAppliesForce(bool aTrueFalse);
public:
	bool getAppliesForce() const;
	void setForce(double aForce);
	double getForce() const;
	double getStress() const;
	// SPEED
	double getSpeed() const;
	// POWER
	double getPower() const;
	// MAX FORCE
	void setMaxForce(double aMax);
	double getMaxForce() const;
	// MIN FORCE
	void setMinForce(double aMin);
	double getMinForce() const;
	// OPTIMAL FORCE
	void setOptimalForce(double aOptimalForce);
	double getOptimalForce() const;


	//--------------------------------------------------------------------------
	// COMPUTATIONS
	//--------------------------------------------------------------------------
	virtual void promoteControlsToStates(const double aX[],double aDT);
	virtual void computeActuation() = 0;
	virtual void computeStateDerivatives(double rDYDT[]);
	virtual void updatePseudoStates();

	//--------------------------------------------------------------------------
	// APPLICATION
	//--------------------------------------------------------------------------
	virtual void apply() = 0;

	//--------------------------------------------------------------------------
	// CHECK
	//--------------------------------------------------------------------------
	virtual bool check() const;

//=============================================================================
};	// END of class rdActuator
//=============================================================================
//=============================================================================

#endif // __rdActuator_h__


