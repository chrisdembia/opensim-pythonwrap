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
#include <NMBLTK/Tools/rdObject.h>
#include <NMBLTK/Simulation/rdSimulationDLL.h>
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include <NMBLTK/Simulation/Model/rdModelIntegrand.h>
#include <NMBLTK/Simulation/Integrator/rdIntegRKF.h>


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
	/** Array of integrated states. */
	rdArray<double> _y;
	/** Number of model pseudostates. */
	int _nyp;
	/** Array of model pseudostates. */
	rdArray<double> _yp;
	/** Integrand for the model. */
	rdModelIntegrand *_integrand;
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
	rdManager(rdModelIntegrand *aIntegrand);
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
	// Integrand
	void setIntegrand(rdModelIntegrand *aIntegrand);
	rdModelIntegrand* getIntegrand() const;
	// Integrator
	rdIntegRKF* getIntegrator() const;
	// Initial and final times
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


//=============================================================================
};	// END of class rdManager
//=============================================================================
//=============================================================================

#endif  // __rdManager_h__

