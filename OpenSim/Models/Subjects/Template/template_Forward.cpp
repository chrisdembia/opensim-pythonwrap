// su_Template__Forward.cpp

#include <string>
#include <OpenSim/Tools/Math.h>
#include <OpenSim/Tools/IO.h>
#include <OpenSim/Simulation/Manager/Manager.h>
#include <OpenSim/Simulation/Control/ControlLinear.h>
#include <OpenSim/Simulation/Control/ControlSet.h>
#include <OpenSim/Analyses/Kinematics.h>
#include <OpenSim/Analyses/PointKinematics.h>
#include <OpenSim/Analyses/Actuation.h>
#include <OpenSim/Analyses/Contact.h>
#include <OpenSim/Analyses/LinearSpring.h>
#include <OpenSim/Analyses/ActuatorGeneralizedForces.h>
#include <OpenSim/Analyses/GeneralizedForces.h>
#include <OpenSim/Analyses/BodyKinematics.h>
#include <OpenSim/Simulation/Model/AnalysisSet.h>
#include "su_Template_.h"


using namespace OpenSim;
using namespace std;

int main()
{
	int i;
	IO::SetPrecision(12);

	// REGISTER TYPES
	Object::RegisterType(ControlLinear());
	Object::RegisterType(ControlLinearNode());

	// INPUT----
	// Controls
	string prefix = "_template_";
	string controlsName = prefix + "cmc.ctr";
	cout<<endl<<endl<<"Loading controls from "<<controlsName<<"..."<<endl;
	ControlSet controlSet(controlsName);
	cout<<"Found "<<controlSet.getSize()<<" controls."<<endl;

	// MODEL----
	std::string parmFile="./params.txt";
	su_Template_ model(parmFile);

	// Initial states
	Array<double> yi(0.0,model.getNY());
	model.getInitialStates(&yi[0]);
	int ny = model.getNY();
	cout<<"\nInitial States:"<<endl;
	for(i=0;i<ny;i++) {
		cout<<model.getStateName(i)<<"["<<i<<"]= "<<yi[i]<<endl;
	}

	// ANALYSES----
	// Kinematics
	Kinematics *kin = new Kinematics(&model);
	model.addAnalysis(kin);
	// Actuation
	Actuation *actuation = new Actuation(&model);
	model.addAnalysis(actuation);
	actuation->setOn(true);
	// Contact
	Contact *contact = new Contact(&model);
	model.addAnalysis(contact);

	BodyKinematics *bodyKin = new BodyKinematics(&model);
	model.addAnalysis(bodyKin);

	// SIMULATION SETUP----
	// Manager
	ModelIntegrand integrand(&model);
	integrand.setControlSet(controlSet);

	Manager manager(&integrand);
	manager.setSessionName("_template_");

	// Initial and final times
	int first = 0;
	ControlLinear *control = (ControlLinear*)controlSet.get(first);
	double ti = control->getFirstTime();
	double tf = control->getLastTime();
	cout<<endl<<endl<<"ti="<<ti<<" tf="<<tf<<endl<<endl;

	// Read actual initial states from CMC and load them into model along with associated time
	Storage initialStateStorage("_template__initialStates.sto");
	ti = initialStateStorage.getFirstTime();
	initialStateStorage.getDataAtTime(ti, model.getNY(), &yi[0]);
	model.setInitialStates(&yi[0]);

	manager.setInitialTime(ti);
	manager.setFinalTime(tf);

	// Integrator settings
	int maxSteps = 20000;
	IntegRKF *integ = manager.getIntegrator();
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
	Storage *yStore = integrand.getStateStorage();
	Storage *ypStore = integrand.getPseudoStateStorage();
	Storage *xStore = integrand.getControlStorage();

	// Print
	double dt = -1.0;
	xStore->print("Results/_template__controls.sto");
	yStore->print("Results/_template__states.sto");
	AnalysisSet *analysisSet = model.getAnalysisSet();
	for(i=0; i< analysisSet->getSize(); i++)
		analysisSet->getAnalysis(i)->printResults((char*)prefix.c_str(),"Results",dt);
	return(0);
}
