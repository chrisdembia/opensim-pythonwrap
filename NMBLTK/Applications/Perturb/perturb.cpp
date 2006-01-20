// perturb.cpp
// author:  Frank C. Anderson

// INCLUDE
#include <string>
#include <iostream>
#include <NMBLTK/Tools/rdMtx.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include <NMBLTK/Simulation/Model/LoadModel.h>
#include <NMBLTK/Analyses/InvestigationPerturbation.h>

using namespace std;

//_____________________________________________________________________________
/**
 * Main routine for conducting a perturbation analysis.
 */
int main(int argc,char **argv)
{

	// REGISTER TYPES
	rdObject::RegisterType(InvestigationPerturbation());

	// INTERPRET COMMAND LINE
	string setupFileName = "";
	string modelName = "";
	if(argc!=3) {
		cout<<"\n\nusage: perturb.exe setupFile.xml modelName\n\n";
		exit(-1);
	} else {
		setupFileName = argv[1];
		modelName = argv[2];
	}

	// CONSTRUCT INVESTIGATION
	cout<<"Loading perturbation setup file "<<setupFileName<<".\n\n";
	InvestigationPerturbation perturb(setupFileName);

	// LOAD MODEL
	rdModel *model1 = LoadModel(modelName);
	if(model1!=NULL) {
		cout<<"-----------------------------------------------------------------------\n";
		cout<<"Loaded library  "<<modelName<<"\n";
		cout<<"-----------------------------------------------------------------------\n";
		model1->printBasicInfo(cout);
		cout<<"-----------------------------------------------------------------------\n\n";
	}

	// RUN
	cout<<"Running..."<<endl<<endl;
	//perturb.setModel(model);
	//perturb.run();

	//
	return(0);
}