// rdSimtkAnimationCallback.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2004 Stanford University
// All rights reserved.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include <NMBLTK/Tools/rdMtx.h>
#include <NMBLTK/Simulation/Model/rdIntegCallbackSet.h>
#include "rdSimtkAnimationCallback.h"
#include <NMBLTK/Tools/rdTransformChangeEvent.h>

//=============================================================================
// STATICS
//=============================================================================


//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
rdSimtkAnimationCallback::~rdSimtkAnimationCallback()
{
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
rdSimtkAnimationCallback::rdSimtkAnimationCallback(rdModel *aModel) :
	rdIntegCallback(aModel)
{
	// NULL
	setNull();

	// We keep pointer to body's xform. Don't delete it on exit
	_transforms.setMemoryOwner(false);

	static double Orig[3] = { 0.0, 0.0, 0.0 };	// Zero 
	double t[3];	// Translation from sdfast
	double com[3];	// Center of mass
	double rot[3];	// Rotation angles 
	double dirCos[3][3];	// Direction cosines
	for(int i=0;i<_model->getNB();i++) {
		// get position from sdfast
		// adjust by com
		_model->getBody(i)->getCenterOfMass(com);
		for(int k=0; k < 3; k++)
			Orig[k] = -com[k];
		_model->getPosition(i, Orig, t);

		_model->getDirectionCosines(i,dirCos);
		_model->convertDirectionCosinesToAngles(dirCos,
			&rot[0],&rot[1],&rot[2]);
		// Initialize xform to identity
		_model->getBody(i)->getTransform().setOrientation(rot);
		_model->getBody(i)->getTransform().setPosition(t);
		_transforms.append(&_model->getBody(i)->getTransform());
	}

	_currentTime=0.0;
	// manually add callback to model
	_model->addIntegCallback(this);
}

//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set NULL values for member variables.
 */
void rdSimtkAnimationCallback::
setNull()
{
	setType("rdSimtkAnimationCallback");
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
const double rdSimtkAnimationCallback::
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
int rdSimtkAnimationCallback::
step(double *aXPrev,double *aYPrev,int aStep,double aDT,double aT,
	double *aX,double *aY,void *aClientData)
{
	_currentTime = aT;
	// CHECK STEP INTERVAL
	if((aStep% getStepInterval())!=0) return 0;

	// MAYA TIME
	double realTime = aT * _model->getTimeNormConstant();
	printf("time = %lf\n",realTime);

	// SET STATES Why do we need this?
	//_model->set(aT,aX,aY);

	// LOOP OVER BODIES
	int i;
	static double Orig[3] = { 0.0, 0.0, 0.0 };	// Zero 
	double t[3];	// Translation from sdfast
	double com[3];	// Center of mass
	double rot[3];	// Rotation angles 
	double dirCos[3][3];	// Direction cosines
	for(i=0;i<_model->getNB();i++) {

		// TRANSLATION AND ROTATION
		rdBody *body = _model->getBody(i);
		body->getCenterOfMass(com);
		for(int k=0; k < 3; k++)
			Orig[k] = -com[k];
		_model->getPosition(i, Orig, t);

		_model->getDirectionCosines(i,dirCos);
		_model->convertDirectionCosinesToAngles(dirCos,
			&rot[0],&rot[1],&rot[2]);
		// Initialize xform to identity
		_transforms[i]->setOrientation(rot);
		_transforms[i]->setPosition(t);
		// Create a transform change event and notify observers
		rdTransformChangeEvent	*xformChangeEvnt = new rdTransformChangeEvent(*body);
		body->setTransform(*_transforms[i]);
		body->notifyObservers(*xformChangeEvnt);
		delete xformChangeEvnt;
	}
	return (0);
}
