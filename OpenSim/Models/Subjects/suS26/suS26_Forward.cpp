// suS26_Forward.cpp

#include <string>
#include <OpenSim/Tools/rdMath.h>
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
#include <OpenSim/Simulation/Simm/AbstractBody.h>
#include "suS26.h"


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
	string prefix = "s26";
	string controlsName = prefix + "cmc.ctr";
	cout<<endl<<endl<<"Loading controls from "<<controlsName<<"..."<<endl;
	ControlSet controlSet(controlsName);
	cout<<"Found "<<controlSet.getSize()<<" controls."<<endl;

	// MODEL----
	std::string parmFile="./params.txt";
	suS26 model(parmFile);

	// Initial states
	Array<double> yi(0.0,model.getNumStates());
	model.getInitialStates(&yi[0]);
	int ny = model.getNumStates();
	cout<<"\nInitial States:"<<endl;
	for(i=0;i<ny;i++) {
		cout<<model.getStateName(i)<<"["<<i<<"]= "<<yi[i]<<endl;
	}

	// Bodies
	cout<<endl<<endl<<"Bodies:"<<endl;
	BodyIterator *bi = model.getDynamicsEngine().newBodyIterator();
	AbstractBody* body = bi->next();
	i = 0;
	while (body)
	{
		cout << "body[" << i++ << "] = " << body->getName() << endl;
		body = bi->next();
	}
	delete bi;
	cout<<endl;


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

	// SIMULATION SETUP----
	// Manager
	ModelIntegrand integrand(&model);
	integrand.setControlSet(controlSet);

	Manager manager(&integrand);
	manager.setSessionName("s26");

	// Initial and final times
	int first = 0;
	ControlLinear *control = (ControlLinear*)controlSet.get(first);
	double ti = control->getFirstTime();
	double tf = control->getLastTime();
	cout<<endl<<endl<<"ti="<<ti<<" tf="<<tf<<endl<<endl;
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
	xStore->print("Data/s26_GAS_Up_Double_controls.sto");
	yStore->print("Data/s26_GAS_Up_Double_states.sto");
	kin->getPositionStorage()->setWriteSIMMHeader(true);
	kin->printResults((char*)prefix.c_str(),"Data",dt);
	actuation->printResults((char*)prefix.c_str(),"Data",dt);
	contact->printResults((char*)prefix.c_str(),"Data",dt);

	return(0);
}
