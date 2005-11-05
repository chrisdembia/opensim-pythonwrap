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
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Tools/rdMtx.h>
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Tools/rdVectorGCVSplineR1R3.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include <NMBLTK/Tools/rdFunctionSet.h>
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
 * @param aBody Body to which external torques are to be applied.
 */
suTorsionalSpring::
suTorsionalSpring(rdModel *aModel,int aBody) : 
	suTorqueApplier(aModel,aBody)
{
	setNull();

	// MEMBER VARIABLES
	setBody(aBody);
}

//_____________________________________________________________________________
/**
 * Set member variables to approprate NULL values.
 */
void suTorsionalSpring::
setNull()
{
	setType("suTorsionalSpring");
	_targetPosition = NULL;
	_targetVelocity = NULL;
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
setTargetPosition(rdVectorFunction* aPosFunction)
{
	_targetPosition = aPosFunction;
}
//_____________________________________________________________________________
/**
 * Get the vector function containing the nominal angular position of the body.
 *
 * @return aPosFunction.
 */
rdVectorFunction* suTorsionalSpring::
getTargetPosition() const
{
	return(_targetPosition);
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
setTargetVelocity(rdVectorFunction* aVelFunction)
{
	_targetVelocity = aVelFunction;
}
//_____________________________________________________________________________
/**
 * Get the vector function containing the nominal angular velocity of the body.
 *
 * @return aVelFunction.
 */
rdVectorFunction* suTorsionalSpring::
getTargetVelocity() const
{
	return(_targetVelocity);
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
// UTILITY
//=============================================================================
//_____________________________________________________________________________
/**
 * Compute the target orientation and angular velocity of the body.
 * A spring force is applied based on the difference between the body's
 * actual orientation and angular velocities and corresponding target
 * values.  The target orientation and angular velocity are computed
 * with respect to the global frame.
 *
 * @param aQStore Storage containing the time history of generalized
 * coordinates for the model. Note that all generalized coordinates must
 * be specified and in radians and Euler parameters.
 * @param aUStore Stoarge containing the time history of generalized
 * speeds for the model.  Note that all generalized speeds must
 * be specified and in radians.
 */
void suTorsionalSpring::
computeTargetFunctions(rdStorage *aQStore,rdStorage *aUStore)
{
	int i;
	int nq = _model->getNQ();
	int nu = _model->getNU();
	double t;
	rdArray<double> q(0.0,nq),u(0.0,nu);
	double dirCos[9],ang[3],angVel[3];
	rdStorage angStore,angVelStore;

	// CREATE THE TARGET POSITION AND VELOCITY FUNCTIONS
	int size = aQStore->getSize();
	for(i=0;i<size;i++) {
		// Set the model state
		aQStore->getTime(i,t);
		aQStore->getData(i,nq,&q[0]);
		aUStore->getData(i,nu,&u[0]);
		_model->setConfiguration(&q[0],&u[0]);

		// Get global position and velocity
		_model->getDirectionCosines(_body,dirCos);
		_model->convertDirectionCosinesToAngles(dirCos,&ang[0],&ang[1],&ang[2]);
		_model->getAngularVelocity(_body,angVel);

		// Append to storage
		angStore.append(t,3,ang);
		angVelStore.append(t,3,angVel);
	}

	// CREATE TARGET FUNCTIONS
	// Position
	size = angStore.getSize();
	int padSize = size / 4;
	if(padSize>100) padSize = 100;
	double *time=NULL;
	double *pg0=0,*pg1=0,*pg2=0;
	angStore.pad(padSize);
	size = angStore.getTimeColumn(time);
	angStore.getDataColumn(0,pg0);
	angStore.getDataColumn(1,pg1);
	angStore.getDataColumn(2,pg2);
	rdVectorGCVSplineR1R3 *angFunc = new rdVectorGCVSplineR1R3(3,size,time,pg0,pg1,pg2);
	setTargetPosition(angFunc);
	// Velocity
	if(time!=NULL) { delete[] time; time=NULL; }
	double *vg0=0,*vg1=0,*vg2=0;
	angVelStore.pad(padSize);
	size = angVelStore.getTimeColumn(time);
	angVelStore.getDataColumn(0,vg0);
	angVelStore.getDataColumn(1,vg1);
	angVelStore.getDataColumn(2,vg2);
	rdVectorGCVSplineR1R3 *angVelFunc = new rdVectorGCVSplineR1R3(3,size,time,vg0,vg1,vg2);
	setTargetVelocity(angVelFunc);
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
		double time = aT*_model->getTimeNormConstant(); 
		double nomDirCos[9];
		double curDirCos[9];
		double difDirCos[9];
		double difAng[3];
		double eulerAngle[3];
		_targetPosition->evaluate(&time,eulerAngle);

		_model->convertAnglesToDirectionCosines(eulerAngle[0],eulerAngle[1],
			eulerAngle[2],nomDirCos);
		_model->getDirectionCosines(_body,curDirCos);
		rdMtx::Transpose(3,3,curDirCos,curDirCos);
		rdMtx::Multiply(3,3,3,curDirCos,nomDirCos,difDirCos);
		_model->convertDirectionCosinesToAngles(difDirCos,&difAng[0],&difAng[1],&difAng[2]);

		// Calculate difference between current angular velocity and nominal ang velocity,
		//  expressed in body-fixed 1-2-3 rotational velocities
		double nomAngVel[3];
		double curAngVel[3];
		double difAngVel[3];
		double difQDot[3];
		double eulerTransform[9];
		_targetVelocity->evaluate(&time,nomAngVel); //NEEDS TO BE IN GLOBAL COORDS
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





