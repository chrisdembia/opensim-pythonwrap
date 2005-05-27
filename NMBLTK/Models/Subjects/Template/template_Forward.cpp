// su_Template__Forward.cpp

#include <string>
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Tools/rdIO.h>
#include <NMBLTK/Simulation/Manager/rdManager.h>
#include <NMBLTK/Simulation/Control/rdControlLinear.h>
#include <NMBLTK/Simulation/Control/rdControlSet.h>
#include <NMBLTK/Analyses/suKinematics.h>
#include <NMBLTK/Analyses/suPointKinematics.h>
#include <NMBLTK/Analyses/suActuation.h>
#include <NMBLTK/Analyses/suContact.h>
#include <NMBLTK/Analyses/suLinearSpring.h>
#include <NMBLTK/Analyses/suActuatorGeneralizedForces.h>
#include <NMBLTK/Analyses/suGeneralizedForces.h>
#include <NMBLTK/Analyses/suBodyKinematics.h>
#include <NMBLTK/Simulation/Model/rdAnalysisSet.h>
#include "su_Template_.h"
using namespace std;

int main()
{
	int i;
	rdIO::SetPrecision(12);

	// REGISTER TYPES
	rdObject::RegisterType(rdControlLinear());
	rdObject::RegisterType(rdControlLinearNode());

	// INPUT----
	// Controls
	string prefix = "_template_";
	string controlsName = prefix + "cmc.ctr";
	cout<<endl<<endl<<"Loading controls from "<<controlsName<<"..."<<endl;
	rdControlSet controlSet(controlsName);
	cout<<"Found "<<controlSet.getSize()<<" controls."<<endl;

	// MODEL----
	std::string parmFile="./params.txt";
	su_Template_ model(parmFile);

	// Initial states
	rdArray<double> yi(0.0,model.getNY());
	model.getInitialStates(&yi[0]);
	int ny = model.getNY();
	cout<<"\nInitial States:"<<endl;
	for(i=0;i<ny;i++) {
		cout<<model.getStateName(i)<<"["<<i<<"]= "<<yi[i]<<endl;
	}

	// ANALYSES----
	// Kinematics
	suKinematics *kin = new suKinematics(&model);
	model.addAnalysis(kin);
	// Actuation
	suActuation *actuation = new suActuation(&model);
	model.addAnalysis(actuation);
	actuation->setOn(true);
	// Contact
	suContact *contact = new suContact(&model);
	model.addAnalysis(contact);

	suBodyKinematics *bodyKin = new suBodyKinematics(&model);
	model.addAnalysis(bodyKin);

	// SIMULATION SETUP----
	// Manager
	rdManager manager(&model,&controlSet);
	manager.setSessionName("_template_");

	// Initial and final times
	int first = 0;
	rdControlLinear *control = (rdControlLinear*)controlSet.get(first);
	double ti = control->getFirstTime();
	double tf = control->getLastTime();
	cout<<endl<<endl<<"ti="<<ti<<" tf="<<tf<<endl<<endl;
	manager.setInitialTime(ti);
	manager.setFinalTime(tf);

	// Integrator settings
	int maxSteps = 20000;
	rdIntegRKF *integ = manager.getIntegrator();
	integ->setMaximumNumberOfSteps(maxSteps);
	integ->setUseConstantDT(false);
	//integ->setDT(0.00087);
	integ->setMaxDT(1.0e-3);
	integ->setTolerance(1.0e-5);
	integ->setFineTolerance(5.0e-7);


	// INTEGRATE
	cout<<"\n\nIntegrating from "<<ti<<" to "<<tf<<endl;

	manager.integrate();

	// RESULTS
	// Storage
	rdStorage *yStore = integ->getStateStorage();
	rdStorage *ypStore = integ->getPseudoStateStorage();
	rdStorage *xStore = integ->getControlStorage();

	// Print
	double dt = -1.0;
	xStore->print("Results/_template__controls.sto");
	yStore->print("Results/_template__states.sto");
	rdAnalysisSet *analysisSet = model.getAnalysisSet();
	for(i=0; i< analysisSet->getSize(); i++)
		analysisSet->getAnalysis(i)->printResults((char*)prefix.c_str(),"Results",dt);
	return(0);
}
