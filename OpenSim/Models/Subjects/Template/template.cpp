// _Template_.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Author:  Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include <iostream>
#include <string>
#include <OpenSim/Models/SIMMPipeline/4.0/Pipeline40Workflow/Pipeline40Workflow.h>
#include "_Template_.h"



using namespace OpenSim;
using namespace std;

//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
_Template_::~_Template_()
{
}
//_____________________________________________________________________________
/**
 * Default constructor.
 */
_Template_::
_Template_(const std::string &aParametersFileName,
	ActuatorSet *aActuators,ContactForceSet *aContacts) :
	Pipeline40Workflow(aParametersFileName,aActuators,aContacts)
{
	setNull();
	setName("_Template_");
}


//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Set member variables to their appropriate null values.
 */
void _Template_::
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
	_Template_ *model = new _Template_("params.txt");
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
	cout<<"_Template_.CreateModel()- not implemented.\n";
	return(NULL);
}

//_____________________________________________________________________________
/**
 * Deserialization from file.
 */
RDSDFAST_API Model*
CreateModel_File(const string &aModelFile)
{
	cout<<"_Template_.CreatModel_File()- not yet implemented.\n";
	return(NULL);
}

//_____________________________________________________________________________
/**
 * Constructor for an actuator set and a contact set.
 */
RDSDFAST_API Model*
CreateModel_ActuatorsContacts(ActuatorSet *aActuatorSet,ContactForceSet *aContactSet)
{
	cout<<"_Template_.CreatModel_ActuatorsContacts()- not yet implemented.\n";
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
	_Template_ *model = new _Template_(aParamsFile,aActuatorSet,aContactSet);
	return(model);
}

}




