// rdRKF_fixed.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2003 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdRKF_fixed_h__
#define __rdRKF_fixed_h__

// INCLUDES
#include "rdIntegrator.h"
#include <RD/Simulation/Model/rdModel.h>
#include "rdRKF.h"


//=============================================================================
//=============================================================================
/**
 * A class which integrates the equations of motion forward one step in time.
 *
 * The integration method is based on a 4th Order Runge-Kutta
 * integrator adapted from one given by Atkinson, L.V., et al,
 * "Numerical Methods with Fortran 77.", pp. 310-322, Addison-Wesley
 * Publishing Company, 1989.
 *
 * The user must supply a pointer to an rdModel on construction.
 */
class RDSIMULATION_API rdRKF_fixed
{
//=============================================================================
// DATA
//=============================================================================
protected:
	rdModel *_model;
	int _ny;
	double *_yv,*_dy;
	double *_k1,*_k2,*_k3,*_k4,*_k5;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdRKF_fixed(rdModel *aModel);
	virtual ~rdRKF_fixed();

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
	// SET AND GET
	rdModel* getModel();
	int getNY();

	//--------------------------------------------------------------------------
	// INTEGRATION
	//--------------------------------------------------------------------------
	int step(double dt,double t,double *xt,double *y);

//=============================================================================
};	// END class rdRKF_fixed
//=============================================================================
//=============================================================================

#endif  // __rdRKF_fixed_h__
