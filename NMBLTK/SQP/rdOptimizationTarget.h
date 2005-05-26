// rdOptimizationTarget.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2000 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdOptimizationTarget_h__
#define __rdOptimizationTarget_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include "rdSQPDLL.h"

//=============================================================================
//=============================================================================
/**
 * This class provides an interface specification for optimizing redundant
 * systems.  If a class represents a redundant system for which one would
 * like to find a set of optimal controls, the class should inherit from
 * this class and implement the virtual functions defined here.
 */
class RDSQP_API rdOptimizationTarget  
{
//=============================================================================
// DATA
//=============================================================================
public:
	/** Smallest allowable perturbation size for computing derivatives. */
	static const double SMALLDX;
protected:
	/** Number of performance evaluations. */
	int _nEval;
	/** Number of controls. */
	int _nx;
	/** Number of performance criteria. */
	int _np;
	/** Number of nonlinear inequality constraints. */
	int _nineqn;
	/** Number of inequality constraints. */
	int _nineq;
	/** Number of nonlinear equality constraints. */
	int _neqn;
	/** Number of equality constraints. */
	int _neq;
	/** Perturbation size for computing numerical derivatives. */
	double *_dx;

//=============================================================================
// METHODS
//=============================================================================
public:
	virtual ~rdOptimizationTarget();
	rdOptimizationTarget(int aNX=0);
private:
	void setNull();

	// PERFORMANCE AND CONSTRAINTS
public:
	virtual int
		compute(double *x,double *p,double *c) = 0;
	virtual int
		computeGradients(double *dx,double *x,double *dpdx,double *dcdx) = 0;

	// PERFORMANCE
	virtual int
		computePerformance(double *x,double *p) = 0;
	virtual int
		computePerformanceGradient(double *x,double *dpdx) = 0;

	// CONSTRAINT
	virtual int
		computeConstraint(double *x,int i,double *c) = 0;
	virtual int
		computeConstraintGradient(double *x,int i,double *dcdx) = 0;

	// SET AND GET
	virtual void setNX(int aNX);
	int getNX();
	void setDX(double aVal);
	void setDX(int aIndex,double aVal);
	double getDX(int aIndex);
	double* getDXArray();
	void setNEvaluations(int aN=0);
	int getNEvaluations();
	int getNP();
	int getNC();
	int getNCInequality();
	int getNCInequalityNonlinear();
	int getNCInequalityLinear();
	int getNCEquality();
	int getNCEqualityNonlinear();
	int getNCEqualityLinear();

	// UTILITY
	bool isControlIndexValid(int aIndex);
	void validatePerturbationSize(double &aSize);
};

#endif // __rdSQP_h__
