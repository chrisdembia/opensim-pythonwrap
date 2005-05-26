// rdActuatorSet.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2002, 2003, 2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdActuatorSet_h__
#define __rdActuatorSet_h__


// INCLUDES
#include <NMBLTK/Simulation/rdSimulationDLL.h>
#include <NMBLTK/Tools/rdObject.h>
#include <NMBLTK/Tools/rdSet.h>
#include "rdModel.h"
#include "rdActuator.h"


#ifndef SWIG
template class RDSIMULATION_API rdSet<rdActuator>;
//template class RDTOOLS_API rdArray<int>;
#endif


//=============================================================================
//=============================================================================
/**
 * A class for holding and managing a set of actuators for a model.
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class RDSIMULATION_API rdActuatorSet : public rdSet<rdActuator>
{

//=============================================================================
// DATA
//=============================================================================
protected:
	/** Model that is actuated. */
	rdModel *_model;

	/** Control to actuator map. */
	rdArray<int> _controlToActuator;
	/** Controls index. */
	rdArray<int> _actuatorToControl;

	/** State to actuator map. */
	rdArray<int> _stateToActuator;
	/** Actuator to state. */
	rdArray<int> _actuatorToState;

	/** Pseudo-state to actuator map. */
	rdArray<int> _pseudoToActuator;
	/** Actuator to pseudo-state map. */
	rdArray<int> _actuatorToPseudo;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdActuatorSet();
	rdActuatorSet(const char *aFileName);
	virtual ~rdActuatorSet();
private:
	void setNull();
	void setupSerializedMembers();
	
	void constructControlMaps();
	void constructStateMaps();
	void constructPseudoStateMaps();

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
#ifndef SWIG
	rdActuatorSet& operator=(const rdActuatorSet &aSet);
#endif
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
public:
	// MODEL
	void setModel(rdModel *aModel);
	rdModel* getModel() const;

	// ACTUATOR
	bool remove(int aIndex);
	bool append(rdActuator *aActuator);
	bool set(int aIndex,rdActuator *aActuator);

	// CONTROLS
	int getNX() const;
	int mapActuatorToControl(int aActuatorIndex) const;
	int mapControlToActuator(int aControlIndex) const;

	int getControlIndex(const std::string &aName) const;
	std::string getControlName(int aIndex) const;

	void setControl(int aIndex,double aValue);
	void setControl(const std::string &aName,double aValue);
	void setControls(const double aX[]);

	double getControl(int aIndex) const;
	double getControl(const std::string &aName) const;
	void getControls(double rX[]) const;

	// STATES
	int getNY() const;
	int mapActuatorToState(int aActuatorIndex) const;
	int mapStateToActuator(int aStateIndex) const;

	int getStateIndex(const std::string &aName) const;
	std::string getStateName(int aIndex) const;

	void setState(int aIndex,double aValue);
	void setState(const std::string &aName,double aValue);
	void setStates(const double aY[]);

	double getState(int aIndex) const;
	double getState(const std::string &aName) const;
	void getStates(double rY[]) const;

	// PSEUDOSTATES
	int getNYP() const;
	int mapActuatorToPseudoState(int aActuatorIndex) const;
	int mapPseudoStateToActuator(int aPseudoStateIndex) const;

	int getPseudoStateIndex(const std::string &aName) const;
	std::string getPseudoStateName(int aIndex) const;

	void setPseudoState(int aIndex,double aValue);
	void setPseudoState(const std::string &aName,double aValue);
	void setPseudoStates(const double aY[]);

	double getPseudoState(int aIndex) const;
	double getPseudoState(const std::string &aName) const;
	void getPseudoStates(double rY[]) const;

	//--------------------------------------------------------------------------
	// COMPUTATIONS
	//--------------------------------------------------------------------------
	void promoteControlsToStates(const double aX[],double aDT);
	void computeActuation();
	void computeStateDerivatives(double rDY[]);
	void updatePseudoStates();

	//--------------------------------------------------------------------------
	// APPLICATION
	//--------------------------------------------------------------------------
	void apply();

	//--------------------------------------------------------------------------
	// CHECK
	//--------------------------------------------------------------------------
	bool check() const;

//=============================================================================
};	// END of class rdActuatorSet
//=============================================================================
//=============================================================================


#endif // __rdActuatorSet_h__


