// rdForce.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2002-2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdForce_h__
#define __rdForce_h__

#include <RD/Simulation/rdSimulationDLL.h>
#include <RD/Tools/rdPropertyInt.h>
#include <RD/Tools/rdPropertyDblArray.h>
#include <RD/Tools/rdFunction.h>
#include <RD/Tools/rdVectorFunction.h>
#include "rdModel.h"
#include "rdActuator.h"


//=============================================================================
//=============================================================================
/**
 * A class that supports the application of a force between two bodies, BodyA
 * and BodyB.  This actuator has no states; the control is simply the force to
 * be applied to the model.
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class RDSIMULATION_API rdForce : public rdActuator
{

//=============================================================================
// DATA
//=============================================================================
protected:
	// PROPERTIES
	/** BodyA. */
	rdPropertyInt _propBodyA;
	/** Point on BodyA expressed in the body-local frame at which the
	force is applied. */
	rdPropertyDblArray _propPointA;
	/** Unit vector expressed in the local frame of BodyA that
	specifies the direction a positive actuator force is applied to BodyA.
	(serialized) */
	rdPropertyDblArray _propUnitVectorA;
	/** BodyB. */
	rdPropertyInt _propBodyB;
	/** Point on BodyB expressed in the body-local frame at which the
	force is applied. */
	rdPropertyDblArray _propPointB;

	// REFERENCES
	int &_bA;
	rdArray<double> &_pA;
	rdArray<double> &_uA;
	int &_bB;
	rdArray<double> &_pB;


	/** Unit vector expressed in the local frame of BodyB that
	specifies the direction a positive actuator force is applied to BodyB. */
	double _uB[3];
	/** Pointer to a vector function that contains coordinates of point on
	BodyA (express in the body-local frame) where force should be applied
	as a function of time. */
	rdVectorFunction *_pAFunction;
	/** Pointer to a vector function that contains coordinates of point on
	BodyB (express in the body-local frame) where force should be applied
	as a function of time. */
	rdVectorFunction *_pBFunction;
	/** Function containing values for the time-dependent force scaling factor. */
	rdFunction* _scaleFunction;
	/** Scale factor that pre-multiplies the applied force */
	double _scaleFactor;



//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdForce(int aBodyA=0,int aBodyB=0,int aNX=1,int aNY=0,int aNYP=0);
	rdForce(DOMElement *aElement,int aNX=1,int aNY=0,int aNYP=0);
	rdForce(const rdForce &aForce);
	virtual ~rdForce();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;
private:
	void setNull();
	void setupProperties();
	

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
	rdForce& operator=(const rdForce &aForce);

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
public:
	// BODY A
	void setBodyA(int aID);
	int getBodyA() const;
	// POINT A
	void setPointA(const double aPoint[3]);
	void getPointA(double rPoint[3]) const;
	// DIRECTION A
	void setForceDirectionA(const double aDirection[3]);
	void getForceDirectionA(double rDirection[3]) const;
	// BODY B
	void setBodyB(int aID);
	int getBodyB() const;
	// POINT B
	void setPointB(const double aPoint[3]);
	void getPointB(double rPoint[3]) const;
	// DIRECTION B
	void getForceDirectionB(double rDirection[3]) const;
	// POINT A FUNCTION
	void setPointAFunction(rdVectorFunction* aVectorFunction);
	const rdVectorFunction* getPointAFunction() const;
	// POINT B FUNCTION
	void setPointBFunction(rdVectorFunction* aVectorFunction);
	const rdVectorFunction* getPointBFunction() const;
	// SCALE FACTOR
	void setScaleFunction(rdFunction* _scaleFunction);
	rdFunction* getScaleFunction() const;
	void setScaleFactor(double aScaleFactor);
	double getScaleFactor();


	//--------------------------------------------------------------------------
	// APPLICATION
	//--------------------------------------------------------------------------
	virtual void apply();

	//--------------------------------------------------------------------------
	// COMPUTATIONS
	//--------------------------------------------------------------------------
	virtual void computeActuation();
	void computeForceDirectionForBodyB();
	void computeSpeed();
	void updatePointA();
	void updatePointB();

	//--------------------------------------------------------------------------
	// CHECK
	//--------------------------------------------------------------------------
	virtual bool check() const;

	//--------------------------------------------------------------------------
	// UTILITY
	//--------------------------------------------------------------------------
	void computeLineOfAction(double aLineOfAction[3]) const;

//=============================================================================
};	// END of class rdForce
//=============================================================================
//=============================================================================

#endif // __rdForce_h__


