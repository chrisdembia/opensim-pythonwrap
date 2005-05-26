// rd1to3VectorGCVSpline.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2002
// All rights reserved.
//
// Authors: Frank C. Anderson and Saryn R. Goldberg
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// C++ INCLUDES
#include "rdMath.h"
#include "rd1to3VectorGCVSpline.h"


//=============================================================================
// DESTRUCTOR AND CONSTRUCTORS
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
rd1to3VectorGCVSpline::~rd1to3VectorGCVSpline()
{
}
//_____________________________________________________________________________
/**
 * Default constructor.
 */
rd1to3VectorGCVSpline::
rd1to3VectorGCVSpline() : _value(0.0)
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
rd1to3VectorGCVSpline::
rd1to3VectorGCVSpline(int aDegree,int aN,const double *aX,double *aY0,double *aY1,
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
rd1to3VectorGCVSpline::
rd1to3VectorGCVSpline(DOMElement *aElement) :
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
 * @param aSpline rd1to3VectorGCVSpline object to be copied.
 */
rd1to3VectorGCVSpline::
rd1to3VectorGCVSpline(const rd1to3VectorGCVSpline &aVectorSpline) :
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
void rd1to3VectorGCVSpline::
setNull()
{
	setType("rd1to3VectorGCVSpline");
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
void rd1to3VectorGCVSpline::
setEqual(const rd1to3VectorGCVSpline &aVectorSpline)
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
rdObject* rd1to3VectorGCVSpline::
copy() const
{
	rd1to3VectorGCVSpline *vectorSpline = new rd1to3VectorGCVSpline(*this);
	return(vectorSpline);
}

//_____________________________________________________________________________
/**
 * Copy this object and modify the copy so that it is consistent
 * with a specified XML element node.   NOT FUNCTIONAL
 *
 * The copy is constructed by first using
 * rd1to3VectorGCVSpline::rd1to3VectorGCVSpline(DOMElement*) in order to establish the
 * XML node.  Then, the assignment operator is used to set all
 * data members of the copy to the values of this object.  Finally, the
 * data members of the copy are updated using rd1to3VectorGCVSpline::updateObject().
 *
 * @param aElement XML element. 
 * @return Pointer to a copy of this object modified by the specified
 * XML element.
 */
rdObject* rd1to3VectorGCVSpline::
copy(DOMElement *aElement) const
{
	// CONSTRUCT FUNCTION BASED ON XML ELEMENT
	rd1to3VectorGCVSpline *func = new rd1to3VectorGCVSpline(aElement);

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
rd1to3VectorGCVSpline& rd1to3VectorGCVSpline::
operator=(const rd1to3VectorGCVSpline &aVectorSpline)
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
void rd1to3VectorGCVSpline::
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
rdGCVSpline* rd1to3VectorGCVSpline::
getSplineY0() const
{
	return(_splineY0);
}
//_____________________________________________________________________________
/**
 * Get the individual splines in the vector.
 *
 */
rdGCVSpline* rd1to3VectorGCVSpline::
getSplineY1() const
{
	return(_splineY1);
}
//_____________________________________________________________________________
/**
 * Get the individual splines in the vector.
 *
 */
rdGCVSpline* rd1to3VectorGCVSpline::
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
void rd1to3VectorGCVSpline::
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
 * Evaluate this function or a derivative of this function given a value for the
 * independent variable.  
 *
 * @param aDerivOrder Derivative order.  If aDerivOrder == 0, the function
 * is evaluated.  Otherwise, if aDerivOrder > 0, the aDerivOrder'th
 * derivative of the function is evaluated.  For example, if aDerivOrder == 1,
 * the first derivative of the function is returned.  Negative values of
 * aDerivOrder (integrals of the function) are not supported.
 * @param aX Value of the x independent variable at which to evaluate
 * this function or its derivatives.
 * @return Value of the function or one of its derivatives.
 */
const rdArray<double>& rd1to3VectorGCVSpline::
evaluate(double aX)
{
	if(_splineY0->getDegree()>=0) {
		_value[0] = _splineY0->evaluate(0,aX);
		_value[1] = _splineY1->evaluate(0,aX);
		_value[2] = _splineY2->evaluate(0,aX);
	} else {
		_value[0] = _value[1] = _value[2] = 0.0;
	}

	return(_value);
}

