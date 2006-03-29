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

string filesToCompare[] = {
							"check.xml",
							"test_Kinematics_u.sto",
							"test_Kinematics_dudt.sto",
							"test_Kinematics_q.sto",
							"test_ActuatorGeneralizedForces.sto",
							"test_BodyKinematics_vel.sto",
							"test_BodyKinematics_acc.sto",
							"test_BodyKinematics_pos.sto"
};

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
	string setupFileName = "forward.xml";
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

	/* Compare results with standard*/
	bool success = true;
	for (int i=0; i < 8 && success; i++){
		string command = "cmp "+filesToCompare[i]+" "+"std_"+filesToCompare[i];
		success = success && (system(command.c_str())==0);
	}

	return (success?0:1);

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

