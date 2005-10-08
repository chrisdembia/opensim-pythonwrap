// rdUTWalkingPrescribedIntegCallback.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdUTWalkingPrescribedIntegCallback_h__
#define __rdUTWalkingPrescribedIntegCallback_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include <NMBLTK/Simulation/Model/rdIntegCallback.h>
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
class rdUTWalkingPrescribedIntegCallback : public rdIntegCallback 
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
//=============================================================================
//=============================================================================


#endif // #ifndef __rdUTWalkingPrescribedIntegCallback_h__
