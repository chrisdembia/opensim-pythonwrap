// simmModel.cpp
// Author: Peter Loan
/* Copyright (c) 2005, Stanford University and Peter Loan.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including 
 * without limitation the rights to use, copy, modify, merge, publish, 
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included 
 * in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


//=============================================================================
// INCLUDES
//=============================================================================
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <math.h>
#include "simmModel.h"
#include "simmKinematicsEngine.h"

//=============================================================================
// STATICS
//=============================================================================


using namespace std;



//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Default constructor.
 */
simmModel::simmModel() :
   _muscles((rdArrayPtrs<simmMuscle>&)_musclesProp.getValueObjArray()),
	_kinematicsEngine((rdArrayPtrs<nmblKinematicsEngine>&)_kinematicsEngineProp.getValueObjArray()),
   _gravity(_gravityProp.getValueDblArray()),
	_builtOK(false)
{
	setNull();
}

//_____________________________________________________________________________
/**
 * Constructor from an XML file
 */
simmModel::simmModel(const string &aFileName) :
	rdModel(aFileName),
   _muscles((rdArrayPtrs<simmMuscle>&)_musclesProp.getValueObjArray()),
	_kinematicsEngine((rdArrayPtrs<nmblKinematicsEngine>&)_kinematicsEngineProp.getValueObjArray()),
   _gravity(_gravityProp.getValueDblArray()),
	_builtOK(false)
{
	setNull();
	updateFromXMLNode();

	_fileName = aFileName;
}

simmModel::simmModel(DOMElement *aElement) :
   rdModel(aElement),
   _muscles((rdArrayPtrs<simmMuscle>&)_musclesProp.getValueObjArray()),
	_kinematicsEngine((rdArrayPtrs<nmblKinematicsEngine>&)_kinematicsEngineProp.getValueObjArray()),
   _gravity(_gravityProp.getValueDblArray()),
	_builtOK(false)
{
	setNull();
	updateFromXMLNode();
}


//_____________________________________________________________________________
/**
 * Destructor.
 */
simmModel::~simmModel()
{
}


//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aModel simmModel to be copied.
 */

simmModel::simmModel(const simmModel &aModel) :
   _muscles((rdArrayPtrs<simmMuscle>&)_musclesProp.getValueObjArray()),
	_kinematicsEngine((rdArrayPtrs<nmblKinematicsEngine>&)_kinematicsEngineProp.getValueObjArray()),
   _gravity(_gravityProp.getValueDblArray()),
	_builtOK(false)
{
	setupProperties();
	copyData(aModel);	
}

//_____________________________________________________________________________
/**
 * Copy this simmModel and return a pointer to the copy.
 * The copy constructor for this class is used.
 *
 * @return Pointer to a copy of this simmModel.
 */
rdObject* simmModel::copy() const
{
	simmModel *model = new simmModel(*this);
	return(model);
}
//_____________________________________________________________________________
/**
 * Copy this simmModel and modify the copy so that it is consistent
 * with a specified XML element node.
 *
 * The copy is constructed by first using
 * simmModel::simmModel(DOMElement*) in order to establish the
 * relationship of the simmModel object with the XML node. Then, the
 * assignment operator is used to set all data members of the copy to the
 * values of this simmModel object. Finally, the data members of the copy are
 * updated using simmModel::updateFromXMLNode().
 *
 * @param aElement XML element. 
 * @return Pointer to a copy of this simmModel.
 */
rdObject* simmModel::copy(DOMElement *aElement) const
{
	simmModel *model = new simmModel(aElement);
	*model = *this;
	model->updateFromXMLNode();
	return(model);
}

//_____________________________________________________________________________
/**
 * Copy the member variables of the model.
 */
void simmModel::copyData(const simmModel &aModel)
{
	_muscles = aModel._muscles;
	_muscleGroups = aModel._muscleGroups;
	_kinematicsEngine = aModel._kinematicsEngine;
	_gravity = aModel._gravity;
}


simmModel& simmModel::operator=(const simmModel &aModel)
{
	// BASE CLASS
	rdModel::operator=(aModel);

	// Class Members
	copyData(aModel);

	setup();

	return(*this);
}

//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set the values of all data members to an appropriate "null" value.
 */
void simmModel::setNull()
{
	setType("SIMMmodel");
	setupProperties();
}

void simmModel::setupProperties()
{
	_kinematicsEngineProp.setName("KinematicsEngines");
	rdArrayPtrs<rdObject> kes;
	_kinematicsEngineProp.setValue(kes);
	_propertySet.append(&_kinematicsEngineProp);

	_musclesProp.setName("Muscles");
	rdArrayPtrs<rdObject> musc;
	_musclesProp.setValue(musc);
	_propertySet.append(&_musclesProp);

	const double defaultGravity[] = {0.0, -9.80665, 0.0};
	_gravityProp.setName("gravity");
	_gravityProp.setValue(3, defaultGravity);
	_propertySet.append(&_gravityProp);
}

void simmModel::registerTypes()
{
	rdObject::RegisterType(simmMuscle());
	rdObject::RegisterType(simmMuscleGroup());
	simmMuscle::registerTypes();
}

void simmModel::setKinematicsEngine(nmblKinematicsEngine& aKE)
{
	//*(_kinematicsEngine[0]) = aKE; TODO
}

nmblKinematicsEngine& simmModel::getKinematicsEngine() const
{
	assert(_kinematicsEngine.getSize() > 0);

	return *(_kinematicsEngine[0]);
}

simmKinematicsEngine& simmModel::getSimmKinematicsEngine() const
{
	assert(_kinematicsEngine.getSize() > 0);

	simmKinematicsEngine* ske = dynamic_cast<simmKinematicsEngine*>(_kinematicsEngine[0]);
	assert(ske);

	return *ske;
}

/* Return a label describing the gravity vector (used for
 * writing SIMM files). It assumes that gravity is expressed
 * in Nm/sec2, and is aligned with a major axis.
 */
const char* simmModel::getGravityLabel() const
{
	if (_gravity[0] <= -9.8)
		return "-X";
	if (_gravity[0] >= 9.8)
		return "+X";
	if (_gravity[1] <= -9.8)
		return "-Y";
	if (_gravity[1] >= 9.8)
		return "+Y";
	if (_gravity[2] <= -9.8)
		return "-Z";
	if (_gravity[2] >= 9.8)
		return "+Z";

	return "";
}

bool simmModel::bodyNeededForDynamics(simmBody* aBody)
{
	// TODO check for wrap objects, etc.
	aBody->_sdfastInfo.skippable = true;
	return false;
}

simmMuscleGroup* simmModel::enterGroup(const string& aName)
{
	for (int i = 0; i < _muscleGroups.getSize(); i++)
		if (aName == _muscleGroups[i]->getName())
			return _muscleGroups[i];

	simmMuscleGroup* newGroup = new simmMuscleGroup();
	newGroup->setName(aName);
	_muscleGroups.append(newGroup);

	return newGroup;
}

/* Perform some set up functions that happen after the
 * object has been deserialized or copied. This is basically
 * calling the setup() functions of the member objects.
 */
void simmModel::setup()
{
	int i;

	/* Muscle groups are set up with these steps:
	 *   1. empty groups are created and named.
	 *   2. group->setup() is called so the groups
	 *      can store pointers to their muscles
	 *   3. muscle->setup() is called so the muscles
	 *      can store pointers to the groups they're in.
	 */
	simmMuscle* sm;
	for (i = 0; i < _muscles.getSize(); i++)
	{
		if (sm = dynamic_cast<simmMuscle*>(_muscles[i]))
		{
			const rdArray<string>& groupNames = sm->getGroupNames();
			for (int j = 0; j < groupNames.getSize(); j++)
				enterGroup(groupNames[j]);
		}
	}

	for (i = 0; i < _muscleGroups.getSize(); i++)
		_muscleGroups[i]->setup(this);

	for (i = 0; i < _muscles.getSize(); i++)
	{
		if (sm = dynamic_cast<simmMuscle*>(_muscles[i]))
			sm->setup(this, &getSimmKinematicsEngine());
	}

	simmKinematicsEngine* ske;
	for (i = 0; i < _kinematicsEngine.getSize(); i++)
	{
		if (ske = dynamic_cast<simmKinematicsEngine*>(_kinematicsEngine[i]))
			ske->setup(this);
	}

	/* The following code should be replaced by a more robust
	 * check for problems while creating the model.
	 */
	if (_kinematicsEngine.getSize() > 0 && _kinematicsEngine[0]->getNumBodies() > 0)
	{
		_builtOK = true;

		/* Copy number of bodies to base class. */
		_nb = _kinematicsEngine[0]->getNumBodies();
	}

	cout << "Created model " << getName() << " from file " << _fileName << endl;
}

void simmModel::solveInverseKinematics(const simmIKTrialParams& aIKOptions, const string aMarkerDataFileName, const string aOutputFileName)
{
	getSimmKinematicsEngine().solveInverseKinematics(aIKOptions, aMarkerDataFileName, aOutputFileName);
}

simmMotionData* simmModel::solveInverseKinematics(const simmIKTrialParams& aIKOptions, simmMarkerData& aMarkerData)
{
	return getSimmKinematicsEngine().solveInverseKinematics(aIKOptions, aMarkerData);
}

simmMotionData* simmModel::solveInverseKinematics(const simmIKTrialParams& aIKOptions, simmMarkerData& aMarkerData, simmMotionData& aCoordinateData)
{
	return getSimmKinematicsEngine().solveInverseKinematics(aIKOptions, aMarkerData, aCoordinateData);
}

void simmModel::moveMarkersToCloud(simmMarkerData& aMarkerData)
{
	getSimmKinematicsEngine().moveMarkersToCloud(aMarkerData);
}

int simmModel::deleteUnusedMarkers(const rdArray<string>& aMarkerNames)
{
	return getSimmKinematicsEngine().deleteUnusedMarkers(aMarkerNames);
}

//_____________________________________________________________________________
/**
 * Replace all markers in the model with the ones in the
 * passed-in marker set. Return value is the number of markers
 * in the marker set that were successfully added to the model.
 */
int simmModel::replaceMarkerSet(simmMarkerSet& aMarkerSet)
{
	return getSimmKinematicsEngine().replaceMarkerSet(aMarkerSet);
}

//_____________________________________________________________________________
/**
 * Update all markers in the model with the ones in the
 * passed-in marker set. If the marker does not yet exist
 * in the model, it is added.
 */
void simmModel::updateMarkers(rdArrayPtrs<simmMarker>& aMarkerArray)
{
	getSimmKinematicsEngine().updateMarkers(aMarkerArray);
}

//_____________________________________________________________________________
/**
 * Update all coordinates in the model with the ones in the
 * passed-in coordinate set. If the coordinate does not yet exist
 * in the model, it is not added.
 */
void simmModel::updateCoordinates(rdArrayPtrs<simmCoordinate>& aCoordinateArray)
{
	getSimmKinematicsEngine().updateCoordinates(aCoordinateArray);
}

double simmModel::takeMeasurement(const simmMeasurement& aMeasurement)
{
	return getSimmKinematicsEngine().takeMeasurement(aMeasurement);
}

const simmUnits& simmModel::getLengthUnits() const
{
	return getSimmKinematicsEngine().getLengthUnits();
}

const simmUnits& simmModel::getForceUnits() const
{
	return getSimmKinematicsEngine().getForceUnits();
}

rdArrayPtrs<simmBody>& simmModel::getBodies()
{
	return getSimmKinematicsEngine().getBodies();
}

rdArrayPtrs<simmCoordinate>& simmModel::getCoordinates()
{
	return getSimmKinematicsEngine().getCoordinates();
}

void simmModel::writeSIMMJointFile(string& aFileName) const
{
	getSimmKinematicsEngine().writeSIMMJointFile(aFileName);
}

void simmModel::writeSIMMMuscleFile(string& aFileName) const
{
   ofstream out;
	int functionIndex = 1;

   out.open(aFileName.c_str());
   out.setf(ios::fixed);
   out.precision(6);

   if (!out.good())
   {
      cout << "Unable to open output file " << aFileName << endl;
      return;
   }

   out << "/**********************************************************/\n";
   out << "/*            Muscle file created by NMBLTS                */\n";
   if (getInputFileName() != "")
      out << "/* name of original model file: " << getInputFileName() << " */\n";
   out << "/**********************************************************/\n";
   out << "\n";

	for (int i = 0; i < getNumberOfMuscles(); i++)
		_muscles[i]->writeSIMM(out);

   out.close();
	cout << "Wrote SIMM muscle file " << aFileName << " from model " << getName() << endl;
}

/* Write an XML file of all the markers in the model.
 * The contents of this file can be pasted into a
 * MarkerSet definition inside a simmMarkerPlacementParams
 * or a simmGenericModelParams.
 */
void simmModel::writeMarkerFile(string& aFileName) const
{
   getSimmKinematicsEngine().writeMarkerFile(aFileName);
}

void simmModel::peteTest() const
{
	int i;

	cout << "simmModel " << getName() << endl;
	cout << "   gravity: " << _gravity << endl;

	for (i = 0; i < getNumberOfMuscles(); i++)
		_muscles[i]->peteTest(&getSimmKinematicsEngine());

	for (i = 0; i < getNumberOfMuscleGroups(); i++)
		_muscleGroups[i]->peteTest();

	getSimmKinematicsEngine().peteTest();
}

//--------------------------------------------------------------------------
// NUMBERS
//--------------------------------------------------------------------------

int simmModel::getNJ() const
{
	return getKinematicsEngine().getNumJoints();
}

int simmModel::getNQ() const
{
	return getKinematicsEngine().getNumCoordinates();
}

int simmModel::getNU() const
{
	return getKinematicsEngine().getNumCoordinates();
}

int simmModel::getNX() const
{
	return 0;
}

int simmModel::getNA() const
{
	return _muscles.getSize();
}

int simmModel::getNP() const
{
	return getKinematicsEngine().getNumContacts();
}

int simmModel::getNY() const
{
	return getKinematicsEngine().getNumStates();
}

int simmModel::getNYP() const
{
	return getKinematicsEngine().getNumPseudoStates();
}

//--------------------------------------------------------------------------
// NAMES
//--------------------------------------------------------------------------

void simmModel::setBodyName(int aIndex, const string &aName)
{
	getKinematicsEngine().setBodyName(aIndex, aName);
}

string simmModel::getBodyName(int aIndex) const
{
	return getKinematicsEngine().getBodyName(aIndex);
}

string simmModel::getCoordinateName(int aIndex) const
{
	return getKinematicsEngine().getCoordinateName(aIndex);
}

string simmModel::getSpeedName(int aIndex) const
{
	return getKinematicsEngine().getSpeedName(aIndex);
}

string simmModel::getActuatorName(int aIndex) const
{
	if (_muscles.getSize() > aIndex)
		return _muscles[aIndex]->getName();
	else
		return "";
}

string simmModel::getControlName(int aIndex) const
{
	return getKinematicsEngine().getControlName(aIndex);
}

string simmModel::getStateName(int aIndex) const
{
	return getKinematicsEngine().getStateName(aIndex);
}

string simmModel::getPseudoStateName(int aIndex) const
{
	return getKinematicsEngine().getPseudoStateName(aIndex);
}

//--------------------------------------------------------------------------
// INDICES FROM NAMES
//--------------------------------------------------------------------------
int simmModel::getBodyIndex(const string &aName) const
{
	return getKinematicsEngine().getBodyIndex(aName);
}

int simmModel::getCoordinateIndex(const string &aName) const
{
	return getKinematicsEngine().getCoordinateIndex(aName);
}

int simmModel::getSpeedIndex(const string &aName) const
{
	return getKinematicsEngine().getSpeedIndex(aName);
}

int simmModel::getActuatorIndex(const string &aName) const
{
	for (int i = 0; i < _muscles.getSize(); i++)
		if (_muscles[i]->getName() == aName)
			return i;

	return -1;
}

int simmModel::getControlIndex(const string &aName) const
{
	return getKinematicsEngine().getControlIndex(aName);
}

int simmModel::getStateIndex(const string &aName) const
{
	return getKinematicsEngine().getStateIndex(aName);
}

int simmModel::getPseudoStateIndex(const string &aName) const
{
	return getKinematicsEngine().getPseudoStateIndex(aName);
}

//--------------------------------------------------------------------------
// SET CURRENT TIME, CONTROLS, AND STATES
//--------------------------------------------------------------------------

void simmModel::set(double aT, const double aX[], const double aY[])
{
	getKinematicsEngine().set(aT, aX, aY);
}

//--------------------------------------------------------------------------
// CONTROLS
//--------------------------------------------------------------------------

void simmModel::setControls(const double aX[])
{
	// TODO
}

void simmModel::setControl(int aIndex, double aValue)
{
	// TODO
}

void simmModel::setControl(const std::string &aName, double aValue)
{
	// TODO
}

void simmModel::getControls(double rX[]) const
{
	// TODO
}

double simmModel::getControl(int aIndex) const
{
	// TODO
	return 0.0;
}

double simmModel::getControl(const std::string &aName) const
{
	// TODO
	return 0.0;
}

//--------------------------------------------------------------------------
// INITIAL STATES
//--------------------------------------------------------------------------

void simmModel::setInitialStates(const double aYI[])
{
	getKinematicsEngine().setInitialStates(aYI);
}

void simmModel::getInitialStates(double rYI[]) const
{
	getKinematicsEngine().getInitialStates(rYI);
}

double simmModel::getInitialState(int aIndex) const
{
	return getKinematicsEngine().getInitialState(aIndex);
}

double simmModel::getInitialState(const string &aName) const
{
	return getKinematicsEngine().getInitialState(aName);
}

//--------------------------------------------------------------------------
// STATES
//--------------------------------------------------------------------------
void simmModel::setStates(const double aY[])
{
	getKinematicsEngine().setStates(aY);
}

void simmModel::getStates(double rY[]) const
{
	getKinematicsEngine().getStates(rY);
}

double simmModel::getState(int aIndex) const
{
	return getKinematicsEngine().getState(aIndex);
}

double simmModel::getState(const string &aName) const
{
	return getKinematicsEngine().getState(aName);
}

//--------------------------------------------------------------------------
// INITIAL PSEUDO STATES
//--------------------------------------------------------------------------

void simmModel::setInitialPseudoStates(const double aYPI[])
{
	getKinematicsEngine().setInitialPseudoStates(aYPI);
}

void simmModel::getInitialPseudoStates(double rYPI[]) const
{
	getKinematicsEngine().getInitialPseudoStates(rYPI);
}

double simmModel::getInitialPseudoState(int aIndex) const
{
	return getKinematicsEngine().getInitialPseudoState(aIndex);
}

double simmModel::getInitialPseudoState(const string &aName) const
{
	return getKinematicsEngine().getInitialPseudoState(aName);
}


//--------------------------------------------------------------------------
// PSEUDO STATES
//--------------------------------------------------------------------------

void simmModel::setPseudoStates(const double aYP[])
{
	getKinematicsEngine().setPseudoStates(aYP);
}

void simmModel::getPseudoStates(double rYP[]) const
{
	getKinematicsEngine().getPseudoStates(rYP);
}

double simmModel::getPseudoState(int aIndex) const
{
	return getKinematicsEngine().getPseudoState(aIndex);
}

//--------------------------------------------------------------------------
// CONFIGURATION
//--------------------------------------------------------------------------

void simmModel::setConfiguration(const double aY[])
{
	getKinematicsEngine().setConfiguration(aY);
}

void simmModel::setConfiguration(const double aQ[], const double aU[])
{
	getKinematicsEngine().setConfiguration(aQ, aU);
}

void simmModel::getCoordinates(double rQ[]) const
{
	getKinematicsEngine().getCoordinateValues(rQ);
}

double simmModel::getCoordinate(int aIndex) const
{
	return getKinematicsEngine().getCoordinateValue(aIndex);
}

double simmModel::getCoordinate(const string &aName) const
{
	return getKinematicsEngine().getCoordinateValue(aName);
}

void simmModel::getSpeeds(double rU[]) const
{
	getKinematicsEngine().getSpeeds(rU);
}

double simmModel::getSpeed(int aIndex) const
{
	return getKinematicsEngine().getSpeed(aIndex);
}

double simmModel::getSpeed(const string &aName) const
{
	return getKinematicsEngine().getSpeed(aName);
}

void simmModel::getAccelerations(double rDUDT[]) const
{
	getKinematicsEngine().getAccelerations(rDUDT);
}

double simmModel::getAcceleration(int aIndex) const
{
	return getKinematicsEngine().getAcceleration(aIndex);
}

double simmModel::getAcceleration(const string &aSpeedName) const
{
	return getKinematicsEngine().getAcceleration(aSpeedName);
}

void simmModel::extractConfiguration(const double aY[], double rQ[], double rU[]) const
{
	getKinematicsEngine().extractConfiguration(aY, rQ, rU);
}

//--------------------------------------------------------------------------
// ASSEMBLING THE MODEL
//--------------------------------------------------------------------------
int simmModel::assemble(double aTime, double *rState, int *aLock, double aTol, int aMaxevals, int *rFcnt, int *rErr)
{
	return getKinematicsEngine().assemble(aTime, rState, aLock, aTol, aMaxevals, rFcnt, rErr);
}

//--------------------------------------------------------------------------
// SCALE THE MODEL
//--------------------------------------------------------------------------
bool simmModel::scale(const suScaleSet& aScaleSet)
{
	// Scale the muscles
	simmMuscle* sm;
	for (int i = 0; i < _muscles.getSize(); i++)
	{
		if (sm = dynamic_cast<simmMuscle*>(_muscles[i]))
			sm->scale(aScaleSet);
	}

	// Scale the rest of the model
	return getKinematicsEngine().scale(aScaleSet);

	cout << "Scaled model " << getName() << endl;
}

//--------------------------------------------------------------------------
// GRAVITY
//--------------------------------------------------------------------------
void simmModel::getGravity(double rGrav[3]) const
{
	getKinematicsEngine().getGravity(rGrav);
}

void simmModel::setGravity(double aGrav[3])
{
	getKinematicsEngine().setGravity(aGrav);
}

//--------------------------------------------------------------------------
// BODY INFORMATION
//--------------------------------------------------------------------------

int simmModel::getGroundID() const
{
	return getKinematicsEngine().getGroundBodyIndex();
}

void simmModel::setBodyToJointBodyLocal(int aBody, const double aBTJ[3])
{
	getKinematicsEngine().setBodyToJointBodyLocal(aBody, aBTJ);
}

void simmModel::getBodyToJointBodyLocal(int aBody, double rBTJ[3]) const
{
	getKinematicsEngine().getBodyToJointBodyLocal(aBody, rBTJ);
}

void simmModel::setInboardToJointBodyLocal(int aBody, const double aBTJ[3])
{
	getKinematicsEngine().setInboardToJointBodyLocal(aBody, aBTJ);
}

void simmModel::getInboardToJointBodyLocal(int aBody, double rBTJ[3]) const
{
	getKinematicsEngine().getInboardToJointBodyLocal(aBody, rBTJ);
}

//--------------------------------------------------------------------------
// INERTIA
//--------------------------------------------------------------------------
double simmModel::getMass(int aBody) const
{
	return getKinematicsEngine().getMass(aBody);
}

int simmModel::getInertiaBodyLocal(int aBody, double rI[3][3]) const
{
	return getKinematicsEngine().getInertiaBodyLocal(aBody, rI);
}

int simmModel::getInertiaBodyLocal(int aBody, double *rI) const
{
	return getKinematicsEngine().getInertiaBodyLocal(aBody, rI);
}

void simmModel::getSystemInertia(double *rM, double rCOM[3], double rI[3][3]) const
{
	getKinematicsEngine().getSystemInertia(rM, rCOM, rI);
}

void simmModel::getSystemInertia(double *rM, double *rCOM, double *rI) const
{
	getKinematicsEngine().getSystemInertia(rM, rCOM, rI);
}

//--------------------------------------------------------------------------
// KINEMATICS
//--------------------------------------------------------------------------
void simmModel::getPosition(int aBody, const double aPoint[3], double rPos[3]) const
{
	getKinematicsEngine().getPosition(aBody, aPoint, rPos);
}

void simmModel::getVelocity(int aBody, const double aPoint[3], double rVel[3]) const
{
	getKinematicsEngine().getVelocity(aBody, aPoint, rVel);
}

void simmModel::getAcceleration(int aBody, const double aPoint[3], double rAcc[3]) const
{
	getKinematicsEngine().getAcceleration(aBody, aPoint, rAcc);
}

void simmModel::getDirectionCosines(int aBody, double rDirCos[3][3]) const
{
	getKinematicsEngine().getDirectionCosines(aBody, rDirCos);
}

void simmModel::getDirectionCosines(int aBody, double *rDirCos) const
{
	getKinematicsEngine().getDirectionCosines(aBody, rDirCos);
}

void simmModel::getAngularVelocity(int aBody, double rAngVel[3]) const
{
	getKinematicsEngine().getAngularVelocity(aBody, rAngVel);
}

void simmModel::getAngularVelocityBodyLocal(int aBody, double rAngVel[3]) const
{
	getKinematicsEngine().getAngularVelocityBodyLocal(aBody, rAngVel);
}

void simmModel::getAngularAcceleration(int aBody, double rAngAcc[3]) const
{
	getKinematicsEngine().getAngularAcceleration(aBody, rAngAcc);
}

void simmModel::getAngularAccelerationBodyLocal(int aBody, double rAngAcc[3]) const
{
	getKinematicsEngine().getAngularAccelerationBodyLocal(aBody, rAngAcc);
}

//--------------------------------------------------------------------------
// LOAD APPLICATION
//--------------------------------------------------------------------------

// FORCES EXPRESSED IN INERTIAL FRAME
void simmModel::applyForce(int aBody, const double aPoint[3], const double aForce[3])
{
	getKinematicsEngine().applyForce(aBody, aPoint, aForce);
}

void simmModel::applyForces(int aN, const int aBodies[], const double aPoints[][3], const double aForces[][3])
{
	getKinematicsEngine().applyForces(aN, aBodies, aPoints, aForces);
}

void simmModel::applyForces(int aN, const int aBodies[], const double *aPoints, const double *aForces)
{
	getKinematicsEngine().applyForces(aN, aBodies, aPoints, aForces);
}

// FORCES EXPRESSED IN BODY-LOCAL FRAME
void simmModel::applyForceBodyLocal(int aBody, const double aPoint[3], const double aForce[3])
{
	getKinematicsEngine().applyForceBodyLocal(aBody, aPoint, aForce);
}

void simmModel::applyForcesBodyLocal(int aN, const int aBodies[], const double aPoints[][3], const double aForces[][3])
{
	getKinematicsEngine().applyForcesBodyLocal(aN, aBodies, aPoints, aForces);
}

void simmModel::applyForcesBodyLocal(int aN, const int aBodies[], const double *aPoints, const double *aForces)
{
	getKinematicsEngine().applyForcesBodyLocal(aN, aBodies, aPoints, aForces);
}

// TORQUES EXPRESSED IN INERTIAL FRAME
void simmModel::applyTorque(int aBody, const double aTorque[3])
{
	getKinematicsEngine().applyTorque(aBody, aTorque);
}

void simmModel::applyTorques(int aN, const int aBodies[], const double aTorques[][3])
{
	getKinematicsEngine().applyTorques(aN, aBodies, aTorques);
}

void simmModel::applyTorques(int aN, const int aBodies[], const double *aTorques)
{
	getKinematicsEngine().applyTorques(aN, aBodies, aTorques);
}

// TORQUES EXPRESSED IN BODY-LOCAL FRAME (sdbodyt())
void simmModel::applyTorqueBodyLocal(int aBody, const double aTorque[3])
{
	getKinematicsEngine().applyTorqueBodyLocal(aBody, aTorque);
}

void simmModel::applyTorquesBodyLocal(int aN, const int aBodies[], const double aTorques[][3])
{
	getKinematicsEngine().applyTorquesBodyLocal(aN, aBodies, aTorques);
}

void simmModel::applyTorquesBodyLocal(int aN, const int aBodies[], const double *aTorques)
{
	getKinematicsEngine().applyTorquesBodyLocal(aN, aBodies, aTorques);
}

// GENERALIZED FORCES
void simmModel::applyGeneralizedForce(int aU, double aF)
{
	getKinematicsEngine().applyGeneralizedForce(aU, aF);
}

void simmModel::applyGeneralizedForces(const double aF[])
{
	getKinematicsEngine().applyGeneralizedForces(aF);
}

void simmModel::applyGeneralizedForces(int aN, const int aU[], const double aF[])
{
	getKinematicsEngine().applyGeneralizedForces(aN, aU, aF);
}

//--------------------------------------------------------------------------
// LOAD ACCESS AND COMPUTATION
//--------------------------------------------------------------------------

double simmModel::getNetAppliedGeneralizedForce(int aU) const
{
	return getKinematicsEngine().getNetAppliedGeneralizedForce(aU);
}

void simmModel::computeGeneralizedForces(double aDUDT[], double rF[]) const
{
	getKinematicsEngine().computeGeneralizedForces(aDUDT, rF);
}

void simmModel::computeReactions(double rForces[][3], double rTorques[][3]) const
{
	getKinematicsEngine().computeReactions(rForces, rTorques);
}

//--------------------------------------------------------------------------
// PRESCRIBED MOTION
//--------------------------------------------------------------------------

void simmModel::prescribeMotion(int aJoint, int aAxis, int aPrescribed)
{
}

//--------------------------------------------------------------------------
// EQUATIONS OF MOTION
//--------------------------------------------------------------------------

void simmModel::formMassMatrix(double *rI)
{
	getKinematicsEngine().formMassMatrix(rI);
}

void simmModel::formEulerTransform(int aBody, double *rE) const
{
	getKinematicsEngine().formEulerTransform(aBody, rE);
}

void simmModel::formJacobianTranslation(int aBody, const double aPoint[3], double *rJ, int aRefBody) const
{
	getKinematicsEngine().formJacobianTranslation(aBody, aPoint, rJ, aRefBody);
}

void simmModel::formJacobianOrientation(int aBody, double *rJ0, int aRefBody) const
{
	getKinematicsEngine().formJacobianOrientation(aBody, rJ0, aRefBody);
}

void simmModel::formJacobianEuler(int aBody, double *rJE, int aRefBody) const
{
	getKinematicsEngine().formJacobianEuler(aBody, rJE, aRefBody);
}

//--------------------------------------------------------------------------
// DERIVATIVES
//--------------------------------------------------------------------------

int simmModel::computeAccelerations(double *dqdt, double *dudt)
{
	return getKinematicsEngine().computeAccelerations(dqdt, dudt);
}

void simmModel::computeAuxiliaryDerivatives(double *dydt)
{
	getKinematicsEngine().computeAuxiliaryDerivatives(dydt);
}

//--------------------------------------------------------------------------
// UTILITY
//--------------------------------------------------------------------------

void simmModel::transform(int aBody1, const double aVec1[3], int aBody2, double rVec2[3]) const
{
	getKinematicsEngine().transform(aBody1, aVec1, aBody2, rVec2);
}

void simmModel::transformPosition(int aBody, const double aPos[3], double rPos[3]) const
{
	getKinematicsEngine().transformPosition(aBody, aPos, rPos);
}

void simmModel::convertQuaternionsToAngles(double *aQ, double *rQAng) const
{
	getKinematicsEngine().convertQuaternionsToAngles(aQ, rQAng);
}

void simmModel::convertQuaternionsToAngles(rdStorage *rQStore) const
{
	getKinematicsEngine().convertQuaternionsToAngles(rQStore);
}

void simmModel::convertAnglesToQuaternions(double *aQAng, double *rQ) const
{
	getKinematicsEngine().convertAnglesToQuaternions(aQAng, rQ);
}

void simmModel::convertAnglesToQuaternions(rdStorage *rQStore) const
{
	getKinematicsEngine().convertAnglesToQuaternions(rQStore);
}

void simmModel::convertRadiansToDegrees(double *aQRad, double *rQDeg) const
{
	getKinematicsEngine().convertRadiansToDegrees(aQRad, rQDeg);
}

void simmModel::convertRadiansToDegrees(rdStorage *rQStore) const
{
	getKinematicsEngine().convertRadiansToDegrees(rQStore);
}

void simmModel::convertDegreesToRadians(double *aQDeg, double *rQRad) const
{
	getKinematicsEngine().convertDegreesToRadians(aQDeg, rQRad);
}

void simmModel::convertDegreesToRadians(rdStorage *rQStore) const
{
	getKinematicsEngine().convertDegreesToRadians(rQStore);
}

void simmModel::convertAnglesToDirectionCosines(double aE1, double aE2, double aE3, double rDirCos[3][3]) const
{
	getKinematicsEngine().convertAnglesToDirectionCosines(aE1, aE2, aE3, rDirCos);
}

void simmModel::convertAnglesToDirectionCosines(double aE1, double aE2, double aE3, double *rDirCos) const
{
	getKinematicsEngine().convertAnglesToDirectionCosines(aE1, aE2, aE3, rDirCos);
}

void simmModel::convertDirectionCosinesToAngles(double aDirCos[3][3], double *rE1, double *rE2, double *rE3) const
{
	getKinematicsEngine().convertDirectionCosinesToAngles(aDirCos, rE1, rE2, rE3);
}

void simmModel::convertDirectionCosinesToAngles(double *aDirCos, double *rE1, double *rE2, double *rE3) const
{
	getKinematicsEngine().convertDirectionCosinesToAngles(aDirCos, rE1, rE2, rE3);
}

void simmModel::convertDirectionCosinesToQuaternions(double aDirCos[3][3], double *rQ1, double *rQ2, double *rQ3, double *rQ4) const
{
	getKinematicsEngine().convertDirectionCosinesToQuaternions(aDirCos, rQ1, rQ2, rQ3, rQ4);
}

void simmModel::convertDirectionCosinesToQuaternions(double *aDirCos, double *rQ1, double *rQ2, double *rQ3, double *rQ4) const
{
	getKinematicsEngine().convertDirectionCosinesToQuaternions(aDirCos, rQ1, rQ2, rQ3, rQ4);
}

void simmModel::convertQuaternionsToDirectionCosines(double aQ1, double aQ2, double aQ3, double aQ4, double rDirCos[3][3]) const
{
	getKinematicsEngine().convertQuaternionsToDirectionCosines(aQ1, aQ2, aQ3, aQ4, rDirCos);
}

void simmModel::convertQuaternionsToDirectionCosines(double aQ1, double aQ2, double aQ3, double aQ4, double *rDirCos) const
{
	getKinematicsEngine().convertQuaternionsToDirectionCosines(aQ1, aQ2, aQ3, aQ4, rDirCos);
}

//--------------------------------------------------------------------------
// ACTUATION
//--------------------------------------------------------------------------
void simmModel::computeActuation()
{
}

void simmModel::applyActuatorForce(int aID)
{
}

void simmModel::applyActuatorForces()
{
}

void simmModel::setActuatorForce(int aID, double aForce)
{
}

double simmModel::getActuatorForce(int aID) const
{
	return 0.0;
}

double simmModel::getActuatorStress(int aID) const
{
	return 0.0;
}

double simmModel::getActuatorSpeed(int aID) const
{
	return 0.0;
}

double simmModel::getActuatorPower(int aID) const
{
	return 0.0;
}

//--------------------------------------------------------------------------
// CONTACT
//--------------------------------------------------------------------------
void simmModel::computeContact()
{
	getKinematicsEngine().computeContact();
}

void simmModel::applyContactForce(int aID)
{
	getKinematicsEngine().applyContactForce(aID);
}

void simmModel::applyContactForces()
{
	getKinematicsEngine().applyContactForces();
}

int simmModel::getContactBodyA(int aID) const
{
	return getKinematicsEngine().getContactBodyA(aID);
}

int simmModel::getContactBodyB(int aID) const
{
	return getKinematicsEngine().getContactBodyB(aID);
}

void simmModel::setContactPointA(int aID, const double aPoint[3])
{
	getKinematicsEngine().setContactPointA(aID, aPoint);
}

void simmModel::getContactPointA(int aID, double rPoint[3]) const
{
	getKinematicsEngine().getContactPointA(aID, rPoint);
}

void simmModel::setContactPointB(int aID, const double aPoint[3])
{
	getKinematicsEngine().setContactPointB(aID, aPoint);
}

void simmModel::getContactPointB(int aID, double rPoint[3]) const
{
	getKinematicsEngine().getContactPointB(aID, rPoint);
}

void simmModel::getContactForce(int aID, double rF[3]) const
{
	getKinematicsEngine().getContactForce(aID, rF);
}

void simmModel::getContactNormalForce(int aID, double rFP[3], double rFV[3], double rF[3]) const
{
	getKinematicsEngine().getContactNormalForce(aID, rFP, rFV, rF);
}

void simmModel::getContactTangentForce(int aID, double rFP[3], double rFV[3], double rF[3]) const
{
	getKinematicsEngine().getContactTangentForce(aID, rFP, rFV, rF);
}

void simmModel::getContactStiffness(int aID, const double aDX[3], double rDF[3]) const
{
	getKinematicsEngine().getContactStiffness(aID, aDX, rDF);
}

void simmModel::getContactViscosity(int aID, const double aDV[3], double rDF[3]) const
{
	getKinematicsEngine().getContactViscosity(aID, aDV, rDF);
}

void simmModel::getContactFrictionCorrection(int aID, double aDFFric[3]) const
{
	getKinematicsEngine().getContactFrictionCorrection(aID, aDFFric);
}

double simmModel::getContactForce(int aID) const
{
	return getKinematicsEngine().getContactForce(aID);
}

double simmModel::getContactSpeed(int aID) const
{
	return getKinematicsEngine().getContactSpeed(aID);
}

double simmModel::getContactPower(int aID) const
{
	return getKinematicsEngine().getContactPower(aID);
}
//--------------------------------------------------------------------------
// BODY INFO, to be implemented
//--------------------------------------------------------------------------

void simmModel::setPin(int aBody,int aPinNumber,const double aPin[3])
{
	//return getKinematicsEngine().setPin(aBody, aPinNumber, aPin);
}

void simmModel::getPin(int aBody,int aPinNumber,double rPin[3]) const
{
	//return getKinematicsEngine().getPin(aBody, aPinNumber, rPin);
}
void simmModel::getJointInfo(int aJoint,int rInfo[50],int rSlider[6]) const
{
	// return getKinematicsEngine().getJointInfo(aJoint, rInfo, rSlider);
}
