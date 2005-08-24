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
 * Construct a derivative callback instance for applying external forces
 * during an integration.
 *
 * @param aModel Model for which external forces are to be applied.
 * @param aBody Body to which external forces are to be applied.
 * @param aPoint Point at which external forces are to be applied.  This point
 * can be expressed in either local or global coordinates, but be sure the
 * _inputPositionsInLocalFrame is set appropriately.
 */
suLinearSpring::
suLinearSpring(rdModel *aModel,int aBody,double aPoint[3]) :
	suForceApplier(aModel,aBody)
{
	setNull();

	// MEMBER VARIABLES
	setBody(aBody);
	setPoint(aPoint);
}

//_____________________________________________________________________________
/**
 * Construct a derivative callback instance for applying external forces
 * during an integration.
 *
 * @param aModel Model for which external forces are to be applied.
 * @param aBody Body to which external forces are to be applied.
 * @param aPoint Point at which external forces are to be applied.  This point
 * can be expressed in either local or global coordinates, but be sure the
 * _inputPositionsInLocalFrame is set appropriately.
 * @param aForce Force to be applied expressed in global coordinates.
 */
suLinearSpring::
suLinearSpring(rdModel *aModel,int aBody,double aPoint[3],
	rdVectorFunction* aPosFunction,rdVectorFunction* aVelFunction, 
		double aK[3], double aB[3]) :
		suForceApplier(aModel,aBody)
{
	setNull();

	// MEMBER VARIABLES
	setBody(aBody);
	setPoint(aPoint);
	setPosFunction(aPosFunction);
	setVelFunction(aVelFunction);
	setKValue(aK);
	setBValue(aB);

}

//_____________________________________________________________________________
/**
 * Construct a derivative callback instance for applying external forces
 * during an integration.
 *
 * @param aModel Model for which external forces are to be applied.
 * @param aBody Body to which external forces are to be applied.
 * @param aPointFunction containing (t,x,y,z) of points at which external
 * forces are to be applied.  These points can be expressed in either local or global
 * coordinates, but be sure the _inputPositionsInLocalFrame is set appropriately. If a 
 * NULL point set is sent in, the  force will be applied at the body COM.
 * @param aForceFunction containing (t,x,y,z) of force to be applied expressed
 * in global coordinates.
 */
suLinearSpring::
suLinearSpring(rdModel *aModel,int aBody,rdVectorFunction* aPointFunction,
	rdVectorFunction* aPosFunction,rdVectorFunction* aVelFunction,double aK[3],
	double aB[3]) :
	suForceApplier(aModel,aBody)
{
	setNull();

	// MEMBER VARIABLES
	setBody(aBody);
	setPointFunction(aPointFunction);
	setPosFunction(aPosFunction);
	setVelFunction(aVelFunction);
	setKValue(aK);
	setBValue(aB);

}



//_____________________________________________________________________________
/**
 * Set member variables to approprate NULL values.
 */
void suLinearSpring::
setNull()
{
	setType("suLinearSpring");
	_posFunction = NULL;
	_velFunction = NULL;
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
setPosFunction(rdVectorFunction* aPosFunction)
{
	_posFunction = aPosFunction;
}
//_____________________________________________________________________________
/**
 * Get the vector function containing the (t,x,y,z) of the poisiton that the point
 * should be corrected towards, expressed in the global ref frame.
 *
 * @return rPosFunction.
 */
rdVectorFunction* suLinearSpring::
getPosFunction() const
{
	return(_posFunction);
}
//-----------------------------------------------------------------------------
// VELOCITY FUNCTION
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the vector function containing the (t,x,y,z) of the velocity that should
 * be corrected towards, expressed in the global ref frame.
 *
 * @param aVelFunction 
 */
void suLinearSpring::
setVelFunction(rdVectorFunction* aVelFunction)
{
	_velFunction = aVelFunction;
}
//_____________________________________________________________________________
/**
 * Get the vector function containing the (t,x,y,z) of the velocity that should
 * be corrected towards, expressed in the global ref frame.
 *
 * @return rVelFunction.
 */
rdVectorFunction* suLinearSpring::
getVelFunction() const
{
	return(_velFunction);
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
	int i;
	double point[3] = {0,0,0};
	double targetPos[3] = {0,0,0};
	double targetVel[3] = {0,0,0};
	double treal = aT*_model->getTimeNormConstant();
	
	if(_model==NULL) {
		printf("suLinearSpring.applyActuation: WARN- no model.\n");
		return;
	}
	if(!getOn()) return;

	if((aT>=getStartTime()) && (aT<getEndTime())){

		if(_pointFunction!=NULL) {
			_pointFunction->evaluate(&treal,point);
			setPoint(point);
		}

		if(_posFunction!=NULL) {
			_posFunction->evaluate(&treal,targetPos);
		}
		if(_velFunction!=NULL) {
			_velFunction->evaluate(&treal,targetVel);
		}

		// GET GLOBAL POSITION AND VELOCITY
		const int ground = _model->getGroundID();
		double posBodyCOMLocal[3] = {0,0,0};
		double posBodyCOMGlobal[3];
		double posPointRelBodyCOMGlobal[3];
		double posPointRelBodyCOMLocal[3];
		double pointGlobal[3];
		double velGlobal[3];

		if(_inputPositionsInLocalFrame == false){
			for(i=0;i<3;i++){
				pointGlobal[i] = _point[i];
			}
			_model->getPosition(_body,posBodyCOMLocal,posBodyCOMGlobal);
			rdMtx::Subtract(1,3,_point,posBodyCOMGlobal,posPointRelBodyCOMGlobal);
			_model->transform(ground,posPointRelBodyCOMGlobal,_body,posPointRelBodyCOMLocal);
			setPoint(posPointRelBodyCOMLocal);
		} else {
			_model->getPosition(_body,_point,pointGlobal);
		}
		_model->getVelocity(_body,_point,velGlobal);

		//CALCULATE FORCE AND APPLY
		double difPos[3];
		double difVel[3];
		double force[3];
		double scaleFactor;

		if(_scaleFunction != NULL){
			scaleFactor = _scaleFunction->evaluate(0,aT*_model->getTimeNormConstant());
			setScaleFactor(scaleFactor);
		}
//		rdMtx::Subtract(1,3,targetPos,pointGlobal,difPos);
//		rdMtx::Subtract(1,3,targetVel,velGlobal,difVel);
		rdMtx::Subtract(1,3,pointGlobal,targetPos,difPos);
		rdMtx::Subtract(1,3,velGlobal,targetVel,difVel);

		for(i=0;i<3;i++){
			force[i] = _scaleFactor*(-_k[i]*difPos[i] - _b[i]*difVel[i]);
		}
		setForce(force);
		_model->applyForce(_body,_point,_force);
		_appliedForceStore->append(aT,3,_force);

	}	
}





