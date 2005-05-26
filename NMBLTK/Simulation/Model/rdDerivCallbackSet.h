// rdDerivCallbackSet.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdDerivCallbackSet_h__
#define __rdDerivCallbackSet_h__


// INCLUDES
#include "rdModel.h"
#include "rdCallbackSet.h"
#include "rdDerivCallback.h"


//=============================================================================
//=============================================================================
/**
 * A class for holding and managing a set of derivative callbacks for
 * a model.
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class RDSIMULATION_API rdDerivCallbackSet : public rdCallbackSet 
{

//=============================================================================
// DATA
//=============================================================================
public:
protected:

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdDerivCallbackSet(rdModel *aModel=0);
	virtual ~rdDerivCallbackSet();
private:
	void setNull();
public:

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	rdDerivCallback* getDerivCallback(int aIndex) const;

	//--------------------------------------------------------------------------
	// CALLBACKS
	//--------------------------------------------------------------------------
	virtual void
		set(double aT,double *aX,double *aY);
	virtual void
		computeActuation(double aT,double *aX,double *aY);
	virtual void
		applyActuation(double aT,double *aX,double *aY);
	virtual void
		computeContact(double aT,double *aX,double *aY);
	virtual void
		applyContact(double aT,double *aX,double *aY);
	virtual void
		computeDerivatives(double aT,double *aX,double *aY,
		double *aDY);


//=============================================================================
};	// END of class rdDerivCallbackSet
//=============================================================================
//=============================================================================

#endif // __rdDerivCallbackSet_h__


