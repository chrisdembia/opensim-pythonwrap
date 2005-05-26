//  rdTestBlock.cpp

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
#include <RD/Simulation/TestSuite/rdModelTestSuite.h>
#include <RD/Simulation/Control/rdControlLinear.h>
#include <RD/Simulation/Manager/rdManager.h>
#include <RD/Models/Block/rdBlock.h>
#include <SU/Analyses/suAnalyses.h>

void TestContacts();

//______________________________________________________________________________
/**
 * Run some tests on model rdBlock and run a forward simulation.
 */
int main(int argc,char **argv)
{
	// SET GENERAL OUTPUT PRECISION
	rdIO::SetPrecision(8);
	rdIO::SetDigitsPad(-1);

	// CREAT DEFAULT ACTUATORS FILE
	rdActuatorSet defaultActuators;
	defaultActuators.print("default.act");
	printf("generated default.act\n");

	// CREAT DEFAULT CONTACTS FILE
	rdContactForceSet defaultContacts;
	defaultContacts.print("default.ctx");
	printf("generated default.ctx\n");

	// LOAD IN AN ACTUATOR SET
	rdActuatorSet *actuatorSet = new rdActuatorSet("set1.act");
	actuatorSet->generateNode(NULL);
	actuatorSet->print("set1_regen.act");

	// LOAD IN A CONTACT SET
	rdContactForceSet *contactSet = new rdContactForceSet("set1.ctx");
	printf("loaded set1.ctx\n");
	contactSet->generateNode(NULL);
	contactSet->print("set1_regen.ctx");
	printf("regenerated set1.ctx\n");

	// CONSTRUCT THE MODEL
	//rdBlock *model = new rdBlock(actuatorSet,contactSet);
	rdBlock *model = new rdBlock(actuatorSet,contactSet);
	printf("constructed model\n");

	//delete actuatorSet;
	//delete contactSet;
	//delete model;

	// MASS INFORMATION
	double mass = model->getMass(0);
	printf("mass = %lf\n",mass);

	// SET SOME INITIAL CONDITIONS
	double *yi = new double[model->getNY()];
	model->getInitialStates(yi);
	yi[1] = 0.25;	// Y Position
	yi[7] = 1.0;	// X Velocity
	yi[9] = 0.0;	// Z Velocity
	model->setInitialStates(yi);


	// SET UP CONTROLS
	int nx = model->getNX();
	int ny = model->getNY();
	printf("model has %d controls and %d states.\n",nx,ny);

	// RUN TESTS
	//rdModelTestSuite suite;
	//suite.Test(model);
	// TestContacts();

	//__________________________________
	// ----- SIMULATION BELOW HERE -----
	// Jim, the following is not meant to be a part of rdModelTestSuite.
	// I just left it in so that you might see how a forward simulation
	// is done.  When you run this executable, a bunch of simulation results
	// should be printed out that you can load into Excel.  Currently,
	// the results are printed out in a directory called "Data" in your
	// current working directory (i.e., wherever you run this executable).

	// PARSE COMMAND LINE
	double ti=0.0;
	double tf;
	if(argc==1) {
		tf = 12.0;
		//tf = 1.0;
	} else if(argc==2) {
		sscanf(argv[1],"%lf",&tf);
	}

	// PARAMETERS
	int maxSteps = 2000000;
	int storeInterval = 1;

	// ANALYSES
	// Kinematics
	suKinematics *kin = new suKinematics(model);
	kin->setStorageInterval(storeInterval);
	model->addAnalysis(kin);
	kin->setOn(true);
	// Body Kinematics
	suBodyKinematics *bodKin = new suBodyKinematics(model);
	bodKin->setStorageInterval(storeInterval);
	model->addAnalysis(bodKin);
	bodKin->setOn(false);
	// Contact
	suContact *contact = new suContact(model);
	contact->setStorageInterval(storeInterval);
	model->addAnalysis(contact);
	contact->setOn(true);
	// Taylor Decomposition
	//suDecompTaylor *taylor = new suDecompTaylor(model);
	//contact->setStorageInterval(1);
	//model->addAnalysis(taylor);
	//taylor->setOn(false);


	// SIMULATION MANAGER
	rdManager *manager =
		new rdManager(model);
	manager->setSessionName("PassiveBlockImpact");
	manager->setInitialTime(ti);
	manager->setFinalTime(tf);

	// GENERATE SOME CONTROLS
	// m1
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

	// SET NEW CONTROLS
	rdControls *controls = manager->getControls();
	controls->setControl(0,m1);
	controls->setControl(1,m2);

	// INTEGRATOR SETTINGS
	rdIntegRKF *integ = manager->getIntegrator();
	integ->setMaximumNumberOfSteps(maxSteps);
	integ->setMaxDT(1.0e-3);
	integ->setTolerance(1.0e-7);
	integ->setFineTolerance(5.0e-9);

	// STORAGE SETTINGS
	rdStorage *yStore = integ->getStateStorage();
	rdStorage *ypStore = integ->getPseudoStateStorage();
	rdStorage *xStore = integ->getControlStorage();
	yStore->setStepInterval(storeInterval);
	xStore->setStepInterval(storeInterval);

	// GRAVITY
	double g[] = { 0.0, -2.0, 0.0 };
	model->setGravity(g);

	// INTEGRATE
	manager->integrate();

	// PRINT RESULTS
	double dt = 0.005;
	xStore->print("Data/controls.sto",dt);
	yStore->print("Data/states.sto",dt);
	ypStore->print("Data/pseudo_states.sto",dt);
	kin->printResults("p3d","Data",dt);
	bodKin->printResults("p3d","Data",dt);
	contact->printResults("p3d","Data",dt);
	//taylor->printResults("p3d","Data",dt);

	// CLEANUP
	delete manager;
	delete model;
	delete kin;
	delete bodKin;
	delete contact;
	delete yStore;
	delete ypStore;
	delete xStore;
	delete actuatorSet;
	delete contactSet;

	return(0);
}


//______________________________________________________________________________
/**
 * Run some tests on contact classes.
 */
void TestContacts()
{
	// CREATE A DEFAULT SET AND WRITE TO FILE
	rdContactForceSet *contactSet = new rdContactForceSet();
	contactSet->print("default.ctx");

	// CONSTRUCT CONTACTS FROM FILE
	rdContactForceSet contactSet1("set1.ctx");
	contactSet1.print("set2.ctx");
	contactSet1.generateNode(NULL);
	contactSet1.print("set2_regenerated.ctx");

	delete contactSet;
}
