// rdCallbackSet.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2003 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdCallbackSet_h__
#define __rdCallbackSet_h__


// INCLUDES
#include <RD/Simulation/rdSimulationDLL.h>
#include <RD/Tools/rdObject.h>
#include "rdModel.h"
#include "rdCallback.h"
#include <RD/Tools/rdSet.h>


template class RDSIMULATION_API rdSet<rdCallback>;


//=============================================================================
//=============================================================================
/**
 * A class for holding and managing a set of callbacks for a model.
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class RDSIMULATION_API rdCallbackSet : public rdSet<rdCallback>
{

//=============================================================================
// DATA
//=============================================================================
protected:
	/** Model for which the callbacks have been set. */
	rdModel *_model;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdCallbackSet(rdModel *aModel=0);
	virtual ~rdCallbackSet();
private:
	void setNull();
public:

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	rdModel* getModel();
	void setOn(bool aTrueFalse);

/**
	void makeIntegCallbacksConsecutive();
	void listIntegCallbacks();
*/


//=============================================================================
};	// END of class rdCallbackSet
//=============================================================================
//=============================================================================


#endif // __rdCallbackSet_h__


