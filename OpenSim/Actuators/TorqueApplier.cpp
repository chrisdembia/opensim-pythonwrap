// TorqueApplier.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson and May Liu
// 
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <OpenSim/Common/rdMath.h>
#include <OpenSim/Common/Mtx.h>
#include <OpenSim/Simulation/Model/Model.h>
#include <OpenSim/Simulation/Model/AbstractDynamicsEngine.h>
#include <OpenSim/Simulation/Model/AbstractBody.h>
#include <OpenSim/Common/VectorFunction.h>
#include <OpenSim/Common/VectorGCVSplineR1R3.h>
#include "TorqueApplier.h"

//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________


using namespace OpenSim;
/**
 * Destructor.
 */
TorqueApplier::~TorqueApplier()
{
	deleteStorage();
}
//_____________________________________________________________________________
/**
 * Construct a derivative callback instance for applying external torques
 * during an integration.
 *
 * @param aModel Model for which external torques are to be applied.
 * @param aBody Body to which external torques are to be applied.
 */
TorqueApplier::
TorqueApplier(Model *aModel,AbstractBody *aBody) :
	DerivCallback(aModel)
{
	setNull();

	// MEMBER VARIABLES
	setBody(aBody);

	// STORAGE
	allocateStorage();

	// DESCRIPTION AND LABELS
	constructDescription();
	constructColumnLabels();
}
//_____________________________________________________________________________
/**
 * Construct a derivative callback instance for applying external torques
 * during an integration.
 *
 * NOTE: This function computes the torque functions from the given
 * data as order-3 generalized cross-validated spline functions.
 *
 * @param aModel Model for which external forces are to be applied.
 * @param bodyFrom Index of body that applies the force.
 * @param bodyTo Index of body to which force is applied.
 * @param torqueData Storage object containing torque data.
 * @param txNum Column index of applied torque's x coordinate in storage object.
 * @param tyNum Column index of applied torque's y coordinate in storage object.
 * @param tzNum Column index of applied torque's z coordinate in storage object.
 */
TorqueApplier::
TorqueApplier(Model *aModel,AbstractBody *bodyFrom,AbstractBody *bodyTo, Storage *torqueData,
              int txNum, int tyNum, int tzNum) :
	DerivCallback(aModel)
{
	setNull();

	// MEMBER VARIABLES
	setBody(bodyTo);

	// STORAGE
	allocateStorage();

	// DESCRIPTION AND LABELS
	constructDescription();
	constructColumnLabels();

	// COMPUTE TORQUE FUNCTION
	double *t=0,*x=0,*y=0,*z=0;
	int torqueSize = torqueData->getSize();
	torqueData->getTimeColumn(t);
	torqueData->getDataColumn(txNum,x);
	torqueData->getDataColumn(tyNum,y);
	torqueData->getDataColumn(tzNum,z);
	VectorGCVSplineR1R3 *torqueFunc;
	torqueFunc = new VectorGCVSplineR1R3(3,torqueSize,t,x,y,z);
	setTorqueFunction(torqueFunc);
}

//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Set member variables to approprate NULL values.
 */
void TorqueApplier::
setNull()
{
	setType("TorqueApplier");
	_body = 0;	
	_torque[0] = _torque[1] = _torque[2] = 0.0;
	_torqueFunction = NULL;
	_inputTorquesInGlobalFrame = true;
	_recordAppliedLoads = false;
	_appliedTorqueStore = NULL;
}
//_____________________________________________________________________________
/**
 * Construct a description for the body kinematics files.
 */
void TorqueApplier::
constructDescription()
{
	char descrip[1024];

	strcpy(descrip,"\nThis file contains the torques ");
	strcat(descrip,"that were applied to the body segment,\n");
	strcat(descrip,"as a function of time.\n");
	strcat(descrip,"\nUnits are S.I. units (seconds, meters, Newtons, ...)");
	strcat(descrip,"\n\n");

	setDescription(descrip);
}

//_____________________________________________________________________________
/**
 * Construct column labels for the body kinematics files.
 */
void TorqueApplier::
constructColumnLabels()
{
	Array<std::string> labels;
	labels.append("time");
	labels.append("Torque_x");
	labels.append("Torque_y");
	labels.append("Torque_z");
	_appliedTorqueStore->setColumnLabels(labels);
}

//_____________________________________________________________________________
/**
 * Allocate storage for the kinematics.
 */
void TorqueApplier::
allocateStorage()
{
	_appliedTorqueStore = new Storage(1000,"Forces applied to " + _body->getName());
	_appliedTorqueStore->setDescription(getDescription());
}


//=============================================================================
// DESTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Delete storage objects.
 */
void TorqueApplier::
deleteStorage()
{
	if(_appliedTorqueStore!=NULL) { delete _appliedTorqueStore;  _appliedTorqueStore=NULL; }
}


//=============================================================================
// GET AND SET
//=============================================================================
//-----------------------------------------------------------------------------
// BODY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set to which body an external torque should be applied.
 *
 * @param aBody Pointer to the body to which an external torque should be applied.
 */
void TorqueApplier::
setBody(AbstractBody *aBody)
{
	_body = aBody;
}
//_____________________________________________________________________________
/**
 * Get to which body an external torque should be applied.
 *
 * @return Pointer to the body to which an external torque should be applied.
 */
AbstractBody* TorqueApplier::
getBody() const
{
	return(_body);
}

//-----------------------------------------------------------------------------
// TORQUE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the external torque to be applied, in the inertial reference frame.
 * 
 * @param aTorque External torque to be applied.
 */
void TorqueApplier::
setTorque(double aTorque[3])
{
	_torque[0] = aTorque[0];
	_torque[1] = aTorque[1];
	_torque[2] = aTorque[2];
}
//_____________________________________________________________________________
/**
 * Get the external torque to be applied, in the inertial reference frame.
 *
 * @return aTorque
 */
void TorqueApplier::
getTorque(double rTorque[3]) const
{
	rTorque[0] = _torque[0];
	rTorque[1] = _torque[1];
	rTorque[2] = _torque[2];
}
//-----------------------------------------------------------------------------
// TORQUE FUNCTION
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the vector function containing the (t,x,y,z) of the torque
 * to applied.
 *
 * @param aTorqueFunction Vector function describing the torque to applied
 * in global coordinates.
 */
void TorqueApplier::
setTorqueFunction(VectorFunction* aTorqueFunction)
{
	_torqueFunction = aTorqueFunction;
}
//_____________________________________________________________________________
/**
 * Get the vector function containing the (t,x,y,z) of the torque
 * to applied.
 *
 * @return rTorqueFunction.
 */
VectorFunction* TorqueApplier::
getTorqueFunction() const
{
	return(_torqueFunction);
}

//-----------------------------------------------------------------------------
// APPLIED TORQUE STORAGE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set whether or not to record the loads that are applied during an
 * integration.  Recording these loads takes a lot of memory as they
 * are stored every time the derivatives are evaluated (e.g., 6 times per
 * integration step).
 *
 * @param aTrueFalse Flag to turn on and off recording of the applied loads.
 */
void TorqueApplier::
setRecordAppliedLoads(bool aTrueFalse)
{
	_recordAppliedLoads = aTrueFalse;
}
//_____________________________________________________________________________
/**
 * Get whether or not to record the loads that are applied during an
 * integration.  Recording these loads takes a lot of memory as they
 * are stored every time the derivatives are evaluated (e.g., 6 times per
 * integration step).
 *
 * @return True if the applied loads are being stored, false otherwise.
 */
bool TorqueApplier::
getRecordAppliedLoads() const
{
	return(_recordAppliedLoads);
}
//_____________________________________________________________________________
/**
 * Get the applied torque storage.
 *
 * @return Applied torque storage.
 */
Storage* TorqueApplier::
getAppliedTorqueStorage()
{
	return(_appliedTorqueStore);
}

//-----------------------------------------------------------------------------
// STORAGE CAPACITY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the capacity increments of applied torque storage.
 *
 * @param aIncrement Increment by which storage capacities will be increased
 * when storage capcities run out.
 */
void TorqueApplier::
setStorageCapacityIncrements(int aIncrement)
{
	_appliedTorqueStore->setCapacityIncrement(aIncrement);
}

//-----------------------------------------------------------------------------
// RESET
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Reset the applied force storage
 *
 */
void TorqueApplier::
reset()
{
	_appliedTorqueStore->reset();
}



//-----------------------------------------------------------------------------
// COORDINATE FRAME OF INPUT TORQUES
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set whether the input torques are expressed in the global coordinate 
 * frame.
 *
 * @param inputTorquesInGlobalFrame flag indicates whether whether input torques
 * are expressed in the global coordinate frame
 */
void TorqueApplier::
setInputTorquesInGlobalFrame(bool aTrueFalse)
{
	_inputTorquesInGlobalFrame = aTrueFalse;
}
//_____________________________________________________________________________
/**
 * Get whether the input torques are expressed in the global coordinate 
 * frame.
 *
 * @return inputTorquesInGlobalFrame Flag
 * @see setInputTorquesInGlobalFrame()
 */
bool TorqueApplier::
getInputTorquesInGlobalFrame() const
{
	return(_inputTorquesInGlobalFrame);
}

//=============================================================================
// CALLBACKS
//=============================================================================
//_____________________________________________________________________________
/**
 * Callback called right after actuation has been applied by the model.
 *
 * *
 * @param aT Real time.
 * @param aX Controls.
 * @param aY States.
 */
void TorqueApplier::
applyActuation(double aT,double *aX,double *aY)
{
	double torque[3] = {0,0,0};
	double treal = aT*_model->getTimeNormConstant();

	if(_model==NULL) {
		printf("TorqueApplier.applyActuation: WARN- no model.\n");
		return;
	}
	if(!getOn()) return;

	if((aT>=getStartTime()) && (aT<getEndTime())){

		if(_torqueFunction!=NULL) {
			_torqueFunction->evaluate(&treal,torque);
			setTorque(torque);
		}
	
		if(_inputTorquesInGlobalFrame == false){
			_model->getDynamicsEngine().applyTorqueBodyLocal(*_body,_torque);
		} else {
			_model->getDynamicsEngine().applyTorque(*_body,_torque);
		}

		if(_recordAppliedLoads) _appliedTorqueStore->append(aT,3,_torque);

	}	
}

//=============================================================================
// IO
//=============================================================================
//_____________________________________________________________________________
/**
 * Print results.
 * 
 * The file names are constructed as
 * aDir + "/" + aBaseName + "_" + ComponentName + aExtension
 *
 * @param aDir Directory in which the results reside.
 * @param aBaseName Base file name.
 * @param aDT Desired time interval between adjacent storage vectors.  Linear
 * interpolation is used to print the data out at the desired interval.
 * @param aExtension File extension.
 *
 * @return 0 on success, -1 on error.
 */
int TorqueApplier::
printResults(const std::string &aBaseName,const std::string &aDir,double aDT,
				 const std::string &aExtension)
{
	// ACCELERATIONS
	_appliedTorqueStore->scaleTime(_model->getTimeNormConstant());
	Storage::printResult(_appliedTorqueStore,aBaseName+"_"+_body->getName()+"_appTorque",aDir,aDT,aExtension);

	return(0);
}




