// rdManager.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2000, 2002, 2003 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdManager_h__
#define __rdManager_h__


// INCLUDES
#include <RD/Tools/rdObject.h>
#include <RD/Simulation/rdSimulationDLL.h>
#include <stdlib.h>
#include <stdio.h>
#include <RD/Tools/rdTools.h>
#include <RD/Simulation/Model/rdModel.h>
#include <RD/Simulation/Control/rdControlSet.h>
#include <RD/Simulation/Integrator/rdIntegRKF.h>


//=============================================================================
//=============================================================================
/**
 * A class that manages the execution of a simulation.
 */
class RDSIMULATION_API rdManager
{

//=============================================================================
// DATA
//=============================================================================
private:
	/** Simulation session name. */
	std::string _sessionName;
	/** Model for which the simulation is performed. */
	rdModel *_model;
	/** Number of states. */
	int _ny;
	/** Array of states. */
	double *_y;
	/** Number of pseudostates. */
	int _nyp;
	/** Array of pseudostates. */
	double *_yp;
	/** Control set for the simulation. */
	rdControlSet *_controlSet;
	/** Default control set for the simulation.  This control set is used
	in the event the user specified control set is invalid for some reason. */
	rdControlSet *_defaultControlSet;
	/** Integrator. */
	rdIntegRKF *_integ;
	/** Initial time of the simulation. */
	double _ti;
	/** Final time of the simulation. */
	double _tf;
	/** First dt in an integration. */
	double _firstDT;
	/** Name to be shown by the UI */
	static std::string _displayName;


//=============================================================================
// METHODS
//=============================================================================
public:
	virtual ~rdManager();
	rdManager(rdModel *model,rdControlSet *aControlSet=NULL);
	/** A Constructor that does not take a model or controlset */
	rdManager();	

private:
	void setNull();
	bool constructStates();
	bool constructIntegrator();
	bool constructStorage();

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
public:
	void setSessionName(const std::string &name);
	const std::string& getSessionName() const;
	const std::string& toString() const;
	void setModel(rdModel *model);
	rdModel* getModel() const;
	rdControlSet* setControlSet(rdControlSet *aControlSet);
	rdControlSet* getControlSet() const;
	rdIntegRKF* getIntegrator() const;
	void setInitialTime(double aTI);
	double getInitialTime() const;
	void setFinalTime(double aTF);
	double getFinalTime() const;
	void setFirstDT(double aDT);
	double getFirstDT() const;

	//--------------------------------------------------------------------------
	// EXECUTION
	//--------------------------------------------------------------------------
	bool initializeStates();
	bool initializeStates(double *aY,double *aYP=NULL);
	bool integrate();
	bool integrate(int startIndex);
	bool integrate(double startTime);

	//--------------------------------------------------------------------------
	// UTILITY
	//--------------------------------------------------------------------------
	rdControlSet* constructControlSet();

	//--------------------------------------------------------------------------
	// PRINT
	//--------------------------------------------------------------------------


//=============================================================================
};	// END of class rdManager
//=============================================================================
//=============================================================================

#endif  // __rdManager_h__

