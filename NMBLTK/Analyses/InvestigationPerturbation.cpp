// InvestigationPerturbation.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=============================================================================
// INCLUDES
//=============================================================================
#include "InvestigationPerturbation.h"
#include <NMBLTK/Tools/rdIO.h>
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
	_yFileName(_yFileNameProp.getValueStr())
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
	_yFileName(_yFileNameProp.getValueStr())
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
	_yFileName(_yFileNameProp.getValueStr())
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
	_yFileName(_yFileNameProp.getValueStr())
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
	_controlSet = 0;
	_copStore = 0;
	_qStore = 0;
	_uStore = 0;
	_yStore = 0;
}
//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void InvestigationPerturbation::setupProperties()
{
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


}

//_____________________________________________________________________________
/**
 * Construct the corrective springs.
 */
void InvestigationPerturbation::
constructCorrectiveSprings()
{





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
