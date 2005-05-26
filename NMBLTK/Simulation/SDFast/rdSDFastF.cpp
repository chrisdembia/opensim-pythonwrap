// rdSDFast.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2000 Realistic Dynamics, Inc.
// All rights reserved.
//
// CONFIDENTIAL
//
// The material contain within this file is the sole property of
// Realistic Dynamics, Inc., and may not be read, copied, or distributed
// without the expressed writen consent of Realistic Dynamics, Inc.
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include "rdSDFastDLL.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <RD/Tools/rdMath.h>
#include "sdfast.h"
#include <RD/Simulation/Model/rdModel.h>
#include "rdSDFast.h"

//=============================================================================
// STATICS
//=============================================================================
const int rdSDFast::GROUND = 0;

//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Default constructor.
 */
rdSDFast::rdSDFast()
{
	// NUMBERS OF THINGS
	_nx = 0;
	_nq = 0;
	_nu = 0;
	_ny = 0;
	_nyi = 0;
	_nj = 0;
	_nb = 0;


	// BODY NAMES


	// COORDINATE TO JOINT AND AXIS MAP

}
//_____________________________________________________________________________
/**
 * Destructor.
 */
rdSDFast::~rdSDFast()
{

	// COORDINATE MAPS
	if(_u2jMap!=NULL) { delete[] _u2jMap;  _u2jMap=NULL; }
	if(_u2aMap!=NULL) { delete[] _u2aMap;  _u2aMap=NULL; }

}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Construct maps from coordinate to joint and axis.
 * These maps should be set up using sdinfo.
 */
int rdSDFast::constructJointAndAxisMaps()
{
	_u2jMap = NULL;
	_u2aMap = NULL;

	return(0);
}



//=============================================================================
// GET AND SET
//=============================================================================
//-----------------------------------------------------------------------------
// KINEMATICS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the inertial position of a point on a body.
 */
void rdSDFast::
getPosition(int aBody,double aPoint[3],double aPos[3])
{
	sdpos_(&aBody,aPoint,aPos);
}
//_____________________________________________________________________________
/**
 * Get the inertial velocity of a point on a body.
 */
void rdSDFast::
getVelocity(int aBody,double aPoint[3],double aVel[3])
{
	sdvel_(&aBody,aPoint,aVel);
}
//_____________________________________________________________________________
/**
 * Get the inertial acceleration of a point on a body.
 */
void rdSDFast::
getAcceleration(int aBody,double aPoint[3],double aAcc[3])
{
	sdacc_(&aBody,aPoint,aAcc);
}

//-----------------------------------------------------------------------------
// BODY KINEMATICS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the orientation of a body with respect to the inertial frame in
 * terms of direction cosines.
 *
 * Note that the configuration of the model must be set before calling this
 * method.
 *
 * @param aBody Body ID.
 * @param rDC Direction cosines.
 *
 * @see setConfiguration()
 */
void rdSDFast::
getDirectionCosines(int aBody,double rDC[3][3])
{
	sdorient_(&aBody,rDC);
}
//_____________________________________________________________________________
/**
 * Get the angular velocity of a body with respect to the inertial frame
 * expressed in the body-local frame.
 *
 * Note that the configuration of the model must be set before calling this
 * method.
 *
 * @param aBody Body ID.
 * @param rAngVel Angular velocity.
 *
 * @see setConfiguration()
 */
void rdSDFast::
getAngularVelocityBodyLocal(int aBody,double rAngVel[3])
{
	sdangvel_(&aBody,rAngVel);
}
//_____________________________________________________________________________
/**
 * Get the angular acceleration of a body with respect to the inertial frame
 * expressed in the body-local frame.
 *
 * Note that the configuration of the model must be set before calling this
 * method.
 *
 * @param aBody Body ID.
 * @param rAngAcc Angular acceleration.
 *
 * @see setConfiguration()
 */
void rdSDFast::
getAngularAccelerationBodyLocal(int aBody,double rAngAcc[3])
{
	sdangacc_(&aBody,rAngAcc);
}


//-----------------------------------------------------------------------------
// GRAVITY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the gravity.
 */
void rdSDFast::
setGravity(double aG[3])
{
	rdModel::setGravity(aG);
	sdgrav_(aG);
	sdinit_();
}
//_____________________________________________________________________________
/**
 * Get the gravity.
 */
void rdSDFast::
getGravity(double aG[3])
{
	sdgetgrav_(aG);
}

//-----------------------------------------------------------------------------
// BODY INFORMATION
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the body ID of the ground (or inertial) frame.
 */
int rdSDFast::
getGroundID()
{
	return(GROUND);
}
//_____________________________________________________________________________
/**
 * Get the mass, center of mass, and inertia tensor of the whole model.
 */
void rdSDFast::
getSystemInertia(double *aM,double aCOM[3],double aI[3][3])
{
	sdsys_(aM,aCOM,aI);
}


//=============================================================================
// CONFIGURATION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set the configuration of the model.
 */
void rdSDFast::
setConfiguration(const double q[],const double u[])
{
	// IN BASE CLASS
	rdModel::setConfiguration(q,u);

	// IN SDFAST
	sdstate_(&_t,_q,_u);
}
//_____________________________________________________________________________
/**
 * Set the configuration of the model.
 */
void rdSDFast::
setConfiguration(const double y[])
{
	// IN BASE CLASS
	rdModel::setConfiguration(y);

	// IN SDFAST
	sdstate_(&_t,_q,_u);
}


//=============================================================================
// DERIVATIVES
//=============================================================================
//_____________________________________________________________________________
/**
 * Compute the derivatives of the states.
 */
int rdSDFast::
computeAccelerations(double *dqdt,double *dudt)
{
	sdderiv_(dqdt,dudt);
	return(0);
}


//=============================================================================
// APPLY LOADS
//=============================================================================
//-----------------------------------------------------------------------------
// FORCES
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Apply a force to a body aBody at a point aPoint.
 *
 * The body point and force should be expressed in the body-local frame.
 */
void rdSDFast::
applyForceBodyLocal(int aBody,double aPoint[3],double aForce[3])
{
	sdpointf_(&aBody,aPoint,aForce);
}
//_____________________________________________________________________________
/**
 * Apply a set of forces to a set of bodies.
 *
 * The body points and forces should be expressed in the body-local frame.
 */
void rdSDFast::
applyForcesBodyLocal(int aN,int aBodies[],double aPoints[][3],double aForces[][3])
{
	int i;
	for(i=0;i<aN;i++) {
		applyForceBodyLocal(aBodies[i],aPoints[i],aForces[i]);
	}
}

//-----------------------------------------------------------------------------
// GLOBAL FORCES
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Apply a force expressed in the global frame to a body at a point.
 *
 * The body point, aPoint, should be expressed in the body-local frame.
 * The force, aForce, should be expressed in the global (inertial) frame.
 */
void rdSDFast::
applyForce(int aBody,double aPoint[3],double aForce[3])
{
	int ground = GROUND;
	double force[3];
	sdtrans_(&ground,aForce,&aBody,force);
	sdpointf_(&aBody,aPoint,force);
}
//_____________________________________________________________________________
/**
 * Apply forces expressed in the global frame to bodies.
 *
 * The body points, aPoint, should be expressed in the body-local frame.
 * The forces, aForce, should be expressed in the global (inertial) frame.
 */
void rdSDFast::
applyForces(int aN,int aBodies[],double aPoints[][3],double aForces[][3])
{
	int i;
	for(i=0;i<aN;i++) {
		applyForce(aBodies[i],aPoints[i],aForces[i]);
	}
}
//_____________________________________________________________________________
/**
 * Apply forces expressed in the inertial frame to bodies.
 *
 * @param aN Number of forces.
 * @param aBodes Array of body ID's.
 * @param aPoints Pointer to a sequence of points laid out as aPoints[aN][3].
 * @param aForces Pointer to a sequence of forces laid out as aForces[aN][3].
 */
void rdSDFast::
applyForces(int aN,int aBodies[],double *aPoints,double *aForces)
{
	int i,I;
	for(i=0;i<aN;i++) {
		I = rdMtx::ComputeIndex(i,3,0);
		applyForce(aBodies[i],&aPoints[I],&aForces[I]);
	}
}

//-----------------------------------------------------------------------------
// TORQUES
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Apply a torque expressed in the body-local to a body.
 *
 * @param aBody Body ID.
 * @param aTorque Torque expressed in the body-local frame.
 */
void rdSDFast::
applyTorqueBodyLocal(int aBody,double aTorque[3])
{
	sdbodyt_(&aBody,aTorque);
}

//-----------------------------------------------------------------------------
// GLOBAL TORQUES
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Apply a torque expressed in the inertial frame to a body.
 *
 * @param aBody Body ID.
 * @param aTorque Torque expressed in the inertial frame.
 */
void rdSDFast::
applyTorque(int aBody,double aTorque[3])
{
	int ground = GROUND;
	double torque[3];
	sdtrans_(&ground,aTorque,&aBody,torque);
	sdbodyt_(&aBody,torque);
}

//-----------------------------------------------------------------------------
// GENERALIZED FORCES
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Apply a generalized force to a generalized coordinate.
 * Note that depending on the axis type the generalized force can be a
 * torque or a force.
 */
void rdSDFast::
applyGeneralizedForce(int aU,double aF)
{
	int joint = _u2jMap[aU];
	int axis = _u2aMap[aU];
	sdhinget_(&joint,&axis,&aF);
}
//_____________________________________________________________________________
/**
 * Apply generalized forces.
 * The dimension of aF is assumed to be the number of generalized speeds.
 */
void rdSDFast::
applyGeneralizedForces(double aF[])
{
	int i;
	for(i=0;i<_nu;i++) applyGeneralizedForce(i,aF[i]);
}
//_____________________________________________________________________________
/**
 * Apply generalized forces.
 * The dimension of aF is assumed to be the number of generalized speeds.
 */
void rdSDFast::
applyGeneralizedForces(int aN,int aU[],double aF[])
{
	int i;
	for(i=0;i<aN;i++) applyGeneralizedForce(aU[i],aF[i]);
}


//=============================================================================
// EQUATIONS OF MOTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Form the system mass matrix.
 *
 * rI is a square matrix of size NU*NU.
 */
void rdSDFast::
formMassMatrix(double *rI)
{
	sdmassmat_(rI);
}
//_____________________________________________________________________________
/**
 * Form the transformation matrix E[3][3] that can be used to express the
 * angular velocity of a body in terms of the time derivatives of the euler
 * angles.  The Euler angle convention is body-fixed 1-2-3.
 */
void rdSDFast::
formEulerTransform(int aBody,double *rE)
{
	if(rE==NULL) return;

	// GET ORIENTATION OF aBody
	double ang[3], dc[3][3];
	sdorient_(&aBody,dc);	
	sddc2ang_(dc,&ang[0],&ang[1],&ang[2]);

	// ROW 1
	*(rE++) = cos(ang[2])/cos(ang[1]);
	*(rE++) = -sin(ang[2])/cos(ang[1]);
	*(rE++) = 0.0;

	// ROW 2
	*(rE++) = sin(ang[2]);
	*(rE++) = cos(ang[2]);
	*(rE++) = 0.0;

	// ROW 3
	*(rE++) = -cos(ang[2])*sin(ang[1])/cos(ang[1]);
	*(rE++) = sin(ang[1])*sin(ang[2])/cos(ang[1]);
	*(rE)   = 1.0;
}
//_____________________________________________________________________________
/**
 * Form the full angular velocity Jacobian matrix (J0) for a point on a body.
 *
 * Note that J0 is not appropriate for operations on the body when the body
 * orientation is specified in terms of Euler angles.  When the body
 * is described in terms of Euler angles, the method formJ should be used.
 *
 * J0 is laid out as follows:
 *		dPx/dq1	dPx/dq2	dPx/dq3	...
 *		dPy/dq1	dPy/dq2	dPy/dq3	...
 *		dPz/dq1	dPz/dq2	dPz/dq3	...
 *		dOx/dq1	dOx/dq2	dOx/dq3	...
 *		dOy/dq1	dOy/dq2	dOy/dq3	...
 *		dOz/dq1	dOz/dq2	dOz/dq3	...
 *	where P is the point on the body and O is the orientation of the body.
 *
 * So, J0 should have 6 rows and NU columns.  In memory, the column index
 * increments fastest, so the representation is J0[6][NU].
 *
 * It is assumed that enough space has been allocated at aJ to hold all
 * of the Jacobian elements.
 *
 * The Jacobian elements are expressed in the inertial or ground frame.
 */
void rdSDFast::
formJacobian(int aBody,double aPoint[3],double *rJ0)
{
	if(rJ0==NULL) return;

	int i,iu,j,I;
	int ground = GROUND;
	double trans[3],orien[3];
	for(i=0;i<getNU();i++) {

		// GET COLUMN
		iu = i + 1;
		sdrel2cart_(&iu,&aBody,aPoint,trans,orien);

		// TRANSFORM TO GROUND FRAME
		sdtrans_(&aBody,trans,&ground,trans);
		sdtrans_(&aBody,orien,&ground,orien);

		// FORM MATRIX
		for(j=0;j<3;j++) {
			I = rdMtx::ComputeIndex(j,_nu,i);
			rJ0[I] = trans[j];
			I = rdMtx::ComputeIndex(j+3,_nu,i);
			rJ0[I] = orien[j];
		}
	}

	// PRINT
	//rdMtx::Print(6,getNU(),rJ0,3);
}
//_____________________________________________________________________________
/**
 * Form the full Jacobian matrix (J) for a point on a body.
 *
 * Note that J is appropriate for operations on the body when the body
 * orientation is specified in terms of Euler angles.
 *
 * J is laid out as follows:
 *		dPx/dq1	dPx/dq2	dPx/dq3	...
 *		dPy/dq1	dPy/dq2	dPy/dq3	...
 *		dPz/dq1	dPz/dq2	dPz/dq3	...
 *		dOx/dq1	dOx/dq2	dOx/dq3	...
 *		dOy/dq1	dOy/dq2	dOy/dq3	...
 *		dOz/dq1	dOz/dq2	dOz/dq3	...
 *	where P is the point on the body and O is the orientation of the body.
 *
 * So, J should have 6 rows and NU columns.  In memory, the column index
 * increments fastest, so the representation is aJ[6][NU].
 *
 * It is assumed that enough space has been allocated at aJ to hold all
 * of the Jacobian elements.
 *
 * The Jacobian elements are expressed in the inertial or ground frame.
 */
void rdSDFast::
formJacobianEuler(int aBody,double aPoint[3],double *rJ)
{
	if(rJ==NULL) return;

	// FORM J0
	formJacobian(aBody,aPoint,rJ);

	// FORM E
	double E[3][3];
	formEulerTransform(aBody,&E[0][0]);
	printf("\nrdSDFast.formJacobianEuler:\n");
	rdMtx::Print(3,3,&E[0][0],3);

	// TRANSFORM J0 TO J
	int I = rdMtx::ComputeIndex(3,getNU(),0);
	rdMtx::Multiply(3,3,getNU(),&E[0][0],&rJ[I],&rJ[I]);

	// PRINT
	//rdMtx::Print(6,getNU(),rJ,3);
}
//_____________________________________________________________________________
/**
 * Form the generalized inverse of the Jacobian matrix, rJInv.
 *
 * rJInv has the shape rJInv[NU][6];
 *
 * rJInv = Inverse(aI) * aJT * Inverse( aJ * Inverse(aI) * JT)
 *
 * @param aI A pointer to the system mass matrix.
 * @param aJ A pointer to the system Jacobian.
 * @param aJInv A pointer to the generalized inverse of the Jacobian.
 * 
 * @return 0 when successful, -1 if an error is encountered, -2 when the
 * generalized inverse has a singularity.
 */
int rdSDFast::
formJacobianInverse(double *aI,double *aJ,double *rJInv)
{
	if(aI==NULL) return(-1);
	if(aJ==NULL) return(-1);
	if(rJInv==NULL) return(-1);

	// INVERSE OF THE MASS MATRIX
	int nu = getNU();
	double *IInv = new double[nu*nu];
	rdMtx::Invert(nu,aI,IInv);
	//printf("\nrdSDFast.formJacobianInverse: Inverse Mass Matrix...\n");
	//rdMtx::Print(nu,nu,IInv,3);

	// FORM JT (NUx6)
	double *JT = new double[nu*6];
	rdMtx::Transpose(6,nu,aJ,JT);
	//printf("\nrdSDFast.formJacobianInverse: JT...\n");
	//rdMtx::Print(nu,6,JT,3);

	// COMPUTE IInv * JT (NUx6)
	double *IInv_JT = new double[nu*6];
	rdMtx::Multiply(nu,nu,6,IInv,JT,IInv_JT);
	//printf("\nrdSDFast.formJacobianInverse: IInv_JT...\n");
	//rdMtx::Print(nu,6,IInv_JT,3);

	// COMPUTE Inverse(J * IInv * JT) (6x6)
	double J_IInv_JT[6*6];
	rdMtx::Multiply(6,nu,6,aJ,IInv_JT,J_IInv_JT);
	//printf("\nrdSDFast.formJacobianInverse: J_IInv_JT...\n");
	//rdMtx::Print(6,6,J_IInv_JT,3);
	int status = rdMtx::Invert(6,J_IInv_JT,J_IInv_JT);
	//printf("\nrdSDFast.formJacobianInverse: Inverse(J_IInv_JT)...\n");
	//rdMtx::Print(6,6,J_IInv_JT,3);

	// COMPUTE GENERALIZED INVERSE (NUx6)
	rdMtx::Multiply(nu,6,6,JT,J_IInv_JT,rJInv);
	rdMtx::Multiply(nu,nu,6,IInv,rJInv,rJInv);

	// CLEANUP
	if(IInv!=NULL) delete[] IInv;
	if(JT!=NULL) delete[] JT;
	if(IInv_JT!=NULL) delete[] IInv_JT;

	// PRINT STATUS
	if(status==-2) {
		printf("\nrdSDFast.formJcobianInverse: WARN- singularity.\n");
	}
	//printf("\nrdSDFast.formJacobianInverse:  Generalized Inverse...\n");
	//rdMtx::Print(nu,6,rJInv,3);

	return(status);
}


//=============================================================================
// UTILITY
//=============================================================================
//_____________________________________________________________________________
/**
 * Transform the orientation of a vector from one frame to another frame.
 *
 * @param aBody1 Body frame of aVec1.
 * @param aVec1 Vector whose orientation is to be transformed.
 * @param aBody2 Frame in which to express aVec1.
 * @param rVec2 Transformed vector.  It is permissible for aVec1 and aVec2 to
 * be the same vector.
 */
void rdSDFast::
	transform(int aBody1,double *aVec1,int aBody2,double *rVec2)
{
	sdtrans_(&aBody1,aVec1,&aBody2,rVec2);
}
//_____________________________________________________________________________
/**
 * Convert quaterions to angles.
 */
void rdSDFast::
convertQuaternionsToAngles(double *aQ,double *rQAng)
{
	sdst2ang_(aQ,rQAng);
}
//_____________________________________________________________________________
/**
 * Convert angles to quaterions.
 */
void rdSDFast::
convertAnglesToQuaternions(double *aQAng,double *rQ)
{
	sdang2st_(aQAng,rQ);
}
//_____________________________________________________________________________
/**
 * Convert direction cosines to Euler angles.
 * The Euler angle convention is body-fixed 1-2-3.
 *
 * @param aDirCos Matrix of direction cosines.
 * @param rE1 Euler angle about axis 1.
 * @param rE2 Euler angle about axis 2.
 * @param rE3 Euler angle about axis 3.
 */
void rdSDFast::
convertDirectionCosinesToAngles(double aDirCos[3][3],
	double *rE1,double *rE2,double *rE3)
{
	sddc2ang_(aDirCos,rE1,rE2,rE3);
}
