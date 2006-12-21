// ModelIntegrandForActuators.cpp
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
 * Author: Frank C. Anderson 
 */

#include <string>
#include <OpenSim/Tools/Array.h>
#include "IntegCallbackSet.h"
#include "AnalysisSet.h"
#include "DerivCallbackSet.h"
#include "ModelIntegrandForActuators.h"
#include <OpenSim/Simulation/SIMM/AbstractModel.h>
#include <OpenSim/Simulation/SIMM/AbstractDynamicsEngine.h>


using namespace OpenSim;
using namespace std;



//=============================================================================
// CONSTRUCTORS & DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Constructs an integrad for an Model.
 *
 * @param aModel An instance of an Model.
 */
ModelIntegrandForActuators::
ModelIntegrandForActuators(AbstractModel *aModel) :
	ModelIntegrand(aModel),
	_qCorrections(0.0),
	_uCorrections(0.0),
	_qWork(0.0),
	_uWork(0.0),
	_yModel(0.0)
{
	setNull();
}

//_____________________________________________________________________________
/**
 * Destructor.
 */
ModelIntegrandForActuators::~ModelIntegrandForActuators()
{
}


//=============================================================================
// CONSTRUCTION AND DESTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Set member variables to their NULL values.
 */
void ModelIntegrandForActuators::
setNull()
{
	setType("ModelIntegrandForActuators");
	_qSet = NULL;
	_uSet = NULL;
	_holdCoordinatesConstant = false;
	_holdTime = 0.0;
	_qCorrections.setSize(_model->getNumCoordinates());
	_uCorrections.setSize(_model->getNumSpeeds());
	_qWork.setSize(_model->getNumCoordinates());
	_uWork.setSize(_model->getNumSpeeds());
	_yModel.setSize(_model->getNumStates());
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
int ModelIntegrandForActuators::
getSize() const
{
	int size = _model->getNumStates() - _model->getNumCoordinates() - _model->getNumSpeeds();
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
 * @thro Exception on error.
 */
void ModelIntegrandForActuators::
setCoordinateTrajectories(FunctionSet *aSet)
{
	// ERROR CHECKING
	if(aSet == NULL) {
		string msg = "ModelIntegrandForActuators.setCoordinateTrajectories:";
		msg += " ERR- NULL function set.\n";
		throw( Exception(msg,__FILE__,__LINE__) );
	}
	if(aSet->getSize() != _model->getNumCoordinates()) {
		string msg = "ModelIntegrandForActuators.setCoordinateTrajectories:";
		msg += " ERR- incorrect number of trajectories.\n";
		throw( Exception(msg,__FILE__,__LINE__) );
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
FunctionSet* ModelIntegrandForActuators::
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
 * @thro Exception on error.
 */
void ModelIntegrandForActuators::
setSpeedTrajectories(FunctionSet *aSet)
{
	// ERROR CHECKING
	if(aSet == NULL) {
		string msg = "ModelIntegrandForActuators.setSpeedTrajectories:";
		msg += " ERR- NULL function set.\n";
		throw( Exception(msg,__FILE__,__LINE__) );
	}
	if(aSet->getSize() != _model->getNumSpeeds()) {
		string msg = "ModelIntegrandForActuators.setSpeedTrajectories:";
		msg += " ERR- incorrect number of trajectories.\n";
		throw( Exception(msg,__FILE__,__LINE__) );
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
FunctionSet* ModelIntegrandForActuators::
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
void ModelIntegrandForActuators::
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
void ModelIntegrandForActuators::
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
void ModelIntegrandForActuators::
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
void ModelIntegrandForActuators::
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
void ModelIntegrandForActuators::
holdCoordinatesConstant(double t)
{
	_holdCoordinatesConstant = true;
	_holdTime = t;
}
//____________________________________________________________________________
/**
 * Release the generalized coordinates and speeds.
 */
void ModelIntegrandForActuators::
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
 * @param yModel Model states (size = getSize()+Model::getNumCoordinates()+Model::getNumSpeeds())
 */
void ModelIntegrandForActuators::
convertStatesIntegrandToModel(double t,const double y[],double yModel[])
{
	// ERROR CHECK
	if(_qSet==NULL) {
		cout<<"ERROR- The desired generalized coordinate values have not been set.\n";
		return;
	}

	int i;
	int nq = _model->getNumCoordinates();
	int nu = _model->getNumSpeeds();
	int nqnu = nq + nu;
	int size = getSize();

	if(_holdCoordinatesConstant) t = _holdTime;

	_qSet->evaluate(_qWork,0,t);
	if(_uSet!=NULL) {
		_uSet->evaluate(_uWork,0,t);
	} else {
		_qSet->evaluate(_uWork,1,t);
	}

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
 * @param yModel Model states (size = getSize()+Model::getNumCoordinates()+Model::getNumSpeeds())
 */
void ModelIntegrandForActuators::
convertStatesModelToIntegrand(const double yModel[],double y[]) const
{
	int i;
	int nq = _model->getNumCoordinates();
	int nu = _model->getNumSpeeds();
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
void ModelIntegrandForActuators::
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
void ModelIntegrandForActuators::
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
 * Compute the state derivatives for an Model (dydt).
 *
 * @param t Current time.
 * @param y State vector (size = getSize()).
 * @param dydt ModelIntegrandForActuators-- the time derivative of the
 * state vector (size = getSize()).
 */
void ModelIntegrandForActuators::
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
	_model->getActuatorSet()->computeActuation();
	_model->getDerivCallbackSet()->computeActuation(t,&_x[0],&_yModel[0]);
	_model->getActuatorSet()->apply();
	_model->getDerivCallbackSet()->applyActuation(t,&_x[0],&_yModel[0]);

	// CONTACT
	_model->getContactSet()->computeContact();
	_model->getDerivCallbackSet()->computeContact(t,&_x[0],&_yModel[0]);
	_model->getContactSet()->apply();
	_model->getDerivCallbackSet()->applyContact(t,&_x[0],&_yModel[0]);

	// DERIVATIVES
	int size = getSize();
	if(size>0) {
		_model->computeAuxiliaryDerivatives(dydt);

		if(_model->getDerivCallbackSet()->getSize()) {
			// Used to just call 
			// _model->getDerivCallbackSet()->computeDerivatives(t,&_x[0],&_yModel[0],dydt);
			// but that seems wrong (since dydt is a shorter vector than the full state vector, and
			// there is no way for the DerivCallback to know that), so instead we convert dydt to
			// the full derivative vector before passing it to the callback.  I think this
			// is right, but can't test it because we don't actually have any DerivCallbacks
			// that implement computeDerivatives.
			int realNY = _model->getNumStates();
			double *fulldydt = new double[realNY];
			int baseIndex = realNY - size;
			for(int i=0;i<baseIndex;i++) fulldydt[i]=0.0;
			for(int i=0;i<size;i++) fulldydt[baseIndex+i]=dydt[i];
			_model->getDerivCallbackSet()->computeDerivatives(t,&_x[0],&_yModel[0],fulldydt);
			for(int i=0;i<size;i++) dydt[i] = fulldydt[baseIndex+i];
			delete[] fulldydt;
		}

		// NORMALIZE
		for(int i=0;i<size;i++) dydt[i] *= tnorm;
	}
   //-----------------------------------
}


//=============================================================================
// HOOKS
//=============================================================================
//____________________________________________________________________________
/**
 * Initialize the ModelIntegrandForActuators at the beginning of an integration.
 *
 * @param ti Initial time of the integration.
 * @param tf Final time of the simulation.
 * @param y Initial values of the states.
 */
void ModelIntegrandForActuators::
initialize(int step,double &dt,double ti,double tf,double y[])
{
	double tnorm = _model->getTimeNormConstant();
	double treal = tnorm * ti;
	convertStatesIntegrandToModel(treal,y,&_yModel[0]);

	ModelIntegrand::initialize(step,dt,ti,tf,&_yModel[0]);
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
void ModelIntegrandForActuators::
processAfterStep(int step,double &dt,double t,double y[])
{
	double tnorm = _model->getTimeNormConstant();
	double treal = tnorm * t;
	convertStatesIntegrandToModel(treal,y,&_yModel[0]);

	ModelIntegrand::processAfterStep(step,dt,t,&_yModel[0]);
}
//____________________________________________________________________________
/**
 * Finalize the ModelIntegrandForActuators after an integration has completed (e.g., clean up).
 *
 * @param step Step number.
 * @param t Time at which the integration completed.
 * @param y Current values of the states.
 */
void ModelIntegrandForActuators::
finalize(int step,double t,double y[])
{
	double tnorm = _model->getTimeNormConstant();
	double treal = tnorm * t;
	convertStatesIntegrandToModel(treal,y,&_yModel[0]);

	ModelIntegrand::finalize(step,t,&_yModel[0]);
}
