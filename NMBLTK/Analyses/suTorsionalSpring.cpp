// suTorsionalSpring.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson and Saryn Goldberg
// 
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <RD/Tools/rdMath.h>
#include <RD/Tools/rdMtx.h>
#include <RD/Tools/rdTools.h>
#include <RD/Simulation/Model/rdModel.h>
#include <RD/Tools/rdFunctionSet.h>
#include "suTorsionalSpring.h"

//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
suTorsionalSpring::~suTorsionalSpring()
{
}
//_____________________________________________________________________________
/**
 * Construct a derivative callback instance for applying external torques
 * during an integration.
 *
 * @param aModel Model for which external torques are to be applied.
 */
suTorsionalSpring::
suTorsionalSpring(rdModel *aModel) : 
	suTorqueApplier(aModel)
{
	setNull();

	// BASE-CLASS MEMBER VARIABLES
	setType("suTorsionalSpring");
}

//_____________________________________________________________________________
/**
 * Construct a derivative callback instance for applying external torques
 * during an integration.
 *
 * @param aModel Model for which external torques are to be applied.
 * @param aBody Body to which external torques are to be applied.
 */
suTorsionalSpring::
suTorsionalSpring(rdModel *aModel,int aBody) : 
	suTorqueApplier(aModel)
{
	setNull();

	// MEMBER VARIABLES
	setBody(aBody);
}

//_____________________________________________________________________________
/**
 * Construct a derivative callback instance for applying external torques
 * during an integration.
 *
 * @param aModel Model for which external torques are to be applied.
 * @param aBody Body to which external torques are to be applied.
 * @param aTorque Torque to be applied expressed in global coordinates.
 */
suTorsionalSpring::
suTorsionalSpring(rdModel *aModel,int aBody,rdVectorFunction *aPosFunction,
		rdVectorFunction *aVelFunction, double aK[3], double aB[3]) : 
	suTorqueApplier(aModel)
{
	setNull();

	// MEMBER VARIABLES
	setBody(aBody);
	setPosFunction(aPosFunction);
	setVelFunction(aVelFunction);
	setKValue(aK);
	setBValue(aB);

}

//_____________________________________________________________________________
/**
 * Set member variables to approprate NULL values.
 */
void suTorsionalSpring::
setNull()
{
	setType("suTorsionalSpring");
	_posFunction = NULL;
	_velFunction = NULL;
	_k[0] = _k[1] = _k[2] = 0.0;
	_b[0] = _b[1] = _b[2] = 0.0;
	_scaleFunction = NULL;
	_scaleFactor = 1.0;
}

//=============================================================================
// GET AND SET
//=============================================================================

//-----------------------------------------------------------------------------
// POSITION VECTOR FUNCTION
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the vetor function containing the nominal angular postion of the body.
 *
 * @param aPosFunction Vector function containing the nominal angular position of
 * the body in the intertial reference frame.
 */
void suTorsionalSpring::
setPosFunction(rdVectorFunction* aPosFunction)
{
	_posFunction = aPosFunction;
}
//_____________________________________________________________________________
/**
 * Get the vector function containing the nominal angular position of the body.
 *
 * @return aPosFunction.
 */
rdVectorFunction* suTorsionalSpring::
getPosFunction() const
{
	return(_posFunction);
}

//-----------------------------------------------------------------------------
// VELOCITY VECTOR FUNCTION
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the vector function containing the nominal angular velocity of the body.
 *
 * @param aPosFunction Vector function containing the nominal angular velocity of
 * the body in the intertial reference frame.
 */
void suTorsionalSpring::
setVelFunction(rdVectorFunction* aVelFunction)
{
	_velFunction = aVelFunction;
}
//_____________________________________________________________________________
/**
 * Get the vector function containing the nominal angular velocity of the body.
 *
 * @return aVelFunction.
 */
rdVectorFunction* suTorsionalSpring::
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
void suTorsionalSpring::
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
void suTorsionalSpring::
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
void suTorsionalSpring::
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
void suTorsionalSpring::
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
void suTorsionalSpring::
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
rdFunction* suTorsionalSpring::
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
void suTorsionalSpring::
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
double suTorsionalSpring::
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
void suTorsionalSpring::
applyActuation(double aT,double *aX,double *aY)
{
	int i;
	double torque[3] = {0,0,0};
	const int ground = _model->getGroundID();

	if(_model==NULL) {
		printf("suTorsionalSpring.applyActuation: WARN- no model.\n");
		return;
	}
	if(!getOn()) return;

	if((aT>=getStartTime()) && (aT<getEndTime())){

		// Calculate Euler angles to rotate from current orientation to nominal orientation,
		//  expressed in current body reference frame
		rdArray<double> nomEulerArray(0.0);
		double nomDirCos[9];
		double curDirCos[9];
		double difDirCos[9];
		double difAng[3];  
		nomEulerArray = _posFunction->evaluate(aT*_model->getTimeNormConstant());
	
double eulerAngle[3];
eulerAngle[0] = nomEulerArray.get(0);
eulerAngle[1] = nomEulerArray.get(1);
eulerAngle[2] = nomEulerArray.get(2);

		_model->convertAnglesToDirectionCosines(nomEulerArray.get(0),nomEulerArray.get(1),
			nomEulerArray.get(2), nomDirCos);
		_model->getDirectionCosines(_body, curDirCos);
		rdMtx::Transpose(3,3,curDirCos,curDirCos);
		rdMtx::Multiply(3,3,3,curDirCos,nomDirCos,difDirCos);
		_model->convertDirectionCosinesToAngles(difDirCos,&difAng[0],&difAng[1],&difAng[2]);

		// Calculate difference between current angular velocity and nominal ang velocity,
		//  expressed in body-fixed 1-2-3 rotational velocities
		rdArray<double> nomAngVelArray(0.0);
		double* nomAngVel;
		double curAngVel[3];
		double difAngVel[3];
		double difQDot[3];
		double eulerTransform[9];
		nomAngVelArray = _velFunction->evaluate(aT*_model->getTimeNormConstant()); //NEEDS TO BE IN GLOBAL COORDS
		nomAngVel = nomAngVelArray.get();
		_model->getAngularVelocity(_body,curAngVel);  //EXPRESSED IN GLOBAL COORDS
		rdMtx::Subtract(3,1,curAngVel,nomAngVel,difAngVel);
//		rdMtx::Subtract(3,1,nomAngVel,curAngVel,difAngVel);
		_model->transform(ground,difAngVel,_body,difAngVel);
		_model->formEulerTransform(_body, eulerTransform);
		rdMtx::Multiply(3,3,1,eulerTransform,difAngVel,difQDot);
		
		// Calculate torque to apply to body, expressed in global reference frame
		double scaleFactor;
		if(_scaleFunction != NULL){
			scaleFactor = _scaleFunction->evaluate(0,aT*_model->getTimeNormConstant());
			setScaleFactor(scaleFactor);
		}
		for(i=0;i<3;i++)
			torque[i] = _scaleFactor*(-_k[i]*difAng[i] - _b[i]*difQDot[i]);
		rdMtx::Multiply(3,3,1,eulerTransform,torque,torque);
		_model->transform(_body,torque,ground,torque);

		// Apply torque to body
		setTorque(torque);
		_model->applyTorque(_body,_torque);
		_appliedTorqueStore->append(aT,3,_torque);

	}	
}





