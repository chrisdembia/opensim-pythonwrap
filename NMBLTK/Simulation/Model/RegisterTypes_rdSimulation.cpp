// RegisterTypes_rdSimulation.cpp
// author: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <string>
#include <iostream>
#include <NMBLTK/Tools/rdObject.h>
#include "RegisterTypes_rdSimulation.h"
#include "rdActuatorSet.h"
#include "rdContactForceSet.h"
#include "rdForce.h"
#include "rdTorque.h"
#include "rdMuscle.h"
#include "rdGeneralizedForce.h"
#include <NMBLTK/Simulation/Manager/rdManager.h>
#include <NMBLTK/Simulation/Control/rdControlConstant.h>
#include <NMBLTK/Simulation/Control/rdControlLinear.h>

using namespace std;


//_____________________________________________________________________________
/**
 * The purpose of this routine is to register all class types exported by
 * the rdSimulation library.
 */
RDSIMULATION_API void RegisterTypes_rdSimulation()
{
	cout<<"RegisterTypes_rdSimulation:  \n";

	//rdObject::RegisterType( rdManager() );

	rdObject::RegisterType( rdControlSet() );
	rdObject::RegisterType( rdControlConstant() );
	rdObject::RegisterType( rdControlLinear() );
	rdObject::RegisterType( rdControlLinearNode() );

	rdObject::RegisterType( rdActuatorSet() );
	rdObject::RegisterType( rdForce() );
	rdObject::RegisterType( rdGeneralizedForce() );
	rdObject::RegisterType( rdTorque() );
	//rdObject::RegisterType( rdMuscle() );

	rdObject::RegisterType( rdContactForceSet() );


	//rdObject::RegisterType( rdIntegCallbackSet() );
	//rdObject::RegisterType( rdDerivCallbackSet() );

}

