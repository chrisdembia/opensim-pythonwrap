// rdUTWalkingIntegCallback.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdUTWalkingIntegCallback_h__
#define __rdUTWalkingIntegCallback_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include <RD/Tools/rdMath.h>
#include <RD/Tools/rdTools.h>
#include <RD/Simulation/Model/rdModel.h>
#include <RD/Simulation/Model/rdIntegCallback.h>
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
class rdUTWalkingIntegCallback : public rdIntegCallback 
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
//=============================================================================
//=============================================================================


#endif // #ifndef __rdUTWalkingIntegCallback_h__
