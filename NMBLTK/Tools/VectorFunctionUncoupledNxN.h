// VectorFunctionUncoupledNxN.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2005 Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __VectorFunctionUncoupledNxN_h__
#define __VectorFunctionUncoupledNxN_h__


// INCLUDES
#include "rdTools.h"
#include "rdVectorFunction.h"
#include "rdArray.h"



//=============================================================================
//=============================================================================
/**
 * An abstract class for representing a vector function.
 *
 * A vector function is a relation between some number of independent variables 
 * and some number of dependent values such that for any particular set of
 * independent variables the correct number of dependent variables is returned.
 * Values of the function and its derivatives
 * are obtained by calling the evaluate() method.  The curve may or may not
 * be finite or diferentiable; the evaluate method returns values between
 * rdMath::MINUS_INFINITY and rdMath::PLUS_INFINITY, or it returns rdMath::NAN
 * (not a number) if the curve is not defined.
 * Currently, functions of up to 3 variables (x,y,z) are supported.
 *
 * @author Frank C. Anderson and Saryn R. Goldberg
 */
class RDTOOLS_API VectorFunctionUncoupledNxN : public rdVectorFunction
{
//=============================================================================
// DATA
//=============================================================================
protected:



//=============================================================================
// METHODS
//=============================================================================
public:
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
	VectorFunctionUncoupledNxN();
	VectorFunctionUncoupledNxN(int aN);
	VectorFunctionUncoupledNxN(DOMElement *aElement);
	VectorFunctionUncoupledNxN(const VectorFunctionUncoupledNxN &aFunction);
	virtual ~VectorFunctionUncoupledNxN();
	virtual rdObject* copy() const = 0;
	virtual rdObject* copy(DOMElement *aElement) const = 0;
private:
	void setNull();
	void setEqual(const VectorFunctionUncoupledNxN &aVectorFunction);

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
	VectorFunctionUncoupledNxN&
		operator=(const VectorFunctionUncoupledNxN &aFunction);

	//--------------------------------------------------------------------------
	// SET AND GET
	//--------------------------------------------------------------------------
	
	//--------------------------------------------------------------------------
	// EVALUATE
	//--------------------------------------------------------------------------

//=============================================================================
};	// END class VectorFunctionUncoupledNxN
//=============================================================================
//=============================================================================

#endif  // __VectorFunctionUncoupledNxN_h__
