// rdDerivCallback.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2002, 2003 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdDerivCallback_h__
#define __rdDerivCallback_h__
//============================================================================
#include <NMBLTK/Tools/rdObject.h>
#include "rdModel.h"
#include "rdCallback.h"


//=============================================================================
//=============================================================================
/**
 * An abstract class for specifying a derivative callback.
 *
 * Derivative callbacks are registered with a model and provide a
 * set of methods that the model calls during computation of the
 * model state derivatives.  The methods are set(), computeContact(),
 * applyContact(), computeActuation(), applyActuation(), and
 * computeDerivatives().  These methods provide low-level access for
 * making adjustments to model states and applied forces,
 * applying additional forces, and/or altering state derivatives.
 * Each of these methods is intended to be called FOLLOWING the 
 * corresponding action in rdModel::deriv(), although rdModel::deriv()
 * can be written to call these methods in any order or not at all.
 * 
 * Derivative callbacks are meant to make alterations to the "normal" model
 * of simulation either for analysis or to achieve some unusual effect.
 * Alternately, this class can be used to implement the entirety of the
 * rdModel::deriv() method, giving the user nearly complete control of how
 * derivatives are computed without making changes to the model.  To
 * accomplish this, the user may need to make a new derived model class
 * that overrides rdModel::deriv() with a new method that makes the
 * appropriate rdDerivCallback method calls.
 *
 * On a final note, it is possible to register many derivative callbacks
 * with a model and no attempt is made to ensure that the
 * the actions of registered callbacks are compatible.  Ensuring
 * compatibility is left to the user.
 *
 * @author Frank C. Anderson
 * @version 1.0
 * @see rdModel::deriv()
 */
class RDSIMULATION_API rdDerivCallback : public rdCallback
{

//=============================================================================
// DATA
//=============================================================================
protected:

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdDerivCallback(rdModel *aModel);
	virtual ~rdDerivCallback();
private:
	void setNull();

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
public:

	//--------------------------------------------------------------------------
	// CALLBACKS
	//--------------------------------------------------------------------------
	virtual void
		set(double aT,double *aX,double *aY);
	virtual void
		computeContact(double aT,double *aX,double *aY);
	virtual void
		applyContact(double aT,double *aX,double *aY);
	virtual void
		computeActuation(double aT,double *aX,double *aY);
	virtual void
		applyActuation(double aT,double *aX,double *aY);
	virtual void
		computeDerivatives(double aT,double *aX,double *aY,double *aDY);
	//--------------------------------------------------------------------------
	// UTILITY
	//--------------------------------------------------------------------------
	virtual void reset() { };
//=============================================================================
};	// END of class rdDerivCallback
//=============================================================================
//=============================================================================

#endif // __rdDerivCallback_h__


