// rdVectorGCVSplineR1R3.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2002
// All rights reserved.
//
// Authors: Frank C. Anderson and Saryn R. Goldberg
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// C++ INCLUDES
#include "rdMath.h"
#include "rdVectorGCVSplineR1R3.h"


//=============================================================================
// DESTRUCTOR AND CONSTRUCTORS
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
rdVectorGCVSplineR1R3::~rdVectorGCVSplineR1R3()
{
}
//_____________________________________________________________________________
/**
 * Default constructor.
 */
rdVectorGCVSplineR1R3::
rdVectorGCVSplineR1R3() : _value(0.0)
{
	setNull();
}
//_____________________________________________________________________________
/**
 * Construct a spline of a specified degree given arrays of paired data points
 * (x,f1(x),f2(x),f3(x)).
 *
 * @param aDegree Degree of the spline.  Only the following degrees
 * are supported: 1 = linear, 3 = cubic, 5 = qunitic, and 7 = heptic.
 * @param aN  of data points.
 * @param aX Array of independent values- should be aN long.
 * @param aF Array of function values- should be aN long and have 3 columns.
 * @param aName Optional name of the spline.
 * @param aErrorVariance Estimate of the variance of the error in the data to
 * be fit.  If negative, the variance will be estimated.  If 0.0, the fit will
 * try to fit the data points exactly- no smoothing.  If positive, the fit
 * will be smoothed according to the specified variance. The larger the error
 * variance, the more the smoothing.  The smoothing parameter, p, in
 * Woltring (1986) is computed based on the error variance.
 */
rdVectorGCVSplineR1R3::
rdVectorGCVSplineR1R3(int aDegree,int aN,const double *aX,double *aY0,double *aY1,
	double *aY2,const char *aName,double aErrorVariance) : _value(0.0)
{
	setNull();

	_splineY0 = new rdGCVSpline(aDegree, aN, aX, aY0, "spline_0", aErrorVariance);
	_splineY1 = new rdGCVSpline(aDegree, aN, aX, aY1, "spline_1", aErrorVariance);
	_splineY2 = new rdGCVSpline(aDegree, aN, aX, aY2, "spline_2", aErrorVariance);

}
//_____________________________________________________________________________
/**
 * Construct a function from an XML Element.  NOT FUNCTIONAL
 *
 * @param aElement XML element.
 */
rdVectorGCVSplineR1R3::
rdVectorGCVSplineR1R3(DOMElement *aElement) :
	rdVectorFunction(aElement), _value(0.0)
{
	setNull();
	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Copy constructor.
 * All data members of the specified spline are copied.
 *
 * @param aSpline rdVectorGCVSplineR1R3 object to be copied.
 */
rdVectorGCVSplineR1R3::
rdVectorGCVSplineR1R3(const rdVectorGCVSplineR1R3 &aVectorSpline) :
	rdVectorFunction(aVectorSpline), _value(0.0)
{
	setEqual(aVectorSpline);
}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set all member variables to their NULL or default values.
 */
void rdVectorGCVSplineR1R3::
setNull()
{
	setType("rdVectorGCVSplineR1R3");
	_splineY0 = NULL;
	_splineY1 = NULL;
	_splineY2 = NULL;
	_value.setSize(3);
}

//_____________________________________________________________________________
/**
 * Set all member variables equal to the members of another object.
 * Note that this method is private.  It is only meant for copying the data
 * members defined in this class.  It does not, for example, make any changes
 * to data members of base classes.
 */
void rdVectorGCVSplineR1R3::
setEqual(const rdVectorGCVSplineR1R3 &aVectorSpline)
{
	setNull();

	// VALUES
	_splineY0 = aVectorSpline.getSplineY0();
	_splineY1 = aVectorSpline.getSplineY1();
	_splineY2 = aVectorSpline.getSplineY2();

}

//_____________________________________________________________________________
/**
 * Copy this object.
 *
 * @return Pointer to a copy of this object.
 */
rdObject* rdVectorGCVSplineR1R3::
copy() const
{
	rdVectorGCVSplineR1R3 *func = new rdVectorGCVSplineR1R3(*this);
	return(func);
}

//_____________________________________________________________________________
/**
 * Copy this object and modify the copy so that it is consistent
 * with a specified XML element node.   NOT FUNCTIONAL
 *
 * The copy is constructed by first using
 * rdVectorGCVSplineR1R3::rdVectorGCVSplineR1R3(DOMElement*) in order to establish the
 * XML node.  Then, the assignment operator is used to set all
 * data members of the copy to the values of this object.  Finally, the
 * data members of the copy are updated using rdVectorGCVSplineR1R3::updateObject().
 *
 * @param aElement XML element. 
 * @return Pointer to a copy of this object modified by the specified
 * XML element.
 */
rdObject* rdVectorGCVSplineR1R3::
copy(DOMElement *aElement) const
{
	// CONSTRUCT FUNCTION BASED ON XML ELEMENT
	rdVectorGCVSplineR1R3 *func = new rdVectorGCVSplineR1R3(aElement);

	// ASSIGN DATA ACCORDING TO THIS ACTUATOR
	*func = *this;

	// UPDATE DATA CCORDING TO THE XML ELEMENT
	func->updateFromXMLNode();

	return(func);
}


//=============================================================================
// OPERATORS
//=============================================================================
//_____________________________________________________________________________
/**
 * Assignment operator.
 * Note that data members of the base class are also assigned.
 *
 * @return Reference to this object.
 */
rdVectorGCVSplineR1R3& rdVectorGCVSplineR1R3::
operator=(const rdVectorGCVSplineR1R3 &aVectorSpline)
{
	// BASE CLASS
	rdVectorFunction::operator=(aVectorSpline);

	// DATA
	setEqual(aVectorSpline);

	return(*this);
}


//=============================================================================
// SET AND GET
//=============================================================================
//-----------------------------------------------------------------------------
// DEGREE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the degree of this spline.
 *
 * @param aDegree Degree of spline.  Legal values: 1 = linear, 3 = cubic,
 * 5 = qunitic, 7 = heptic.
 */
void rdVectorGCVSplineR1R3::
setDegree(int aDegree)
{
	_splineY0->setDegree(aDegree);
	_splineY1->setDegree(aDegree);
	_splineY2->setDegree(aDegree);

}
//-----------------------------------------------------------------------------
// SPLINES
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the individual splines in the vector.
 *
 */
rdGCVSpline* rdVectorGCVSplineR1R3::
getSplineY0() const
{
	return(_splineY0);
}
//_____________________________________________________________________________
/**
 * Get the individual splines in the vector.
 *
 */
rdGCVSpline* rdVectorGCVSplineR1R3::
getSplineY1() const
{
	return(_splineY1);
}
//_____________________________________________________________________________
/**
 * Get the individual splines in the vector.
 *
 */
rdGCVSpline* rdVectorGCVSplineR1R3::
getSplineY2() const
{
	return(_splineY2);
}



//=============================================================================
// EVALUATION
//=============================================================================
//_____________________________________________________________________________
/**
 * Update the bounding box for this function.
 *
 * For an rdGCVSpline, there is only one indepdendent variable x, so the 
 * minimum and maximum values of indepdent variables y and z is 0.0.
 *
 * When this method is called, the minimum and maximum x of the bounding box
 * is simply set to the minimum and maximum values of the x data points that
 * were used to construct the spline, that is, min x = x[0] and
 * max x = x[getN()-1].
 *
 * @see rdFunction
 */
void rdVectorGCVSplineR1R3::
updateBoundingBox()
{
	setMinX(0.0);
	setMaxX(0.0);

	if(_splineY0->getSize()<=0) return;

	setMinX(_splineY0->getX().get(0));
	setMaxX(_splineY0->getX().getLast());
}
//_____________________________________________________________________________
/**
 * Evaluate this function given a value for the independent variable.  
 *
 * @param aX Vector of the independent variables.
 * @param rY Vector of the resulting dependent variables.
 */
void rdVectorGCVSplineR1R3::
evaluate(const double *aX,double *rY)
{
	rY[0] = _splineY0->evaluate(0,aX[0]);
	rY[1] = _splineY1->evaluate(0,aX[0]);
	rY[2] = _splineY2->evaluate(0,aX[0]);
}
//_____________________________________________________________________________
/**
 * Evaluate this function given a value for the independent variable.  
 *
 * @param aX Vector of the independent variables.
 * @param rY Vector of the resulting dependent variables.
 */
void rdVectorGCVSplineR1R3::
evaluate(const rdArray<double> &aX,rdArray<double> &rY)
{
	assert(aX.getSize()==1);
	evaluate(&aX[0],&rY[0]);
}
//_____________________________________________________________________________
/**
 * Evaluate this function or a derivative of this function given a value for the
 * independent variable.  
 *
 * @param aX Vector of the independent variables.
 * @param rY Vector of the resulting dependent variables.
 * @param aDerivWRT
 */
void rdVectorGCVSplineR1R3::
evaluate(const rdArray<double> &aX,rdArray<double> &rY,
			const rdArray<int> &aDerivWRT)
{
	assert(aX.getSize()==1);

	int derivOrder = aDerivWRT.getSize();
	rY[0] = _splineY0->evaluate(derivOrder,aX[0]);
	rY[1] = _splineY1->evaluate(derivOrder,aX[0]);
	rY[2] = _splineY2->evaluate(derivOrder,aX[0]);
}


