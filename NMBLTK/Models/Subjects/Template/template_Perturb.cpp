// su_Template_Perturb.cpp

#include <string>
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Tools/rdIO.h>
#include <NMBLTK/Tools/rdGCVSpline.h>
#include <NMBLTK/Tools/rd1to3VectorGCVSpline.h>
#include <NMBLTK/Simulation/Manager/rdManager.h>
#include <NMBLTK/Simulation/Control/rdControlLinear.h>
#include <NMBLTK/Simulation/Control/rdControlSet.h>
#include <NMBLTK/Simulation/TestSuite/rdModelTestSuite.h>
#include <NMBLTK/Simulation/Model/rdDerivCallbackSet.h>
#include <NMBLTK/Analyses/suKinematics.h>
#include <NMBLTK/Analyses/suPointKinematics.h>
#include <NMBLTK/Analyses/suActuation.h>
#include <NMBLTK/Analyses/suContact.h>
#include <NMBLTK/Analyses/suLinearSpring.h>
#include <NMBLTK/Analyses/suActuatorGeneralizedForces.h>
#include <NMBLTK/Analyses/suGeneralizedForces.h>
#include <NMBLTK/Analyses/suBodyKinematics.h>
#include <NMBLTK/Analyses/suActuatorPerturbationIndependent.h>
#include <NMBLTK/Simulation/Model/rdAnalysisSet.h>
#include "su_Template_.h"

using namespace std;


void engageCorrectiveSprings(rdModel *aModel);


static int calcnr = 8;
static int calcnl = 14;
static double R0[] = {-0.15, -0.02,  0.04 };
static double R1[] = {-0.15, -0.02, -0.04 };
static double R2[] = { 0.10, -0.02,  0.04 };
static double R3[] = { 0.10, -0.02, -0.04 };
static double L0[] = {-0.15, -0.02, -0.04 };
static double L1[] = {-0.15, -0.02,  0.04 };
static double L2[] = { 0.10, -0.02, -0.04 };
static double L3[] = { 0.10, -0.02,  0.04 };


int main(int argc,char *argv[])
{
	int i;
	rdIO::SetPrecision(16);

	// PARSE COMMAND LINE
	string prefix;
	bool pointKinOn = false;
	if((argc<2)||(argc>3)) {
		cout<<"\n\nUsage:  su_Template_Perturb.exe baseName [-pointKinOn]\n\n";
		exit(-1);
	} else if(argc==2) {
		prefix = argv[1];
	} else {
		prefix = argv[1];
		string flag = argv[2];
		if(flag=="-pointKinOn") {
			pointKinOn = true;
			cout<<"\n\nRecording point kinematics of feet...\n\n";
		} else {
			cout<<"\n\nUnrecognized flag  "<<flag;
			exit(-1);
		}
	}
	
	// REGISTER TYPES
	rdObject::RegisterType(rdControlLinear());
	rdObject::RegisterType(rdControlLinearNode());

	// INPUT----
	// MODEL----
	std::string parmFile="./params.txt";
	su_Template_ model(parmFile);

	// Test the model
	//rdModelTestSuite testSuite;
	//testSuite.Test(&model);
	//exit(0);

	// Controls
	string controlsName = prefix + ".ctr";
	cout<<endl<<endl<<"Loading controls from "<<controlsName<<"..."<<endl;
	rdControlSet controlSet(controlsName);
	cout<<"Found "<<controlSet.getSize()<<" controls."<<endl;


	// Initial states
	rdArray<double> yi(0.0,model.getNY());
	model.getInitialStates(&yi[0]);
	int ny = model.getNY();
	cout<<"\nInitial States:"<<endl;
	for(i=0;i<ny;i++) {
		cout<<model.getStateName(i)<<"["<<i<<"]= "<<yi[i]<<endl;
	}

	// ANALYSES----
	// Kinematics
	suKinematics *kin = new suKinematics(&model);
	model.addAnalysis(kin);
	kin->getPositionStorage()->setWriteSIMMHeader(true);
	// Actuation
	suActuation *actuation = new suActuation(&model);
	model.addAnalysis(actuation);
	actuation->setOn(true);
	// Contact
	suContact *contact = new suContact(&model);
	model.addAnalysis(contact);
	// Point Kinematics
	// R0
	suPointKinematics *kinR0 = new suPointKinematics(&model);
	kinR0->setBody(calcnr);
	kinR0->setPoint(R0);
	kinR0->setOn(pointKinOn);
	model.addAnalysis(kinR0);
	// R1
	suPointKinematics *kinR1 = new suPointKinematics(&model);
	kinR1->setBody(calcnr);
	kinR1->setPoint(R1);
	kinR1->setOn(pointKinOn);
	model.addAnalysis(kinR1);
	// R2
	suPointKinematics *kinR2 = new suPointKinematics(&model);
	kinR2->setBody(calcnr);
	kinR2->setPoint(R2);
	kinR2->setOn(pointKinOn);
	model.addAnalysis(kinR2);
	// R3
	suPointKinematics *kinR3 = new suPointKinematics(&model);
	kinR3->setBody(calcnr);
	kinR3->setPoint(R3);
	kinR3->setOn(pointKinOn);
	model.addAnalysis(kinR3);
	// L0
	suPointKinematics *kinL0 = new suPointKinematics(&model);
	kinL0->setBody(calcnl);
	kinL0->setPoint(L0);
	kinL0->setOn(pointKinOn);
	model.addAnalysis(kinL0);
	// L1
	suPointKinematics *kinL1 = new suPointKinematics(&model);
	kinL1->setBody(calcnl);
	kinL1->setPoint(L1);
	kinL1->setOn(pointKinOn);
	model.addAnalysis(kinL1);
	// L2
	suPointKinematics *kinL2 = new suPointKinematics(&model);
	kinL2->setBody(calcnl);
	kinL2->setPoint(L2);
	kinL2->setOn(pointKinOn);
	model.addAnalysis(kinL2);
	// L3
	suPointKinematics *kinL3 = new suPointKinematics(&model);
	kinL3->setBody(calcnl);
	kinL3->setPoint(L3);
	kinL3->setOn(pointKinOn);
	model.addAnalysis(kinL3);


	// CORRECTIVE SPRINGS
	if(!pointKinOn) {
		engageCorrectiveSprings(&model);
	}

	
	// SIMULATION SETUP----
	// Manager
	rdModelIntegrand integrand(&model);
	integrand.setControlSet(controlSet);

	rdManager manager(&integrand);
	manager.setSessionName("_template_");

	// Initial and final times
	int first = 0;
	rdControlLinear *control = (rdControlLinear*)controlSet.get(first);
	double ti = control->getFirstTime();
	double tf = control->getLastTime();
	cout<<endl<<endl<<"ti="<<ti<<" tf="<<tf<<endl<<endl;
	manager.setInitialTime(ti);
	manager.setFinalTime(tf);

	// Integrator settings
	int maxSteps = 4000;
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


	// PERTURBATION
	if(!pointKinOn) {

		// CREATE AND ADD PERTURBATION CALLBACK
		suActuatorPerturbationIndependent *perturbation = 
			new suActuatorPerturbationIndependent(&model);
		model.addDerivCallback(perturbation);


		// INTEGRATE TO RECORD UNPERTURBED MUSCLE FORCES 
		cout<<"\nUnperturbed integration 2 to record forces and kinematics\n";
		perturbation->setRecordUnperturbedForces(true);
		integ->setUseSpecifiedDT(true);
		manager.integrate();


		// INTEGRATE WITH PERTURBATION
		cout<<"\nPerturbed integration\n";
		double tip = ti + (tf-ti)/4.0;
		tip = 0.80;
		double tfp = tip + 0.030;
		perturbation->setStartTime(tip); 
		perturbation->setEndTime(tfp); 
		// Reset the internal storages (required for looping)
		perturbation->reset(); 
		// Tell callback to change force, rather than record it
		perturbation->setRecordUnperturbedForces(false); 
		// Set the muscle of interest
		perturbation->setActuator( model.getActuatorIndex("vas_med_r") ); 
		// Tell it what kind of perturbation (scale, delta, constant) and 
		// how much to change the force (df)
		double df = 1.0;
		perturbation->setPerturbation(suActuatorPerturbationIndependent::DELTA,+df);
		perturbation->setOn(true);
		// Check start and end times for perturbation
		printf("perturbation start time: %.6f\n",perturbation->getStartTime());
		printf("perturbation end time: %.6f\n",perturbation->getEndTime());
		manager.integrate();

	}


	// RESULTS
	// Storage
	rdStorage *yStore = integrand.getStateStorage();
	rdStorage *ypStore = integrand.getPseudoStateStorage();
	rdStorage *xStore = integrand.getControlStorage();

	// Print
	double dt = -1.0;
	xStore->print("ResultsPerturbed/_template__controls.sto");
	yStore->print("ResultsPerturbed/_template__states.sto");
	rdAnalysisSet *analysisSet = model.getAnalysisSet();
	for(i=0; i< analysisSet->getSize(); i++)
		analysisSet->getAnalysis(i)->printResults((char*)prefix.c_str(),"ResultsPerturbed",dt);

	
	// Unperturbed point kinematics
	if(pointKinOn) {
		kinR0->printResults("_template__R0","ResultsPerturbed");
		kinR1->printResults("_template__R1","ResultsPerturbed");
		kinR2->printResults("_template__R2","ResultsPerturbed");
		kinR3->printResults("_template__R3","ResultsPerturbed");
		kinL0->printResults("_template__L0","ResultsPerturbed");
		kinL1->printResults("_template__L1","ResultsPerturbed");
		kinL2->printResults("_template__L2","ResultsPerturbed");
		kinL3->printResults("_template__L3","ResultsPerturbed");
	}
	// Corrective spring forces
	rdDerivCallbackSet *derivSet = model.getDerivCallbackSet();
	rdObject *obj;
	suLinearSpring *spr;
	char fileName[rdObject::NAME_LENGTH];
	for(i=0;i<derivSet->getSize();i++) {
		obj = derivSet->get(i);
		if(obj->getType() == "suLinearSpring") {
			sprintf(fileName,"_template__%d",i);
			spr = (suLinearSpring*)obj;
			spr->printResults(fileName,".");
		}
	}
	
	return(0);
}


//_____________________________________________________________________________
/**
 * Create and add some corrective springs to the model so that some
 * perturbations can be performed.
 */
void engageCorrectiveSprings(rdModel *aModel)
{
	int i,n;
	double *t,*x,*y,*z;
	double k[] = { 10000.0, 100000.0, 10000.0 };
	double b[] = { 20.0, 200.0, 20.0 };

	cout<<"\n\nEngaging corrective springs...\n\n";

	// Normalization factors for spring coefficients
	rdStorage *storeKinetic = new rdStorage("./_template_cmc_grf.mot");
	int grfRYIndex,grfLYIndex;
	bool notFound;
	char *tok;
	const char *colLabels = storeKinetic->getColumnLabels();
	char *labels = new char[strlen(colLabels) + 1];
	strcpy(labels,colLabels);
	for(i=0,notFound=true,tok=strtok(labels," \t");notFound;i++,tok=strtok(NULL," \t")) {
		if(tok==NULL) break;
		if(strcmp(tok,"calcn_r_force_vy")==0) {
			notFound = false;
			grfRYIndex = i-1;
			break;
		}
	}
	if(notFound) {
		cout<<endl<<endl<<"Could not find calcn_r_force_vy"<<endl<<endl;
		exit(-1);
	}
	strcpy(labels,colLabels);
	for(i=0,notFound=true,tok=strtok(labels," \t");notFound;i++,tok=strtok(NULL," \t")) {
		if(tok==NULL) break;
		if(strcmp(tok,"calcn_l_force_vy")==0) {
			notFound = false;
			grfLYIndex = i-1;
			break;
		}
	}
	if(notFound) {
		cout<<endl<<endl<<"Could not find calcn_l_force_vy"<<endl<<endl;
		exit(-1);
	}
	cout<<endl<<endl<<"grfRYIndex="<<grfRYIndex<<"   "<<"grfLYIndex="<<grfLYIndex<<endl<<endl;

	int size = storeKinetic->getSize();
	double *grfTime=NULL,*grfRY=NULL,*grfLY=NULL;
	n = storeKinetic->getTimeColumn(grfTime);
	n = storeKinetic->getDataColumn(grfRYIndex,grfRY);
	n = storeKinetic->getDataColumn(grfLYIndex,grfLY);
	cout<<"\n\nExperimental Vertical Ground Reactions...\n";
	for(i=0;i<n;i++) {
		cout<<grfTime[i]<<" "<<grfRY[i]<<" "<<grfLY[i]<<endl;
	}
	cout<<endl<<endl;

	rdArray<double> grfTY(0.0,n),scaleR(0.0,n),scaleL(0.0,n);
	for(i=0;i<n;i++) {
		grfTY[i] = fabs(grfRY[i]) + fabs(grfLY[i]);
		if(grfTY[i]<rdMath::SMALL) grfTY[i]=rdMath::SMALL;
		scaleR[i] = fabs(grfRY[i]/grfTY[i]);
		scaleL[i] = fabs(grfLY[i]/grfTY[i]);
	}
	cout<<endl<<endl<<"scaleR = "<<scaleR<<endl;
	cout<<endl<<endl<<"scaleL = "<<scaleL<<endl<<endl;
	rdGCVSpline *scaleRSpline = new rdGCVSpline(3,n,grfTime,&scaleR[0]);
	rdGCVSpline *scaleLSpline = new rdGCVSpline(3,n,grfTime,&scaleL[0]);

	// R0
	rdStorage storeR0("./ResultsPerturbed/_template__R0_PointKinematics__pos.sto");
	storeR0.pad(10);
	t = x = y = z = NULL;
	n = storeR0.getTimeColumn(t);
	storeR0.getDataColumn(0,x);
	storeR0.getDataColumn(1,y);
	storeR0.getDataColumn(2,z);
	rd1to3VectorGCVSpline *vectorR0 = new rd1to3VectorGCVSpline(3,n,t,x,y,z);
	rdArray<double> result(0.0, 3);
	vectorR0->evaluate(&t[0], &result[0]);
	cout<<"\n\nvector result = "<<result<<endl<<endl;
	delete[] t; delete[] x;  delete[] y;  delete[] z;
	// VR0
	rdStorage storeVR0("./ResultsPerturbed/_template__R0_PointKinematics__vel.sto");
	storeVR0.pad(10);
	t = x = y = z = NULL;
	n = storeVR0.getTimeColumn(t);
	storeVR0.getDataColumn(0,x);
	storeVR0.getDataColumn(1,y);
	storeVR0.getDataColumn(2,z);
	rd1to3VectorGCVSpline *vectorVR0 = new rd1to3VectorGCVSpline(3,n,t,x,y,z);
	delete[] t; delete[] x;  delete[] y;  delete[] z;
	// Spring R0
	suLinearSpring *sprR0 = new suLinearSpring(aModel,calcnr,R0,vectorR0,vectorVR0,k,b);
	sprR0->setScaleFunction(scaleRSpline);
	sprR0->setOn(true);
	//sprR0->setInputPositionsInLocalFrame(false);
	aModel->addDerivCallback(sprR0);

	// R1
	rdStorage storeR1("./ResultsPerturbed/_template__R1_PointKinematics__pos.sto");
	storeR1.pad(10);
	t = x = y = z = NULL;
	n = storeR1.getTimeColumn(t);
	storeR1.getDataColumn(0,x);
	storeR1.getDataColumn(1,y);
	storeR1.getDataColumn(2,z);
	rd1to3VectorGCVSpline *vectorR1 = new rd1to3VectorGCVSpline(3,n,t,x,y,z);
	delete[] t; delete[] x;  delete[] y;  delete[] z;
	// VR1
	rdStorage storeVR1("./ResultsPerturbed/_template__R1_PointKinematics__vel.sto");
	storeVR1.pad(10);
	t = x = y = z = NULL;
	n = storeVR1.getTimeColumn(t);
	storeVR1.getDataColumn(0,x);
	storeVR1.getDataColumn(1,y);
	storeVR1.getDataColumn(2,z);
	rd1to3VectorGCVSpline *vectorVR1 = new rd1to3VectorGCVSpline(3,n,t,x,y,z);
	delete[] t; delete[] x;  delete[] y;  delete[] z;
	// Spring R1
	suLinearSpring *sprR1 = new suLinearSpring(aModel,calcnr,R1,vectorR1,vectorVR1,k,b);
	sprR1->setScaleFunction(scaleRSpline);
	sprR1->setOn(true);
	aModel->addDerivCallback(sprR1);

	// R2
	rdStorage storeR2("./ResultsPerturbed/_template__R2_PointKinematics__pos.sto");
	storeR2.pad(10);
	t = x = y = z = NULL;
	n = storeR2.getTimeColumn(t);
	storeR2.getDataColumn(0,x);
	storeR2.getDataColumn(1,y);
	storeR2.getDataColumn(2,z);
	rd1to3VectorGCVSpline *vectorR2 = new rd1to3VectorGCVSpline(3,n,t,x,y,z);
	delete[] t; delete[] x;  delete[] y;  delete[] z;
	// VR2
	rdStorage storeVR2("./ResultsPerturbed/_template__R2_PointKinematics__vel.sto");
	storeVR2.pad(10);
	t = x = y = z = NULL;
	n = storeVR2.getTimeColumn(t);
	storeVR2.getDataColumn(0,x);
	storeVR2.getDataColumn(1,y);
	storeVR2.getDataColumn(2,z);
	rd1to3VectorGCVSpline *vectorVR2 = new rd1to3VectorGCVSpline(3,n,t,x,y,z);
	delete[] t; delete[] x;  delete[] y;  delete[] z;
	// Spring R2
	suLinearSpring *sprR2 = new suLinearSpring(aModel,calcnr,R2,vectorR2,vectorVR2,k,b);
	sprR2->setScaleFunction(scaleRSpline);
	sprR2->setOn(true);
	aModel->addDerivCallback(sprR2);

	// R3
	rdStorage storeR3("./ResultsPerturbed/_template__R3_PointKinematics__pos.sto");
	storeR3.pad(10);
	t = x = y = z = NULL;
	n = storeR3.getTimeColumn(t);
	storeR3.getDataColumn(0,x);
	storeR3.getDataColumn(1,y);
	storeR3.getDataColumn(2,z);
	rd1to3VectorGCVSpline *vectorR3 = new rd1to3VectorGCVSpline(3,n,t,x,y,z);
	delete[] t; delete[] x;  delete[] y;  delete[] z;
	// VR3
	rdStorage storeVR3("./ResultsPerturbed/_template__R3_PointKinematics__vel.sto");
	storeVR3.pad(10);
	t = x = y = z = NULL;
	n = storeVR3.getTimeColumn(t);
	storeVR3.getDataColumn(0,x);
	storeVR3.getDataColumn(1,y);
	storeVR3.getDataColumn(2,z);
	rd1to3VectorGCVSpline *vectorVR3 = new rd1to3VectorGCVSpline(3,n,t,x,y,z);
	delete[] t; delete[] x;  delete[] y;  delete[] z;
	// Spring R3
	suLinearSpring *sprR3 = new suLinearSpring(aModel,calcnr,R3,vectorR3,vectorVR3,k,b);
	sprR3->setScaleFunction(scaleRSpline);
	sprR3->setOn(true);
	aModel->addDerivCallback(sprR3);

	// L0
	rdStorage storeL0("./ResultsPerturbed/_template__L0_PointKinematics__pos.sto");
	storeL0.pad(10);
	t = x = y = z = NULL;
	n = storeL0.getTimeColumn(t);
	storeL0.getDataColumn(0,x);
	storeL0.getDataColumn(1,y);
	storeL0.getDataColumn(2,z);
	rd1to3VectorGCVSpline *vectorL0 = new rd1to3VectorGCVSpline(3,n,t,x,y,z);
	delete[] t; delete[] x;  delete[] y;  delete[] z;
	// VL0
	rdStorage storeVL0("./ResultsPerturbed/_template__L0_PointKinematics__vel.sto");
	storeVL0.pad(10);
	t = x = y = z = NULL;
	n = storeVL0.getTimeColumn(t);
	storeVL0.getDataColumn(0,x);
	storeVL0.getDataColumn(1,y);
	storeVL0.getDataColumn(2,z);
	rd1to3VectorGCVSpline *vectorVL0 = new rd1to3VectorGCVSpline(3,n,t,x,y,z);
	delete[] t; delete[] x;  delete[] y;  delete[] z;
	// Spring L0
	suLinearSpring *sprL0 = new suLinearSpring(aModel,calcnl,L0,vectorL0,vectorVL0,k,b);
	sprL0->setScaleFunction(scaleLSpline);
	sprL0->setOn(true);
	aModel->addDerivCallback(sprL0);

	// L1
	rdStorage storeL1("./ResultsPerturbed/_template__L1_PointKinematics__pos.sto");
	storeL1.pad(10);
	t = x = y = z = NULL;
	n = storeL1.getTimeColumn(t);
	storeL1.getDataColumn(0,x);
	storeL1.getDataColumn(1,y);
	storeL1.getDataColumn(2,z);
	rd1to3VectorGCVSpline *vectorL1 = new rd1to3VectorGCVSpline(3,n,t,x,y,z);
	delete[] t; delete[] x;  delete[] y;  delete[] z;
	// VL1
	rdStorage storeVL1("./ResultsPerturbed/_template__L1_PointKinematics__vel.sto");
	storeVL1.pad(10);
	t = x = y = z = NULL;
	n = storeVL1.getTimeColumn(t);
	storeVL1.getDataColumn(0,x);
	storeVL1.getDataColumn(1,y);
	storeVL1.getDataColumn(2,z);
	rd1to3VectorGCVSpline *vectorVL1 = new rd1to3VectorGCVSpline(3,n,t,x,y,z);
	delete[] t; delete[] x;  delete[] y;  delete[] z;
	// Spring L1
	suLinearSpring *sprL1 = new suLinearSpring(aModel,calcnl,L1,vectorL1,vectorVL1,k,b);
	sprL1->setScaleFunction(scaleLSpline);
	sprL1->setOn(true);
	aModel->addDerivCallback(sprL1);

	// L2
	rdStorage storeL2("./ResultsPerturbed/_template__L2_PointKinematics__pos.sto");
	storeL2.pad(10);
	t = x = y = z = NULL;
	n = storeL2.getTimeColumn(t);
	storeL2.getDataColumn(0,x);
	storeL2.getDataColumn(1,y);
	storeL2.getDataColumn(2,z);
	rd1to3VectorGCVSpline *vectorL2 = new rd1to3VectorGCVSpline(3,n,t,x,y,z);
	delete[] t; delete[] x;  delete[] y;  delete[] z;
	// VL2
	rdStorage storeVL2("./ResultsPerturbed/_template__L2_PointKinematics__vel.sto");
	storeVL2.pad(10);
	t = x = y = z = NULL;
	n = storeVL2.getTimeColumn(t);
	storeVL2.getDataColumn(0,x);
	storeVL2.getDataColumn(1,y);
	storeVL2.getDataColumn(2,z);
	rd1to3VectorGCVSpline *vectorVL2 = new rd1to3VectorGCVSpline(3,n,t,x,y,z);
	delete[] t; delete[] x;  delete[] y;  delete[] z;
	// Spring L2
	suLinearSpring *sprL2 = new suLinearSpring(aModel,calcnl,L2,vectorL2,vectorVL2,k,b);
	sprL2->setScaleFunction(scaleLSpline);
	sprL2->setOn(true);
	aModel->addDerivCallback(sprL2);

	// L3
	rdStorage storeL3("./ResultsPerturbed/_template__L3_PointKinematics__pos.sto");
	storeL3.pad(10);
	t = x = y = z = NULL;
	n = storeL3.getTimeColumn(t);
	storeL3.getDataColumn(0,x);
	storeL3.getDataColumn(1,y);
	storeL3.getDataColumn(2,z);
	rd1to3VectorGCVSpline *vectorL3 = new rd1to3VectorGCVSpline(3,n,t,x,y,z);
	delete[] t; delete[] x;  delete[] y;  delete[] z;
	// VL3
	rdStorage storeVL3("./ResultsPerturbed/_template__L3_PointKinematics__vel.sto");
	storeVL3.pad(10);
	t = x = y = z = NULL;
	n = storeVL3.getTimeColumn(t);
	storeVL3.getDataColumn(0,x);
	storeVL3.getDataColumn(1,y);
	storeVL3.getDataColumn(2,z);
	rd1to3VectorGCVSpline *vectorVL3 = new rd1to3VectorGCVSpline(3,n,t,x,y,z);
	delete[] t; delete[] x;  delete[] y;  delete[] z;
	// Spring L3
	suLinearSpring *sprL3 = new suLinearSpring(aModel,calcnl,L3,vectorL3,vectorVL3,k,b);
	sprL3->setScaleFunction(scaleLSpline);
	sprL3->setOn(true);
	aModel->addDerivCallback(sprL3);
}