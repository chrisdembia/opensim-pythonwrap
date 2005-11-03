// suDecompTargetNoCompPrescribed.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suDecompTargetNoCompPrescribed_h__
#define __suDecompTargetNoCompPrescribed_h__


//==============================================================================
// INCLUDES
//==============================================================================
#include <math.h>
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/SQP/rdFSQP.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include "suDecompHardUTWalkNoCompPrescribed.h"



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * An optimization target for finding spring forces that will achieve
 * specified acceleration constraints.  This "NoComp" version is a 
 * companion to suDecmpHardUTWalkNoComp and accepts this type of analysis
 * as an input
 */
class suDecompTargetNoCompPrescribed : public rdOptimizationTarget
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//==============================================================================
// DATA
//==============================================================================
private:
	suDecompHardUTWalkNoCompPrescribed *_analysis;

//==============================================================================
// METHODS
//==============================================================================
public:
	//---------------------------------------------------------------------------
	// CONSTRUCTION
	//---------------------------------------------------------------------------
	virtual ~suDecompTargetNoCompPrescribed();
	suDecompTargetNoCompPrescribed(int aNX,int aNC,suDecompHardUTWalkNoCompPrescribed *aAnalysis);

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
};	// END class suDecompTargetNoCompPrescribed
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


#endif // #ifndef __suDecompTargetNoCompPrescribed_h__
