// PerturbationTool.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=============================================================================
// INCLUDES
//=============================================================================
#include "PerturbationTool.h"
#include "ForwardTool.h"
#include <time.h>
#include <OpenSim/Common/IO.h>
#include <OpenSim/Common/VectorGCVSplineR1R3.h>
#include <OpenSim/Simulation/Model/Model.h>
#include <OpenSim/Simulation/Model/AbstractDynamicsEngine.h>
#include <OpenSim/Simulation/Model/ActuatorSet.h>
#include <OpenSim/Simulation/Model/BodySet.h>
#include <OpenSim/Simulation/Model/DerivCallbackSet.h>
#include <OpenSim/Simulation/Model/AnalysisSet.h>
#include <OpenSim/Simulation/Control/ControlLinear.h>
#include <OpenSim/Simulation/Control/ControlSet.h>
#include <OpenSim/Analyses/Kinematics.h>
#include <OpenSim/Analyses/PointKinematics.h>
#include <OpenSim/Analyses/BodyKinematics.h>
#include <OpenSim/Analyses/Actuation.h>
#include <OpenSim/Analyses/Contact.h>
#include <OpenSim/Actuators/LinearSpring.h>
#include <OpenSim/Actuators/TorsionalSpring.h>
#include <OpenSim/Analyses/ActuatorPerturbationIndependent.h>
#include <OpenSim/Actuators/ForceApplier.h>



using namespace OpenSim;
using namespace std;


//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
PerturbationTool::~PerturbationTool()
{
}
//_____________________________________________________________________________
/**
 * Default constructor.
 */
PerturbationTool::PerturbationTool() :
	_pertWindow(_pertWindowProp.getValueDbl()),
	_pertIncrement(_pertIncrementProp.getValueDbl()),
	_pertDF(_pertDFProp.getValueDbl()),
	_actuatorsToPerturb(_actuatorsToPerturbProp.getValueStrArray()),
	_perturbGravity(_perturbGravityProp.getValueBool())
{
	setType("PerturbationTool");
	setNull();
}
//_____________________________________________________________________________
/**
 * Construct from file.
 *
 * The object is constructed from the root element of the XML document.
 * The type of object is the tag name of the XML root element.
 *
 * @param aFileName File name of the document.
 */
PerturbationTool::PerturbationTool(const string &aFileName):
	ForwardTool(aFileName, false),
	_pertWindow(_pertWindowProp.getValueDbl()),
	_pertIncrement(_pertIncrementProp.getValueDbl()),
	_pertDF(_pertDFProp.getValueDbl()),
	_actuatorsToPerturb(_actuatorsToPerturbProp.getValueStrArray()),
	_perturbGravity(_perturbGravityProp.getValueBool())
{
	setType("PerturbationTool");
	setNull();
	updateFromXMLNode();
	loadModel(aFileName);
}
//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * Copy constructors for all Tools only copy the non-XML variable
 * members of the object; that is, the object's DOMnode and XMLDocument
 * are not copied but set to NULL.  The reason for this is that for the
 * object and all its derived classes to establish the correct connection
 * to the XML document nodes, the the object would need to reconstruct based
 * on the XML document not the values of the object's member variables.
 *
 * There are three proper ways to generate an XML document for an Tool:
 *
 * 1) Construction based on XML file (@see Tool(const char *aFileName)).
 * In this case, the XML document is created by parsing the XML file.
 *
 * 2) Construction by Tool(const XMLDocument *aDocument).
 * This constructor explictly requests construction based on an
 * XML document.  In this way the proper connection between an object's node
 * and the corresponding node within the XML document is established.
 * This constructor is a copy constructor of sorts because all essential
 * Tool member variables should be held within the XML document.
 * The advantage of this style of construction is that nodes
 * within the XML document, such as comments that may not have any
 * associated Tool member variable, are preserved.
 *
 * 3) A call to generateXMLDocument().
 * This method generates an XML document for the Tool from scratch.
 * Only the essential document nodes are created (that is, nodes that
 * correspond directly to member variables.).
 *
 * @param aTool Object to be copied.
 * @see Tool(const XMLDocument *aDocument)
 * @see Tool(const char *aFileName)
 * @see generateXMLDocument()
 */
PerturbationTool::
PerturbationTool(const PerturbationTool &aTool):
	ForwardTool(aTool),
	_pertWindow(_pertWindowProp.getValueDbl()),
	_pertIncrement(_pertIncrementProp.getValueDbl()),
	_pertDF(_pertDFProp.getValueDbl()),
	_actuatorsToPerturb(_actuatorsToPerturbProp.getValueStrArray()),
	_perturbGravity(_perturbGravityProp.getValueBool())
{
	setNull();
	*this = aTool;
}

//_____________________________________________________________________________
/**
 * Virtual copy constructor.
 */
Object* PerturbationTool::
copy() const
{
	PerturbationTool *object = new PerturbationTool(*this);
	return(object);
}
//_____________________________________________________________________________
/**
 * Set all member variables to their null or default values.
 */
void PerturbationTool::
setNull()
{
	setupProperties();

	_actuatorsToPerturb.setSize(1);
	_actuatorsToPerturb[0] = "all";
	_perturbGravity = true;
}
//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void PerturbationTool::setupProperties()
{
	string comment;

	// PERTURBATION PARAMETERS
	comment = "Time over which the model states are integrated following a perturbation. "
				 "To allow reaction forces to adjust to adjust to the perturbation, the recommended "
				 "window is from about 0.020 seconds to about 0.040 seconds, although it may differ "
				 "from model to model.";
	_pertWindowProp.setComment(comment);
	_pertWindowProp.setName("perturbation_time_window");
	_propertySet.append( &_pertWindowProp );

	comment = "Time increment between perturbation windows.  This can be smaller than "
				 "the perturbation time window size (e.g., 0.010 sec).";
	_pertIncrementProp.setComment(comment);
	_pertIncrementProp.setName("perturbation_time_increment");
	_propertySet.append( &_pertIncrementProp );

	comment = "Magnitude of perturbation. Perturbation results should be fairly insensitive to "
				 "the perturbation size.  Values between 0.10N and 10N should be fine.";
	_pertDFProp.setComment(comment);
	_pertDFProp.setName("perturbation_size");
	_propertySet.append( &_pertDFProp);

	_actuatorsToPerturbProp.setComment("List of actuator names to be perturbed (for which induced acceleration will be computed).  "
												  "Use 'all' to perturb all actuators.");
	_actuatorsToPerturbProp.setName("perturbed_actuators");
	_propertySet.append( &_actuatorsToPerturbProp );

	_perturbGravityProp.setComment("Whether or not to compute induced accelerations due to gravity perturbation.");
	_perturbGravityProp.setName("perturb_gravity");
	_propertySet.append( &_perturbGravityProp );
}



//=============================================================================
// OPERATORS
//=============================================================================
//_____________________________________________________________________________
/**
 * Assignment operator.
 *
 * @return Reference to this object.
 */
PerturbationTool& PerturbationTool::
operator=(const PerturbationTool &aTool)
{
	// BASE CLASS
	AbstractTool::operator=(aTool);

	// MEMEBER VARIABLES

	return(*this);
}

//=============================================================================
// GET AND SET
//=============================================================================


//=============================================================================
// RUN
//=============================================================================
//_____________________________________________________________________________
/**
 * Run the investigation.
 */
bool PerturbationTool::run()
{
	cout<<"Running investigation "<<getName()<<".\n";

	// CHECK FOR A MODEL
	if(_model==NULL) {
		string msg = "ERROR- A model has not been set.";
		cout<<endl<<msg<<endl;
		throw(Exception(msg,__FILE__,__LINE__));
	}

	// SET OUTPUT PRECISION
	IO::SetPrecision(_outputPrecision);

	// Do the maneuver to change then restore working directory 
	// so that the parsing code behaves properly if called from a different directory.
	string saveWorkingDirectory = IO::getCwd();
	string directoryOfSetupFile = IO::getParentDirectory(getDocumentFileName());
	IO::chDir(directoryOfSetupFile);

	// Gather actuators to perturb
	ActuatorSet *as = _model->getActuatorSet();
	ArrayPtrs<AbstractActuator> actuators;
	Array<int> mapPerturbedActuatorsToAllActuators;
	actuators.setMemoryOwner(false);
	actuators.setSize(_actuatorsToPerturb.getSize());
	for(int i=0; i<_actuatorsToPerturb.getSize(); i++) {
		if(_actuatorsToPerturb[i] == "all") {
			actuators.setSize(as->getSize());
			for(int j=0;j<as->getSize();j++) {
				actuators.set(j,as->get(j));
				mapPerturbedActuatorsToAllActuators.append(j);
			}
			break;
		}
		int index = as->getIndex(_actuatorsToPerturb[i]);
		if(index<0) throw Exception("PerturbationTool: ERR- Could not find actuator '"+_actuatorsToPerturb[i]+
										    "' (listed in "+_actuatorsToPerturbProp.getName()+") in model's actuator set.",__FILE__,__LINE__);
		actuators.set(i,as->get(index));
		mapPerturbedActuatorsToAllActuators.append(index);
	}

	if(_actuatorsToPerturb.getSize() == 0 && !_perturbGravity)
		//throw Exception("PerturbationTool: ERR- Nothing to perturb (no actuators selected and gravity perturbation disabled).",__FILE__,__LINE__);
		cout << "PerturbationTool: WARNING- Nothing will be perturbed (no actuators to perturb and gravity perturbation is off)" << endl;

	// GROUND REACTION FORCES
	ForceApplier *rightGRFApp, *leftGRFApp;
	ForwardTool::initializeExternalLoads(_model,_externalLoadsFileName,_externalLoadsModelKinematicsFileName,
		_externalLoadsBody1,_externalLoadsBody2,_lowpassCutoffFrequencyForLoadKinematics,&rightGRFApp,&leftGRFApp);

	// CORRECTIVE SPRINGS
	Storage qStore,uStore;
	_model->getDynamicsEngine().extractConfiguration(*_yStore,qStore,uStore);
	AbstractBody *body1 = _model->getDynamicsEngine().getBodySet()->get(_externalLoadsBody1);
	AbstractBody *body2 = _model->getDynamicsEngine().getBodySet()->get(_externalLoadsBody2);
	// Body1 Linear
	if(_rLinSpringOn) {
		_rLin = addLinearCorrectiveSpring(qStore,uStore,*rightGRFApp);
	}
	// Body1 Torsional
	if(_rTorSpringOn) {
		double tauOn = _tauRightStartProp.getUseDefault() ? _tau : _tauRightStart;
		double tauOff = _tauRightEndProp.getUseDefault() ? _tau : _tauRightEnd;
		_rTor = addTorsionalCorrectiveSpring(qStore,uStore,body1,tauOn,_rFootFlat,tauOff,_rHeelOff);
	}
	// Body2 Linear
	if(_lLinSpringOn) {
		_lLin = addLinearCorrectiveSpring(qStore,uStore,*leftGRFApp);
	}
	// Body2 Torsional
	if(_lTorSpringOn) {
		double tauOn = _tauLeftStartProp.getUseDefault() ? _tau : _tauLeftStart;
		double tauOff = _tauLeftEndProp.getUseDefault() ? _tau : _tauLeftEnd;
		_lTor = addTorsionalCorrectiveSpring(qStore,uStore,body2,tauOn,_lFootFlat,tauOff,_lHeelOff);
	}

	// INPUT
	// Controls
	cout<<endl<<endl<<"Loading controls from file "<<_controlsFileName<<".\n";
	ControlSet *controlSet = new ControlSet(_controlsFileName);
	cout<<"Found "<<controlSet->getSize()<<" controls.\n\n";
	// States
	Storage *yStore = new Storage(_statesFileName);

	// Add actuation analysis -- needed in order to evaluate unperturbed forces
	// Actuation
	Actuation *actuation = new Actuation(_model);
	_model->addAnalysis(actuation);

	Kinematics *kin=0;
	BodyKinematics *bodyKin=0;
	AnalysisSet &ans=getAnalysisSet();
	for(int i=0;i<ans.getSize();i++) {
		if(!ans.get(i)->getOn()) continue;
		if(dynamic_cast<Kinematics*>(ans.get(i))) kin=dynamic_cast<Kinematics*>(ans.get(i));
		else if(dynamic_cast<BodyKinematics*>(ans.get(i))) bodyKin=dynamic_cast<BodyKinematics*>(ans.get(i));
	}

	// SETUP SIMULATION
	// Manager
	ModelIntegrand integrand(_model);
	integrand.setControlSet(*controlSet);
	Manager manager(&integrand);
	manager.setSessionName(getName());
	// Initial and final times
	// If the times lie outside the range for which control values are
	// available, the initial and final times are altered.
	int first = 0;
	ControlLinear *control = (ControlLinear*)controlSet->get(first);
	if(control==NULL) {
		cout<<"\n\nError- There are no controls.\n\n";
		exit(-1);
	}
	double ti = control->getFirstTime();
	double tf = control->getLastTime();
	// Check initial time.
	if(_ti<ti) {
		cout<<"\n\nControls not available at "<<_ti<<".  ";
		cout<<"Changing initial time to "<<ti<<".";
		_ti = ti;
	}
	// Check final time.
	if(tf<_tf) {
		cout<<"\n\nControls not available at "<<_tf<<".  ";
		cout<<"Changing final time to "<<tf<<".";
		_tf = tf;
	}
	manager.setInitialTime(_ti);
	manager.setFinalTime(_tf);
	cout<<"\n\nPerforming perturbations over the range ti=";
	cout<<_ti<<" to tf="<<_tf<<endl<<endl;

	// Integrator settings
	IntegRKF *integ = manager.getIntegrator();
	integ->setMaximumNumberOfSteps(_maxSteps);
	integ->setMaxDT(_maxDT);
	integ->setTolerance(_errorTolerance);
	integ->setFineTolerance(_fineTolerance);

	// Pertubation callback
	ActuatorPerturbationIndependent *perturbation = 
		new ActuatorPerturbationIndependent(_model);
	_model->addDerivCallback(perturbation);

	int gravity_axis = 1;
	double original_gravity[3];
	int nperturb = actuators.getSize() + (_perturbGravity ? 1 : 0);

	if(_perturbGravity) _model->getGravity(original_gravity);

	Array<string> columnLabels;
	columnLabels.append("time");
	for(int i=0; i<actuators.getSize(); i++) columnLabels.append(actuators.get(i)->getName());
	if(_perturbGravity) columnLabels.append("gravity");

	// Figure out which columns are being recorded in the Kinematics and BodyKinematics analyses...
	// but make sure to ignore the first (time) column
	int ncoords = kin ? kin->getPositionStorage()->getColumnLabels().getSize()-1 : 0;
	int nbodycoords = bodyKin ? bodyKin->getPositionStorage()->getColumnLabels().getSize()-1 : 0;
	int nvalues = ncoords + nbodycoords;
	if(nvalues==0) 
		throw Exception("PerturbationTool.run: ERROR- No (active) analyses found -- no perturbation to compute.",__FILE__,__LINE__);

	Array<string> values_name("",nvalues);
	for(int i=0;i<ncoords;i++)
		values_name[i] = kin->getPositionStorage()->getColumnLabels()[i+1];
	for(int i=0;i<nbodycoords;i++)
		values_name[ncoords+i] = bodyKin->getPositionStorage()->getColumnLabels()[i+1];

	cout << "PERTURBED DATA:" << endl;
	if(actuators.getSize()) {
		cout << "Actuators:";
		for(int i=0; i<actuators.getSize(); i++) cout << (i>0?", ":"") << actuators.get(i)->getName();
		cout << endl;
	}
	if(_perturbGravity) cout << "Gravity perturbation on" << endl;
	cout << endl;

	cout << "MEASURED INDUCED ACCELERATIONS:" << endl;
	if(ncoords) {
		cout << "Kinematics: ";
		for(int i=0;i<ncoords;i++) {
			values_name[i] = kin->getPositionStorage()->getColumnLabels()[i+1];
			cout << (i>0?", ":"") << values_name[i];
		}
		cout << endl;
	}
	if(nbodycoords) {
		cout << "BodyKinematics: ";
		for(int i=0;i<nbodycoords;i++) {
			values_name[ncoords+i] = bodyKin->getPositionStorage()->getColumnLabels()[i+1];
			cout << (i>0?", ":"") << values_name[ncoords+i];
		}
		cout << endl;
	}

	// The first ncoords values in the values_* arrays refer to generalized coordinates that are being measured; the
	// remaining nbodycoords values refer to body coordinates that are being measured.
	Array<double> values_unperturbed(0.0,nvalues);
	ArrayPtrs<Array<double> > values_perturbed, values_dAdF;
	values_perturbed.setSize(nvalues);
	values_dAdF.setSize(nvalues);
	ArrayPtrs<Storage> values_perturbedStorage, values_dAdFStorage, values_deltaAStorage;
	values_perturbedStorage.setSize(nvalues);
	values_dAdFStorage.setSize(nvalues);
	values_deltaAStorage.setSize(nvalues);
	for(int i=0; i<nvalues; i++) {
		values_perturbed.set(i,new Array<double>(0.0,nperturb));
		values_dAdF.set(i,new Array<double>(0.0,nperturb));
		values_perturbedStorage.set(i,new Storage);
		values_dAdFStorage.set(i,new Storage);
		values_deltaAStorage.set(i,new Storage);
		values_perturbedStorage[i]->setName(values_name[i]+"_perturbed");
		values_perturbedStorage[i]->setColumnLabels(columnLabels);
		values_dAdFStorage[i]->setName(values_name[i]+"_dAdF");
		values_dAdFStorage[i]->setColumnLabels(columnLabels);
		values_deltaAStorage[i]->setName(values_name[i]+"_deltaA");
		values_deltaAStorage[i]->setColumnLabels(columnLabels);
	}

	Storage unperturbedAccelStorage;
	unperturbedAccelStorage.setName("unperturbedAccel");
	columnLabels.setSize(0);
	columnLabels.append("time");
	for(int i=0;i<nvalues;i++) columnLabels.append(values_name[i]);
	unperturbedAccelStorage.setColumnLabels(columnLabels);

	Array<double> deltaA(0,nperturb);

	// From now on we'll only need the last state vectors recorded in these analyses, so we
	// set their step interval to a large number to avoid them computing and writing their
	// data at the (many) individual integration steps.
	if(kin && !_outputDetailedResults) kin->setStepInterval(1000000);
	if(bodyKin) bodyKin->setStepInterval(1000000);
	actuation->setStepInterval(1000000);

	IO::makeDir(getResultsDir());

	time_t startTime,finishTime,iterationTime;
	time(&startTime);
	iterationTime = startTime;
	struct tm *localTime = localtime(&startTime);
	double elapsedTime;
	cout<<"================================================================\n";
	cout<<"Start time = "<<asctime(localTime);
	cout<<"================================================================\n";

	//********************************************************************
	// LOOP
	//********************************************************************
	double lastPertTime = _tf - _pertWindow;
	for(double t=_ti;t<=lastPertTime;t+=_pertIncrement) {
		// SET INITIAL AND FINAL TIME AND THE INITIAL STATES
		int index = yStore->findIndex(t);
		double tiPert;
		yStore->getTime(index,tiPert);
		double tfPert = tiPert + _pertWindow;
		manager.setInitialTime(tiPert);
		manager.setFinalTime(tfPert);
		const Array<double> &yi = yStore->getStateVector(index)->getData();
		_model->setInitialStates(&yi[0]);

		// RESET ANALYSES
		if(kin) {
			kin->getPositionStorage()->reset();
			kin->getVelocityStorage()->reset();
			kin->getAccelerationStorage()->reset();
		}
		if(bodyKin) {
			bodyKin->getPositionStorage()->reset();
			bodyKin->getVelocityStorage()->reset();
			bodyKin->getAccelerationStorage()->reset();
		}
		actuation->getForceStorage()->reset();

		// INTEGRATE (1)
		integ->setUseSpecifiedDT(false);
		perturbation->setOn(false);
		cout<<"\n\nUnperturbed integration (1) from "<<tiPert<<" to "<<tfPert<<endl;
		manager.integrate();
		
		// record unperturbed accelerations:
		Array<double> unperturbedAccel(0.0, nvalues);
		if(kin) {
			const Array<double> &posStart = kin->getPositionStorage()->getStateVector(0)->getData();
			const Array<double> &velStart = kin->getVelocityStorage()->getStateVector(0)->getData();
			const Array<double> &posEnd = kin->getPositionStorage()->getLastStateVector()->getData();
			double dt=kin->getPositionStorage()->getLastTime() - kin->getPositionStorage()->getFirstTime();
			if(dt>1e-8) for(int i=0;i<ncoords;i++) unperturbedAccel[i] = 2*(posEnd[i]-posStart[i]-dt*velStart[i])/(dt*dt);
		}
		if(bodyKin) {
			const Array<double> &posStart = bodyKin->getPositionStorage()->getStateVector(0)->getData();
			const Array<double> &velStart = bodyKin->getVelocityStorage()->getStateVector(0)->getData();
			const Array<double> &posEnd = bodyKin->getPositionStorage()->getLastStateVector()->getData();
			double dt=bodyKin->getPositionStorage()->getLastTime() - bodyKin->getPositionStorage()->getFirstTime();
			if(dt>1e-8) for(int i=0;i<nbodycoords;i++) unperturbedAccel[ncoords+i] = 2*(posEnd[i]-posStart[i]-dt*velStart[i])/(dt*dt);
		}
		unperturbedAccelStorage.append(tiPert, nvalues, &unperturbedAccel[0]);
		char fileName[Object::NAME_LENGTH];
		sprintf(fileName,"%s/%s_unperturbedAccel_dt_%.3f_df_%.3lf.sto",getResultsDir().c_str(),getName().c_str(),_pertWindow,_pertDF);
		unperturbedAccelStorage.print(fileName);

		// If we are not perturbing any actuators/gravity, we must only be computing unperturbed accelerations...
		// so can skip rest of this loop body.
		if(nperturb==0) continue;

		// INTEGRATE (2) - Record unperturbed muscle forces
		integ->setUseSpecifiedDT(true);
		perturbation->setOn(true);
		perturbation->getUnperturbedForceStorage()->reset(); 
		perturbation->setRecordUnperturbedForces(true);
		cout<<"\nUnperturbed integration 2 to record forces and kinematics" << endl;
		manager.integrate();
		perturbation->setRecordUnperturbedForces(false);

		// Get unperturbed values (concatenate generalized coordinates and body coordinates)
		if(kin) {
			const Array<double> &unperturbedCoordinates = kin->getPositionStorage()->getLastStateVector()->getData(); // at end of timestep
			for(int i=0;i<ncoords;i++) values_unperturbed[i] = unperturbedCoordinates[i];
		}
		if(bodyKin) {
			const Array<double> &unperturbedBodyCoordinates = bodyKin->getPositionStorage()->getLastStateVector()->getData(); // at end of timestep
			for(int i=0;i<nbodycoords;i++) values_unperturbed[ncoords+i] = unperturbedBodyCoordinates[i];
		}

		// Unperturbed forces
		Array<double> &unperturbedForcesAll = actuation->getForceStorage()->getStateVector(0)->getData(); // at BEGINNING of timestep
		// Unperturbed forces for only the subset of actuators we care about
		Array<double> unperturbedForces(0,actuators.getSize());
		for(int m=0;m<actuators.getSize();m++) unperturbedForces[m]=unperturbedForcesAll[mapPerturbedActuatorsToAllActuators[m]];
		// include unperturbed gravity value if doing gravity perturbation
		if(_perturbGravity) unperturbedForces.append(original_gravity[gravity_axis]);

		// Loop over actuators/gravity to be perturbed
		for (int m=0;m<nperturb;m++)	{
			_model->getDerivCallbackSet()->resetCallbacks();
			perturbation->reset(); 
			string actuatorName;
			if(m<actuators.getSize()) {
				AbstractActuator *act = actuators.get(m);
				actuatorName = act->getName();
				// Set up pertubation callback
				cout<<"\nPerturbation of muscle "<<act->getName()<<" ("<<m<<") in loop"<<endl;
				perturbation->setActuator(act); 
				perturbation->setPerturbation(ActuatorPerturbationIndependent::DELTA,+_pertDF);
			} else {
				cout<<"\nGravity perturbation"<<endl;
				actuatorName = "gravity";
				perturbation->setActuator(0); 
				double grav[3];
				for(int i=0;i<3;i++) grav[i]=original_gravity[i];
				grav[gravity_axis] += _pertDF;
				_model->setGravity(grav);
			}

			// Integrate
 			manager.integrate();

			if(m<actuators.getSize()) {
				cout << "actuator:\t"<<m<<"\tunperturbed force:\t"<<unperturbedForces[m]<<endl;
			} else {
				cout << "gravity original:\t"<<unperturbedForces[m]<<endl;
				// undo gravity perturbation
				_model->setGravity(original_gravity);
			}

			// Perturbed generalized coordinate values (concatenate into values_perturbed array)
			if(kin) {
				const Array<double> &perturbedCoordinates = kin->getPositionStorage()->getLastStateVector()->getData();
				for(int i=0;i<ncoords;i++) (*values_perturbed[i])[m] = perturbedCoordinates[i];
			}
			if(bodyKin) {
				const Array<double> &perturbedBodyCoordinates = bodyKin->getPositionStorage()->getLastStateVector()->getData();
				for(int i=0;i<nbodycoords;i++) (*values_perturbed[ncoords+i])[m] = perturbedBodyCoordinates[i];
			}

			// COMPUTE DERIVATIVES
			for(int i=0;i<nvalues;i++) {
				double perturbed = (*values_perturbed[i])[m], unperturbed = values_unperturbed[i];
				double dAdF = 2*(perturbed - unperturbed)/(_pertDF*_pertWindow*_pertWindow);
				(*values_perturbed[i])[m] = perturbed;
				(*values_dAdF[i])[m] = dAdF;

				cout << values_name[i] << ": perturbed="<<perturbed<<"  unperturbed="<<unperturbed<<"  diff="<<perturbed-unperturbed
					  <<"  dAdF="<<dAdF<<"  deltaA="<<unperturbedForces[m]*dAdF<<endl;
			}

			if(_outputDetailedResults) {
				// Spring forces
				if(_rLin) {
					sprintf(fileName,"%s/%s_detailed_actuator_%s_time_%.3f_appliedForce_rLin.sto",getResultsDir().c_str(),getName().c_str(),actuatorName.c_str(), tiPert);
					_rLin->getAppliedForceStorage()->print(fileName);
				}
				if(_lLin) {
					sprintf(fileName,"%s/%s_detailed_actuator_%s_time_%.3f_appliedForce_lLin.sto",getResultsDir().c_str(),getName().c_str(),actuatorName.c_str(), tiPert);
					_lLin->getAppliedForceStorage()->print(fileName);
				}
				if(_rTor) {
					sprintf(fileName,"%s/%s_detailed_actuator_%s_time_%.3f_appliedTorque_rTrq.sto",getResultsDir().c_str(),getName().c_str(),actuatorName.c_str(), tiPert);
					_rTor->getAppliedTorqueStorage()->print(fileName);
				}
				if(_lTor) {
					sprintf(fileName,"%s/%s_detailed_actuator_%s_time_%.3f_appliedTorque_lTrq.sto",getResultsDir().c_str(),getName().c_str(),actuatorName.c_str(), tiPert);
					_lTor->getAppliedTorqueStorage()->print(fileName);
				}
				if(kin) {
					sprintf(fileName,"%s/%s_detailed_actuator_%s_time_%.3f_Kinematics_q.sto",getResultsDir().c_str(),getName().c_str(),actuatorName.c_str(), tiPert);
					kin->getPositionStorage()->print(fileName);
				}
			}
		} //end muscle loop

		// Append to storage objects
		for(int i=0;i<nvalues;i++) {
			const Array<double> &perturbed = *values_perturbed[i];
			const Array<double> &dAdF = *values_dAdF[i];
			values_perturbedStorage[i]->append(tiPert,nperturb,&perturbed[0]);
			values_dAdFStorage[i]->append(tiPert,nperturb,&dAdF[0]);
			for(int m=0;m<nperturb;m++) deltaA[m] = unperturbedForces[m] * dAdF[m];
			values_deltaAStorage[i]->append(tiPert,nperturb,&deltaA[0]);
		}
	
		// Print results
		for(int i=0;i<nvalues;i++) {
			sprintf(fileName,"%s/%s_%s_perturbed_dt_%.3f_df_%.3lf.sto",getResultsDir().c_str(),getName().c_str(),values_name[i].c_str(),_pertWindow,_pertDF);
			values_perturbedStorage[i]->print(fileName);
			sprintf(fileName,"%s/%s_%s_dAdF_dt_%.3f_df_%.3lf.sto",getResultsDir().c_str(),getName().c_str(),values_name[i].c_str(),_pertWindow,_pertDF);
			values_dAdFStorage[i]->print(fileName);
			sprintf(fileName,"%s/%s_%s_deltaA_dt_%.3f_df_%.3lf.sto",getResultsDir().c_str(),getName().c_str(),values_name[i].c_str(),_pertWindow,_pertDF);
			values_deltaAStorage[i]->print(fileName);
		}

		time(&finishTime);
		elapsedTime = difftime(finishTime,iterationTime);
		iterationTime = finishTime;
		cout<<"Iteration finished (took " << elapsedTime << " seconds)\n";

	} // end time loop
	//***************************************************************************
	IO::chDir(saveWorkingDirectory);

	cout<<"\n\n=================================================================\n";
	cout<<"PerturbationTool finished\n";
	cout<<"=================================================================\n";
	localTime = localtime(&startTime);
	cout<<"Start time   = "<<asctime(localTime);
	time(&finishTime);
	localTime = localtime(&finishTime);
	cout<<"Finish time  = "<<asctime(localTime);
	elapsedTime = difftime(finishTime,startTime);
	cout<<"Elapsed time = "<<elapsedTime<<" seconds.\n";
	cout<<"================================================================\n\n\n";

	return true;
}




//=============================================================================
// IO
//=============================================================================
//_____________________________________________________________________________
/**
 * Print the results of the analysis.
 *
 * @param aFileName File to which to print the data.
 * @param aDT Time interval between results (linear interpolation is used).
 * If not included as an argument or negative, all time steps are printed
 * without interpolation.
 * @param aExtension Extension for written files.
 */
void PerturbationTool::
printResults(const string &aBaseName,const string &aDir,double aDT,
				 const string &aExtension)
{
	cout<<"PerturbationTool.printResults: ";
	cout<<"Printing results of investigation "<<getName()<<".\n";
}
