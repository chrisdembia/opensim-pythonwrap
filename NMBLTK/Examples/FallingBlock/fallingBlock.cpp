// fallingBlock.cpp
// author:  Frank C. Anderson

//==============================================================================
//==============================================================================
#include <iostream>
#include <NMBLTK/Tools/rdIO.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include <NMBLTK/Simulation/Model/rdActuator.h>
#include <NMBLTK/Simulation/Model/rdActuatorSet.h>
#include <NMBLTK/Simulation/Model/rdContactForce.h>
#include <NMBLTK/Simulation/Model/rdContactForceSet.h>
#include <NMBLTK/Simulation/Model/rdForce.h>
#include <NMBLTK/Simulation/Model/rdGeneralizedForce.h>
#include <NMBLTK/Actuators/rdGeneralizedForceAtv.h>
#include <NMBLTK/Actuators/rdLinearSetPoint.h>
#include <NMBLTK/Actuators/rdPolynomialSetPoint.h>
#include <NMBLTK/Simulation/Control/rdControlConstant.h>
#include <NMBLTK/Simulation/Control/rdControlLinear.h>
#include <NMBLTK/Simulation/Control/rdControlSet.h>
#include <NMBLTK/Simulation/Manager/rdManager.h>
#include <NMBLTK/Models/Block/rdBlock.h>
#include <NMBLTK/Analyses/suAnalyses.h>
#include <NMBLTK/Analyses/suActuation.h>
#include <NMBLTK/Analyses/suContact.h>
#include <NMBLTK/Analyses/suKinematics.h>



/** Some points:

// IO
1. IO Precision can be set globally.

// ACTUATION AND CONTACT
2. Actator and contact types are registered.  This mechanism
   gives the user a way to develop their own actuator or
   contact types and use these types within the simulation
   framework.
3. The actuation and contact layer sits on top of the model.
4. Default versions of actuators and contacts can be written to file
   so that the user knows what the tunable properties are.
5. Actuator and contact sets are stored in files written in
   XML format.

// MODEL CONSTRUCTION
6. The actuator and contact sets are used when constructing the
   model.  Once the model is constructed, it is valid and can
   be used in a simulation.
7. Initial states can be specified.  Normally this would be
   done by reading the initial states from a file.
8. Gravity can be set.

// ANALYSES
9. Analyses can be added to the model.  The model only knows about
   the base-class analysis.  Any classes derived from the base
   analysis class can be added on to the model.  These analyses
   are performed during the integration.
10. Since a model is an abstract thing, the analyses can be used
    for any model (assuming the any model complies with the
    abstract specification of a model).
11. Users can develop their own analyses by deriving from
    rdAnalysis.

// SIMULATION
12. Controls can be altered.  Normally they are read in from file.
13. Controls can be any number of types (step, linear interp,
    spline, ...).  The user/developer is free to make up a new
	type of control.  This is made possible by defining a base
	class for what a control is.
14. The integrator has a variety of tunable parameters.

// RESULTS
15. Storage capacity for a simulation grows as needed.
16. The controls, states, and pseudostates resulting from
    a simulation can be printed to file.
17. Results of the analyses can be printed at a specified uniform
    time spacing if desired, or at every time step that the
	results were recorded.

*/


using namespace std;


//______________________________________________________________________________
/**
 * Run a simulation with a falling block acted on by contact elements
 * and actuators.
 */
int main(int argc,char **argv)
{
	// SET OUTPUT PRECISION
	rdIO::SetPrecision(8);
	rdIO::SetDigitsPad(-1);


	//=======================
	// TYPE REGISTRATION
	//=======================
	// CONTROLS
	rdObject::RegisterType(rdControlConstant());
	rdObject::RegisterType(rdControlLinear());
	rdObject::RegisterType(rdControlLinearNode());
	// ACTUATORS
	rdObject::RegisterType(rdForce());
	rdObject::RegisterType(rdGeneralizedForce());
	rdObject::RegisterType(rdGeneralizedForceAtv());
	// CONTACT FORCES
	rdObject::RegisterType(rdLinearSetPoint());
	rdObject::RegisterType(rdPolynomialSetPoint());

	// WRITE DEFAULT FILES
	// These default files are simply a way of listing the available actutor,
	// contact, and control types and their available properties.
	// Writing out these files is not necessary for executing a simulation.
	rdControlSet defaultControls;  defaultControls.print("Data/default.ctr");
	rdActuatorSet defaultActuators;  defaultActuators.print("Data/default.act");
	rdContactForceSet defaultContacts;  defaultContacts.print("Data/default.ctx");


	//=======================
	// INPUT FILES
	//=======================
	rdActuatorSet actuatorSet("fallingBlock.act");
	rdControlSet controlSet("fallingBlock.ctr");
	rdContactForceSet contactSet("fallingBlock.ctx");

	
	//=======================
	// MODEL
	//=======================
	// CONSTRUCT THE MODEL
	rdBlock model(&actuatorSet,&contactSet);

	// PRINT SOME MODEL INFORMATION
	int i;
	int nb = model.getNB();
	int nx = model.getNX();
	int ny = model.getNY();
	int nyp = model.getNYP();
	cout<<"\n\nModel "<<model.getName()<<" has "<<nx<<" controls, ";
	cout<<ny<<" states, and "<<nyp<<" pseudo-states.\n";
	cout<<"\nThe control set has "<<controlSet.getSize(false)<<" controls in ";
	cout<<"total and "<<controlSet.getSize(true)<<" model controls.\n";
	cout<<"\nBodies:"<<endl;
	for(i=0;i<nb;i++) {
		cout<<model.getBodyName(i)<<" ("<<model.getMass(i)<<"kg)"<<endl;
	}

	// SET SOME INITIAL CONDITIONS
	rdArray<double> yi(0.0,ny);
	model.getInitialStates(&yi[0]);
	yi[1] = 0.25;	// Y Position
	yi[7] = 1.0;	// X Velocity
	yi[9] = 0.0;	// Z Velocity
	model.setInitialStates(&yi[0]);

	// GRAVITY
	double g[] = { 0.0, -2.0, 0.0 };
	model.setGravity(g);


	//=======================
	// ANALYSES
	//=======================
	int stepInterval = 4;
	// Kinematics
	suKinematics *kin = new suKinematics(&model);
	kin->setStepInterval(stepInterval);
	model.addAnalysis(kin);
	// Actuation
	suActuation *actuation = new suActuation(&model);
	actuation->setStepInterval(stepInterval);
	model.addAnalysis(actuation);
	// Contact
	suContact *contact = new suContact(&model);
	contact->setStepInterval(stepInterval);
	model.addAnalysis(contact);


	//=======================
	// SIMULATION
	//=======================
	// INTEGRAND AND MANAGER
	rdModelIntegrand *integrand = new rdModelIntegrand(&model);
	integrand->setControlSet(controlSet);
	rdManager manager(integrand);

	// INITIAL AND FINAL TIMES
	rdControl *control;
	double ti=0.0,tf=0.25;
	control = controlSet.get("ti");
	if(control!=NULL) ti = control->getControlValue();
	control = controlSet.get("tf");
	if(control!=NULL) tf = control->getControlValue();
	manager.setInitialTime(ti);
	manager.setFinalTime(tf);

	// INTEGRATOR SETTINGS
	int maxSteps = 20000;
	rdIntegRKF *integ = manager.getIntegrator();
	integ->setMaximumNumberOfSteps(maxSteps);
	integ->setMaxDT(1.0e-2);
	integ->setTolerance(1.0e-7);
	integ->setFineTolerance(5.0e-9);

	// INTEGRATE
	cout<<"\n\nIntegrating from "<<ti<<" to "<<tf<<endl;
	manager.integrate();


	//=======================
	// RESULTS
	//=======================
	// GET STORAGE
	rdStorage *yStore = integrand->getStateStorage();
	rdStorage *ypStore = integrand->getPseudoStateStorage();
	rdStorage *xStore = integrand->getControlStorage();

	// PRINT
	double dt = 0.005;
	// Print results at a uniform time step.
	xStore->print("Data/controls.sto",dt);
	yStore->print("Data/states.sto",dt);
	ypStore->print("Data/pseudo_states.sto",dt);
	kin->printResults("fallingBlock","Data");
	// Print every time step that was recorded.
	actuation->printResults("fallingBlock","Data");
	contact->printResults("fallingBlock","Data");


	//=======================
	// CLEANUP
	//=======================
	delete yStore;
	delete ypStore;
	delete xStore;

	cout<<endl<<endl;
	return(0);
}
