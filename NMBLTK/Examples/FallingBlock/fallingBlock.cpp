// fallingBlock.cpp
// author:  Frank C. Anderson

//==============================================================================
//==============================================================================
#include <stdlib.h>
#include <stdio.h>
#include <RD/Tools/rdIO.h>
#include <RD/Simulation/Model/rdModel.h>
#include <RD/Simulation/Model/rdActuator.h>
#include <RD/Simulation/Model/rdActuatorSet.h>
#include <RD/Simulation/Model/rdContactForce.h>
#include <RD/Simulation/Model/rdContactForceSet.h>
#include <RD/Simulation/Model/rdForce.h>
#include <RD/Simulation/Model/rdGeneralizedForce.h>
#include <RD/Actuators/rdGeneralizedForceAtv.h>
#include <RD/Actuators/rdLinearSetPoint.h>
#include <RD/Actuators/rdPolynomialSetPoint.h>
#include <RD/Simulation/Control/rdControlLinear.h>
#include <RD/Simulation/Manager/rdManager.h>
#include <RD/Models/Block/rdBlock.h>
#include <SU/Analyses/suAnalyses.h>
#include <SU/Analyses/suActuation.h>
#include <SU/Analyses/suContact.h>
#include <SU/Analyses/suKinematics.h>


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


//______________________________________________________________________________
/**
 * Run a simulation with a falling block acted on by contact elements
 * and actuators.
 */
int main(int argc,char **argv)
{
	// SET OUTPUT PRECISION
	rdIO::SetPrecision(16);
	rdIO::SetDigitsPad(-1);


	//=======================
	// ACTUATION AND CONTACT
	//=======================
	// REGISTER ACTUATOR AND CONTACT TYPES
	// Actuators
	rdForce frc;
	rdGeneralizedForce genFrc;
	rdGeneralizedForceAtv genFrcAtv;
	rdActuatorSet::RegisterType(frc);
	rdActuatorSet::RegisterType(genFrc);
	rdActuatorSet::RegisterType(genFrcAtv);
	// Contacts
	rdLinearSetPoint linearCtx;
	rdPolynomialSetPoint polyCtx;
	rdContactForceSet::RegisterType(linearCtx);
	rdContactForceSet::RegisterType(polyCtx);

	// WRITE DEFAULT ACTUATORS AND CONTACTS TO FILE
	// These default files are simply a way of listing the available actutor
	// and contact types and their available properties.
	// Writing out these files is not necessary for executing a simulation.
	rdActuatorSet defaultActuators;
	defaultActuators.print("default.act");
	rdContactForceSet defaultContacts;
	defaultContacts.print("default.ctx");

	// LOAD ACTUATOR SET AND CONTACT SET
	rdActuatorSet *actuatorSet = new rdActuatorSet("fallingBlock.act");
	rdContactForceSet *contactSet = new rdContactForceSet("fallingBlock.ctx");


	//=======================
	// MODEL
	//=======================
	// CONSTRUCT THE MODEL
	rdBlock *model = new rdBlock(actuatorSet,contactSet);

	// PRINT SOME MODEL INFORMATION
	double mass = model->getMass(0);
	int nx = model->getNX();
	int ny = model->getNY();
	int nyp = model->getNYP();
	printf("mass = %lf\n",mass);
	printf("model has %d controls, %d states, and %d pseudo-states.\n",
		nx,ny,nyp);

	// SET SOME INITIAL CONDITIONS
	double *yi = new double[model->getNY()];
	model->getInitialStates(yi);
	yi[1] = 0.25;	// Y Position
	yi[7] = 1.0;	// X Velocity
	yi[9] = 0.0;	// Z Velocity
	model->setInitialStates(yi);

	// GRAVITY
	double g[] = { 0.0, -2.0, 0.0 };
	model->setGravity(g);


	//=======================
	// ANALYSES
	//=======================
	// Kinematics
	suKinematics *kin = new suKinematics(model);
	model->addAnalysis(kin);
	// Actuation
	suActuation *actuation = new suActuation(model);
	model->addAnalysis(actuation);
	actuation->setOn(false);
	// Contact
	suContact *contact = new suContact(model);
	model->addAnalysis(contact);


	//=======================
	// SIMULATION
	//=======================
	// SIMULATION MANAGER
	double ti = 0.0;
	double tf = 10.0;
	rdManager *manager = new rdManager(model);
	manager->setSessionName("FallingBlock");
	manager->setInitialTime(ti);
	manager->setFinalTime(tf);

	// GENERATE SOME CONTROLS
	const int nn = 5;
	double tn[nn],xn[nn];
	// muscle 1
	tn[0] = 0.0;	xn[0] = 0.0;
	tn[1] = 5.0;	xn[1] = 0.0;
	tn[2] = 6.0;	xn[2] = 200.0;
	tn[3] = 7.0;	xn[3] = 0.0;
	tn[4] = tf;		xn[4] = 0.0;
	rdControlLinear *m1 = new rdControlLinear(nn,tn,xn);
	// muscle 2
	tn[0] = 0.0;	xn[0] = 0.0;
	tn[1] = 6.5;	xn[1] = 0.0;
	tn[2] = 6.51;	xn[2] = 50.0;
	tn[3] = 6.0;	xn[3] = 50.0;
	tn[4] = tf;		xn[4] = 50.0;
	rdControlLinear *m2 = new rdControlLinear(nn,tn,xn);
	// set new controls
	rdControls *controls = manager->getControls();
	controls->setControl(0,m1);
	controls->setControl(1,m2);

	// INTEGRATOR SETTINGS
	int maxSteps = 5000;
	rdIntegRKF *integ = manager->getIntegrator();
	integ->setMaximumNumberOfSteps(maxSteps);
	integ->setMaxDT(1.0e-1);
	integ->setTolerance(5.0e-8);
	integ->setFineTolerance(5.0e-10);

	// GET STORAGE
	rdStorage *yStore = integ->getStateStorage();
	rdStorage *ypStore = integ->getPseudoStateStorage();
	rdStorage *xStore = integ->getControlStorage();

	// INTEGRATE
	// The following three integrations should produce identical
	// results.
	// 1: Integration.
	manager->integrate();
	yStore->print("Data/states1.sto");
	integ->printTimeArray("Data/time1.sto");
	integ->printDTArray("Data/dt1.sto");

	// 2: Repeat integration.
	manager->integrate();
	yStore->print("Data/states2.sto");
	integ->printTimeArray("Data/time2.sto");
	integ->printDTArray("Data/dt2.sto");

	// 3: Repeat integration starting from intermediate time.
	// This integration uses stored integration results.
	manager->integrate(1.8769510300001);
	yStore->print("Data/states3.sto");
	integ->printTimeArray("Data/time3.sto");
	integ->printDTArray("Data/dt3.sto");

	//=======================
	// RESULTS
	//=======================
	// PRINT
	double dt = 0.05;
	// Print results at a uniform time step.
	xStore->print("Data/controls.sto",dt);
	yStore->print("Data/states.sto",dt);
	ypStore->print("Data/pseudo_states.sto",dt);
	kin->printResults("fallingBlock","Data",dt);
	// Print every time step that was recorded.
	actuation->printResults("fallingBlock","Data");
	contact->printResults("fallingBlock","Data");


	//=======================
	// CLEANUP
	//=======================
	delete manager;
	delete model;
	delete kin;
	delete contact;
	delete actuation;
	delete yStore;
	delete ypStore;
	delete xStore;
	delete actuatorSet;
	delete contactSet;

	return(0);
}
