// Controller.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*
* Copyright (c)  2010, Stanford University. All rights reserved. 
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

/* 
 * Author: Ajay Seth Frank C. Anderson, Chand T. John, Samuel R. Hamner, 
 */


//=============================================================================
// INCLUDES
//=============================================================================
#include <cstdio>
#include <OpenSim/Common/IO.h>
#include <OpenSim/Common/Object.h>
#include <OpenSim/Common/Set.h>
#include "Controller.h"
#include <OpenSim/Simulation/Model/Model.h>
#include <OpenSim/Simulation/Model/ModelComponent.h>
#include <OpenSim/Simulation/Model/Actuator.h>
#include "SimTKsimbody.h"


//=============================================================================
// STATICS
//=============================================================================

// This command indicates that any identifier (class, variable, method, etc.)
// defined within the OpenSim namespace can be used in this file without the
// "OpenSim::" prefix.
using namespace OpenSim;
using namespace std;



//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Default constructor.
 */
Controller::Controller() :
	ModelComponent(),
    _actuatorNameList(_actuatorNameListProp.getValueStrArray()),
    _isControllerEnabled(_isControllerEnabledProp.getValueBool())
{
	setNull();
}
//_____________________________________________________________________________
/**
 * Constructor.
 */
Controller::Controller(Model& aModel) :
	ModelComponent(),
   _actuatorNameList(_actuatorNameListProp.getValueStrArray()),
    _isControllerEnabled(_isControllerEnabledProp.getValueBool())
{
	setNull();
	_model = &aModel;
}
//_____________________________________________________________________________
/**
 * Constructor from an XML Document
  */
  Controller::Controller(const std::string &aFileName, bool aUpdateFromXMLNode) :
      ModelComponent(aFileName, false),
      _actuatorNameList(_actuatorNameListProp.getValueStrArray()),
      _isControllerEnabled(_isControllerEnabledProp.getValueBool())
{
      setNull();
      if(aUpdateFromXMLNode) updateFromXMLNode();
}

//_____________________________________________________________________________
/**
 * Copy constructor.
 */
Controller::Controller(const Controller &aController) :
	ModelComponent(aController),
    _actuatorNameList(_actuatorNameListProp.getValueStrArray()),
    _isControllerEnabled(aController._isControllerEnabled)
{
	setNull();
	copyData(aController);
}
//_____________________________________________________________________________
/**
 * Destructor.
 */
Controller::~Controller()
{

}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set NULL values for all member variables.
 */
void Controller::
setNull()
{
	setupProperties();
	setType("Controller");
    _actuatorSet.setMemoryOwner(false);


	// MODEL
	_model = NULL;

	_isControllerEnabled = true;

}
//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void Controller::
setupProperties()
{
     string comment;

    comment = "A list of actuators that this controller will control."
              "The keyword ALL indicates the controller will controll all the acuators in the model";
    _actuatorNameListProp.setComment(comment);
    _actuatorNameListProp.setName("actuator_list");
    _propertySet.append(&_actuatorNameListProp);

    comment = "Flag (true or false) indicating whether or not the controller is enabled (ON) should ";
    _isControllerEnabledProp.setComment(comment);
    _isControllerEnabledProp.setName("enable_controller");
    _propertySet.append( &_isControllerEnabledProp );




}
//_____________________________________________________________________________
/**
 * Copy the member variables of the specified controller.
 */
void Controller::
copyData(const Controller &aController)
{
	_model = aController._model;
	_isControllerEnabled = aController._isControllerEnabled;
    _actuatorSet = aController._actuatorSet;
    _actuatorNameList = aController._actuatorNameList;
}


//=============================================================================
// OPERATORS
//=============================================================================
//-----------------------------------------------------------------------------
// ASSIGNMENT
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Assignment operator.
 */
Controller& Controller::
operator=(const Controller &aController)
{
	// BASE CLASS
	ModelComponent::operator=(aController);

	// DATA
	copyData(aController);

	return(*this);
}


//=============================================================================
// GET AND SET
//=============================================================================

//-----------------------------------------------------------------------------
// ON/OFF
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get whether or not this controller is on.
 */
bool Controller::getIsEnabled() const
{
    if( _model->getAllControllersEnabled() ) {
	   return(_isControllerEnabled);
    } else {
       return( false );
    }
}
//_____________________________________________________________________________
/**
 * Turn this controller on or off.
 */
void Controller::setIsEnabled(bool aTrueFalse)
{
	_isControllerEnabled = aTrueFalse;
}

double Controller::getFirstTime() const {
  return( -SimTK::Infinity); 
}
double Controller::getLastTime() const {
  return( SimTK::Infinity); 
}

// for any post XML deseraialization intialization
void Controller:: setup(Model& model)
{
	ModelComponent::setup(model);

	if(IO::Uppercase(_actuatorNameList[0]) == "ALL"){
		setActuators(model.updActuators());
		// setup actuators to ensure actuators added by controllers are also setup properly
		_actuatorSet.setup(*_model);
		return;
	}

	Set<Actuator> actuatorsByName;
	for(int i =0; i < _actuatorNameList.getSize(); i++){
		if(model.updActuators().contains(_actuatorNameList[i]))
			actuatorsByName.append(&model.updActuators().get(_actuatorNameList[i]));
		else
			throw Exception("Controller::setup : Actuator " + _actuatorNameList[i] + " not found.");
	}
	actuatorsByName.setMemoryOwner(false);
	setActuators(actuatorsByName);

	// setup actuators to ensure actuators added by controllers are also setup properly
	_actuatorSet.setup(*_model);
}

// makes a request for which actuators a controller will control
void Controller::setActuators( Set<Actuator>& actuators ) {
	//Rebuild consistent set of actuator lists
	_actuatorSet.setSize(0);
	_actuatorNameList.setSize(0);
	for(int i=0; i< actuators.getSize(); i++){
		addActuator(&actuators[i]);
	}
	_actuatorSet.setMemoryOwner(false);
}

void Controller::addActuator(Actuator *actuator)
{
	actuator->setController(this);
	actuator->setIsControlled(true);
	actuator->setControlIndex(_actuatorSet.getSize());
	_actuatorSet.append(actuator);
	_actuatorNameList.append(actuator->getName());
}


Set<Actuator>& Controller::updActuators() { return _actuatorSet.updActuators(); }

const Set<Actuator>& Controller::getActuatorSet() const { return _actuatorSet.getActuators(); }
