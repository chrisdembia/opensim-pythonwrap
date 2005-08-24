// Integrand.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2005 Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <string>
#include "Integrand.h"
#include <NMBLTK/Tools/rdException.h>

using namespace std;


//=============================================================================
// SIZE
//=============================================================================
//____________________________________________________________________________
/**
 * Get the size of the state vector (y) and time derivative of the state
 * vector (dydt).  The size is the number of integrated variables.
 *
 * @return Size of the state vector y.
 * @throws rdException All methods in this base class should be over-ridden.
 */
int Integrand::
getSize() const
{
	string msg = "Integrand.getSize: ERROR- this method should ";
	msg += "be over-ridden by derived classes.";

	throw rdException(msg,__FILE__,__LINE__);

	return(0);
}



//=============================================================================
// HOOKS
//=============================================================================
//____________________________________________________________________________
/**
 * Initialize the Integrand at the beginning of an integration.
 *
 * @param ti Initial time of the integration.
 * @param tf Final time of the simulation.
 * @param y Initial values of the states.
 * @return Status of the initialization.
 * @throws rdException All methods in this base class should be over-ridden.
 */
Integrand::Status Integrand::
initialize(double ti,double tf,double y[])
{
	string msg = "Integrand.initialize: ERR- this method should ";
	msg += "be over-ridden by derived classes.\n";

	throw rdException(msg,__FILE__,__LINE__);

	return(ERR);
}
//____________________________________________________________________________
/**
 * Perform any desired operations after the last successful integration step.
 *
 * @param step Step number.
 * @param dt Time delta for the next integration step.
 * @param t Current time of the integration.
 * @param y Current values of the states.
 * @return Status of the processing.
 * @throws rdException All methods in this base class should be over-ridden.
 */
Integrand::Status Integrand::
processAfterStep(int step,double dt,double t,double y[])
{
	string msg = "Integrand.processAfter Step: ERR- this method should ";
	msg += "be over-ridden by derived classes.\n";

	throw rdException(msg,__FILE__,__LINE__);

	return(ERR);
}
//____________________________________________________________________________
/**
 * Finalize the integrand after an integration has completed (e.g., clean up).
 *
 * @param step Step number.
 * @param t Time at which the integration completed.
 * @param y Current values of the states.
 * @return Status of the processing.
 * @throws rdException All methods in this base class should be over-ridden.
 */
Integrand::Status Integrand::
finalize(int step,double t,double y[])
{
	string msg = "Integrand.finalize: ERR- this method should ";
	msg += "be over-ridden by derived classes.\n";

	throw rdException(msg,__FILE__,__LINE__);

	return(ERR);
}



//=============================================================================
// COMPUTATION
//=============================================================================
//____________________________________________________________________________
/**
 * Compute the integrand. The integrand is the time derivative of
 * the states (dydt).
 *
 * @param t Current time.
 * @param y State vector (size = getSize()).
 * @param dydt Integrand-- the time derivative of the
 * state vector (size = getSize()).
 * @return Status of the computation.
 * @throws rdException All methods in this base class should be over-ridden.
 */
Integrand::Status Integrand::
compute(double t,double y[],double dydt[])
{
	string msg = "Integrand.compute: ERROR- this method should ";
	msg += "be over-ridden by derived classes.\n";

	throw rdException(msg,__FILE__,__LINE__);

	return(ERR);
}

//____________________________________________________________________________
/**
 * Compute the Jacobian of the integrand.
 * 
 * The Jacobian is the partial derivative of the integrand with respect
 * to the states.  The Jacobian is denoted here by dydtdy.
 *
 * It is thus an n x n square matrix:
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
 * @param t Current time.
 * @param y State vector (size = getSize()).
 * @param dydtdy Jacobian- partial derivative of the integrand with
 * respect to the states (size = getSize() x getSize()).
 * @return Status of the computation.
 * @throws rdException All methods in this base class should be over-ridden.
 */
Integrand::Status Integrand::
computeJacobian(double t,double y[],double *dydtdy)
{
	string msg = "Integrand.computeJacobian: ERROR- this method should ";
	msg += "be over-ridden by derived classes \nif it is required by the ";
	msg += "integrator being used.\n";

	throw rdException(msg,__FILE__,__LINE__);

	return(ERR);
}

