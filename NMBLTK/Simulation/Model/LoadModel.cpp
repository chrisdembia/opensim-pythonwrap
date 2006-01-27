// LoadModel.cpp
// author: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <string>
#include <iostream>
#include "LoadModel.h"
#include "rdActuatorSet.h"
#include "rdContactForceSet.h"

using namespace std;

// Type definition for the CreateModel() function
// This is necessary to create a pointer that can properly point to the
// CreateModel() function.
typedef rdModel* (CALLBACK* CREATEMODEL)();
typedef rdModel* (CALLBACK* CREATEMODEL_FILE)(const string &aModelFile);
typedef rdModel* (CALLBACK* CREATEMODEL_ActuatorContact)(rdActuatorSet *aActuatorSet,rdContactForceSet *aContactSet);
typedef rdModel* (CALLBACK* CREATEMODEL_ParamsActuatorContact)(const string &aParamsFile,rdActuatorSet *aActuatorSet,rdContactForceSet *aContactSet);


/*
rdModel* CreateModel();
rdModel* CreateModel_File(const string &aModelFile);
rdModel* CreateModel_ActuatorContact(rdActuatorSet *aActuatorSet,rdContactForceSet *aContactSet);
rdModel* CreateModel_ParamsActuatorContact(const string &aParamsFile,rdActuatorSet *aActuatorSet,rdContactForceSet *aContactSet);
*/


//_____________________________________________________________________________
/**
 * Load and create a model from a dynamically loaded library (DLL).
 *
 * @param aModelLibraryName Name of the model DLL (e.g., rdBlock_D).  Do not
 * include the library (.lib) or DLL (.dll) extension in the name of the
 * model library.
 * @param Pointer to an instance of the model.
 */
RDSIMULATION_API rdModel* LoadModel(const string &aModelLibraryName)
{
	// LOAD MODEL LIBRARY
	HINSTANCE modelLibrary = LoadLibrary(aModelLibraryName.c_str());
	if(modelLibrary==NULL) {
		cout<<"ERROR- library for model "<<aModelLibraryName<<" could not be loaded.\n\n";
		return(NULL);
	}

	// GET POINTER TO THE CreateModel() FUNCTION
	CREATEMODEL createModelFunction = (CREATEMODEL)GetProcAddress(modelLibrary,"CreateModel");
	if(createModelFunction==NULL) {
		cout<<"ERROR- function CreateModel() was not found in library "<<aModelLibraryName<<".\n\n";
		return(NULL);
	}

	// CALL THE CreatModel() FUNCTION
	rdModel *model = createModelFunction();
	if(model==NULL) {
		cout<<"ERROR- model "<<aModelLibraryName<<" was not created.\n\n";
		return(NULL);
	}
	
	return(model);
}


//_____________________________________________________________________________
/**
 * Load and create a model from a dynamically loaded library (DLL).
 *
 * @param aModelLibraryName Name of the model DLL (e.g., rdBlock_D).  Do not
 * include the library (.lib) or DLL (.dll) extension in the name of the
 * model library.
 * @param Pointer to an instance of the model.
 */
RDSIMULATION_API rdModel* LoadModel(int argc,char **argv)
{
	// VARIABLES
	int i;
	string option,value;
	HINSTANCE library;

	// LOAD AUXILIARY LIBRARIES FIRST
	for(i=0;i<argc;i++) {
		if(argv[i][0]!='-') continue;
		option = argv[i];
		if((i+1)>=argc) break;  // no more arguments.
		if((option=="-Library")||(option=="-L")) {
			library = LoadLibrary(argv[i+i]);
			if(library==NULL) {
				cout<<"ERROR- library "<<value<<" could not be loaded.\n\n";
			} else {
				i++;
			}
		}
	}

	// PARSE THE COMMAND LINE FOR OTHER OPTIONS
	string actuators="",contacts="",params="";
	string modelFileName="",modelLibraryName="";
	for(i=0;i<(argc-1);i++) {

	if(argv[i][0] != '-') continue;
	option = argv[i];

	if((option=="-Actuators")||(option=="-A")) {
		if(actuators=="") actuators = argv[i+1];

	} else if((option=="-Contacts")||(option=="-C")) {
		if(contacts=="") contacts = argv[i+1];

	} else if((option=="-Params")||(option=="-P")) {
		if(params=="") params = argv[i+1];

	} else if((option=="-ModelFile")||(option=="-MF")) {
		if(modelFileName=="") modelFileName = argv[i+1];

	} else if((option=="-ModelLibrary")||(option=="-ML")) {
		if(modelLibraryName=="") modelLibraryName = argv[i+1];
	
	} else {
		cout<<"WARN- "<<option<<" is an unknown option.\n";
	}
	}

	// CONSTRUCT ACTUATOR SET
	rdActuatorSet *actuatorSet=NULL;
	if(actuators!="") {
		actuatorSet = new rdActuatorSet(actuators.c_str());
		if(actuatorSet==NULL) {
			cout<<"ERROR- actuator set "<<actuators<<" could not be constructed.\n\n";
		} else {
			cout<<"Constructed actuator set "<<actuators<<".\n";
		}
	}

	// CONSTRUCT CONTACT FORCE SET
	rdContactForceSet *contactForceSet=NULL;
	if(contacts!="") {
		contactForceSet = new rdContactForceSet(contacts.c_str());
		if(contactForceSet==NULL) {
			cout<<"ERROR- contact force set "<<contacts<<" could not be constructed.\n\n";
		} else {
			cout<<"Constructed contact force set "<<contacts<<".\n";
		}
	}

	// LOAD MODEL LIBRARY
	HINSTANCE modelLibrary = LoadLibrary(modelLibraryName.c_str());
	if(modelLibrary==NULL) {
		cout<<"ERROR- library for model "<<modelLibraryName<<" could not be loaded.\n\n";
		return(NULL);
	}

	// GET POINTER TO THE CreateModel() FUNCTION
	CREATEMODEL createModelFunction = (CREATEMODEL)GetProcAddress(modelLibrary,"CreateModel");
	if(createModelFunction==NULL) {
		cout<<"ERROR- function CreateModel() was not found in library "<<modelLibraryName<<".\n\n";
		return(NULL);
	}

	// CREATE THE MODEL
	rdModel *model = createModelFunction();
	if(model==NULL) {
		cout<<"ERROR- model "<<modelLibraryName<<" was not created.\n\n";
		return(NULL);
	}
	
	return(model);
}

