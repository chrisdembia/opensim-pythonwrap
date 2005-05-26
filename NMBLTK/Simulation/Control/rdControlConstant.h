// rdControlConstant.h:
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2000-2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fc.anderson@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdControlConstant_h__
#define __rdControlConstant_h__


// INCLUDES
#include <RD/Simulation/rdSimulationDLL.h>
#include <RD/Tools/rdObject.h>
#include "rdControl.h"


//=============================================================================
//=============================================================================
/**
 * A class that represents a constant control curve.  That is, the value
 * of the control curve is the same at any value of time.
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class RDSIMULATION_API rdControlConstant : public rdControl
{

//=============================================================================
// MEMBER DATA
//=============================================================================
protected:
	// PROPERTIES
	/** Control value. */
	rdPropertyDbl _propX;

	// REFERENCES
	double &_x;

//=============================================================================
// METHODS
//=============================================================================
public:
	rdControlConstant(double aX=0.0,const char *aName="UNKOWN");
	rdControlConstant(DOMElement *aElement);
	rdControlConstant(const rdControlConstant &aControl);
	virtual ~rdControlConstant();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;
private:
	void setNull();
	void copyData(const rdControlConstant &aControl);
protected:
	void setupProperties();
	

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
#ifndef SWIG
	rdControlConstant& operator=(const rdControlConstant &aControl);
#endif
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	// PARAMETERS
	// Number
	virtual int getNumParameters() const;
	// Min
	virtual void setParameterMin(int aI,double aMin);
	virtual double getParameterMin(int aI) const;
	// Max
	virtual void setParameterMax(int aI,double aMax);
	virtual double getParameterMax(int aI) const;
	// Time and Neighborhood
	virtual double getParameterTime(int aI) const;
	virtual void getParameterNeighborhood(int aI,double &rTLower,double &rTUpper) const;
	// List
	virtual int getParameterList(double aT,rdArray<int> &rList);
	virtual int getParameterList(double aT1,double aT2,rdArray<int> &rList);
	// Value
	virtual void setParameterValue(int aI,double aP);
	virtual double getParameterValue(int aI) const;
	// CONTROL VALUE
	virtual void setControlValue(double aT,double aX);
	virtual double getControlValue(double aT);

//=============================================================================
};	// END of class rdControlConstant
//=============================================================================
//=============================================================================

#endif // __rdControlConstant_h__
