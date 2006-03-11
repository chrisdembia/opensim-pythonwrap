// rra.cpp
// Authors:  Clay Anderson, Chand T. John

// INCLUDE
#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include <NMBLTK/Simulation/Model/LoadModel.h>
#include <NMBLTK/Simulation/Model/rdAnalysisSet.h>
#include <NMBLTK/Simulation/Model/rdDerivCallbackSet.h>
#include <NMBLTK/Simulation/Model/rdModelIntegrandForActuators.h>
#include <NMBLTK/Simulation/Control/rdControlLinear.h>
#include <NMBLTK/Simulation/Control/rdControlConstant.h>
#include <NMBLTK/Simulation/Control/rdControlSet.h>
#include <NMBLTK/Simulation/Manager/rdManager.h>
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Tools/rdArray.h>
#include <NMBLTK/Tools/rdIO.h>
#include <NMBLTK/Tools/rdVectorGCVSplineR1R3.h>
#include <NMBLTK/Tools/rdGCVSplineSet.h>
#include <NMBLTK/Analyses/suForceApplier.h>
#include <NMBLTK/Analyses/suTorqueApplier.h>
#include <NMBLTK/Analyses/suKinematics.h>
#include <NMBLTK/Analyses/suActuation.h>
#include <RDI/CMC/rdCMC.h>
#include <RDI/CMC/rdCMC_TaskSet.h>
#include <RDI/CMC/rdCMC_Joint.h>
#include <RDI/CMC/rdActuatorForceTarget.h>
#include <RDI/CMC/rdActuatorForceTargetFast.h>

#define PI 3.14159265359


using namespace std;

void ParseCommandLine(int argc, char **argv,
					  string &prefix, string &trackingFileName,
					  double perturb[12],
					  bool &computingCorrections);

//_____________________________________________________________________________
/**
 * Main routine for running RRA on a given model and motion.
 */
int main(int argc,char **argv)
{
	int i;
	rdIO::SetPrecision(12);


	//=======================
	// PARSE COMMAND LINE
	//=======================

	string prefix, trackingFileName;
	double perturb[12] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	bool computingCorrections;
	ParseCommandLine(argc, argv, prefix, trackingFileName, perturb, computingCorrections);


	//=======================
	// REGISTER TYPES
	//=======================
	
	// Control task types
	rdObject::RegisterType(rdCMC_Joint());


	//=======================
	// CONSTRUCT MODEL
	//=======================

	// Load model: for now, we assume we are working only with SIMM-wrapped models
	rdModel *model = LoadModel(argc,argv);
	cout<<"Finished call to LoadModel\n";
	if(model==NULL) {
		cout<<"\nrra:  ERROR- failed to load model.\n";
		exit(-1);
	}
	model->setIncludePipelineActuators(false);
	cout<<"-----------------------------------------------------------------------\n";
	cout<<"Loaded library\n";
	cout<<"-----------------------------------------------------------------------\n";
	model->printDetailedInfo(cout);
	cout<<"-----------------------------------------------------------------------\n\n";


	//============================
	// ALTER INERTIAL PARAMETERS
	//============================

	// Add RRA perturbations to user perturbations
	rdArray<double> btj(0.0);
	btj.setSize(3);
	int iTorso = model->getBodyIndex("torso");
	string rraPerturbFileName = prefix + ".txt";
	ifstream rraPerturbFile;
	rraPerturbFile.open(rraPerturbFileName.c_str());
	// If file is valid, read and incorporate torso COM alterations
	if(!rraPerturbFile.fail())
	{
		double changeTx, changeTz;
		rraPerturbFile >> changeTx >> changeTz;
		perturb[0] += changeTx;
		perturb[2] += changeTz;
	}
	else
	{
		cout << "No torso COM alterations suggested by RRA." << "\n";
	}
	rraPerturbFile.close();
    
	// Alter the center of mass of the torso if user and/or RRA said so
	for(i = 0; i < 3; i++)
	{
		if (perturb[i] != 0.0)
		{
			model->getBodyToJointBodyLocal(iTorso,&btj[0]);
			btj[i] += perturb[i];
			model->setBodyToJointBodyLocal(iTorso,&btj[0]);
		}
	}
	
	// Write message for torso center of mass perturbation if there was any
	if (perturb[0] != 0.0 || perturb[1] != 0.0 || perturb[2] != 0.0)
	{
		cout << "Changed torso COM to " << "("
			 << btj[0] << ", " << btj[1] << ", " << btj[2] << ").\n\n";
	}

	
	//=====================================
	// COMPUTE TRAJECTORIES FROM .MOT FILE
	//=====================================

	// Load desired trajectories
	string kineticsFileName = prefix + ".mot";
	
	//rdStorage fileStore(kineticsFileName.c_str());
	//string stofile = "s26ik_q.sto";
	//rdStorage fileStore2(stofile.c_str());
	rdStorage fileStore2(kineticsFileName.c_str());

	int nq = model->getNQ();

	// Get coordinate file indices
	string qName,columnLabels;
	rdArray<int> index(-1,nq);
	columnLabels = "time";
	for(i=0;i<nq;i++) {
		qName = model->getCoordinateName(i);
		columnLabels += "\t";
		columnLabels += qName;
		index[i] = fileStore2.getColumnIndex(qName);
	}

	// Extract Coordinates
	double time;
	rdArray<double> data(0.0);
	rdArray<double> q(0.0,nq);
	rdStorage qStore;
	qStore.setName("GeneralizedCoordinates");
	qStore.setColumnLabels(columnLabels.c_str());
	int size = fileStore2.getSize();
	rdStateVector *vector;
	int j;
	for(i=0;i<size;i++)
	{
		vector = fileStore2.getStateVector(i);
		data = vector->getData();
		time = vector->getTime();

		for(j=0;j<nq;j++) {
			q[j] = 0.0;
			if(index[j]<0) continue;
			q[j] = data[index[j]];
		}

		qStore.append(time,nq,&q[0]);
	}

	// Convert to radians
	model->convertDegreesToRadians(&qStore);

	// Compute generalized speeds
	rdGCVSplineSet tempQset(5,&qStore);
	rdStorage *uStore = tempQset.constructStorage(1);

	// Compute constraints
	rdArray<double> qu(0.0,nq+nq);
	int qSize = qStore.getSize();
	int uSize = uStore->getSize();
	cout<<"qSize = "<<qSize<<endl<<endl;
	cout<<"uSize = "<<uSize<<endl<<endl;
	rdStorage trajectories;
	rdStorage uCompleteStore;
	for(i=0;i<size;i++)
	{
		qStore.getTime(i,time);
		qStore.getData(i,nq,&qu[0]);
		uStore->getData(i,nq,&qu[nq]);
		model->computeConstrainedCoordinates(&qu[0]);
		trajectories.append(time,nq,&qu[0]);
		uCompleteStore.append(time,nq,&qu[nq]);
	}

	// Convert back to degrees
	model->convertRadiansToDegrees(&trajectories);
	model->convertRadiansToDegrees(&uCompleteStore);

	// Compute storage object for simulation
	trajectories.setColumnLabels(columnLabels.c_str());
	trajectories.print("Results/rra_q.sto");
	uCompleteStore.setColumnLabels(columnLabels.c_str());
	uCompleteStore.print("Results/rra_u.sto");


	//=======================
	// SET UP TRACKING
	//=======================

	// Alter back angles if user said so
	if (perturb[3] != 0.0)
	{
		int columnIndex = trajectories.getColumnIndex("lumbar_extension");
		trajectories.add(columnIndex, perturb[3]);
	}
	if (perturb[4] != 0.0)
	{
		int columnIndex = trajectories.getColumnIndex("lumbar_bending");
		trajectories.add(columnIndex, perturb[4]);
	}
	if (perturb[5] != 0.0)
	{
		int columnIndex = trajectories.getColumnIndex("lumbar_rotation");
		trajectories.add(columnIndex, perturb[5]);
	}

	// Convert to radians
	model->convertDegreesToRadians(&trajectories);
	model->convertAnglesToQuaternions(&trajectories);

	// Set initial and final times
	double ti,tf;
	ti = trajectories.getFirstTime() + 0.01;
	tf = trajectories.getLastTime() - 0.01;
	cout<<endl<<endl<<"ti="<<ti<<" tf="<<tf<<endl<<endl;

	// Filter
	trajectories.pad(60);
	trajectories.print("Results/pad.sto");
	int order = 50;
	double cutoff = 20.0;
	trajectories.lowpassFIR(order,cutoff);

	// Construct splines for trajectories
	rdGCVSplineSet qSet(5,&trajectories);
	rdStorage *trajectoriesVel = qSet.constructStorage(1);
	rdGCVSplineSet uSet(5,trajectoriesVel);

	// Construct task set
	rdCMC_TaskSet taskSet(trackingFileName.c_str());
	taskSet.setModel(model);
	taskSet.setParametersBasedOnName();
	taskSet.setFunctions(qSet);
	cout<<"\n\nTracking "<<taskSet.getSize()<<" trajectories.\n\n";

	// Check trajectories
	trajectories.print("Results/filtered.sto");
	rdStorage *checkPositions = qSet.constructStorage(0);
	checkPositions->print("Results/checkPositions.sto");
	delete checkPositions;
	rdStorage *checkVelocities = qSet.constructStorage(1);
	checkVelocities->print("Results/checkVelocities.sto");
	delete checkVelocities;
	rdStorage *checkAccelerations = qSet.constructStorage(2);
	checkAccelerations->print("Results/checkAccelerations.sto");
	delete checkAccelerations;


	//=======================
	// INITIAL STATES
	//=======================

	int nu = model->getNU();
	int ny = model->getNY();
	rdArray<double> yi(0.0,ny);
	model->getInitialStates(&yi[0]);
	trajectories.getData(0, nq+nu, &yi[0]);
	rdCMC_Task *task;
	rdFunction *func;
	cout<<"\n\nInitial states:\n";
	for(i=0;i<nq;i++) {
		try {
			task = taskSet.get(model->getCoordinateName(i));
		} catch(rdException x) {
			x.print(cout);
			continue;
		}
		func = task->getTaskFunction(0);
		cout<<func->getName()<<endl;;
		yi[i] = func->evaluate(0,ti);
		yi[i+nq] = func->evaluate(1,ti);
		cout<<model->getStateName(i)<<"["<<i<<"]= "<<yi[i]<<", "<<yi[i+nq]<<endl;
	}
	model->setInitialStates(&yi[0]);

	// Bodies
	cout<<endl<<endl<<"Bodies:"<<endl;
	int nb = model->getNB();
	for(i=0;i<nb;i++) {
		cout<<"body["<<i<<"]= "<<model->getBodyName(i)<<endl;
	}
	cout<<endl;


	//=======================
	// GROUND REACTION FORCES
	//=======================

	// Read in ground reaction data from kinetics file.
	// The .mot file has the following column numbers and labels of interest:
	// - Right foot center of pressure (x,y,z): (col 35, col 36, col 37)
	// - Right foot ground reaction force vector (x,y,z): (col 38, col 39, col 40)
	// - Left foot center of pressure (x,y,z): (col 41, col 42, col 43)
	// - Left foot ground reaction force vector (x,y,z): (col 44, col 45, col 46)
	// - Right foot ground reaction torque vector (x,y,z): (col 47, col 48, col 49)
	// - Left foot ground reaction torque vector (x,y,z): (col 50, col 51, col 52)
	
	rdStorage fileStore(kineticsFileName.c_str());
	int copSize = fileStore.getSize();

	// If true, applies constant (usually zero) ground reaction forces and torques.
	// If false, applies GRFs and torques from the kinetics file.
	bool zeroGroundReactionForces = false;

	// If true, applies GRFs at constant body-local positions (usually (0,0,0)).
	// If false, applies GRFs at COPs from the kinetics file.
	bool constantForceLocation = false;

	// Create force and torque appliers
	int rightFoot = model->getBodyIndex("calcn_r");
	int  leftFoot = model->getBodyIndex("calcn_l");
	suForceApplier *rightForceApp = new suForceApplier(model,rightFoot);
	suTorqueApplier *rightTorqueApp = new suTorqueApplier(model,rightFoot);
	suForceApplier *leftForceApp = new suForceApplier(model,leftFoot);
	suTorqueApplier *leftTorqueApp = new suTorqueApplier(model,leftFoot);

	// Add COP location to force applier so frame is shifted
	// correctly as the model moves around
	double *t=0,*x=0,*y=0,*z=0;
	fileStore.getTimeColumn(t);

	// Alter the right foot COP location if user said so.
	if (perturb[6] != 0.0) {fileStore.add(35, perturb[6]);}
	if (perturb[7] != 0.0) {fileStore.add(36, perturb[7]);}
	if (perturb[8] != 0.0) {fileStore.add(37, perturb[8]);}

	// Set right foot COP location as point function for the right foot
	// force applier.
	//
	// Note:
	// <prefix>.mot has multiple columns with the same label,
	// doesn't distinguish between left and right COP column labels,
	// so we have to use the column numbers instead of the column
	// names to search for the columns of data we want.  Normally we
	// would just search for the column with the name ground_force_px_r,
	// or ground_force_px_l, etc.
	if (!constantForceLocation)
	{
		fileStore.getDataColumn(35,x);
		fileStore.getDataColumn(36,y);
		fileStore.getDataColumn(37,z);
		rdVectorGCVSplineR1R3 *rightCop;
		rightCop = new rdVectorGCVSplineR1R3(3,copSize,t,x,y,z);
		rightForceApp->computePointFunction(&trajectories, trajectoriesVel, *rightCop);
	}
	else
	{
		double rightCop[3] = {0.0, 0.0, 0.0};
		rightForceApp->setPoint(rightCop);
	}

	// Alter the right foot COP location if user said so.
	if (perturb[ 9] != 0.0) {fileStore.add(41, perturb[ 9]);}
	if (perturb[10] != 0.0) {fileStore.add(42, perturb[10]);}
	if (perturb[11] != 0.0) {fileStore.add(43, perturb[11]);}

	// Set left foot COP location as point function for the left foot
	// force applier.
	if (!constantForceLocation)
	{
		fileStore.getDataColumn(41,x);
		fileStore.getDataColumn(42,y);
		fileStore.getDataColumn(43,z);
		rdVectorGCVSplineR1R3 *leftCop;
		leftCop = new rdVectorGCVSplineR1R3(3,copSize,t,x,y,z);
		leftForceApp->computePointFunction(&trajectories, trajectoriesVel, *leftCop);
	}
	else
	{
		double leftCop[3] = {0.0, 0.0, 0.0};
		leftForceApp->setPoint(leftCop);
	}

	// Compute and set the force function for the right foot
	// force applier.
	if (!zeroGroundReactionForces)
	{
		fileStore.getDataColumn(38,x);
		fileStore.getDataColumn(39,y);
		fileStore.getDataColumn(40,z);
		rdVectorGCVSplineR1R3 *rightForce;
		rightForce = new rdVectorGCVSplineR1R3(3,copSize,t,x,y,z);
		rightForceApp->setForceFunction(rightForce);
	}
	else // Apply a constant force
	{
		double rightForce[3] = {0.0, 0.0, 0.0};
		rightForceApp->setForce(rightForce);
	}

	// Compute and set the force function for the left foot
	// force applier.
	if (!zeroGroundReactionForces)
	{
		fileStore.getDataColumn(44,x);
		fileStore.getDataColumn(45,y);
		fileStore.getDataColumn(46,z);
		rdVectorGCVSplineR1R3 *leftForce;
		leftForce = new rdVectorGCVSplineR1R3(3,copSize,t,x,y,z);
		leftForceApp->setForceFunction(leftForce);
	}
	else // Apply a constant force
	{
		double leftForce[3] = {0.0, 0.0, 0.0};
		leftForceApp->setForce(leftForce);
	}

	// Compute and set the torque function for the right foot
	// torque applier.
	if (!zeroGroundReactionForces)
	{
		fileStore.getDataColumn(47,x);
		fileStore.getDataColumn(48,y);
		fileStore.getDataColumn(49,z);
		rdVectorGCVSplineR1R3 *rightTorque;
		rightTorque = new rdVectorGCVSplineR1R3(3,copSize,t,x,y,z);
		rightTorqueApp->setTorqueFunction(rightTorque);
	}
	else // Apply a constant torque
	{
		double rightTorque[3] = {0.0, 0.0, 0.0};
		rightTorqueApp->setTorque(rightTorque);
	}

	// Compute and set the torque function for the left foot
	// torque applier.
	if (!zeroGroundReactionForces)
	{
		fileStore.getDataColumn(50,x);
		fileStore.getDataColumn(51,y);
		fileStore.getDataColumn(52,z);
		rdVectorGCVSplineR1R3 *leftTorque;
		leftTorque = new rdVectorGCVSplineR1R3(3,copSize,t,x,y,z);
		leftTorqueApp->setTorqueFunction(leftTorque);
	}
	else // Apply a constant torque
	{
		double leftTorque[3] = {0.0, 0.0, 0.0};
		leftTorqueApp->setTorque(leftTorque);
	}

	// Add force and torque appliers as derivative callbacks for model.
	// Set input in global frame is true by default--we're just being
	// paranoid here by setting it to true for sure.
	rightForceApp->setInputForcesInGlobalFrame(true);
	leftForceApp->setInputForcesInGlobalFrame(true);
	rightTorqueApp->setInputTorquesInGlobalFrame(true);
	leftTorqueApp->setInputTorquesInGlobalFrame(true);
	model->addDerivCallback(rightForceApp);
	model->addDerivCallback(leftForceApp);
	model->addDerivCallback(rightTorqueApp);
	model->addDerivCallback(leftTorqueApp);


	//=======================
	// ANALYSES
	//=======================
	
	int stepInterval = 10;
	// Actuation
	suActuation *actuation = new suActuation(model);
	actuation->setStepInterval(stepInterval);
	model->addAnalysis(actuation);
	// Kinematics
	suKinematics *kin = new suKinematics(model);
	kin->setStepInterval(stepInterval);
	kin->getPositionStorage()->setWriteSIMMHeader(true);
	model->addAnalysis(kin);


	// TRACKING CONTROLLER----
	// CONTROLLER
	rdCMC controller(model,&taskSet);
	controller.setTargetDT(0.001);

	// OPTIMIZATION TARGET
	int na = model->getNA();
	//rdActuatorForceTargetFast target(na,&controller);
	rdActuatorForceTarget target(na,&controller);
	controller.setOptimizationTarget(&target);
	controller.setCheckTargetTime(true);
	target.setDX(1.0e-4);

	// ACTUATOR FORCE PREDICTOR
	// Integrand
	//rdModelIntegrand cmcIntegrand(&model);
	rdModelIntegrandForActuators cmcIntegrand(model);
	cmcIntegrand.setCoordinateTrajectories(&qSet);
	cmcIntegrand.setSpeedTrajectories(&uSet);
	rdControlSet *rootSet = cmcIntegrand.getControlSet();
	for(i=0;i<rootSet->getSize();i++) {
		rdControlLinear *control = (rdControlLinear*)rootSet->get(i);
		control->setUseSteps(true);
		control->getNodeArray().setSize(0);
		control->setDefaultParameterMin(-1.0);
		control->setDefaultParameterMax(1.0);
	}
	VectorFunctionForActuators *predictor =
		new VectorFunctionForActuators(&cmcIntegrand);
	controller.setActuatorForcePredictor(predictor);


	// OPTIMIZATION SETTINGS
	rdFSQP *sqp = controller.getOptimizer();
	sqp->setPrintLevel(0);
	sqp->setConvergenceCriterion(1.0e-6);


	// SIMULATION SETUP----
	// Manager
	rdModelIntegrand integrand(model);
	integrand.setController(&controller);
	rdManager manager(&integrand);
	manager.setSessionName("RRA");
	manager.setInitialTime(ti);
	manager.setFinalTime(tf);

	// CREATE CONTROL SET
	rdControlSet *controlSet = integrand.getControlSet();
	size = controlSet->getSize();
	for(i=0;i<size;i++) {
		rdControlLinear *control = (rdControlLinear*)controlSet->get(i);
		control->setUseSteps(true);
		control->setControlValueMin(0.0,-1.0);
		control->setControlValueMax(0.0,1.0);
		control->setDefaultParameterMin(-1.0);
		control->setDefaultParameterMax(1.0);
	}

	// Integrator settings
	int maxSteps = 20000;
	rdIntegRKF *integ = manager.getIntegrator();
	integ->setMaximumNumberOfSteps(maxSteps);
	integ->setUseConstantDT(false);
	//integ->setDT(0.00087);
	integ->setMaxDT(5.0e-4);
	integ->setTolerance(1.0e-5);
	integ->setFineTolerance(5.0e-7);


	// INTEGRATE
	cout<<"\n\nIntegrating from "<<ti<<" to "<<tf<<endl;
	manager.integrate();


	// RESULTS
	// Storage
	rdStorage *yStore = integrand.getStateStorage();
	rdStorage *ypStore = integrand.getPseudoStateStorage();
	rdStorage *xStore = integrand.getControlStorage();

	// Print
	double dt = 0.005;
	rdAnalysisSet *analysisSet = model->getAnalysisSet();
	string stoFileName;
	stoFileName= "Results/" + prefix + "_controls.sto";
	xStore->print(stoFileName.c_str(),dt);
	stoFileName= "Results/" + prefix + "_states.sto";
	yStore->print(stoFileName.c_str(),dt);
	analysisSet->printResults(prefix.c_str(),"Results",dt);

	// Print ground reaction force and torque application results
	rightForceApp->printResults(prefix.c_str(), "Results", dt);
	rightTorqueApp->printResults(prefix.c_str(), "Results", dt);
	leftForceApp->printResults(prefix.c_str(), "Results", dt);
	leftTorqueApp->printResults(prefix.c_str(), "Results", dt);


	// COMPUTE NEEDED DC OFFSETS
	rdStorage *forceStore = actuation->getForceStorage();
	int ncols = forceStore->getSmallestNumberOfStates();
	int iFX,iFY,iFZ,iMX,iMY,iMZ;
	iFX = forceStore->getColumnIndex("FX");
	iFY = forceStore->getColumnIndex("FY");
	iFZ = forceStore->getColumnIndex("FZ");
	iMX = forceStore->getColumnIndex("MX");
	iMY = forceStore->getColumnIndex("MY");
	iMZ = forceStore->getColumnIndex("MZ");

	rdStorage residuals(6, "Residuals");
	string colLabels = "time\tFX\tFY\tFZ\tMX\tMY\tMZ";
	residuals.setColumnLabels(colLabels.c_str());
	double tempTime;
	// Temporary array to store each row of residual data
	double resid[6];
	for (int i = 0; i < forceStore->getSize(); i++)
	{
		// t := ith time value
		forceStore->getTime(i, tempTime);
		// Read the values of FX, FY, FZ, MX, MY, and MZ
		// in the ith row of the forceStore object
		forceStore->getData(i, iFX, resid[0]);
		forceStore->getData(i, iFY, resid[1]);
		forceStore->getData(i, iFZ, resid[2]);
		forceStore->getData(i, iMX, resid[3]);
		forceStore->getData(i, iMY, resid[4]);
		forceStore->getData(i, iMZ, resid[5]);
		// Add the row (tempTime,resid[0],resid[1],...,resid[5]) to
		// the residual storage object.  Note that FX=resid[0],
		// FY=resid[1], FZ=resid[2], MX=resid[3], MY=resid[4],
		// and MZ=resid[5].
		residuals.append(tempTime, 6, resid);
	}

	// Print residuals out to a file
	stoFileName = "Results/" + prefix + "_residuals.sto";
	residuals.print(stoFileName.c_str(),dt);

	// Now actually compute the DC offsets like we promised
	rdArray<double> ave(0.0);
	ave.setSize(ncols);
	forceStore->computeAverage(ncols,&ave[0]);
	cout<<"\n\nAverage residuals:\n";
	cout<<"FX="<<ave[iFX]<<" FY="<<ave[iFY]<<" FZ="<<ave[iFZ]<<endl;
	cout<<"MX="<<ave[iMX]<<" MY="<<ave[iMY]<<" MZ="<<ave[iMZ]<<endl<<endl<<endl;

	// Write the average residuals (DC offsets) out to a file
	ofstream residualFile;
	stoFileName = "Results/" + prefix + "_avgResiduals.txt";
	residualFile.open (stoFileName.c_str());
	residualFile << "Average Residuals:\n\n";
	residualFile << "FX average = " << ave[iFX] << "\n";
	residualFile << "FY average = " << ave[iFY] << "\n";
	residualFile << "FZ average = " << ave[iFZ] << "\n";
	residualFile << "MX average = " << ave[iMX] << "\n";
	residualFile << "MY average = " << ave[iMY] << "\n";
	residualFile << "MZ average = " << ave[iMZ] << "\n";
	residualFile.close();

	// End program if not computing corrections.  Otherwise, proceed.
	if (!computingCorrections)
	{
		cout << "Not computing corrections, so RRA is done." << endl;
		return(0);
	}

	//=======================
	// COMPUTE CORRECTIONS
	//=======================

	// Compute torso weight
	double torsoMass = model->getMass(iTorso);
	double torsoWeight = 9.81 * torsoMass;

	// Compute torso moment arm and torque
	int iPelvis = model->getBodyIndex("pelvis");
	rdArray<double> pelvis(0.0);
	pelvis.setSize(3);
	model->getBodyToJointBodyLocal(iTorso, &btj[0]);
	model->getBodyToJointBodyLocal(iPelvis,&pelvis[0]);
	double rx = pelvis[0] - btj[0];
	double ry = pelvis[1] - btj[1];
	double rz = pelvis[2] - btj[2];
	double torsoMomentArm = sqrt(rx*rx + ry*ry + rz*rz);
	double torsoTorque = torsoWeight * torsoMomentArm;

	// Boolean flags for whether or not to perform each correction
	bool txOkay = true, tzOkay = true;

	// Compute torso center-of-mass corrections
	double dTx =  ave[iMZ] / torsoWeight;
	double dTz = -ave[iMX] / torsoWeight;
	if (dTx < -0.1 || dTx > 0.1)
	{
		cout << "Torso COM x needs to be changed too much." << endl;
		cout << "Continuing without changing torso COM x." << endl;
		txOkay = false;
	}
	if (dTz < -0.1 || dTz > 0.1)
	{
		cout << "Torso COM z needs to be changed too much." << endl;
		cout << "Continuing without changing torso COM z." << endl;
		tzOkay = false;
	}

	// If data cannot be corrected, say so and exit
	if (!txOkay && !tzOkay)
	{
		cout << "This data cannot be corrected." << endl;
		cout << "I'm giving up!" << endl;
	}

	// Write torso center-of-mass corrections to a file
	double txOutput = txOkay ? dTx : 0.0;
	double tzOutput = tzOkay ? dTz : 0.0;
	if ((txOkay || tzOkay) && (txOutput != 0.0 || tzOutput != 0.0))
	{
		ofstream perturbFile;
		stoFileName = prefix + "_corrected_by_RRA.txt";
		perturbFile.open (stoFileName.c_str());
		perturbFile << txOutput << "\n";
		perturbFile << tzOutput << "\n";
		perturbFile.close();
	}

	// Write corrected trajectories out to a file
	// Note: currently, this should be identical to the
	//       original .mot file, since we are not changing
	//       the back angles or any other kinematics
	stoFileName = prefix + "_corrected_by_RRA.mot";
	fileStore2.print(stoFileName.c_str());

	return(0);
}


//_____________________________________________________________________________
/**
 * Parse the command line for perturbations and filename prefix.
 *
 * @param argc Number of arguments in command line including .exe filename.
 * @param argv Array of arguments from command line.
 * @param prefix Prefix for subject-specific data file names to be returned.
 * @param trackingFileName Name of file containing tracked coordinates.
 * @param perturb Array of perturbation amounts to be returned.
 * @param computingCorrections Flag indicating whether to run RRA corrections.
 */
void ParseCommandLine(int argc, char **argv,
					  string &prefix, string &trackingFileName,
					  double perturb[12],
					  bool &computingCorrections)
{
	// Create cushioned usage string to output in case of command line errors.
	string usage =
	         "Usage:  rra.exe  -ModelLibrary <subject>.dll\n";
	usage += "                 -Actuators    <actuatorsFile>\n";
	usage += "                [-Contacts     <contactsFile>]\n";
	usage += "                [-Library      <libraryFile>]\n";
	usage += "                [-ModelFile    <modelFile>]\n";
	usage += "                 -Params       <parameterFile>\n";
	usage += "                 -Prefix   <prefix>\n";
	usage += "                 -Tracking <trackingFile>\n";
	usage += "                [-Correct  <yes|no>]\n";
	usage += "                [-tx amt] [-ty amt] [-tz amt]\n";
	usage += "                [-le amt] [-lb amt] [-lr amt]\n";
	usage += "                [-rx amt] [-ry amt] [-rz amt]\n";
	usage += "                [-lx amt] [-ly amt] [-lz amt]\n";
	usage += "\n";
	usage += "The first six flags are case sensitive.\n";
	usage += "The remaining flags are NOT case sensitive.\n";
	usage += "The flags can appear in any order but should not be repeated.\n";
	usage += "The flags inside square brackets are optional.\n";
	usage += "All angular perturbations should be in degrees.\n";
	usage += "All distance perturbations should be in meters.\n";
	usage += "\n";
	usage += "Guide to first eight flags:\n";
	usage += "-ModelLibrary or -ML is for the model dll file\n";
	usage += "-Actuators or -A is for the actuator set\n";
	usage += "-Contacts or -C is for the contact set\n";
	usage += "-Library or -L is for the type of actuators used by the model\n";
	usage += "-ModelFile or -MF is for the model file that will be phased in later\n";
	usage += "-Params or -P is for the parameter file\n";
	usage += "-Prefix is the prefix for the kinetics file\n";
	usage += "-Tracking is for the tracking file\n";
	usage += "-Correct is for whether or not to run RRA corrections.\n";
	usage += "\n";
	usage += "Guide to perturbation flags:\n";
	usage += "-tx Torso center of mass x coordinate\n";
	usage += "-ty Torso center of mass y coordinate\n";
	usage += "-tz Torso center of mass z coordinate\n";
	usage += "-le Lumbar extension\n";
	usage += "-lb Lumbar bending\n";
	usage += "-lr Lumbar rotation\n";
	usage += "-rx Right foot center of pressure x coordinate\n";
	usage += "-ry Right foot center of pressure y coordinate\n";
	usage += "-rz Right foot center of pressure z coordinate\n";
	usage += "-lx Left foot center of pressure x coordinate\n";
	usage += "-ly Left foot center of pressure y coordinate\n";
	usage += "-lz Left foot center of pressure z coordinate\n";
	usage += "\n";
	usage += "Example:\n";
	usage += "rra.exe -ML s26_D.dll -A s26_rra.act -P params.txt\n";
	usage += "        -Prefix s26ik -Tracking s26_rra.trk -tx -0.095 -ty 0.01\n";
	usage += "\n";
	usage += "This command runs RRA on the subject whose gait data is\n";
	usage += "in s26ik.mot, using the actuator set specified in\n";
	usage += "s26_rra.act and using the model specified in s26_D.dll.\n";
	usage += "It perturbs the torso center of mass x values by -0.095\n";
	usage += "and the torso center of mass y values by +0.01.\n";
	usage += "The tracked coordinates are specified in s26_rra.trk.\n";
	usage += "RRA corrections will be run on this data automatically.\n";
	string cushion = "\n\n";
	string cushionedUsage = cushion + usage + cushion;

	// Parse the command line arguments.
	if(argc%2==0 || argc<2)
	{
		cout << cushion;
		cout << "Incorrect number of arguments.";
		cout << cushionedUsage;
		exit(-1);
	}
	else
	{
		// We only parse the perturbation flags and the prefix.
		string flags[12] =
			{"-tx", "-ty", "-tz", "-le", "-lb", "-lr",
			 "-rx", "-ry", "-rz", "-lx", "-ly", "-lz"};
		// We ignore the flags for rdModel.
		string modelFlags[12] =
			{"-ModelLibrary", "-ML", "-Actuators", "-A", "-Contacts", "-C",
			 "-Library", "-L", "-ModelFile", "-MF", "-Params", "-P"};
		int numFlags = 12;
		int numModelFlags = 12;
		for(int i = 1; i < argc - 1; i += 2)
		{
			// If we see one of the rdModel flags, skip to the next flag.
			bool foundModelFlag = false;
			for (int m = 0; m < numModelFlags; m++)
			{
				if (argv[i] == modelFlags[m])
				{
					foundModelFlag = true;
					break;
				}
			}
			if (foundModelFlag) {continue;}
			// Convert argument to all lowercase.
			string lowercase = argv[i];
			transform(lowercase.begin(), lowercase.end(), lowercase.begin(), tolower);
			// If current argument is prefix flag, read prefix and skip to next flag.
			if (lowercase == "-prefix")
			{
				prefix = argv[i+1];
				continue;
			}
			// If current argument is tracking flag, read tracking file name and skip
			// to the next flag.
			if (lowercase == "-tracking")
			{
				trackingFileName = argv[i+1];
				continue;
			}
			// If current argument is correction flag, read the yes/no and skip to the
			// next flag.
			if (lowercase == "-correct")
			{
				string yesno = argv[i+1];
				transform(yesno.begin(), yesno.end(), yesno.begin(), tolower);
				computingCorrections = (yesno == "no") ? false : true;
				continue;
			}
			for(int j = 0; j < numFlags; j++)
			{
				if(lowercase == flags[j])
				{
					if(perturb[j] == 0.0)
					{
						if(sscanf(argv[i+1], "%lg", &perturb[j]) != 0)
						{
							// Break out of inner loop but not outer loop by
							// violating the loop invariant of the inner loop.
							j = numFlags;
						}
						else // The argument is not a valid number.
						{
							cout << cushion;
							cout << argv[i+1] << " is not a valid number.";
							cout << cushionedUsage;
							exit(-1);
						}
					}
					else
					{
						cout << cushion;
						cout << "You specified multiple nonzero perturbations";
						cout << " for the " << flags[j] << " flag.";
						cout << cushionedUsage;
						exit(-1);
					}
				}
				else if(j == numFlags - 1)
				{
					cout << cushion;
					cout << "Flag " << argv[i] << " is not a valid flag.";
					cout << cushionedUsage;
					exit(-1);
				}
			}
		}
		string flagnames[12] =
			{"Torso COM x", "Torso COM y", "Torso COM z",
			 "Lumbar extension", "Lumbar bending", "Lumbar rotation",
			 "Right COP x", "Right COP y", "Right COP z",
			 "Left COP x", "Left COP y", "Left COP z"};
		cout << "Perturbation amounts:\n";
		for (int k = 0; k < 12; k++)
		{
			if(perturb[k] > 0.0)
			{
				cout << flagnames[k] << " +" << perturb[k] << endl;
			}
			else if(perturb[k] < 0.0)
			{
				// Minus sign is already included in perturb[k] since it is
				// a negative number.
				cout << flagnames[k] << " " << perturb[k] << endl;
			}
		}
		cout << cushion;
	}
}

