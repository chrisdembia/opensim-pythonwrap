// rdOptimizationTarget.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2000 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include "rdSQPDLL.h"
#include <stdlib.h>
#include <stdio.h>
#include "rdOptimizationTarget.h"


//=============================================================================
// EXPORTED STATIC CONSTANTS
//=============================================================================
const double rdOptimizationTarget::SMALLDX = 1.0e-14;

//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
//_____________________________________________________________________________
/**
 * Destructor.
 */
rdOptimizationTarget::
~rdOptimizationTarget()
{
	if(_dx!=NULL) {delete[] _dx;  _dx=NULL; }
}
//_____________________________________________________________________________
/**
 * Construct an optimization target.
 *
 * @param aNX The number of controls.
 */
rdOptimizationTarget::
rdOptimizationTarget(int aNX)
{
	setNull();

	// SET NUMBER OF CONTROLS
	setNX(aNX);
}


//==============================================================================
// CONSTRUCTION
//==============================================================================
//------------------------------------------------------------------------------
// NULL
//------------------------------------------------------------------------------
///______________________________________________________________________________
/**
 * Set NULL values for the member variables.
 */
void rdOptimizationTarget::
setNull()
{
	_nEval = 0;
	_nx = 0;
	_np = 1;
	_nineqn = 0;
	_nineq = 0;
	_neqn = 0;
	_neq = 0;  // Used to be 2, and I don't know why.
	_dx = NULL;
}

//==============================================================================
// SET AND GET
//==============================================================================
//------------------------------------------------------------------------------
// CONTROLS
//------------------------------------------------------------------------------
///______________________________________________________________________________
/**
 * Set the number of controls.
 *
 * The number of controls can be set at any time.  However, the perturbation
 * sizes for the controls (i.e., _dx) is destroyed.  Therefore, the
 * perturbation sizes must be reset.
 *
 * @param aNX Number of controls.
 * @see setDX()
 */
void rdOptimizationTarget::
setNX(int aNX)
{
	_nx = aNX;
	if(_nx<0) _nx = 0;

	// ALLOCATE PERTURBATION VECTOR
	if(_dx!=NULL) delete[] _dx;
	if(_nx>0) _dx = new double[_nx];
}
//______________________________________________________________________________
/**
 * Get the number of controls.
 *
 * @return Number of controls.
 */
int rdOptimizationTarget::
getNX()
{
	return(_nx);
}

//------------------------------------------------------------------------------
// DERIVATIVE PERTURBATION SIZES
//------------------------------------------------------------------------------
//______________________________________________________________________________
/**
 * Set the derivative perturbation size.
 */
void rdOptimizationTarget::
setDX(int aIndex,double aValue)
{
	// CHECK FOR NULL
	if(_dx==NULL) return;

	// CHECK INDEX
	if(!isControlIndexValid(aIndex)) return;

	// VALIDATE VALUE
	validatePerturbationSize(aValue);

	// SET VALUE
	_dx[aIndex] = aValue;
}
//______________________________________________________________________________
/**
 * Set the derivative perturbation size for all controls.
 */
void rdOptimizationTarget::
setDX(double aValue)
{
	// CHECK FOR NULL
	if(_dx==NULL) return;

	// VALIDATE VALUE
	validatePerturbationSize(aValue);

	// SET VALUE
	for(int i=0;i<_nx;i++) _dx[i] = aValue;
}
//______________________________________________________________________________
/**
 * Get the derivative perturbation size.
 */
double rdOptimizationTarget::
getDX(int aIndex)
{
	// CHECK FOR NULL
	if(_dx==NULL) return(0.0);

	// CHECK INDEX
	if(!isControlIndexValid(aIndex)) return(0.0);

	return(_dx[aIndex]);
}
//______________________________________________________________________________
/**
 * Get a pointer to the vector of derivative perturbation sizes.
 */
double* rdOptimizationTarget::
getDXArray()
{
	return(_dx);
}
//------------------------------------------------------------------------------
// EVALUATIONS
//------------------------------------------------------------------------------
//______________________________________________________________________________
/**
 * Get the number of evaluations.
 */
void rdOptimizationTarget::
setNEvaluations(int aN)
{
	_nEval = aN;
}
//______________________________________________________________________________
/**
 * Get the number of evaluations.
 */
int rdOptimizationTarget::
getNEvaluations()
{
	return(_nEval);
}

//------------------------------------------------------------------------------
// PERFORMANCE
//------------------------------------------------------------------------------
///______________________________________________________________________________
/**
 * Get the number of performance criteria.
 */
int rdOptimizationTarget::
getNP()
{
	return(_np);
}

//------------------------------------------------------------------------------
// TOTAL CONSTRAINTS
//------------------------------------------------------------------------------
//______________________________________________________________________________
/**
 * Get the total number of constraints.
 */
int rdOptimizationTarget::
getNC()
{
	return(_nineq+_neq);
}
//------------------------------------------------------------------------------
// INEQUALITY CONSTRAINTS
//------------------------------------------------------------------------------
//______________________________________________________________________________
/**
 * Get the total number of inequality constraints.
 */
int rdOptimizationTarget::
getNCInequality()
{
	return(_nineq);
}
//______________________________________________________________________________
/**
 * Get the number of nonlinear inequality constraints.
 */
int rdOptimizationTarget::
getNCInequalityNonlinear()
{
	return(_nineqn);
}
//______________________________________________________________________________
/**
 * Get the number of linear inequality constraints.
 */
int rdOptimizationTarget::
getNCInequalityLinear()
{
	return(_nineq-_nineqn);
}
//------------------------------------------------------------------------------
// EQUALITY CONSTRAINTS
//------------------------------------------------------------------------------
//______________________________________________________________________________
/**
 * Get the total number of equality constraints.
 */
int rdOptimizationTarget::
getNCEquality()
{
	return(_neq);
}
//______________________________________________________________________________
/**
 * Get the number of nonlinear equality constraints.
 */
int rdOptimizationTarget::
getNCEqualityNonlinear()
{
	return(_neqn);
}
//______________________________________________________________________________
/**
 * Get the number of linear equality constraints.
 */
int rdOptimizationTarget::
getNCEqualityLinear()
{
	return(_neq-_neqn);
}



//==============================================================================
// UTILITY
//==============================================================================
//______________________________________________________________________________
/**
 * Is a control index valid?
 */
bool rdOptimizationTarget::
isControlIndexValid(int aIndex)
{
	if(aIndex>=_nx) {
		printf("rdOptimizationTarget.isControlIndexValid: false.\n");
		return(false);
	}
	return(true);
}
//______________________________________________________________________________
/**
 * Ensure that a derivative perturbation is a valid size
 */
void rdOptimizationTarget::
validatePerturbationSize(double &aSize)
{
	if(aSize<SMALLDX) {
		printf("rdOptimizationTarget.validatePerturbationSize: WARNING- ");
		printf("dx size too small (%le).\n",aSize);
		printf("\tResetting dx=%le.\n",SMALLDX);
		aSize = SMALLDX;
	}
}
