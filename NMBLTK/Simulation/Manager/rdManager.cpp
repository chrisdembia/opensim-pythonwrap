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
	if(_defaultControlSet!=NULL) {
		delete _defaultControlSet; _defaultControlSet=NULL;
	}
	if(_integ!=NULL) { delete _integ; _integ=NULL; }
	if(_y!=NULL) { delete []_y; _y=NULL; }
	if(_yp!=NULL) { delete []_yp; _yp=NULL; }
}


//=============================================================================
// CONSTRUCTOR(S)
//=============================================================================
//_____________________________________________________________________________
/**
 * Construct a simulation manager.
 *
 * @param aModel Model used in the simulation.
 * @param aControlSet Control set used in the simulation.
 */
rdManager::rdManager(rdModel *aModel,rdControlSet *aControlSet)
{
	setNull();

	// SET STATES
	_model = aModel;

	//INTEGRATOR
	constructIntegrator();

	// If model not set yet, exit and let setModel do the work.
	if (_model==NULL)
		return;

	// CONTROLS
	_defaultControlSet = constructControlSet();
	setControlSet(aControlSet);

	// STATES
	constructStates();

	// STORAGE
	constructStorage();

	// SESSION NAME
	setSessionName(_controlSet->getName());
}
//_____________________________________________________________________________
/**
 * Construct a simulation manager.
 *
 */
rdManager::rdManager()
{
	setNull();

	_model = NULL;

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
	_ny = 0;
	_y = NULL;
	_nyp = 0;
	_yp = NULL;
	_controlSet = NULL;
	_defaultControlSet = NULL;
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
	_ny = _model->getNY();        if(_ny>0)  _y = new double[_ny];
	_nyp = _model->getNYP();      if(_nyp>0) _yp = new double[_nyp];

	return(true);
}
//_____________________________________________________________________________
/**
 * Construct the integrator.
 */
bool rdManager::
constructIntegrator()
{

	// CONSTRUCT THE INTEGRATOR
	_integ = new rdIntegRKF(_model,1.0e-8);

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
	_integ->setControlStorage(store);

	// STATES
	int ny = _model->getNY();
	store = new rdStorage(512,"states");
	columnLabels = "time";
	for(i=0;i<ny;i++) {
		columnLabels += "\t";
		columnLabels += _model->getStateName(i);
	}
	store->setColumnLabels(columnLabels.c_str());
	_integ->setStateStorage(store);

	// PSEUDO-STATES
	int nyp = _model->getNYP();
	store = new rdStorage(512,"pseudo");
	columnLabels = "time";
	for(i=0;i<nyp;i++) {
		columnLabels += "\t";
		columnLabels += _model->getPseudoStateName(i);
	}
	store->setColumnLabels(columnLabels.c_str());
	_integ->setPseudoStateStorage(store);

	
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
	store = _integ->getControlStorage();
	if(store!=NULL) {
		name = _sessionName + "_controls";
		store->setName(name);
	}
	store = _integ->getStateStorage();
	if(store!=NULL) {
		name = _sessionName + "_states";
		store->setName(name);
	}
	store = _integ->getPseudoStateStorage();
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
// KEY MEMBER CLASSES
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the model.
 */
rdModel* rdManager::
getModel() const
{
	return(_model);
}
//_____________________________________________________________________________
/**
 * Sets the model and initializes other entities that depend on it
 * In particular, the integrator and the controlSet.
 */
void rdManager::
setModel(rdModel *model)
{
	if (_model){
		// May need to issue a warning here that model was already set to avoid a leak.
	}
	_model = model;

	//INTEGRATOR needs model, we'll construct it when model is set
	constructIntegrator();

	// CONTROLS
	_defaultControlSet = constructControlSet();

	if(_controlSet==NULL){
		setControlSet(_defaultControlSet);
	}

	// STATES
	constructStates();

	// STORAGE
	constructStorage();

	// SESSION NAME
	setSessionName(_controlSet->getName());
}
//-----------------------------------------------------------------------------
// CONTROLS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set a control set for use during a dynamic simulation.
 * Note that the simulation manager does not delete the control set; the
 * caller is responsible for the memory management of the control set
 * object.  For this reason, a pointer to the previous user-specified
 * control set is returned so that the caller can delete the previous
 * user-specified control set if appropriate.
 *
 * @param aControlSet New control set for the simulation.
 * @return Previous user-specified control set; NULL is there was
 * no user-specified control set.
 */
rdControlSet* rdManager::
setControlSet(rdControlSet *aControlSet)
{
	// PREV
	rdControlSet *prev = _controlSet;

	// SET
	if(aControlSet==NULL) {
		_controlSet = _defaultControlSet;
	} else {
		_controlSet = aControlSet;
	}

	// CHECK FOR THE CORRECT NUMBER OF CONTROLS
	int nx = _model->getNX();
	int n = _controlSet->getSize();
	if(n!=nx) {
		printf("rdManager.constructControls: ERROR- incompatible number ");
		printf("of controls: model=%d file=%d!\n",nx,n);
		printf("Using default controls...\n");
		_controlSet = _defaultControlSet;
	}

	if(prev==_defaultControlSet) return(NULL);
	return(prev);
}
//_____________________________________________________________________________
/**
 * Get the control set.
 *
 * @return Current control set.  NULL is returned if a user-specified
 * control set is not currently set.
 */
rdControlSet* rdManager::
getControlSet() const
{
	if(_controlSet==_defaultControlSet) return(NULL);
	return(_controlSet);
}
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
	_model->getInitialStates(_y);
	_model->getInitialPseudoStates(_yp);
	_model->setPseudoStates(_yp);
	return(true);
}
//_____________________________________________________________________________
/**
 * Initialize the states for integration.  This version sets the states
 * to the specified states and pseudostates.
 *
 * @param aY Specified states.
 * @param aYP Specified pseudostates.
 * @return true when successful, false otherwise.
 */
bool rdManager::
initializeStates(double *aY,double *aYP)
{
	if(aY==NULL) return(false);
	for(int i=0;i<_ny;i++) _y[i] = aY[i];
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
	rdStorage *controlStorage = _integ->getControlStorage();
	rdStorage *stateStorage = _integ->getStateStorage();
	rdStorage *pseudoStorage = _integ->getPseudoStateStorage();

	// RESET STORAGE
	if(controlStorage!=NULL) controlStorage->reset();
	if(stateStorage!=NULL) stateStorage->reset();
	if(pseudoStorage!=NULL) pseudoStorage->reset();

	// INITIALIZE STATES
	initializeStates();

	// INTEGRATE
	bool submitted = _integ->integrate(_ti,_tf,*_controlSet,_y,_firstDT);
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
	rdStorage *controlStorage = _integ->getControlStorage();
	rdStorage *stateStorage = _integ->getStateStorage();
	rdStorage *pseudoStorage = _integ->getPseudoStateStorage();

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
	bool submitted = _integ->integrate(t,_tf,*_controlSet,_y,_firstDT);
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
	rdStorage *controlStorage = _integ->getControlStorage();
	rdStorage *stateStorage = _integ->getStateStorage();
	rdStorage *pseudoStorage = _integ->getPseudoStateStorage();

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
	bool submitted = _integ->integrate(t,_tf,*_controlSet,_y,dt);

	return(submitted);
}


//=============================================================================
// UTILITY
//=============================================================================
//_____________________________________________________________________________
/**
 * Construct a control set for the model.  All the controls in the set
 * are constructed as rdControlLinear controls.
 */
rdControlSet* rdManager::
constructControlSet()
{
	int nx = _model->getNX();
	rdControlSet *controlSet = new rdControlSet();
	controlSet->setName(_model->getName());

	rdArrayPtrs<rdControlLinearNode> array;
	array.append( new rdControlLinearNode(0.0,0.0,0.0,1.0));

	for(int i=0;i<nx;i++) {
		rdControlLinear *control = new rdControlLinear(&array,_model->getControlName(i));
		controlSet->append(control);
	}

	return(controlSet);
}
