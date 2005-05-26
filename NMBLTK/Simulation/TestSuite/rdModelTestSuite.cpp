// rdModelTestSuite.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2002 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include "rdModelTestSuiteDLL.h"
#include <iostream>
#include <string>
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Simulation/Model/rdActuatorSet.h>
#include <NMBLTK/Simulation/Model/rdContactForceSet.h>
#include "rdModelTestSuite.h"
#include <NMBLTK/Simulation/Model/rdContactForceSet.h>


using namespace std;


//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
rdModelTestSuite::
rdModelTestSuite()
{

}


//=============================================================================
// TEST
//=============================================================================
//__________________________________________________________________________
/**
 * Run all tests on a model.
 *
 * @param aModel Model on which to test the methods.
 * @return False if the test fails in some manner, true otherwise.
 */
bool rdModelTestSuite::
Test(rdModel *aModel)
{
	if(aModel==NULL) {
		printf("rdModelTestSuite.Test: ERROR- NULL model pointer.\n");
		return(false);
	}


	if ( (_outFPT=fopen("modelTestSuite.txt","w")) == NULL )
	{
		printf("rdModelTestSuite.Test: ERROR- Cannot open output file.\n");
		return(false);
	}


	fprintf(_outFPT,"-------------------------- "
		"rdModelTestSuite Results ---------------------------\n\n");

	// TESTS
	bool status;
	status = TestNumbers(aModel);
	status = TestNames(aModel);
	status = TestStates(aModel);
	status = TestPseudoStates(aModel);
	status = TestGravity(aModel);
	status = TestBodies(aModel);
	status = TestKinematics(aModel);
	status = TestLoads(aModel);
	status = TestDerivatives(aModel);
	status = TestMassMatrix(aModel);
	status = TestJacobian(aModel);
	status = TestOrientationUtilities(aModel);

	status = TestContacts(aModel);
	//status = TestActuation(aModel);


	fprintf(_outFPT,"\n\n----------------------- "
		"End of rdModelTestSuite Results -----------------------");

	fclose(_outFPT);

	return(true);
}


//=============================================================================
// NUMBERS
//=============================================================================
//__________________________________________________________________________
/**
 * Test the various numbers of things in a model.
 *		rdModel::getNX()
 *		rdModel::getNQ()
 *		rdModel::getNU()
 *		rdModel::getNY()
 *		rdModel::getNB()
 *		rdModel::getNJ()
 *		rdModel::getNA()
 *		rdModel::getNP()
 *
 * @param aModel Model on which to test the methods.
 * @return False if the test fails in some manner, true otherwise.
 */
bool rdModelTestSuite::
TestNumbers(rdModel *aModel)
{
	if(aModel==NULL) {
		fprintf(_outFPT,
			"rdModelTestSuite.TestNumbers: FAILED- NULL model pointer.\n");
		return(false);
	}

	// PRINT NUMBERS
	fprintf(_outFPT,"\n========================================"
		"=======================================\n"
		"rdModelTestSuite.TestNumbers:\n");

	fprintf(_outFPT,"Controls    = %d\n",aModel->getNX());
	fprintf(_outFPT,"Coordinates = %d\n",aModel->getNQ());
	fprintf(_outFPT,"Speeds      = %d\n",aModel->getNU());
	fprintf(_outFPT,"States      = %d\n",aModel->getNY());
	fprintf(_outFPT,"Bodies      = %d\n",aModel->getNB());
	fprintf(_outFPT,"Joints      = %d\n",aModel->getNJ());
	fprintf(_outFPT,"Actuators   = %d\n",aModel->getNA());
	fprintf(_outFPT,"Points      = %d\n",aModel->getNP());

	fprintf(_outFPT,"\nrdModelTestSuite.TestNumbers: PASSED.\n"
		"========================================"
		"=======================================\n\n");
	return(true);
}


//=============================================================================
// NAMES
//=============================================================================
//__________________________________________________________________________
/**
 * Test the names of things in a model.
 *		rdModel::getName()
 *		rdModel::getBodyName()
 *		rdModel::getCoordinateName()
 *		rdModel::getSpeedName()
 *		rdModel::getActuatorName()
 *		rdModel::getControlName()
 *		rdModel::getStateName()
 *
 * @param aModel Model on which to test the methods.
 * @return False if the test fails in some manner, true otherwise.
 */
bool rdModelTestSuite::
TestNames(rdModel *aModel)
{
	if(aModel==NULL) {
		fprintf(_outFPT,
			"rdModelTestSuite.TestNames: FAILED- NULL model pointer.\n");
		return(false);
	}

	fprintf(_outFPT,"\n========================================"
		"=======================================\n"
		"rdModelTestSuite.TestNames:\n");

	fprintf(_outFPT,"\nModel Name = '%s'",aModel->getName().c_str());

	int i;

	fprintf(_outFPT,"\n\n Body          Name\n------------------------------");
	for (i=0;i<aModel->getNB();i++)
		fprintf(_outFPT,"\n%4d           '%s'",i,aModel->getBodyName(i).c_str());
	fprintf(_outFPT,"\n------------------------------\n");


	fprintf(_outFPT,"\n\nCoordinate     Name\n------------------------------");
	for (i=0;i<aModel->getNQ();i++)
		fprintf(_outFPT,"\n%4d           '%s'",i,aModel->getCoordinateName(i).c_str());
	fprintf(_outFPT,"\n------------------------------\n");

	fprintf(_outFPT,"\n\nSpeed          Name\n------------------------------");
	for (i=0;i<aModel->getNU();i++)
		fprintf(_outFPT,"\n%4d           '%s'",i,aModel->getSpeedName(i).c_str());
	fprintf(_outFPT,"\n------------------------------\n");

	fprintf(_outFPT,"\n\nActuator       Name\n------------------------------");
	for (i=0;i<aModel->getNA();i++)
		fprintf(_outFPT,"\n%4d           '%s'",i,aModel->getActuatorName(i).c_str());
	fprintf(_outFPT,"\n------------------------------\n");

	fprintf(_outFPT,"\n\nControl        Name\n------------------------------");
	for (i=0;i<aModel->getNX();i++)
		fprintf(_outFPT,"\n%4d           '%s'",i,aModel->getControlName(i).c_str());
	fprintf(_outFPT,"\n------------------------------\n");

	fprintf(_outFPT,"\n\nState          Name\n------------------------------");
	for (i=0;i<aModel->getNY();i++)
		fprintf(_outFPT,"\n%4d           '%s'",i,aModel->getStateName(i).c_str());
	fprintf(_outFPT,"\n------------------------------\n");

	fprintf(_outFPT,"\nrdModelTestSuite.TestNames: PASSED.\n"
		"========================================"
		"=======================================\n\n");


	return(true);
}


//=============================================================================
// STATES
//=============================================================================
//__________________________________________________________________________
/**
 * Test the methods for setting and getting the states of a model.
 *		rdModel::set()
 *		rdModel::setTime()
 *		rdModel::getTime()
 *		rdModel::setTimeNormConstant()
 *		rdModel::getTimeNormConstant()
 *		rdModel::setControls()
 *		rdModel::getControls()
 *		rdModel::setInitialStates()
 *		rdModel::getInitialStates()
 *		rdModel::setStates()
 *		rdModel::getStates()
 *		rdModel::setConfiguration()
 *		rdModel::getCoordinates()
 *		rdModel::getSpeeds()
 *		rdModel::extractConfiguration()
 *
 * @param aModel Model on which to test the methods.
 * @return False if the test fails in some manner, true otherwise.
 */
bool rdModelTestSuite::
TestStates(rdModel *aModel)
{
	if(aModel==NULL) {
		fprintf(_outFPT,
			"rdModelTestSuite.TestStates: FAILED- NULL model pointer.\n");
		return(false);
	}

	fprintf(_outFPT,"\n========================================"
		"=======================================\n"
		"rdModelTestSuite.TestStates:\n");

	int i;

	// Set states, controls, and time.
	double *yi = new double[aModel->getNY()];

	for (i=0;i<aModel->getNY();i++)
		yi[i] = (double)i;

	double *xi = new double[aModel->getNX()];

	for (i=0;i<aModel->getNX();i++)
		xi[i] = -(double)i;

	double T = 12.3;

	aModel->set(T,xi,yi);



	// Get the values.
	double *rY = new double[aModel->getNY()];
	double *rX = new double[aModel->getNX()];

	// Get the states and the controls.
	aModel->getStates(rY);
	aModel->getControls(rX);

	fprintf(_outFPT,"\nSet Time, States, and Controls -----\n");

	fprintf(_outFPT,"\nTime = %.4lf seconds",aModel->getTime());

	fprintf(_outFPT,"\n\nState      Value      Name\n"
		"-------------------------------------");

	for (i=0;i<aModel->getNY();i++)
		fprintf(_outFPT,"\n%4d   %12.4e  '%s'",
		i,rY[i],aModel->getStateName(i).c_str());

	fprintf(_outFPT,"\n-------------------------------------\n");

	fprintf(_outFPT,"\n\nControl    Value      Name\n"
		"-------------------------------------");

	for (i=0;i<aModel->getNX();i++)
		fprintf(_outFPT,"\n%4d   %12.4e  '%s'",
		i,rX[i],aModel->getControlName(i).c_str());

	fprintf(_outFPT,"\n-------------------------------------\n");


	fprintf(_outFPT,"\nReset Time, States, and Controls -----\n");

	T += 10.0;

	aModel->setTime(T);
	fprintf(_outFPT,"\nTime = %.4lf seconds",aModel->getTime());

	double Tnorm = 5.0;
	aModel->setTimeNormConstant(Tnorm);
	fprintf(_outFPT,"\nTime normalization constant = %.4lf",
		aModel->getTimeNormConstant());


	for (i=0;i<aModel->getNY();i++)
		yi[i] = (double)(i+10);

	aModel->setStates(yi);
	aModel->getStates(rY);

	fprintf(_outFPT,"\n\nState      Value      Name\n"
		"-------------------------------------");

	for (i=0;i<aModel->getNY();i++)
		fprintf(_outFPT,"\n%4d   %12.4e  '%s'",
		i,rY[i],aModel->getStateName(i).c_str());

	fprintf(_outFPT,"\n-------------------------------------\n");


	for (i=0;i<aModel->getNX();i++)
		xi[i] = -(double)(i+10);

	aModel->setControls(xi);
	aModel->getControls(rX);

	fprintf(_outFPT,"\n\nControl    Value      Name\n"
		"-------------------------------------");

	for (i=0;i<aModel->getNX();i++)
		fprintf(_outFPT,"\n%4d   %12.4e  '%s'",
		i,rX[i],aModel->getControlName(i).c_str());

	fprintf(_outFPT,"\n-------------------------------------\n");




	fprintf(_outFPT,"\n\nConfiguration tests -----");

	rdArray<double> rQ(0.0,aModel->getNQ());
	aModel->getCoordinates(&rQ[0]);

	fprintf(_outFPT,"\n\nCoordinate       Value\n"
		                "-------------------------");

	for (i=0;i<aModel->getNQ();i++)
		fprintf(_outFPT,"\n %4d        %12.4e",i,rQ[i]);

	fprintf(_outFPT,"\n-------------------------\n");


	rdArray<double> rU(0.0,aModel->getNU());
	aModel->getSpeeds(&rU[0]);

	fprintf(_outFPT,"\n\nSpeed      Value\n"
		"------------------");

	for (i=0;i<aModel->getNU();i++)
		fprintf(_outFPT,"\n%3d   %12.4e",i,rU[i]);

	fprintf(_outFPT,"\n------------------\n");


	fprintf(_outFPT,"\n\nExtracting configuration:");

	aModel->extractConfiguration(yi,&rQ[0],&rU[0]);

	fprintf(_outFPT,"\n\nCoordinate       Value\n"
		                "-------------------------");

	for (i=0;i<aModel->getNQ();i++)
		fprintf(_outFPT,"\n %4d        %12.4e",i,rQ[i]);

	fprintf(_outFPT,"\n-------------------------\n");

	fprintf(_outFPT,"\n\nSpeed      Value\n"
		"------------------");

	for (i=0;i<aModel->getNU();i++)
		fprintf(_outFPT,"\n%3d   %12.4e",i,rU[i]);

	fprintf(_outFPT,"\n------------------\n");


	fprintf(_outFPT,"\n\nReset states:");

	for (i=0;i<aModel->getNY();i++)
		yi[i] = (double)(i+20);

	aModel->setConfiguration(yi);

	aModel->getCoordinates(&rQ[0]);

	fprintf(_outFPT,"\n\nCoordinate       Value\n"
		                "-------------------------");

	for (i=0;i<aModel->getNQ();i++)
		fprintf(_outFPT,"\n %4d        %12.4e",i,rQ[i]);

	fprintf(_outFPT,"\n-------------------------\n");


	aModel->getSpeeds(&rU[0]);

	fprintf(_outFPT,"\n\nSpeed      Value\n"
		"------------------");

	for (i=0;i<aModel->getNU();i++)
		fprintf(_outFPT,"\n%3d   %12.4e",i,rU[i]);

	fprintf(_outFPT,"\n------------------\n");


	fprintf(_outFPT,"\n\nReset coordinates and speeds:");

	for (i=0;i<aModel->getNQ();i++)
		rQ[i] = rQ[i] + 10.0;

	for (i=0;i<aModel->getNU();i++)
		rU[i] = rU[i] + 20.0;

	aModel->setConfiguration(&rQ[0],&rU[0]);

	aModel->getCoordinates(&rQ[0]);

	fprintf(_outFPT,"\n\nCoordinate       Value\n"
		                "-------------------------");

	for (i=0;i<aModel->getNQ();i++)
		fprintf(_outFPT,"\n %4d        %12.4e",i,rQ[i]);

	fprintf(_outFPT,"\n-------------------------\n");


	aModel->getSpeeds(&rU[0]);

	fprintf(_outFPT,"\n\nSpeed      Value\n"
		"------------------");

	for (i=0;i<aModel->getNU();i++)
		fprintf(_outFPT,"\n%3d   %12.4e",i,rU[i]);

	fprintf(_outFPT,"\n------------------\n");



	fprintf(_outFPT,"\nrdModelTestSuite.TestStates: PASSED.\n"
		"========================================"
		"=======================================\n\n");


	delete yi;
	delete xi;

	delete rY;
	delete rX;


	return(true);
}


//=============================================================================
// PSEUDO-STATES
//=============================================================================
//__________________________________________________________________________
/**
 * Test the methods for setting and getting the pseudo-states of a model.
 *		rdModel::setInitialPseudoStates()
 *		rdModel::getInitialPseudoStates()
 *		rdModel::setPseudoStates()
 *		rdModel::getPseudoStates()
 *
 * @param aModel Model on which to test the methods.
 * @return False if the test fails in some manner, true otherwise.
 */
bool rdModelTestSuite::
TestPseudoStates(rdModel *aModel)
{

	if(aModel==NULL) {
		fprintf(_outFPT,
			"rdModelTestSuite.TestStates: FAILED- NULL model pointer.\n");
		return(false);
	}

	fprintf(_outFPT,"\n========================================"
		"=======================================\n"
		"rdModelTestSuite.TestStates:\n");

	//----------------------
	// INITIAL PSEUDO-STATES
	//----------------------
	// CURRENT
	rdArray<double> ypi(0.0,aModel->getNYP());
	aModel->getInitialPseudoStates(&ypi[0]);
	cout<<"ypi:  "<<ypi<<endl;

	
	//----------------------
	// PSEUDO-STATES
	//----------------------
	// CURRENT
	rdArray<double> yp(0.0,aModel->getNYP());
	aModel->getPseudoStates(&yp[0]);
	cout<<"yp:  "<<yp<<endl;
	aModel->setPseudoStates(&ypi[0]);
	aModel->getPseudoStates(&yp[0]);
	cout<<"yp:  "<<yp<<endl;
	
	
	return(true);
}


//=============================================================================
// GRAVITY
//=============================================================================
//__________________________________________________________________________
/**
 * Test class rdGravity.
 *		rdModel::getGravity()
 *		rdModel::setGravity()
 *
 * @param aModel Model on which to test the methods.
 * @return False if the test fails in some manner, true otherwise.
 */
bool rdModelTestSuite::
TestGravity(rdModel *aModel)
{
	if(aModel==NULL) {
		fprintf(_outFPT,
			"rdModelTestSuite.TestGravity: FAILED- NULL model pointer.\n");
		return(false);
	}

	fprintf(_outFPT,"\n========================================"
		"=======================================\n"
		"rdModelTestSuite.TestGravity:\n");


	// Get the states before we do anything with gravity.
	double *rY = new double[aModel->getNY()];

	aModel->getStates(rY);


	double rGrav[3],aGrav[3],aGravSave[3];

	fprintf(_outFPT,"\nGet gravity -----");

	aModel->getGravity(rGrav);

	aGravSave[0] = rGrav[0];
	aGravSave[1] = rGrav[1];
	aGravSave[2] = rGrav[2];

	fprintf(_outFPT,"\nGravity = %9.4lf  %9.4lf  %9.4lf",
		rGrav[0],rGrav[1],rGrav[2]);

	if (rGrav[0] < 0.0)
		aGrav[0] = rGrav[0] - 10.0;
	else
		aGrav[0] = rGrav[0] + 10.0;

	if (rGrav[1] < 0.0)
		aGrav[1] = rGrav[1] - 10.0;
	else
		aGrav[1] = rGrav[1] + 10.0;

	if (rGrav[2] < 0.0)
		aGrav[2] = rGrav[2] - 10.0;
	else
		aGrav[2] = rGrav[2] + 10.0;

	aModel->setGravity(aGrav);
	aModel->getGravity(rGrav);

	fprintf(_outFPT,"\n\nReset gravity -----");

	fprintf(_outFPT,"\nGravity = %9.4lf  %9.4lf  %9.4lf",
		rGrav[0],rGrav[1],rGrav[2]);

	fprintf(_outFPT,"\n\nReset gravity -----");

	aModel->setGravity(aGravSave);

	aModel->getGravity(rGrav);

	fprintf(_outFPT,"\nGravity = %9.4lf  %9.4lf  %9.4lf",
		rGrav[0],rGrav[1],rGrav[2]);

	// Reset the states.
	aModel->setStates(rY);

	delete rY;

	fprintf(_outFPT,"\n\nrdModelTestSuite.TestGravity: PASSED.\n"
		"========================================"
		"=======================================\n\n");


	return(true);
}


//=============================================================================
// BODIES
//=============================================================================
//__________________________________________________________________________
/**
 * Test class for bodies.
 *		rdModel::getGroundID()
 *		rdModel::getMass()
 *		rdModel::getInertiaBodyLocal()
 *		rdModel::getSystemInertia()
 *
 * @param aModel Model on which to test the methods.
 * @return False if the test fails in some manner, true otherwise.
 */
bool rdModelTestSuite::
TestBodies(rdModel *aModel)
{
	if(aModel==NULL) {
		fprintf(_outFPT,
			"rdModelTestSuite.TestBodies: FAILED- NULL model pointer.\n");
		return(false);
	}

	fprintf(_outFPT,"\n========================================"
		"=======================================\n"
		"rdModelTestSuite.TestBodies:\n");

	fprintf(_outFPT,"\nGround ID = %d",aModel->getGroundID());


	int i;


	fprintf(_outFPT,"\n\n Body      Mass\n"
		"------------------");

	for (i=0;i<aModel->getNB();i++)
		fprintf(_outFPT,"\n%4d  %12.4e",i,aModel->getMass(i));

	fprintf(_outFPT,"\n------------------\n");

	double rI[3][3];

	for (i=0;i<aModel->getNB();i++)
	{

		aModel->getInertiaBodyLocal(i,rI);

		fprintf(_outFPT,"\nInertia Matrix for Body: %d -----",i);

		fprintf(_outFPT,"\n         X              Y              Z"
			"\n---------------------------------------------");
		fprintf(_outFPT,"\nX  %12.4e   %12.4e   %12.4e",
			rI[0][0],rI[0][1],rI[0][2]);
		fprintf(_outFPT,"\nY  %12.4e   %12.4e   %12.4e",
			rI[1][0],rI[1][1],rI[1][2]);
		fprintf(_outFPT,"\nZ  %12.4e   %12.4e   %12.4e",
			rI[2][0],rI[2][1],rI[2][2]);

		fprintf(_outFPT,"\n---------------------------------------------\n");
	}


	double rM,rCOM[3];

	aModel->getSystemInertia(&rM,rCOM,rI);

	fprintf(_outFPT,"\n\nSystem Properties:\n");
	fprintf(_outFPT,"\nMass = %.3lf",rM);
	fprintf(_outFPT,"\n COM = %12.3e  %12.3e  %12.3e",rCOM[0],rCOM[1],rCOM[2]);


	fprintf(_outFPT,"\n\nInertia Tensor -----");

	fprintf(_outFPT,"\n         X              Y              Z"
		"\n---------------------------------------------");
	fprintf(_outFPT,"\nX  %12.4e   %12.4e   %12.4e",
		rI[0][0],rI[0][1],rI[0][2]);
	fprintf(_outFPT,"\nY  %12.4e   %12.4e   %12.4e",
		rI[1][0],rI[1][1],rI[1][2]);
	fprintf(_outFPT,"\nZ  %12.4e   %12.4e   %12.4e",
		rI[2][0],rI[2][1],rI[2][2]);

	fprintf(_outFPT,"\n---------------------------------------------\n");


	fprintf(_outFPT,"\n\nrdModelTestSuite.TestBodies: PASSED.\n"
		"========================================"
		"=======================================\n\n");


	return(true);
}


//=============================================================================
// KINEMATICS
//=============================================================================
//__________________________________________________________________________
/**
 * Test the methods for computing kinematic quantities for a model.
 *		rdModel::getPosition()
 *		rdModel::getVelocity()
 *		rdModel::getAcceleration()
 *		rdModel::getDirectionCosines()
 *		rdModel::getAngularVelocity()
 *		rdModel::getAngularVelocityBodyLocal()
 *		rdModel::getAngularAcceleration()
 *		rdModel::getAngularAccelerationBodyLocal()
 *
 * @param aModel Model on which to test the methods.
 * @return False if the test fails in some manner, true otherwise.
 */
bool rdModelTestSuite::
TestKinematics(rdModel *aModel)
{
	if(aModel==NULL) {
		fprintf(_outFPT,
			"rdModelTestSuite.TestKinematics: FAILED- NULL model pointer.\n");
		return(false);
	}

	fprintf(_outFPT,"\n========================================"
		"=======================================\n"
		"rdModelTestSuite.TestKinematics:\n");

	int i;
	double aPoint[] = { 0.0, 0.0, 0.0 };

	fprintf(_outFPT,"\n\n Body                 Position"
					"                               Velocity\n"
"---------------------------------------------------------"
"----------------------");

	// CONFIGURATION
	rdArray<double> q(0.0);  q.setSize(aModel->getNQ());
	rdArray<double> u(0.0);  u.setSize(aModel->getNU());
	aModel->setConfiguration(&q[0],&u[0]);

	for (i=0;i<aModel->getNB();i++)
	{
		double rPos[3],rVel[3];
		aModel->getPosition(i,aPoint,rPos);
		aModel->getVelocity(i,aPoint,rVel);

		fprintf(_outFPT,"\n%4d   %11.3e %11.3e %11.3e %11.3e %11.3e %11.3e",
			i,rPos[0],rPos[1],rPos[2],rVel[0],rVel[1],rVel[2]);
	}
	fprintf(_outFPT,"\n-----------------------------------------------------"
		"--------------------------\n");


	fprintf(_outFPT,"\n\n Body               Acceleration\n"
		"---------------------------------------------");


	int nq = aModel->getNQ();
	int nu = aModel->getNU();

	double *dqdt = new double[nq];
	double *dudt = new double[nu];

	aModel->computeAccelerations(dqdt,dudt);

	delete dqdt;
	delete dudt;

	for (i=0;i<aModel->getNB();i++)
	{
		double rAcc[3];
		aModel->getAcceleration(i,aPoint,rAcc);

		fprintf(_outFPT,"\n%4d   %12.4e %12.4e %12.4e",
			i,rAcc[0],rAcc[1],rAcc[2]);
	}
	fprintf(_outFPT,"\n---------------------------------------------\n");


	fprintf(_outFPT,"\n\n Body       Direction Cosines (Array)\n"
		"--------------------------------------");

	for (i=0;i<aModel->getNB();i++)
	{
		double rDirCosArray[3][3];
		aModel->getDirectionCosines(i,rDirCosArray);

		fprintf(_outFPT,"\n%4d   %9.6lf  %9.6lf  %9.6lf",
			i,rDirCosArray[0][0],rDirCosArray[0][1],rDirCosArray[0][2]);
		fprintf(_outFPT,"\n       %9.6lf  %9.6lf  %9.6lf",
			rDirCosArray[1][0],rDirCosArray[1][1],rDirCosArray[1][2]);
		fprintf(_outFPT,"\n       %9.6lf  %9.6lf  %9.6lf",
			rDirCosArray[2][0],rDirCosArray[2][1],rDirCosArray[2][2]);

		if (i < (aModel->getNB()-1) ) fprintf(_outFPT,"\n");
	}
	fprintf(_outFPT,"\n--------------------------------------\n");


	fprintf(_outFPT,"\n\n Body       Direction Cosines (Vector)\n"
		"--------------------------------------");

	double *rDirCosVector;
	rDirCosVector = new double[9];

	for (i=0;i<aModel->getNB();i++)
	{
		aModel->getDirectionCosines(i,rDirCosVector);

		fprintf(_outFPT,"\n%4d   %9.6lf  %9.6lf  %9.6lf",
			i,rDirCosVector[0],rDirCosVector[1],rDirCosVector[2]);
		fprintf(_outFPT,"\n       %9.6lf  %9.6lf  %9.6lf",
			rDirCosVector[3],rDirCosVector[4],rDirCosVector[5]);
		fprintf(_outFPT,"\n       %9.6lf  %9.6lf  %9.6lf",
			rDirCosVector[6],rDirCosVector[7],rDirCosVector[8]);

		if (i < (aModel->getNB()-1) ) fprintf(_outFPT,"\n");
	}
	fprintf(_outFPT,"\n--------------------------------------\n");

	delete rDirCosVector;


	fprintf(_outFPT,"\n\n Body            Angular Velocity (Global)        "
		"Resultant\n"
		"-------------------------------------------------------------");

	for (i=0;i<aModel->getNB();i++)
	{
		double rAngVel[3],totalAngVel;
		aModel->getAngularVelocity(i,rAngVel);

		totalAngVel = sqrt(rAngVel[0]*rAngVel[0]+rAngVel[1]*rAngVel[2]+
			rAngVel[2]*rAngVel[2]);

		fprintf(_outFPT,"\n%4d   %12.4e %12.4e %12.4e   %12.4e",
			i,rAngVel[0],rAngVel[1],rAngVel[2],totalAngVel);
	}
	fprintf(_outFPT,"\n------------------------------"
		"-------------------------------\n");


	fprintf(_outFPT,"\n\n Body            Angular Velocity (Local)         "
		"Resultant\n"
		"-------------------------------------------------------------");

	for (i=0;i<aModel->getNB();i++)
	{
		double rAngVel[3],totalAngVel;
		aModel->getAngularVelocityBodyLocal(i,rAngVel);

		totalAngVel = sqrt(rAngVel[0]*rAngVel[0]+rAngVel[1]*rAngVel[2]+
			rAngVel[2]*rAngVel[2]);

		fprintf(_outFPT,"\n%4d   %12.4e %12.4e %12.4e   %12.4e",
			i,rAngVel[0],rAngVel[1],rAngVel[2],totalAngVel);
	}
	fprintf(_outFPT,"\n------------------------------"
		"-------------------------------\n");


	fprintf(_outFPT,"\n\n Body        Angular Acceleration (Global)        "
		"Resultant\n"
		"------------------------------------------------------------");

	for (i=0;i<aModel->getNB();i++)
	{
		double rAngAcc[3],totalAngAcc;
		aModel->getAngularAcceleration(i,rAngAcc);

		totalAngAcc = sqrt(rAngAcc[0]*rAngAcc[0]+rAngAcc[1]*rAngAcc[2]+
			rAngAcc[2]*rAngAcc[2]);

		fprintf(_outFPT,"\n%4d   %12.4e %12.4e %12.4e   %12.4e",
			i,rAngAcc[0],rAngAcc[1],rAngAcc[2],totalAngAcc);
	}
	fprintf(_outFPT,"\n------------------------------"
		"------------------------------\n");


	fprintf(_outFPT,"\n\n Body        Angular Acceleration (Local)         "
		"Resultant\n"
		"------------------------------------------------------------");

	for (i=0;i<aModel->getNB();i++)
	{
		double rAngAcc[3],totalAngAcc;
		aModel->getAngularAccelerationBodyLocal(i,rAngAcc);

		totalAngAcc = sqrt(rAngAcc[0]*rAngAcc[0]+rAngAcc[1]*rAngAcc[2]+
			rAngAcc[2]*rAngAcc[2]);

		fprintf(_outFPT,"\n%4d   %12.4e %12.4e %12.4e   %12.4e",
			i,rAngAcc[0],rAngAcc[1],rAngAcc[2],totalAngAcc);
	}
	fprintf(_outFPT,"\n------------------------------"
		"------------------------------\n");



	fprintf(_outFPT,"\nrdModelTestSuite.TestKinematics: PASSED.\n"
		"========================================"
		"=======================================\n\n");

	return(true);
}



//=============================================================================
// LOADS
//=============================================================================
//__________________________________________________________________________
/**
 * Test class Loads.
 *		rdModel::applyForce()
 *		rdModel::getNetAppliedGeneralizedForce()
 *
 * @param aModel Model on which to test the methods.
 * @return False if the test fails in some manner, true otherwise.
 */
bool rdModelTestSuite::
TestLoads(rdModel *aModel)
{
	if(aModel==NULL) {
		fprintf(_outFPT,
			"rdModelTestSuite.TestLoads: FAILED- NULL model pointer.\n");
		return(false);
	}

	fprintf(_outFPT,"\n========================================"
		"=======================================\n"
		"rdModelTestSuite.TestLoads:\n");

	int i,j;
	int nb = aModel->getNB();
	int nu = aModel->getNU();

	double rF;
	double aPoint[] = { 1.0, 0.0, 0.0 };
	double aForce[] = { 0.0, 1.0, 0.0 };

	for (i=0;i<nb;i++)
	{
		fprintf(_outFPT,"\n\nBody: %d -----",i);

		aModel->applyForce(i,aPoint,aForce);

		fprintf(_outFPT,"\n\nGeneralized Speed   Force/Torque\n"
			"--------------------------------");

		for (j=0;j<nu;j++)
		{
			rF = aModel->getNetAppliedGeneralizedForce(j);
			fprintf(_outFPT,"\n    %3d             %12.4e",j,rF);
		}
		fprintf(_outFPT,"\n--------------------------------\n");


	}



	fprintf(_outFPT,"\n\nrdModelTestSuite.TestLoads: PASSED.\n"
		"========================================"
		"=======================================\n\n");

	return(true);
}


//=============================================================================
// DERIVATIVES
//=============================================================================
//__________________________________________________________________________
/**
 * Test class Derivatives.
 *		rdModel::computeAccelerations()
 *		rdModel::deriv()
 *
 * @param aModel Model on which to test the methods.
 * @return False if the test fails in some manner, true otherwise.
 */
bool rdModelTestSuite::
TestDerivatives(rdModel *aModel)
{
	if(aModel==NULL) {
		fprintf(_outFPT,
			"rdModelTestSuite.TestDerivatives: FAILED- NULL model pointer.\n");
		return(false);
	}

	fprintf(_outFPT,"\n========================================"
		"=======================================\n"
		"rdModelTestSuite.TestDerivatives:\n");

	// ALLOCATIONS
	int nq = aModel->getNQ();
	int nu = aModel->getNU();
	double *dqdt = new double[nq];
	double *dudt = new double[nu];


	// SET STATES
	rdArray<double> yi(0.0,aModel->getNY());
	aModel->getInitialStates(&yi[0]);
	cout<<yi<<endl;
	aModel->setStates(&yi[0]);

	// COMPUTE ACCELERATIONS
	aModel->computeAccelerations(dqdt,dudt);


	int i;

	fprintf(_outFPT,"\n\nGeneralized Coordinate    dqdt\n"
		"-------------------------------------");

	for (i=0;i<aModel->getNQ();i++)
		fprintf(_outFPT,"\n     %4d             %12.4e",i,dqdt[i]);

	fprintf(_outFPT,"\n-------------------------------------\n");

	fprintf(_outFPT,"\n\nGeneralized Speed    dudt\n"
		"-------------------------------------");

	for (i=0;i<aModel->getNU();i++)
		fprintf(_outFPT,"\n   %4d          %12.4e",i,dudt[i]);

	fprintf(_outFPT,"\n-------------------------------------\n");


	// TIME
	double t = aModel->getTime();

	// CONTROLS
	rdArray<double> x(0.02);  x.setSize(aModel->getNX());
	aModel->getControls(&x[0]);


	// DERIVATIVES
	aModel->deriv(t,&x[0],&yi[0],dqdt,dudt);

	fprintf(_outFPT,"\n\nGeneralized Coordinate    dqdt\n"
		"-------------------------------------");

	for (i=0;i<aModel->getNQ();i++)
		fprintf(_outFPT,"\n     %4d             %12.4e",i,dqdt[i]);

	fprintf(_outFPT,"\n-------------------------------------\n");

	fprintf(_outFPT,"\n\nGeneralized Speed    dudt\n"
		"-------------------------------------");

	for (i=0;i<aModel->getNU();i++)
		fprintf(_outFPT,"\n   %4d          %12.4e",i,dudt[i]);

	fprintf(_outFPT,"\n-------------------------------------\n");



	delete dqdt;
	delete dudt;


	fprintf(_outFPT,"\n\nrdModelTestSuite.TestDerivatives: PASSED.\n"
		"========================================"
		"=======================================\n\n");

	return(true);
}


//=============================================================================
// MASS MATRIX
//=============================================================================
//__________________________________________________________________________
/**
 * Test class rdMassMatrix.
 *		rdModel::formMassMatrix()
 *
 * @param aModel Model on which to test the methods.
 * @return False if the test fails in some manner, true otherwise.
 */
bool rdModelTestSuite::
TestMassMatrix(rdModel *aModel)
{
	if(aModel==NULL) {
		fprintf(_outFPT,
			"rdModelTestSuite.TestMassMatrix: FAILED- NULL model pointer.\n");
		return(false);
	}

	fprintf(_outFPT,"\n========================================"
		"=======================================\n"
		"rdModelTestSuite.TestMassMatrix:\n");

	double *rI;

	int nu = aModel->getNU();

	rI = new double[nu*nu];

	aModel->formMassMatrix(rI);

	for (int i=0;i<nu;i++)
	{
		fprintf(_outFPT,"\n");

		for (int j=0;j<nu;j++)
			fprintf(_outFPT,"%12.4e   ",rI[i*nu + j]);
	}

	delete rI;

	fprintf(_outFPT,"\n\nrdModelTestSuite.TestMassMatrix: PASSED.\n"
		"========================================"
		"=======================================\n\n");

	return(true);
}



//=============================================================================
// JOCOBIAN
//=============================================================================
//__________________________________________________________________________
/**
 * Test the Jocobian methods.
 *
 * @param aModel Model on which to test the methods.
 * @return False if the test fails in some manner, true otherwise.
 */
bool rdModelTestSuite::
TestJacobian(rdModel *aModel)
{
/*
	if(aModel==NULL) {
		fprintf(_outFPT,
			"rdModelTestSuite.TestJacobian: FAILED- NULL model pointer.\n");
		return(false);
	}

	fprintf(_outFPT,"\n========================================"
		"=======================================\n"
		"rdModelTestSuite.TestJacobian:\n");

	int i,j,body;

	// GET NUMBERS
	int nq = aModel->getNQ();
	int nu = aModel->getNU();

	// CONSTRUCT Q's and U's
	double *q = new double[nq];
	double *u = new double[nu];

	// SET VALUES FOR THE Q'S AND U'S
	for(i=0;i<nq;i++) q[i] = 0.0;
	for(i=0;i<nu;i++) u[i] = 0.0;
	//q[3] = rdMath::DTR*90.0;   
	//q[4] = rdMath::DTR*20.0;
	//q[5] = rdMath::DTR*20.0;

	// CONVERT TO QUATERNIONS
	aModel->convertAnglesToQuaternions(q,q);

	// SET THE CONFIGURATION
	aModel->setConfiguration(q,u);

	// DEFINE SOME PARAMETERS
	double point1[] = { 1.0, 1.0, 1.0 };
	double point2[] = { 1.0, 1.0, -1.0 };

	// TEST JACOBIAN METHODS
	double *I = new double[nu*nu];
	double *J = new double[6*nu];
	double *J_1 = new double[nu*6];

	aModel->formMassMatrix(I);
	fprintf(_outFPT,"\nMass Matrix:");
	for (i=0;i<nu;i++)
	{
		fprintf(_outFPT,"\n");

		for (j=0;j<nu;j++)
			fprintf(_outFPT,"%12.5lf   ",I[i*nu + j]);
	}


	for (body=0;body<aModel->getNB();body++)
	{
		fprintf(_outFPT,"\n\nBody: %d ====================\n",body);

		aModel->formJacobian(body,point1,J);
		fprintf(_outFPT,"\nJacobian at point (%.3lf, %.3lf, %.3lf):",
			point1[0],point1[1],point1[2]);
		for (i=0;i<6;i++)
		{
			fprintf(_outFPT,"\n");

			for (j=0;j<nu;j++)
				fprintf(_outFPT,"%12.5lf   ",J[i*nu + j]);
		}

		aModel->formJacobianInverse(I,J,J_1);
		fprintf(_outFPT,"\n\nJacobianInverse at point (%.3lf, %.3lf, %.3lf):",
			point1[0],point1[1],point1[2]);
		for (i=0;i<nu;i++)
		{
			fprintf(_outFPT,"\n");

			for (j=0;j<6;j++)
				fprintf(_outFPT,"%12.5lf   ",J_1[i*nu + j]);
		}

		// MULTIPLY J * J_1
		double identity[6][6];
		rdMtx::Multiply(6,nu,6,J,J_1,&identity[0][0]);

		fprintf(_outFPT,"\n\nJacobian * JacobianInverse ?= Identity Matrix:");
		for (i=0;i<6;i++)
		{
			fprintf(_outFPT,"\n");

			for (j=0;j<6;j++)
				fprintf(_outFPT,"%12.5lf   ",identity[i][j]);
		}


		// APPLY A FORCE AT POINT
		double fp[] = { 1.0, 0.0, 0.0 , 0.0, 0.0, 0.0 };

		// COMPUTE EQUIVALENT GENERALIZED FORCES
		double f[6];
		double *JT = new double[nu*6];

		rdMtx::Transpose(6,nu,J,JT);

		fprintf(_outFPT,"\n\nJacobianTranspose at point (%.3lf, %.3lf, %.3lf):",
			point1[0],point1[1],point1[2]);
		for (i=0;i<nu;i++)
		{
			fprintf(_outFPT,"\n");

			for (j=0;j<6;j++)
				fprintf(_outFPT,"%12.5lf   ",JT[i*nu + j]);
		}


		rdMtx::Multiply(nu,6,1,JT,fp,f);

		fprintf(_outFPT,"\n\nForce at point (%.3lf, %.3lf, %.3lf):",
			point1[0],point1[1],point1[2]);

		fprintf(_outFPT,"\n");

		for (i=0;i<6;i++)
			fprintf(_outFPT,"%.3lf   ",f[i]);


		// GET JACOBIAN AND ITS INVERSE FOR A NEW POINT

		aModel->formJacobian(body,point2,J);
		fprintf(_outFPT,"\n\nJacobian at point (%.3lf, %.3lf, %.3lf):",
			point2[0],point2[1],point2[2]);
		for (i=0;i<6;i++)
		{
			fprintf(_outFPT,"\n");

			for (j=0;j<nu;j++)
				fprintf(_outFPT,"%12.5lf   ",J[i*nu + j]);
		}

		aModel->formJacobianInverse(I,J,J_1);
		fprintf(_outFPT,"\n\nJacobianInverse at point (%.3lf, %.3lf, %.3lf):",
			point2[0],point2[1],point2[2]);
		for (i=0;i<6;i++)
		{
			fprintf(_outFPT,"\n");

			for (j=0;j<nu;j++)
				fprintf(_outFPT,"%12.5lf   ",J_1[i*nu + j]);
		}


		// PROJECT BACK TO THE NEW POINT
		double fpp[6];
		double *J_1T = new double[6*nu];

		rdMtx::Transpose(nu,6,J_1,J_1T);

		fprintf(_outFPT,"\n\nJacobianInverseTranspose at point (%.3lf, %.3lf, "
			"%.3lf):",point2[0],point2[1],point2[2]);
		for (i=0;i<nu;i++)
		{
			fprintf(_outFPT,"\n");

			for (j=0;j<6;j++)
				fprintf(_outFPT,"%12.5lf   ",J_1T[i*nu + j]);
		}


		rdMtx::Multiply(6,nu,1,J_1T,f,fpp);

		fprintf(_outFPT,"\n\nForce at point (%.3lf, %.3lf, %.3lf):",
			point2[0],point2[1],point2[2]);

		fprintf(_outFPT,"\n");

		for (i=0;i<6;i++)
			fprintf(_outFPT,"%.3lf   ",fpp[i]);


		delete JT;
		delete J_1T;
	}


	delete I;
	delete J;
	delete J_1;

	fprintf(_outFPT,"\n\nrdModelTestSuite.TestJacobian: PASSED.\n"
		"========================================"
		"=======================================\n\n");

	*/
	return(true);
}

/*
	int i;

	// GET NUMBERS
	int nq = aModel->getNQ();
	int nu = aModel->getNU();

	// CONSTRUCT Q's and U's
	double *q = new double[nq];
	double *u = new double[nu];

	// SET VALUES FOR THE Q'S AND U'S
	for(i=0;i<nq;i++) q[i] = 0.0;
	for(i=0;i<nu;i++) u[i] = 0.0;
	//q[3] = rdMath::DTR*90.0;   
	//q[4] = rdMath::DTR*20.0;
	//q[5] = rdMath::DTR*20.0;

	// CONVERT TO QUATERNIONS
	aModel->convertAnglesToQuaternions(q,q);

	// SET THE CONFIGURATION
	aModel->setConfiguration(q,u);

	// DEFINE SOME PARAMETERS
	int body = 0;
	double point[] = { 1.0, 1.0, 1.0 };

	// TEST JACOBIAN METHODS
	double *I = new double[nu*nu];
	double *J = new double[6*nu];
	double *J_1 = new double[nu*6];
	aModel->formMassMatrix(I);
	fprintf(_outFPT,"\nMass Matrix:\n");  rdMtx::Print(nu,nu,I,3);
	aModel->formJacobian(body,point,J);
	fprintf(_outFPT,"\nJacobian:\n");  rdMtx::Print(6,nu,J,3);
	aModel->formJacobianInverse(I,J,J_1);

	// MULTIPLY J * J_1
	double identity[6][6];
	rdMtx::Multiply(6,nu,6,J,J_1,&identity[0][0]);
	fprintf(_outFPT,"\n\nIdentity?:\n");
	rdMtx::Print(6,6,&identity[0][0],3);

	// APPLY A FORCE AT POINT
	double fp[] = { 1.0, 0.0, 0.0 , 0.0, 0.0, 0.0 };

	// COMPUTE EQUIVALENT GENERALIZED FORCES
	double f[6];
	double *JT = new double[nu*6];
	rdMtx::Transpose(6,nu,J,JT);
	rdMtx::Multiply(nu,6,1,JT,fp,f);

	// GET JACOBIAN AND ITS INVERSE FOR A NEW POINT
	double point2[] = { 1.0, 1.0, -1.0 };
	aModel->formJacobian(body,point2,J);
	aModel->formJacobianInverse(I,J,J_1);

	// PROJECT BACK TO THE NEW POINT
	double fpp[6];
	double *J_1T = new double[6*nu];
	rdMtx::Transpose(nu,6,J_1,J_1T);
	rdMtx::Multiply(6,nu,1,J_1T,f,fpp);

	// PRINT THE RESULTS
	fprintf(_outFPT,"\n\nForce Testing...\n");
	fprintf(_outFPT,"\nForce:\n");
	rdMtx::Print(6,1,fp,3);
	fprintf(_outFPT,"\nGeneralized Forces:\n");
	rdMtx::Print(6,1,f,3);
	fprintf(_outFPT,"\nProjected Force:\n");
	rdMtx::Print(6,1,fpp,3);


*/


//=============================================================================
// UTILITY
//=============================================================================
//__________________________________________________________________________
/**
 * Test angular conversions.
 *		rdModel::convertDirectionCosinesToQuaternions()
 *		rdModel::convertQuaternionsToDirectionCosines()
 *		rdModel::convertDirectionCosinesToAngles()
 *		rdModel::convertAnglesToDirectionCosines()
 *		rdModel::convertAnglesToQuaternions()
 *		rdModel::convertQuaternionsToAngles()
 *		rdModel::convertRadiansToDegrees()
 *		rdModel::convertDegreesToRadians()
 *
 * @param aModel Model on which to test the methods.
 * @return False if the test fails in some manner, true otherwise.
 */
bool rdModelTestSuite::
TestOrientationUtilities(rdModel *aModel)
{
	if(aModel==NULL) {
		fprintf(_outFPT,"rdModelTestSuite.TestOrientationUtilities: "
			"FAILED- NULL model pointer.\n");
		return(false);
	}


	fprintf(_outFPT,"\n========================================"
		"=======================================\n"
		"rdModelTestSuite.TestOrientationUtilities:\n");

	int i;
	double rDirCosStart[3][3],rDirCosOut[3][3];


	for (i=0;i<aModel->getNB();i++)
	{

		fprintf(_outFPT,"\n\nBody: %d  ------------------------------\n",i);

		aModel->getDirectionCosines(i,rDirCosStart);

		fprintf(_outFPT,"\nDirection Cosines (Start)\n"
			"-------------------------------");

		fprintf(_outFPT,"\n%9.6lf  %9.6lf  %9.6lf",
			rDirCosStart[0][0],rDirCosStart[0][1],rDirCosStart[0][2]);
		fprintf(_outFPT,"\n%9.6lf  %9.6lf  %9.6lf",
			rDirCosStart[1][0],rDirCosStart[1][1],rDirCosStart[1][2]);
		fprintf(_outFPT,"\n%9.6lf  %9.6lf  %9.6lf",
			rDirCosStart[2][0],rDirCosStart[2][1],rDirCosStart[2][2]);

		fprintf(_outFPT,"\n-------------------------------\n");


		double rQ1,rQ2,rQ3,rQ4;

		aModel->convertDirectionCosinesToQuaternions(rDirCosStart,
			&rQ1,&rQ2,&rQ3,&rQ4);

		fprintf(_outFPT,"\n\nQuaternions\n"
			"------------------------------------------------------");

		fprintf(_outFPT,"\n%12.4lf  %12.4lf  %12.4lf  %12.4lf",
			rQ1,rQ2,rQ3,rQ4);

		fprintf(_outFPT,"\n------------------------------"
			"------------------------\n");


		aModel->convertQuaternionsToDirectionCosines(rQ1,rQ2,rQ3,rQ4,
			rDirCosOut);

		fprintf(_outFPT,"\n\nDirection Cosines\n"
			"-------------------------------");

		fprintf(_outFPT,"\n%9.6lf  %9.6lf  %9.6lf",
			rDirCosOut[0][0],rDirCosOut[0][1],rDirCosOut[0][2]);
		fprintf(_outFPT,"\n%9.6lf  %9.6lf  %9.6lf",
			rDirCosOut[1][0],rDirCosOut[1][1],rDirCosOut[1][2]);
		fprintf(_outFPT,"\n%9.6lf  %9.6lf  %9.6lf",
			rDirCosOut[2][0],rDirCosOut[2][1],rDirCosOut[2][2]);

		fprintf(_outFPT,"\n-------------------------------\n");


		double rE1,rE2,rE3;

		aModel->convertDirectionCosinesToAngles(rDirCosOut,&rE1,&rE2,&rE3);

		fprintf(_outFPT,"\n\nAngles\n"
			"----------------------------------------");

		fprintf(_outFPT,"\n%12.4lf  %12.4lf  %12.4lf",rE1,rE2,rE3);

		fprintf(_outFPT,"\n----------------------------------------\n");


		aModel->convertAnglesToDirectionCosines(rE1,rE2,rE3,rDirCosOut);

		fprintf(_outFPT,"\nDirection Cosines\n"
			"------------------------------");

		fprintf(_outFPT,"\n%9.6lf  %9.6lf  %9.6lf",
			rDirCosOut[0][0],rDirCosOut[0][1],rDirCosOut[0][2]);
		fprintf(_outFPT,"\n%9.6lf  %9.6lf  %9.6lf",
			rDirCosOut[1][0],rDirCosOut[1][1],rDirCosOut[1][2]);
		fprintf(_outFPT,"\n%9.6lf  %9.6lf  %9.6lf",
			rDirCosOut[2][0],rDirCosOut[2][1],rDirCosOut[2][2]);

		fprintf(_outFPT,"\n-------------------------------\n");


		double DCError[3][3];

		for (int j=0;j<3;j++)
			for (int k=0;k<3;k++)
				DCError[j][k] = rDirCosOut[j][k] - rDirCosStart[j][k];

		fprintf(_outFPT,"\n\nDirection Cosines Error\n"
			"-------------------------------");

		fprintf(_outFPT,"\n%9.6lf  %9.6lf  %9.6lf",
			DCError[0][0],DCError[0][1],DCError[0][2]);
		fprintf(_outFPT,"\n%9.6lf  %9.6lf  %9.6lf",
			DCError[1][0],DCError[1][1],DCError[1][2]);
		fprintf(_outFPT,"\n%9.6lf  %9.6lf  %9.6lf",
			DCError[2][0],DCError[2][1],DCError[2][2]);

		fprintf(_outFPT,"\n-------------------------------\n");




		int nu = aModel->getNU();
		int nq = aModel->getNQ();

		double *aQAng = new double[nu];
		double *aQ = new double[nq];


		for (i=0;i<nu;i++)
			aQAng[i] = ((double)i) * 0.1;

		fprintf(_outFPT,"\n\nAngles (Start)\n----------");

		for (i=0;i<nu;i++)
			fprintf(_outFPT,"\n%.4lf",aQAng[i]);

		fprintf(_outFPT,"\n---------\n");


		aModel->convertAnglesToQuaternions(aQAng,aQ);


		fprintf(_outFPT,"\n\nQuaternions\n----------");

		for (i=0;i<nq;i++)
			fprintf(_outFPT,"\n%.4lf",aQ[i]);

		fprintf(_outFPT,"\n---------\n");


		aModel->convertQuaternionsToAngles(aQ,aQAng);


		fprintf(_outFPT,"\n\nAngles (radians)\n----------");

		for (i=0;i<nu;i++)
			fprintf(_outFPT,"\n%.4lf",aQAng[i]);

		fprintf(_outFPT,"\n---------\n");


		double *rQDeg = new double[nu];

		aModel->convertRadiansToDegrees(aQAng,rQDeg);

		fprintf(_outFPT,"\n\nAngles (degrees)\n----------");

		for (i=0;i<nu;i++)
			fprintf(_outFPT,"\n%.4lf",rQDeg[i]);

		fprintf(_outFPT,"\n---------\n");

		double *rQAng = new double[nu];

		aModel->convertDegreesToRadians(rQDeg,rQAng);

		fprintf(_outFPT,"\n\nAngles (radians)\n----------");

		for (i=0;i<nu;i++)
			fprintf(_outFPT,"\n%.4lf",rQAng[i]);

		fprintf(_outFPT,"\n---------\n");


		delete aQAng;
		delete aQ;
		delete rQDeg;
		delete rQAng;

	}



	fprintf(_outFPT,"\nrdModelTestSuite.TestOrientationUtilities: PASSED.\n"
		"========================================"
		"=======================================\n\n");


	return(true);
}



//=============================================================================
// CONTACT
//=============================================================================
//__________________________________________________________________________
/**
 * Test class rdContactForceSet.
 *
 * Right now these tests don't make use of the model at all; they
 * just test constructing a set of contacts from file and then writing
 * them back out to file.
 * @param aModel Model on which to test the methods.
 * @return False if the test fails in some manner, true otherwise.
 */
bool rdModelTestSuite::
TestContacts(rdModel *aModel)
{
	fprintf(_outFPT,"\n\nrdModelTestSuite.TestContacts...");
	char defaultName[] = "default.ctx";
	char set1Name[] = "set1.ctx";
	char set2Name[] = "set2.ctx";

	// CREATE A DEFAULT SET AND WRITE TO FILE
	rdContactForceSet *contacts = new rdContactForceSet();
	contacts->print(defaultName);

	// CONSTRUCT CONTACTS FROM FILE
	//rdContactForceSet *contacts1 = new rdContactForceSet(fileName1);

	// WRITE CONTACTS
	//contacts1->print(set2Name);

	// CLEANUP
	delete contacts;
	//delete contacts1;

	return(true);
}


//=============================================================================
// ACTUATORS
//=============================================================================
//__________________________________________________________________________
/**
 * Test class rdActuatorSet.
 *
 * Right now these tests don't make use of the model at all; they
 * just test constructing a set of actuators from file and then writing
 * them back out to file.
 *
 * @param aModel Model on which to test the methods.
 * @return False if the test fails in some manner, true otherwise.
 */
bool rdModelTestSuite::
TestActuators(rdModel *aModel)
{
	fprintf(_outFPT,"\n\nrdModelTestSuite.TestActuators...");
	char defaultName[] = "default.act";
	char set1Name[] = "set1.act";
	char set2Name[] = "set2.act";

	// CREATE A DEFAULT SET AND WRITE TO FILE
	rdActuatorSet *act = new rdActuatorSet();
	act->print(defaultName);

	// CONSTRUCT ACTUATORS FROM FILE
	//rdActuatorSet *act1 = new rdActuatorSet(set1Name);

	// WRITE ACTUATORS
	//act1->print(set2Name);

	// CLEANUP
	delete act;
	//delete act1;

	return(true);
}
