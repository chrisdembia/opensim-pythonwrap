// Investigation.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include "Investigation.h"

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
	_outputPrecision(_outputPrecisionProp.getValueInt()),
	_ti(_tiProp.getValueDbl()),
	_tf(_tfProp.getValueDbl()),
	_maxSteps(_maxStepsProp.getValueInt()),
	_maxDT(_maxDTProp.getValueDbl()),
	_errorTolerance(_errorToleranceProp.getValueDbl()),
	_fineTolerance(_fineToleranceProp.getValueDbl()),
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
	_outputPrecision(_outputPrecisionProp.getValueInt()),
	_ti(_tiProp.getValueDbl()),
	_tf(_tfProp.getValueDbl()),
	_maxSteps(_maxStepsProp.getValueInt()),
	_maxDT(_maxDTProp.getValueDbl()),
	_errorTolerance(_errorToleranceProp.getValueDbl()),
	_fineTolerance(_fineToleranceProp.getValueDbl()),
	_analysisSet((rdAnalysisSet&)_analysisSetProp.getValueObj())
{
	setType("Investigation");
	setNull();
	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Construct from a DOMElement.
 */
Investigation::Investigation(DOMElement *aElement):
	rdObject(aElement),
	_outputPrecision(_outputPrecisionProp.getValueInt()),
	_ti(_tiProp.getValueDbl()),
	_tf(_tfProp.getValueDbl()),
	_maxSteps(_maxStepsProp.getValueInt()),
	_maxDT(_maxDTProp.getValueDbl()),
	_errorTolerance(_errorToleranceProp.getValueDbl()),
	_fineTolerance(_fineToleranceProp.getValueDbl()),
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
	_outputPrecision(_outputPrecisionProp.getValueInt()),
	_ti(_tiProp.getValueDbl()),
	_tf(_tfProp.getValueDbl()),
	_maxSteps(_maxStepsProp.getValueInt()),
	_maxDT(_maxDTProp.getValueDbl()),
	_errorTolerance(_errorToleranceProp.getValueDbl()),
	_fineTolerance(_fineToleranceProp.getValueDbl()),
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

	_model = 0;
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

	rdAnalysisSet *analysisSet = new rdAnalysisSet();
	_analysisSetProp.setValue(*analysisSet);
	_analysisSetProp.setName("analysis_set");
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
	_analysisSet = aInvestigation._analysisSet;
	_outputPrecision = aInvestigation._outputPrecision;
	_ti = aInvestigation._ti;
	_tf = aInvestigation._tf;
	_maxSteps = aInvestigation._maxSteps;
	_errorTolerance = aInvestigation._errorTolerance;
	_fineTolerance = aInvestigation._fineTolerance;

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
	//_analysisSet.setModel(_model);
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