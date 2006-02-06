// RegisterTypes.cpp
// author: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <string>
#include <iostream>
#include <NMBLTK/Tools/rdObject.h>
#include "RegisterTypes_rdActuators.h"
#include "rdGeneralizedForceAtv.h"
#include "rdLinearSetPoint.h"
#include "rdPolynomialSetPoint.h"

using namespace std;


//_____________________________________________________________________________
/**
 * The purpose of this routine is to register all class types exported by
 * the rdSimulation library.
 */
RDSIMULATION_API void RegisterTypes_rdActuators()
{
	cout<<"RegisterTypes_rdActuators:  \n";

	rdObject::RegisterType( rdGeneralizedForceAtv() );
	rdObject::RegisterType( rdLinearSetPoint() );
	rdObject::RegisterType( rdPolynomialSetPoint() );
}

