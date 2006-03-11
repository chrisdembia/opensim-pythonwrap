// su900061.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Author:  Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include <iostream>
#include <string>
#include <NMBLTK/Models/SIMMPipeline/4.0/Pipeline40Workflow/suPipeline40Workflow.h>
#include "su900061.h"

using namespace std;

//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
su900061::~su900061()
{
}
//_____________________________________________________________________________
/**
 * Default constructor.
 */
su900061::
su900061(const std::string &aParametersFileName,
	rdActuatorSet *aActuators,rdContactForceSet *aContacts) :
	suPipeline40Workflow(aParametersFileName,aActuators,aContacts)
{
	setNull();
}


//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Set member variables to their appropriate null values.
 */
void su900061::
setNull()
{
}


//=============================================================================
// STATIC METHOD FOR CREATING THIS MODEL
//=============================================================================
/*
extern "C" {

RDSDFAST_API rdModel* CreateModel()
{
	su900061 *model = new su900061("params.txt");
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
RDSDFAST_API rdModel*
CreateModel()
{
	cout<<"su900061.CreateModel()- not implemented.\n";
	return(NULL);
}

//_____________________________________________________________________________
/**
 * Deserialization from file.
 */
RDSDFAST_API rdModel*
CreateModel_File(const string &aModelFile)
{
	cout<<"su900061.CreatModel_File()- not yet implemented.\n";
	return(NULL);
}

//_____________________________________________________________________________
/**
 * Constructor for an actuator set and a contact set.
 */
RDSDFAST_API rdModel*
CreateModel_ActuatorsContacts(rdActuatorSet *aActuatorSet,rdContactForceSet *aContactSet)
{
	cout<<"su900061.CreatModel_ActuatorsContacts()- not yet implemented.\n";
	return(NULL);
}
//_____________________________________________________________________________
/**
 * Constructor for a SIMM Pipeline 4.0 model.
 */
RDSDFAST_API rdModel*
CreateModel_ParamsActuatorsContacts(const string &aParamsFile,
	rdActuatorSet *aActuatorSet,rdContactForceSet *aContactSet)
{
	su900061 *model = new su900061(aParamsFile,aActuatorSet,aContactSet);
	return(model);
}

}




