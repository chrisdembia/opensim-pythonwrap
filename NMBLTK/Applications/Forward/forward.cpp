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


static void PrintUsage(ostream &aOStream);


//_____________________________________________________________________________
/**
 * Main routine for executing a forward integration and running a set of
 * analyses during the forward integration.
 */
int main(int argc,char **argv)
{
	// INTERPRET COMMAND LINE
	int i;
	string option = "";
	string setupFileName = "";
	if(argc<=2) {
		PrintUsage(cout);
		return(-1);
	}
	for(i=1;i<(argc-1);i++) {
		option = argv[i];

		// PRINT THE USAGE OPTIONS
		if((option=="-help")||(option=="-h")||(option=="-Help")||(option=="-H")||
		(option=="-usage")||(option=="-u")||(option=="-Usage")||(option=="-U")) {
			PrintUsage(cout);
			return(0);
 
		// PRINT A DEFAULT SETUP FILE FOR THIS INVESTIGATION
		} else if((option=="-PrintSetup")||(option=="-PS")) {
			InvestigationForward *investigation = new InvestigationForward();
			investigation->setName("default");
			rdObject::setSerializeAllDefaults(true);
			investigation->print("default_forward.xml");
			return(0);

		// IDENTIFY SETUP FILE
		} else if((option=="-Setup")||(option=="-S")) {
			setupFileName = argv[i+1];
			break;
		}

	}


	// ERROR CHECK
	if(setupFileName=="") {
		cout<<"\n\nforward.exe: ERROR- A setup file must be specified.\n";
		PrintUsage(cout);
		return(-1);
	}


	// MODEL LOADING
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

	
	// INVESTIGATION
	// Construct
	cout<<"Constructing investigation from setup file "<<setupFileName<<".\n\n";
	InvestigationForward forward(setupFileName);
	forward.print("check.xml");
	// Set model
	forward.setModel(model);
	// Run
	cout<<"Running..."<<endl<<endl;
	forward.run();


	return(0);
}


//_____________________________________________________________________________
/**
 * Print the usage for this application
 */
void PrintUsage(ostream &aOStream)
{
	aOStream<<"\n\nforward.exe:\n\n";
	aOStream<<"Option              Argument            Action / Notes\n";
	aOStream<<"------              --------            --------------\n";
	aOStream<<"-Help, -H                               Print the command-line options for forward.exe.\n";
	aOStream<<"-PrintSetup, -PS                        Print a default setup file for forward.exe (default_forward.xml).\n";
	aOStream<<"-ModelLibrary, -ML  ModelLibrary        Specify/Load a model.  Do not include the library extension\n";
	aOStream<<"                                        (e.g., .dll or .lib).\n";
	aOStream<<"-ModelFile, -MF     ModelFile           Specify an xml file for the model.\n";
	aOStream<<"-Actuators, -A      ActuatorSet         Specify an xml file for an actuator set for the model.\n";
	aOStream<<"-Contacts, -C       ContactSet          Specify an xml file for a contact set file the model.\n";
	aOStream<<"-Params, -P         PipelineParamsFile  Specify a params file for a SIMM Pipeline model.\n";
	aOStream<<"-Library, -L        LibraryToLoad       Load an additional library.  To load more than one library,\n";
	aOStream<<"                                        use as many -Library options as needed.\n";
	aOStream<<"                                        Do not include the library extension (e.g., .dll or .lib).\n";
}

