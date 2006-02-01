// RegisterTypes.cpp
// author: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <string>
#include <iostream>
#include <NMBLTK/Tools/rdObject.h>
#include "RegisterTypes.h"
#include "rdGeneralizedForceAtv.h"
#include "rdLinearSetPoint.h"
#include "rdPolynomialSetPoint.h"

using namespace std;


//_____________________________________________________________________________
/**
 * The purpose of this routine is to register all class types exported by
 * the rdSimulation library.
 */
RDSIMULATION_API void RegisterTypes()
{
	cout<<"rdActuators.RegisterTypes:  \n";

	rdObject::RegisterType( rdGeneralizedForceAtv() );
	rdObject::RegisterType( rdLinearSetPoint() );
	rdObject::RegisterType( rdPolynomialSetPoint() );
}

