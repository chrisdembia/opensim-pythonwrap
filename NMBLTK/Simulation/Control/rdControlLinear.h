// rdControlLinear.h:
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2000-2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fc.anderson@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdControlLinear_h__
#define __rdControlLinear_h__


// INCLUDES
#include <NMBLTK/Simulation/rdSimulationDLL.h>
#include <NMBLTK/Tools/rdObject.h>
#include <NMBLTK/Tools/rdPropertyBool.h>
#include <NMBLTK/Tools/rdPropertyObjArray.h>
#include "rdControl.h"
#include "rdControlLinearNode.h"


//=============================================================================
//=============================================================================
/**
 * A class that represents a piece-wise linear control curve.
 *
 * The curve is specified by an array of control nodes (see class
 * rdControlLinearNode) that occur at monotonically increasing times.
 * The value of the control curve is computed by linearly interpolating
 * the values of the appropriate control nodes.
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class RDSIMULATION_API rdControlLinear : public rdControl
{

//=============================================================================
// MEMBER DATA
//=============================================================================
public:
	/** Default control node. */
	static const rdControlLinearNode DEFAULT_NODE;

protected:
	// PROPERTIES
	/** Flag that indicates whether or not to linearly interpolate between
	nodes or use step functions. */
	rdPropertyBool _propUseSteps;
	/** Array of control nodes. */
	rdPropertyObjArray _propNodes;

	// REFERENCES
	bool &_useSteps;
	rdArrayPtrs<rdControlLinearNode> &_nodes;


	/** Utility node for speeding up searches for control values in
	getControlValue() and elsewhere.  Without this node, a control node would
	need to be contructed, but this is too expensive.  It is better to contruct
	a node up front, and then just alter the time. */
	rdControlLinearNode _searchNode;


//=============================================================================
// METHODS
//=============================================================================
public:
	rdControlLinear(rdArrayPtrs<rdControlLinearNode> *aX=NULL,
		const std::string &aName="UNKOWN");
	rdControlLinear(DOMElement *aElement);
	rdControlLinear(const rdControlLinear &aControl);
	virtual ~rdControlLinear();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;
protected:
	virtual void setupProperties();
	
private:
	void setNull();
	void copyData(const rdControlLinear &aControl);
	double extrapolateBefore(double aT) const;
	double extrapolateAfter(double aT) const;
	double extrapolateMinBefore(double aT) const;
	double extrapolateMinAfter(double aT) const;
	double extrapolateMaxBefore(double aT) const;
	double extrapolateMaxAfter(double aT) const;

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
#ifndef SWIG
	rdControlLinear& operator=(const rdControlLinear &aControl);
#endif

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	void setUseSteps(bool aTrueFalse);
	bool getUseSteps() const;
	// PARAMETERS
	// Number
	virtual int getNumParameters() const;
	// Parameter Min
	virtual void setParameterMin(int aI,double aMin);
	virtual double getParameterMin(int aI) const;
	// Parameter Max
	virtual void setParameterMax(int aI,double aMax);
	virtual double getParameterMax(int aI) const;
	// Parameter Time and Neighborhood
	virtual double getParameterTime(int aI) const;
	virtual void getParameterNeighborhood(int aI,double &rTLower,double &rTUpper) const;
	// Parmeter List
	virtual int getParameterList(double aT,rdArray<int> &rList);
	virtual int getParameterList(double aT1,double aT2,rdArray<int> &rList);
	// Parameter Value
	virtual void setParameterValue(int aI,double aP);
	virtual double getParameterValue(int aI) const;
	// CONTROL VALUE
	virtual void setControlValue(double aT,double aX);
	virtual double getControlValue(double aT);
	virtual double getControlValueMin(double aT=0.0);
	virtual void setControlValueMin(double aT,double aX);
	virtual double getControlValueMax(double aT=0.0);
	virtual void setControlValueMax(double aT,double aX);

	// NODE ARRAY
#ifndef SWIG
	const rdArrayPtrs<rdControlLinearNode>& getNodeArray() const;
#endif
	rdArrayPtrs<rdControlLinearNode>& getNodeArray(); 
	// Convenience methods
	virtual const double getFirstTime() const;
	virtual const double getLastTime() const;

	// SIMPLIFY
	virtual void
		simplify(const rdPropertySet &aProperties);

	NMBLTK_DERIVED(rdControlLinear, rdControl)

//=============================================================================
};	// END of class rdControlLinear
//=============================================================================
//=============================================================================

#endif // __rdControlLinear_h__
