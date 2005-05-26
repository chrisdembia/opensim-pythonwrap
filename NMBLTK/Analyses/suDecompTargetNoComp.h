// suDecompTargetNoComp.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suDecompTargetNoComp_h__
#define __suDecompTargetNoComp_h__


//==============================================================================
// INCLUDES
//==============================================================================
#include <math.h>
#include <RD/Tools/rdMath.h>
#include <RD/SQP/rdFSQP.h>
#include <RD/Simulation/Model/rdModel.h>
#include "suDecompHardUTWalkNoComp.h"



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * An optimization target for finding spring forces that will achieve
 * specified acceleration constraints.  This "NoComp" version is a 
 * companion to suDecmpHardUTWalkNoComp and accepts this type of analysis
 * as an input
 */
class suDecompTargetNoComp : public rdOptimizationTarget
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//==============================================================================
// DATA
//==============================================================================
private:
	suDecompHardUTWalkNoComp *_analysis;

//==============================================================================
// METHODS
//==============================================================================
public:
	//---------------------------------------------------------------------------
	// CONSTRUCTION
	//---------------------------------------------------------------------------
	virtual ~suDecompTargetNoComp();
	suDecompTargetNoComp(int aNX,int aNC,suDecompHardUTWalkNoComp *aAnalysis);

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
};	// END class suDecompTargetNoComp
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


#endif // #ifndef __suDecompTargetNoComp_h__
