// LoadModel.cpp
// author: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <string>
#include <iostream>
#include "LoadModel.h"

using namespace std;

// Type definition for the CreateModel() function
// This is necessary to create a pointer that can properly point to the
// CreateModel() function.
typedef rdModel* (CALLBACK* CREATEMODEL)();

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






