// forward.cpp
// author:  Frank C. Anderson

// INCLUDE
#include <string>
#include <iostream>
#include <NMBLTK/Tools/rdMtx.h>
#include <NMBLTK/Tools/rdIO.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include <NMBLTK/Simulation/Model/LoadModel.h>
#include <NMBLTK/Simulation/Model/rdAnalysisSet.h>
#include <NMBLTK/Analyses/InvestigationForward.h>
#include <NMBLTK/Analyses/suKinematics.h>
#include <NMBLTK/Analyses/suActuation.h>
#include <NMBLTK/Analyses/suPointKinematics.h>
#include <NMBLTK/Analyses/suBodyKinematics.h>
#include <NMBLTK/Analyses/suActuatorGeneralizedForces.h>


using namespace std;


static void PrintUsage(ostream &aOStream);


//_____________________________________________________________________________
/**
 * Main routine for executing a forward integration and running a set of
 * analyses during the forward integration.
 */
int main(int argc,char **argv)
{
	// PARSE COMMAND LINE
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
			rdObject::setSerializeAllDefaults(false);
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
	// CONSTRUCT
	cout<<"Constructing investigation from setup file "<<setupFileName<<".\n\n";
	InvestigationForward forward(setupFileName);
	forward.print("check.xml");

	// PRINT MODEL INFORMATION
	rdModel *model = forward.getModel();
	if(model==NULL) {
		cout<<"\nperturb:  ERROR- failed to load model.\n";
		exit(-1);
	}
	cout<<"-----------------------------------------------------------------------\n";
	cout<<"Loaded library\n";
	cout<<"-----------------------------------------------------------------------\n";
	model->printBasicInfo(cout);
	cout<<"-----------------------------------------------------------------------\n\n";

	// RUN
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
}

