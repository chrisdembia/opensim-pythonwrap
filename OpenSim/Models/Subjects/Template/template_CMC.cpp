// su_Template__Forward.cpp

#include <string>
#include <OpenSim/Tools/Math.h>
#include <OpenSim/Tools/IO.h>
#include <OpenSim/Tools/GCVSplineSet.h>
#include <OpenSim/Simulation/Model/ModelIntegrand.h>
#include <OpenSim/Simulation/Model/ModelIntegrandForActuators.h>
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
#include <RDI/CMC/rdCMC.h>
#include <RDI/CMC/rdHigherOrderTarget.h>
#include <RDI/CMC/rdCMC_Joint.h>
#include <RDI/CMC/rdCMC_TaskSet.h>
#include <RDI/CMC/ActuatorForceTarget.h>
#include <RDI/CMC/ActuatorForceTargetFast.h>
#include "su_Template_.h"


using namespace OpenSim;
using namespace std;

int extractCoordinates(su_Template_& model, const char *reaOutputFilename);
int recordInitialStates(double actualInitialTime ,double *states, su_Template_& model);

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
	IO::SetPrecision(16);

	// REGISTER TYPES
	Object::RegisterType(ControlLinear());
	Object::RegisterType(ControlLinearNode());
	// TRACK OBJECTS
	Object::RegisterType(rdCMC_Joint());

	// INPUT----
	// Controls
	string prefix = "_Template_";
	string controlsName = prefix + "cmc.ctr";

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
	int stepInterval = 1;
	// Kinematics
	Kinematics *kin = new Kinematics(&model);
	kin->setStepInterval(stepInterval);
	model.addAnalysis(kin);
	// Actuation
	Actuation *actuation = new Actuation(&model);
	actuation->setStepInterval(stepInterval);
	model.addAnalysis(actuation);
	actuation->setOn(true);
	// Contact
	Contact *contact = new Contact(&model);
	contact->setStepInterval(stepInterval);
	model.addAnalysis(contact);
	// Body kinematics
	BodyKinematics *bodyKin = new BodyKinematics(&model);
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
	Storage qStore("_template_rea_q.sto");
	model.convertDegreesToRadians(&qStore);
	model.convertAnglesToQuaternions(&qStore);
	Storage uStore("_template_rea_u.sto");
	model.convertDegreesToRadians(&uStore);
	GCVSplineSet qSet(5,&qStore);
	GCVSplineSet uSet(5,&uStore);

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
	ControlSet controlConstraints("_template__constraints.ctr");
	controller.setControlConstraints(&controlConstraints);

	// OPTIMIZATION TARGET
	int na = model.getNA();
	// Select Target per user preference. Param 'f' or 'F' should trigger the faster, less robust one
	ActuatorForceTargetFast fTarget(na,&controller);
	ActuatorForceTarget target(na,&controller);
	bool useFastTarget=(argc==2 && (*argv[1]=='f' || *argv[1]=='F'));
	if ( useFastTarget)
		controller.setOptimizationTarget(&fTarget);
	else
		controller.setOptimizationTarget(&target);
	controller.setCheckTargetTime(true);

	// ACTUATOR FORCE PREDICTOR
	// Integrand
	//ModelIntegrand cmcIntegrand(&model);
	ModelIntegrandForActuators cmcIntegrand(&model);
	cmcIntegrand.setCoordinateTrajectories(&qSet);
	cmcIntegrand.setSpeedTrajectories(&uSet);
	ControlSet *rootSet = cmcIntegrand.getControlSet();
	for(i=0;i<rootSet->getSize();i++) {
		ControlLinear *control = (ControlLinear*)rootSet->get(i);
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
	double ti = qStore.getFirstTime() + 1.0e-2;
	//double ti = 0.35;
	double tf = qStore.getLastTime() - 2.0e-2;
	//double tf = ti + 0.100;
	cout<<endl<<endl<<"ti="<<ti<<" tf="<<tf<<endl<<endl;

	// INITIAL STATES
	int nq = model.getNQ();
	int nu = model.getNU();
	model.getInitialStates(&yi[0]);
	Array<double> q(0.0,nq),u(0.0,nu);
	qSet.evaluate(q,0,ti);
	uSet.evaluate(u,0,ti);
	for(i=0;i<nq;i++) yi[i] = q[i];
	for(i=0;i<nu;i++) yi[i+nq] = u[i];
	model.setInitialStates(&yi[0]);

	// COMPUTE INITIAL STATES----
	controller.computeInitialStates(ti,&yi[0]);

	// Save "computed" initial time and corresponding intial states
	recordInitialStates(ti,&yi[0],model);

	cout<<"\n\nNew initial time = "<<ti<<".\n";
	model.setInitialStates(&yi[0]);
	cout<<"\n\nInitial States:\n";
	cout<<yi<<endl<<endl;

	// SIMULATION SETUP----
	// Manager
	ModelIntegrand integrand(&model);
	//integrand.setControlSet(forwaControlSet);  // COMMENT OUT WHEN CMC, DON'T COMMENT OUT WHEN FORWARD
	Manager manager(&integrand);
	manager.setSessionName("_Template_");

	// Use steps (COMMENT OUT WHEN FORWARD)
	ControlSet *controlSet = integrand.getControlSet();
		for(i=0;i<controlSet->getSize();i++) {
		ControlLinear *control = (ControlLinear*)controlSet->get(i);
		control->setUseSteps(true);
	}

	// Initial and final times
	int first = 0;
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
	// critical part for tracking (COMMENT OUT WHEN FORWARD)
	integrand.setController(&controller);


	// INTEGRATE
	cout<<"\n\nIntegrating from "<<ti<<" to "<<tf<<endl;

	manager.integrate();


	// WRITE OUT CONTROLS (COMMENT OUT WHEN FORWARD)
	controlSet->print("_template_cmc.ctr");


	// RESULTS
	// Storage
	Storage *yStore = integrand.getStateStorage();
	Storage *ypStore = integrand.getPseudoStateStorage();
	Storage *xStore = integrand.getControlStorage();

	// Print
	double dt = -1.0;
	xStore->print("Results/_Template__controls.sto");
	yStore->print("Results/_Template__states.sto");
	AnalysisSet *analysisSet = model.getAnalysisSet();
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
	Storage fileStore(reaOutputFilename);
	int nq = model.getNQ();

	// GET COORDINATE FILE INDICES
	string qName,columnLabels;
	Array<int> index(-1,nq);
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
	Array<double> data(0.0);
	Array<double> q(0.0,nq);
	Storage qStore;
	qStore.setName("_template__GeneralizedCoordinates");
	qStore.setColumnLabels(columnLabels.c_str());
	int size = fileStore.getSize();
	StateVector *vector;
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
	GCVSplineSet qSet(5,&qStore);
	Storage *uStore = qSet.constructStorage(1);


	// COMPUTE CONSTRAINTS
	Array<double> qu(0.0,nq+nq);
	int qSize = qStore.getSize();
	int uSize = uStore->getSize();
	cout<<"qSize = "<<qSize<<endl<<endl;
	cout<<"uSize = "<<uSize<<endl<<endl;
	Storage qCompleteStore;
	Storage uCompleteStore;
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

//_____________________________________________________________________________
/**
 * recordInitialStates records initial states after muscles reach equlibrium state
 * saves all states along with the time associated with them to 
 * reproduce exact initialization when running forward simulation.
 */
int recordInitialStates(double actualInitialTime ,double *states, su_Template_& model)
{
	Storage *fileStore = new Storage();
	int ny = model.getNY();
	string columnLabels = "time";
	StateVector initialStates(actualInitialTime, ny, states);
	int i;
	for(i=0;i<ny;i++) {
		string qName = model.getStateName(i);
		columnLabels += "\t";
		columnLabels += qName;
	}
	fileStore->setColumnLabels(columnLabels.c_str());
	fileStore->append(initialStates);
	fileStore->print("_template__initialStates.sto");
	return 0;
}