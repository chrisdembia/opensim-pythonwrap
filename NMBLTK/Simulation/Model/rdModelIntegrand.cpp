// rdModelIntegrand.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2005 Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <string>
#include "rdIntegCallbackSet.h"
#include "rdAnalysisSet.h"
#include "rdDerivCallbackSet.h"
#include "rdModelIntegrand.h"
#include <NMBLTK/Simulation/Control/rdControlLinear.h>
#include <NMBLTK/Simulation/Control/rdControlLinearNode.h>

using namespace std;



//=============================================================================
// CONSTRUCTORS & DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Constructs an integrad for an rdModel.
 *
 * @param aModel An instance of an rdModel.
 */
rdModelIntegrand::rdModelIntegrand(rdModel *aModel):
	_x(0.0),_xPrev(0.0),_yPrev(0.0),_yp(0.0)
{
	setNull();

	// MEMBER VARIABLES
	_model = aModel;
	rdControlSet *tmpControlSet = constructControlSet();
	_controlSet = *tmpControlSet;
	delete tmpControlSet;

	// WORK VARIABLES
	_x.setSize(_model->getNX());
	_xPrev.setSize(_model->getNX());
	_yPrev.setSize(_model->getNY());
	_yp.setSize(_model->getNYP());
}

//_____________________________________________________________________________
/**
 * Destructor.
 */
rdModelIntegrand::~rdModelIntegrand()
{
}


//=============================================================================
// CONSTRUCTION AND DESTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Set member variables to their NULL values.
 */
void rdModelIntegrand::
setNull()
{
	setType("rdModelIntegrand");
	_ti = 0.0;
	_tf = 0.0;
	_tPrev = 0.0;
	_dtPrev = 0.0;
	_model = NULL;
	_controller = NULL;
	_controlStore = NULL;
	_stateStore = NULL;
	_pseudoStore = NULL;
}



//=============================================================================
// GET & SET
//=============================================================================
//-----------------------------------------------------------------------------
// SIZE
//-----------------------------------------------------------------------------
//____________________________________________________________________________
/**
 * Get the size of the state vector (y) and time derivative of the state
 * vector (dydt).  The size is the number of integrated variables.
 *
 * @return Size of the state vector y.
 */
int rdModelIntegrand::
getSize() const
{
	return(_model->getNY());
}

//-----------------------------------------------------------------------------
// MODEL
//-----------------------------------------------------------------------------
//____________________________________________________________________________
/**
 * Get the model of this integrand.
 *
 * @return Model.
 */
rdModel* rdModelIntegrand::
getModel()
{
	return(_model);
}

//-----------------------------------------------------------------------------
// CONTROL STORAGE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the storage buffer for the integration controls.
 */
void rdModelIntegrand::
setControlStorage(rdStorage *aStorage)
{
	_controlStore = aStorage;
}
//_____________________________________________________________________________
/**
 * Get the storage buffer for the integration controls.
 */
rdStorage* rdModelIntegrand::
getControlStorage()
{
	return(_controlStore);
}

//-----------------------------------------------------------------------------
// STATE STORAGE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the storage buffer for the integration states.
 */
void rdModelIntegrand::
setStateStorage(rdStorage *aStorage)
{
	_stateStore = aStorage;
}
//_____________________________________________________________________________
/**
 * Get the storage buffer for the integration states.
 */
rdStorage* rdModelIntegrand::
getStateStorage()
{
	return(_stateStore);
}

//-----------------------------------------------------------------------------
// PSEUDOSTATE STORAGE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the storage for the pseudostates.
 */
void rdModelIntegrand::
setPseudoStateStorage(rdStorage *aStorage)
{
	_pseudoStore = aStorage;
}
//_____________________________________________________________________________
/**
 * Get the storage for the pseudostates.
 */
rdStorage* rdModelIntegrand::
getPseudoStateStorage()
{
	return(_pseudoStore);
}

//-----------------------------------------------------------------------------
// CONTROL SET
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the control set for this integrand.
 *
 * @param aControlSet Set of controls for the integrand.
 */
void rdModelIntegrand::
setControlSet(const rdControlSet &aControlSet)
{
	if(aControlSet.getSize() != _model->getNX()) {
		cout<<"rdModelIntegrand.setControlSet: incorrect number of controls.\n";
		return;
	}
	_controlSet = aControlSet;
}
//_____________________________________________________________________________
/**
 * Set the control set for this integrand.
 *
 * @return aControlSet Set of controls.
 */
rdControlSet* rdModelIntegrand::
getControlSet()
{
	return(&_controlSet);
}


//-----------------------------------------------------------------------------
// CONTROLLER
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set a controller for this integration.
 * If one is set, the controller will be called each integration step to
 * determine a set of controls for controlling the current model.
 *
 * @param aController Controller.  To remove the controller, set the
 * controller to NULL.
 */
void rdModelIntegrand::
setController(rdController *aController)
{
	_controller = aController;
}
//_____________________________________________________________________________
/**
 * Get the dynamic filter.
 *
 * @return Controller set for this model.  If no controller is set NULL is
 * returned.
 */
rdController* rdModelIntegrand::
getController()
{
	return(_controller);
}


//=============================================================================
// UTILITY
//=============================================================================
//_____________________________________________________________________________
/**
 * Construct a control set for the model.  All the controls in the set
 * are constructed as rdControlLinear controls.
 */
rdControlSet* rdModelIntegrand::
constructControlSet() const
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
//____________________________________________________________________________
/**
 * Convert an array of integrated states to an array of model states.
 * The function sets for the coordinate and speed trajectories are used to
 * fill in the values for the generalized coordinates and speeds.
 *
 * @param t Time (real time not normalized time).
 * @param y Integrated states (size = getSize()).
 * @param yModel Model states (size = getSize()+rdModel::getNQ()+rdModel getNU())
 */
void rdModelIntegrand::
convertStatesIntegrandToModel(double t,const double y[],double yModel[])
{
	int i;
	int ny = _model->getNY();
	for(i=0;i<ny;i++) yModel[i] = y[i];
}
//____________________________________________________________________________
/**
 * Convert an array of model states to an array of integrated states.
 * The function sets for the coordinate and speed trajectories are used to
 * fill in the values for the generalized coordinates and speeds.
 *
 * @param t Time (real time not normalized time).
 * @param y Integrated states (size = getSize()).
 * @param yModel Model states (size = getSize()+rdModel::getNQ()+rdModel getNU())
 */
void rdModelIntegrand::
convertStatesModelToIntegrand(const double yModel[],double y[]) const
{
	int i;
	int ny = _model->getNY();
	for(i=0;i<ny;i++) y[i] = yModel[i];
}


//=============================================================================
// INITIAL STATES
//=============================================================================
//__________________________________________________________________________
/**
  * Set the initial states for the integration.
  *
  * @param ti Time at which the initial states occur.
  * @param yi Array of initial states (size = getSize()).
  */
void rdModelIntegrand::
setInitialStates(double ti,const double yi[])
 {
	_model->setInitialStates(yi);
 }
 //__________________________________________________________________________
 /**
  * Get the initial states for the integration.
  *
  * @param yi Array of initial states (size = getSize()).
  */
void rdModelIntegrand::
getInitialStates(double yi[]) const
{
	_model->getInitialStates(yi);
}


//=============================================================================
// COMPUTATION
//=============================================================================
//____________________________________________________________________________
/**
 * Compute the state derivatives for an rdModel (dydt).
 *
 * @param t Current time.
 * @param y State vector (size = getSize()).
 * @param dydt rdModelIntegrand-- the time derivative of the
 * state vector (size = getSize()).
 */
void rdModelIntegrand::
compute(double t,double y[],double dydt[])
{

	// GET CONTROLS
	_controlSet.getControlValues(t,_x);
	
	// TIME, CONTROLS, STATES
	_model->set(t,&_x[0],y);
	_model->getDerivCallbackSet()->set(t,&_x[0],y);

	// ACTUATION
	_model->computeActuation();
	_model->getDerivCallbackSet()->computeActuation(t,&_x[0],y);
	_model->applyActuatorForces();
	_model->getDerivCallbackSet()->applyActuation(t,&_x[0],y);

	// CONTACT
	_model->computeContact();
	_model->getDerivCallbackSet()->computeContact(t,&_x[0],y);
	_model->applyContactForces();
	_model->getDerivCallbackSet()->applyContact(t,&_x[0],y);

	// DERIVATIVES
	int i;
	int ny = _model->getNY();
	int nq = _model->getNQ();
	int nu = _model->getNU();
	for(i=0;i<ny;i++) dydt[i] = 0.0;
	_model->computeAccelerations(&dydt[0],&dydt[nq]);
	int iAux = nq + nu;
	if(iAux<ny) _model->computeAuxiliaryDerivatives(&dydt[iAux]);
	_model->getDerivCallbackSet()->computeDerivatives(t,&_x[0],y,dydt);

	// NORMALIZE
	double tnorm = _model->getTimeNormConstant();
	for(i=0;i<ny;i++) dydt[i] *= tnorm;
}


//=============================================================================
// HOOKS
//=============================================================================
//____________________________________________________________________________
/**
 * Initialize the rdModelIntegrand at the beginning of an integration.
 *
 * @param step Integration step.
 * @param dt First step size; it can be changed.
 * @param ti Initial time of the integration.
 * @param tf Final time of the simulation.
 * @param y Initial values of the states.
 */
void rdModelIntegrand::
initialize(int step,double &dt,double ti,double tf,double y[])
{
	// VARIABLES
	_ti = ti;
	_tf = tf;
	_tPrev = _ti;
	double tReal = _ti * _model->getTimeNormConstant();
	int nx = _model->getNX();
	int ny = _model->getNY();
	int nyp = _model->getNYP();

		// SET
	_model->setTime(_ti);
	_model->setStates(y);

	// INITIAL CONTROLS
	if(_controller!=NULL) {
		_controller->computeControls(dt,_ti,y,_controlSet);
	}
	_controlSet.getControlValues(_ti,_x);
	_model->setControls(&_x[0]);

	// INITIALIZE PREVIOUS CONTROL AND STATE VALUES
	memcpy(&_xPrev[0],&_x[0],nx*sizeof(double));
	memcpy(&_yPrev[0],y,ny*sizeof(double));

	// STORE STARTING CONTROLS
	if(_controlStore!=NULL) {
		// ONLY IF NO CONTROLS WERE PREVIOUSLY STORED
		if(_controlStore->getLastStateVector()==NULL) {
			_controlStore->store(step,tReal,nx,&_x[0]);
		}
	}

	// STORE STARTING STATES
	if(_stateStore!=NULL) {
		// ONLY IF NO STATES WERE PREVIOUSLY STORED
		if(_stateStore->getLastStateVector()==NULL) {
			_stateStore->store(step,tReal,ny,y);
		}
	}

	// STORE STARTING PSEUDOSTATES
	if(_pseudoStore!=NULL) {
		// ONLY IF NO STATES WERE PREVIOUSLY STORED
		if(_pseudoStore->getLastStateVector()==NULL) {
			_model->getPseudoStates(&_yp[0]);
			_pseudoStore->store(step,tReal,nyp,&_yp[0]);
		}
	}

	// ANALYSES & INTEGRATION CALLBACKS
	rdIntegCallbackSet *callbackSet = _model->getIntegCallbackSet();
	rdAnalysisSet *analysisSet = _model->getAnalysisSet();
	if(callbackSet!=NULL) callbackSet->begin(step,dt,_ti,&_x[0],y);
	if(analysisSet!=NULL) analysisSet->begin(step,dt,_ti,&_x[0],y);
}
//____________________________________________________________________________
/**
 * Perform any desired operations after the last successful integration step.
 *
 * @param step Step number.
 * @param dt Time delta for the next integration step; it can be changed.
 * @param t Current time of the integration.
 * @param y Current values of the states.
 */
void rdModelIntegrand::
processAfterStep(int step,double &dt,double t,double y[])
{
	_dtPrev = t - _tPrev;
	double tReal = t * _model->getTimeNormConstant();

	// GET THE CONTROLS AT THE NEW TIME t
	if(_controller!=NULL) {
		_controller->computeControls(dt,t,y,_controlSet);
	}
	_controlSet.getControlValues(t,_x);

	// STORE CONTROLS
	int nx = _x.getSize();
	if(_controlStore!=NULL) {
		if(t<_tf) {
			_controlStore->store(step,tReal,nx,&_x[0]);
		} else {
			_controlStore->append(tReal,nx,&_x[0]);
		}
	}

	// STORE STATES
	int ny = _model->getNY();
	if(_stateStore!=NULL) {
		if(t<_tf) {
			_stateStore->store(step,tReal,ny,y);
		} else {
			_stateStore->append(tReal,ny,y);
		}
	}

	// INTEGRATION CALLBACKS
	rdIntegCallbackSet *callbackSet = _model->getIntegCallbackSet();
	if(callbackSet!=NULL)
		callbackSet->step(&_xPrev[0],&_yPrev[0],step,_dtPrev,t,&_x[0],y);

	// ANALYSES
	rdAnalysisSet *analysisSet = _model->getAnalysisSet();
	if(analysisSet!=NULL)
		analysisSet->step(&_xPrev[0],&_yPrev[0],step,_dtPrev,t,&_x[0],y);

	// STORE PSEUDOSTATES
	int nyp = _model->getNYP();
	if(_pseudoStore!=NULL) {
		_model->getPseudoStates(&_yp[0]);
		if(t<_tf) {
			_pseudoStore->store(step,tReal,nyp,&_yp[0]);
		} else {
			_pseudoStore->append(tReal,nyp,&_yp[0]);
		}
	}

	// UPDATE PREVIOUS CONTROL AND STATE VALUES
	memcpy(&_xPrev[0],&_x[0],nx*sizeof(double));
	memcpy(&_yPrev[0],&y[0],ny*sizeof(double));

	// UPDATE PREVIOUS TIME
	_tPrev = t;
}
//____________________________________________________________________________
/**
 * Finalize the rdModelIntegrand after an integration has completed (e.g., clean up).
 *
 * @param step Step number.
 * @param t Time at which the integration completed.
 * @param y Current values of the states.
 */
void rdModelIntegrand::
finalize(int step,double t,double y[])
{
	rdIntegCallbackSet *callbackSet = _model->getIntegCallbackSet();
	if(callbackSet!=NULL) callbackSet->end(step,_dtPrev,t,&_x[0],y);

	rdAnalysisSet *analysisSet = _model->getAnalysisSet();
	if(analysisSet!=NULL) analysisSet->end(step,_dtPrev,t,&_x[0],y);
}
