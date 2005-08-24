// ExampleVectorFunctionUncoupledNxN.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2005 Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// INCLUDES
#include "ExampleVectorFunctionUncoupledNxN.h"

using namespace std;


//=============================================================================
// DESTRUCTOR AND CONSTRUCTORS
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
ExampleVectorFunctionUncoupledNxN::~ExampleVectorFunctionUncoupledNxN()
{
}
//_____________________________________________________________________________
/**
 * Default constructor.
 */
ExampleVectorFunctionUncoupledNxN::
ExampleVectorFunctionUncoupledNxN() :
	VectorFunctionUncoupledNxN(1)
{
	setNull();
}
//_____________________________________________________________________________
/**
 * Default constructor.
 */
ExampleVectorFunctionUncoupledNxN::
ExampleVectorFunctionUncoupledNxN(int aN) :
	VectorFunctionUncoupledNxN(aN)
{
	setNull();
}
//_____________________________________________________________________________
/**
 * Construct a function from an XML Element. THIS CONSTRUCTOR IS NOT YET WORKING
 * NEED TO ADD HOW TO DEFINE _nX AND _nY FROM aElement
 *
 * @param aElement XML element.
 */
ExampleVectorFunctionUncoupledNxN::
ExampleVectorFunctionUncoupledNxN(DOMElement *aElement) :
	VectorFunctionUncoupledNxN(aElement)
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
ExampleVectorFunctionUncoupledNxN::
ExampleVectorFunctionUncoupledNxN(const ExampleVectorFunctionUncoupledNxN &aVectorFunction) :
	VectorFunctionUncoupledNxN(aVectorFunction)
{
	setNull();

	// ASSIGN
	setEqual(aVectorFunction);
}
//_____________________________________________________________________________
/**
 * Copy this object.
 *
 * @return Pointer to a copy of this object.
 */
rdObject* ExampleVectorFunctionUncoupledNxN::
copy() const
{
	ExampleVectorFunctionUncoupledNxN *func =
		new ExampleVectorFunctionUncoupledNxN(*this);
	return(func);
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
rdObject* ExampleVectorFunctionUncoupledNxN::
copy(DOMElement *aElement) const
{
	// CONSTRUCT FUNCTION BASED ON XML ELEMENT
	ExampleVectorFunctionUncoupledNxN *func =
		new ExampleVectorFunctionUncoupledNxN(aElement);

	// ASSIGN DATA ACCORDING TO THIS ACTUATOR
	*func = *this;

	// UPDATE DATA CCORDING TO THE XML ELEMENT
	func->updateFromXMLNode();

	return(func);
}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set all member variables to NULL values.
 */
void ExampleVectorFunctionUncoupledNxN::
setNull()
{
	setType("ExampleVectorFunctionUncoupledNxN");
}

//_____________________________________________________________________________
/**
 * Set all member variables equal to the members of another object.
 * Note that this method is private.  It is only meant for copying the data
 * members defined in this class.  It does not, for example, make any changes
 * to data members of base classes.
 */
void ExampleVectorFunctionUncoupledNxN::
setEqual(const ExampleVectorFunctionUncoupledNxN &aVectorFunction)
{
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
ExampleVectorFunctionUncoupledNxN& ExampleVectorFunctionUncoupledNxN::
operator=(const ExampleVectorFunctionUncoupledNxN &aVectorFunction)
{
	// BASE CLASS
	VectorFunctionUncoupledNxN::operator=(aVectorFunction);

	// DATA
	setEqual(aVectorFunction);

	return(*this);
}


//=============================================================================
// EVALUATE
//=============================================================================
//_____________________________________________________________________________
/**
 * Evaluate the vector function.
 *
 * @param aX Array of abscissae.
 * @param aY Array of resulting function values.
 */
void ExampleVectorFunctionUncoupledNxN::
evaluate(const double *aX,double *rY)
{
	int N = getNX();

	// COMMON PART
	int i;
	double sum;
	double scale = 0.01;
	for(sum=0.0,i=0;i<N;i++) {
		sum += (double)i;
	}
	sum *= scale;

	// UNIQUE PART
	// Uncoupled-- each aY depends only on its corresponding aX.
	double root;
	for(i=0;i<N;i++) {
		root = scale * (double)i;
		// sin test function
		rY[i] = sum * sin(aX[i] - root);
		// parabolic test function
		//rY[i] = sum *aX[i]*aX[i]*aX[i] - sum*root*root*root; 
	}

}

