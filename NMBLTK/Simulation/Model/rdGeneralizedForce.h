// rdGeneralizedForce.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2002-2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdGeneralizedForce_h__
#define __rdGeneralizedForce_h__


#include <NMBLTK/Simulation/rdSimulationDLL.h>
#include <NMBLTK/Tools/rdPropertyInt.h>
#include "rdModel.h"
#include "rdActuator.h"


//=============================================================================
//=============================================================================
/**
 * A class that supports the application of a generalized force to a model.
 * This actuator has no states; the control is simply the force to
 * be applied to the model.
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class RDSIMULATION_API rdGeneralizedForce : public rdActuator
{
//=============================================================================
// DATA
//=============================================================================
private:
	/** Name of the control. */
	static const std::string X_NAME;
protected:
	// PROPERTIES
	/** Coordinate to which the generalized force is applied. */
	rdPropertyInt _propQID;

	// REFERENCES
	int &_qID;

	/** Temporary work array for holding generalized speeds. */
	double *_utmp;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdGeneralizedForce(int aQID=-1,int aNX=1,int aNY=0,int aNYP=0);
	rdGeneralizedForce(DOMElement *aElement,int aNX=1,int aNY=0,int aNYP=0);
	rdGeneralizedForce(const rdGeneralizedForce &aGenForce);
	virtual ~rdGeneralizedForce();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;
private:
	void setNull();
	void setupProperties();
	

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
	rdGeneralizedForce& operator=(const rdGeneralizedForce &aGenForce);

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	// GENERALIZED COORDINATE
	void setQID(int aQID);
	int getQID() const;

	//--------------------------------------------------------------------------
	// APPLICATION
	//--------------------------------------------------------------------------
	virtual void apply();

	//--------------------------------------------------------------------------
	// COMPUTATIONS
	//--------------------------------------------------------------------------
	virtual void computeActuation();

	//--------------------------------------------------------------------------
	// CHECK
	//--------------------------------------------------------------------------
	virtual bool check() const;
	virtual bool isQIDValid() const;

	//--------------------------------------------------------------------------
	// XML
	//--------------------------------------------------------------------------
	virtual void updateFromXMLNode();

//=============================================================================
};	// END of class rdGeneralizedForce
//=============================================================================
//=============================================================================

#endif // __rdGeneralizedForce_h__


