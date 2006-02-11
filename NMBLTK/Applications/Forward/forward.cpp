// forward.cpp
// author:  Frank C. Anderson

// INCLUDE
#include <string>
#include <iostream>
#include <NMBLTK/Tools/rdMtx.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include <NMBLTK/Simulation/Model/LoadModel.h>
#include <NMBLTK/Simulation/Model/rdAnalysisSet.h>
#include <NMBLTK/Analyses/InvestigationForward.h>
#include <NMBLTK/Analyses/suKinematics.h>


using namespace std;

//_____________________________________________________________________________
/**
 * Main routine for executing a forward integration and running a set of
 * analyses during the forward integration.
 */
int main(int argc,char **argv)
{

	/*
	// INTERPRET COMMAND LINE
	int i;
	string option = "";
	string setupFileName = "";
	if(argc<=2) {
		cout<<"\n\nusage: forward.exe -Setup setupFile.xml\n\n";
		exit(-1);
	}
	for(i=1;i<(argc-1);i++) {
		option = argv[i];
		if(option == "-Setup") {
			setupFileName = argv[i+1];
			break;
		}
	}
	*/

	// LOAD MODEL
	rdModel *model = LoadModel(argc,argv);
	if(model==NULL) {
		cout<<"\nperturb:  ERROR- failed to load model.\n";
		exit(-1);
	}
	cout<<"-----------------------------------------------------------------------\n";
	cout<<"Loaded library\n";
	cout<<"-----------------------------------------------------------------------\n";
	model->printBasicInfo(cout);
	cout<<"-----------------------------------------------------------------------\n\n";

	
	// ANALYSIS SET
	rdAnalysisSet *analysisSet = new rdAnalysisSet();
	analysisSet->setName("test");
	rdObject::setSerializeAllDefaults(true);
	analysisSet->append( new suKinematics() );
	analysisSet->print("default_analysis_set.xml");


	/*
	// CONSTRUCT INVESTIGATION
	cout<<"Constructing investigation from setup file "<<setupFileName<<".\n\n";
	InvestigationForward forward(setupFileName);
	forward.print("test.xml");

	// RUN
	cout<<"Running..."<<endl<<endl;
	//forward.setModel(model);
	//forward.run();
	*/

	return(0);
}

