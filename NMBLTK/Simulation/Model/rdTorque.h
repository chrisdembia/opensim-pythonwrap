// rdTorque.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdTorque_h__
#define __rdTorque_h__

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
 * A class that supports the application of a torque between two bodies, BodyA
 * and BodyB.  This actuator has no states; the control is simply the
 * excitation of the actuator.  The torque is the optimal force multiplied
 * by the excitation.  So the excitation is a simply normalized torque
 * (i.e., torque / optimal force).  The direction of the torque is
 * expressed in the body-local frame of BodyA.
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class RDSIMULATION_API rdTorque : public rdActuator
{

//=============================================================================
// DATA
//=============================================================================
protected:
	// PROPERTIES
	/** BodyA. */
	rdPropertyInt _propBodyA;
	/** Unit vector expressed in the local frame of BodyA that
	specifies the direction a positive torque is applied to BodyA.
	(serialized) */
	rdPropertyDblArray _propUnitVectorA;
	/** BodyB. */
	rdPropertyInt _propBodyB;

	// REFERENCES
	int &_bA;
	rdArray<double> &_uA;
	int &_bB;

	/** Unit vector expressed in the local frame of BodyB that
	specifies the direction a positive actuator force is applied to BodyB. */
	double _uB[3];


//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdTorque(int aBodyA=0,int aBodyB=0,int aNX=1,int aNY=0,int aNYP=0);
	rdTorque(DOMElement *aElement,int aNX=1,int aNY=0,int aNYP=0);
	rdTorque(const rdTorque &aForce);
	virtual ~rdTorque();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;
private:
	void setNull();
	void setupProperties();
	

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
	rdTorque& operator=(const rdTorque &aForce);

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
public:
	// BODY A
	void setBodyA(int aID);
	int getBodyA() const;
	// DIRECTION A
	void setDirectionA(const double aDirection[3]);
	void getDirectionA(double rDirection[3]) const;
	// BODY B
	void setBodyB(int aID);
	int getBodyB() const;
	// DIRECTION B
	void getDirectionB(double rDirection[3]) const;

	//--------------------------------------------------------------------------
	// APPLICATION
	//--------------------------------------------------------------------------
	virtual void apply();

	//--------------------------------------------------------------------------
	// COMPUTATIONS
	//--------------------------------------------------------------------------
	virtual void computeActuation();
	void computeDirectionForBodyB();
	void computeSpeed();

	//--------------------------------------------------------------------------
	// CHECK
	//--------------------------------------------------------------------------
	virtual bool check() const;

	//--------------------------------------------------------------------------
	// UTILITY
	//--------------------------------------------------------------------------

//=============================================================================
};	// END of class rdTorque
//=============================================================================
//=============================================================================

#endif // __rdTorque_h__


