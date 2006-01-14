// InvestigationPerturbation.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=============================================================================
// INCLUDES
//=============================================================================
#include "InvestigationPerturbation.h"
#include <NMBLTK/Tools/rdIO.h>
#include <NMBLTK/Tools/rdVectorGCVSplineR1R3.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include <NMBLTK/Simulation/Model/rdDerivCallbackSet.h>
#include <NMBLTK/Simulation/Control/rdControlLinear.h>
#include <NMBLTK/Simulation/Control/rdControlSet.h>
#include <NMBLTK/Analyses/suKinematics.h>
#include <NMBLTK/Analyses/suPointKinematics.h>
#include <NMBLTK/Analyses/suBodyKinematics.h>
#include <NMBLTK/Analyses/suActuation.h>
#include <NMBLTK/Analyses/suContact.h>
#include <NMBLTK/Analyses/suLinearSpring.h>
#include <NMBLTK/Analyses/suTorsionalSpring.h>
#include <NMBLTK/Analyses/suActuatorPerturbationIndependent.h>

using namespace std;

//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
InvestigationPerturbation::~InvestigationPerturbation()
{
	if(_controlSet!=0) delete _controlSet;
	if(_copStore!=0) delete _copStore;
	if(_qStore!=0) delete _qStore;
	if(_uStore!=0) delete _uStore;
	if(_yStore!=0) delete _yStore;
}
//_____________________________________________________________________________
/**
 * Default constructor.
 */
InvestigationPerturbation::InvestigationPerturbation() :
	_controlsFileName(_controlsFileNameProp.getValueStr()),
	_copFileName(_copFileNameProp.getValueStr()),
	_qFileName(_qFileNameProp.getValueStr()),
	_uFileName(_uFileNameProp.getValueStr()),
	_yFileName(_yFileNameProp.getValueStr()),
	_rHeelStrike(_rHeelStrikeProp.getValueDbl()),
	_rFootFlat(_rFootFlatProp.getValueDbl()),
	_rHeelOff(_rHeelOffProp.getValueDbl()),
	_rToeOff(_rToeOffProp.getValueDbl()),
	_lHeelStrike(_lHeelStrikeProp.getValueDbl()),
	_lFootFlat(_lFootFlatProp.getValueDbl()),
	_lHeelOff(_lHeelOffProp.getValueDbl()),
	_lToeOff(_lToeOffProp.getValueDbl()),
	_tau(_tauProp.getValueDbl()),
	_kLin(_kLinProp.getValueDblArray()),
	_bLin(_bLinProp.getValueDblArray()),
	_kTor(_kTorProp.getValueDblArray()),
	_bTor(_bTorProp.getValueDblArray())
{
	setType("InvestigationPerturbation");
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
InvestigationPerturbation::InvestigationPerturbation(const string &aFileName):
	Investigation(aFileName),
	_controlsFileName(_controlsFileNameProp.getValueStr()),
	_copFileName(_copFileNameProp.getValueStr()),
	_qFileName(_qFileNameProp.getValueStr()),
	_uFileName(_uFileNameProp.getValueStr()),
	_yFileName(_yFileNameProp.getValueStr()),
	_rHeelStrike(_rHeelStrikeProp.getValueDbl()),
	_rFootFlat(_rFootFlatProp.getValueDbl()),
	_rHeelOff(_rHeelOffProp.getValueDbl()),
	_rToeOff(_rToeOffProp.getValueDbl()),
	_lHeelStrike(_lHeelStrikeProp.getValueDbl()),
	_lFootFlat(_lFootFlatProp.getValueDbl()),
	_lHeelOff(_lHeelOffProp.getValueDbl()),
	_lToeOff(_lToeOffProp.getValueDbl()),
	_tau(_tauProp.getValueDbl()),
	_kLin(_kLinProp.getValueDblArray()),
	_bLin(_bLinProp.getValueDblArray()),
	_kTor(_kTorProp.getValueDblArray()),
	_bTor(_bTorProp.getValueDblArray())
{
	setType("InvestigationPerturbation");
	setNull();
	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Construct from a DOMElement.
 */
InvestigationPerturbation::InvestigationPerturbation(DOMElement *aElement):
	Investigation(aElement),
	_controlsFileName(_controlsFileNameProp.getValueStr()),
	_copFileName(_copFileNameProp.getValueStr()),
	_qFileName(_qFileNameProp.getValueStr()),
	_uFileName(_uFileNameProp.getValueStr()),
	_yFileName(_yFileNameProp.getValueStr()),
	_rHeelStrike(_rHeelStrikeProp.getValueDbl()),
	_rFootFlat(_rFootFlatProp.getValueDbl()),
	_rHeelOff(_rHeelOffProp.getValueDbl()),
	_rToeOff(_rToeOffProp.getValueDbl()),
	_lHeelStrike(_lHeelStrikeProp.getValueDbl()),
	_lFootFlat(_lFootFlatProp.getValueDbl()),
	_lHeelOff(_lHeelOffProp.getValueDbl()),
	_lToeOff(_lToeOffProp.getValueDbl()),
	_tau(_tauProp.getValueDbl()),
	_kLin(_kLinProp.getValueDblArray()),
	_bLin(_bLinProp.getValueDblArray()),
	_kTor(_kTorProp.getValueDblArray()),
	_bTor(_bTorProp.getValueDblArray())
{
	setType("InvestigationPerturbation");
	setNull();
	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * Copy constructors for all Investigation's only copy the non-XML variable
 * members of the object; that is, the object's DOMnode and rdXMLDocument
 * are not copied but set to NULL.  The reason for this is that for the
 * object and all its derived classes to establish the correct connection
 * to the XML document nodes, the the object would need to reconstruct based
 * on the XML document not the values of the object's member variables.
 *
 * There are three proper ways to generate an XML document for an Investigation:
 *
 * 1) Construction based on XML file (@see Investigation(const char *aFileName)).
 * In this case, the XML document is created by parsing the XML file.
 *
 * 2) Construction by Investigation(const rdXMLDocument *aDocument).
 * This constructor explictly requests construction based on an
 * XML document.  In this way the proper connection between an object's node
 * and the corresponding node within the XML document is established.
 * This constructor is a copy constructor of sorts because all essential
 * Investigation member variables should be held within the XML document.
 * The advantage of this style of construction is that nodes
 * within the XML document, such as comments that may not have any
 * associated Investigation member variable, are preserved.
 *
 * 3) A call to generateDocument().
 * This method generates an XML document for the Investigation from scratch.
 * Only the essential document nodes are created (that is, nodes that
 * correspond directly to member variables.).
 *
 * @param aInvestigation Object to be copied.
 * @see Investigation(const rdXMLDocument *aDocument)
 * @see Investigation(const char *aFileName)
 * @see generateDocument()
 */
InvestigationPerturbation::
InvestigationPerturbation(const InvestigationPerturbation &aInvestigation):
	Investigation(aInvestigation),
	_controlsFileName(_controlsFileNameProp.getValueStr()),
	_copFileName(_copFileNameProp.getValueStr()),
	_qFileName(_qFileNameProp.getValueStr()),
	_uFileName(_uFileNameProp.getValueStr()),
	_yFileName(_yFileNameProp.getValueStr()),
	_rHeelStrike(_rHeelStrikeProp.getValueDbl()),
	_rFootFlat(_rFootFlatProp.getValueDbl()),
	_rHeelOff(_rHeelOffProp.getValueDbl()),
	_rToeOff(_rToeOffProp.getValueDbl()),
	_lHeelStrike(_lHeelStrikeProp.getValueDbl()),
	_lFootFlat(_lFootFlatProp.getValueDbl()),
	_lHeelOff(_lHeelOffProp.getValueDbl()),
	_lToeOff(_lToeOffProp.getValueDbl()),
	_tau(_tauProp.getValueDbl()),
	_kLin(_kLinProp.getValueDblArray()),
	_bLin(_bLinProp.getValueDblArray()),
	_kTor(_kTorProp.getValueDblArray()),
	_bTor(_bTorProp.getValueDblArray())
{
	setNull();
	*this = aInvestigation;
}

//_____________________________________________________________________________
/**
 * Virtual copy constructor.
 */
rdObject* InvestigationPerturbation::
copy() const
{
	InvestigationPerturbation *object = new InvestigationPerturbation(*this);
	return(object);
}
//_____________________________________________________________________________
/**
 * Virtual copy constructor from DOMElement.
 */
rdObject* InvestigationPerturbation::
copy(DOMElement *aElement) const
{
	InvestigationPerturbation *object = new InvestigationPerturbation(aElement);
	*object = *this;
	object->updateFromXMLNode();
	return(object);
}
//_____________________________________________________________________________
/**
 * Set all member variables to their null or default values.
 */
void InvestigationPerturbation::
setNull()
{
	setupProperties();

	// POINTERS
	_controlSet = NULL;
	_copStore = NULL;
	_qStore = NULL;
	_uStore = NULL;
	_yStore = NULL;

	// FOOT CONTACT EVENTS
	_rHeelStrike = _rFootFlat =_rHeelOff = _rToeOff = 0.0;
	_lHeelStrike = _lFootFlat =_lHeelOff = _lToeOff = 0.0;

	// CORRECTIVE SPRING PARAMETERS
	_tau = 0.001;
	_kLin[0] = _kLin[1] = _kLin[2] = 5000000.0;
	_bLin[0] = _bLin[1] = _bLin[2] = 1500.0;
	_kTor[0] = _kTor[1] = _kTor[2] = 100000.0;
	_bTor[0] = _bTor[1] = _bTor[2] = 1000.0;
}
//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void InvestigationPerturbation::setupProperties()
{
	// INPUT FILE NAMES
	_controlsFileNameProp.setName("controls_file_name");
	_propertySet.append( &_controlsFileNameProp );

	_copFileNameProp.setName("cop_file_name");
	_propertySet.append( &_copFileNameProp );

	_qFileNameProp.setName("coordinates_file_name");
	_propertySet.append( &_qFileNameProp );

	_uFileNameProp.setName("speeds_file_name");
	_propertySet.append( &_uFileNameProp );

	_yFileNameProp.setName("states_file_name");
	_propertySet.append( &_yFileNameProp );

	// FOOT CONTACT EVENT TIMES
	_rHeelStrikeProp.setName("r_heel_strike");
	_propertySet.append( &_rHeelStrikeProp );

	_rFootFlatProp.setName("r_foot_flat");
	_propertySet.append( &_rFootFlatProp );

	_rHeelOffProp.setName("r_heel_off");
	_propertySet.append( &_rHeelOffProp );

	_rToeOffProp.setName("r_toe_off");
	_propertySet.append( &_rToeOffProp );

	_lHeelStrikeProp.setName("l_heel_strike");
	_propertySet.append( &_lHeelStrikeProp );

	_lFootFlatProp.setName("l_foot_flat");
	_propertySet.append( &_lFootFlatProp );

	_lHeelOffProp.setName("l_heel_off");
	_propertySet.append( &_lHeelOffProp );

	_lToeOffProp.setName("l_toe_off");
	_propertySet.append( &_lToeOffProp );


	// CORRECTIVE SPRING PARAMETERS
	_tauProp.setName("scaling_rise_time");
	_propertySet.append( &_tauProp );

	_kLinProp.setName("corrective_spring_linear_stiffness");
	_propertySet.append( &_kLinProp );

	_bLinProp.setName("corrective_spring_linear_damping");
	_propertySet.append( &_bLinProp );

	_kTorProp.setName("corrective_spring_torsional_stiffness");
	_propertySet.append( &_kTorProp );

	_bTorProp.setName("corrective_spring_torsional_damping");
	_propertySet.append( &_bTorProp );

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
InvestigationPerturbation& InvestigationPerturbation::
operator=(const InvestigationPerturbation &aInvestigation)
{
	// BASE CLASS
	Investigation::operator=(aInvestigation);

	// MEMEBER VARIABLES

	return(*this);
}

//=============================================================================
// GET AND SET
//=============================================================================
//_____________________________________________________________________________
/**
 * Set the model to be investigated.
 */
void InvestigationPerturbation::
setModel(rdModel *aModel)
{
	_model = aModel;
}


//=============================================================================
// RUN
//=============================================================================
//_____________________________________________________________________________
/**
 * Run the investigation.
 */
void InvestigationPerturbation::run()
{
	cout<<"Running investigation "<<getName()<<".\n";

	int i;
	rdIO::SetPrecision(_outputPrecision);

	// REGISTER TYPES
	rdObject::RegisterType(rdControlLinear());
	rdObject::RegisterType(rdControlLinearNode());

	// INPUT
	// Controls
	cout<<endl<<endl<<"Loading controls from file "<<_controlsFileName<<".\n";
	_controlSet = new rdControlSet(_controlsFileName);
	cout<<"Found "<<_controlSet->getSize()<<" controls.\n\n";
	// Center of pressure
	cout<<endl<<endl<<"Loading center of pressure data from file ";
	cout<<_copFileName<<".\n";
	_copStore = new rdStorage(_copFileName.c_str());
	// Qs and Us
	cout<<endl<<endl<<"Loading generalized coordinates and speeds from files ";
	cout<<_qFileName<<" and "<<_uFileName<<".\n";
	_qStore = new rdStorage(_qFileName.c_str());
	_uStore = new rdStorage(_uFileName.c_str());
	// States
	_yStore = new rdStorage(_yFileName.c_str());

	// CONVERT Qs AND Us TO RADIANS AND QUATERNIONS
	_model->convertDegreesToRadians(_qStore);
	_model->convertAnglesToQuaternions(_qStore);
	_model->convertDegreesToRadians(_uStore);

	// CONSTRUCT CORRECTIVE SPRINGS
	constructCorrectiveSprings();

	// ADD ANALYSES
	// Kinematics
	suKinematics *kinAngles = new suKinematics(_model);
	_model->addAnalysis(kinAngles);
	kinAngles->getPositionStorage()->setWriteSIMMHeader(true);
	kinAngles->setOn(true);
	// Body kinematics
	suBodyKinematics *kin = new suBodyKinematics(_model);
	_model->addAnalysis(kin);
	kin->getPositionStorage()->setWriteSIMMHeader(true);		
	kin->setOn(true);

	// SETUP SIMULATION
	// Manager
	rdModelIntegrand integrand(_model);
	integrand.setControlSet(*_controlSet);
	rdManager manager(&integrand);
	manager.setSessionName(getName());

	// Initial and final times
	// If the times lie outside the range for which control values are
	// available, the initial and final times are altered.
	int first = 0;
	rdControlLinear *control = (rdControlLinear*)_controlSet->get(first);
	if(control==NULL) {
		cout<<"\n\nError- There are no controls.\n\n";
		exit(-1);
	}
	double ti = control->getFirstTime();
	double tf = control->getLastTime();
	if(_ti<ti) {
		cout<<"\n\nControls not available at "<<_ti<<".  ";
		cout<<"Changing initial time to "<<ti<<".";
		_ti = ti;
	}
	if(tf<_tf) {
		cout<<"\n\nControls not available at "<<_tf<<".  ";
		cout<<"Changing final time to "<<tf<<".";
		_tf = tf;
	}

	cout<<"\n\nPerforming perturbations from ti="<<_ti<<" to tf="<<_tf<<endl<<endl;



}

//_____________________________________________________________________________
/**
 * Construct the corrective springs.
 */
void InvestigationPerturbation::
constructCorrectiveSprings()
{
	// SCALING FUNCTIONS FOR SPRINGS
	double tScale,dtScale=0.001;
	double tiScale = _qStore->getFirstTime();
	double tfScale = _qStore->getLastTime();
	double value1,value2;
	rdArray<double> timeScale(0.0);
	rdArray<double> rLinearScale(0.0),rTorsionalScale(0.0);
	rdArray<double> lLinearScale(0.0),lTorsionalScale(0.0);
	for(tScale=tiScale;tScale<=tfScale;tScale+=dtScale) {
		// time
		timeScale.append(tScale);
		// rLinear
		value1 = rdMath::SigmaUp(_tau,_rHeelStrike,tScale);
		value2 = rdMath::SigmaDn(_tau,_rToeOff,tScale);
		rLinearScale.append(value1+value2-1.0);
		// rTorsional
		value1 = rdMath::SigmaUp(_tau,_rFootFlat,tScale);
		value2 = rdMath::SigmaDn(_tau,_rHeelOff,tScale);
		rTorsionalScale.append(value1+value2-1.0);
		// lLinear
		value1 = rdMath::SigmaUp(_tau,_lHeelStrike,tScale);
		value2 = rdMath::SigmaDn(_tau,_lToeOff,tScale);
		lLinearScale.append(value1+value2-1.0);
		// lTorsional
		value1 = rdMath::SigmaUp(_tau,_lFootFlat,tScale);
		value2 = rdMath::SigmaDn(_tau,_lHeelOff,tScale);
		lTorsionalScale.append(value1+value2-1.0);
	}
	// Create Splines
	rdGCVSpline *rScaleTranslationalSpline = new rdGCVSpline(3,timeScale.getSize(),&timeScale[0],&rLinearScale[0]);
	rScaleTranslationalSpline->setName("Right_Translational");
	rdGCVSpline *rScaleTorsionalSpline = new rdGCVSpline(3,timeScale.getSize(),&timeScale[0],&rTorsionalScale[0]);
	rScaleTorsionalSpline->setName("Right_Torsional");
	rdGCVSpline *lScaleTranslationalSpline = new rdGCVSpline(3,timeScale.getSize(),&timeScale[0],&lLinearScale[0]);
	lScaleTranslationalSpline->setName("Left_Translational");
	rdGCVSpline *lScaleTorsionalSpline = new rdGCVSpline(3,timeScale.getSize(),&timeScale[0],&lTorsionalScale[0]);
	lScaleTorsionalSpline->setName("Left_Torsional");

	// CONSTRUCT SPRINGS
	rdVectorGCVSplineR1R3 *cop;
	int size = _copStore->getSize();
	double *t=0,*x=0,*y=0,*z=0;
	_copStore->getTimeColumn(t);

	// LINEAR
	// right
	string colName;
	colName = "ground_force_px_r";
	_copStore->getDataColumn(colName,x);
	colName = "ground_force_py_r";
	_copStore->getDataColumn(colName,y);
	colName = "ground_force_pz_r";
	_copStore->getDataColumn(colName,z);
	cop = new rdVectorGCVSplineR1R3(5,size,t,x,y,z);
	suLinearSpring *rLin = new suLinearSpring(_model,_model->getBodyIndex("calcn_r"));
	rLin->computePointAndTargetFunctions(_qStore,_uStore,*cop);
	rLin->setKValue(&_kLin[0]);
	rLin->setBValue(&_bLin[0]);
	rLin->setScaleFunction(rScaleTranslationalSpline);
	rdStorage *rLinStore = rLin->getAppliedForceStorage();
	_model->addDerivCallback(rLin);
	// left linear
	colName = "ground_force_px_l";
	_copStore->getDataColumn(colName,x);
	colName = "ground_force_py_l";
	_copStore->getDataColumn(colName,y);
	colName = "ground_force_pz_l";
	_copStore->getDataColumn(colName,z);
	cop = new rdVectorGCVSplineR1R3(5,size,t,x,y,z);
	suLinearSpring *lLin = new suLinearSpring(_model,_model->getBodyIndex("calcn_l"));
	lLin->computePointAndTargetFunctions(_qStore,_uStore,*cop);
	lLin->setKValue(&_kLin[0]);
	lLin->setBValue(&_bLin[0]);
	lLin->setScaleFunction(lScaleTranslationalSpline);
	rdStorage *lLinStore = lLin->getAppliedForceStorage();
	_model->addDerivCallback(lLin);

	// TORSIONAL
	// right
	suTorsionalSpring *rTrq = new suTorsionalSpring(_model,_model->getBodyIndex("calcn_r"));
	rTrq->computeTargetFunctions(_qStore,_uStore);
	rTrq->setKValue(&_kTor[0]);
	rTrq->setBValue(&_bTor[0]);
	rTrq->setScaleFunction(rScaleTorsionalSpline);
	rdStorage *rTrqStore = rTrq->getAppliedTorqueStorage();
	_model->addDerivCallback(rTrq);
	// left
	suTorsionalSpring *lTrq = new suTorsionalSpring(_model,_model->getBodyIndex("calcn_l"));
	lTrq->computeTargetFunctions(_qStore,_uStore);
	lTrq->setKValue(&_kTor[0]);
	lTrq->setBValue(&_bTor[0]);
	lTrq->setScaleFunction(lScaleTorsionalSpline);
	rdStorage *lTrqStore = lTrq->getAppliedTorqueStorage();
	_model->addDerivCallback(lTrq);
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
void InvestigationPerturbation::
printResults(const char *aBaseName,const char *aDir,double aDT,
				 const char *aExtension)
{
	cout<<"InvestigationPerturbation.printResults: ";
	cout<<"Printing results of investigation "<<getName()<<".\n";
}
