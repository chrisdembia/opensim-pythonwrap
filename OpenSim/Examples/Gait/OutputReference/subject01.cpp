// subject01.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Author:  Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include <iostream>
#include <string>
#include <OpenSim/Models/SIMMPipeline/4.0/Pipeline40Workflow/suPipeline40Workflow.h>
#include "subject01.h"



using namespace OpenSim;
using namespace std;

//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
subject01::~subject01()
{
}
//_____________________________________________________________________________
/**
 * Default constructor.
 */
subject01::
subject01(const std::string &aParametersFileName,
	ActuatorSet *aActuators,ContactForceSet *aContacts) :
	suPipeline40Workflow(aParametersFileName,aActuators,aContacts)
{
	setNull();
	setName("subject01");
}


//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Set member variables to their appropriate null values.
 */
void subject01::
setNull()
{
}


//=============================================================================
// STATIC METHOD FOR CREATING THIS MODEL
//=============================================================================
/*
extern "C" {

RDSDFAST_API Model* CreateModel()
{
	subject01 *model = new subject01("params.txt");
	return(model);
}

}
*/


extern "C" {

//=============================================================================
// STATIC METHOD FOR CREATING THIS MODEL
//=============================================================================
//_____________________________________________________________________________
/**
 * Default constructor.
 */
RDSDFAST_API Model*
CreateModel()
{
	cout<<"subject01.CreateModel()- not implemented.\n";
	return(NULL);
}

//_____________________________________________________________________________
/**
 * Deserialization from file.
 */
RDSDFAST_API Model*
CreateModel_File(const string &aModelFile)
{
	cout<<"subject01.CreatModel_File()- not yet implemented.\n";
	return(NULL);
}

//_____________________________________________________________________________
/**
 * Constructor for an actuator set and a contact set.
 */
RDSDFAST_API Model*
CreateModel_ActuatorsContacts(ActuatorSet *aActuatorSet,ContactForceSet *aContactSet)
{
	cout<<"subject01.CreatModel_ActuatorsContacts()- not yet implemented.\n";
	return(NULL);
}
//_____________________________________________________________________________
/**
 * Constructor for a SIMM Pipeline 4.0 model.
 */
RDSDFAST_API Model*
CreateModel_ParamsActuatorsContacts(const string &aParamsFile,
	ActuatorSet *aActuatorSet,ContactForceSet *aContactSet)
{
	subject01 *model = new subject01(aParamsFile,aActuatorSet,aContactSet);
	return(model);
}

}




