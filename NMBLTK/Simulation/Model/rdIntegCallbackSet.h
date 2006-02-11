// rdIntegCallbackSet.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2003 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdIntegCallbackSet_h__
#define __rdIntegCallbackSet_h__


// INCLUDES
#include "rdModel.h"
#include "rdCallbackSet.h"
#include "rdIntegCallback.h"


//=============================================================================
//=============================================================================
/**
 * A class for holding and managing a set of integration callbacks for
 * a model.
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class RDSIMULATION_API rdIntegCallbackSet : public rdSet<rdCallback>
{

//=============================================================================
// DATA
//=============================================================================
protected:
	/** Model on which the callbacks have been set. */
	rdModel *_model;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdIntegCallbackSet(rdModel *aModel=0);
	virtual ~rdIntegCallbackSet();
private:
	void setNull();
public:

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	void setModel(rdModel *aModel);
	rdModel* getModel();
	void setOn(bool aTrueFalse);
	rdIntegCallback* getIntegCallback(int aIndex) const;

	//--------------------------------------------------------------------------
	// CALLBACKS
	//--------------------------------------------------------------------------
	virtual void
		begin(int aStep,double aDT,double aT,
		double *aX,double *aY,void *aClientData=NULL);
	virtual void
		step(double *aXPrev,double *aYPrev,int aStep,double aDT,double aT,
		double *aX,double *aY,void *aClientData=NULL);
	virtual void
		end(int aStep,double aDT,double aT,
		double *aX,double *aY,void *aClientData=NULL);

//=============================================================================
};	// END of class rdIntegCallbackSet
//=============================================================================
//=============================================================================

#endif // __rdIntegCallbackSet_h__


