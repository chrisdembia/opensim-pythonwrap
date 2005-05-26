// rdSimtkAnimationCallback.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2004 Realistic Dynamics, Inc.
// All rights reserved.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdSimtkAnimationCallback_h__
#define __rdSimtkAnimationCallback_h__


// INCLUDES
#include <NMBLTK/Tools/rdObject.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include <NMBLTK/Simulation/Model/rdIntegCallback.h>
#include <NMBLTK/Tools/rdTransform.h>

//=============================================================================
//=============================================================================
/**
 * A class for generating an animation sequence in Simtk platform based on a
 * forward dynamic simulation.
 *
 * @author Ayman Habib (After rdmAnimationCallback)
 * @version 1.0
 */
class RDSIMULATION_API rdSimtkAnimationCallback : public rdIntegCallback
{

//=============================================================================
// DATA
//=============================================================================
protected:
	/** Keep pointers to body transforms. This is not used right now as 
	 * when we get the data from SDFast we recover translations and rotations separately
	 * And these are passed directly to VTK for display 
	 *
	 * @todo check if building the xform and passing it directly to vtk is faster
	 */
	
	rdArrayPtrs<rdTransform> _transforms;
	/** Current simulation time for feedback purposes */
	double					 _currentTime;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdSimtkAnimationCallback(rdModel *aModel);
	virtual ~rdSimtkAnimationCallback();
private:
	void setNull();
public:

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	const double getCurrentTime() const;
	//--------------------------------------------------------------------------
	// CALLBACKS
	//--------------------------------------------------------------------------
	virtual int
		step(double *aXPrev,double *aYPrev,int aStep,double aDT,double aT,
		double *aX,double *aY,void *aClientData=NULL);

//=============================================================================
};	// END of class rdSimtkAnimationCallback
//=============================================================================
//=============================================================================

#endif // __rdSimtkAnimationCallback_h__


