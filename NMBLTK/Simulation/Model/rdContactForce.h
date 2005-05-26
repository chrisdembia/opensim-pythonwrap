// rdContactForce.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2002-2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdContactForce_h__
#define __rdContactForce_h__


#include "rdModel.h"
#include "rdForce.h"


//=============================================================================
//=============================================================================
/**
 * A abstract class that supports the application of contact force between
 * two bodies, BodyA and BodyB.  Actuators of this type have no states
 * and no controls.  That is, contact is assumed to be entirely passive
 * and depends only on the states of a model or models.
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class RDSIMULATION_API rdContactForce : public rdForce
{

//=============================================================================
// DATA
//=============================================================================
protected:
	// PROPERTIES
	/** Surface normal on BodyA expressed in the BodyA frame. */
	rdPropertyDblArray _propNormalA;
	/** Surface normal on BodyB expressed in the BodyB frame. */
	rdPropertyDblArray _propNormalB;

	// REFERENCES
	rdArray<double> &_nA;
	rdArray<double> &_nB;


	/** Normal displacement vector expressed in the BodyA frame. */
	double _rnA[3];
	/** Normal distance from PointA to PointB. */
	double _rn;
	/** Normal velocity of PointB relative to PointA expressed in the BodyA
	frame. */
	double _vnA[3];
	/** Normal speed of PointB relative to PointA. */
	double _vn;
	/** Tangent displacement unit vector expressed in the BodyA frame. */
	double _tA[3];
	/** Tangential displacement vector expressed in the BodyA frame. */
	double _rtA[3];
	/** Tangential distance from PointA to PointB. */
	double _rt;
	/** Tangential velocity of PointB relative to PointA expressed in the
	BodyA frame. */
	double _vtA[3];
	// FORCE GEOMETRY
	/** Total normal force magnitude. */
	double _fnMag;
	/** Elastic normal force applied to BodyB expressed in the local frame
	of BodyA. */
	double _fnp[3];
	/** Viscous normal force applied to BodyB expressed in the local frame
	of BodyA. */
	double _fnv[3];
	/** Total ormal force applied to BodyB expressed in the local frame of BodyA. */
	double _fn[3];
	/** Total tangential force magnitude corrected to be consistent with
	friction constraints. */
	double _ftMag;
	/** Elastic tangential force NOT corrected to enforce friction
	constraints expressed in the local frame of BodyA. */
	double _ftp[3];
	/** Viscous tangential force NOT corrected to enforce friction
	constraints expressed in the local frame of BodyA. */
	double _ftv[3];
	/** Total tangential force applied to BodyB expressed in the local frame
	of BodyA.  Note that _ftA is not necessarily in the same direction as _tA
	because of the viscosity component. */
	double _ft[3];
	/** Correction in the spring force in order to enforce friction
	constraints.  It is the change made to the force applied to
   BodyA and is expressed in the local frame of BodyA. */
	double _dfFric[3];
	/** Pointer to a vector function that contains the velocity of _pA,
	expressed in the inertial frame, as a function of time. */
	rdVectorFunction *_vAFunction;
	/** Pointer to a vector function that contains the velocity of _pB,
	expressed in the inertial frame, as a function of time. */
	rdVectorFunction *_vBFunction;


//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdContactForce(int aBodyA=0,int aBodyB=0,int aNYP=0);
	rdContactForce(DOMElement *aElement,int aNYP=0);
	rdContactForce(const rdContactForce &aForce);
	virtual ~rdContactForce();
private:
	void setNull();
	void setupProperties();
	

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
	rdContactForce& operator=(const rdContactForce &aContact);

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
public:
	// CONTROLS (This are here to override what's in rdForce)
	virtual int getNX() const;
	virtual const std::string getControlName(int aIndex) const;
	virtual int getControlIndex(const std::string &aName) const;
	virtual void setControl(int aIndex,double aValue);
	virtual void setControl(const std::string &aName,double aValue);
	virtual void setControls(const double aX[]);
	virtual double getControl(int aIndex) const;
	virtual double getControl(const std::string &aName) const;
	virtual void getControls(double rX[]) const;
	// NORMAL ON BODY A
	void setNormalA(const double aNormal[3]);
	void getNormalA(double rNormal[3]) const;
	// NORMAL ON BODY B
	void setNormalB(const double aNormal[3]);
	void getNormalB(double rNormal[3]) const;
	// NORMAL DISPLACEMENT VECTOR
	void getNormalDisplacement(double rDisplacement[3]) const;
	// NORMAL DISTANCE
	double getNormalDistance() const;
	// NORMAL VELOCITY
	void getNormalVelocity(double rVelocity[3]) const;
	// NORMAL SPEED
	double getNormalSpeed() const;
	// TANGENT ON BODY A
	void getTangent(double rTangent[3]) const;
	// TANGENTIAL DISPLACEMENT VECTOR
	void getTangentialDisplacement(double rDisplacement[3]) const;
	// TANGENTIAL DISTANCE
	double getTangentialDistance() const;
	// TANGENTIAL VELOCITY
	void getTangentialVelocity(double rVelocity[3]) const;
	// FORCE
	void getNormalForce(double rFP[3],double rFV[3],double rF[3]) const;
	void getTangentialForce(double rFP[3],double rFV[3],double rF[3]) const;
	// TANGENTIAL IMPEDANCE
	virtual double getInstantaneousTangentialStiffness() const;
	virtual double getInstantaneousTangentialViscosity() const;
	// NORMAL IMPEDANCE
	virtual double getInstantaneousNormalStiffness() const;
	virtual double getInstantaneousNormalViscosity() const;
	// FRICTION CORRECTION
	void getFrictionCorrection(double rDF[3]) const;
	// POINT A VELOCITY FUNCTION
	void setVelPointAFunction(rdVectorFunction* aVectorFunction);
	const rdVectorFunction* getVelPointAFunction() const;
	// POINT B VELOCITY FUNCTION
	void setVelPointBFunction(rdVectorFunction* aVectorFunction);
	const rdVectorFunction* getVelPointBFunction() const;



	//--------------------------------------------------------------------------
	// COMPUTATIONS
	//--------------------------------------------------------------------------
	virtual void updatePseudoStates();
	virtual void computeDisplacements();
	virtual void computeVelocities();

	//--------------------------------------------------------------------------
	// APPLICATION
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// CHECK
	//--------------------------------------------------------------------------
	virtual bool check() const;

	//--------------------------------------------------------------------------
	// UTILITY
	//--------------------------------------------------------------------------
	virtual void
		computeLineOfActionComponents(double rNormal[3],
		double rTangential[3]) const;

	//--------------------------------------------------------------------------
	// XML
	//--------------------------------------------------------------------------
	virtual void updateFromXMLNode();

//=============================================================================
};	// END of class rdContactForce
//=============================================================================
//=============================================================================

#endif // __rdContactForce_h__


