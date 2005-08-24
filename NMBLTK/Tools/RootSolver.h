// RootSolver.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2005 Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __RootSolver_h__
#define __RootSolver_h__


// INCLUDES
#include "rdTools.h"
#include <string>
#include "rdArray.h"
#include "VectorFunctionUncoupledNxN.h"


template class RDTOOLS_API rdArray<double>;


//=============================================================================
//=============================================================================
/**
 * A class for finding the N roots of N one-dimensional non-linear equations.
 * 
 * The rational for making this class solve for the roots of N equations
 * simultaneously is that, for some problems, it is more computationally
 * efficient to evaluate the N equations at the same time, as opposed to one
 * after the other.  That is, the N equations, though decoupled, do share
 * some common terms.
 *
 * This class can always be used for a system where N=1, although there
 * will be some small amount of overhead for this class to function in
 * this way when compared to a class that is dedicated to an N=1.
 *
 * To construct an instance of this class, the user must provide an
 * instance of a VectorFunctionUncoupledNxN.
 *
 * @version 1.0
 * @author Frank C. Anderson
 */
class RDTOOLS_API RootSolver
{
//=============================================================================
// MEMBER VARIABLES
//=============================================================================
private:
	/** NxN Decoupled Vector Function */
	VectorFunctionUncoupledNxN *_function;


//=============================================================================
// METHODS
//=============================================================================
public:
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
	RootSolver(VectorFunctionUncoupledNxN *aFunc);
	virtual ~RootSolver();
private:
	void setNull();

	//--------------------------------------------------------------------------
	// SOLVE
	//--------------------------------------------------------------------------
public:
	rdArray<double> solve(const rdArray<double> &ax,const rdArray<double> &bx,
		const rdArray<double> &tol);

//=============================================================================
};	// END class RootSolver
//=============================================================================
//=============================================================================

#endif  // __RootSolver_h__
