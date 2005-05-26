// suTorqueApplier.cpp
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
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Tools/rdMtx.h>
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include <NMBLTK/Tools/rdVectorFunction.h>
#include "suTorqueApplier.h"

//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
suTorqueApplier::~suTorqueApplier()
{
	deleteStorage();
}
//_____________________________________________________________________________
/**
 * Construct a derivative callback instance for applying external torques
 * during an integration.
 *
 * @param aModel Model for which external torques are to be applied.
 */
suTorqueApplier::
suTorqueApplier(rdModel *aModel) :
	rdDerivCallback(aModel)
{
	setNull();

	// BASE-CLASS MEMBER VARIABLES
	setType("suTorqueApplier");

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
 * @param aModel Model for which external torques are to be applied.
 * @param aBody Body to which external torques are to be applied.
 */
suTorqueApplier::
suTorqueApplier(rdModel *aModel,int aBody) :
	rdDerivCallback(aModel)
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
 * @param aModel Model for which external torques are to be applied.
 * @param aBody Body to which external torques are to be applied.
 * @param aTorque Torque to be applied.  This torque can be expressed in 
 *  either global or local coordinates, but be sure that _inputTorquesInGlobalFrame
 *  is set correctly.
 */
suTorqueApplier::
suTorqueApplier(rdModel *aModel,int aBody,double aTorque[3]) :
	rdDerivCallback(aModel)
{
	setNull();

	// MEMBER VARIABLES
	setBody(aBody);
	setTorque(aTorque);

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
 * @param aModel Model for which external torques are to be applied.
 * @param aBody Body to which external torques are to be applied.
 * @param aTorqueFunction Vector function containing (t,x,y,z) of torque to be applied.  
 *  This torque can be expressed in either global or local coordinates, but be sure 
 *  that _inputTorquesInGlobalFrame is set correctly.
 */
suTorqueApplier::
suTorqueApplier(rdModel *aModel,int aBody,rdVectorFunction* aTorqueFunction) :
	rdDerivCallback(aModel)
{
	setNull();

	// MEMBER VARIABLES
	setBody(aBody);
	setTorqueFunction(aTorqueFunction);

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
 * @param aModel Model for which external torques are to be applied.
 * @param aBody Body to which external torques are to be applied.
 * @param aTorqueStorage rdStorage containing (t,x,y,z) of torque to be applied.  
 *  This torque can be expressed in either global or local coordinates, but be sure 
 *  that _inputTorquesInGlobalFrame is set correctly.
 */
suTorqueApplier::
suTorqueApplier(rdModel *aModel,int aBody,rdStorage* aTorqueStorage) :
	rdDerivCallback(aModel)
{
	setNull();

	// MEMBER VARIABLES
	setBody(aBody);
	setTorqueStorage(aTorqueStorage);

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
 * @param aModel Model for which external torques are to be applied.
 * @param aBody Body to which external torques are to be applied.
 * @param aTorqueFunction Vector function containing (t,x,y,z) of torque to be applied.  
 *  This torque can be expressed in either global or local coordinates, but be sure 
 *  that _inputTorquesInGlobalFrame is set correctly.
 */
suTorqueApplier::
suTorqueApplier(rdModel *aModel,int aBody,rdFunctionSet* aTorqueSet) :
	rdDerivCallback(aModel)
{
	setNull();

	// MEMBER VARIABLES
	setBody(aBody);
	setTorqueSet(aTorqueSet);

	// STORAGE
	allocateStorage();

	// DESCRIPTION AND LABELS
	constructDescription();
	constructColumnLabels();

}

//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Set member variables to approprate NULL values.
 */
void suTorqueApplier::
setNull()
{
	setType("suTorqueApplier");
	_body = 0;	
	_torque[0] = _torque[1] = _torque[2] = 0.0;
	setStartTime(0.0);
	setEndTime(1.0);
	_torqueFunction = NULL;
	_torqueStorage = NULL;
	_torqueSet = NULL;
	_inputTorquesInGlobalFrame = true;
}
//_____________________________________________________________________________
/**
 * Construct a description for the body kinematics files.
 */
void suTorqueApplier::
constructDescription()
{
	char descrip[1024];
	char tmp[2048];

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
void suTorqueApplier::
constructColumnLabels()
{
	char labels[2048];

	strcpy(labels,"time\tTorque_x\tTorque_y\tTorque_z\n");

	_appliedTorqueStore->setColumnLabels(labels);
}

//_____________________________________________________________________________
/**
 * Allocate storage for the kinematics.
 */
void suTorqueApplier::
allocateStorage()
{
	char bodyName[2048];
	char title[2048];
	sprintf(title,"Forces applied to ");
	sprintf(bodyName,"body_%d",_body);
	strcat(title, bodyName);
	_appliedTorqueStore = new rdStorage(1000,title);
	_appliedTorqueStore->setDescription(getDescription());
	_appliedTorqueStore->setColumnLabels(_appliedTorqueStore->getColumnLabels());

//
}


//=============================================================================
// DESTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Delete storage objects.
 */
void suTorqueApplier::
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
 * @param aIndex Index of the body to which an external torque should be applied.
 */
void suTorqueApplier::
setBody(int aBody)
{
	_body = aBody;
}
//_____________________________________________________________________________
/**
 * Get to which body an external torque should be applied.
 *
 * @return aIndex Index of the body to which an external torque should be applied.
 */
int suTorqueApplier::
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
void suTorqueApplier::
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
void suTorqueApplier::
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
void suTorqueApplier::
setTorqueFunction(rdVectorFunction* aTorqueFunction)
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
rdVectorFunction* suTorqueApplier::
getTorqueFunction() const
{
	return(_torqueFunction);
}


//-----------------------------------------------------------------------------
// TORQUESTORAGE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the rdStorage containing the (t,x,y,z) of the torque
 * to applied.
 *
 * @param aTorqueStorage rdStorage containing  the torque to applied
 * in global coordinates.
 */
void suTorqueApplier::
setTorqueStorage(rdStorage* aTorqueStorage)
{
	_torqueStorage = aTorqueStorage;
}
//_____________________________________________________________________________
/**
 * Get the rdStoarge containing the (t,x,y,z) of the torque
 * to applied.
 *
 * @return aTorqueStorage.
 */
rdStorage* suTorqueApplier::
getTorqueStorage() const
{
	return(_torqueStorage);
}
//-----------------------------------------------------------------------------
// TORQUE SET
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the vector function containing the (t,x,y,z) of the torque
 * to applied.
 *
 * @param aTorqueFunction Vector function describing the torque to applied
 * in global coordinates.
 */
void suTorqueApplier::
setTorqueSet(rdFunctionSet* aTorqueSet)
{
	_torqueSet = aTorqueSet;
}
//_____________________________________________________________________________
/**
 * Get the vector function containing the (t,x,y,z) of the torque
 * to applied.
 *
 * @return rTorqueFunction.
 */
rdFunctionSet* suTorqueApplier::
getTorqueSet() const
{
	return(_torqueSet);
}

//-----------------------------------------------------------------------------
// APPLIED TORQUE STORAGE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the applied torque storage.
 *
 * @return Applied torque storage.
 */
rdStorage* suTorqueApplier::
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
void suTorqueApplier::
setStorageCapacityIncrements(int aIncrement)
{
	_appliedTorqueStore->setCapacityIncrement(aIncrement);
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
void suTorqueApplier::
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
bool suTorqueApplier::
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
void suTorqueApplier::
applyActuation(double aT,double *aX,double *aY)
{
	int i;
	double torque[3] = {0,0,0};
	const int ground = _model->getGroundID();

	if(_model==NULL) {
		printf("suTorqueApplier.applyActuation: WARN- no model.\n");
		return;
	}
	if(!getOn()) return;

	if((aT>=getStartTime()) && (aT<getEndTime())){

		if(_torqueFunction!=NULL) {
			const rdArray<double> &torqueArray = _torqueFunction->evaluate(aT*_model->getTimeNormConstant());
			for(i=0;i<3;i++){
				torque[i] = torqueArray.get(i);
			}
			setTorque(torque);
		}

		if(_torqueSet!=NULL) {
			for(i=0;i<3;i++){
				torque[i] =_torqueSet->evaluate(i,0,aT*_model->getTimeNormConstant());
			}
			setTorque(torque);
		}

		if(_torqueStorage!=NULL) {
			_torqueStorage->getDataAtTime(aT*_model->getTimeNormConstant(),3,torque);
			setTorque(torque);
		}
		
		if(_inputTorquesInGlobalFrame == false){
			_model->applyTorqueBodyLocal(_body,_torque);
		} else {
			_model->applyTorque(_body,_torque);
		}

		_appliedTorqueStore->append(aT,3,_torque);

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
int suTorqueApplier::
printResults(const char *aBaseName,const char *aDir,double aDT,
				 const char *aExtension)
{
	if(aBaseName==NULL) return(-1);

	// CONSTRUCT PATH
	char path[2048],name[2048],bodyName[2048];
	if(aDir==NULL) {
		strcpy(path,".");
	} else {
		strcpy(path,aDir);
	}

	sprintf(bodyName,"body_%d",_body);


	// ACCELERATIONS
	_appliedTorqueStore->scaleTime(_model->getTimeNormConstant());
	if(aExtension==NULL) {
		sprintf(name,"%s/%s_%s_appTorque",path,aBaseName,bodyName);
	} else {
		sprintf(name,"%s/%s_%s_appTorque%s",path,aBaseName,bodyName,aExtension);
	}
	if(aDT<=0.0) {
		if(_appliedTorqueStore!=NULL)  _appliedTorqueStore->print(name);
	} else {
		if(_appliedTorqueStore!=NULL)  _appliedTorqueStore->print(name,aDT);
	}

	return(0);
}




