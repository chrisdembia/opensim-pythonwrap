#ifndef _rdUTWalkingIntegCallback_h_
#define _rdUTWalkingIntegCallback_h_
// rdUTWalkingIntegCallback.h
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
#include "rdUTWalking8.h"


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

class rdUTWalkingIntegCallback : public IntegCallback 
{
//=============================================================================
// DATA
//=============================================================================
private:


//=============================================================================
// METHODS
//=============================================================================
public:
	rdUTWalkingIntegCallback(rdUTWalking8 *aModel);
	virtual ~rdUTWalkingIntegCallback();
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
};	// END of class rdUTWalkingIntegCallback

}; //namespace
//=============================================================================
//=============================================================================


#endif // #ifndef __rdUTWalkingIntegCallback_h__
