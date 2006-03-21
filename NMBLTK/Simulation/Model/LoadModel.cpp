// LoadModel.cpp
// author: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <string>
#include <iostream>
#include "LoadModel.h"
#include "rdActuatorSet.h"
#include "rdContactForceSet.h"

using namespace std;

extern "C" {

// Type definition for the CreateModel() function
// This is necessary to create a pointer that can properly point to the
// CreateModel() function.
typedef rdModel* (*CREATEMODEL)();
typedef rdModel* (*CREATEMODEL_FILE)(const string &);
typedef rdModel* (*CREATEMODEL_ActuatorsContacts)(rdActuatorSet*,rdContactForceSet*);
typedef rdModel* (*CREATEMODEL_ParamsActuatorsContacts)(const string&,rdActuatorSet*,rdContactForceSet*);

}


static void PrintUsage(ostream &aOStream);


//_____________________________________________________________________________
/**
 * A Wrapper around Window's LoadLibrary that implements library naming convention 
 * and loading policy on windows which follows:
 * If you're loading rdSimulation_D and other libraries that do not have a trailing _D
 * an _D is apprended to the library file name. If loading of that fails, we revert to using
 * the non _D file instead, if that fails we give error and return 0. Reciprocal treatment from
 * release libraries is implemented. I tried to keep this function in the same file to try
 * to localize platform specific code. -Ayman
 * 
 */

RDSIMULATION_API
HMODULE
WINAPI
LoadOpenSimLibrary(const char *lpLibFileName)
{
	string actualLibFileName(lpLibFileName);
	string debugSuffix="_D";
	char* locationOf_D=strstr(lpLibFileName, debugSuffix.c_str());
	bool hasDebugSuffix = (locationOf_D!= 0) && (strcmp(locationOf_D, debugSuffix.c_str())==0);

	HINSTANCE	libraryHandle;
#ifdef _DEBUG
	// if library name has no trailing _D try to append it and load
	// find locaion of _D in lpLibFileName and make sure it's trailing
	if (!hasDebugSuffix){
		// Append _D to lpLibFileName;
		cout << "WARNING: SUSPECT LOADING RELEASE LIB INTO DEBUG Simulation library." << endl;
		cout << "Trying to load a debug version ..." << endl;
		actualLibFileName = string(lpLibFileName)+debugSuffix;
		// if that fails we'll try the one with no _D 
		if ((libraryHandle = LoadLibrary(actualLibFileName.c_str()))==0){
			cout << "Loading of Debug library " << actualLibFileName << "Failed. Trying lpLibFileName .." << endl;
			// library with _D loading failed, try non _D version
			actualLibFileName = string(lpLibFileName);
			if ((libraryHandle = LoadLibrary(actualLibFileName.c_str()))==0){
				cout << "Loaded library " << actualLibFileName << endl;
			}
			else
				cout << "Failed to load either debug or release library " << actualLibFileName << endl;
		}
		else
			cout << "Loaded library " << actualLibFileName << endl;
	}
#else
	// Here we're in release mode, highly unlikely to have a trailing _D intentionally!
	if (hasDebugSuffix){

		// try stripping the trailing _D first 
		cout << "WARNING: SUSPECT LOADING DEBUG LIB INTO RELEASE rdSimulation";
		cout << "Trying ";
		if ((libraryHandle = LoadLibrary(actualLibFileName.c_str()))==0){
			*locationOf_D= '\0';	// Strip trailing _D and retry (can we do that with const!)
			if ((libraryHandle = LoadLibrary(actualLibFileName.c_str()))==0){
				cout << "Loaded library " << actualLibFileName << endl;
			}
			else
				cout << "Failed to load either debug or release library " << actualLibFileName << endl;

		}
		else
			cout << "Loaded library " << actualLibFileName << endl;

	}
	else
		libraryHandle = LoadLibrary(actualLibFileName.c_str());
#endif
	return libraryHandle;
}

//_____________________________________________________________________________
/**
 * Load and create a model from a dynamically loaded library (DLL).
 *
 * @param aModelLibraryName Name of the model DLL (e.g., rdBlock_D).  Do not
 * include the library (.lib) or DLL (.dll) extension in the name of the
 * model library.
 * @return Pointer to an intance of the model, NULL if no model was created.
 */
RDSIMULATION_API rdModel* LoadModel(const string &aModelLibraryName)
{
	// LOAD MODEL LIBRARY
	HINSTANCE modelLibrary = LoadOpenSimLibrary(aModelLibraryName.c_str());
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
 * @param argc Number of character strings in argv.
 * @param argv Array of character strings.
 * @return Pointer to an intance of the model, NULL if no model was created.
 */
RDSIMULATION_API rdModel* LoadModel(int argc,char **argv)
{
	// VARIABLES
	int i;
	string option,value;
	HINSTANCE library;

	// PARSE THE COMMAND LINE FOR OTHER OPTIONS
	string actuators="",contacts="",params="";
	string modelFileName="",modelLibraryName="";
	for(i=1;i<argc;i++) {

		if(argv[i][0] != '-') continue;
		option = argv[i];

		if((argc<=1)||(option=="-help")||(option=="-h")||(option=="-Help")||(option=="-H")
			||(option=="-usage")||(option=="-u")||(option=="-Usage")||(option=="-U")) {
			PrintUsage(cout);
			return(NULL);

		} else if((option=="-Actuators")||(option=="-A")) {
			if((i+1)>=argc) continue;
			if(actuators=="") actuators = argv[i+1];

		} else if((option=="-Contacts")||(option=="-C")) {
			if((i+1)>=argc) continue;
			if(contacts=="") contacts = argv[i+1];

		} else if((option=="-Params")||(option=="-P")) {
			if((i+1)>=argc) continue;
			if(params=="") params = argv[i+1];

		} else if((option=="-ModelFile")||(option=="-MF")) {
			if((i+1)>=argc) continue;
			if(modelFileName=="") modelFileName = argv[i+1];

		} else if((option=="-ModelLibrary")||(option=="-ML")) {
			if((i+1)>=argc) continue;
			if(modelLibraryName=="") modelLibraryName = argv[i+1];

		} else if((option=="-Library")||(option=="-L")) {
			// DO NOTHING
			// -Library is a valid option.  Just not acting on it here.
		
		} else if((option=="-Setup")||(option=="-S")) {
			// DO NOTHING
			// -Setup is a valid option.  Just not acting on it here.
		
		} else {
			cout<<"WARN- "<<option<<" is an unknown option.\n";
		}
	}

	// LOAD AUXILIARY LIBRARIES FIRST
	for(i=0;i<argc;i++) {
		if(argv[i][0]!='-') continue;
		option = argv[i];
		if((i+1)>=argc) break;  // no more arguments.
		if((option=="-Library")||(option=="-L")) {
			string libraryName = argv[i+1];
			library = LoadOpenSimLibrary(libraryName.c_str());
			if(library==NULL) {
				cout<<"ERROR- library "<<value<<" could not be loaded.\n\n";
			} else {
				i++;
			}
		}
	}

	// CONSTRUCT ACTUATOR SET
	rdActuatorSet *actuatorSet=NULL;
	if(actuators!="") {
		actuatorSet = new rdActuatorSet(actuators.c_str());
		if(actuatorSet==NULL) {
			cout<<"ERROR- actuator set "<<actuators<<" could not be constructed.\n\n";
		} else {
			cout<<"Constructed actuator set from file "<<actuators<<".\n";
		}
	}

	// CONSTRUCT CONTACT FORCE SET
	rdContactForceSet *contactForceSet=NULL;
	if(contacts!="") {
		contactForceSet = new rdContactForceSet(contacts.c_str());
		if(contactForceSet==NULL) {
			cout<<"ERROR- contact force set "<<contacts<<" could not be constructed.\n\n";
		} else {
			cout<<"Constructed contact force set from file "<<contacts<<".\n";
		}
	}


	// LOAD MODEL LIBRARY
	HINSTANCE modelLibrary = LoadOpenSimLibrary(modelLibraryName.c_str());
	if(modelLibrary==NULL) {
		cout<<"ERROR- library for model "<<modelLibraryName<<" could not be loaded.\n\n";
		return(NULL);
	}

	// CREATE MODEL
	rdModel *model = NULL;
	// Model file (deserialize)
	if(modelFileName!="") {

		// GET POINTER TO THE CreateModel() FUNCTION
		CREATEMODEL_FILE createModelFunction = (CREATEMODEL_FILE)GetProcAddress(modelLibrary,"CreateModel_File");
		if(createModelFunction==NULL) {
			cout<<"ERROR- function CreateModel_File() was not found in library "<<modelLibraryName<<".\n\n";
			return(NULL);
		}

		// CREATE THE MODEL
		model = createModelFunction(modelFileName);
		if(model==NULL) {
			cout<<"ERROR- model "<<modelLibraryName<<" was not created.\n\n";
			return(NULL);
		}

	// Params file and actuator and/or contact set
	} else if(params!="") {

		// GET POINTER TO THE CreateModel() FUNCTION
		CREATEMODEL_ParamsActuatorsContacts createModelFunction =
			(CREATEMODEL_ParamsActuatorsContacts)GetProcAddress(modelLibrary,
			"CreateModel_ParamsActuatorsContacts");
		if(createModelFunction==NULL) {
			cout<<"ERROR- function CreateModel_ParamsActuatorsContacts() was not found in library "<<modelLibraryName<<".\n\n";
			return(NULL);
		}

		// CREATE THE MODEL
		model = createModelFunction(params,actuatorSet,contactForceSet);
		if(model==NULL) {
			cout<<"ERROR- model "<<modelLibraryName<<" was not created.\n\n";
			return(NULL);
		}

	// Actuator and/or contact set
	} else if((actuatorSet!=NULL)||(contactForceSet!=NULL)) {

		// GET POINTER TO THE CreateModel() FUNCTION
		CREATEMODEL_ActuatorsContacts createModelFunction =
			(CREATEMODEL_ActuatorsContacts)GetProcAddress(modelLibrary,
			"CreateModel_ActuatorsContacts");
		if(createModelFunction==NULL) {
			cout<<"ERROR- function CreateModel_ActuatorsContacts() was not found in library "<<modelLibraryName<<".\n\n";
			return(NULL);
		}

		// CREATE THE MODEL
		model = createModelFunction(actuatorSet,contactForceSet);
		if(model==NULL) {
			cout<<"ERROR- model "<<modelLibraryName<<" was not created.\n\n";
			return(NULL);
		}

	// Default
	} else {

		// GET POINTER TO THE CreateModel() FUNCTION
		CREATEMODEL createModelFunction = (CREATEMODEL)GetProcAddress(modelLibrary,"CreateModel");
		if(createModelFunction==NULL) {
			cout<<"ERROR- function CreateModel() was not found in library "<<modelLibraryName<<".\n\n";
			return(NULL);
		}

		// CREATE THE MODEL
		model = createModelFunction();
		if(model==NULL) {
			cout<<"ERROR- model "<<modelLibraryName<<" was not created.\n\n";
			return(NULL);
		}
	}

	return(model);
}

//_____________________________________________________________________________
/**
 * Print the usage for this application
 */
void PrintUsage(ostream &aOStream)
{
	aOStream<<"Options for LoadModel(int argc,char **argv):\n";
	aOStream<<"\t-Help or -H           Print the options for LoadModel(int argc,char **argv)\n";
	aOStream<<"\t-ModelLibrary or -ML  NameOfModelLibrary (do not include the library extension [e.g., .dll or .lib])\n";
	aOStream<<"\t-ModelFile or -MF     NameOfModelDeserializationFile (including path)\n";
	aOStream<<"\t-Actuators or -A      NameOfActuatorSet (including path)\n";
	aOStream<<"\t-Contacts or -C       NameofContactSet (including path)\n";
	aOStream<<"\t-Params or -P         NameOfPipelineParamsFile (including path)\n";
	aOStream<<"\t-Library or -L        NameOfAdditionalLibraryToLoad (to load more than one library,\n";
	aOStream<<"\t                      add as many -Library options as needed)\n";
}



