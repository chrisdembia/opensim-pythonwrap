// rdAnalysis.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2001 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include "rdAnalysis.h"


using namespace std;
//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Default constructor.
 *
 * @param aModel Model on which the analysis is to be performed.
 */
rdAnalysis::rdAnalysis(rdModel *aModel):
	rdIntegCallback(aModel),
	_inDegrees(_inDegreesProp.getValueBool())
{
	
	setNull();

	// ON
	setOn(true);

	// NAME
	setName("Un-named analysis.");

	// DESCRIPTION
	setDescription("No description.");

	// MODEL
	_model = aModel;

}
//_____________________________________________________________________________
/**
 * Destructor.
 */
rdAnalysis::~rdAnalysis()
{

}
//_____________________________________________________________________________
/**
 * Construct an object from file.
 *
 * The object is constructed from the root element of the XML document.
 * The type of object is the tag name of the XML root element.
 *
 * @param aFileName File name of the document.
 */
rdAnalysis::rdAnalysis(const string &aFileName):
rdIntegCallback(aFileName),
_inDegrees(_inDegreesProp.getValueBool())
{
	setType("rdAnalysis");
	setNull();
	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Construct an object from an DOMElement.
 */
rdAnalysis::rdAnalysis(DOMElement *aElement):
rdIntegCallback(aElement),
_inDegrees(_inDegreesProp.getValueBool())
{
	setType("rdAnalysis");
	setNull();
	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * Copy constructors for all rdAnalysis's only copy the non-XML variable
 * members of the object; that is, the object's DOMnode and rdXMLDocument
 * are not copied but set to NULL.  The reason for this is that for the
 * object and all its derived classes to establish the correct connection
 * to the XML document nodes, the the object would need to reconstruct based
 * on the XML document not the values of the object's member variables.
 *
 * There are three proper ways to generate an XML document for an rdAnalysis:
 *
 * 1) Construction based on XML file (@see rdAnalysis(const char *aFileName)).
 * In this case, the XML document is created by parsing the XML file.
 *
 * 2) Construction by rdAnalysis(const rdXMLDocument *aDocument).
 * This constructor explictly requests construction based on an
 * XML document.  In this way the proper connection between an object's node
 * and the corresponding node within the XML document is established.
 * This constructor is a copy constructor of sorts because all essential
 * rdAnalysis member variables should be held within the XML document.
 * The advantage of this style of construction is that nodes
 * within the XML document, such as comments that may not have any
 * associated rdAnalysis member variable, are preserved.
 *
 * 3) A call to generateDocument().
 * This method generates an XML document for the rdAnalysis from scratch.
 * Only the essential document nodes are created (that is, nodes that
 * correspond directly to member variables.).
 *
 * @param aAnalysis Object to be copied.
 * @see rdAnalysis(const rdXMLDocument *aDocument)
 * @see rdAnalysis(const char *aFileName)
 * @see generateDocument()
 */
rdAnalysis::rdAnalysis(const rdAnalysis &aAnalysis):
rdIntegCallback(aAnalysis),
_inDegrees(_inDegreesProp.getValueBool())
{
	setType("rdAnalysis");
	setNull();
	*this = aAnalysis;
}

//_____________________________________________________________________________
/**
 * virtual copy constructor
 */
rdObject* rdAnalysis::
copy() const
{

	rdAnalysis *object = new rdAnalysis(*this);
	return(object);
}

//_____________________________________________________________________________
/**
 * virtual copy constructor from DOMElement
 */
rdObject* rdAnalysis::
copy(DOMElement *aElement) const
{
	rdAnalysis *object = new rdAnalysis(aElement);
	*object = *this;
	object->updateFromXMLNode();
	return(object);
}

//_____________________________________________________________________________
/**
 * Set all member variables to their null or default values.
 */
void rdAnalysis::
setNull()
{
	setupProperties();
	_inDegrees=true;
	_storageList.setMemoryOwner(false);
}
//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void rdAnalysis::setupProperties()
{
	_inDegreesProp.setName("InDegrees");
	_propertySet.append( &_inDegreesProp );
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
rdAnalysis& rdAnalysis::
operator=(const rdAnalysis &aAnalysis)
{
	// BASE CLASS
	rdIntegCallback::operator=(aAnalysis);

	// Data members
	_inDegrees = aAnalysis._inDegrees;

	return(*this);
}

//=============================================================================
// GET AND SET
//=============================================================================
//-----------------------------------------------------------------------------
// IN DEGREES
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set whether or not to write the output of angles in degrees.
 * This flag must be set before an analysis is performed to ensure that
 * the results are in the proper format.
 *
 * @param aTureFalse Output will be in degrees if "true" and in radians
 * if "false".
 */
void rdAnalysis::
setInDegrees(bool aTrueFalse)
{
	_inDegrees = aTrueFalse;
}
//_____________________________________________________________________________
/**
 * Get whether or not output of angles will be in degrees or radians.
 *
 * @return "true" if the output will be in degrees, "false" in radians.
 */
bool rdAnalysis::
getInDegrees() const
{
	return(_inDegrees);
}
//_____________________________________________________________________________
/**
 * set pointer to model to be analyzed.
 */

void rdAnalysis::
setModel(rdModel *aModel)
{
	// BASE CLASS
	rdIntegCallback::setModel(aModel);

	// SIDE EFFECTS


}
//-----------------------------------------------------------------------------
// COLUMN LABELS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the column labels for this analysis.
 *
 * The length of the column labels string should be 8191 characters or shorter.
 *
 * @param aLabels String of tab delimited labels.
 */
void rdAnalysis::
setColumnLabels(const char *aLabels)
{
	_labels = string(aLabels);
}
//_____________________________________________________________________________
/**
 * Get the columns labels of this analysis.
 *
 * @return Labels for this analysis.
 */
const char* rdAnalysis::
getColumnLabels() const
{
	return(_labels.c_str());
}


//=============================================================================
// ANALYSIS
//=============================================================================
//_____________________________________________________________________________
/**
 * Return whether or not to proceed with this analysis.
 * The analysis will not proceed (i.e., returns false) if either the
 * analysis is turned off or if aStep is not an even multiple of
 * the step interval set @see rdStepCallback.
 *
 * @return True or False.
 */
bool rdAnalysis::
proceed(int aStep)
{
	return(getOn() && ((aStep%_stepInterval)==0));
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
 *
 * @return -1 on error, 0 otherwise.
 */
int rdAnalysis::
printResults(const char *aBaseName,const char *aDir,double aDT,
				 const char *aExtension)
{
	printf("rdAnalysis.printResults: Printing results of analysis %s.\n",
		getName());
	return(0);
}

rdArrayPtrs<rdStorage>& rdAnalysis::getStorageList()
{
	return _storageList;
}
