// rdControlLinear.cpp
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
#include <NMBLTK/Tools/rdSignal.h>
#include <NMBLTK/Tools/rdIO.h>
#include <NMBLTK/Tools/rdProperty.h>
#include <NMBLTK/Tools/rdPropertyBool.h>
#include <NMBLTK/Tools/rdPropertyDbl.h>
#include <NMBLTK/Tools/rdPropertyObjArray.h>
#include <NMBLTK/Tools/rdPropertySet.h>
#include "rdControlLinear.h"
#include "rdControlLinearNode.h"


using namespace std;


//=============================================================================
// STATIC CONSTANTS
//=============================================================================
const rdControlLinearNode rdControlLinear::DEFAULT_NODE(0.0,0.0,0.0,1.0);


//=============================================================================
// CONSTRUCTOR(S)
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
rdControlLinear::~rdControlLinear()
{
}
//_____________________________________________________________________________
/**
 * Default constructor.
 *
 * @param aX Pointer to an array of control nodes.  By default, the value of
 * aX is NULL.  If it is not NULL, the control nodes pointed to
 * by aX are copied.  This class keeps its own internal array of control
 * nodes.  The caller owns the array pointed to by aX, is free to use
 * this array in any way, and, if necessary, is responsible for deleting the
 * memory associated with aX.
 * @param aName Name of the control.
 *
 */
rdControlLinear::
rdControlLinear(rdArrayPtrs<rdControlLinearNode> *aX,const string &aName) :
	_useSteps(_propUseSteps.getValueBool()),
	_nodes((rdArrayPtrs<rdControlLinearNode>&)_propNodes.getValueObjArray())
{
	setNull();
	if(aX!=NULL) {
		_nodes = *aX;
	}
	setName(aName);
}
//_____________________________________________________________________________
/**
 * Construct a control from an XML Element.
 *
 * @param aElement XML element.
 */
rdControlLinear::rdControlLinear(DOMElement *aElement) :
	rdControl(aElement),
	_useSteps(_propUseSteps.getValueBool()),
	_nodes((rdArrayPtrs<rdControlLinearNode>&)_propNodes.getValueObjArray())
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
rdControlLinear::rdControlLinear(const rdControlLinear &aControl) :
	rdControl(aControl),
	_useSteps(_propUseSteps.getValueBool()),
	_nodes((rdArrayPtrs<rdControlLinearNode>&)_propNodes.getValueObjArray())
{
	setNull();
	copyData(aControl);
}
//_____________________________________________________________________________
/**
 * Construct a copy of this control.
 */
rdObject* rdControlLinear::
copy() const
{
	return(new rdControlLinear(*this));
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
rdObject* rdControlLinear::
copy(DOMElement *aElement) const
{
	// ESTABLISH RELATIONSHIP WITH XML NODE
	rdControlLinear *control = (rdControlLinear *)this->copy();

	// ASSIGNMENT OPERATOR
	control->setXMLNode(aElement);

	// UPDATE BASED ON NODE
	control->updateFromXMLNode();

	return(control);
}


//=============================================================================
// CONSTRUCTION/DESTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set the member data to their NULL values.
 */
void rdControlLinear::
setNull()
{
	setType("rdControlLinear");
	setupProperties();
}
//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void rdControlLinear::
setupProperties()
{
	_propUseSteps.setName("use_steps");
	_propUseSteps.setValue(false);
	_propertySet.append( &_propUseSteps );

	_propNodes.setName("nodes");
	rdArrayPtrs<rdObject> nodes;
	_propNodes.setValue(nodes);
	_propertySet.append( &_propNodes );
}
//_____________________________________________________________________________
/**
 * Copy the member variables of the specified control.
 */
void rdControlLinear::
copyData(const rdControlLinear &aControl)
{
	_useSteps = aControl.getUseSteps();
	_nodes = aControl.getNodeArray();
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
 * @return  Reference to the altered object.
 */
rdControlLinear& rdControlLinear::
operator=(const rdControlLinear &aControl)
{
	// BASE CLASS
	rdControl::operator=(aControl);

	// DATA
	copyData(aControl);

	return(*this);
}


//=============================================================================
// GET AND SET
//=============================================================================
//-----------------------------------------------------------------------------
// USE STEPS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set whether or not step functions are used between control nodes or
 * linear interpolation.  When step functions are used, the value of the
 * control curve between two nodes is the value of the node that occurs later
 * in time.
 *
 * @param aTrueFalse If true, step functions will be used to determine the
 * value between adjacent nodes.  If false, linear interpolation will be used.
 */
void rdControlLinear::
setUseSteps(bool aTrueFalse)
{
	_useSteps = aTrueFalse;
}
//_____________________________________________________________________________
/**
 * Get whether or not step functions are used between control nodes or
 * linear interpolation.  When step functions are used, the value of the
 * control curve between two nodes is the value of the node that occurs later
 * in time.
 *
 * @return True if steps functions are used.  False if linear interpolation
 * is used.
 */
bool rdControlLinear::
getUseSteps() const
{
	return(_useSteps);
}

//-----------------------------------------------------------------------------
// NUMBER OF PARAMETERS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the number of parameters that are used to specify the control curve.
 *
 * @return Number of parameters.
 */
int rdControlLinear::
getNumParameters() const
{
	return(_nodes.getSize());
}

//-----------------------------------------------------------------------------
// PARAMETER MIN
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the minimum value of a control parameter.
 *
 * @param aI Index of the parameter.
 * @param aMin Minimum value of the parameter.
 * @throws rdException if aI is invalid.
 */
void rdControlLinear::
setParameterMin(int aI,double aMin)
{
	_nodes.get(aI)->setMin(aMin);
}
//_____________________________________________________________________________
/**
 * Get the minimum value of a control parameter.
 *
 * @param aI Index of the parameter.
 * @return Minimum value of the parameter.
 * @throws rdException if aI is invalid.
 */
double rdControlLinear::
getParameterMin(int aI) const
{
	return(_nodes.get(aI)->getMin());
}

//-----------------------------------------------------------------------------
// PARAMETER MAX
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the maximum value of a control parameter.
 *
 * @param aI Index of the parameter.
 * @param aMax Maximum value of the parameter.
 * @throws rdException if aI is invalid.
 */
void rdControlLinear::
setParameterMax(int aI,double aMax)
{
	_nodes.get(aI)->setMax(aMax);
}
//_____________________________________________________________________________
/**
 * Get the maximum value of a control parameter.
 *
 * @param aI Index of the parameter.
 * @return Maximum value of the parameter.
 * @throws rdException if aI is invalid.
 */
double rdControlLinear::
getParameterMax(int aI) const
{
	return(_nodes.get(aI)->getMax());
}

//-----------------------------------------------------------------------------
// PARAMETER TIME
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the time at which a parameter is specified.
 *
 * Parameters for some types of control curves do not have a time at which
 * they are specified.  For example, in a Fourier series the control
 * parameters are the cooefficients in the expansion, and each term in
 * the expansion corresponds not to a specific time but to a frequency.
 * Another example is a constant that has the same value for all times.
 * In these cases, this method returns rdMath::NAN.
 *
 * @param aI Index of the parameter.
 * @return Time at which the control parameter occurs.  For rdControlLinear
 * this value is not defined, and so rdMath::NAN is always returned.
 * @throws rdException if aI is invalid.
 */
double rdControlLinear::
getParameterTime(int aI) const
{
	return(_nodes.get(aI)->getTime());
}

//-----------------------------------------------------------------------------
// PARAMETER NEIGHBORHOOD
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the time neighborhood (i.e., the lower and upper bounds of time)
 * in which a control parameter affects the value of the control curve.
 *
 * Changes in the specified parameter are guarranteed not to change the value
 * of the control curve below the lower bound time or above the upper bound
 * time.  If a parameter influences the value of the control curve for all
 * times, rdMath::MINUS_INFINITY and rdMath::PLUS_INFINITY are returned for
 * the upper and lower bound times, respectively.
 *
 * @param aI Index of the parameter.
 * @param rTLower Time below which the curve is not affected by the specified
 * parameter.  For rdControlLinear, aTLower is the time of parameter aI-1 or of
 * aI if there is no parameter aI-1.  If there are no nodes at all or if
 * aI is invalid, aTLower is given the value rdMath::NAN.
 * @param rTUpper Time above which the curve is not affected by the specified
 * parameter.  For rdControlLinear, aTUpper is the time of parameter aI+1 or of
 * aI if there is no parameter aI+1.  If there are no nodes at all or if
 * aI is invalid, aTUpper is given the value rdMath::NAN.
 * @throws rdException if aI is invalid.
 */
void rdControlLinear::
getParameterNeighborhood(int aI,double &rTLower,double &rTUpper) const
{
	rTLower = rdMath::NAN;
	rTUpper = rdMath::NAN;

	// CHECK THAT THE NODE EXISTS
	// An exception is thrown if aI is out of bounds. 
	_nodes.get(aI);

	// NEIGHBORING NODES
	int size = _nodes.getSize();
	if(size==1) {
		rTLower = rdMath::MINUS_INFINITY;
		rTUpper = rdMath::PLUS_INFINITY;
		return;
	}
	int lower = aI - 1;
	if(lower<0) lower = 0;
	int upper;
	if(_useSteps) upper = aI;
	else  upper = aI + 1;
	if(upper>=size) upper = size-1;
	rTLower = _nodes.get(lower)->getTime();
	rTUpper = _nodes.get(upper)->getTime();
}

//-----------------------------------------------------------------------------
// PARAMETER LIST
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the list of parameters that affect the control curve at a
 * specified time.
 *
 * @param aT Time in question.
 * @param rList Array of control parameters that affect the curve at time aT.
 * For rdControlLinear, if aT lies between two nodes, the indices of these
 * two nodes is returned; if aT equals the time at which a node occurs, the
 * index of that node is returned; if aT is less than the time of the first
 * node in the array, the index of the first node (i.e., 0) is returned;
 * if aT is greater than the time of the last node, the index of the last
 * node (i.e., size-1) is returned.
 * @return Number of parameters in the list.
 */
int rdControlLinear::
getParameterList(double aT,rdArray<int> &rList)
{
	rList.setSize(0);

	// CHECK SIZE
	int size = _nodes.getSize();
	if(size<=0) return(0);

	// FIND THE NODE
	_searchNode.setTime(aT);
	int i = _nodes.searchBinary(_searchNode);

	// LESS THAN TIME OF FIRST NODE
	if(i<0) {
		rList.append(0);

	// GREATER THAN TIME OF LAST NODE
	} else if(i>=(size-1)) {
		rList.append(size-1);

	// EQUAL & LINEAR INTERPOLATION
	} else if((!_useSteps) && (_searchNode == (*_nodes.get(i)) )) {
		rList.append(i);

	// BETWEEN & LINEAR INTERPOLATION
	} else if(!_useSteps)  {
		rList.append(i);
		rList.append(i+1);

	// STEPS
	} else {
		rList.append(i+1);
	}

	return(rList.getSize());
}
//_____________________________________________________________________________
/**
 * Get the list of parameters that affect the control curve between two
 * specified times and that do NOT affect the control curve below the lower
 * of these two times.
 *
 * This method is useful when solving for a set of controls for a dynamic
 * simulation.  When solving for a set of controls, one always wants to
 * go forward in time.  Therefore, one does not want to change control
 * parameters that affect the control curve at past times.
 *
 * A control parameter is included in the list only if it affects
 * the control curve in the specified time interval AND does NOT
 * affect the control curve below the lower bound of the
 * specified time interval.  So, it is possible that some of the
 * parameters on the returned list could affect the control curve at
 * times greater than the upper bound of the specified time interval.
 *
 * @param aTLower Lower time bound.  The control curves are not affected
 * below this time by any of the returned parameters.
 * @param aTUpper Upper time bound.  The control curves may be affected
 * for times greater than this time.
 * @param rList List of control parameters (their indices to be exact) that
 * affect the curve between aTLower and aTUpper but not before aTLower.
 * @return Number of parameters indices in the list.
 */
int rdControlLinear::
getParameterList(double aTLower,double aTUpper,rdArray<int> &rList)
{
	rList.setSize(0);

	// CHECK SIZE
	int size = _nodes.getSize();
	if(size<=0) return(0);

	// CHECK FOR VALID INTERVAL
	if(aTLower>aTUpper) return(0);

	// LOWER NODE
	_searchNode.setTime(aTLower);
	int iL = _nodes.searchBinary(_searchNode);
	if(iL==-1) {
		iL += 1;
	} else if(iL==(size-1)) {
		return(0);
	} else if( (*_nodes.get(iL)) == _searchNode ) {
		iL += 1;
	} else {
		iL += 2;
	}

	// UPPER NODE
	_searchNode.setTime(aTUpper);
	int iU = _nodes.searchBinary(_searchNode);
	if(iU==-1) {
		return(0);
	} else if( (*_nodes.get(iU)) < _searchNode) {
		iU += 1;
	}

	// FORM LIST
	while(iL<=iU) {
		if(iL>=size) return(rList.getSize());
		rList.append(iL);
		iL++;
	}

	return(rList.getSize());
}

//-----------------------------------------------------------------------------
// PARAMETER VALUE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the value of a control parameter.
 *
 * @param aI Index of the parameter.
 * @param aX Value of the parameter.  For rdControlLinear, the parameter
 * value is simply the value of the control node.
 * @see getNumParameters()
 * @throws rdException if aI is invalid.
 */
void rdControlLinear::
setParameterValue(int aI,double aX)
{
	_nodes.get(aI)->setValue(aX);
}
//_____________________________________________________________________________
/**
 * Get the value of a control parameter.
 *
 * @param aI Index of the parameter.
 * @return Value of the parameter.  For rdControlLinear, the parameter value
 * is simply the value of the control node.
 */
double rdControlLinear::
getParameterValue(int aI) const
{
	return(_nodes.get(aI)->getValue());
}

//-----------------------------------------------------------------------------
// CONTROL VALUE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the value of this control curve at time aT.
 *
 * This method adds a set of control parameters at the specified time unless
 * the specified time equals the time of an existing control node, in which
 * case the parameters of that control node are changed.
 *
 * @param aT Time at which to set the control.
 * @param aX Control value.
 */
void rdControlLinear::
setControlValue(double aT,double aX)
{
	rdControlLinearNode node(aT,aX,getDefaultParameterMin(),getDefaultParameterMax());
	int lower = _nodes.searchBinary(node);

	// NO NODE
	if(lower<0) {
		_nodes.insert(0, (rdControlLinearNode*)node.copy() );

	// CHECK NODE
	} else {

		int upper = lower + 1;

		// EQUAL TO LOWER NODE
		if( (*_nodes[lower]) == node) {
			_nodes[lower]->setTime(aT);
			_nodes[lower]->setValue(aX);

		// NOT AT END OF ARRAY
		} else if(upper<_nodes.getSize()) {

			// EQUAL TO UPPER NODE
			if( (*_nodes[upper]) == node) {
				_nodes[upper]->setTime(aT);
				_nodes[upper]->setValue(aX);

			// NOT EQUAL
			} else {
				_nodes.insert(upper, (rdControlLinearNode*)node.copy() );
			}

		// AT END OF ARRAY
		} else {
			_nodes.append( (rdControlLinearNode*)node.copy() );
		}
	}
}
//_____________________________________________________________________________
/**
 * Get the value of this control at time aT.
 *
 * @param aT Time at which to get the control.
 * @return Control value.  If the value of the curve is not defined,
 * rdMath::NAN is returned.  If the control is set to extrapolate,
 * getExtraplate, and the time is before the first node or
 * after the last node, then an extrapolation is performed to determin
 * the value of the control curve.  Otherwise, the value of either the
 * first control node or last control node is returned.
 */
double rdControlLinear::
getControlValue(double aT)
{
	// CHECK SIZE
	int size = _nodes.getSize();
	if(size<=0) return(rdMath::NAN);

	// GET NODE
	_searchNode.setTime(aT);
	int i = _nodes.searchBinary(_searchNode);

	// BEFORE FIRST
	double value;
	if(i<0) {
		if(getExtrapolate()) {
			value = extrapolateBefore(aT);
		} else {
			value = _nodes[0]->getValue();
		}

	// AFTER LAST
	} else if(i>=(size-1)) {
		if(getExtrapolate()) {
			value = extrapolateAfter(aT);
		} else {
			value = _nodes.getLast()->getValue();
		}

	// IN BETWEEN
	} else {

		// LINEAR INTERPOLATION
		if(!_useSteps) {
			double t1,v1,t2,v2;
			t1 = _nodes[i]->getTime();
			v1 = _nodes[i]->getValue();
			t2 = _nodes[i+1]->getTime();
			v2 = _nodes[i+1]->getValue();
			value = rdMath::Interpolate(t1,v1,t2,v2,aT);

		// STEPS
		} else {
			value = _nodes[i+1]->getValue();
		}
	}

	return(value);
}
//_____________________________________________________________________________
/**
 * Extrapolate the value of the control curve before the first node.
 *
 * Currently, simple linear extrapolation using the first two nodes is
 * used.
 *
 * @param aT Time at which to evalute the control curve.
 * @return Extrapolated value of the control curve.
 */
double rdControlLinear::
extrapolateBefore(double aT) const
{
	if(_nodes.getSize()<=0) return(rdMath::NAN);
	if(_nodes.getSize()==1) return(_nodes[0]->getValue());

	double t1,v1,t2,v2;
	t1 = _nodes[0]->getTime();
	v1 = _nodes[0]->getValue();
	t2 = _nodes[1]->getTime();
	v2 = _nodes[1]->getValue();
	double value = rdMath::Interpolate(t1,v1,t2,v2,aT);

	return(value);
}
//_____________________________________________________________________________
/**
 * Extrapolate the value of the control curve after the last node.
 *
 * Currently, simple linear extrapolation using the last two nodes is
 * used.
 *
 * @param aT Time at which to evalute the control curve.
 * @return Extrapolated value of the control curve.
 */
double rdControlLinear::
extrapolateAfter(double aT) const
{
	int size = _nodes.getSize();
	if(size<=0) return(rdMath::NAN);
	if(size==1) return(_nodes[0]->getValue());

	int n1 = size - 2;
	int n2 = size - 1;
	double t1,v1,t2,v2;
	t1 = _nodes[n1]->getTime();
	v1 = _nodes[n1]->getValue();
	t2 = _nodes[n2]->getTime();
	v2 = _nodes[n2]->getValue();
	double value = rdMath::Interpolate(t1,v1,t2,v2,aT);

	return(value);
}

//-----------------------------------------------------------------------------
// CONTROL VALUE MINIMUM
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the minimum value of this control curve at time aT.
 *
 * This method adds a set of control parameters at the specified time unless
 * the specified time equals the time of an existing control node, in which
 * case the parameters of that control node are changed.
 *
 * @param aT Time at which to set the control.
 * @param aMin Minimum allowed control value.
 */
void rdControlLinear::
setControlValueMin(double aT,double aMin)
{
	rdControlLinearNode node(aT,0.0,getDefaultParameterMin(),getDefaultParameterMax());
	node.setMin(aMin);
	int lower = _nodes.searchBinary(node);

	// NO NODE
	if(lower<0) {
		_nodes.insert(0, (rdControlLinearNode*)node.copy() );

	// CHECK NODE
	} else {

		int upper = lower + 1;

		// EQUAL TO LOWER NODE
		if( (*_nodes[lower]) == node) {
			_nodes[lower]->setTime(aT);
			_nodes[lower]->setMin(aMin);

		// NOT AT END OF ARRAY
		} else if(upper<_nodes.getSize()) {

			// EQUAL TO UPPER NODE
			if( (*_nodes[upper]) == node) {
				_nodes[upper]->setTime(aT);
				_nodes[upper]->setMin(aMin);

			// NOT EQUAL
			} else {
				_nodes.insert(upper, (rdControlLinearNode*)node.copy() );
			}

		// AT END OF ARRAY
		} else {
			_nodes.append( (rdControlLinearNode*)node.copy() );
		}
	}
}
//_____________________________________________________________________________
/**
 * Get the minimum allowed value of this control at time aT.
 *
 * @param aT Time at which to get the control.
 * @return Minimum allowed control value.  If the value of the curve is not defined,
 * rdMath::NAN is returned.  If the control is set to extrapolate,
 * getExtraplate, and the time is before the first node or
 * after the last node, then an extrapolation is performed to determin
 * the value of the control curve.  Otherwise, the value of either the
 * first control node or last control node is returned.
 */
double rdControlLinear::
getControlValueMin(double aT)
{
	// CHECK SIZE
	int size = _nodes.getSize();
	if(size<=0) return(rdMath::NAN);

	// GET NODE
	_searchNode.setTime(aT);
	int i = _nodes.searchBinary(_searchNode);

	// BEFORE FIRST
	double t1,v1,t2,v2;
	double value;
	if(i<0) {
		if(getExtrapolate()) {
			value = extrapolateMinBefore(aT);
		} else {
			value = _nodes[0]->getMin();
		}

	// AFTER LAST
	} else if(i>=(size-1)) {
		if(getExtrapolate()) {
			value = extrapolateMinAfter(aT);
		} else {
			value = _nodes.getLast()->getMin();
		}

	// IN BETWEEN
	} else {

		// LINEAR INTERPOLATION
		if(!_useSteps) {
			t1 = _nodes[i]->getTime();
			v1 = _nodes[i]->getMin();
			t2 = _nodes[i+1]->getTime();
			v2 = _nodes[i+1]->getMin();
			value = rdMath::Interpolate(t1,v1,t2,v2,aT);

		// STEPS
		} else {
			value = _nodes[i+1]->getMin();
		}
	}

	return(value);
}
//_____________________________________________________________________________
/**
 * Extrapolate the value of the control curve before the first node.
 *
 * Currently, simple linear extrapolation using the first two nodes is
 * used.
 *
 * @param aT Time at which to evalute the control curve.
 * @return Extrapolated value of the control curve.
 */
double rdControlLinear::
extrapolateMinBefore(double aT) const
{
	if(_nodes.getSize()<=0) return(rdMath::NAN);
	if(_nodes.getSize()==1) return(_nodes[0]->getMin());

	double t1,v1,t2,v2;
	t1 = _nodes[0]->getTime();
	v1 = _nodes[0]->getMin();
	t2 = _nodes[1]->getTime();
	v2 = _nodes[1]->getMin();
	double value = rdMath::Interpolate(t1,v1,t2,v2,aT);

	return(value);
}
//_____________________________________________________________________________
/**
 * Extrapolate the value of the control curve after the last node.
 *
 * Currently, simple linear extrapolation using the last two nodes is
 * used.
 *
 * @param aT Time at which to evalute the control curve.
 * @return Extrapolated value of the control curve.
 */
double rdControlLinear::
extrapolateMinAfter(double aT) const
{
	int size = _nodes.getSize();
	if(size<=0) return(rdMath::NAN);
	if(size==1) return(_nodes[0]->getMin());

	int n1 = size - 2;
	int n2 = size - 1;
	double t1,v1,t2,v2;
	t1 = _nodes[n1]->getTime();
	v1 = _nodes[n1]->getMin();
	t2 = _nodes[n2]->getTime();
	v2 = _nodes[n2]->getMin();
	double value = rdMath::Interpolate(t1,v1,t2,v2,aT);

	return(value);
}


//-----------------------------------------------------------------------------
// CONTROL VALUE MAXIMUM
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the maximum value of this control curve at time aT.
 *
 * This method adds a set of control parameters at the specified time unless
 * the specified time equals the time of an existing control node, in which
 * case the parameters of that control node are changed.
 *
 * @param aT Time at which to set the control.
 * @param aMax Maximum allowed control value.
 */
void rdControlLinear::
setControlValueMax(double aT,double aMax)
{
	rdControlLinearNode node(aT,0.0,getDefaultParameterMin(),getDefaultParameterMax());
	node.setMax(aMax);
	int lower = _nodes.searchBinary(node);

	// NO NODE
	if(lower<0) {
		_nodes.insert(0, (rdControlLinearNode*)node.copy() );

	// CHECK NODE
	} else {

		int upper = lower + 1;

		// EQUAL TO LOWER NODE
		if( (*_nodes[lower]) == node) {
			_nodes[lower]->setTime(aT);
			_nodes[lower]->setMax(aMax);

		// NOT AT END OF ARRAY
		} else if(upper<_nodes.getSize()) {

			// EQUAL TO UPPER NODE
			if( (*_nodes[upper]) == node) {
				_nodes[upper]->setTime(aT);
				_nodes[upper]->setMax(aMax);

			// NOT EQUAL
			} else {
				_nodes.insert(upper, (rdControlLinearNode*)node.copy() );
			}

		// AT END OF ARRAY
		} else {
			_nodes.append( (rdControlLinearNode*)node.copy() );
		}
	}
}
//_____________________________________________________________________________
/**
 * Get the maximum allowed value of this control at time aT.
 *
 * @param aT Time at which to get the control.
 * @return Maximum allowed control value.  If the value of the curve is not defined,
 * rdMath::NAN is returned.  If the control is set to extrapolate,
 * getExtraplate, and the time is before the first node or
 * after the last node, then an extrapolation is performed to determin
 * the value of the control curve.  Otherwise, the value of either the
 * first control node or last control node is returned.
 */
double rdControlLinear::
getControlValueMax(double aT)
{
	// CHECK SIZE
	int size = _nodes.getSize();
	if(size<=0) return(rdMath::NAN);

	// GET NODE
	_searchNode.setTime(aT);
	int i = _nodes.searchBinary(_searchNode);

	// BEFORE FIRST
	double t1,v1,t2,v2;
	double value;
	if(i<0) {
		if(getExtrapolate()) {
			value = extrapolateMaxBefore(aT);
		} else {
			value = _nodes[0]->getMax();
		}

	// AFTER LAST
	} else if(i>=(size-1)) {
		if(getExtrapolate()) {
			value = extrapolateMaxAfter(aT);
		} else {
			value = _nodes.getLast()->getMax();
		}

	// IN BETWEEN
	} else {

		// LINEAR INTERPOLATION
		if(!_useSteps) {
			t1 = _nodes[i]->getTime();
			v1 = _nodes[i]->getMax();
			t2 = _nodes[i+1]->getTime();
			v2 = _nodes[i+1]->getMax();
			value = rdMath::Interpolate(t1,v1,t2,v2,aT);

		// STEPS
		} else {
			value = _nodes[i+1]->getMax();
		}
	}

	return(value);
}
//_____________________________________________________________________________
/**
 * Extrapolate the value of the control curve before the first node.
 *
 * Currently, simple linear extrapolation using the first two nodes is
 * used.
 *
 * @param aT Time at which to evalute the control curve.
 * @return Extrapolated value of the control curve.
 */
double rdControlLinear::
extrapolateMaxBefore(double aT) const
{
	if(_nodes.getSize()<=0) return(rdMath::NAN);
	if(_nodes.getSize()==1) return(_nodes[0]->getMax());

	double t1,v1,t2,v2;
	t1 = _nodes[0]->getTime();
	v1 = _nodes[0]->getMax();
	t2 = _nodes[1]->getTime();
	v2 = _nodes[1]->getMax();
	double value = rdMath::Interpolate(t1,v1,t2,v2,aT);

	return(value);
}
//_____________________________________________________________________________
/**
 * Extrapolate the value of the control curve after the last node.
 *
 * Currently, simple linear extrapolation using the last two nodes is
 * used.
 *
 * @param aT Time at which to evalute the control curve.
 * @return Extrapolated value of the control curve.
 */
double rdControlLinear::
extrapolateMaxAfter(double aT) const
{
	int size = _nodes.getSize();
	if(size<=0) return(rdMath::NAN);
	if(size==1) return(_nodes[0]->getMax());

	int n1 = size - 2;
	int n2 = size - 1;
	double t1,v1,t2,v2;
	t1 = _nodes[n1]->getTime();
	v1 = _nodes[n1]->getMax();
	t2 = _nodes[n2]->getTime();
	v2 = _nodes[n2]->getMax();
	double value = rdMath::Interpolate(t1,v1,t2,v2,aT);

	return(value);
}

//-----------------------------------------------------------------------------
// NODE ARRAY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the array of control nodes.
 *
 * @return Array of nodes.
 */
const rdArrayPtrs<rdControlLinearNode>& rdControlLinear::
getNodeArray() const
{
	return(_nodes);
}
//_____________________________________________________________________________
/**
 * Get the array of control nodes.
 *
 * @return Array of nodes.
 */
rdArrayPtrs<rdControlLinearNode>& rdControlLinear::
getNodeArray()
{
	return(_nodes);
}
//_____________________________________________________________________________
/**
 * Get const ref to the time corresponding to first node
 *
 * @return const ref to time corresponding to first node.
 */
const double rdControlLinear::getFirstTime() const
{
	const rdControlLinearNode *node=getNodeArray().get(0);
	return node->getTime();
}
//_____________________________________________________________________________
/**
 * Get const ref to the time corresponding to Last node
 *
 * @return const ref to time corresponding to last node.
 */
const double rdControlLinear::getLastTime() const
{
	const rdControlLinearNode *node=getNodeArray().getLast();
	return node->getTime();
}

//-----------------------------------------------------------------------------
// SIMPLIFY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Simplify the control curve.
 *
 * The number of control nodes is reduced by first applying a lowpass filter
 * to the sequence of control nodes using a specified cutoff frequency and
 * then removing nodes that keep the curve within a specified distance
 * to the low-pass filtered curve. 
 * 
 * @param aProperties Property set containing the needed properties for
 * this method.  The property set should contain:\n
 * \tTYPE          NAME
 * \trdPropertyDbl cutoff_frequency\n
 * \trdPropertyDbl distance\n\n
 * @throws rdException if an error is encountered.
 */
void rdControlLinear::
simplify(const rdPropertySet &aProperties)
{
	// INITIAL SIZE
	int size = _nodes.getSize();
	cout<<"\nrdControlLinear.simplify: initial size = "<<size<<".\n";
	
	// GET THE NODE TIMES
	int i;
	rdArray<double> t(0.0,size);
	for(i=0;i<size;i++) {
		t[i] = _nodes[i]->getTime();
	}

	// SEARCH FOR THE MINIMUM TIME INTERVAL
	double dt,dtMin=rdMath::PLUS_INFINITY;
	for(i=0;i<(size-1);i++) {
		dt = t[i+1] - t[i];
		if(dt<dtMin) {
			dtMin = dt;
			if(dtMin<=rdMath::ZERO) {
				string msg = "rdControlLinear.simplify: zero or negative dt!";
				throw(rdException(msg,__FILE__,__LINE__));
			}
		}
	}
	//cout<<"rdControlLinear.simplify: dtMin="<<dtMin<<endl;

	// RESAMPLE THE NODE VALUES
	int n = (int)(1.0 + (t[size-1] - t[0])/dtMin);
	double time;
	rdArray<double> x(0.0,n);
	t.setSize(n);
	//cout<<"rdControlLinear.simplify: resampling using "<<n<<" points.\n";
	for(time=t[0],i=0;i<n;i++,time+=dtMin) {
		t[i] = time;
		x[i] = getControlValue(time);
	}

	// FILTER
	double cutoffFrequency = aProperties.get("cutoff_frequency")->getValueDbl();
	if(cutoffFrequency < rdMath::ZERO) {
		throw(rdException());
	}
	rdArray<double> xFilt(0.0,n);
	int order = 50;
	if(order>(n/2)) order = n/2;
	if(order<10) {
		cout<<"rdControlLinear.simplify: WARN- too few data points ";
		cout<<"(n="<<n<<") to filter "<<getName()<<".\n";
	} else {
		if(order<20) {
			cout<<"rdControlLinear.simplify: WARN- order of FIR filter had to be ";
			cout<<"low due to small number of data points ";
			cout<<"(n="<<n<<") in control "<<getName()<<".\n";
		}
		cout<<"rdControlLinear.simplify: lowpass filtering with a ";
		cout<<"cutoff frequency of "<<cutoffFrequency<<" and order of ";
		cout<<order<<".\n"; 
		rdSignal::LowpassFIR(order,dtMin,cutoffFrequency,n,&x[0],&xFilt[0]);
	}

	// REMOVE POINTS
	double distance = aProperties.get("distance")->getValueDbl();
	cout<<"rdControlLinear.simplify: reducing points with distance tolerance = ";
	cout<<distance<<".\n";
	int nRemoved = rdSignal::ReduceNumberOfPoints(distance,t,xFilt);	

	// CLEAR OLD NODES
	_nodes.trim();
	_nodes.setSize(0);

	// ADD NEW NODES
	int newSize = t.getSize();
	char name[rdObject::NAME_LENGTH];
	rdControlLinearNode *node;
	for(i=0;i<newSize;i++) {
		node = new rdControlLinearNode(t[i],xFilt[i]);
		sprintf(name,"%d",i);
		node->setName(name);
		_nodes.append(node);
	}

	cout<<"rdControlLinear.simplify: final size = "<<_nodes.getSize()<<".\n";
}
