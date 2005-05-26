// rdMuscle.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Author: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "rdModel.h"
//=============================================================================
#ifndef __rdMuscle_h__
#define __rdMuscle_h__


//=============================================================================
//=============================================================================
/**
 * This class provides basic methods for activation and muscle-tendon dynamics.
 *
 */
class RDSIMULATION_API rdMuscle 
{

//=============================================================================
// DATA
//=============================================================================
private:

//=============================================================================
// METHODS
//=============================================================================
public:
	//--------------------------------------------------------------------------
	// ACTIVATION DYNAMICS
	//--------------------------------------------------------------------------
	static double
		EstimateActivation(double aTRise,double aTFall,double aA0,double aX,
		double aDT);
	static double
		InvertActivation(double aTRise,double aTFall,double aA0,double aA,
		double aDT);
	static double
		DADT(double aTRise,double aTFall,double aX,double aA);
	static double
		DADTNonlinear(double aTRise,double aTFall,double aX,double aA);

	//--------------------------------------------------------------------------
	// MUSCLE-TENDON DYNAMICS FOR AN IDEAL MUSCLE
	//--------------------------------------------------------------------------
	static double f(double aFMax,double aA);

//=============================================================================
};	// END class rdMuscle
//=============================================================================
//=============================================================================

#endif //__rdMuscle_h__
