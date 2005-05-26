// rdControlLinearNode.h:
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2000-2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fc.anderson@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdControlLinearNode_h__
#define __rdControlLinearNode_h__


// INCLUDES
#include <RD/Simulation/rdSimulationDLL.h>
#include <RD/Tools/rdObject.h>
#include <RD/Tools/rdArray.h>
#include <RD/Tools/rdPropertyDbl.h>

//=============================================================================
//=============================================================================
/**
 * A control node used to reconstruct a piecewise linear control.
 *
 * The member variables consist of a time, a value, a minimum value, and
 * a maximum value.  So that an rdArray<T> can be instantiated for
 * rdControlLinearNode, this class implements a default constructor, a copy
 * constructor, the assignment operator (=), the equality operator (==),
 * and the less than operator (<).  The time at which a control node
 * occurs is used to determine the results of the operators == and <.
 *
 * @author Frank C. Anderson
 * @version 1.0
 * @see rdControlLinear
 */
class RDSIMULATION_API rdControlLinearNode : public rdObject
{

//=============================================================================
// MEMBER DATA
//=============================================================================
public:
	/** Equality tolerance. */
	static double _EqualityTolerance;

protected:
	// PROPERTIES
	/** Time at which the node occurs. */
	rdPropertyDbl _propT;
	/** Control value of the node. */
	rdPropertyDbl _propX;
	/** Minimum control value of the node. */
	rdPropertyDbl _propMin;
	/** Maximum control value of the node. */
	rdPropertyDbl _propMax;

	// REFERENCES
	/** Reference to the value of the T property. */
	double &_t;
	/** Reference to the value of the X property. */
	double &_x;
	/** Reference to the value of the Min property. */
	double &_min;
	/** Reference to the value of the Max property. */
	double &_max;

	/** Local control node for doing searches.  This improves performance. */

//=============================================================================
// METHODS
//=============================================================================
public:
	rdControlLinearNode(double aT=0.0,double aX=0.0,
		double aMin=0.0,double aMax=1.0);
	rdControlLinearNode(DOMElement *aElement);
	rdControlLinearNode(const rdControlLinearNode &aNode);
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;
private:
	void setNull();
	void setupProperties();

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
	rdControlLinearNode& operator=(const rdControlLinearNode &aControl);
	bool operator==(const rdControlLinearNode &aControl) const;
	bool operator<(const rdControlLinearNode &aControl) const;

	friend std::ostream& operator<<(std::ostream &aOut,
		const rdControlLinearNode &aControlLinearNode);

	//--------------------------------------------------------------------------
	// SET AND GET
	//--------------------------------------------------------------------------
	static void SetEqualityTolerance(double aTol);
	static double GetEqualityTolerance();
	void setTime(double aT);
	double getTime() const;
	void setValue(double aX);
	double getValue() const;
	void setMin(double aMin);
	double getMin() const;
	void setMax(double aMax);
	double getMax() const;

	//--------------------------------------------------------------------------
	// UTILITY
	//--------------------------------------------------------------------------
	char* toString();

//=============================================================================
};	// END of class rdControlLinearNode
//=============================================================================
//=============================================================================

#endif // __rdControlLinearNode_h__
