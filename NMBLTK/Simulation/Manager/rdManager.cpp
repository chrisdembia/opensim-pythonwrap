// rdManager.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2000 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "rdManager.h"
#include <NMBLTK/Simulation/Control/rdControlConstant.h>
#include <NMBLTK/Simulation/Control/rdControlLinear.h>
#include <NMBLTK/Simulation/Model/rdModelIntegrand.h>


using namespace std;

//=============================================================================
// STATICS
//=============================================================================
std::string rdManager::_displayName = "Simulator";
//=============================================================================
// DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
rdManager::~rdManager()
{
	// DESTRUCTORS
	if(_integ!=NULL) { delete _integ; _integ=NULL; }
}


//=============================================================================
// CONSTRUCTOR(S)
//=============================================================================
//_____________________________________________________________________________
/**
 * Construct a simulation manager.
 *
 * @param aIntegrand Integrand for the simulation.
 */
rdManager::rdManager(rdModelIntegrand *aIntegrand) :
	_y(0.0),
	_yp(0.0)
{
	setNull();

	// INTEGRAND AND MODEL
	_integrand = aIntegrand;
	_model = _integrand->getModel();

	//INTEGRATOR
	constructIntegrator();

	// If model not set yet, exit and let setModel do the work.
	if (_model==NULL)
		return;

	// STATES
	constructStates();

	// STORAGE
	constructStorage();

	// SESSION NAME
	setSessionName(_model->getName());
}
//_____________________________________________________________________________
/**
 * Construct a simulation manager.
 *
 */
rdManager::rdManager() :
	_y(0.0),
	_yp(0.0)
{
	setNull();
}

//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Set all member variables to their NULL values.
 */
void rdManager::
setNull()
{
	_sessionName = "";
	_model = NULL;
	_integrand = NULL;
	_integ = NULL;
	_ti = 0.0;
	_tf = 1.0;
	_firstDT = 1.0e-8;
}
//_____________________________________________________________________________
/**
 * Construct the states.
 */
bool rdManager::
constructStates()
{
	_y.setSize(_integrand->getSize());
	_yp.setSize(_model->getNYP());
	return(true);
}
//_____________________________________________________________________________
/**
 * Construct the integrator.
 */
bool rdManager::
constructIntegrator()
{
	_integ = new rdIntegRKF(_integrand,1.0e-8);

	return(true);
}
//_____________________________________________________________________________
/**
 * Construct the storage utility.
 */
bool rdManager::
constructStorage()
{
	rdStorage *store;
	string columnLabels;

	// CONTROLS
	int i;
	int nx = _model->getNX();
	store = new rdStorage(512,"controls");
	columnLabels = "time";
	for(i=0;i<nx;i++) {
		columnLabels += "\t";
		columnLabels += _model->getControlName(i);
	}
	store->setColumnLabels(columnLabels.c_str());
	_integrand->setControlStorage(store);

	// STATES
	int ny = _model->getNY();
	store = new rdStorage(512,"states");
	columnLabels = "time";
	for(i=0;i<ny;i++) {
		columnLabels += "\t";
		columnLabels += _model->getStateName(i);
	}
	store->setColumnLabels(columnLabels.c_str());
	_integrand->setStateStorage(store);

	// PSEUDO-STATES
	int nyp = _model->getNYP();
	store = new rdStorage(512,"pseudo");
	columnLabels = "time";
	for(i=0;i<nyp;i++) {
		columnLabels += "\t";
		columnLabels += _model->getPseudoStateName(i);
	}
	store->setColumnLabels(columnLabels.c_str());
	_integrand->setPseudoStateStorage(store);

	return(true);
}


//=============================================================================
// GET AND SET
//=============================================================================
//-----------------------------------------------------------------------------
// NAME
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the session name of this rdManager instance.
 */
void rdManager::
setSessionName(const string &aSessionName)
{
	_sessionName = aSessionName;
	if(_integ==NULL) return;

	// STORAGE NAMES
	string name;
	rdStorage *store;
	store = _integrand->getControlStorage();
	if(store!=NULL) {
		name = _sessionName + "_controls";
		store->setName(name);
	}
	store = _integrand->getStateStorage();
	if(store!=NULL) {
		name = _sessionName + "_states";
		store->setName(name);
	}
	store = _integrand->getPseudoStateStorage();
	if(store!=NULL) {
		name = _sessionName + "_pseudo";
		store->setName(name);
	}
}
//_____________________________________________________________________________
/**
 * Get the session name of this rdManager instance.
 */
const string& rdManager::
getSessionName() const
{
	return(_sessionName);
}

//_____________________________________________________________________________
/**
 * Get name to be shown for this object in Simtk-model tree

 */
const std::string& rdManager::
toString() const
{
	return(_displayName);
}

//-----------------------------------------------------------------------------
// INTEGRAND
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Sets the model integrand and initializes other entities that depend on it
 */
void rdManager::
setIntegrand(rdModelIntegrand *aIntegrand)
{
	if(_integrand!=NULL){
		// May need to issue a warning here that model was already set to avoid a leak.
	}
	_integrand = aIntegrand;
	_model = _integrand->getModel();

	//INTEGRATOR needs model, we'll construct it when model is set
	constructIntegrator();

	// STATES
	constructStates();

	// STORAGE
	constructStorage();

	// SESSION NAME
	setSessionName(_model->getName());
}
//_____________________________________________________________________________
/**
 * Get the integrand.
 */
rdModelIntegrand* rdManager::
getIntegrand() const
{
	return(_integrand);
}

//-----------------------------------------------------------------------------
// INTEGRATOR
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the integrator.
 */
rdIntegRKF* rdManager::
getIntegrator() const
{
	return(_integ);
}

//-----------------------------------------------------------------------------
// INTIAL AND FINAL TIME
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the initial time of the simulation.
 *
 * @param aTI Initial time.
 */
void rdManager::
setInitialTime(double aTI)
{
	_ti = aTI;
}
//_____________________________________________________________________________
/**
 * Get the initial time of the simulation.
 *
 * @return Initial time.
 */
double rdManager::
getInitialTime() const
{
	return(_ti);
}
//_____________________________________________________________________________
/**
 * Set the final time of the simulation.
 *
 * @param aTF Final time.
 */
void rdManager::
setFinalTime(double aTF)
{
	_tf = aTF;
}
//_____________________________________________________________________________
/**
 * Get the final time of the simulation.
 *
 * @return Final time.
 */
double rdManager::
getFinalTime() const
{
	return(_tf);
}

//-----------------------------------------------------------------------------
// FIRST DT
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the first time step taken in an integration.
 *
 * @param aDT First integration time step.
 */
void rdManager::
setFirstDT(double aDT)
{
	_firstDT = aDT;
	if(_firstDT<1.0e-8) _firstDT = 1.0e-8;
}
//_____________________________________________________________________________
/**
 * Get the first time step taken in an integration.
 *
 * @return First integration time step.
 */
double rdManager::
getFirstDT() const
{
	return(_firstDT);
}


//=============================================================================
// EXECUTION
//=============================================================================
//-----------------------------------------------------------------------------
// STATE INITIALIZATION
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Initialize the states for integration.  This version sets the states
 * and pseudostates to the initial states and pseudostates of the model.
 */
bool rdManager::
initializeStates()
{
	_integrand->getInitialStates(&_y[0]);
	_model->getInitialPseudoStates(&_yp[0]);
	_model->setPseudoStates(&_yp[0]);
	return(true);
}
//_____________________________________________________________________________
/**
 * Initialize the states for integration.  This version sets the states
 * to the specified states and pseudostates.
 *
 * @param aY Specified integrated states.
 * @param aYP Specified model pseudostates.
 * @return true when successful, false otherwise.
 */
bool rdManager::
initializeStates(double *aY,double *aYP)
{
	if(aY==NULL) return(false);

	int size = _integrand->getSize();
	for(int i=0;i<size;i++) _y[i] = aY[i];
	if(aYP!=NULL) _model->setPseudoStates(aYP);
	return(true);
}

//-----------------------------------------------------------------------------
// INTEGRATION
//-----------------------------------------------------------------------------
///____________________________________________________________________________
/**
 * Integrate the equations of motion for the specified model.
 *
 * This method starts the integration at the initial default states of
 * the model.
 */
bool rdManager::
integrate()
{
	// NOTE- The safe thing to do would be to send
	// a copy of the controls and the states to the
	// integrator.
	// If we want to allow for concurrently changing
	// the controls while an integration is in progress,
	// copies should not be made of _controlSet.
	// The storage class should also have a flag which
	// makes it thread safe- which allows access but not
	// modification while it is being written to.  The
	// integrator should set that flag when it is writing
	// to the storage class.
	// copy(_controlSet)
	// copy(_y)

	// GET STORAGE
	rdStorage *controlStorage = _integrand->getControlStorage();
	rdStorage *stateStorage = _integrand->getStateStorage();
	rdStorage *pseudoStorage = _integrand->getPseudoStateStorage();

	// RESET STORAGE
	if(controlStorage!=NULL) controlStorage->reset();
	if(stateStorage!=NULL) stateStorage->reset();
	if(pseudoStorage!=NULL) pseudoStorage->reset();

	// INITIALIZE STATES
	initializeStates();

	// INTEGRATE
	bool submitted = _integ->integrate(_ti,_tf,&_y[0],_firstDT);
	return(submitted);
}
//_____________________________________________________________________________
/**
 * Integrate the equations of motion for the specified model starting at the
 * states which are stored at the specified index.
 *
 * The starting states are obtained from storage.  If there are no states
 * in storage, the integration begins from the default initial states of the
 * model.  Otherwise, the integration starts from the closest posible index.
 */
bool rdManager::
integrate(int aIndex)
{
	// GET STORAGE
	rdStorage *controlStorage = _integrand->getControlStorage();
	rdStorage *stateStorage = _integrand->getStateStorage();
	rdStorage *pseudoStorage = _integrand->getPseudoStateStorage();

	// RESET CONTROLS
	if(controlStorage!=NULL){
		controlStorage->reset(aIndex);
	}

	// RESET STATES
	rdStateVector *states,*pseudo;
	if(stateStorage!=NULL) {
		stateStorage->reset(aIndex);
		pseudoStorage->reset(aIndex);
		states = stateStorage->getLastStateVector();
		pseudo = pseudoStorage->getLastStateVector();
	}

	// SET THE INITIAL STATES
	double t;
	if(states==NULL) {
		t = _ti;
		initializeStates();
		printf("rdManager.integrate(int):  no valid states stored.\n");
	} else {
		t = states->getTime();
		initializeStates(states->getData().get(),pseudo->getData().get());
		printf("rdManager.integrate(int):  starting at index=%d, t=%lf.\n",
		 aIndex,t);
	}

	// INTEGRATE
	bool submitted = _integ->integrate(t,_tf,&_y[0],_firstDT);
	return(submitted);
}
//_____________________________________________________________________________
/**
 * Integrate the equations of motion for the specified model starting at the
 * states which occured at or just prior to aStartTime.  aStartTime is given
 * in the normalized time units used by the manager and the integrator.
 *
 * The starting states are obtained from storage.  If there are no states
 * in storage, the integration begins from the default initial states of the
 * model.  Otherwise, the integration starts from the states which are closest
 * to aStartTime, but not after aStartTime.
 *
 * Note that it is not guarranteed that the actual start time will be very
 * close to the requested start time.  How close the requested start time is
 * to the actual start time dependes on the resolution of the stored states.
 *
 * @param aStartTime Normalized time at which to begin the integration.
 * @return true on successful integration, false otherwise.
 * @todo Check restarting integrations at the very last time step of
 * a previous integration.
 */
bool rdManager::
integrate(double aStartTime)
{
	// CONVERT TO REAL TIME
	double realTime = _model->getTimeNormConstant() * aStartTime;

	// GET STORAGE
	rdStorage *controlStorage = _integrand->getControlStorage();
	rdStorage *stateStorage = _integrand->getStateStorage();
	rdStorage *pseudoStorage = _integrand->getPseudoStateStorage();

	// RESET CONTROLS
	if(controlStorage!=NULL){
		controlStorage->reset(realTime);
	}

	// RESET STATES
	rdStateVector *states=NULL;
	if(stateStorage!=NULL) {
		stateStorage->reset(realTime);
		states = stateStorage->getLastStateVector();
	}

	// RESET PSEUDOSTATES
	rdStateVector *pseudo=NULL;
	if(pseudoStorage!=NULL) {
		pseudoStorage->reset(realTime);
		pseudo = pseudoStorage->getLastStateVector();
	}

	// SET THE INITIAL STATES
	double t,dt=1.0e-8;
	// start from beginning
	if(states==NULL) {
		t = _ti;
		initializeStates();
		printf("rdManager.integrate(double):  no valid states stored.\n");

	// start in the middle
	} else {

		// GET START TIME
		t = states->getTime() / _model->getTimeNormConstant();

		// GET TIME STEP
		int step = _integ->getTimeArrayStep(t);
		dt = _integ->getDTArrayDT(step);
		if(dt<=rdMath::NAN) dt = 1.0e-8;

		// GET DATA
		double *y=NULL,*yp=NULL;
		y = states->getData().get();
		if(pseudo!=NULL) yp = pseudo->getData().get();
		initializeStates(y,yp);

		// PRINT
		printf("rdManager.integrate(aStarTime):  ");
		printf(" (in real time)=%.15lf  (in normalized time)=%.15lf.\n",
			_model->getTimeNormConstant()*t,t);
		printf("Using an integration step size of %.16lf for first step.\n",
			dt);
	}

	// INTEGRATE
	bool submitted = _integ->integrate(t,_tf,&_y[0],dt);

	return(submitted);
}
