// Integrand.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2005 Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <string>
#include "Integrand.h"
#include <NMBLTK/Tools/rdException.h>

#using namespace std;

//============================================================================
// EXPORTED CONSTANTS
//============================================================================


//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Default constructor.
 */
Integrand::Integrand()
{
}

//_____________________________________________________________________________
/**
 * Destructor.
 */
Integrand::~Integrand()
{
}


//=============================================================================
// REQUIRED METHODS
//=============================================================================
//____________________________________________________________________________
/**
 * Get the size of the state vector (y) and time derivative of the state
 * vector (dydt).  The size is the number of integrated variables.
 *
 * @return Size of the state vector.
 * @throws rdException All methods in this class should
 */
Integrand::status Integrand::
computeJacobian(double t,double y[],double *dydtdy)
{
	string msg = "Integrand.computeJacobian: ERROR- this method should ";
	msg += "be over-ridden by derived classes \nif it is required by the ";
	msg += "integrator being used.\n";

	throw rdException(msg,__FILE__,__LINE__);

	return(Integrand::ERROR);
}
