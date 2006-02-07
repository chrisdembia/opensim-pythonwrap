// rdModel.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2000-2003 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdModel_h__
#define __rdModel_h__

// INCLUDES
#include <NMBLTK/Simulation/rdSimulationDLL.h>
#include <iostream>
#include <string>
#include <NMBLTK/Tools/rdObject.h>
#include <NMBLTK/Tools/rdStorage.h>
#include <NMBLTK/Tools/rdArrayPtrs.h>
#include <NMBLTK/Tools/rdNamedValueArray.h>
#include "rdBodySet.h"

class rdBody;
class rdAnalysis;
class rdAnalysisSet;
class rdIntegCallback;
class rdIntegCallbackSet;
class rdDerivCallback;
class rdDerivCallbackSet;
class rdVisibleObject;
class rdMaterialSet;
class suScaleSet;

#ifdef SWIG
	#ifdef RDSIMULATION_API
		#undef RDSIMULATION_API
		#define RDSIMULATION_API
	#endif
#endif


//=============================================================================
//=============================================================================
/**
 * An abstract class that specifies the interface for a dynamic model.
 *
 * @auther Frank C. Anderson, except where noted
 * @version 1.0
 */

class RDSIMULATION_API rdModel  : public rdObject
{

//=============================================================================
// DATA
//=============================================================================
protected:
	// PROPERTIES
	/** Set of bodies. */
	rdPropertyObj _propBodySet;
	/* Materials to be used by the model */
	rdPropertyObj _propMaterialSet;
	
	// REFERENCES
	rdBodySet &_b;
	rdMaterialSet &_materialSet;

	/** Gravitational acceleration. */
	double _g[3];
	/** Time. */
	double _t;
	/** Time normalization. */
	double _tNormConst;

	/** Number of bodies */
	int _nb;
	/** Names of bodies */
	char **_bNames;

	/** Set of analyses. */
	rdAnalysisSet *_analysisSet;

	/** Set of integration callbacks. */
	rdIntegCallbackSet *_integCallbackSet;

	/** Set of derivative callbacks. */
	rdDerivCallbackSet *_derivCallbackSet;

	/** External file to write model to */
	std::string _modelDescriptionFileName;


//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION AND DESTRUCTION
	//--------------------------------------------------------------------------
public:
	rdModel();
	rdModel(const std::string &aFileName);
	rdModel(DOMElement *aElement);
	virtual ~rdModel();
private: // Not implemented
	rdModel(const rdModel& aModel);
#ifndef SWIG
	rdModel& operator=(const rdModel &aModel);
#endif
	void setNull();
	virtual void init();	
	void setupProperties();
protected:
	/* Register types to be used when reading an rdActuatedModel_SDFast object
	from xml file. */
	static void RegisterTypes();

public:
	//--------------------------------------------------------------------------
	// MODEL FILE
	//--------------------------------------------------------------------------
	/** Name of model description file to contain user preferences and external data */
	const char *getModelDescriptionFileName() const;
	void setModelDescriptionFileName(const std::string &aModelDescriptionFileName);

	//--------------------------------------------------------------------------
	// NUMBERS
	//--------------------------------------------------------------------------
	int getNB() const;	// rdModel. done.
	virtual int getNJ() const = 0; // SDFAST
	virtual int getNQ() const = 0; // SDFAST GenCoord
	virtual int getNU() const = 0; // SDFAST GenSpeeds
	virtual int getNX() const = 0; // ACTUATED MODEL Controls
	virtual int getNA() const = 0; // ACTUATED MODEL Actuators
	virtual int getNP() const = 0; // ACTUATED MODEL Contacts
	virtual int getNY() const = 0; // ACTUATED MODEL States
	virtual int getNYP() const = 0; // ACTUATED MODEL PseudoStates

	//--------------------------------------------------------------------------
	// NAMES
	//--------------------------------------------------------------------------
protected:
	virtual void setBodyName(int aIndex,const std::string &aName);
public:
	virtual void setName(const std::string &aName);
	virtual std::string getBodyName(int aIndex) const;
	virtual std::string getCoordinateName(int aIndex) const = 0;
	virtual std::string getSpeedName(int aIndex) const = 0;
	virtual std::string getActuatorName(int aIndex) const = 0;
	virtual std::string getControlName(int aIndex) const = 0;
	virtual std::string getStateName(int aIndex) const = 0;
	virtual std::string getPseudoStateName(int aIndex) const = 0;

	//--------------------------------------------------------------------------
	// INDICES FROM NAMES
	//--------------------------------------------------------------------------
	virtual int getBodyIndex(const std::string &aName) const;
	virtual int getCoordinateIndex(const std::string &aName) const = 0;
	virtual int getSpeedIndex(const std::string &aName) const = 0;
	virtual int getActuatorIndex(const std::string &aName) const = 0;
	virtual int getControlIndex(const std::string &aName) const = 0;
	virtual int getStateIndex(const std::string &aName) const = 0;
	virtual int getPseudoStateIndex(const std::string &aName) const = 0;

	//--------------------------------------------------------------------------
	// BODIES SUPPORT
	//--------------------------------------------------------------------------
	rdBody *getBody(int aIndex) const;
	virtual void constructBodies();
	rdBodySet *getBodySet();

	//--------------------------------------------------------------------------
	// MATERIALS SUPPORT
	//--------------------------------------------------------------------------
	rdMaterialSet *getMaterialSet();

	//--------------------------------------------------------------------------
	// Object Look up
	//--------------------------------------------------------------------------
	rdVisibleObject *getVisibleObjectByName(const std::string &aName) const;

	//--------------------------------------------------------------------------
	// SET CURRENT TIME, CONTROLS, AND STATES
	//--------------------------------------------------------------------------
	virtual void set(double aT,const double aX[],const double aY[]);

	//--------------------------------------------------------------------------
	// TIME
	//--------------------------------------------------------------------------
	virtual void setTime(double aT);
	double getTime() const;

	//--------------------------------------------------------------------------
	// TIME NORMALIZATION
	//--------------------------------------------------------------------------
	virtual void setTimeNormConstant(double aNormConst);
	double getTimeNormConstant() const;
	
	//--------------------------------------------------------------------------
	// CONTROLS
	//--------------------------------------------------------------------------
	virtual void setControls(const double aX[]) = 0;
	virtual void setControl(int aIndex,double aValue) = 0;
	virtual void setControl(const std::string &aName,double aValue) = 0;
	virtual void getControls(double rX[]) const = 0;
	virtual double getControl(int aIndex) const = 0;
	virtual double getControl(const std::string &aName) const = 0;

	//--------------------------------------------------------------------------
	// INITIAL STATES
	//--------------------------------------------------------------------------
	virtual void setInitialStates(const double aYI[]) = 0;
	virtual void getInitialStates(double rYI[]) const = 0;
	virtual double getInitialState(int aIndex) const = 0;
	virtual double getInitialState(const std::string &aName) const = 0;

	//--------------------------------------------------------------------------
	// STATES
	//--------------------------------------------------------------------------
	virtual void setStates(const double aY[]) = 0;
	virtual void getStates(double rY[]) const = 0;
	virtual double getState(int aIndex) const = 0;
	virtual double getState(const std::string &aName) const = 0;

	//--------------------------------------------------------------------------
	// INITIAL PSEUDO STATES
	//--------------------------------------------------------------------------
	virtual void setInitialPseudoStates(const double aYPI[]) = 0;
	virtual void getInitialPseudoStates(double rYPI[]) const = 0;
	virtual double getInitialPseudoState(int aIndex) const = 0;
	virtual double getInitialPseudoState(const std::string &aName) const = 0;

	//--------------------------------------------------------------------------
	// PSEUDO STATES
	//--------------------------------------------------------------------------
	virtual void setPseudoStates(const double aYP[]) = 0;
	virtual void getPseudoStates(double rYP[]) const = 0;
	virtual double getPseudoState(int aIndex) const = 0;
	//??virtual double getPseudoState(const std::string &aName) const = 0;

	//--------------------------------------------------------------------------
	// CONFIGURATION
	//--------------------------------------------------------------------------
	virtual void setConfiguration(const double aY[]) = 0;
	virtual void setConfiguration(const double aQ[],const double aU[]) = 0;
	virtual void getCoordinates(double rQ[]) const = 0;
	virtual double getCoordinate(int aIndex) const = 0;
	virtual double getCoordinate(const std::string &aName) const = 0;
	virtual void getSpeeds(double rU[]) const = 0;
	virtual double getSpeed(int aIndex) const = 0;
	virtual double getSpeed(const std::string &aName) const = 0;
	virtual void getAccelerations(double rDUDT[]) const = 0; // DYN
	virtual double getAcceleration(int aIndex) const = 0; // DYN
	virtual double getAcceleration(const std::string &aSpeedName) const = 0; // DYN
	virtual void
		extractConfiguration(const double aY[],double rQ[],double rU[]) const = 0;

	//--------------------------------------------------------------------------
	// ASSEMBLING THE MODEL
	//--------------------------------------------------------------------------
	virtual int assemble(double aTime,double *rState,int *aLock,double aTol,
		 int aMaxevals,int *rFcnt,int *rErr) = 0;	//DYN

	//--------------------------------------------------------------------------
	// SCALE THE MODEL
	//--------------------------------------------------------------------------
	virtual bool scale(const suScaleSet& aScaleSet) = 0;
	//--------------------------------------------------------------------------
	// GRAVITY
	//--------------------------------------------------------------------------
	virtual void getGravity(double rGrav[3]) const; // DYN
	virtual void setGravity(double aGrav[3]); // DYN

	//--------------------------------------------------------------------------
	// BODY INFORMATION
	//--------------------------------------------------------------------------
	virtual int getGroundID() const = 0;
	virtual void setBodyToJointBodyLocal(int abody,const double aBTJ[3]) = 0;
	virtual void getBodyToJointBodyLocal(int aBody,double rBTJ[3]) const = 0;
	virtual void setInboardToJointBodyLocal(int aBody,const double aBTJ[3]) = 0;
	virtual void getInboardToJointBodyLocal(int aBody,double rBTJ[3]) const = 0;
	virtual void setPin(int aBody,int aPinNumber,const double aPin[3]) = 0;
	virtual void getPin(int aBody,int aPinNumber,double rPin[3]) const = 0;
	virtual void getJointInfo(int aJoint,int rInfo[50],int rSlider[6]) const = 0;

	//--------------------------------------------------------------------------
	// INERTIA	// DYN
	//--------------------------------------------------------------------------
	virtual double getMass(int aBody) const = 0;
	virtual int getInertiaBodyLocal(int aBody,double rI[3][3]) const = 0;
	virtual int
		getInertiaBodyLocal(int aBody,double *rI) const = 0;
	virtual void
		getSystemInertia(double *rM,double rCOM[3],double rI[3][3]) const = 0;
	virtual void
		getSystemInertia(double *rM,double *rCOM,double *rI) const = 0;

	//--------------------------------------------------------------------------
	// KINEMATICS
	//--------------------------------------------------------------------------
	virtual void
		getPosition(int aBody,const double aPoint[3],double rPos[3])
		const = 0;
	virtual void
		getVelocity(int aBody,const double aPoint[3],double rVel[3])
		const = 0;
	virtual void
		getAcceleration(int aBody,const double aPoint[3],double rAcc[3]) // DYN
		const = 0;
	virtual void
		getDirectionCosines(int aBody,double rDirCos[3][3]) const = 0;
	virtual void
		getDirectionCosines(int aBody,double *rDirCos) const = 0;
	virtual void
		getAngularVelocity(int aBody,double rAngVel[3]) const = 0;
	virtual void
		getAngularVelocityBodyLocal(int aBody,double rAngVel[3]) const = 0;
	virtual void
		getAngularAcceleration(int aBody,double rAngAcc[3]) const = 0; // DYN
	virtual void
		getAngularAccelerationBodyLocal(int aBody,double rAngAcc[3]) const = 0; // DYN

	//--------------------------------------------------------------------------
	// LOAD APPLICATION
	//--------------------------------------------------------------------------
	// FORCES EXPRESSED IN INERTIAL FRAME
	virtual void 
		applyForce(int aBody,const double aPoint[3],const double aForce[3]) = 0; // DYN
	virtual void 
		applyForces(int aN,const int aBodies[],const double aPoints[][3],
		const double aForces[][3]) = 0; // DYN
	virtual void 
		applyForces(int aN,const int aBodies[],const double *aPoints,
		const double *aForces) = 0; // DYN

	// FORCES EXPRESSED IN BODY-LOCAL FRAME
	virtual void
		applyForceBodyLocal(int aBody,const double aPoint[3],
		const double aForce[3]) = 0; // DYN
	virtual void 
		applyForcesBodyLocal(int aN,const int aBodies[],
		const double aPoints[][3],const double aForces[][3])= 0; // DYN
	virtual void 
		applyForcesBodyLocal(int aN,const int aBodies[],const double *aPoints,
		const double *aForces) = 0; // DYN

	// TORQUES EXPRESSED IN INERTIAL FRAME
	virtual void
		applyTorque(int aBody,const double aTorque[3]) = 0; // DYN
	virtual void
		applyTorques(int aN,const int aBodies[],const double aTorques[][3]) = 0; // DYN
	virtual void
		applyTorques(int aN,const int aBodies[],const double *aTorques) = 0; // DYN

	// TORQUES EXPRESSED IN BODY-LOCAL FRAME (sdbodyt())
	virtual void
		applyTorqueBodyLocal(int aBody,const double aTorque[3]) = 0; // DYN
	virtual void
		applyTorquesBodyLocal(int aN,const int aBodies[],
		const double aTorques[][3]) = 0; // DYN
	virtual void
		applyTorquesBodyLocal(int aN,const int aBodies[],
		const double *aTorques) = 0; // DYN

	// GENERALIZED FORCES
	virtual void 
		applyGeneralizedForce(int aU,double aF) = 0; // DYN
	virtual void
		applyGeneralizedForces(const double aF[]) = 0; // DYN
	virtual void 
		applyGeneralizedForces(int aN,const int aU[],const double aF[]) = 0; // DYN

	//--------------------------------------------------------------------------
	// LOAD ACCESS AND COMPUTATION
	//--------------------------------------------------------------------------
	virtual double
		getNetAppliedGeneralizedForce(int aU) const = 0; // DYN
	virtual void
		computeGeneralizedForces(double aDUDT[],double rF[]) const = 0; // DYN
	virtual void
		computeReactions(double rForces[][3],double rTorques[][3]) const = 0; // DYN

	//--------------------------------------------------------------------------
	// PRESCRIBED MOTION
	//--------------------------------------------------------------------------
	virtual void
		prescribeMotion(int aJoint,int aAxis,int aPrescribed) = 0;  // DYN

	//--------------------------------------------------------------------------
	// EQUATIONS OF MOTION
	//--------------------------------------------------------------------------
	virtual void formMassMatrix(double *rI) = 0; // DYN
	virtual void formEulerTransform(int aBody,double *rE) const = 0; // DYN
	virtual void
		formJacobianTranslation(int aBody,const double aPoint[3],double *rJ,
		int aRefBody=-1) const = 0; // DYN
	virtual void
		formJacobianOrientation(int aBody,double *rJ0,int aRefBody=-1) const = 0; // DYN
	virtual void 
		formJacobianEuler(int aBody,double *rJE,int aRefBody=-1) const = 0; // DYN
	static int
		ComputeEffectiveMassMatrix(int aNJX,int aNU,const double *aJ,
		const double *aIinv,double *rIeff); // DYN
	static int
		ComputeJacobianInverse(int aNJX,int aNU,const double *aJ,
		const double *aI,double *rJInv); // DYN


	//--------------------------------------------------------------------------
	// DERIVATIVES
	//--------------------------------------------------------------------------
	virtual int
		computeAccelerations(double *dqdt,double *dudt) = 0; // DYN
	virtual void
		computeAuxiliaryDerivatives(double *dydt) = 0;  // DYN


	//--------------------------------------------------------------------------
	// OPTIMIZATION
	//--------------------------------------------------------------------------
	virtual void
		promoteControlsToStates(const double aX[],double aDT);
	virtual int
		computePerformance(double t,double *x,double *y,double *p,
		void *cd=NULL);
	virtual int
		computeConstraint(double t,double *x,double *y,int ic,double *c,
		void *cd=NULL);

	//--------------------------------------------------------------------------
	// UTILITY
	//--------------------------------------------------------------------------
	virtual void
		transform(int aBody1,const double aVec1[3],int aBody2,
		double rVec2[3]) const = 0;
	virtual void
		transformPosition(int aBody,const double aPos[3],double rPos[3]) const = 0;

	virtual void
		convertQuaternionsToAngles(double *aQ,double *rQAng) const = 0;
	virtual void
		convertQuaternionsToAngles(rdStorage *rQStore) const = 0;
	virtual void
		convertAnglesToQuaternions(double *aQAng,double *rQ) const = 0;
	virtual void
		convertAnglesToQuaternions(rdStorage *rQStore) const = 0;

	virtual void
		convertRadiansToDegrees(double *aQRad,double *rQDeg) const = 0;
	virtual void
		convertRadiansToDegrees(rdStorage *rQStore) const = 0;
	virtual void
		convertDegreesToRadians(double *aQDeg,double *rQRad) const = 0;
	virtual void
		convertDegreesToRadians(rdStorage *rQStore) const = 0;

	virtual void
		convertAnglesToDirectionCosines(double aE1,double aE2,double aE3,
		double rDirCos[3][3]) const = 0;
	virtual void
		convertAnglesToDirectionCosines(double aE1,double aE2,double aE3,
		double *rDirCos) const = 0;

	virtual void
		convertDirectionCosinesToAngles(double aDirCos[3][3],
		double *rE1,double *rE2,double *rE3) const = 0;
	virtual void
		convertDirectionCosinesToAngles(double *aDirCos,
		double *rE1,double *rE2,double *rE3) const = 0;

	virtual void
		convertDirectionCosinesToQuaternions(double aDirCos[3][3],
		double *rQ1,double *rQ2,double *rQ3,double *rQ4) const = 0;
	virtual void
		convertDirectionCosinesToQuaternions(double *aDirCos,
		double *rQ1,double *rQ2,double *rQ3,double *rQ4) const = 0;

	virtual void
		convertQuaternionsToDirectionCosines(
		double aQ1,double aQ2,double aQ3,double aQ4,double rDirCos[3][3])
		const = 0;
	virtual void
		convertQuaternionsToDirectionCosines(
		double aQ1,double aQ2,double aQ3,double aQ4,double *rDirCos)
		const = 0;

	//--------------------------------------------------------------------------
	// ACTUATION
	//--------------------------------------------------------------------------
	virtual void computeActuation();
	virtual void applyActuatorForce(int aID); // DYN
	virtual void applyActuatorForces(); // DYN
	virtual void setActuatorForce(int aID,double aForce);
	virtual double getActuatorForce(int aID) const;
	virtual double getActuatorStress(int aID) const;
	virtual double getActuatorSpeed(int aID) const;
	virtual double getActuatorPower(int aID) const;

	//--------------------------------------------------------------------------
	// CONTACT
	//--------------------------------------------------------------------------
	virtual void
		computeContact();
	virtual void
		applyContactForce(int aID); // DYN
	virtual void
		applyContactForces(); // DYN
	virtual int
		getContactBodyA(int aID) const;
	virtual int
		getContactBodyB(int aID) const;
	virtual void
		setContactPointA(int aID,const double aPoint[3]);
	virtual void
		getContactPointA(int aID,double rPoint[3]) const;
	virtual void
		setContactPointB(int aID,const double aPoint[3]);
	virtual void
		getContactPointB(int aID,double rPoint[3]) const;
	virtual void
		getContactForce(int aID,double rF[3]) const;
	virtual void
		getContactNormalForce(int aID,double rFP[3],double rFV[3],double rF[3])
		const;
	virtual void
		getContactTangentForce(int aID,double rFP[3],double rFV[3],double rF[3])
		const;
	virtual void
		getContactStiffness(int aID,const double aDX[3],double rDF[3]) const;
	virtual void
		getContactViscosity(int aID,const double aDV[3],double rDF[3]) const;
	virtual void
		getContactFrictionCorrection(int aID,double aDFFric[3]) const;
	virtual double
		getContactForce(int aID) const;
	virtual double
		getContactSpeed(int aID) const;
	virtual double
		getContactPower(int aID) const;

	//--------------------------------------------------------------------------
	// ANALYSES
	//--------------------------------------------------------------------------
	rdAnalysisSet *getAnalysisSet();
	void addAnalysis(rdAnalysis *aAnalysis);
	// Added to support recovering the analyses from the Gui
	int  getNumAnalyses() const;
	rdAnalysis& getAnalysis(const int index) const;

	//--------------------------------------------------------------------------
	// INTEGRATION CALLBACKS
	//--------------------------------------------------------------------------
	rdIntegCallbackSet* getIntegCallbackSet();
	void addIntegCallback(rdIntegCallback *aCallback);

	//--------------------------------------------------------------------------
	// DERIVATIVE CALLBACKS
	//--------------------------------------------------------------------------
	rdDerivCallbackSet *getDerivCallbackSet();
	void addDerivCallback(rdDerivCallback *aCallback);

	//--------------------------------------------------------------------------
	// FOR RRA - ADDED BY CHAND, 2/3/2006
	//--------------------------------------------------------------------------
	virtual void setIncludePipelineActuators(bool include);
	virtual void computeConstrainedCoordinates(double* y);

	//--------------------------------------------------------------------------
	// PRINT
	//--------------------------------------------------------------------------
	void printBasicInfo(std::ostream &aOStream) const;
	void printDetailedInfo(std::ostream &aOStream) const;

//=============================================================================
};	// END of class rdModel
//=============================================================================
//=============================================================================


#endif // __rdModel_h__


