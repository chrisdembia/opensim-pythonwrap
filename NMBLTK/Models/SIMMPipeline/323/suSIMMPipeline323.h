// suSIMMPipeline323.h
// Joon H. Shim shimm@stanford.edu

#ifndef __suSIMMPipeline323_h__
#define __suSIMMPipeline323_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include <RD/Simulation/SDFast/rdSDFastDLL.h>
#include <RD/Simulation/Model/rdModel.h>
#include <RD/Simulation/SDFast/rdSDFast.h>
#include <RD/Simulation/SDFast/rdActuatedModel_SDFast.h>

//-----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//-----------------------------------------------------------------------------

#include <universal_323.h>
#include "simm_init_323.h"

//-----------------------------------------------------------------------------
#ifdef __cplusplus
}
#endif
//-----------------------------------------------------------------------------

//=============================================================================
//=============================================================================
/**
 * A class that wraps a model created by the SIMM Dynamics Pipeline 3.2.3.
 *
 * At this time, in addition to construction (i.e., model initialization),
 * the class implements the "actuation" and "deriv" methods of rdModel.
 * In the deriv() methods the appropriate calls are made for any
 * rdDerivCallback's registered on the model.  Also, the appropriate calls
 * are made at the beginning, during, and end of an integration for any
 * analyses registered with the model.
 *
 * The contact methods implemented through the Dynamics Pipeline are not
 * accessible.  It is assumed that all contact will be implemented through
 * rdActuatedModel_SDFast.
 *
 * @authors Joon Shim, Frank C. Anderson
 * @version 1.0
 */
class RDSDFAST_API suSIMMPipeline323 : public rdActuatedModel_SDFast
{
//=============================================================================
// DATA
//=============================================================================
public:

protected:
	double *_y;
	double *_dy;

//=============================================================================
// METHODS
//=============================================================================
public:
	suSIMMPipeline323(char *aParametersFileName,rdContactForceSet *aContacts=NULL);
	virtual ~suSIMMPipeline323();
	virtual void computeActuation();
	virtual void applyActuatorForce(int aID);
	virtual void applyActuatorForces() ;
	virtual void setActuatorForce(int aID,double aForce);
	virtual double getActuatorSpeed(int aID) const;
	virtual double getActuatorForce(int aID) const;
	virtual double getActuatorPower(int aID) const;

	virtual int deriv(double t, double *xt, double *y, double *dy);
	virtual int deriv(double t, double *xt, double *y, double *dqdt, double *dudt);
	
	virtual void
		integBeginCallback(int aStep,double aDT,double aT,double *aX,double *aY,
		 void *aClientData);
	virtual void
		integStepCallback(double *aXPrev,double *aYPrev,int aStep,double aDT,
		 double aT,double *aX,double *aY,
		 void *aClientData);
	virtual void
		integEndCallback(int aStep,double aDT,double aT,double *aX,double *aY,
		 void *aClientData);

private:
	void setNull();					// PUBLIC VIRTUAL? - Joon
	void constructInitialStates();// It is likely to have another function with 
	void constructNames();			// the same name in lower classes.
	
public:
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	// STATES
	virtual void setStates(const double aY[]);
	virtual void setConfiguration(const double aY[]);
	virtual void setConfiguration(const double aQ[],const double aU[]);

//=============================================================================
};	// END of class suSIMMPipeline323
//=============================================================================
//=============================================================================


#endif // #ifndef __suSIMMPipeline323_h__
