// VectorFunctionUncoupledNxN.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2005 Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// INCLUDES
#include "VectorFunctionUncoupledNxN.h"
#include "rdPropertyDbl.h"


using namespace std;


//=============================================================================
// DESTRUCTOR AND CONSTRUCTORS
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
VectorFunctionUncoupledNxN::~VectorFunctionUncoupledNxN()
{
}
//_____________________________________________________________________________
/**
 * Default constructor.
 */
VectorFunctionUncoupledNxN::
VectorFunctionUncoupledNxN() :
	rdVectorFunction(0,0)
{
	setNull();
}
//_____________________________________________________________________________
/**
 * Default constructor.
 */
VectorFunctionUncoupledNxN::
VectorFunctionUncoupledNxN(int aN) :
	rdVectorFunction(aN,aN)
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
VectorFunctionUncoupledNxN::
VectorFunctionUncoupledNxN(DOMElement *aElement) :
	rdVectorFunction(aElement)
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
VectorFunctionUncoupledNxN::
VectorFunctionUncoupledNxN(const VectorFunctionUncoupledNxN &aVectorFunction) :
	rdVectorFunction(aVectorFunction)
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
void VectorFunctionUncoupledNxN::
setNull()
{
	setType("VectorFunctionUncoupledNxN");
}

//_____________________________________________________________________________
/**
 * Set all member variables equal to the members of another object.
 * Note that this method is private.  It is only meant for copying the data
 * members defined in this class.  It does not, for example, make any changes
 * to data members of base classes.
 */
void VectorFunctionUncoupledNxN::
setEqual(const VectorFunctionUncoupledNxN &aVectorFunction)
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
VectorFunctionUncoupledNxN& VectorFunctionUncoupledNxN::
operator=(const VectorFunctionUncoupledNxN &aVectorFunction)
{
	// BASE CLASS
	rdVectorFunction::operator=(aVectorFunction);

	// DATA
	setEqual(aVectorFunction);

	return(*this);
}


//=============================================================================
// SET AND GET
//=============================================================================

