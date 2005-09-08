// su_Template__Forward.cpp

#include <string>
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Tools/rdIO.h>
#include <NMBLTK/Tools/rdGCVSplineSet.h>
#include <NMBLTK/Simulation/Model/rdModelIntegrand.h>
#include <NMBLTK/Simulation/Model/rdModelIntegrandForActuators.h>
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
#include <RDI/CMC/rdCMC.h>
#include <RDI/CMC/rdHigherOrderTarget.h>
#include <RDI/CMC/rdCMC_Joint.h>
#include <RDI/CMC/rdCMC_TaskSet.h>
#include <RDI/CMC/rdActuatorForceTarget.h>
#include <RDI/CMC/rdActuatorForceTargetFast.h>
#include "su_Template_.h"
using namespace std;

int extractCoordinates(su_Template_& model, const char *reaOutputFilename);

extern "C" {

	// Pipeline include files
	#include "dynsim/src/basic.h"
	#include "dynsim/src/dp.h"
	#include "dynsim/src/structs.h"
	#include "dynsim/src/functions.h"
	//#include "dynsim/src/model_d.h"

	// Pipeline global variables
   extern dpModelStruct *sdm;

	// Functions from sdufuncs_darryl
	void computeConstrainedCoords(dpModelStruct* sdm,double* y);
}

int main(int argc,char **argv)
{
	int i;
	rdIO::SetPrecision(16);

	// REGISTER TYPES
	rdObject::RegisterType(rdControlLinear());
	rdObject::RegisterType(rdControlLinearNode());
	// TRACK OBJECTS
	rdObject::RegisterType(rdCMC_Joint());

	// INPUT----
	// Controls
	string prefix = "_Template_";
	string controlsName = prefix + "cmc.ctr";

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
	int stepInterval = 1;
	// Kinematics
	suKinematics *kin = new suKinematics(&model);
	kin->setStepInterval(stepInterval);
	model.addAnalysis(kin);
	// Actuation
	suActuation *actuation = new suActuation(&model);
	actuation->setStepInterval(stepInterval);
	model.addAnalysis(actuation);
	actuation->setOn(true);
	// Contact
	suContact *contact = new suContact(&model);
	contact->setStepInterval(stepInterval);
	model.addAnalysis(contact);
	// Body kinematics
	suBodyKinematics *bodyKin = new suBodyKinematics(&model);
	bodyKin->setStepInterval(stepInterval);
	model.addAnalysis(bodyKin);

	//========================
	// Extract GenCorrdinates, speeds, compute constraints
	// from rea.mot file and write them in files to be used by cmc
	extractCoordinates(model, "_template_rea.mot");
	//========================
	// CMC RELATED STUFF BELOW
	//||||||||||||||||||||||||
	// DESIRED KINEMATICS
	rdStorage qStore("_template_rea_q.sto");
	model.convertDegreesToRadians(&qStore);
	model.convertAnglesToQuaternions(&qStore);
	rdStorage uStore("_template_rea_u.sto");
	model.convertDegreesToRadians(&uStore);
	rdGCVSplineSet qSet(5,&qStore);
	rdGCVSplineSet uSet(5,&uStore);

	// TASK SET
	rdCMC_TaskSet taskSet("_template_.trk");
	cout<<"\n\n taskSet size = "<<taskSet.getSize()<<endl<<endl;
	taskSet.setModel(&model);
	taskSet.setParametersBasedOnName();
	taskSet.setFunctions(qSet);
	//taskSet.setFunctionsForVelocity(uSet);

	// CONTROLLER
	double targetDT = 0.010;
	rdCMC controller(&model,&taskSet);
	controller.setTargetDT(targetDT);

	// EXCITATION CONSTRAINTS
	rdControlSet controlConstraints("_template__constraints.ctr");
	controller.setControlConstraints(&controlConstraints);

	// OPTIMIZATION TARGET
	int na = model.getNA();
	// Select Target per user preference. Param 'f' or 'F' should trigger the faster, less robust one
	rdActuatorForceTargetFast fTarget(na,&controller);
	rdActuatorForceTarget target(na,&controller);
	bool useFastTarget=(argc==2 && (*argv[1]=='f' || *argv[1]=='F'));
	if ( useFastTarget)
		controller.setOptimizationTarget(&fTarget);
	else
		controller.setOptimizationTarget(&target);
	controller.setCheckTargetTime(true);

	// ACTUATOR FORCE PREDICTOR
	// Integrand
	//rdModelIntegrand cmcIntegrand(&model);
	rdModelIntegrandForActuators cmcIntegrand(&model);
	cmcIntegrand.setCoordinateTrajectories(&qSet);
	cmcIntegrand.setSpeedTrajectories(&uSet);
	rdControlSet *rootSet = cmcIntegrand.getControlSet();
	for(i=0;i<rootSet->getSize();i++) {
		rdControlLinear *control = (rdControlLinear*)rootSet->get(i);
		control->setUseSteps(true);
		control->getNodeArray().setSize(0);
	}
	VectorFunctionForActuators *predictor =
		new VectorFunctionForActuators(&cmcIntegrand);
	controller.setActuatorForcePredictor(predictor);

	// OPTIMIZATION SETTINGS
	rdFSQP *sqp = controller.getOptimizer();
	sqp->setPrintLevel(0);
	sqp->setConvergenceCriterion(1.0e-6);
	//^^^^^^^^^^^^^^^^^^^^^^^^
	// CMC RELATED STUFF ABOVE
	//========================
	
	// INITIAL AND FINAL TIMES
	//double ti = qStore.getFirstTime() + 1.0e-3;
	double ti = 0.35;
	double tf = qStore.getLastTime() - 2.0e-2;
	//double tf = ti + 0.100;
	cout<<endl<<endl<<"ti="<<ti<<" tf="<<tf<<endl<<endl;

	// INITIAL STATES
	int nq = model.getNQ();
	int nu = model.getNU();
	model.getInitialStates(&yi[0]);
	rdArray<double> q(0.0,nq),u(0.0,nu);
	qSet.evaluate(q,0,ti);
	uSet.evaluate(u,0,ti);
	for(i=0;i<nq;i++) yi[i] = q[i];
	for(i=0;i<nu;i++) yi[i+nq] = u[i];
	model.setInitialStates(&yi[0]);

	// COMPUTE INITIAL STATES----
	controller.computeInitialStates(ti,&yi[0]);
	cout<<"\n\nNew initial time = "<<ti<<".\n";
	model.setInitialStates(&yi[0]);
	cout<<"\n\nInitial States:\n";
	cout<<yi<<endl<<endl;

	// SIMULATION SETUP----
	// Manager
	rdModelIntegrand integrand(&model);
	//integrand.setControlSet(forwardControlSet);  // COMMENT OUT WHEN CMC, DON'T COMMENT OUT WHEN FORWARD
	rdManager manager(&integrand);
	manager.setSessionName("_Template_");

	// Use steps (COMMENT OUT WHEN FORWARD)
	rdControlSet *controlSet = integrand.getControlSet();
		for(i=0;i<controlSet->getSize();i++) {
		rdControlLinear *control = (rdControlLinear*)controlSet->get(i);
		control->setUseSteps(true);
	}

	// Initial and final times
	int first = 0;
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
	// critical part for tracking (COMMENT OUT WHEN FORWARD)
	integrand.setController(&controller);


	// INTEGRATE
	cout<<"\n\nIntegrating from "<<ti<<" to "<<tf<<endl;

	manager.integrate();


	// WRITE OUT CONTROLS (COMMENT OUT WHEN FORWARD)
	controlSet->print("_template_cmc.ctr");


	// RESULTS
	// Storage
	rdStorage *yStore = integrand.getStateStorage();
	rdStorage *ypStore = integrand.getPseudoStateStorage();
	rdStorage *xStore = integrand.getControlStorage();

	// Print
	double dt = -1.0;
	xStore->print("Results/_Template__controls.sto");
	yStore->print("Results/_Template__states.sto");
	rdAnalysisSet *analysisSet = model.getAnalysisSet();
	analysisSet->printResults(prefix.c_str(),"Results",dt);

	return(0);
}
//_____________________________________________________________________________
/**
 * extractCoordinates reads the rea.mot file and extract generalized coordinates 
 * generalized speeds and computes values for constraints, writes the results to 
 * files to be used by CMC. (for efficiency this may be kept as a storage rather 
 * than writing the files and reading them back later).
 */
int extractCoordinates(su_Template_& model, const char *reaOutputFilename)
{
	rdStorage fileStore(reaOutputFilename);
	int nq = model.getNQ();

	// GET COORDINATE FILE INDICES
	string qName,columnLabels;
	rdArray<int> index(-1,nq);
	columnLabels = "time";
	int i,j;
	for(i=0;i<nq;i++) {
		qName = model.getCoordinateName(i);
		columnLabels += "\t";
		columnLabels += qName;
		index[i] = fileStore.getColumnIndex(qName);
	}

	// EXTRACT COORDINATES
	double time;
	rdArray<double> data(0.0);
	rdArray<double> q(0.0,nq);
	rdStorage qStore;
	qStore.setName("_template__GeneralizedCoordinates");
	qStore.setColumnLabels(columnLabels.c_str());
	int size = fileStore.getSize();
	rdStateVector *vector;
	for(i=0;i<size;i++) {

		vector = fileStore.getStateVector(i);
		data = vector->getData();
		time = vector->getTime();

		for(j=0;j<nq;j++) {
			q[j] = 0.0;
			if(index[j]<0) continue;
			q[j] = data[index[j]];
		}

		qStore.append(time,nq,&q[0]);
	}

	// CONVERT TO RADIANS
	model.convertDegreesToRadians(&qStore);

	// COMPUTE GENERALIZED SPEEDS
	rdGCVSplineSet qSet(5,&qStore);
	rdStorage *uStore = qSet.constructStorage(1);


	// COMPUTE CONSTRAINTS
	rdArray<double> qu(0.0,nq+nq);
	int qSize = qStore.getSize();
	int uSize = uStore->getSize();
	cout<<"qSize = "<<qSize<<endl<<endl;
	cout<<"uSize = "<<uSize<<endl<<endl;
	rdStorage qCompleteStore;
	rdStorage uCompleteStore;
	for(i=0;i<size;i++) {

		qStore.getTime(i,time);
		qStore.getData(i,nq,&qu[0]);
		uStore->getData(i,nq,&qu[nq]);

		computeConstrainedCoords(sdm,&qu[0]);

		qCompleteStore.append(time,nq,&qu[0]);
		uCompleteStore.append(time,nq,&qu[nq]);
	}

	// CONVERT BACK TO DEGREES
	model.convertRadiansToDegrees(&qCompleteStore);
	model.convertRadiansToDegrees(&uCompleteStore);

	// WRITE TO FILE
	qCompleteStore.setColumnLabels(columnLabels.c_str());
	qCompleteStore.print("_template_rea_q.sto");
	uCompleteStore.setColumnLabels(columnLabels.c_str());
	uCompleteStore.print("_template_rea_u.sto");
	return 0;

}