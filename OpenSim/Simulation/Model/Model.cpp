// Model.cpp
// Authors: Frank C. Anderson, Peter Loan, Ayman Habib, Ajay Seth
/*
 * Copyright (c)  2006, Stanford University. All rights reserved. 
* Use of the OpenSim software in source form is permitted provided that the following
* conditions are met:
* 	1. The software is used only for non-commercial research and education. It may not
*     be used in relation to any commercial activity.
* 	2. The software is not distributed or redistributed.  Software distribution is allowed 
*     only through https://simtk.org/home/opensim.
* 	3. Use of the OpenSim software or derivatives must be acknowledged in all publications,
*      presentations, or documents describing work in which OpenSim or derivatives are used.
* 	4. Credits to developers may not be removed from executables
*     created from modifications of the source.
* 	5. Modifications of source code must retain the above copyright notice, this list of
*     conditions and the following disclaimer. 
* 
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
*  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
*  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
*  SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
*  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
*  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
*  OR BUSINESS INTERRUPTION) OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
*  WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

//=============================================================================
// INCLUDES
//=============================================================================
#include <iostream>
#include <string>
#include <math.h>
#include <OpenSim/Common/IO.h>
#include <OpenSim/Common/XMLDocument.h>
#include <OpenSim/Common/XMLNode.h>
#include "Model.h"
#include "Muscle.h"
#include "CoordinateSet.h"
#include "BodySet.h"
#include "AnalysisSet.h"
#include "ForceSet.h"
#include <OpenSim/Common/ScaleSet.h>
#include "Analysis.h"
#include "OpenSimForceSubsystem.h"
#include "ForceAdapter.h"
#include "Actuator.h"
#include <OpenSim/Common/Storage.h>
#include <OpenSim/Simulation/Model/MarkerSet.h>
#include <OpenSim/Simulation/Model/ContactGeometrySet.h>
#include <OpenSim/Simulation/Control/Controller.h>
#include <OpenSim/Simulation/SimbodyEngine/SimbodyEngine.h>
#include <OpenSim/Simulation/SimbodyEngine/CoordinateCouplerConstraint.h>
#include <OpenSim/Simulation/Control/ControlLinear.h>
#include <OpenSim/Simulation/Control/ControlLinearNode.h>
#include "SimTKcommon/internal/SystemGuts.h"

using namespace std;
using namespace OpenSim;
using namespace SimTK;
using SimTK::Mat33;

//=============================================================================
// STATICS
//=============================================================================


//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Default constructor.
 */
Model::Model() :
	_fileName("Unassigned"),
	_creditsStr(_creditsStrProp.getValueStr()),
	_publicationsStr(_publicationsStrProp.getValueStr()),
	_lengthUnitsStr(_lengthUnitsStrProp.getValueStr()),
	_forceUnitsStr(_forceUnitsStrProp.getValueStr()),
	_forceSetProp(PropertyObj("", ForceSet())),
	_forceSet((ForceSet&)_forceSetProp.getValueObj()),
    _gravity(_gravityProp.getValueDblVec3()),
    _bodySetProp(PropertyObj("", BodySet())),
    _bodySet((BodySet&)_bodySetProp.getValueObj()),
    _constraintSetProp(PropertyObj("", ConstraintSet())),
    _constraintSet((ConstraintSet&)_constraintSetProp.getValueObj()),
    _markerSetProp(PropertyObj("", MarkerSet())),
    _markerSet((MarkerSet&)_markerSetProp.getValueObj()),
    _contactGeometrySetProp(PropertyObj("", ContactGeometrySet())),
    _contactGeometrySet((ContactGeometrySet&)_contactGeometrySetProp.getValueObj()),
    _jointSet(JointSet()),
    _analysisSet(AnalysisSet()),
    _coordinateSet(CoordinateSet()),
    _controllerSet(ControllerSet()),
    _allControllersEnabled(true),
    _perturbActuatorForces(false),
    _system(NULL)
{
	setNull();
	setupProperties();
    _analysisSet.setMemoryOwner(false);
	createGroundBodyIfNecessary();
}
//_____________________________________________________________________________
/**
 * Constructor from an XML file
 */
Model::Model(const string &aFileName) :
	ModelComponent(aFileName, false),
	_fileName("Unassigned"),
	_creditsStr(_creditsStrProp.getValueStr()),
	_publicationsStr(_publicationsStrProp.getValueStr()),
	_lengthUnitsStr(_lengthUnitsStrProp.getValueStr()),
	_forceUnitsStr(_forceUnitsStrProp.getValueStr()),
	_forceSetProp(PropertyObj("", ForceSet())),
	_forceSet((ForceSet&)_forceSetProp.getValueObj()),
    _gravity(_gravityProp.getValueDblVec3()),
    _bodySetProp(PropertyObj("", BodySet())),
    _bodySet((BodySet&)_bodySetProp.getValueObj()),
    _constraintSetProp(PropertyObj("", ConstraintSet())),
    _constraintSet((ConstraintSet&)_constraintSetProp.getValueObj()),
    _markerSetProp(PropertyObj("", MarkerSet())),
    _markerSet((MarkerSet&)_markerSetProp.getValueObj()),
    _contactGeometrySetProp(PropertyObj("", ContactGeometrySet())),
    _contactGeometrySet((ContactGeometrySet&)_contactGeometrySetProp.getValueObj()),
    _jointSet(JointSet()),
    _analysisSet(AnalysisSet()),
    _coordinateSet(CoordinateSet()),
    _controllerSet(ControllerSet()),
    _allControllersEnabled(true),
    _perturbActuatorForces(false),
    _system(NULL)
{
	setNull();
	setupProperties();
	updateFromXMLNode();
	_fileName = aFileName;
    _analysisSet.setMemoryOwner(false);

	setup();
	cout << "Loaded model " << getName() << " from file " << getInputFileName() << endl;
}
//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aModel Model to be copied.
 */

Model::Model(const Model &aModel) :
   ModelComponent(aModel),
	_creditsStr(_creditsStrProp.getValueStr()),
	_publicationsStr(_publicationsStrProp.getValueStr()),
	_lengthUnitsStr(_lengthUnitsStrProp.getValueStr()),
	_forceUnitsStr(_forceUnitsStrProp.getValueStr()),
	_forceSetProp(PropertyObj("", ForceSet())),
	_forceSet((ForceSet&)_forceSetProp.getValueObj()),
    _gravity(_gravityProp.getValueDblVec3()),
    _bodySetProp(PropertyObj("", BodySet())),
    _bodySet((BodySet&)_bodySetProp.getValueObj()),
    _constraintSetProp(PropertyObj("", ConstraintSet())),
    _constraintSet((ConstraintSet&)_constraintSetProp.getValueObj()),
    _markerSetProp(PropertyObj("", MarkerSet())),
    _markerSet((MarkerSet&)_markerSetProp.getValueObj()),
    _contactGeometrySetProp(PropertyObj("", ContactGeometrySet())),
    _contactGeometrySet((ContactGeometrySet&)_contactGeometrySetProp.getValueObj()),
    _allControllersEnabled(true),
    _perturbActuatorForces(false),
    _system(NULL)
{
	//cout << "Construct copied model " <<  endl;
	// Throw exception if something wrong happened and we don't have a dynamics engine.
	setNull();
	setupProperties();
	copyData(aModel);

	setup();
}
//_____________________________________________________________________________
/**
 * Destructor.
 */
Model::~Model()
{
    //cout << "Deleted model " <<  getName() << endl;

	//std::cout << "Model destructor has been called" << endl;
}
//_____________________________________________________________________________
/**
 * Override default implementation by object to intercept and fix the XML node
 * underneath the model to match current version
 */
/*virtual*/
void Model::updateFromXMLNode()
{
	int documentVersion = getDocument()->getDocumentVersion();
	if ( documentVersion < XMLDocument::getLatestVersion()){
		cout << "Updating Model file to latest format..." << endl;
		// Version has to be 1.6 or later, otherwise assert
		if (_node!=NULL && documentVersion==10600){
			// Get node for DynamicsEngine
			DOMElement* enginesNode = XMLNode::GetFirstChildElementByTagName(_node,"DynamicsEngine");
			//Get node for SimbodyEngine
			if (enginesNode != 0){
				DOMElement* simbodyEngineNode = XMLNode::GetFirstChildElementByTagName(enginesNode,"SimbodyEngine");
				// Move all Children of simbodyEngineNode to be children of _node 
				// we'll keep inserting before enginesNode then remove it;
				if (simbodyEngineNode!= 0){
					for(DOMNode *child=simbodyEngineNode->getFirstChild(); child!=NULL;
												child=child->getNextSibling()) {
						DOMElement* childElement = (DOMElement*)child;
						//const XMLCh *   nodeName = childElement->getTagName();
						//char *str1 = XMLString::transcode(nodeName);
						//cout << "Moving child " << std::string(str1) << endl;
						_node->insertBefore(childElement->cloneNode(true), enginesNode);
					}
				}
				XMLNode::RemoveChildren(enginesNode);
				_node->removeChild(enginesNode);
			}
			// Now handling the rename of ActuatorSet to ForceSet
			DOMElement* actuatorsNode = XMLNode::GetFirstChildElementByTagName(_node,"ActuatorSet");
			if (actuatorsNode != 0) {
				DOMElement* forcesNode = XMLNode::CreateDOMElement(getDocument()->getDOMDocument(), "ForceSet");
				DOMNodeList * children = actuatorsNode->getChildNodes();
				for (unsigned int i=0; i<children->getLength(); i++){
					DOMNode* nextChild = children->item(i);
					//actuatorsNode->removeChild(nextChild);
					forcesNode->appendChild(nextChild->cloneNode(true));
				}
				_node->insertBefore(forcesNode, actuatorsNode);
				_node->removeChild(actuatorsNode);
			}
		}
	}
	// Call base class now assuming _node has been corrected for current version
	Object::updateFromXMLNode();
    
	setDefaultProperties();
}
//_____________________________________________________________________________
/**
 * Copy this Model and return a pointer to the copy.
 * The copy constructor for this class is used.
 *
 * @return Pointer to a copy of this Model.
 */
Object* Model::copy() const
{
	Model *model = new Model(*this);
	return(model);
}


//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Copy the member variables of the model.
 *
 * @param aModel model to be copied
 */
void Model::copyData(const Model &aModel)
{
	_fileName = aModel._fileName;
	_creditsStr = aModel._creditsStr;
	_publicationsStr = aModel._publicationsStr;
	_lengthUnits = aModel._lengthUnits;
	_forceUnits = aModel._forceUnits;
	_lengthUnitsStr = aModel._lengthUnitsStr;
	_forceUnitsStr = aModel._forceUnitsStr;
	_forceSet = aModel._forceSet;
	_analysisSet = aModel._analysisSet;
	_tNormConst = aModel._tNormConst;
    _gravity = aModel._gravity;
    _bodySet=aModel._bodySet;
    _constraintSet=aModel._constraintSet;
	_controllerSet=aModel._controllerSet;
    _markerSet = aModel._markerSet;
    _contactGeometrySet = aModel._contactGeometrySet;
	_builtOK = aModel._builtOK; //??

}
//_____________________________________________________________________________
/**
 * Set the values of all data members to an appropriate "null" value.
 */
void Model::setNull()
{
	setType("Model");

	_tNormConst = 1.0;
	_builtOK = false;
    _allControllersEnabled = true;
	_perturbActuatorForces = false,
    _groundBody = NULL;

    _system = NULL;
    _matter = NULL;
    _forceSubsystem = NULL;
    _userForceElements = NULL;
    _contactSubsystem = NULL;
    _gravityForce = NULL;

}
//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 *
 */
void Model::setupProperties()
{
	_creditsStrProp.setName("credits");
	_propertySet.append(&_creditsStrProp);

	_publicationsStrProp.setName("publications");
	_propertySet.append(&_publicationsStrProp);

	_forceSetProp.setName("ForceSet");
	_propertySet.append(&_forceSetProp);

	_lengthUnitsStrProp.setName("length_units");
	_propertySet.append(&_lengthUnitsStrProp);

	_forceUnitsStrProp.setName("force_units");
	_propertySet.append(&_forceUnitsStrProp);

   const SimTK::Vec3 defaultGravity(0.0, -9.80665, 0.0);
    _gravityProp.setComment("Acceleration due to gravity.");
    _gravityProp.setName("gravity");
    _gravityProp.setValue(defaultGravity);
    _propertySet.append(&_gravityProp);

    // Note: PropertyObj tag names come from the object's type (e.g. _bodySetProp below will automatically be associated with <BodySet> tag)
    // don't need to call _bodySetProp.setName()...
    _bodySetProp.setComment("Bodies in the model.");
    _propertySet.append(&_bodySetProp);

    _constraintSetProp.setComment("Constraints in the model.");
    _propertySet.append(&_constraintSetProp);

    _markerSetProp.setComment("Markers in the model.");
    _propertySet.append(&_markerSetProp);

    _contactGeometrySetProp.setComment("ContactGeometry objects in the model.");
    _propertySet.append(&_contactGeometrySetProp);
}

SimTK::State& Model::initSystem() 
{
    setup();
	createSystem();
    getSystem().realizeTopology();
    SimTK::State& s = getSystem().updDefaultState();
	// The folllowing line is commented out as it removes all forces that were
	// added to the system during realizeTopology() 
    //_matter->setUseEulerAngles(s, true);

    getSystem().realizeModel(s);
	//std::cout << s.toString() << endl;

    initState(s);
    getSystem().realize(s, Stage::Position );
    _analysisSet.setModel(*this);

    updControllerSet().setActuators(updActuators());
    //updControllerSet().constructStorage();

	// Satisfy the constraints.
	getSimbodyEngine().projectConfigurationToSatisfyConstraints(s, 1e-8);

	 return(s);
}

void Model::invalidateSystem()
{
    if (_system != NULL)
        _system->getSystemGuts().invalidateSystemTopologyCache();
}
//_____________________________________________________________________________
/**
 * Create the multibody system.
 * 
 */
void Model::createSystem()
{
    if (_system != NULL)
    {
        // Delete the old system.
        delete _matter;
        delete _forceSubsystem;
        delete _userForceElements;
        delete _contactSubsystem;
        delete _gravityForce;
        delete _system;
    }

    // create system 
    _system = new SimTK::MultibodySystem;
    _matter = new SimTK::SimbodyMatterSubsystem(*_system);
    _forceSubsystem = new OpenSimForceSubsystem( *_system, this );
    _userForceElements = new SimTK::GeneralForceSubsystem(*_system);
    _contactSubsystem = new SimTK::GeneralContactSubsystem(*_system);
    _gravityForce = new SimTK::Force::Gravity(*_userForceElements,*_matter,_gravity);

    // Let all the ModelComponents add their parts to the System.
    static_cast<const ModelComponentSet<Body>&>(getBodySet()).createSystem(*_system);
    
	static_cast<const ModelComponentSet<Joint>&>(getJointSet()).createSystem(*_system);
	for(int i=0;i<getBodySet().getSize();i++) {
		OpenSim::Body& body = getBodySet().get(i);
		MobilizedBodyIndex idx(body.getIndex());
        if (!idx.isValid() && body.getName()!= "ground")   
			throw Exception("Body: "+body.getName()+" has no Joint... Model initialization aborted.");
	}

    static_cast<const ModelComponentSet<Constraint>&>(getConstraintSet()).createSystem(*_system);
    static_cast<const ModelComponentSet<ContactGeometry>&>(getContactGeometrySet()).createSystem(*_system);


    // Add extra constraints for coordinates.
	static_cast<const ModelComponentSet<Coordinate>&>(getCoordinateSet()).createSystem(*_system);

    
    static_cast<const ModelComponentSet<Force>&>(getForceSet()).createSystem(*_system);

	// controllers perform setup that requires a completed system (ie. all generalized coordinates )
    updControllerSet().setupSystem( *_system );
    
	// controllers add their parts to the System. 
    static_cast<const ModelComponentSet<Controller>&>(getControllerSet()).createSystem(*_system);
}

//_____________________________________________________________________________
/**
 * Add a body to the Model.
 */
void Model::addBody(OpenSim::Body *aBody) 
{
	updBodySet().append(aBody);
	updBodySet().setup(*this);
	updJointSet().populate(*this);
	updCoordinateSet().populate(*this);
}

//_____________________________________________________________________________
/**
 * Add a constraint to the Model.
 */
void Model::addConstraint(OpenSim::Constraint *aConstraint) 
{
	updConstraintSet().append(aConstraint);
	updConstraintSet().setup(*this);
}

//_____________________________________________________________________________
/**
 * Add a force to the Model.
 */
void Model::addForce(OpenSim::Force *aForce) 
{
	updForceSet().append(aForce);
	updForceSet().setup(*this);
}

//_____________________________________________________________________________
/**
 * Add a contact geometry to the Model.
 */
void Model::addContactGeometry(OpenSim::ContactGeometry *aContactGeometry) 
{
	updContactGeometrySet().append(aContactGeometry);
	updContactGeometrySet().setup(*this);
}

//_____________________________________________________________________________
/**
 * Add a controller to the Model.
 */
void Model::addController(Controller *aController) 
{
	if (aController ) {
	   updControllerSet().append(aController);
	   updControllerSet().setup(*this);
    }
}
//_____________________________________________________________________________
/**
 * Perform some set up functions that happen after the
 * object has been deserialized. This method is
 * not yet designed to be called after a model has been
 * copied.
 */
void Model::setup()
{
	createGroundBodyIfNecessary();

	// Update model components, not that Joints and Coordinates
	// belong to Bodies, alough model lists are assembled for convenience
	updBodySet().setup(*this);

    // Populate lists of model joints and coordinates according to the Bodies
	// setup here who own the Joints which in turn own the model's Coordinates
	// this list of Coordinates is now available for setting up constraints and forces
	updJointSet().populate(*this);
    updCoordinateSet().populate(*this);

    updConstraintSet().setup(*this);
    updMarkerSet().setup(*this);
    updContactGeometrySet().setup(*this);
	updForceSet().setup(*this);
	updControllerSet().setup(*this);

	// TODO: Get rid of the SimbodyEngine
	updSimbodyEngine().setup(*this);



	// The following code should be replaced by a more robust
	// check for problems while creating the model.
	if ( getNumBodies() > 0) {
		_builtOK = true;
	}
}

/**
 * Create a ground body if necessary.
 */
void Model::createGroundBodyIfNecessary()
{
    const std::string SimbodyGroundName = "ground";

	// See if the ground body already exists.
	// The ground body is assumed to have the name simbodyGroundName.
	int size = getBodySet().getSize();
	Body *ground=NULL;
	for(int i=0; i<size; i++) {
		Body& body = getBodySet().get(i);
		if(body.getName() == SimbodyGroundName) {
			ground = &body;
			break;
		}
	}

	if(ground==NULL) {
		ground = new Body();
		_bodySet.append(ground);
	}
	// Set member variables
	ground->setName(SimbodyGroundName);
    ground->setMass(0.0);
	ground->setMassCenter(Vec3(0.0));
	_groundBody = ground;
}


//_____________________________________________________________________________
/**
 * Perform some clean up functions that are normally done from the destructor
 * however this gives the GUI a way to proactively do the cleaning without waiting for garbage
 * collection to do the actual cleanup.
 */
void Model::cleanup()
{
	_forceSet.setSize(0);	
}

void Model::setDefaultProperties()
{
	if (_creditsStrProp.getUseDefault()){
		_creditsStr = "Model authors names..";
	}
	if (_publicationsStrProp.getUseDefault()){
		_publicationsStr = "List of publications related to model...";
	}

	// Initialize the length and force units from the strings specified in the model file.
	// If they were not specified, use meters and Newtons.

    if (_lengthUnitsStrProp.getUseDefault()){
		_lengthUnits = Units(Units::Meters);
		_lengthUnitsStr = _lengthUnits.getLabel();
	}
	else
		_lengthUnits = Units(_lengthUnitsStr);

	if (_forceUnitsStrProp.getUseDefault()){
		_forceUnits = Units(Units::Newtons);
		_forceUnitsStr = _forceUnits.getLabel();
	}
	else
		_forceUnits = Units(_forceUnitsStr);
}

void Model::initState(SimTK::State& state) const
{
    _bodySet.initState(state);
    _constraintSet.initState(state);
    _contactGeometrySet.initState(state);
    _jointSet.initState(state);
    _forceSet.initState(state);
}

void Model::setDefaultsFromState(const SimTK::State& state)
{
    _bodySet.setDefaultsFromState(state);
    _constraintSet.setDefaultsFromState(state);
    _contactGeometrySet.setDefaultsFromState(state);
    _jointSet.setDefaultsFromState(state);
    _forceSet.setDefaultsFromState(state);
}

void Model::equilibrateMuscles(SimTK::State& state)
{
    for (int i = 0; i < _forceSet.getSize(); i++)
    {
        Muscle* muscle = dynamic_cast<Muscle*>(&_forceSet.get(i));
        if (muscle != NULL)
            muscle->equilibrate(state);
    }
}

//_____________________________________________________________________________
/**
 * Register the types used by this class.
void Model::registerTypes()
{
	// now handled by RegisterTypes_osimSimulation()
}
 */


//=============================================================================
// OPERATORS
//=============================================================================
//_____________________________________________________________________________
/**
 * Assignment operator.
 *
 * @return Reference to this object.
 */
Model& Model::operator=(const Model &aModel)
{
	// BASE CLASS
	Object::operator=(aModel);

	// Class Members


	copyData(aModel);

	setup();

	return(*this);
}


//=============================================================================
// GRAVITY
//=============================================================================
//_____________________________________________________________________________
/**
 * Get the gravity vector in the gloabl frame.
 *
 * @return the XYZ gravity vector in the global frame is returned here.
 */
SimTK::Vec3 Model::getGravity() const
{
	if(_gravityForce)
		_gravity = _gravityForce->getDefaultGravityVector();

	return _gravity;
}
//_____________________________________________________________________________
/**
 * Set the gravity vector in the gloabl frame.
 *
 * @param aGrav the XYZ gravity vector
 * @return Whether or not the gravity vector was successfully set.
 */
bool Model::setGravity(const SimTK::Vec3& aGrav)
{
	_gravity = aGrav;

	if(_gravityForce)
		_gravityForce->setDefaultGravityVector(aGrav);

	return true;
}


//=============================================================================
// NUMBERS
//=============================================================================
//_____________________________________________________________________________
/**
 * Get the number of markers in the model.
 *
 * @return Number of markers.
 */
int Model::getNumMarkers() const 
{ 
    return _markerSet.getSize(); 
}
/**
 * Get the number of ContactGeometry objects in the model.
 *
 * @return Number of ContactGeometries.
 */
int Model::getNumContactGeometries() const
{
	return _contactGeometrySet.getSize();
}
int Model::getNumStates() const 
{
    return( _system->getDefaultState().getNY() );
}

/**
 * Get the number of Muscle state variabls in the model.
 *
 * @return Number of MuscleStates.
 */

int Model::getNumMuscleStates() const {

	int n = 0;
	for(int i=0;i<_forceSet.getSize();i++){
        Muscle *mus = dynamic_cast<Muscle*>( &_forceSet.get(i) );
		if(mus!=NULL) {
			n += mus->getNumStateVariables();
		}
	}
	return(n);
}
//_____________________________________________________________________________
/**
 * Get the total number of bodies in the model.
 *
 * @return Number of bodies.
 */
int Model::getNumBodies() const
{
	return  _bodySet.getSize();
}
//_____________________________________________________________________________
/**
 * Get the total number of joints in the model.
 *
 * @return Number of joints.
 */
int Model::getNumJoints() const
{
	return  _jointSet.getSize();
}
//_____________________________________________________________________________
/**
 * Get the total number of coordinates in the model.
 *
 * @return Number of coordinates.
 */
int Model::getNumCoordinates() const
{
	return _coordinateSet.getSize();
}

/**
 * Get the total number of coordinates = number of speeds in the model.
 *
 * @return Number of coordinates.
 */
int Model::getNumSpeeds() const
{
	return _coordinateSet.getSize();
}
//_____________________________________________________________________________
/**
 * Get the subset of Forces in the model which are actuators
 *
 * @return The set of Actuators
 */
const Set<Actuator>& Model::getActuators() const
{
	return _forceSet.getActuators();
}
Set<Actuator>& Model::updActuators() 
{
	return _forceSet.updActuators();
}


//_____________________________________________________________________________
/**
 * Get the number of analyses in the model.
 *
 * @return The number of analyses
 */
int Model::getNumAnalyses() const
{
    return _analysisSet.getSize();
}

//_____________________________________________________________________________

//=============================================================================
// TIME NORMALIZATION CONSTANT
//=============================================================================
//_____________________________________________________________________________
/**
 * Set the constant by which time is normalized.
 *
 * The normalization constant must be greater than or equal to the constant
 * Zero.
 *
 * @param Time normalization constant.
 */
void Model::setTimeNormConstant(double aNormConst)
{
	_tNormConst = aNormConst;

	if(_tNormConst < Zero) _tNormConst = Zero; 
}
//_____________________________________________________________________________
/**
 * Get the constant by which time is normalized.
 *
 * By default, the time normalization constant is 1.0.
 *
 * @return Current time normalization constant.
 */
double Model::getTimeNormConstant() const
{
	return _tNormConst;
}



//=============================================================================
// STATES
//=============================================================================
//_____________________________________________________________________________
/**
 * Get the names of the states.
 *
 * @param rStateNames Array of state names..
 */
void Model::getStateNames(OpenSim::Array<string> &rStateNames) const
{
	getCoordinateSet().getNames(rStateNames);
	getCoordinateSet().getSpeedNames(rStateNames);
	getForceSet().getStateVariableNames(rStateNames);
}

//=============================================================================
// INITIAL STATES
//=============================================================================

void Model::setInitialTime( double ti ) {
	    _system->updDefaultState().updTime() = ti;
}

//_____________________________________________________________________________
/**
 * Add an analysis to the model.
 *
 * @param aAnalysis pointer to the analysis to add
 */
void Model::addAnalysis(Analysis *aAnalysis)
{
	if (aAnalysis )
	{
//		aAnalysis->setModel(this);
		_analysisSet.append(aAnalysis);
	}
}
//_____________________________________________________________________________
/**
 * Remove an analysis from the model
 *
 * @param aAnalysis Pointer to the analysis to remove.
 * If deleteIt is true (default) the Analysis object itself is destroyed
 * else only removed from te list which is the desired behavior when the Analysis 
 * is created from the GUI.
 */
void Model::removeAnalysis(Analysis *aAnalysis, bool deleteIt)
{
	// CHECK FOR NULL
	if(aAnalysis==NULL) {
		cout << "Model.removeAnalysis:  ERROR- NULL analysis.\n" << endl;
	}
	if (!deleteIt){
		bool saveStatus = _analysisSet.getMemoryOwner();
		_analysisSet.setMemoryOwner(false);
		_analysisSet.remove(aAnalysis);
		_analysisSet.setMemoryOwner(saveStatus);
	}
	else 
		_analysisSet.remove(aAnalysis);
}

//_____________________________________________________________________________
/**
 * Remove a controller from the model
 *
 * @param aController Pointer to the controller to remove.
 */
void Model::removeController(Controller *aController)
{
	// CHECK FOR NULL
	if(aController==NULL) {
		cout << "Model.removeController:  ERROR- NULL controller.\n" << endl;
	}

	_controllerSet.remove(aController);
}

//_____________________________________________________________________________
/**
//_____________________________________________________________________________
/**
 * Compute values for the auxiliary states (i.e., states other than the
 * generalized coordinates and speeds) that are in quasi-static equilibrium.
 * The auxiliary states usually belong to the actuators (e.g., muscle
 * activation and muscle fiber length).  The equilibrium computations
 * are passed on to the owner of the the states.
 *
 * This methods is useful for computing initial conditions for a simulation
 * or for computing torque-angle curves, for example.
 *
 * @param rY Array of states. The values sent in are used as the initial
 * guess for equilibrium. The values returned are those that satisfy
 * equilibrium.
 */
void Model::
computeEquilibriumForAuxiliaryStates( SimTK::State& s)
{

    _system->realize(s, SimTK::Stage::Velocity );

	// COMPUTE EQUILIBRIUM STATES
	_forceSet.computeEquilibrium(s);

}


//==========================================================================
// OPERATIONS
//==========================================================================
//--------------------------------------------------------------------------
// SCALE
//--------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Scale the model
 *
 * @param aScaleSet the set of XYZ scale factors for the bodies
 * @param aFinalMass the mass that the scaled model should have
 * @param aPreserveMassDist whether or not the masses of the
 *        individual bodies should be scaled with the body scale factors.
 * @return Whether or not scaling was successful.
 */
bool Model::scale(SimTK::State& s, const ScaleSet& aScaleSet, double aFinalMass, bool aPreserveMassDist)
{
	int i;

	// 1. Save the current pose of the model, then put it in a
	//    default pose, so pre- and post-scale muscle lengths
	//    can be found.
    SimTK::Vector savedConfiguration = s.getY();
	applyDefaultConfiguration(s );
	// 2. For each Actuator, call its preScale method so it
	//    can calculate and store its pre-scale length in the
	//    current position, and then call its scale method to
	//    scale all of the muscle properties except tendon and
	//    fiber length.
	for (i = 0; i < _forceSet.getSize(); i++)
	{
        Actuator* act = dynamic_cast<Actuator*>(&_forceSet.get(i));
        if( act ) {
 		    act->preScale(s, aScaleSet);
		    act->scale(s, aScaleSet);
        }
	}
	// 3. Scale the rest of the model
	bool returnVal = updSimbodyEngine().scale(s, aScaleSet, aFinalMass, aPreserveMassDist);

	// 4. If the dynamics engine was scaled successfully,
	//    call each SimmMuscle's postScale method so it
	//    can calculate its post-scale length in the current
	//    position and then scale the tendon and fiber length
	//    properties.
	
	
	if (returnVal)
	{
		initSystem();	// This crashes now trying to delete the old matterSubsystem
    	updSimbodyEngine().setup(*this);
	    getSystem().realizeTopology();
		SimTK::State& newState = getSystem().updDefaultState();
	    getSystem().realize( newState, SimTK::Stage::Velocity);

		for (i = 0; i < _forceSet.getSize(); i++) {
            Actuator* act = dynamic_cast<Actuator*>(&_forceSet.get(i));
            if( act ) {
	 		    act->postScale(newState, aScaleSet);
            }
        }

		// 5. Put the model back in whatever pose it was in.
		
        newState.updY() = savedConfiguration;
		getSystem().realize( newState, SimTK::Stage::Velocity );
	}

    return returnVal;
}


//=============================================================================
// PRINT
//=============================================================================
//_____________________________________________________________________________
/**
 * Print some basic information about the model.
 *
 * @param aOStream Output stream.
 */
void Model::printBasicInfo(std::ostream &aOStream) const
{
	aOStream<<"             MODEL: "<<getName()<<std::endl;
	aOStream<<"            forces: "<<getForceSet().getSize()<<std::endl;
	aOStream<<"          analyses: "<<getNumAnalyses()<<std::endl;
	aOStream<<"            bodies: "<<getBodySet().getSize()<<std::endl;
	aOStream<<"            joints: "<<((OpenSim::Model*)this)->getJointSet().getSize()<<std::endl;
	aOStream<<"           markers: "<<getMarkerSet().getSize()<<std::endl;
}
//_____________________________________________________________________________
/**
 * Print detailed information about the model.
 *
 * @param aOStream Output stream.
 */
void Model::printDetailedInfo(const SimTK::State& s, std::ostream &aOStream) const
{
	//int i;

	aOStream << "MODEL: " << getName() << std::endl;

	aOStream << "\nANALYSES (" << getNumAnalyses() << ")" << std::endl;
	for (int i = 0; i < _analysisSet.getSize(); i++)
		aOStream << "analysis[" << i << "] = " << _analysisSet.get(i).getName() << std::endl;

	aOStream << "\nBODIES (" << getNumBodies() << ")" << std::endl;
	const BodySet& bodySet = getBodySet();
	for(int i=0; i < bodySet.getSize(); i++) {
		const OpenSim::Body& body = bodySet.get(i);
		aOStream << "body[" << i << "] = " << body.getName();
		aOStream << " (mass: "<<body.getMass()<<")";
		Mat33 inertia;
		body.getInertia(inertia);
		aOStream << " (inertia:";
		for(int j=0; j<3; j++) for(int k=0; k<3; k++) aOStream<<" "<<inertia[j][k];
		aOStream << ")"<<endl;
	}

    int j = 0;
	aOStream << "\nACTUATORS (" << getActuators().getSize() << ")" << std::endl;
	for (int i = 0; i < getActuators().getSize(); i++) {
		 aOStream << "actuator[" << j << "] = " << getActuators().get(i).getName() << std::endl;
         j++;
	}

	aOStream << "numStates = " << s.getNY() << std::endl;
	aOStream << "numCoordinates = " << getNumCoordinates() << std::endl;
	aOStream << "numSpeeds = " << getNumSpeeds() << std::endl;
	aOStream << "numActuators = " << getActuators().getSize() << std::endl;
	aOStream << "numBodies = " << getNumBodies() << std::endl;
	aOStream << "numConstraints = " << getConstraintSet().getSize() << std::endl;
	;

	/*
	int n;
	aOStream<<"MODEL: "<<getName()<<std::endl;

	n = getNumBodies();
	aOStream<<"\nBODIES ("<<n<<")" << std::endl;
	for(i=0;i<n;i++) aOStream<<"body["<<i<<"] = "<<getBodyName(i)<<std::endl;

	n = getNQ();
	aOStream<<"\nGENERALIZED COORDINATES ("<<n<<")" << std::endl;
	for(i=0;i<n;i++) aOStream<<"q["<<i<<"] = "<<getCoordinateName(i)<<std::endl;

	n = getNU();
	aOStream<<"\nGENERALIZED SPEEDS ("<<n<<")" << std::endl;
	for(i=0;i<n;i++) aOStream<<"u["<<i<<"] = "<<getSpeedName(i)<<std::endl;

	n = getNA();
	aOStream<<"\nACTUATORS ("<<n<<")" << std::endl;
	for(i=0;i<n;i++) aOStream<<"actuator["<<i<<"] = "<<getActuatorName(i)<<std::endl;

	n = getNP();
	aOStream<<"\nCONTACTS ("<<n<<")" << std::endl;

*/
	Array<string> stateNames("");
	getStateNames(stateNames);
	aOStream<<"\nSTATES ("<<stateNames.getSize()<<")"<<std::endl;
	for(int i=0;i<s.getNY();i++) aOStream<<"y["<<i<<"] = "<<stateNames[i]<<std::endl;
}

//____________________________________________________________________________
/**
 * get pointer to MultibodySystem 
 *
 * @param state SimTK::State 
 */
SimTK::MultibodySystem& Model::
getSystem()  const {
   return(*_system);
}
//____________________________________________________________________________
/**
 * set pointer to MultibodySystem
 * @param mbs pointer to a SimTK::MultibodySystem 
 */
void Model::
setSystem( SimTK::MultibodySystem* mbs ) {
   _system = mbs;
   return;

}

//--------------------------------------------------------------------------
// CONFIGURATION
//--------------------------------------------------------------------------

//_____________________________________________________________________________
/**
 * Apply the default configuration to the model.  This means setting the
 * generalized coordinates and spees to their default values.
 */
void Model::applyDefaultConfiguration(SimTK::State& s)
{
	int i;
	
	// Coordinates
	int ncoords = getCoordinateSet().getSize();

	for(i=0; i<ncoords; i++) {
		Coordinate& coord = getCoordinateSet().get(i);
		coord.setValue(s, coord.getDefaultValue(), false);
		coord.setSpeedValue(s, coord.getDefaultSpeedValue());
	}

	// Satisfy the constraints.
	getSimbodyEngine().projectConfigurationToSatisfyConstraints(s, 1e-8);
}

/* Enforce the coordinate coupler constraints. This should be done before
 * calling a Simbody function to project the constraints so that the values
 * of the dependent coordinates are already at their proper values. This
 * prevents the projection from changing the independent coordinate values
 * to satisfy the constraints.
 */
void Model::enforceCoordinateCouplerConstraints(SimTK::State& s) const
{
	for (int i=0; i<getConstraintSet().getSize(); i++) {
		Constraint& aConstraint = getConstraintSet().get(i);
		if (aConstraint.getType() == "CoordinateCouplerConstraint") {
			CoordinateCouplerConstraint& coupler = dynamic_cast<CoordinateCouplerConstraint&>(aConstraint);
			if (coupler.isDisabled(s)) continue;
			const Array<string> indNames = coupler.getIndependentCoordinateNames();
			// Build a vector of the independent coordinate values and use it to calculate
			// the desired value of the dependent coordinate.
			SimTK::Vector indValues(indNames.getSize());
			for (int k=0; k<indNames.getSize(); k++) {
				const Coordinate& ind = getCoordinateSet().get(indNames.get(k));
				indValues[k] = ind.getValue(s);
			}
			double desiredValue = coupler.getFunction().calcValue(indValues);
			const string& depName = coupler.getDependentCoordinateName();
			const Coordinate& dep = getCoordinateSet().get(depName);
			dep.setValue(s, desiredValue, false);
		}
	}
}


//--------------------------------------------------------------------------
// MARKERS
//--------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Write an XML file of all the markers in the model.
 *
 * @param aFileName the name of the file to create
 */
void Model::writeMarkerFile(const string& aFileName) const
{
	_markerSet.print(aFileName);
}

//_____________________________________________________________________________
/**
 * Replace all markers in the model with the ones in the passed-in marker set.
 *
 * @param aMarkerSet The new marker set.
 * @return Number of markers that were successfully added to the model.
 */
int Model::replaceMarkerSet(const SimTK::State& s, MarkerSet& aMarkerSet)
{
	int i, numAdded = 0;

	// First remove all existing markers from the model.
	_markerSet.clearAndDestroy();
	_markerSetProp.setUseDefault(false);

	// Now add the markers from aMarkerSet whose body names match bodies in the engine.
	for (i = 0; i < aMarkerSet.getSize(); i++)
	{
		// Eran: we make a *copy* since both _markerSet and aMarkerSet own their elements (so they will delete them)
		Marker* marker = (Marker*)aMarkerSet.get(i).copy();
		const string* bodyName = marker->getBodyName();
		if (getBodySet().contains(*bodyName))
		{
    		OpenSim::Body& body = updBodySet().get(*bodyName);
			marker->changeBody(body);
			_markerSet.append(marker);
			numAdded++;
		}
	}

	cout << "Replaced marker set in model " << getName() << endl;
	return numAdded;
}

//_____________________________________________________________________________
/**
 * Update all markers in the model with the ones in the
 * passed-in marker set. If the marker does not yet exist
 * in the model, it is added.
 *
 * @param aMarkerSet set of markers to be updated/added
 */
void Model::updateMarkerSet(MarkerSet& aMarkerSet)
{
	_markerSetProp.setUseDefault(false);
	for (int i = 0; i < aMarkerSet.getSize(); i++)
	{
		Marker& updatingMarker = aMarkerSet.get(i);
		const string* updatingBodyName = updatingMarker.getBodyName();

		/* If there is already a marker in the model with that name,
		 * update it with the parameters from the updating marker,
		 * moving it to a new body if necessary.
		 */
		if (updMarkerSet().contains(updatingMarker.getName()))
		{
    		Marker& modelMarker = updMarkerSet().get(updatingMarker.getName());
			/* If the updating marker is on a different body, delete the
			 * marker from the model and add the updating one (as long as
			 * the updating marker's body exists in the model).
			 */
			if (updatingBodyName &&
				 modelMarker.getBody().getName() != *updatingBodyName)
			{
				_markerSet.remove(&modelMarker);
				// Eran: we append a *copy* since both _markerSet and aMarkerSet own their elements (so they will delete them)
				_markerSet.append((Marker*)updatingMarker.copy());
			}
			else
			{
				modelMarker.updateFromMarker(updatingMarker);
			}
		}
		else
		{
			/* The model does not contain a marker by that name. If it has
			 * a body by that name, add the updating marker to the markerset.
			 */
			// Eran: we append a *copy* since both _markerSet and aMarkerSet own their elements (so they will delete them)
			if (updatingBodyName && getBodySet().contains(*updatingBodyName))
				_markerSet.append((Marker*)updatingMarker.copy());
		}
	}

	// Todo_AYMAN: We need to call setup again to make sure the _body pointers are up to date; but
	// note that we've already called setup before so we need to make sure the setup() function
	// supports getting called multiple times
	for (int i = 0; i < _markerSet.getSize(); i++)
		_markerSet.get(i).setup(*this);

	cout << "Updated markers in model " << getName() << endl;
}

//_____________________________________________________________________________
/**
 * Remove all markers from the model that are not in the passed-in list.
 *
 * @param aMarkerNames array of marker names not to be deleted
 * @return Number of markers deleted
 *
 * @Todo_AYMAN make sure visuals adjust as well
 */
int Model::deleteUnusedMarkers(const OpenSim::Array<string>& aMarkerNames)
{
	int i, numDeleted = 0;

	for (i = 0; i < _markerSet.getSize(); )
	{
		int index = aMarkerNames.findIndex(_markerSet.get(i).getName());
		if (index < 0)
		{
			// Delete the marker, but don't increment i or else you'll
			// skip over the marker right after the deleted one.
			_markerSet.get(i).removeSelfFromDisplay();
			_markerSet.remove(i);
			numDeleted++;
		}
		else
		{
			i++;
		}
	}

	cout << "Deleted " << numDeleted << " unused markers from model " << getName() << endl;

	return numDeleted;
}

/**
 ** Get a flat list of Joints contained in the model
 ** 
 **/
JointSet& Model::updJointSet()
{
    return _jointSet;
}

const JointSet& Model::getJointSet()
{

    return _jointSet;
}

/**
 * Get the body that is being used as ground.
 *
 * @return Pointer to the ground body.
 */
OpenSim::Body& Model::getGroundBody() const
{
	assert(_groundBody);
	return *_groundBody;
}


    //--------------------------------------------------------------------------
    // CONTROLS
    //--------------------------------------------------------------------------
const ControllerSet& Model::getControllerSet() const{
    return(_controllerSet);
}
ControllerSet& Model::updControllerSet() {
    return(_controllerSet);
}
void Model::storeControls( const SimTK::State& s, int step ) {
    _controllerSet.storeControls(s, step);
    return;
}
void Model::printControlStorage(const string& fileName ) const {
    _controllerSet.printControlStorage(fileName);
}
bool Model::getAllControllersEnabled() const{
  return( _allControllersEnabled );
}
void Model::setAllControllersEnabled( bool enabled ) {
    _allControllersEnabled = enabled;
}
/**
 * Model::formStateStorage is intended to take any storage and populate stateStorage.
 * stateStorage is supposed to be a Storage with labels identical to those obtained by calling 
 * Model::getStateNames(). Columns/entries found in the "originalStorage" are copied to the 
 * output statesStorage. Entries not found are populated with 0s.
 */
void Model::formStateStorage(const Storage& originalStorage, Storage& statesStorage)
{
	Array<string> rStateNames;
	getStateNames(rStateNames);
    int numStates = getNumStates();
	// make sure same size, otherwise warn
	if (originalStorage.getSmallestNumberOfStates() != rStateNames.getSize()){
		cout << "Number of columns does not match in formStateStorage. Found "
			<< originalStorage.getSmallestNumberOfStates() << " Expected  " << rStateNames.getSize() << "." << endl;
	}
	// Create a list with entry for each desiredName telling which column in originalStorage has the data
	int* mapColumns = new int[rStateNames.getSize()];
	for(int i=0; i< rStateNames.getSize(); i++){
		// the index is -1 if not found, >=1 otherwise since time has index 0 by defn.
		mapColumns[i] = originalStorage.getColumnLabels().findIndex(rStateNames[i]); 
		if (mapColumns[i]==-1)
			cout << "Column "<< rStateNames[i] << " not found in formStateStorage, assuming 0." << endl;
	}
	// Now cycle thru and shuffle each 

	for (int row =0; row< originalStorage.getSize(); row++){
		StateVector* originalVec = originalStorage.getStateVector(row);
		StateVector* stateVec = new StateVector(originalVec->getTime());
		stateVec->getData().setSize(numStates);  // default value 0f 0.
		for(int column=0; column< numStates; column++){
			double valueInOriginalStorage=0.0;
			if (mapColumns[column]!=-1)
				originalVec->getDataValue(mapColumns[column]-1, valueInOriginalStorage);

			stateVec->setDataValue(column, valueInOriginalStorage);
			
		}
		statesStorage.append(*stateVec);
	}
	rStateNames.insert(0, "time");
	statesStorage.setColumnLabels(rStateNames);

}

/**
 * Model::formStateStorage is intended to take any storage and populate qStorage.
 * stateStorage is supposed to be a Storage with labels identical to those obtained by calling 
 * Model::getStateNames(). Columns/entries found in the "originalStorage" are copied to the 
 * output qStorage. Entries not found are populated with 0s.
 */
void Model::formQStorage(const Storage& originalStorage, Storage& qStorage) {

    int nq =  _system->getDefaultState().getNQ();
	Array<string> qNames;
	getCoordinateSet().getNames(qNames);


	int* mapColumns = new int[qNames.getSize()];
	for(int i=0; i< nq; i++){
		// the index is -1 if not found, >=1 otherwise since time has index 0 by defn.
		mapColumns[i] = originalStorage.getColumnLabels().findIndex(qNames[i]); 
		if (mapColumns[i]==-1)
			cout << "\n Column "<< qNames[i] << " not found in formQStorage, assuming 0.\n" << endl;
	}


	// Now cycle thru and shuffle each 
	for (int row =0; row< originalStorage.getSize(); row++){
		StateVector* originalVec = originalStorage.getStateVector(row);
		StateVector* stateVec = new StateVector(originalVec->getTime());
		stateVec->getData().setSize(nq);  // default value 0f 0.
		for(int column=0; column< nq; column++){
			double valueInOriginalStorage=0.0;
			if (mapColumns[column]!=-1)
				originalVec->getDataValue(mapColumns[column]-1, valueInOriginalStorage);

			stateVec->setDataValue(column, valueInOriginalStorage);
		}
		qStorage.append(*stateVec);
	}
	qNames.insert(0, "time");

	qStorage.setColumnLabels(qNames);

}
void Model::disownAllComponents()
{
	updBodySet().setMemoryOwner(false);
	updConstraintSet().setMemoryOwner(false);
	updForceSet().setMemoryOwner(false);
	updContactGeometrySet().setMemoryOwner(false);
	updControllerSet().setMemoryOwner(false);
	updAnalysisSet().setMemoryOwner(false);
	updMarkerSet().setMemoryOwner(false);
}
