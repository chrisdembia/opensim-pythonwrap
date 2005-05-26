// rdVectorFunction.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2002 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// INCLUDES
#include "rdVectorFunction.h"
#include "rdPropertyDbl.h"


using namespace std;


//=============================================================================
// DESTRUCTOR AND CONSTRUCTORS
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
rdVectorFunction::~rdVectorFunction()
{
}
//_____________________________________________________________________________
/**
 * Default constructor.
 */
rdVectorFunction::rdVectorFunction() :
	_minX(0.0), _maxX(0.0)
{
	setNull();
}
//_____________________________________________________________________________
/**
 * Default constructor.
 */
rdVectorFunction::rdVectorFunction(int aNX, int aNY) :
	_minX(0.0), _maxX(0.0)
{
	setNull();
	setNX(aNX);
	setNY(aNY);
}
//_____________________________________________________________________________
/**
 * Construct a function from an XML Element. THIS CONSTRUCTOR IS NOT YET WORKING
 * NEED TO ADD HOW TO DEFINE _nX AND _nY FROM aElement
 *
 * @param aElement XML element.
 */
rdVectorFunction::rdVectorFunction(DOMElement *aElement) :
	rdObject(aElement), _minX(0.0), _maxX(0.0)
{
	setNull();
	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aVectorFunction Function to copy.
 */
rdVectorFunction::rdVectorFunction(const rdVectorFunction &aVectorFunction) :
	rdObject(aVectorFunction), _minX(0.0), _maxX(0.0)
{
	setNull();

	// ASSIGN
	setEqual(aVectorFunction);
}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set all member variables to NULL values.
 */
void rdVectorFunction::
setNull()
{
	setType("rdVectorFunction");
	_nX = 0;
	_nY = 0;
}

//_____________________________________________________________________________
/**
 * Set all member variables equal to the members of another object.
 * Note that this method is private.  It is only meant for copying the data
 * members defined in this class.  It does not, for example, make any changes
 * to data members of base classes.
 */
void rdVectorFunction::
setEqual(const rdVectorFunction &aVectorFunction)
{
	setNX(aVectorFunction.getNX());
	setNY(aVectorFunction.getNY());
	setMinX(aVectorFunction.getMinX());
	setMaxX(aVectorFunction.getMaxX());
}

//=============================================================================
// OPERATORS
//=============================================================================
//_____________________________________________________________________________
/**
 * Assignment operator.
 *
 * @return Reference to this object.
 */
rdVectorFunction& rdVectorFunction::
operator=(const rdVectorFunction &aVectorFunction)
{
	// BASE CLASS
	rdObject::operator=(aVectorFunction);

	// DATA
	setEqual(aVectorFunction);

	return(*this);
}


//=============================================================================
// SET AND GET
//=============================================================================
//-----------------------------------------------------------------------------
// NUMBER OF INDEPENDENT AND DEPENDENT VARIABLES
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the number of independent variables.
 *
 * @param aNX Number of independent variables.
 */
void rdVectorFunction::
setNX(int aNX)
{
	_nX = aNX;
}
//_____________________________________________________________________________
/**
 * Get the number of independent variables.
 *
 * @return Number of independent variables.
 */
int rdVectorFunction::
getNX() const
{
	return(_nX);
}
//_____________________________________________________________________________
/**
 * Set the number of dependent variables.
 *
 * @param aNX Number of dependent variables.
 */
void rdVectorFunction::
setNY(int aNY)
{
	_nY = aNY;
}
//_____________________________________________________________________________
/**
 * Get the number of dependent variables.
 *
 * @return Number of dependent variables.
 */
int rdVectorFunction::
getNY() const
{
	return(_nY);
}
//-----------------------------------------------------------------------------
// MIN AND MAX INDPEPENDENT VARIABLES
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the minimum values of the independent variables.
 *
 * @param aMinX Array of minimum values of the independent variables.
 */
void rdVectorFunction::
setMinX(const rdArray<double> &aMinX)
{
	if(aMinX.getSize()!=_nX) {
		string msg = "rdVectorFunction.setMinX: ERR- ";
		msg += "Array size does not.match number of variables.";
		throw( rdException(msg,__FILE__,__LINE__) );
	}

	_minX = aMinX;
}
//_____________________________________________________________________________
/**
 * Get the minimum values of the independent variables.
 *
 * @return Array of minimum values of the independent variables.
 */
const rdArray<double>& rdVectorFunction::
getMinX() const
{
	return(_minX);
}
//_____________________________________________________________________________
/**
 * Set the minimum value of one of the independent variables.
 *
 * @param aXIndex Index of the independent variable value to be set.
 * @param aMinX Value of the independent variable specified by aX.
 */
void rdVectorFunction::
setMinX(int aXIndex, double aMinX)
{
	_minX.set(aXIndex, aMinX);
}
//_____________________________________________________________________________
/**
 * Get the minimum values of the independent variables.
 * 
 * @param aXIndex Index of the independent variable value to be set.
 * @return Array of minimum values of the independent variables.
 */
double rdVectorFunction::
getMinX(int aXIndex) const
{
	return(_minX.get(aXIndex));
}
//_____________________________________________________________________________
/**
 * Set the maximum values of the independent variables.
 *
 * @param aMaxX Array of maximum values of the independent variables.
 */
void rdVectorFunction::
setMaxX(const rdArray<double> &aMaxX)
{
	if(aMaxX.getSize()!=_nX) {
		string msg = "rdVectorFunction.setMaxX: ERR- ";
		msg += "Array size does not.match number of variables.";
		throw( rdException(msg,__FILE__,__LINE__) );
	}

	_maxX = aMaxX;}
//_____________________________________________________________________________
/**
 * Get the maximum values of the independent variables.
 *
 * @return Array of maximum values of the independent variables.
 */
const rdArray<double>& rdVectorFunction::
getMaxX() const
{
	return(_maxX);
}
//_____________________________________________________________________________
/**
 * Set the maximum value of one of the independent variables.
 *
 * @param aX Index of the independent variable value to be set.
 * @param aMaxX Value of the independent variable specified by aX.
 */
void rdVectorFunction::
setMaxX(int aXIndex, double aMaxX)
{
	_maxX.set(aXIndex, aMaxX);
}
//_____________________________________________________________________________
/**
 * Get the maximum values of the independent variables.
 *
 * @param aX Index of the independent variable value to be set.
 * @return Array of maximum values of the independent variables.
 */
double rdVectorFunction::
getMaxX(int aXIndex) const
{
	return(_maxX.get(aXIndex));
}

