// rdIntegCallback.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2003 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdIntegCallback_h__
#define __rdIntegCallback_h__
//=============================================================================
//#include <rdObject.h>
class rdModel;
#include <NMBLTK/Tools/rdPropertyInt.h>
#include "rdCallback.h"


//=============================================================================
//=============================================================================
/**
 * An abstract class for specifying an integration callback.
 *
 * Integration callbacks are registered with a model and provide a
 * set of methods that the model calls at various stages of an integration.
 * The methods are begin(), which is called at the beginning of an
 * integration, step(), which is called after each successful integration
 * step, and end(), which is called at the completion of an integration.
 * These methods provide low-level access for performing analysis,
 * animating simulations, etc.
 *
 * On a final note, it is possible to register many integration callbacks
 * with a model and no attempt is made to ensure that the
 * the actions of registered callbacks are compatible.  Ensuring
 * compatibility is left to the user.
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class RDSIMULATION_API rdIntegCallback : public rdCallback
{

//=============================================================================
// DATA
//=============================================================================
protected:
	/** Step interval. */
	rdPropertyInt _stepIntervalProp;
	int &_stepInterval;
//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdIntegCallback(rdModel *aModel=0);
	// Support for rdObject behavior
	rdIntegCallback(const std::string &aFileName);
	rdIntegCallback(DOMElement *aElement);
	rdIntegCallback(const rdIntegCallback &aIntegCallback);
	virtual ~rdIntegCallback();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;
	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
#ifndef SWIG
	rdIntegCallback& operator=(const rdIntegCallback &aIntegCallback);
#endif

private:
	void setNull();
	void setupProperties();

public:

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	void setStepInterval(int aStepInterval);
	int getStepInterval() const;

	//--------------------------------------------------------------------------
	// CALLBACKS
	//--------------------------------------------------------------------------
	virtual int
		begin(int aStep,double aDT,double aT,
		double *aX,double *aY,void *aClientData=NULL);
	virtual int
		step(double *aXPrev,double *aYPrev,int aStep,double aDT,double aT,
		double *aX,double *aY,void *aClientData=NULL);
	virtual int
		end(int aStep,double aDT,double aT,
		double *aX,double *aY,void *aClientData=NULL);

//=============================================================================
};	// END of class rdIntegCallback
//=============================================================================
//=============================================================================

#endif // __rdIntegCallback_h__


