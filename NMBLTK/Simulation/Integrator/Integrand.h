// Integrand.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2005 Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __Integrand_h__
#define __Integrand_h__

// INCLUDES
#include "rdIntegrator.h"

#ifdef SWIG
	#ifdef RDSIMULATION_API
		#undef RDSIMULATION_API
		#define RDSIMULATION_API
	#endif
#endif

//=============================================================================
//=============================================================================
/**
 * This abstract base class specifies the interface for an integrand.
 * An integrad is simply a function, or vector-valued fuction, that is
 * integrated.
 *
 * The assumped context is that of a simulation in time.  That is,
 * a vector of states y of size n is integrated forward in time.
 * The integrand is thus dydt, the time derivative of the states.
 * dydt is the same size as y and is typically computed by evaluating
 * a set of couple ordinary differential equations.
 *
 * Some integrators, in addition to an evaluation of dydt, require an
 * evaluation  of the Jacobian.  The Jacobian is the partial derivative of
 * the integrand with respect to the states.  The Jacobian is denoted
 * here by dydtdy.  It is thus an n x n square matrix:
 *
 * | dydt_1/dy_1 dydt_1/dy_2 ... dydt_1/dy_n | \n
 * | dydt_2/dy_1 dydt_2/dy_2 ... dydt_2/dy_n | \n
 * |     ...         ...     ...     ...     | \n
 * | dydt_n/dy_1 dydt_n/dy_2 ... dydt_n/dy_n | \n
 * 
 * The _i above indicates the ith element of a vector.
 *
 * The elements of the Jacobian matrix are assumed to be held sequentially
 * in memory as in an array.  The assumed order of the elements is the
 * first column (dydt/dy_1), followed by the second column (dydt/dy_2), ...,
 * all the way to the last column (dydt/dy_n).
 *
 * Definitions:\n
 * t: Time
 * n: Number of states, or size of the state vector.
 * y: Vector of states (size=n).
 * dydt: Integrand- the time derivative of states (size=n).
 * dydtdy: Jacobian- the partial of the integrad wrt the states (size=nxn).
 *
 * To function as an integrand, a derived class must implement the
 * following methods:
 * getSize(): Return the number of states (n).
 * compute: Compute the value of the integrand (dydt).
 * computeJacobian: Compute the Jacobian (dydtdy).
 *
 * @version 1.0
 * @author Frank C. Anderson
 */
class RDSIMULATION_API Integrand
{
//=============================================================================
// DATA
//=============================================================================
public:
	enum status { NORMAL=0, NAN=1, ERROR=2 };

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	Integrand();
	virtual ~Integrand();

	virtual int getSize() const;
	virtual status compute(double t,double y[],double dydt[]);
	virtual status computeJacobian(double t,double y[],double *dydtdy);

//=============================================================================
};	// END class Integrand
//=============================================================================
//=============================================================================

#endif  // __Integrand_h__
