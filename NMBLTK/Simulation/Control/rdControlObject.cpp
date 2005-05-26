// rdControlObject.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2003-2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fc.anderson@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include "rdControlObject.h"
#include <NMBLTK/Simulation/Model/rdModel.h>
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Tools/rdMtx.h>


//=============================================================================
// STATICS
//=============================================================================
const char rdControlObject::DEFAULT_NAME[] = "default";
const char rdControlObject::PROP_ON[] = "on";
const char rdControlObject::PROP_WRT_BODY[] = "wrt_body";
const char rdControlObject::PROP_EXPRESS_BODY[] = "express_body";
const char rdControlObject::PROP_ACTIVE[] = "active";
const char rdControlObject::PROP_W[] = "weight";
const char rdControlObject::PROP_KP[] = "kp";
const char rdControlObject::PROP_KV[] = "kv";
const char rdControlObject::PROP_KA[] = "ka";
const char rdControlObject::PROP_R0[] = "R0";
const char rdControlObject::PROP_R1[] = "R1";
const char rdControlObject::PROP_R2[] = "R2";


//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
rdControlObject::~rdControlObject()
{
	if(_pTrk[0]!=NULL) { delete _pTrk[0];  _pTrk[0]=NULL; }
	if(_pTrk[1]!=NULL) { delete _pTrk[1];  _pTrk[1]=NULL; }
	if(_pTrk[2]!=NULL) { delete _pTrk[2];  _pTrk[2]=NULL; }
	if(_vTrk[0]!=NULL) { delete _vTrk[0];  _vTrk[0]=NULL; }
	if(_vTrk[1]!=NULL) { delete _vTrk[1];  _vTrk[1]=NULL; }
	if(_vTrk[2]!=NULL) { delete _vTrk[2];  _vTrk[2]=NULL; }
	if(_aTrk[0]!=NULL) { delete _aTrk[0];  _aTrk[0]=NULL; }
	if(_aTrk[1]!=NULL) { delete _aTrk[1];  _aTrk[1]=NULL; }
	if(_aTrk[2]!=NULL) { delete _aTrk[2];  _aTrk[2]=NULL; }
}
//_____________________________________________________________________________
/**
 * Construct a default track object for a specified model.
 *
 * @param aModel Model for which tracking is being conducted.
 */
rdControlObject::rdControlObject()
{
	setNull();
}
//_____________________________________________________________________________
/**
 * Construct a track object from an XML Element.
 *
 * @param aModel Model for which tracking is being conducted.
 * @param aElement XML element.
 */
rdControlObject::
rdControlObject(DOMElement *aElement) :
	rdObject(aElement)
{
	setNull();
	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aTrackObject Track object to be copied.
 */
rdControlObject::rdControlObject(const rdControlObject &aTrackObject) :
	rdObject(aTrackObject)
{
	setNull();
	copyData(aTrackObject);
}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set NULL values for all member variables.
 */
void rdControlObject::
setNull()
{
	setType("rdTrackObject");
	setName(DEFAULT_NAME);

	_model = NULL;
	_wrtBody = -1;
	_expressBody = -1;
	_on = true;
	_active[0] = _active[1] = _active[2] = false;
	_w[0] = _w[1] = _w[2] = 1.0;
	_kp[0] = _kp[1] = _kp[2] = 1.0;
	_kv[0] = _kv[1] = _kv[2] = 0.5;
	_ka[0] = _ka[1] = _ka[2] = 1.0;
	_r[0][0] = _r[0][1] = _r[0][2] = 0.0;
	_r[1][0] = _r[1][1] = _r[1][2] = 0.0;
	_r[2][0] = _r[2][1] = _r[2][2] = 0.0;
	_nTrk = 0;
	_pTrk[0] = _pTrk[1] = _pTrk[2] = NULL;
	_vTrk[0] = _vTrk[1] = _vTrk[2] = NULL;
	_aTrk[0] = _aTrk[1] = _aTrk[2] = NULL;
	_pErrLast[0] = _pErrLast[1] = _pErrLast[2] = 0.0;
	_pErr[0] = _pErr[1] = _pErr[2] = 0.0;
	_vErrLast[0] = _vErrLast[1] = _vErrLast[2] = 0.0;
	_vErr[0] = _vErr[1] = _vErr[2] = 0.0;
	_aDes[0] = _aDes[1] = _aDes[2] = 0.0;
	_a[0] = _a[1] = _a[2] = 0.0;
	_j = NULL;
	_m = NULL;
}

//_____________________________________________________________________________
/**
 * Copy the member data for this class only.
 *
 * @param aTrackObject Object whose data is to be copied.
 */
void rdControlObject::
copyData(const rdControlObject &aTrackObject)
{
	int i;
	_model = aTrackObject.getModel();
	setWRTBody(aTrackObject.getWRTBody());
	setExpressBody(aTrackObject.getExpressBody());
	setOn(aTrackObject.getOn());
	for(i=0;i<3;i++) _active[i] = aTrackObject.getActive(i);
	for(i=0;i<3;i++) _kp[i] = aTrackObject.getKP(i);
	for(i=0;i<3;i++) _kv[i] = aTrackObject.getKV(i);
	for(i=0;i<3;i++) _ka[i] = aTrackObject.getKA(i);
	aTrackObject.getDirection_0(_r[0]);
	aTrackObject.getDirection_1(_r[1]);
	aTrackObject.getDirection_2(_r[2]);

	// FUNCTIONS
	const rdFunction *func;
	for(i=0;i<3;i++) {
		// position
		if(_pTrk[i]!=NULL) {delete _pTrk[i];  _pTrk[i]=NULL; }
		func = aTrackObject.getTrackFunction(i);
		if(func!=NULL) _pTrk[i] = (rdFunction*) func->copy();
		// velocity
		if(_vTrk[i]!=NULL) {delete _vTrk[i];  _vTrk[i]=NULL; }
		func = aTrackObject.getTrackFunctionForVelocity(i);
		if(func!=NULL) _vTrk[i] = (rdFunction*) func->copy();
		// acceleration
		if(_aTrk[i]!=NULL) {delete _aTrk[i];  _aTrk[i]=NULL; }
		func = aTrackObject.getTrackFunctionForAcceleration(i);
		if(func!=NULL) _aTrk[i] = (rdFunction*) func->copy();
	}
}


//=============================================================================
// OPERATORS
//=============================================================================
//-----------------------------------------------------------------------------
// ASSIGNMENT
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Assignment operator.
 *
 * @return  Reference to the altered object.
 */
rdControlObject& rdControlObject::
operator=(const rdControlObject &aObject)
{
	// BASE CLASS
	rdObject::operator =(aObject);

	// DATA
	copyData(aObject);

	return(*this);
}


//=============================================================================
// GET AND SET
//=============================================================================
//-----------------------------------------------------------------------------
// MODEL
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the model to which this track object applies.
 *
 * @param aModel Model.
 */
void rdControlObject::
setModel(rdModel *aModel)
{
	_model = aModel;
}

//_____________________________________________________________________________
/**
 * Get the model to which this track object applies.
 *
 * @return Pointer to the model.
 */
rdModel* rdControlObject::
getModel() const
{
	return(_model);
}

//-----------------------------------------------------------------------------
// ON/OFF
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Turn this track object on or off.
 *
 * @param aTureFalse Turns analysis on if "true" and off if "false".
 */
void rdControlObject::
setOn(bool aTrueFalse)
{
	_on = aTrueFalse;
}
//_____________________________________________________________________________
/**
 * Get whether or not this track object is on.
 *
 * @return True if on, false if off.
 */
bool rdControlObject::
getOn() const
{
	return(_on);
}

//-----------------------------------------------------------------------------
// WRT BODY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the body with respect to (WRT) which the track goals are specified.
 *
 * @param aBody Body ID.
 */
void rdControlObject::
setWRTBody(int aBody)
{
	_wrtBody = aBody;
}
//_____________________________________________________________________________
/**
 * Get the body with respect to (WRT) which the track goals are specified.
 *
 * @return Body ID.
 */
int rdControlObject::
getWRTBody() const
{
	return(_wrtBody);
}

//-----------------------------------------------------------------------------
// EXPRESS BODY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the body in which the track goals are expressed.
 *
 * @param aBody Body ID.
 */
void rdControlObject::
setExpressBody(int aBody)
{
	_expressBody = aBody;
}
//_____________________________________________________________________________
/**
 * Get the body in which the track goals are expressed.
 *
 * @return Body ID.
 */
int rdControlObject::
getExpressBody() const
{
	return(_expressBody);
}

//-----------------------------------------------------------------------------
// ACTIVE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set whether or not track goals are active.
 *
 * @param a0 Active flag for track goal 0-- true means active.
 * @param a1 Active flag for track goal 1-- true means active.
 * @param a2 Active flag for track goal 2-- true means active.
 */
void rdControlObject::
setActive(bool a0,bool a1,bool a2)
{
	_active[0] = a0;
	_active[1] = a1;
	_active[2] = a2;
}
//_____________________________________________________________________________
/**
 * Get whether a specified track goal is active.
 *
 * @param aWhich Number of the track goal in question.
 * @return True if the specified track goal is active, false otherwise.
 */
bool rdControlObject::
getActive(int aWhich) const
{
	if(aWhich<0) return(false);
	if(aWhich>2) return(false);
	return(_active[aWhich]);
}

//-----------------------------------------------------------------------------
// WEIGHTS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the weight of each track goal.
 *
 * @param aW0 Weight for track goal 0.
 * @param aW1 Weight for track goal 1.
 * @param aW2 Weight for track goal 2.
 */
void rdControlObject::
setWeight(double aW0,double aW1,double aW2)
{
	_w[0] = aW0;
	_w[1] = aW1;
	_w[2] = aW2;
}
//_____________________________________________________________________________
/**
 * Get the weight of each track goal.
 *
 * @param aWhich Number of the track goal in question.
 * @return Weight.
 */
double rdControlObject::
getWeight(int aWhich) const
{
	if(aWhich<0) return(0.0);
	if(aWhich>2) return(0.0);
	return(_w[aWhich]);
}

//-----------------------------------------------------------------------------
// POSITION GAINS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the position gains for each track goal.
 *
 * @param aK0 Gain for track goal 0.
 * @param aK1 Gain for track goal 1.
 * @param aK2 Gain for track goal 2.
 */
void rdControlObject::
setKP(double aK0,double aK1,double aK2)
{
	_kp[0] = aK0;
	_kp[1] = aK1;
	_kp[2] = aK2;
}
//_____________________________________________________________________________
/**
 * Get the position gain for a specified track goal.
 *
 * @param aWhich Number of the track goal in question.
 * @return Position gain.
 */
double rdControlObject::
getKP(int aWhich) const
{
	if(aWhich<0) return(0.0);
	if(aWhich>2) return(0.0);
	return(_kp[aWhich]);
}

//-----------------------------------------------------------------------------
// VELOCITY GAINS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the velocity gains for each track goal.
 *
 * @param aK0 Gain for track goal 0.
 * @param aK1 Gain for track goal 1.
 * @param aK2 Gain for track goal 2.
 */
void rdControlObject::
setKV(double aK0,double aK1,double aK2)
{
	_kv[0] = aK0;
	_kv[1] = aK1;
	_kv[2] = aK2;
}
//_____________________________________________________________________________
/**
 * Get the velocity gain for a specified track goal.
 *
 * @param aWhich Number of the track goal in question.
 * @return Velocity gain.
 */
double rdControlObject::
getKV(int aWhich) const
{
	if(aWhich<0) return(0.0);
	if(aWhich>2) return(0.0);
	return(_kv[aWhich]);
}

//-----------------------------------------------------------------------------
// ACCELERATION GAINS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the acceleration gains for each track goal.
 *
 * @param aK0 Gain for track goal 0.
 * @param aK1 Gain for track goal 1.
 * @param aK2 Gain for track goal 2.
 */
void rdControlObject::
setKA(double aK0,double aK1,double aK2)
{
	_ka[0] = aK0;
	_ka[1] = aK1;
	_ka[2] = aK2;
}
//_____________________________________________________________________________
/**
 * Get the acceleration gain for a specified track goal.
 *
 * @param aWhich Number of the track goal in question.
 * @return Acceleration gain.
 */
double rdControlObject::
getKA(int aWhich) const
{
	if(aWhich<0) return(0.0);
	if(aWhich>2) return(0.0);
	return(_ka[aWhich]);
}

//-----------------------------------------------------------------------------
// DIRECTION 0
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the direction of track goal 0.
 *
 * @param aR Direction.  This vector is normalized.
 */
void rdControlObject::
setDirection_0(const double aR[3])
{
	if(aR==NULL) {
		_r[0][0] = _r[0][1] = _r[0][2] = 0.0;
		return;
	}
	rdMtx::Normalize(3,aR,_r[0]);
}
//_____________________________________________________________________________
/**
 * Get the direction of track goal 0.
 *
 * @param aR Direction.
 */
void rdControlObject::
getDirection_0(double rR[3]) const
{
	if(rR==NULL) return;
	rdMtx::Assign(1,3,_r[0],rR);
}

//-----------------------------------------------------------------------------
// DIRECTION 1
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the direction of track goal 1.
 *
 * @param aR Direction.  This vector is normalized.
 */
void rdControlObject::
setDirection_1(const double aR[3])
{
	if(aR==NULL) {
		_r[1][0] = _r[1][1] = _r[1][2] = 0.0;
		return;
	}
	rdMtx::Normalize(3,aR,_r[1]);
}
//_____________________________________________________________________________
/**
 * Get the direction of track goal 1.
 *
 * @param aR Direction.
 */
void rdControlObject::
getDirection_1(double rR[3]) const
{
	if(rR==NULL) return;
	rdMtx::Assign(1,3,_r[1],rR);
}

//-----------------------------------------------------------------------------
// DIRECTION 2
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the direction of track goal 2.
 *
 * @param aR Direction.  This vector is normalized.
 */
void rdControlObject::
setDirection_2(const double aR[3])
{
	if(aR==NULL) {
		_r[2][0] = _r[2][1] = _r[2][2] = 0.0;
		return;
	}
	rdMtx::Normalize(3,aR,_r[2]);
}
//_____________________________________________________________________________
/**
 * Get the direction of track goal 2.
 *
 * @param aR Direction.
 */
void rdControlObject::
getDirection_2(double rR[3]) const
{
	if(rR==NULL) return;
	rdMtx::Assign(1,3,_r[2],rR);
}

//-----------------------------------------------------------------------------
// NUMBER OF TRACK FUNCTIONS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the number of position track functions.
 *
 * @return Number of position track functions.
 */
int rdControlObject::
getNumTrackFunctions() const
{
	return(_nTrk);
}

//-----------------------------------------------------------------------------
// TRACK FUNCTIONS - POSITION
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the track functions.  Note that this method makes copies of the
 * specified track functions, so the caller may use the specified functions
 * for whatever purposes.
 *
 * @param aF0 Function for track goal 0.
 * @param aF1 Function for track goal 1.
 * @param aF2 Function for track goal 2.
 */
void rdControlObject::
setTrackFunctions(rdFunction *aF0,rdFunction *aF1,rdFunction *aF2)
{
	if(_pTrk[0]!=NULL) { delete _pTrk[0];  _pTrk[0]=NULL; }
	if(_pTrk[1]!=NULL) { delete _pTrk[1];  _pTrk[1]=NULL; }
	if(_pTrk[2]!=NULL) { delete _pTrk[2];  _pTrk[2]=NULL; }

	if(aF0!=NULL) _pTrk[0] = (rdFunction*)aF0->copy();
	if(aF1!=NULL) _pTrk[1] = (rdFunction*)aF1->copy();
	if(aF2!=NULL) _pTrk[2] = (rdFunction*)aF2->copy();
}
//_____________________________________________________________________________
/**
 * Get a specified track function.
 *
 * @param aWhich Specifies which track function (0, 1, or 2).
 * @return Function.
 */
rdFunction* rdControlObject::
getTrackFunction(int aWhich) const
{
	if(aWhich<0) return(NULL);
	if(aWhich>2) return(NULL);
	return(_pTrk[aWhich]);
}

//-----------------------------------------------------------------------------
// TRACK FUNCTIONS - VELOCITY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the velocity track functions.  Note that this method makes copies of the
 * specified functions, so the caller may use the specified functions
 * for whatever purposes.
 *
 * @param aF0 Function for track goal 0.
 * @param aF1 Function for track goal 1.
 * @param aF2 Function for track goal 2.
 */
void rdControlObject::
setTrackFunctionsForVelocity(rdFunction *aF0,rdFunction *aF1,rdFunction *aF2)
{
	if(_vTrk[0]!=NULL) { delete _vTrk[0];  _vTrk[0]=NULL; }
	if(_vTrk[1]!=NULL) { delete _vTrk[1];  _vTrk[1]=NULL; }
	if(_vTrk[2]!=NULL) { delete _vTrk[2];  _vTrk[2]=NULL; }

	if(aF0!=NULL) _vTrk[0] = (rdFunction*)aF0->copy();
	if(aF1!=NULL) _vTrk[1] = (rdFunction*)aF1->copy();
	if(aF2!=NULL) _vTrk[2] = (rdFunction*)aF2->copy();
}
//_____________________________________________________________________________
/**
 * Get a specified velocity track function.
 *
 * @param aWhich Specifies which track function (0, 1, or 2).
 * @return Function.
 */
rdFunction* rdControlObject::
getTrackFunctionForVelocity(int aWhich) const
{
	if(aWhich<0) return(NULL);
	if(aWhich>2) return(NULL);
	return(_vTrk[aWhich]);
}

//-----------------------------------------------------------------------------
// TRACK FUNCTIONS - POSITION
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the acceleration track functions.  Note that this method makes copies of
 * the specified track functions, so the caller may use the specified functions
 * for whatever purposes.
 *
 * @param aF0 Function for track goal 0.
 * @param aF1 Function for track goal 1.
 * @param aF2 Function for track goal 2.
 */
void rdControlObject::
setTrackFunctionsForAcceleration(
	rdFunction *aF0,rdFunction *aF1,rdFunction *aF2)
{
	if(_aTrk[0]!=NULL) { delete _aTrk[0];  _aTrk[0]=NULL; }
	if(_aTrk[1]!=NULL) { delete _aTrk[1];  _aTrk[1]=NULL; }
	if(_aTrk[2]!=NULL) { delete _aTrk[2];  _aTrk[2]=NULL; }

	if(aF0!=NULL) _aTrk[0] = (rdFunction*)aF0->copy();
	if(aF1!=NULL) _aTrk[1] = (rdFunction*)aF1->copy();
	if(aF2!=NULL) _aTrk[2] = (rdFunction*)aF2->copy();
}
//_____________________________________________________________________________
/**
 * Get a specified acceleration track function.
 *
 * @param aWhich Specifies which track function (0, 1, or 2).
 * @return Function.
 */
rdFunction* rdControlObject::
getTrackFunctionForAcceleration(int aWhich) const
{
	if(aWhich<0) return(NULL);
	if(aWhich>2) return(NULL);
	return(_aTrk[aWhich]);
}

//-----------------------------------------------------------------------------
// LAST POSITION ERRORS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the last achieved position error.  This information is useful for
 * checking that error dynamics are being followed.
 *
 * @param aE0 Last position error for track goal 0.
 * @param aE1 Last position error for track goal 1.
 * @param aE2 Last position error for track goal 2.
 */
void rdControlObject::
setPositionErrorLast(double aE0,double aE1,double aE2)
{
	_pErrLast[0] = aE0;
	_pErrLast[1] = aE1;
	_pErrLast[2] = aE2;
}
//_____________________________________________________________________________
/**
 * Get the last achieved position error.  This information is useful for
 * checking that error dynamics are being followed.
 *
 * @param aWhich Specifies which track goal (0, 1, or 2).
 * @return Last position error.
 */
double rdControlObject::
getPositionErrorLast(int aWhich) const
{
	if(aWhich<0) return(0.0);
	if(aWhich>2) return(0.0);
	return(_pErrLast[aWhich]);
}

//-----------------------------------------------------------------------------
// LAST VELOCITY ERRORS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the last achieved velocity error.  This information is useful for
 * checking that error dynamics are being followed.
 *
 * @param aE0 Last velocity error for track goal 0.
 * @param aE1 Last velocity error for track goal 1.
 * @param aE2 Last velocity error for track goal 2.
 */
void rdControlObject::
setVelocityErrorLast(double aE0,double aE1,double aE2)
{
	_vErrLast[0] = aE0;
	_vErrLast[1] = aE1;
	_vErrLast[2] = aE2;
}
//_____________________________________________________________________________
/**
 * Get the last achieved velocity error.  This information is useful for
 * checking that error dynamics are being followed.
 *
 * @param aWhich Specifies which track goal (0, 1, or 2).
 * @return Last velocity error.
 */
double rdControlObject::
getVelocityErrorLast(int aWhich) const
{
	if(aWhich<0) return(0.0);
	if(aWhich>2) return(0.0);
	return(_vErrLast[aWhich]);
}

//-----------------------------------------------------------------------------
// TRACK ERRORS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the position track error of a specified track goal.
 *
 * @param aWhich Specifies which track goal (0, 1, or 2).
 * @return Error
 */
double rdControlObject::
getPositionError(int aWhich) const
{
	if(aWhich<0) return(0.0);
	if(aWhich>2) return(0.0);
	return(_pErr[aWhich]);
}
//_____________________________________________________________________________
/**
 * Get the velocity track error of a specified track goal.
 *
 * @param aWhich Specifies which track goal (0, 1, or 2).
 * @return Error
 */
double rdControlObject::
getVelocityError(int aWhich) const
{
	if(aWhich<0) return(0.0);
	if(aWhich>2) return(0.0);
	return(_vErr[aWhich]);
}

//-----------------------------------------------------------------------------
// DESIRED ACCELERATION
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the desired acceleration of a specified track goal.
 * The method computeDesiredAccelerations() must be called first for the
 * values returned by this method to be valid.
 *
 * @param aWhich Specifies which track goal (0, 1, or 2).
 * @return Desired acceleration.  rdMath::NAN is returned on an error.
 */
double rdControlObject::
getDesiredAcceleration(int aWhich) const
{
	if(aWhich<0) return(rdMath::NAN);
	if(aWhich>2) return(rdMath::NAN);
	return(_aDes[aWhich]);
}

//-----------------------------------------------------------------------------
// ACCELERATION
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the acceleration of a specified track goal.  The acceleration returned
 * is the dot product of the appropriate track-goal direction and the
 * acceleration of the point or orientation in question.  In the case of
 * generalized coordinates, the acceleration of the generalized coordinate
 * is returned (i.e., a direction is not appropriate).
 *
 * For the value returned by this method to be valid, the method
 * computeAccelerations() must be called first.
 *
 * @param aWhich Specifies which track goal (0, 1, or 2).
 * @return Acceleration.  rdMath::NAN is returned on an error.
 */
double rdControlObject::
getAcceleration(int aWhich) const
{
	if(aWhich<0) return(rdMath::NAN);
	if(aWhich>2) return(rdMath::NAN);
	return(_a[aWhich]);
}


//=============================================================================
// COMPUTATIONS
//=============================================================================
//-----------------------------------------------------------------------------
// JACOBIAN
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Compute the Jacobian.
 */
void rdControlObject::
computeJacobian()
{
	printf("rdControlObject.computeJacobian: ERROR- this method should be ");
	printf("overriden in derived classes.\n");
}

//-----------------------------------------------------------------------------
// EFFECTIVE MASS MATRIX
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Compute the effective mass matrix.
 */
void rdControlObject::
computeEffectiveMassMatrix()
{
	printf("rdControlObject.computeEffectiveMassMatrix: ERROR- this method ");
	printf("should be overriden in derived classes.\n");
}
