// rdControlLinearNode.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2000-2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fc.anderson@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <NMBLTK/Simulation/rdSimulationDLL.h>
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Tools/rdIO.h>
#include <NMBLTK/Tools/rdPropertyDbl.h>
#include "rdControlLinearNode.h"


//=============================================================================
// STATIC CONSTANTS
//=============================================================================
double rdControlLinearNode::_EqualityTolerance = rdMath::ZERO;

//=============================================================================
// CONSTRUCTOR(S)
//=============================================================================
//_____________________________________________________________________________
/**
 * Default constructor. 
 *
 * @param aT Time.
 * @param aX Control value.
 * @param aMin Minimum allowed control value.
 * @param aMax Maximum allowed control value.
 *
 */
rdControlLinearNode::
rdControlLinearNode(double aT,double aX,double aMin,double aMax) :
	_t(_propT.getValueDbl()),
	_x(_propX.getValueDbl()),
	_min(_propMin.getValueDbl()),
	_max(_propMax.getValueDbl())
{
	setNull();
	_t = aT;
	_x = aX;
	_min = aMin;
	_max = aMax;
}
//_____________________________________________________________________________
/**
 * Construct a control node from an XML Element.
 *
 * @param aElement XML element.
 */
rdControlLinearNode::rdControlLinearNode(DOMElement *aElement) :
	rdObject(aElement),
	_t(_propT.getValueDbl()),
	_x(_propX.getValueDbl()),
	_min(_propMin.getValueDbl()),
	_max(_propMax.getValueDbl())
{
	setNull();
	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aControl Control to copy.
 */
rdControlLinearNode::rdControlLinearNode(const rdControlLinearNode &aControl) :
	_t(_propT.getValueDbl()),
	_x(_propX.getValueDbl()),
	_min(_propMin.getValueDbl()),
	_max(_propMax.getValueDbl())
{
	setNull();
	*this = aControl;
}
//_____________________________________________________________________________
/**
 * Construct and return a copy of this object.
 *
 * The object is allocated using the new operator, so the caller is
 * responsible for deleting the returned object.
 *
 * @return Copy of this object.
 */
rdObject* rdControlLinearNode::
copy() const
{
	rdControlLinearNode *object = new rdControlLinearNode(*this);
	return(object);
}
//_____________________________________________________________________________
/**
 * Copy this control and modify the copy so that it is consistent
 * with a specified XML element node.
 *
 * The copy is constructed by first using the contructor for the DOMElement
 * in order to establish the relationship of the control with the
 * XML node.  Then, the assignment operator is used to set all member variables
 * of the copy to the values of this object.  Finally, the data members of
 * the copy are updated from the DOMElment using updateFromXMLNode().
 *
 * @param aElement XML element. 
 * @return Pointer to a copy of this actuator.
 */
rdObject* rdControlLinearNode::
copy(DOMElement *aElement) const
{
	// ESTABLISH RELATIONSHIP WITH XML NODE
	rdControlLinearNode *node = (rdControlLinearNode *)this->copy();

	node->setXMLNode(aElement);

	// UPDATE BASED ON NODE
	node->updateFromXMLNode();

	return(node);
}

rdControlLinearNode::~rdControlLinearNode()
{
}
//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Set NULL value for the member variables.
 */
void rdControlLinearNode::
setNull()
{
	setType("rdControlLinearNode");
	setupProperties();
}
//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void rdControlLinearNode::
setupProperties()
{
	_propT.setName("t");
	_propT.setValue(0.0);
	_propertySet.append(&_propT);

	_propX.setName("x");
	_propX.setValue(0.0);
	_propertySet.append(&_propX);

	_propMin.setName("min");
	_propMin.setValue(0.0);
	_propertySet.append(&_propMin);

	_propMax.setName("max");
	_propMax.setValue(1.0);
	_propertySet.append(&_propMax);
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
 * @return Reference to the altered object.
 */
rdControlLinearNode& rdControlLinearNode::
operator=(const rdControlLinearNode &aNode)
{
	_t = aNode._t;
	_x = aNode._x;
	_min = aNode._min;
	_max = aNode._max;
	return(*this);
}

//-----------------------------------------------------------------------------
// EQUALITY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Equality operator.
 *
 * Equality of nodes is dertermined by comparing the time member varaibles.
 * If two nodes have the same value for time within the set equality
 * tolerance, the two nodes are considered equal:\n\n
 *
 *
 * @param aNode Node with which to evaluate equality.
 * @return True if the times are equal, false otherwise.
 */
bool rdControlLinearNode::
operator==(const rdControlLinearNode &aNode) const
{
	if((_t-_EqualityTolerance) > aNode._t) return(false);
	if((_t+_EqualityTolerance) < aNode._t) return(false);
	return(true);
}

//-----------------------------------------------------------------------------
// LESS THAN
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Less than operator.
 *
 * @param aNode Node with which to evaluate less than.
 * @return True if the time of this node is less than the time of aNode.
 */
bool rdControlLinearNode::
operator<(const rdControlLinearNode &aNode) const
{
	if(_t<aNode._t) return(true);
	else return(false);
}


//=============================================================================
// SET / GET
//=============================================================================
//-----------------------------------------------------------------------------
// EQUALITY TOLERANCE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the tolerance for determining equality of nodes.
 *
 * Equality of nodes is dertermined by comparing the time member varaibles.
 * If two nodes have the same value for time within the set equality
 * tolerance, the two nodes are considered equal.
 *
 * Note that the member variable _EqualityTolerance and this method are
 * static.  So, the specified equality tolerance affects all nodes.
 *
 * @param aTol Equality tolerance.  The equality tolerance must be 0.0 or
 * positive.  If a negative tolerance is sent in, the equality tolerance
 * is set to 0.0.
 * @see ==
 */
void rdControlLinearNode::
SetEqualityTolerance(double aTol)
{
	_EqualityTolerance = aTol;
	if(_EqualityTolerance<0.0) _EqualityTolerance = 0.0;
}
//_____________________________________________________________________________
/**
 * Get the tolerance for determining equality of nodes.
 *
 * Equality of nodes is dertermined by comparing _time member varaibles.
 * If two nodes have the same value for _time within the set equality
 * tolerance, the two nodes are considered equal.
 *
 * Note that the member variable _EqualityTolerance and this method are
 * static.  So, the specified equality tolerance affects all nodes.
 *
 * @return Equality tolerance.
 * @see ==
 */
double rdControlLinearNode::
GetEqualityTolerance()
{
	return(_EqualityTolerance);
}

//-----------------------------------------------------------------------------
// TIME
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the time at which this control node occurs.
 *
 * @param aTime Time at which this control node occurs.
 */
void rdControlLinearNode::
setTime(double aTime)
{
	_t = aTime;
}
//_____________________________________________________________________________
/**
 * Get the time at which this control node occurs.
 *
 * @return Time at which this control node occurs.
 */
double rdControlLinearNode::
getTime() const
{
	return(_t);
}

//-----------------------------------------------------------------------------
// VALUE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the value of this control node.
 *
 * @param aValue Value of this control node.
 */
void rdControlLinearNode::
setValue(double aValue)
{
	_x = aValue;
	_propX.setUseDefault(false);
}
//_____________________________________________________________________________
/**
 * Get the value of this control node.
 *
 * @return Value of this control node.
 */
double rdControlLinearNode::
getValue() const
{
	return(_x);
}

//-----------------------------------------------------------------------------
// MIN
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the minimum allowed value of this control node.
 *
 * @param aMin Minimum allowed value of this control node.  If aMin is
 * greater than the current maximum allowed value, the current
 * maximum allowed value is set to aMin.
 */
void rdControlLinearNode::
setMin(double aMin)
{
	_min = aMin;
	_propMin.setUseDefault(false);
	if(_min>_max){
		_max = _min;
		_propMax.setUseDefault(false);
	}
}
//_____________________________________________________________________________
/**
 * Get the minimum allowed value of this control node.
 *
 * @return Minimum allowed value of this control node.
 */
double rdControlLinearNode::
getMin() const
{
	return(_min);
}

//-----------------------------------------------------------------------------
// MAX
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the maximum allowed value of this control node.
 *
 * @param aMax Maximum allowed value of this control node.  If aMax is
 * less than the current minimum allowed value, the current
 * minimum allowed value is set to aMax.
 */
void rdControlLinearNode::
setMax(double aMax)
{
	_max = aMax;
	_propMax.setUseDefault(false);
	if(_max<_min){
		_min = _max;
		_propMin.setUseDefault(false);
	}
}
//_____________________________________________________________________________
/**
 * Get the maximum allowed value of this control node.
 *
 * @return Maximum allowed value of this control node.
 */
double rdControlLinearNode::
getMax() const
{
	return(_max);
}


//=============================================================================
// UTILITY
//=============================================================================
//-----------------------------------------------------------------------------
// TO STRING
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Convert the node to a string representation.
 *
 * The caller is responsible for deleting the returned string.
 *
 * @return String representation of the node.
 * @todo Alter this method so that a string value is returned.  It is too
 * complicated to have to remember to delete the returned string.
 */
char* rdControlLinearNode::
toString()
{
	int size = 8*32; 
	char *string = new char[size];
	char tmp[128];
	const char *format = rdIO::GetDoubleOutputFormat();

	strcpy(string,"t=");
	sprintf(tmp,format,_t);
	strcat(string,tmp);

	strcat(string," x=");
	sprintf(tmp,format,_x);
	strcat(string,tmp);

	strcat(string," min=");
	sprintf(tmp,format,_min);
	strcat(string,tmp);

	strcat(string," max=");
	sprintf(tmp,format,_max);
	strcat(string,tmp);

	return(string);
}


