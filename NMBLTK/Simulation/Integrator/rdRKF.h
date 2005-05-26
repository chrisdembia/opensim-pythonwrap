// rdRKF.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2000, 2003 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdRKF_h__
#define __rdRKF_h__

// INCLUDES
#include "rdIntegrator.h"
#include <RD/Simulation/Model/rdModel.h>
#include <RD/Simulation/Control/rdControlSet.h>

#ifdef SWIG
	#ifdef RDSIMULATION_API
		#undef RDSIMULATION_API
		#define RDSIMULATION_API
	#endif
#endif

// EXPORTED CONSTANTS
/*
extern RDSIMULATION_API const int rdRKF_NORMAL;
extern RDSIMULATION_API const int rdRKF_FINE;
extern RDSIMULATION_API const int rdRKF_POOR;
extern RDSIMULATION_API const int rdRKF_NAN;
extern RDSIMULATION_API const int rdRKF_ERROR;
extern RDSIMULATION_API const int rdRKF_TOO_MANY_STEPS;
*/

//=============================================================================
//=============================================================================
/**
 * A class which integrates the equations of motion forward one step in time.
 *
 * The integration method is based on a Runge-Kutta-Feldberg 5-6 Variable-Step
 * Integrator adapted from one given by Atkinson, L.V., et al,
 * "Numerical Methods with Fortran 77.", pp. 310-322, Addison-Wesley
 * Publishing Company, 1989.
 *
 * The user must supply a pointer to an rdModel on construction.
 */
class RDSIMULATION_API rdRKF
{
//=============================================================================
// DATA
//=============================================================================
public:
	enum status {
		rdRKF_NORMAL=20,
		rdRKF_FINE=30,
		rdRKF_POOR=-40,
		rdRKF_NAN=-50,
		rdRKF_ERROR=-60,
		rdRKF_TOO_MANY_STEPS=-70
	};
protected:
	/** Integration tolerance. */
	double _tol;
	/** Integration fine tolerance. */
	double _tolFine;
	/** Dynamic model. */
	rdModel *_model;
	/** Number of controls. */
	int _nx;
	/** Controls at time t. */
	double *_x;
	/** Number of states. */
	int _ny;
	/** Work arrays for computing the new states. */
	double *_yv,*_ye,*_dy;
	double *_k1,*_k2,*_k3,*_k4,*_k5,*_k6;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdRKF(rdModel *aModel,double aTol=1.0e-4,double aTolFine=-1.0);
	virtual ~rdRKF();

	//--------------------------------------------------------------------------
	// MEMORY
	//--------------------------------------------------------------------------
private:
	int allocateMemory();
	int freeMemory();

	//--------------------------------------------------------------------------
	//	GET AND SET
	//--------------------------------------------------------------------------
public:
	// MODEL
	rdModel* getModel();
	// NUMBER OF STATES
	int getNY();
	// TOLERANCE
	void setTolerance(double aTol,double aTolFine=-1.0);
	double getTolerance();
	void setFineTolerance(double aFineTol);
	double getFineTolerance();

	//--------------------------------------------------------------------------
	// INTEGRATION
	//--------------------------------------------------------------------------
	int step(double dt,double t,rdControlSet &x,double *y);
	int step(double dt,double t,double *x,double *y);
	int stepFixed(double dt,double t,rdControlSet &x,double *y);
	int stepFixed(double dt,double t,double *x,double *y);

//=============================================================================
};	// END class rdRKF
//=============================================================================
//=============================================================================

#endif  // __rdRKF_h__
