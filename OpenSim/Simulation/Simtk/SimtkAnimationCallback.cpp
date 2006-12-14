// SimtkAnimationCallback.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*
* Copyright (c) 2005, Stanford University. All rights reserved. 
* Redistribution and use in source and binary forms, with or without 
* modification, are permitted provided that the following conditions
* are met: 
*  - Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer. 
*  - Redistributions in binary form must reproduce the above copyright 
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the distribution. 
*  - Neither the name of the Stanford University nor the names of its 
*    contributors may be used to endorse or promote products derived 
*    from this software without specific prior written permission. 
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN 
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
* POSSIBILITY OF SUCH DAMAGE. 
*/

/*  
 * Author:  
 */


//=============================================================================
// INCLUDES
//=============================================================================
#include <OpenSim/Tools/Mtx.h>
#include <OpenSim/Simulation/SIMM/AbstractModel.h>
#include <OpenSim/Simulation/SIMM/AbstractDynamicsEngine.h>
#include <OpenSim/Simulation/SIMM/BodySet.h>
#include <OpenSim/Simulation/Model/IntegCallbackSet.h>
#include <OpenSim/Simulation/SIMM/SimmBody.h>
#include <OpenSim/Simulation/SIMM/SimmKinematicsEngine.h>
#include <OpenSim/Simulation/SIMM/AbstractModel.h>
#include "SimtkAnimationCallback.h"


using namespace std;
using namespace OpenSim;


//=============================================================================
// STATICS
//=============================================================================
bool SimtkAnimationCallback::_busy = false;


//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
SimtkAnimationCallback::~SimtkAnimationCallback()
{
	delete[] _transforms;
}

//_____________________________________________________________________________
/**
 * Default constructor.
 *
 * Note that this constructor adds the callback to the model.  Derived
 * classes should not also add themselves to the model.
 *
 * @param aModel Model to which the callback mthods apply.
 */
SimtkAnimationCallback::SimtkAnimationCallback(AbstractModel *aModel) :
	IntegCallback(aModel)
{
	cout<<"\n\nCreating new SimtkAnimationCallback...\n";
	// NULL
	setNull();
	AbstractDynamicsEngine& de = aModel->getDynamicsEngine();
	// We keep pointer to body's xform. Don't delete them on exit
	_transforms = new Transform[de.getNumBodies()];
	static double Orig[3] = { 0.0, 0.0, 0.0 };	// Zero 

	BodySet *bodySet = de.getBodySet();
	AbstractBody* body;
	int i,nb = bodySet->getSize();
	for(i=0;i<nb;i++) {
		body = bodySet->get(i);
		_transforms[i] = de.getTransform(*body);
	}

	_currentTime=0.0;
	cout<<endl<<endl;
}

//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set NULL values for member variables.
 */
void SimtkAnimationCallback::
setNull()
{
	setType("SimtkAnimationCallback");
	setName("UNKNOWN");
	//_transforms.setSize(0);
	_currentTime=0.0;
}


//=============================================================================
// GET AND SET
//=============================================================================
//_____________________________________________________________________________
/**
 * This method is called from ui code to give user feedback about how far along 
 * is the simulation
 */
const double SimtkAnimationCallback::
getCurrentTime() const
{
	return _currentTime;
}

//=============================================================================
// CALLBACKS
//=============================================================================
//_____________________________________________________________________________
/**
 * This method is called after each successful integration time step and is
 * intended to be used for conducting analyses, driving animations, etc.
 *
 * Override this method in derived classes.
 *
 * @param aXPrev Control values at the previous time step.
 * @param aYPrev State values at the previous time step.
 * @param aStep Number of integrations steps that have been completed.
 * @param aDT Size of the time step that WAS just completed.
 * @param aT Current time in the integration.
 * @param aX Current control values.
 * @param aY Current states.
 * @param aClientData General use pointer for sending in client data.
 */
int SimtkAnimationCallback::
step(double *aXPrev,double *aYPrev,int aStep,double aDT,double aT,
	double *aX,double *aY,void *aClientData)
{
	return (0);
}
const Transform* SimtkAnimationCallback::getBodyTransform(int index) const
{
	return &_transforms[index];
}
/**
 * Cache Coms for bodies so that we can get the xform for the bodies from SDFast in one go with 
 * minimal computation on our side. If displaying a SimmModel for example in IK then offsets are set to 0
 */
void SimtkAnimationCallback::extractOffsets(AbstractModel& displayModel)
{
}
/*------------------------------------------------------------------
 * getTransformsFromKinematicsEngine is a utility used to filll the 
 * _transforms array from a SimmKinematicsEngine
 * @param simmModel: The model to use with associated kinematicsEngine
 */
void SimtkAnimationCallback::
getTransformsFromKinematicsEngine(AbstractModel& simmModel)
{
}
