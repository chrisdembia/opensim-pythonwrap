// rdControlConstant.cpp
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
#include <NMBLTK/Tools/rdProperty.h>
#include <NMBLTK/Tools/rdPropertyDbl.h>
#include "rdControlConstant.h"


//=============================================================================
// CONSTRUCTOR(S)
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
rdControlConstant::~rdControlConstant()
{
}
//_____________________________________________________________________________
/**
 * Default constructor.
 *
 * @param aX Value of the control.  By default, the control is assigned a
 * value of 0.0.
 * @param aName Name of the control.  By default, the control is given the
 * name "UNKNOWN".
 */
rdControlConstant::rdControlConstant(double aX,const char *aName) :
	_x(_propX.getValueDbl())
{
	setNull();
	setIsModelControl(false);
	_x = aX;
	setName(aName);
}
//_____________________________________________________________________________
/**
 * Construct a control from an XML Element.
 *
 * @param aElement XML element.
 */
rdControlConstant::rdControlConstant(DOMElement *aElement) :
	rdControl(aElement),
	_x(_propX.getValueDbl())
{
	setNull();
	setIsModelControl(false);
	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aControl Control to copy.
 */
rdControlConstant::rdControlConstant(const rdControlConstant &aControl) :
	rdControl(aControl),
	_x(_propX.getValueDbl())
{
	setNull();
	copyData(aControl);
}
//_____________________________________________________________________________
/**
 * Construct a copy of this control.
 */
rdObject* rdControlConstant::
copy() const
{
	return(new rdControlConstant(*this));
}
//_____________________________________________________________________________
/**
 * Copy this object and modify the copy so that it is consistent
 * with a specified XML element node.
 *
 * The copy is constructed by first using the contructor for the DOMElement
 * in order to establish the relationship of the control with the
 * XML node.  Then, the assignment operator is used to set all member variables
 * of the copy to the values of this object.  Finally, the data members of
 * the copy are updated from the DOMElment using updateFromXMLNode().
 *
 * @param aElement XML element. 
 * @return Pointer to a copy of this object.
 */
rdObject* rdControlConstant::
copy(DOMElement *aElement) const
{
	// ESTABLISH RELATIONSHIP WITH XML NODE
	rdControlConstant *control = new rdControlConstant(aElement);

	// ASSIGNMENT OPERATOR
	*control = *this;

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
void rdControlConstant::
setNull()
{
	setType("rdControlConstant");
	setupProperties();
	_x = 0.0;
}
//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void rdControlConstant::
setupProperties()
{
	_propX.setName("value");
	_propX.setValue(0.0);
	_propertySet.append( &_propX );
}
//_____________________________________________________________________________
/**
 * Copy the member variables of the specified control.
 */
void rdControlConstant::
copyData(const rdControlConstant &aControl)
{
	_x = aControl.getParameterValue(0);
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
rdControlConstant& rdControlConstant::
operator=(const rdControlConstant &aControl)
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
// NUMBER OF PARAMETERS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the number of parameters that are used to specify the control curve.
 *
 * @return Number of parameters.
 */
int rdControlConstant::
getNumParameters() const
{
	return(1);
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
 */
void rdControlConstant::
setParameterMin(int aI,double aMin)
{
	setDefaultParameterMin(aMin);
}
//_____________________________________________________________________________
/**
 * Get the minimum value of a control parameter.
 *
 * @param aI Index of the parameter.
 * @return Minimum value of the parameter.
 */
double rdControlConstant::
getParameterMin(int aI) const
{
	return(getDefaultParameterMin());
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
 */
void rdControlConstant::
setParameterMax(int aI,double aMax)
{
	setDefaultParameterMax(aMax);
}
//_____________________________________________________________________________
/**
 * Get the maximum value of a control parameter.
 *
 * @param aI Index of the parameter.
 * @return Maximum value of the parameter.
 */
double rdControlConstant::
getParameterMax(int aI) const
{
	return(getDefaultParameterMax());
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
 * @return Time at which the control parameter occurs.  For rdControlConstant
 * this value is not defined, and so rdMath::NAN is always returned.
 */
double rdControlConstant::
getParameterTime(int aI) const
{
	return(rdMath::NAN);
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
 * @param aTLower Time below which the curve is not affected the specified
 * parameter.  For rdControlConstant, rdMath::MINUS_INFINITY is always
 * returned.
 * @param aTUpper Time above which the curve is not affected the specified
 * parameter.  For rdControlConstant, rdMath::PLUS_INFINITY is always
 * returned.
 */
void rdControlConstant::
getParameterNeighborhood(int aI,double &rTLower,double &rTUpper) const
{
	rTLower = rdMath::MINUS_INFINITY;
	rTUpper = rdMath::PLUS_INFINITY;
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
 * @param rList List of control parameters that affect the curve at time aT.
 * For rdControlConstant, parameter 0 (i.e., the value of the constant)
 * should be the only paramter on the list.
 * @return Number of parameters in the list.  For rdControlConstant, 1 should
 * always be returned.
 */
int rdControlConstant::
getParameterList(double aT,rdArray<int> &rList)
{
	rList.setSize(0);
	rList.append(0);
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
 * @param aTLower Lower time bound.  The control curve is guarranteed
 * not to be affected below this time by any of the returned parameters.
 * @param aTUpper Upper time bound.  The control curve is NOT guarranteed
 * to not be affected for times greater than this time.
 * @param rList List of control parameters that affect the curve at time aT.
 * For rdControlConstant, parameter 0 (i.e., the value of the constant)
 * should be the only paramter on the list.
 * @return Number of parameters in the list.  For rdControlConstant, 1 should
 * always be returned.
 */
int rdControlConstant::
getParameterList(double aTLower,double aTUpper,rdArray<int> &rList)
{
	rList.setSize(0);
	return(rList.getSize());
}

//-----------------------------------------------------------------------------
// PARAMETER VALUE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the value of a control parameter.
 *
 * Class rdControlConstant has only 1 parameter, which is the value of
 * the control.\n\n
 * Index     Parameter\n
 *   0       Control value
 *
 * @param aI Index of the parameter (only 0 is valid for rdControlConstant).
 * @param aX Value of the parameter (value of the control for rdControlConstant).
 * @see getNumParameters()
 */
void rdControlConstant::
setParameterValue(int aI,double aX)
{
	_x = aX;
}
//_____________________________________________________________________________
/**
 * Get the value of a control parameter.
 *
 * Class rdControlConstant has only 1 parameter, which is the value of
 * the control.\n\n
 * Index     Parameter\n
 *   0       Control value
 *
 * @param aI Index of the parameter (only 0 is valid in this case).
 * @return Value of the parameter (value of the control in this case).
 */
double rdControlConstant::
getParameterValue(int aI) const
{
	return(_x);
}

//-----------------------------------------------------------------------------
// CONTROL VALUE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the value of this control at time aT.
 *
 * @param aT Time at which to set the control.
 * @return Control value.  For rdControlConstant, aT is not used since the
 * control has a constant, time-independent value.
 */
void rdControlConstant::
setControlValue(double aT,double aX)
{
	_x = aX;
}
//_____________________________________________________________________________
/**
 * Get the value of this control at time aT.
 *
 * @param aT Time at which to get the control.
 * @return Control value.  For rdControlConstant, aT is not used since the
 * control has a constant, time-independent value.
 */
double rdControlConstant::
getControlValue(double aT)
{
	return(_x);
}
