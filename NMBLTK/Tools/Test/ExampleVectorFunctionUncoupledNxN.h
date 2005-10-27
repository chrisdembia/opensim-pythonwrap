// ExampleVectorFunctionUncoupledNxN.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2005 Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __ExampleVectorFunctionUncoupledNxN_h__
#define __ExampleVectorFunctionUncoupledNxN_h__

#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Tools/rdArray.h>
#include <NMBLTK/Tools/VectorFunctionUncoupledNxN.h>

//extern template class RDTOOLS_API rdArray<double>;

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
 * @author Frank C. Anderson
 */
class ExampleVectorFunctionUncoupledNxN : public VectorFunctionUncoupledNxN
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
	ExampleVectorFunctionUncoupledNxN();
	ExampleVectorFunctionUncoupledNxN(int aN);
	ExampleVectorFunctionUncoupledNxN(DOMElement *aElement);
	ExampleVectorFunctionUncoupledNxN(const ExampleVectorFunctionUncoupledNxN &aFunction);
	virtual ~ExampleVectorFunctionUncoupledNxN();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;
private:
	void setNull();
	void setEqual(const ExampleVectorFunctionUncoupledNxN &aVectorFunction);

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
	ExampleVectorFunctionUncoupledNxN&
		operator=(const ExampleVectorFunctionUncoupledNxN &aFunction);

	//--------------------------------------------------------------------------
	// SET AND GET
	//--------------------------------------------------------------------------
public:
	
	//--------------------------------------------------------------------------
	// EVALUATE
	//--------------------------------------------------------------------------
	virtual void evaluate(const double *aX,double *aY);
	virtual void evaluate(const rdArray<double> &aX,rdArray<double> &rY);
	virtual void evaluate(const rdArray<double> &aX,rdArray<double> &rY,
		const rdArray<int> &aDerivWRT);

//=============================================================================
};	// END class ExampleVectorFunctionUncoupledNxN
//=============================================================================
//=============================================================================

#endif  // __ExampleVectorFunctionUncoupledNxN_h__
