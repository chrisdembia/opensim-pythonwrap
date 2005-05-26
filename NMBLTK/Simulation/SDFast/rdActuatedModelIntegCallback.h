// rdActuatedModelIntegCallback.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdActuatedModelIntegCallback_h__
#define __rdActuatedModelIntegCallback_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include <NMBLTK/Simulation/Model/rdIntegCallback.h>
#include "rdActuatedModel_SDFast.h"


//=============================================================================
//=============================================================================
/**
 * A integration callback used to simulate a slip.  This is done by changing
 * the friction coefficients of contact forces during a simulation.
 * Specifically, between the start and end time of the callback
 * (see rdCallback::setStartTime() and rdCallback::setEndTime()), the
 * coefficients of friction for all contact forces is set to a specified
 * value (muSlip).  Otherwise, the coefficients of friction for all
 * contact forces is set to a normal value (mu).
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class rdActuatedModelIntegCallback : public rdIntegCallback 
{
//=============================================================================
// DATA
//=============================================================================
private:


//=============================================================================
// METHODS
//=============================================================================
public:
	rdActuatedModelIntegCallback(rdActuatedModel_SDFast *aModel);
	virtual ~rdActuatedModelIntegCallback();
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
};	// END of class rdActuatedModelIntegCallback
//=============================================================================
//=============================================================================


#endif // #ifndef __rdActuatedModelIntegCallback_h__
