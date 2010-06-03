// ActuatorForceTargetFast.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*
* Copyright (c)  2005, Stanford University. All rights reserved. 
* Use of the OpenSim software in source form is permitted provided that the following
* conditions are met:
* 	1. The software is used only for non-commercial research and education. It may not
*     be used in relation to any commercial activity.
* 	2. The software is not distributed or redistributed.  Software distribution is allowed 
*     only through https://simtk.org/home/opensim.
* 	3. Use of the OpenSim software or derivatives must be acknowledged in all publications,
*      presentations, or documents describing work in which OpenSim or derivatives are used.
* 	4. Credits to developers may not be removed from executables
*     created from modifications of the source.
* 	5. Modifications of source code must retain the above copyright notice, this list of
*     conditions and the following disclaimer. 
* 
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
*  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
*  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
*  SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
*  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
*  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
*  OR BUSINESS INTERRUPTION) OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
*  WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
//
// This software, originally developed by Realistic Dynamics, Inc., was
// transferred to Stanford University on November 1, 2006.
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//==============================================================================
// INCLUDES
//==============================================================================
#include <iostream>
#include <OpenSim/Common/Exception.h>

#include <OpenSim/Simulation/Model/Actuator.h>
#include <OpenSim/Simulation/Model/Muscle.h>

#include "ActuatorForceTargetFast.h"
#include "CMC_TaskSet.h"
#include "CMC.h" 
#include "StateTrackingTask.h"

#include <OpenSim/Common/Storage.h>

using namespace std;
using namespace OpenSim;
using SimTK::Real;
using SimTK::Vector;
using SimTK::Matrix;

#define USE_LINEAR_CONSTRAINT_MATRIX

//==============================================================================
// DESTRUCTOR & CONSTRUCTIOR(S)
//==============================================================================
//______________________________________________________________________________
/**
 * Destructor.
 */
ActuatorForceTargetFast::~ActuatorForceTargetFast()
{
}
//______________________________________________________________________________
/**
 * Constructor.
 *
 * @param aNX Number of controls.
 * @param aController Parent controller.
 */
ActuatorForceTargetFast::
ActuatorForceTargetFast(SimTK::State& s, int aNX,CMC *aController):
	OptimizationTarget(aNX), _controller(aController)
{
	// NUMBER OF CONTROLS
	if(getNumParameters()<=0) {
		throw(Exception("ActuatorForceTargetFast: ERROR- no controls.\n"));
	}

	// ALLOCATE STATE ARRAYS
	int ny = _controller->getModel().getNumStates();
	int nq = _controller->getModel().getNumCoordinates();
	int nu = _controller->getModel().getNumSpeeds();
	int na = _controller->getModel().getActuators().getSize();

	_y.setSize(ny);
	_dydt.setSize(ny);
	_dqdt.setSize(nq);
	_dudt.setSize(nu);
	_recipAreaSquared.setSize(na);
	_recipOptForceSquared.setSize(na);
	_recipAvgActForceRangeSquared.setSize(na);
	
	int nConstraints = _controller->getTaskSet().getNumActiveTaskFunctions();

	// NUMBERS OF CONSTRAINTS
	// There are only linear equality constraints.
	setNumEqualityConstraints(nConstraints);
	setNumLinearEqualityConstraints(nConstraints);

	// DERIVATIVE PERTURBATION SIZES;
	setDX(1.0e-6);

	// COMPUTE ACTUATOR AREAS
	Array<double> f(1.0,na);
	const Set<Actuator>& fSet = _controller->getModel().getActuators();
	for(int i=0,j=0;i<fSet.getSize();i++) {
        Actuator& act = fSet.get(i);
	    act.setForce( s, f[j]);
	    _recipAreaSquared[j] = act.getStress(s);
	    _recipAreaSquared[j] *= _recipAreaSquared[j];
        j++;
	}
//std::cout << "ActuatorForceTargetFast _recipAreaSquared= " << _recipAreaSquared << std::endl;

}


//==============================================================================
// CONSTRUCTION AND DESTRUCTION
//==============================================================================
bool ActuatorForceTargetFast::
prepareToOptimize(SimTK::State& s, double *x)
{
	// Keep around a "copy" of the state so we can use it in objective function 
	// in cases where we're tracking states
	_saveState = s;
#ifdef USE_LINEAR_CONSTRAINT_MATRIX
	int nf = _controller->getModel().getActuators().getSize();
	int nc = getNumConstraints();

	_constraintMatrix.resize(nc,nf);
	_constraintVector.resize(nc);

	Vector f(nf), c(nc);

	// Build linear constraint matrix and constant constraint vector
	f = 0;


	computeConstraintVector(s, f, _constraintVector);

	for(int j=0; j<nf; j++) {
		f[j] = 1;
		computeConstraintVector(s, f, c);
		for(int i=0; i<nc; i++) _constraintMatrix(i,j) = (c[i] - _constraintVector[i]);
		f[j] = 0;
	}
#endif


	// COMPUTE MAX ISOMETRIC FORCE
	const Set<Actuator>& fSet = _controller->getModel().getActuators();
	
    const double eps = std::numeric_limits<double>::epsilon();
	double fOpt;
	// use tempory copy of state because computeIsokineticForceAssumingInfinitelyStiffTendon
	// will change the muscle states
	SimTK::State tempState = s;
	getController()->getModel().getSystem().realize( tempState, SimTK::Stage::Dynamics );
	for(int i=0, index=0;i<fSet.getSize();i++) {
        Actuator& act = fSet.get(i);
	    Muscle* mus = dynamic_cast<Muscle*>(&act);
		if(mus==NULL) {
			fOpt = 1.0e-4;
		} else {
			double activation = 1.0;
			fOpt = mus->computeIsokineticForceAssumingInfinitelyStiffTendon(tempState,activation);
			if( std::fabs(fOpt) < eps ) fOpt = 1.0e-4;
		}
		_recipOptForceSquared[index++] = 1.0 / (fOpt*fOpt);
	}

//std::cout << "Fast:prepareToOptimize _recipOptForceSquared \n" << _recipOptForceSquared << std::endl;

	
	// return false to indicate that we still need to proceed with optimization (did not do a lapack direct solve)
	return false;
}

//==============================================================================
// SET AND GET
//==============================================================================


//==============================================================================
// PERFORMANCE AND CONSTRAINTS
//==============================================================================
//------------------------------------------------------------------------------
// PERFORMANCE
//------------------------------------------------------------------------------
//______________________________________________________________________________
/**
 * Compute performance given x.
 *
 * @param aF Vector of controls.
 * @param rP Value of the performance criterion.
 * @return Status (normal termination = 0, error < 0).
 */
int ActuatorForceTargetFast::
objectiveFunc(const Vector &aF, const bool new_coefficients, Real& rP) const
{
	const Set<Actuator>& fSet = _controller->getModel().getActuators();
	double p = 0.0;
	const CMC_TaskSet& tset=_controller->getTaskSet();
	for(int i=0,j=0;i<fSet.getSize();i++) {
        Actuator& act = fSet.get(i);
	    Muscle* mus = dynamic_cast<Muscle*>(&act);
	    if(mus) {
		    p +=  aF[j] * aF[j] * _recipOptForceSquared[j];
//std::cout << "ActuatorForceTargetFast::objectiveFunc area" << j << " " << act.getName() << "  =" << aF[j] * aF[j] *  _recipAreaSquared[j]  << std::endl;

	    } else {
		    p +=  aF[j] * aF[j] *  _recipAreaSquared[j];
//std::cout << "ActuatorForceTargetFast::objectiveFunc force" << j << " " << act.getName() << "  =" << aF[j] * aF[j] * _recipOptForceSquared[j]  << std::endl;

        }
        j++;
	}
	double pre = p;
	// If tracking states, add in errors from them squared
	for(int t=0; t<tset.getSize(); t++){
		TrackingTask& ttask = tset.get(t);
		StateTrackingTask* stateTask=NULL;
		if ((stateTask=dynamic_cast<StateTrackingTask*>(&ttask))!= NULL){
			double err = stateTask->getTaskError(_saveState);
			//cout << "task error " << err << endl;
			p+= (err * err * stateTask->getWeight(0));

		}
	}
	rP = p;
	//cout << "Objective function" << rP << " vs. without emg " << pre << endl;

	return(0);
}
//______________________________________________________________________________
/**
 * Compute the gradient of performance given x.
 *
 * @param x Vector of controls.
 * @param dpdx Derivatives of performance with respect to the controls.
 * @return Status (normal termination = 0, error < 0).
 */
int ActuatorForceTargetFast::
gradientFunc(const Vector &x, const bool new_coefficients, Vector &gradient) const
{
    const Set<Actuator>& fSet = _controller->getModel().getActuators();
    double p = 0.0;
    for(int i=0,index=0;i<fSet.getSize();i++) {
        Actuator& act = fSet.get(i);
        Muscle* mus = dynamic_cast<Muscle*>(&act);
        if(mus) {
		    gradient[index] =  2.0 * x[index] * _recipOptForceSquared[index];
        } else {
		    gradient[index] =  2.0 * x[index] * _recipAreaSquared[index];
        }
        index++;
    }
//std::cout << "rdActuatorForceTargetFast::gradentFuncgradient =" << gradient << std::endl;
	// Add in the terms for the stateTracking
	const CMC_TaskSet& tset=_controller->getTaskSet();
	for(int t=0; t<tset.getSize(); t++){
		TrackingTask& ttask = tset.get(t);
		StateTrackingTask* stateTask=NULL;
		if ((stateTask=dynamic_cast<StateTrackingTask*>(&ttask))!= NULL){
			Vector errGradient = stateTask->getTaskErrorGradient(_saveState);
			gradient += errGradient;
		}
	}

	return(0);
}

//------------------------------------------------------------------------------
// CONSTRAINT
//------------------------------------------------------------------------------
//______________________________________________________________________________
/**
 * Compute constraint ic given x.
 * Note that the indexing starts at 1;
 *
 * @param x Array of controls.
 * @param ic Index of the constraint (indexing starts at 1, not 0).
 * @param c Value of constraint ic.
 * @return Status (normal termination = 0, error < 0).
 */
int ActuatorForceTargetFast::
constraintFunc(const SimTK::Vector &x, const bool new_coefficients, SimTK::Vector &constraints) const
{
#ifndef USE_LINEAR_CONSTRAINT_MATRIX

	// Evaluate constraint function for all constraints and pick the appropriate component
	computeConstraintVector(s, x,constraints);

#else

	// Use precomputed constraint matrix
	constraints = _constraintMatrix * x + _constraintVector;

#endif
	return(0);
}
//______________________________________________________________________________
/**
 * Compute all constraints given x.
 */
void ActuatorForceTargetFast::
computeConstraintVector(SimTK::State& s, const Vector &x,Vector &c) const
{
	CMC_TaskSet&  taskSet = _controller->updTaskSet();
	const Set<Actuator>& fSet = _controller->getModel().getActuators();
	for(int i=0;i<fSet.getSize();i++) {
        Actuator& act = fSet.get(i);
        act.setOverrideForce(s, x[i]);
        act.overrideForce(s,true);

	}
	_controller->getModel().getSystem().realize(s, SimTK::Stage::Acceleration );

	taskSet.computeAccelerations(s);
	Array<double> &w = taskSet.getWeights();
	Array<double> &aDes = taskSet.getDesiredAccelerations();
	Array<double> &a = taskSet.getAccelerations();
	// CONSTRAINTS
	for(int i=0; i<getNumConstraints(); i++)
		c[i]=w[i]*(aDes[i]-a[i]);
	// reset the actuator control 
	for(int i=0;i<fSet.getSize();i++) {
        Actuator& act = fSet.get(i);
        act.overrideForce(s,false);

	}
    _controller->getModel().getSystem().realizeModel(s);
    _controller->getModel().getSystem().realize(s, SimTK::Stage::Position );

}
//______________________________________________________________________________
/**
 * Compute the gradient of constraint i given x.
 *
 * @param x Array of controls.
 * @param ic Index of the constraint (indexing starts at 1, not 0).
 * @param dcdx Derivative of constraint ic with respect to the controls.
 * @return Status (normal termination = 0, error < 0).
 */
int ActuatorForceTargetFast::
constraintJacobian(const SimTK::Vector &x, const bool new_coefficients, SimTK::Matrix &jac) const
{
#ifndef USE_LINEAR_CONSTRAINT_MATRIX

	// Compute gradient using callbacks to constraintFunc
	OptimizationTarget::CentralDifferencesConstraint(this,&_dx[0],x,jac);

#else

	// Use precomputed constraint matrix (works if constraint is linear)
	jac = _constraintMatrix;

#endif

	return 0;
}
