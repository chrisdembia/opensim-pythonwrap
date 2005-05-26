// suGeneralizedForcePerturbation.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson and Saryn Goldberg
// 
// NOTE:  When you use this callBack to make a perturbation the actuator force,
//        this change in the force IS NOT recoreded in the state file.  If you
//			 want to run an induced accleration analysis using results from a 
//			 perturbation, you must first alter the states fiel to accurately
//			 reflect the changes made to the forces.
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include <NMBLTK/Tools/rdGCVSpline.h>
#include "suGeneralizedForcePerturbation.h"

//=============================================================================
// CONSTANTS
//=============================================================================



//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
suGeneralizedForcePerturbation::~suGeneralizedForcePerturbation()
{
}
//_____________________________________________________________________________
/**
 * Construct a derivative callback instance for perturbing a generalized
 * force during an integration.
 * When this default constructor is used, the perturbation for to the
 * generalized force is set to be a unit torque.  This can then be scaled
 * if the user wants to apply a constant torque to a generalized coordinate.
 *
 * @param aModel Model for which actuator forces are to be perturbed.
 */
suGeneralizedForcePerturbation::
suGeneralizedForcePerturbation(rdModel *aModel) :
	rdDerivCallback(aModel)
{
	setNull();

	// BASE-CLASS MEMBER VARIABLES
	setType("suGeneralizedForcePerturbation");
}

/**
 * Construct a derivative callback instance for perturbing a generalized
 * force during an integration.
 * When this constructor is used, the rdStorage sent in by the user is used
 * to define a function object. This function is used to define the 
 * generalized force that is applied during the simulation.
 *
 * @param aModel Model for which actuator forces are to be perturbed.
 * @param aFunction Function that defines the generalized force to be applied.
 */
suGeneralizedForcePerturbation::
suGeneralizedForcePerturbation(rdModel *aModel, rdGCVSpline *_aSpline) :
	rdDerivCallback(aModel)
{
	setNull();

	_genForceSpline = _aSpline;

	// BASE-CLASS MEMBER VARIABLES
	setType("suGeneralizedForcePerturbation");
}

//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Set member variables to approprate NULL values.
 */
void suGeneralizedForcePerturbation::
setNull()
{
	_genCoord = -1;
	_perturbation = 0.0;
	_genForceSpline = NULL;
	_scaleFactor = 1.0;
}


//=============================================================================
// GET AND SET
//=============================================================================
//-----------------------------------------------------------------------------
// ACTUATOR
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set which generalized coordinate the force perturbation should be made.
 *
 * @param aIndex Index of the generalized coordinate.
 */
void suGeneralizedForcePerturbation::
setGenCoord(int aIndex)
{
	_genCoord = aIndex;
}
//_____________________________________________________________________________
/**
 * Get which generalized coordinate the force perturbation should be made.
 *
 * @return Generalized coordiante to which force is applied..
 */
int suGeneralizedForcePerturbation::
getGenCoord() const
{
	return(_genCoord);
}

//-----------------------------------------------------------------------------
// PERTURBATION
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the scale factor by which the perturbation will be multiplied.
 *
 * @param aScaleFactor Factor by which perturbation is multiplied
 */
void suGeneralizedForcePerturbation::
setScaleFactor(double aScaleFactor)
{
	_scaleFactor = aScaleFactor;
	printf("scale factor set\n");
}
//_____________________________________________________________________________
/**
 * Get the scale factor by which the perturbation will be multiplied.
 *
 * @return  Factor by which perturbation is multiplied
 */
double suGeneralizedForcePerturbation::
getScaleFactor() const
{
	return(_scaleFactor);
}
//_____________________________________________________________________________
/**
 * Set the perturbation.  This is only neccesary if you want to apply
 * a constant perturbation that does not come from a spline.
 *
 * @param aPerturbation Value of constatn perturbation
 */
void suGeneralizedForcePerturbation::
setPerturbation(double aPerturbation)
{
	_perturbation = aPerturbation;
}
//_____________________________________________________________________________
/**
 * Get the pertubation value.
 *
 * @return  Factor by which perturbation is multiplied
 */
double suGeneralizedForcePerturbation::
getPerturbation() const
{
	return(_perturbation);
}


//-----------------------------------------------------------------------------
// FORCE STORAGE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________

//=============================================================================
// CALLBACKS
//=============================================================================
//_____________________________________________________________________________
/**
 * Callback called right after actuation has been computed by the model.
 *
 * The perturbation generalized force is applied to the generalized coordinate.
 *
 * @param aT Normalized time.
 * @param aX Controls.
 * @param aY States.
 */
void suGeneralizedForcePerturbation::
computeActuation(double aT,double *aX,double *aY)
{
	if(_model==NULL) {
		printf("suGeneralizedForcePerturbation.computeActuation: WARN- no model.\n");
		return;
	}
	if(!getOn()) return;

	// COMPUTE PERTURBED GENERALIZED FORCE

	if((aT>=getStartTime()) && (aT<getEndTime())){
		if( _genForceSpline != NULL){
			_perturbation = _scaleFactor * 
				_genForceSpline->evaluate(0,aT*_model->getTimeNormConstant());
//			printf("time = %f\tspline perturbation = %f\n",aT*_model->getTimeNormConstant(),_perturbation);
		}
		else {
			_perturbation = _scaleFactor * _perturbation;
//			printf("constant perturbation = %f\n",_perturbation);
		}
	}	
}
//_____________________________________________________________________________
/**
 * Callback called right after actuation has been applied by the model.
 *
 * The nominal atuator force is restored.
 */
void suGeneralizedForcePerturbation::
applyActuation(double aT,double *aX,double *aY)
{
	if(_model==NULL) {
		printf("suActuatorPerturbation.applyActuation: WARN- no model.\n");
		return;
	}
	if(!getOn()) return;

	if((aT>=getStartTime()) && (aT<getEndTime())){
		_model->applyGeneralizedForce(_genCoord, _perturbation);	
//		printf("time = %f\t apply perturbation = %f\n",aT*_model->getTimeNormConstant(),_perturbation);
	}
}





