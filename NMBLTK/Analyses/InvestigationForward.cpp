// InvestigationForward.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=============================================================================
// INCLUDES
//=============================================================================
#include "InvestigationForward.h"
#include <NMBLTK/Tools/rdIO.h>
#include <NMBLTK/Tools/rdVectorGCVSplineR1R3.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include <NMBLTK/Simulation/Model/rdDerivCallbackSet.h>
#include <NMBLTK/Simulation/Model/rdAnalysisSet.h>
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
InvestigationForward::~InvestigationForward()
{
}
//_____________________________________________________________________________
/**
 * Default constructor.
 */
InvestigationForward::InvestigationForward() :
	_controlsFileName(_controlsFileNameProp.getValueStr()),
	_initialStatesFileName(_initialStatesFileNameProp.getValueStr())
{
	setType("InvestigationForward");
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
InvestigationForward::InvestigationForward(const string &aFileName) :
	_controlsFileName(_controlsFileNameProp.getValueStr()),
	_initialStatesFileName(_initialStatesFileNameProp.getValueStr())
{
	setType("InvestigationForward");
	setNull();
	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Construct from a DOMElement.
 */
InvestigationForward::InvestigationForward(DOMElement *aElement) :
	_controlsFileName(_controlsFileNameProp.getValueStr()),
	_initialStatesFileName(_initialStatesFileNameProp.getValueStr())
{
	setType("InvestigationForward");
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
InvestigationForward::
InvestigationForward(const InvestigationForward &aInvestigation) :
	_controlsFileName(_controlsFileNameProp.getValueStr()),
	_initialStatesFileName(_initialStatesFileNameProp.getValueStr())
{
	setNull();
	*this = aInvestigation;
}

//_____________________________________________________________________________
/**
 * Virtual copy constructor.
 */
rdObject* InvestigationForward::
copy() const
{
	InvestigationForward *object = new InvestigationForward(*this);
	return(object);
}
//_____________________________________________________________________________
/**
 * Virtual copy constructor from DOMElement.
 */
rdObject* InvestigationForward::
copy(DOMElement *aElement) const
{
	InvestigationForward *object = new InvestigationForward(aElement);
	*object = *this;
	object->updateFromXMLNode();
	return(object);
}
//_____________________________________________________________________________
/**
 * Set all member variables to their null or default values.
 */
void InvestigationForward::
setNull()
{
	setupProperties();

}
//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void InvestigationForward::setupProperties()
{

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
InvestigationForward& InvestigationForward::
operator=(const InvestigationForward &aInvestigation)
{
	// BASE CLASS
	Investigation::operator=(aInvestigation);

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
void InvestigationForward::run()
{
	cout<<"Running investigation "<<getName()<<".\n";

	// SET OUTPUT PRECISION
	rdIO::SetPrecision(_outputPrecision);

	// INPUT
	// Controls
	cout<<"\n\nLoading controls from file "<<_controlsFileName<<".\n";
	rdControlSet *controlSet = new rdControlSet(_controlsFileName);
	cout<<"Found "<<controlSet->getSize()<<" controls.\n\n";
	// Initial states
	cout<<"\n\nLoading initial states from file "<<_initialStatesFileName<<".\n";
	rdStorage *yiStore = new rdStorage(_initialStatesFileName.c_str());

	// CHECK FOR A MODEL
	if(_model==NULL) {
		string msg = "ERROR- A model has not been set.";
		cout<<endl<<msg<<endl;
		throw(rdException(msg,__FILE__,__LINE__));
	}

	// ASSIGN NUMBERS OF THINGS
	int ny = _model->getNY();
	int nq = _model->getNQ();
	int nu = _model->getNU();
	int na = _model->getNA();
	int nb = _model->getNB();

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
	// Actuation
	suActuation *actuation = new suActuation(_model);
	_model->addAnalysis(actuation);
	actuation->setOn(true);

	// SETUP SIMULATION
	// Manager
	rdModelIntegrand integrand(_model);
	integrand.setControlSet(*controlSet);
	rdManager manager(&integrand);
	manager.setSessionName(getName());
	// Initial and final times
	// If the times lie outside the range for which control values are
	// available, the initial and final times are altered.
	int first = 0;
	rdControlLinear *control = (rdControlLinear*)controlSet->get(first);
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
	rdIntegRKF *integ = manager.getIntegrator();
	integ->setMaximumNumberOfSteps(_maxSteps);
	integ->setMaxDT(_maxDT);
	integ->setTolerance(_errorTolerance);
	integ->setFineTolerance(_fineTolerance);

	// SET INITIAL AND FINAL TIME AND THE INITIAL STATES
	rdArray<double> yi(0.0,ny);
	int index = yiStore->findIndex(_ti);
	yiStore->getTime(index,_ti);
	yiStore->getData(index,ny,&yi[0]);
	manager.setInitialTime(_ti);
	manager.setFinalTime(_tf);
	_model->setInitialStates(&yi[0]);

	// INTEGRATE
	cout<<"\n\nUnperturbed integration (1) from "<<_ti<<" to "<<_tf<<endl;
	manager.integrate();
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
void InvestigationForward::
printResults(const char *aBaseName,const char *aDir,double aDT,
				 const char *aExtension)
{
	cout<<"InvestigationForward.printResults: ";
	cout<<"Printing results of investigation "<<getName()<<".\n";
	_model->getAnalysisSet()->printResults(aBaseName,aDir,aDT,aExtension);
}
