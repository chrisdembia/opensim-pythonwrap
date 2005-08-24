// rdIntegRKF.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2000-2003 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdIntegRKF_h__
#define __rdIntegRKF_h__

// INCLUDES
#include "rdIntegrator.h"
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Tools/rdArray.h>
#include <NMBLTK/Tools/rdStorage.h>
#include <NMBLTK/Tools/rdMath.h>
#include "Integrand.h"
#include "rdRKF.h"


// DLL SPECIFICATIONS FOR TEMPLATES
//template class RDSIMULATION_API rdArray<double>;


//=============================================================================
//=============================================================================
/**
 * A class for integrating the equations of motion of a dynamic system.
 *
 * This class performs the relatively high-level tasks during an integration
 * and implements the logic for when to reduce the integration step size or
 * increase it.  This class sits on top of class rdRKF which implements
 * the low-level numerics for computing the derivatives and taking the states
 * one step forward in time.  RKF means Runge-Kutta-Feldberg.  See rdRKF
 * for details.
 *
 * The user must supply a valid pointer to an rdModel on construction.
 */
class RDSIMULATION_API rdIntegRKF
	: public rdRKF
{

//=============================================================================
// DATA
//=============================================================================
private:
	/** Status of the integration. */
	int _status;
	/** Number of integration steps successfully taken. */
	int _steps;
	/** Number of integration step trys. */
	int _trys;
	/** Maximum number of steps in an integration. */
	int _maxSteps;
	/** Flag for signaling a desired halt. */
	bool _halt;
	/** Minimum step size. */
	double _dtMin;
	/** Maximum step size. */
	double _dtMax;
	/** Flag to indicate whether or not specified integration time steps
	should be used.  The specified integration time steps are held in _tVec.
	If _tVec does not contain time steps appropriate for the integration,
	an exception is thrown. */
	bool _specifiedDT;
	/** Flag to indicate whether or not constant (fixed) integration time
	steps should be used.  The constant integration time step is set using
	setDT(). */
	bool _constantDT;
	/** Constant integration time step. */
	double _dt;
	/** Vector of integration time steps. */
	rdArray<double> _tArray;
	/** Vector of integration time step deltas. */
	rdArray<double> _dtArray;
	/** Name to be shown by the UI */
	static std::string _displayName;

//=============================================================================
// METHODS
//=============================================================================
public:
	rdIntegRKF(Integrand *aIntegrand,
		double aTol=1.0e-4,double aTolFine=-1.0);
	virtual ~rdIntegRKF();
private:
	void setNull();

public:
	//--------------------------------------------------------------------------
	//	GET AND SET
	//--------------------------------------------------------------------------
	// MIN DT
	void setMinDT(double aMin);
	double getMinDT();
	// MIN DT
	void setMaxDT(double aMax);
	double getMaxDT();
	// MAX STEPS
	void setMaximumNumberOfSteps(int aMaxSteps);
	int getMaximumNumberOfSteps();
	// STATUS
	int getStatus();
	// SEPECIFIED TIME STEP
	void setUseSpecifiedDT(bool aTrueFalse);
	bool getUseSpecifiedDT() const;
	// CONSTANT TIME STEP
	void setUseConstantDT(bool aTrueFalse);
	bool getUseConstantDT() const;
	// DT
	void setDT(double aDT);
	double getDT() const;
	// DT VECTOR
	const rdArray<double>& getDTArray();
	void setDTArray(int aN,const double aDT[],double aTI=0.0);
	double getDTArrayDT(int aStep);
	void printDTArray(const char *aFileName=NULL);
	// TIME VECTOR
	const rdArray<double>& getTimeArray();
	double getTimeArrayTime(int aStep);
	int getTimeArrayStep(double aTime);
	void printTimeArray(const char *aFileName=NULL);
	void resetTimeAndDTArrays(double aTime);
	// NAME
	const std::string& toString() const;

	//--------------------------------------------------------------------------
	//	INTEGRATION
	//--------------------------------------------------------------------------
	bool integrate(double ti,double tf,double *y,double dtFirst=1.0e-3);

	//--------------------------------------------------------------------------
	//	INTERRUPT
	//--------------------------------------------------------------------------
	void halt();
	void clearHalt();
	bool checkHalt();

//=============================================================================
};	// END class rdIntegRKF
//=============================================================================
//=============================================================================


#endif // __rdIntegRKF_h__
