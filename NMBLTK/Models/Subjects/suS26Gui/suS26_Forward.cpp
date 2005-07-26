// suS26_Forward.cpp

#include <string>
#include <rdMath.h>
#include <rdIO.h>
#include <rdManager.h>
#include <rdControlLinear.h>
#include <rdControlSet.h>
#include <rdModelTestSuite.h>
#include <suKinematics.h>
#include <suPointKinematics.h>
#include <suActuation.h>
#include <suContact.h>
#include <suLinearSpring.h>
#include <suS26.h>
#include "suActuatorGeneralizedForces.h"
#include "suGeneralizedForces.h"
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
	string prefix = "s26";
	string controlsName = prefix + "cmc.ctr";
	cout<<endl<<endl<<"Loading controls from "<<controlsName<<"..."<<endl;
	rdControlSet controlSet(controlsName);
	cout<<"Found "<<controlSet.getSize()<<" controls."<<endl;

	// MODEL----
	std::string parmFile="./params.txt";
	suS26 model(parmFile);

	// Initial states
	rdArray<double> yi(0.0,model.getNY());
	model.getInitialStates(&yi[0]);
	int ny = model.getNY();
	cout<<"\nInitial States:"<<endl;
	for(i=0;i<ny;i++) {
		cout<<model.getStateName(i)<<"["<<i<<"]= "<<yi[i]<<endl;
	}

	// Bodies
	cout<<endl<<endl<<"Bodies:"<<endl;
	int nb = model.getNB();
	for(i=0;i<nb;i++) {
		cout<<"body["<<i<<"]= "<<model.getBodyName(i)<<endl;
	}
	cout<<endl;


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

	// SIMULATION SETUP----
	// Manager
	rdManager manager(&model,&controlSet);
	manager.setSessionName("s26");

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
	xStore->print("Data/s26_GAS_Up_Double_controls.sto");
	yStore->print("Data/s26_GAS_Up_Double_states.sto");
	kin->getPositionStorage()->setWriteSIMMHeader(true);
	kin->printResults((char*)prefix.c_str(),"Data",dt);
	actuation->printResults((char*)prefix.c_str(),"Data",dt);
	contact->printResults((char*)prefix.c_str(),"Data",dt);
	return(0);
}
