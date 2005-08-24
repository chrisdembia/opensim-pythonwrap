// rdModelIntegrandForActuators.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2005 Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <string>
#include <NMBLTK/Tools/rdArray.h>
#include "rdIntegCallbackSet.h"
#include "rdAnalysisSet.h"
#include "rdDerivCallbackSet.h"
#include "rdModelIntegrandForActuators.h"

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
rdModelIntegrandForActuators::
rdModelIntegrandForActuators(rdModel *aModel) :
	rdModelIntegrand(aModel),
	_qWork(0.0),
	_uWork(0.0),
	_yModel(0.0),
	_qCorrections(0.0),
	_uCorrections(0.0)
{
	setNull();
}

//_____________________________________________________________________________
/**
 * Destructor.
 */
rdModelIntegrandForActuators::~rdModelIntegrandForActuators()
{
}


//=============================================================================
// CONSTRUCTION AND DESTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Set member variables to their NULL values.
 */
void rdModelIntegrandForActuators::
setNull()
{
	setType("rdModelIntegrandForActuators");
	_qSet = NULL;
	_uSet = NULL;
	_holdCoordinatesConstant = false;
	_holdTime = 0.0;
	_qCorrections.setSize(_model->getNQ());
	_uCorrections.setSize(_model->getNU());
	_qWork.setSize(_model->getNQ());
	_uWork.setSize(_model->getNU());
	_yModel.setSize(_model->getNY());
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
int rdModelIntegrandForActuators::
getSize() const
{
	int size = _model->getNY() - _model->getNQ() - _model->getNU();
	return(size);
}

//-----------------------------------------------------------------------------
// COORDINATE TRAJECTORIES
//-----------------------------------------------------------------------------
//____________________________________________________________________________
/**
 * Set the function set that contains the trajectories that the generalized
 * coordinates are to follow.  Time in this function set should be in real
 * time, not normalized time.  The number of trajectories should be equal
 * to the number of generalized coordinates in the model.
 *
 * @param aSet Set of trajectories for the generalized coordinates.
 * @thro rdException on error.
 */
void rdModelIntegrandForActuators::
setCoordinateTrajectories(rdFunctionSet *aSet)
{
	// ERROR CHECKING
	if(aSet == NULL) {
		string msg = "rdModelIntegrandForActuators.setCoordinateTrajectories:";
		msg += " ERR- NULL function set.\n";
		throw( rdException(msg,__FILE__,__LINE__) );
	}
	if(aSet->getSize() != _model->getNQ()) {
		string msg = "rdModelIntegrandForActuators.setCoordinateTrajectories:";
		msg += " ERR- incorrect number of trajectories.\n";
		throw( rdException(msg,__FILE__,__LINE__) );
	}

	_qSet = aSet;
}
//____________________________________________________________________________
/**
 * Get the function set that contains the trajectories that the generalized
 * coordinates are to follow.
 *
 * @return Set of trajectories for the generalized coordinates.
 */
rdFunctionSet* rdModelIntegrandForActuators::
getCoordinateTrajectories()
{
	return(_qSet);
}

//-----------------------------------------------------------------------------
// SPEED TRAJECTORIES
//-----------------------------------------------------------------------------
//____________________________________________________________________________
/**
 * Set the function set that contains the trajectories that the generalized
 * speeds are to follow.  Time in this function set should be in real
 * time, not normalized time.  The number of trajectories should be equal
 * to the number of generalized coordinates in the model.
 *
 * @param aSet Set of trajectories for the generalized speeds.
 * @thro rdException on error.
 */
void rdModelIntegrandForActuators::
setSpeedTrajectories(rdFunctionSet *aSet)
{
	// ERROR CHECKING
	if(aSet == NULL) {
		string msg = "rdModelIntegrandForActuators.setSpeedTrajectories:";
		msg += " ERR- NULL function set.\n";
		throw( rdException(msg,__FILE__,__LINE__) );
	}
	if(aSet->getSize() != _model->getNU()) {
		string msg = "rdModelIntegrandForActuators.setSpeedTrajectories:";
		msg += " ERR- incorrect number of trajectories.\n";
		throw( rdException(msg,__FILE__,__LINE__) );
	}

	_uSet = aSet;
}
//____________________________________________________________________________
/**
 * Get the function set that contains the trajectories that the generalized
 * speeds are to follow.
 *
 * @return Set of trajectories for the generalized speeds.
 */
rdFunctionSet* rdModelIntegrandForActuators::
getSpeedTrajectories()
{
	return(_uSet);
}

//-----------------------------------------------------------------------------
// COORDINATE CORRECTIONS
//-----------------------------------------------------------------------------
//____________________________________________________________________________
/**
 * Specify an array of corrections for the generalized speeds.
 *
 * @param aCorrections Array of constant corrections.
 */
void rdModelIntegrandForActuators::
setCoordinateCorrections(const double aCorrections[])
{
	int i;
	int size = _qCorrections.getSize();
	for(i=0;i<size;i++) {
		_qCorrections[i] = aCorrections[i];
	}
}
//____________________________________________________________________________
/**
 * Get the array of corrections for the generalized speeds.
 *
 * @param rCorrections Array of constant corrections.
 */
void rdModelIntegrandForActuators::
getCoordinateCorrections(double rCorrections[]) const
{
	int i;
	int size = _qCorrections.getSize();
	for(i=0;i<size;i++) {
		rCorrections[i] = _qCorrections[i];
	}
}

//-----------------------------------------------------------------------------
// SPEED CORRECTIONS
//-----------------------------------------------------------------------------
//____________________________________________________________________________
/**
 * Specify an array of corrections for the generalized speeds.
 *
 * @param aCorrections Array of constant corrections.
 */
void rdModelIntegrandForActuators::
setSpeedCorrections(const double aCorrections[])
{
	int i;
	int size = _uCorrections.getSize();
	for(i=0;i<size;i++) {
		_uCorrections[i] = aCorrections[i];
	}
}
//____________________________________________________________________________
/**
 * Get the array of corrections for the generalized speeds.
 *
 * @param rCorrections Array of constant corrections.
 */
void rdModelIntegrandForActuators::
getSpeedCorrections(double rCorrections[]) const
{
	int i;
	int size = _uCorrections.getSize();
	for(i=0;i<size;i++) {
		rCorrections[i] = _uCorrections[i];
	}
}


//=============================================================================
// MODEL STATES
//=============================================================================
//____________________________________________________________________________
/**
 * Hold the generalized coordinates and speeds constant.
 *
 * @param t Time (real time, not normalized time) at which to hold the
 * coordinates and speeds constant.
 */
void rdModelIntegrandForActuators::
holdCoordinatesConstant(double t)
{
	_holdCoordinatesConstant = true;
	_holdTime = t;
}
//____________________________________________________________________________
/**
 * Release the generalized coordinates and speeds.
 */
void rdModelIntegrandForActuators::
releaseCoordinates()
{
	_holdCoordinatesConstant = false;
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
void rdModelIntegrandForActuators::
convertStatesIntegrandToModel(double t,const double y[],double yModel[])
{
	int i;
	int nq = _model->getNQ();
	int nu = _model->getNU();
	int ny = _model->getNY();
	int nqnu = nq + nu;
	int size = getSize();

	if(_holdCoordinatesConstant) t = _holdTime;

	 _qSet->evaluate(_qWork,0,t);
	 _uSet->evaluate(_uWork,0,t);

	for(i=0;i<nq;i++) yModel[i] = _qWork[i] + _qCorrections[i];
	for(i=0;i<nu;i++) yModel[i+nq] = _uWork[i] + _uCorrections[i];
	for(i=0;i<size;i++) yModel[i+nqnu] = y[i];
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
void rdModelIntegrandForActuators::
convertStatesModelToIntegrand(const double yModel[],double y[]) const
{
	int i;
	int nq = _model->getNQ();
	int nu = _model->getNU();
	int nqnu = nq + nu;
	int size = getSize();
	for(i=0;i<size;i++) y[i] = yModel[i+nqnu];
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
void rdModelIntegrandForActuators::
setInitialStates(double ti,const double yi[])
 {
	double tnorm = _model->getTimeNormConstant();
	double treal = tnorm * ti;
	convertStatesIntegrandToModel(treal,yi,&_yModel[0]);

	_model->setInitialStates(&_yModel[0]);
 }
 //__________________________________________________________________________
 /**
  * Get the initial states for the integration.
  *
  * @param yi Array of initial states (size = getSize()).
  */
void rdModelIntegrandForActuators::
getInitialStates(double yi[]) const
{
	_model->getInitialStates(&_yModel[0]);
	convertStatesModelToIntegrand(&_yModel[0],yi);
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
 * @param dydt rdModelIntegrandForActuators-- the time derivative of the
 * state vector (size = getSize()).
 */
void rdModelIntegrandForActuators::
compute(double t,double y[],double dydt[])
{
	// CONVERT
	double tnorm = _model->getTimeNormConstant();
	double treal = tnorm * t;
	convertStatesIntegrandToModel(treal,y,&_yModel[0]);

   // ----------------------------------
	// GET CONTROLS
	_controlSet.getControlValues(t,_x);
	
	// TIME, CONTROLS, STATES
	_model->set(t,&_x[0],&_yModel[0]);
	_model->getDerivCallbackSet()->set(t,&_x[0],&_yModel[0]);

	// ACTUATION
	_model->computeActuation();
	_model->getDerivCallbackSet()->computeActuation(t,&_x[0],&_yModel[0]);
	_model->applyActuatorForces();
	_model->getDerivCallbackSet()->applyActuation(t,&_x[0],&_yModel[0]);

	// CONTACT
	_model->computeContact();
	_model->getDerivCallbackSet()->computeContact(t,&_x[0],&_yModel[0]);
	_model->applyContactForces();
	_model->getDerivCallbackSet()->applyContact(t,&_x[0],&_yModel[0]);

	// DERIVATIVES
	int i;
	int size = getSize();
	if(size>0) {
		for(i=0;i<size;i++) dydt[i] = 0.0;
		_model->computeAuxiliaryDerivatives(dydt);
		_model->getDerivCallbackSet()->computeDerivatives(t,&_x[0],&_yModel[0],dydt);

		// NORMALIZE
		for(i=0;i<size;i++) dydt[i] *= tnorm;
	}
   //-----------------------------------
}


//=============================================================================
// HOOKS
//=============================================================================
//____________________________________________________________________________
/**
 * Initialize the rdModelIntegrandForActuators at the beginning of an integration.
 *
 * @param ti Initial time of the integration.
 * @param tf Final time of the simulation.
 * @param y Initial values of the states.
 */
void rdModelIntegrandForActuators::
initialize(int step,double &dt,double ti,double tf,double y[])
{
	double tnorm = _model->getTimeNormConstant();
	double treal = tnorm * ti;
	convertStatesIntegrandToModel(treal,y,&_yModel[0]);

	rdModelIntegrand::initialize(step,dt,ti,tf,&_yModel[0]);
}
//____________________________________________________________________________
/**
 * Perform any desired operations after the last successful integration step.
 *
 * @param step Step number.
 * @param dt Time delta for the next integration step.
 * @param t Current time of the integration.
 * @param y Current values of the states.
 */
void rdModelIntegrandForActuators::
processAfterStep(int step,double &dt,double t,double y[])
{
	double tnorm = _model->getTimeNormConstant();
	double treal = tnorm * t;
	convertStatesIntegrandToModel(treal,y,&_yModel[0]);

	rdModelIntegrand::processAfterStep(step,dt,t,&_yModel[0]);
}
//____________________________________________________________________________
/**
 * Finalize the rdModelIntegrandForActuators after an integration has completed (e.g., clean up).
 *
 * @param step Step number.
 * @param t Time at which the integration completed.
 * @param y Current values of the states.
 */
void rdModelIntegrandForActuators::
finalize(int step,double t,double y[])
{
	double tnorm = _model->getTimeNormConstant();
	double treal = tnorm * t;
	convertStatesIntegrandToModel(treal,y,&_yModel[0]);

	rdModelIntegrand::finalize(step,t,&_yModel[0]);
}
