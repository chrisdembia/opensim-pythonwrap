// suLinearSpring.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson and Saryn Goldberg
// 
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include <iostream>
#include <string>
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Tools/rdMtx.h>
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include <NMBLTK/Tools/rdVectorFunction.h>
#include "suLinearSpring.h"


using namespace std;


//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
suLinearSpring::~suLinearSpring()
{
}
//_____________________________________________________________________________
/**
 * Construct a derivative callback instance for applying external forces
 * during an integration.
 *
 * @param aModel Model for which external forces are to be applied.
 */
suLinearSpring::
suLinearSpring(rdModel *aModel,int aBody) :
	suForceApplier(aModel,aBody)
{
	setNull();

	// BASE-CLASS MEMBER VARIABLES
	setType("suLinearSpring");
}

//_____________________________________________________________________________
/**
 * Set member variables to approprate NULL values.
 */
void suLinearSpring::
setNull()
{
	setType("suLinearSpring");
	_target = NULL;
	_scaleFunction = NULL;
	_scaleFactor = 1.0;
}

//=============================================================================
// GET AND SET
//=============================================================================

//-----------------------------------------------------------------------------
// POSITION FUNCTION
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the vector function containing the (t,x,y,z) of the poisiton that the point
 * should be corrected towards, expressed in teh global ref frame.
 *
 * @param aPosFunction containing force application point function.
 */
void suLinearSpring::
setTarget(rdVectorFunction* aPosFunction)
{
	_target = aPosFunction;
}
//_____________________________________________________________________________
/**
 * Get the vector function containing the (t,x,y,z) of the poisiton that the point
 * should be corrected towards, expressed in the global ref frame.
 *
 * @return rPosFunction.
 */
rdVectorFunction* suLinearSpring::
getTarget() const
{
	return(_target);
}

//-----------------------------------------------------------------------------
// K VALUE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the spring constant, k.
 *
 * @param aK Vector of three values of k.
 */
void suLinearSpring::
setKValue(double aK[3])
{
	int i;
	for(i=0;i<3;i++)
		_k[i] = aK[i];
}
//_____________________________________________________________________________
/**
 * Get the spring constant, k.
 *
 * @return aK.
 */
void suLinearSpring::
getKValue(double aK[3])
{
	aK = _k;
}

//-----------------------------------------------------------------------------
// B VALUE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the damping constant, b.
 *
 * @param aK Vector of three values of b.
 */
void suLinearSpring::
setBValue(double aB[3])
{
	int i;
	for(i=0;i<3;i++)
		_b[i] = aB[i];

}
//_____________________________________________________________________________
/**
 * Get the damping constant, b.
 *
 * @return aB.
 */
void suLinearSpring::
getBValue(double aB[3])
{
	aB = _b;
}

//-----------------------------------------------------------------------------
// SCALE FACTOR FUNCTION
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the function containing the scale factor as a function of time.
 *
 * @param aScaleFunction.
 */
void suLinearSpring::
setScaleFunction(rdFunction* aScaleFunction)
{
	_scaleFunction = aScaleFunction;
}
//_____________________________________________________________________________
/**
 * Get the function containing the scale factor as a function of time.
 *
 * @return aScaleFunction.
 */
rdFunction* suLinearSpring::
getScaleFunction() const
{
	return(_scaleFunction);
}

//-----------------------------------------------------------------------------
// SCALE FACTOR
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the scale factor that pre-multiplies the applied torque.
 *
 * @param aScaleFactor
 */
void suLinearSpring::
setScaleFactor(double aScaleFactor)
{
	_scaleFactor = aScaleFactor;
}
//_____________________________________________________________________________
/**
 * Get the scale factor that pre-multiplies the applied torque.
 *
 * @return aScaleFactor.
 */
double suLinearSpring::
getScaleFactor()
{
	return(_scaleFactor);
}

//=============================================================================
// CALLBACKS
//=============================================================================
//_____________________________________________________________________________
/**
 * Callback called right after actuation has been applied by the model.
 *
 * *
 * @param aT Real time.
 * @param aX Controls.
 * @param aY States.
 */
void suLinearSpring::
applyActuation(double aT,double *aX,double *aY)
{
	//CALCULATE FORCE AND APPLY
	double dx[3],dv[3];
	double force[3];
	double scaleFactor;

	int i;
	int ground = _model->getGroundID();
	rdArray<int> derivWRT(0,1);
	rdArray<double> origin(0.0,3);
	rdArray<double> vcomGlobal(0.0,3);
	rdArray<double> treal(0.0,1);
	rdArray<double> pLocal(0.0,3);
	rdArray<double> vLocal(0.0,3);
	rdArray<double> pTarget(0.0,3);
	rdArray<double> vTarget(0.0,3);
	rdArray<double> pGlobal(0.0,3);
	rdArray<double> vGlobal(0.0,3);
	
	treal[0] = aT*_model->getTimeNormConstant();
	
	if(_model==NULL) {
		printf("suLinearSpring.applyActuation: WARN- no model.\n");
		return;
	}
	if(!getOn()) return;

	if((aT>=getStartTime()) && (aT<getEndTime())){

		if(_pointFunction!=NULL) {
			_pointFunction->evaluate(treal,pLocal);
			_pointFunction->evaluate(treal,vLocal,derivWRT);
			setPoint(&pLocal[0]);
		}

		if(_target!=NULL) {
			_target->evaluate(treal,pTarget);
			_target->evaluate(treal,vTarget,derivWRT);
		} else {
			cout<<"\nsuLinearSpring.applyActuation:  WARN- no target has been set.\n";
		}

		// GET GLOBAL POSITION AND VELOCITY
		_model->getPosition(_body,&pLocal[0],&pGlobal[0]);
		_model->getVelocity(_body,&origin[0],&vcomGlobal[0]);
		_model->transform(_body,&vLocal[0],ground,&vLocal[0]);
		rdMtx::Add(1,3,&vcomGlobal[0],&vLocal[0],&vGlobal[0]);

	
		if(_scaleFunction != NULL){
			scaleFactor = _scaleFunction->evaluate(0,aT*_model->getTimeNormConstant());
			setScaleFactor(scaleFactor);
		}
		rdMtx::Subtract(1,3,&pTarget[0],&pGlobal[0],dx);
		rdMtx::Subtract(1,3,&vTarget[0],&vGlobal[0],dv);

		for(i=0;i<3;i++){
			force[i] = _scaleFactor*(_k[i]*dx[i] + _b[i]*dv[i]);
		}
		setForce(force);
		_model->applyForce(_body,&pLocal[0],force);

		_appliedForceStore->append(aT,3,_force);
	}	
}





