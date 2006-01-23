// suDecompTarget.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suDecompTarget_h__
#define __suDecompTarget_h__


//==============================================================================
// INCLUDES
//==============================================================================
#include <math.h>
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/SQP/rdFSQP.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include "suDecompHard.h"



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * An optimization target for finding spring forces that will achieve
 * specified acceleration constraints.
 */
class suDecompTarget : public rdOptimizationTarget
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//==============================================================================
// DATA
//==============================================================================
private:
	suDecompHard *_analysis;

//==============================================================================
// METHODS
//==============================================================================
public:
	//---------------------------------------------------------------------------
	// CONSTRUCTION
	//---------------------------------------------------------------------------
	virtual ~suDecompTarget();
	suDecompTarget(int aNX,int aNC,suDecompHard *aAnalysis);

	//---------------------------------------------------------------------------
	// SET AND GET
	//---------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// REQUIRED OPTIMIZATION TARGET METHODS
	//--------------------------------------------------------------------------
	// PERFORMANCE AND CONSTRAINTS
	int compute(double *x,double *p,double *c);
	int computeGradients(double *dx,double *x,double *dpdx,double *dcdx);
	// PERFORMANCE
	int computePerformance(double *x,double *p);
	int computePerformanceGradient(double *x,double *dpdx);
	// CONSTRAINTS
	int computeConstraint(double *x,int i,double *c);
	int computeConstraintGradient(double *x,int i,double *dcdx);

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
};	// END class suDecompTarget
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


#endif // #ifndef __suDecompTarget_h__
