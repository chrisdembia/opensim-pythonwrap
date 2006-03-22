// Investigation.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include "Investigation.h"
#include "LoadModel.h"

using namespace std;


//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
Investigation::~Investigation()
{
}
//_____________________________________________________________________________
/**
 * Default constructor.
 */
Investigation::Investigation():
	_modelLibrary(_modelLibraryProp.getValueStr()),
	_modelFile(_modelFileProp.getValueStr()),
	_actuatorSetFile(_actuatorSetFileProp.getValueStr()),
	_contactForceSetFile(_contactForceSetFileProp.getValueStr()),
	_paramsFile(_paramsFileProp.getValueStr()),
	_resultsDir(_resultsDirProp.getValueStr()),
	_outputPrecision(_outputPrecisionProp.getValueInt()),
	_ti(_tiProp.getValueDbl()),
	_tf(_tfProp.getValueDbl()),
	_maxSteps(_maxStepsProp.getValueInt()),
	_maxDT(_maxDTProp.getValueDbl()),
	_errorTolerance(_errorToleranceProp.getValueDbl()),
	_fineTolerance(_fineToleranceProp.getValueDbl()),
	_analysisSetProp(rdPropertyObj("Analyses",rdAnalysisSet())),
	_analysisSet((rdAnalysisSet&)_analysisSetProp.getValueObj())
{
	setType("Investigation");
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
Investigation::Investigation(const string &aFileName):
	rdObject(aFileName),
	_modelLibrary(_modelLibraryProp.getValueStr()),
	_modelFile(_modelFileProp.getValueStr()),
	_actuatorSetFile(_actuatorSetFileProp.getValueStr()),
	_contactForceSetFile(_contactForceSetFileProp.getValueStr()),
	_paramsFile(_paramsFileProp.getValueStr()),
	_resultsDir(_resultsDirProp.getValueStr()),
	_outputPrecision(_outputPrecisionProp.getValueInt()),
	_ti(_tiProp.getValueDbl()),
	_tf(_tfProp.getValueDbl()),
	_maxSteps(_maxStepsProp.getValueInt()),
	_maxDT(_maxDTProp.getValueDbl()),
	_errorTolerance(_errorToleranceProp.getValueDbl()),
	_fineTolerance(_fineToleranceProp.getValueDbl()),
	_analysisSetProp(rdPropertyObj("Analyses",rdAnalysisSet())),
	_analysisSet((rdAnalysisSet&)_analysisSetProp.getValueObj())
{
	setType("Investigation");
	setNull();
	updateFromXMLNode();
	loadModel();
}
//_____________________________________________________________________________
/**
 * Construct from a DOMElement.
 */
Investigation::Investigation(DOMElement *aElement):
	rdObject(aElement),
	_modelLibrary(_modelLibraryProp.getValueStr()),
	_modelFile(_modelFileProp.getValueStr()),
	_actuatorSetFile(_actuatorSetFileProp.getValueStr()),
	_contactForceSetFile(_contactForceSetFileProp.getValueStr()),
	_paramsFile(_paramsFileProp.getValueStr()),
	_resultsDir(_resultsDirProp.getValueStr()),
	_outputPrecision(_outputPrecisionProp.getValueInt()),
	_ti(_tiProp.getValueDbl()),
	_tf(_tfProp.getValueDbl()),
	_maxSteps(_maxStepsProp.getValueInt()),
	_maxDT(_maxDTProp.getValueDbl()),
	_errorTolerance(_errorToleranceProp.getValueDbl()),
	_fineTolerance(_fineToleranceProp.getValueDbl()),
	_analysisSetProp(rdPropertyObj("Analyses",rdAnalysisSet())),
	_analysisSet((rdAnalysisSet&)_analysisSetProp.getValueObj())
{
	setType("Investigation");
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
Investigation::Investigation(const Investigation &aInvestigation):
	rdObject(aInvestigation),
	_modelLibrary(_modelLibraryProp.getValueStr()),
	_modelFile(_modelFileProp.getValueStr()),
	_actuatorSetFile(_actuatorSetFileProp.getValueStr()),
	_contactForceSetFile(_contactForceSetFileProp.getValueStr()),
	_paramsFile(_paramsFileProp.getValueStr()),
	_resultsDir(_resultsDirProp.getValueStr()),
	_outputPrecision(_outputPrecisionProp.getValueInt()),
	_ti(_tiProp.getValueDbl()),
	_tf(_tfProp.getValueDbl()),
	_maxSteps(_maxStepsProp.getValueInt()),
	_maxDT(_maxDTProp.getValueDbl()),
	_errorTolerance(_errorToleranceProp.getValueDbl()),
	_fineTolerance(_fineToleranceProp.getValueDbl()),
	_analysisSetProp(rdPropertyObj("Analyses",rdAnalysisSet())),
	_analysisSet((rdAnalysisSet&)_analysisSetProp.getValueObj())
{
	setNull();
	*this = aInvestigation;
}

//_____________________________________________________________________________
/**
 * Set all member variables to their null or default values.
 */
void Investigation::
setNull()
{
	setupProperties();

	_model = NULL;
	_modelLibrary = "";
	_modelFile = "";
	_actuatorSetFile = "";
	_contactForceSetFile = "";
	_paramsFile = "";
	_resultsDir = "./";
	_outputPrecision = 8;
	_ti = 0.0;
	_tf = 1.0;
	_maxSteps = 20000;
	_maxDT = 1.0;
	_errorTolerance = 1.0e-3;
	_fineTolerance = 1.0e-5;
}
//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void Investigation::setupProperties()
{
	_modelLibraryProp.setName("model_library");
	_propertySet.append( &_modelLibraryProp );

	_modelFileProp.setName("model_file");
	_propertySet.append( &_modelFileProp );

	_actuatorSetFileProp.setName("actuator_set_file");
	_propertySet.append( &_actuatorSetFileProp );

	_contactForceSetFileProp.setName("contact_force_set_file");
	_propertySet.append( &_contactForceSetFileProp );

	_paramsFileProp.setName("params_file");
	_propertySet.append( &_paramsFileProp );

	_resultsDirProp.setName("results_directory");
	_propertySet.append( &_resultsDirProp );

	_outputPrecisionProp.setName("output_precision");
	_propertySet.append( &_outputPrecisionProp );

	_tiProp.setName("initial_time");
	_propertySet.append( &_tiProp );

	_tfProp.setName("final_time");
	_propertySet.append( &_tfProp );

	_maxStepsProp.setName("maximum_number_of_integrator_steps");
	_propertySet.append( &_maxStepsProp );

	_maxDTProp.setName("maximum_integrator_step_size");
	_propertySet.append( &_maxDTProp );

	_errorToleranceProp.setName("integrator_error_tolerance");
	_propertySet.append( &_errorToleranceProp );

	_fineToleranceProp.setName("integrator_fine_tolerance");
	_propertySet.append( &_fineToleranceProp );

	_analysisSetProp.setName("Analyses");
	_propertySet.append( &_analysisSetProp );
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
Investigation& Investigation::
operator=(const Investigation &aInvestigation)
{
	// BASE CLASS
	rdObject::operator=(aInvestigation);

	// MEMEBER VARIABLES
	_model = aInvestigation._model;

	_modelLibrary = aInvestigation._modelLibrary;
	_modelFile = aInvestigation._modelFile;
	_actuatorSetFile = aInvestigation._actuatorSetFile;
	_contactForceSetFile = aInvestigation._contactForceSetFile;
	_paramsFile = aInvestigation._paramsFile;
	_resultsDir = aInvestigation._resultsDir;

	_outputPrecision = aInvestigation._outputPrecision;
	_ti = aInvestigation._ti;
	_tf = aInvestigation._tf;
	_maxSteps = aInvestigation._maxSteps;
	_errorTolerance = aInvestigation._errorTolerance;
	_fineTolerance = aInvestigation._fineTolerance;
	_analysisSet = aInvestigation._analysisSet;

	return(*this);
}


//=============================================================================
// GET AND SET
//=============================================================================
//-----------------------------------------------------------------------------
// MODEL
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the model to be investigated.
 */
void Investigation::
setModel(rdModel *aModel)
{
	_model = aModel;
	_analysisSet.setModel(_model);
}
//_____________________________________________________________________________
/**
 * Get the model to be investigated.
 */
rdModel* Investigation::
getModel() const
{
	return(_model);
}

//-----------------------------------------------------------------------------
// OUTPUT PRECISION
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the output precision.
 */
void Investigation::
setOutputPrecision(int aOutputPrecision)
{
	_outputPrecision = aOutputPrecision;
}
//_____________________________________________________________________________
/**
 * Get the output precision.
 */
int Investigation::
getOutputPrecision() const
{
	return(_outputPrecision);
}

//-----------------------------------------------------------------------------
// ANALYSIS SET
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the analysis set.
 */
rdAnalysisSet& Investigation::
getAnalysisSet() const
{
	return(_analysisSet);
}

//=============================================================================
// LOAD MODEL
//=============================================================================
//_____________________________________________________________________________
/**
 * Load and construct a model based on the property settings of
 * this investigation.
 */
void Investigation::
loadModel()
{
	cout<<"Investigation "<<getName()<<" loading a model using the ";
	cout<<"following command line:\n";

	rdArray<string> args("");
	constructCommandLineForLoadModel(args);
	cout<<args<<endl;

	int i;
	int argc = args.getSize();
	if(argc==0) { setModel(NULL);  return; }
	char **argv = new char*[argc];
	for(i=0;i<argc;i++) {
		argv[i] = (char *)args[i].c_str();
	}

	rdModel *model = LoadModel(argc,argv);
	setModel(model);
}
//_____________________________________________________________________________
/**
 * Construct a command line for LoadModel().
 */
void Investigation::
constructCommandLineForLoadModel(rdArray<string> &args)
{
	args.setSize(0);
	args.append(getName());

	if(_modelLibrary!="") {
		args.append("-ModelLibrary");
		args.append(_modelLibrary);
	}

	if(_modelFile!="") {
		args.append("-ModelFile");
		args.append(_modelFile);
	}

	if(_actuatorSetFile!="") {
		args.append("-Actuators");
		args.append(_actuatorSetFile); 
	}

	if(_contactForceSetFile!="") {
		args.append("-Contacts");
		args.append(_contactForceSetFile);
	}

	if(_paramsFile!="") {
		args.append("-Params");
		args.append(_paramsFile);
	}
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
void Investigation::
printResults(const char *aBaseName,const char *aDir,double aDT,
				 const char *aExtension)
{
	cout<<"Printing results of investigation "<<getName()<<".\n";
	_model->getAnalysisSet()->printResults(aBaseName,aDir,aDT,aExtension);
}
