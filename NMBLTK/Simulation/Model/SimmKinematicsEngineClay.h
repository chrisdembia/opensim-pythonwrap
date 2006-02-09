// SimmKinematicsEngine.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2005 Frank C. Anderson, Ayman Habib, Peter Loan
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __SimmKinematicsEngine_h__
#define __SimmKinematicsEngine_h__

// INCLUDES
#include <NMBLTK/Simulation/rdSimulationDLL.h>
#include <iostream>
#include <string>
#include <NMBLTK/Tools/rdObject.h>
#include <NMBLTK/Tools/rdArrayPtrs.h>
#include "SimmBodySet.h"

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
 * An abstract class that specifies the interface for a kinematics engine.
 * A kinematics engine is used to compute the positions, velocities, and
 * accelerations of bodies and points on bodies in an aticulated linkage.
 *
 * At a minimum, a kinematics engine must contain a description of the
 * topology of the articulated linkage.  That is, how many bodies and how
 * those bodies are connected.
 *
 * @auther Frank C. Anderson, except where noted
 * @version 1.0
 */

class RDSIMULATION_API SimmKinematicsEngine  : public KinematicsEngine
{

//=============================================================================
// DATA
//=============================================================================
protected:
	// PROPERTIES
	/** Set of bodies. */
	rdPropertyObj _propBodySet;
	/** Set of joints. */
	rdPropertyObj _propJointSet;
	/** Set of generalized coordinates. */
	rdPropertyObj _propCoordinateSet;
	/** Set of constraint objects. */
	rdPropertyObj _propConstraintSet;

	// REFERENCES
	BodySet &_bodySet;
	JointSet &_jointSet;
	CoordinateSet &_coordinateSet;
	ConstraintSet &_constraintSet;


//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION AND DESTRUCTION
	//--------------------------------------------------------------------------
public:
	SimmKinematicsEngine();
	SimmKinematicsEngine(const std::string &aFileName);
	SimmKinematicsEngine(DOMElement *aElement);
	virtual ~SimmKinematicsEngine();
private:
	SimmKinematicsEngine(const SimmKinematicsEngine& aEngine);
#ifndef SWIG
	SimmKinematicsEngine& operator=(const SimmKinematicsEngine &aEngine);
#endif
	void setNull();
	void setupProperties();
protected:
	/* Register types to be used when reading an rdActuatedModel_SDFast object
	from xml file. */
	static void RegisterTypes();

public:

	//--------------------------------------------------------------------------
	// NUMBERS
	//--------------------------------------------------------------------------
	int getNumBodies() const;	// SimmKinematicsEngine. done.
	virtual int getNumJoints() const = 0; // SDFAST
	virtual int getNumCoordinates() const = 0; // SDFAST GenCoord
	virtual int getNumSpeeds() const = 0; // SDFAST GenSpeeds


	//--------------------------------------------------------------------------
	// ELEMENTS
	//--------------------------------------------------------------------------
	virtual const rdObject& getObject(const std::string &aType,const std::string &aName) const;
	virtual const rdBodySet& getBodySet();
	virtual const Body& getBody(const std::string &aName) const;
	virtual const rdJointSet& getJointSet();
	virtual const Joint& getJoint(const std::string &aName) const;
	virtual const rdCoordinateSet& getCoordinateSet();
	virtual const Coordinate& getCoordinate(const std::string &aName) const;
	virtual const rdConstraintSet& getConstraintSet();
	virtual const Constraint& getConstraint(const std::string &aName) const;

	//--------------------------------------------------------------------------
	// CONFIGURATION
	//--------------------------------------------------------------------------
	virtual void setCoordinates(const double aQ[],const double aU[]=NULL);
	virtual void getCoordinates(rdArray<double> &rQ) const;
	virtual void getSpeeds(rdArray<double> &rU) const;

	//--------------------------------------------------------------------------
	// ASSEMBLING
	//--------------------------------------------------------------------------
	virtual int assemble(double aTime,double *rState,int *aLock,double aTol,
		 int aMaxevals,int *rFcnt,int *rErr) = 0;	//DYN

	//--------------------------------------------------------------------------
	// SCALE
	//--------------------------------------------------------------------------
	virtual bool scale(const suScaleSet& aScaleSet) = 0;

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
	// EQUATIONS OF MOTION
	//--------------------------------------------------------------------------
	virtual void formEulerTransform(int aBody,double *rE) const = 0; // DYN
	virtual void
		formJacobianTranslation(int aBody,const double aPoint[3],double *rJ,
		int aRefBody=-1) const = 0; // DYN
	virtual void
		formJacobianOrientation(int aBody,double *rJ0,int aRefBody=-1) const = 0; // DYN
	virtual void 
		formJacobianEuler(int aBody,double *rJE,int aRefBody=-1) const = 0; // DYN

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

//=============================================================================
};	// END of class SimmKinematicsEngine
//=============================================================================
//=============================================================================

#endif // __SimmKinematicsEngine_h__


