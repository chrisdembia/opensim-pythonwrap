#ifndef _rdUTWalkingPrescribedIntegCallback_h_
#define _rdUTWalkingPrescribedIntegCallback_h_
// rdUTWalkingPrescribedIntegCallback.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include <OpenSim/Tools/rdMath.h>
#include <OpenSim/Tools/rdTools.h>
#include <OpenSim/Simulation/Model/Model.h>
#include <OpenSim/Simulation/Model/IntegCallback.h>
#include "rdUTWalking8Prescribed.h"


//=============================================================================
//=============================================================================
/**
 * A integration callback used to update the foot-ground spring zeros in
 * x-z plane (horizontal plane) of the floor.
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
namespace OpenSim { 

class rdUTWalkingPrescribedIntegCallback : public IntegCallback 
{
//=============================================================================
// DATA
//=============================================================================
private:


//=============================================================================
// METHODS
//=============================================================================
public:
	rdUTWalkingPrescribedIntegCallback(rdUTWalking8Prescribed *aModel);
	virtual ~rdUTWalkingPrescribedIntegCallback();
private:
	void setNull();

public:

	//--------------------------------------------------------------------------
	// CALLBACKS
	//--------------------------------------------------------------------------
	virtual int
		step(double *aXPrev,double *aYPrev,int aStep,double aDT,double aT,
		double *aX,double *aY,void *aClientData=NULL);

//=============================================================================
};	// END of class rdUTWalkingPrescribedIntegCallback


}; //namespace
//=============================================================================
//=============================================================================


#endif // #ifndef __rdUTWalkingPrescribedIntegCallback_h__
