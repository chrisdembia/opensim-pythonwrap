// rdSQP.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2000 Realistic Dynamics, Inc.
// All rights reserved.
//
// CONFIDENTIAL
//
// The material contain within this file is the property of
// Realistic Dynamics, Inc.  Please do not read, copy, or distribute
// without the expressed writen consent of Realistic Dynamics, Inc.
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdSQP_h__
#define __rdSQP_h__



//=============================================================================
// INCLUDES
//=============================================================================
#include <NMBLTK/Tools/rdMtx.h>
#include "rdSQPDLL.h"
#include "rdOptimizationTarget.h"


//=============================================================================
//=============================================================================
/**
 * This class provides methods for finding the optimal controls of a redundant
 * system by applying sequential quadratic programming techniques.
 */
class RDSQP_API rdSQP
{
//=============================================================================
// DATA
//=============================================================================
private:
	// OPTIMIZATION TARGET
	rdOptimizationTarget *_target;

	// CONTROLS
	int _nx;
	double *_xtmp,*_dx;

	// PERFORMANCE AND CONSTRAINTS
	int _status;
	int _nc,_nceq;
	double _p,*_c,*_cw;

	// DERIVATIVES
	double *_dpdx,*_dcdx,*_dxda;

	// WORKSPACE
	int _nwd,_nwi;
	double *_wd;
	int *_wi;

	// SQP PARAMETERS
	int _statusOpt;
	int _maxIter;
	double _epsOpt,_convergence;

	// LINE SEARCH PARAMETERS
	int _statusLine;
	int _mfc;
	double _epsLine;
	double _fact[4];
	double _minAlpha,_maxAlpha;
	double _firstAlpha;
	double _alpha[4];

//=============================================================================
// METHODS
//=============================================================================
public:
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
	virtual ~rdSQP();
	static void Delete(void *aPtr);
	rdSQP(rdOptimizationTarget *aTarget);

	//--------------------------------------------------------------------------
	// SET AND GET
	//--------------------------------------------------------------------------
	void setMaxIterations(int aMaxIter);
	int getMaxIterations();
	void setConvergenceCriterion(double aMaxIter);
	double getConvergenceCriterion();
	void setMaxEvaluations(int aMaxEval);
	int getMaxEvaluations();
	void setLineConvergenceCriterion(double aMaxIter);
	double getLineConvergenceCriterion();
	void setMinAlpha(double aMin);
	double getMinAlpha();
	void setMaxAlpha(double aMax);
	double getMaxAlpha();


	//--------------------------------------------------------------------------
	// OPTIMAL CONTROLS
	//--------------------------------------------------------------------------
	int computeOptimalControls(const double *xstart,double *x);

	//--------------------------------------------------------------------------
	// DERIVATIVES
	//--------------------------------------------------------------------------
	static int
	CentralDifferences(rdOptimizationTarget *aTarget,
	 double *dx,double *x,double *dpdx,double *dcdx);

	//--------------------------------------------------------------------------
	// SEARCH DIRECTION
	//--------------------------------------------------------------------------
	void
	computeSearchDirection(int *status,double *x,
	 double *p,double *dpdx,double *c,double *dcdx,double *alpha,
	 double *dxda,double *mu);

	//--------------------------------------------------------------------------
	// LINE SEARCH
	//--------------------------------------------------------------------------
	int lineSearch(double *x,double *dx,double *mu,double *xnew);

//=============================================================================
};	// END class rdSQP
//=============================================================================
//=============================================================================

#endif // __rdSQP_h__
