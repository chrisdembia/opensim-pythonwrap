// suForceApplier.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson and May Liu
// 
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
//#include <iostream>
//#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Tools/rdMtx.h>
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include <NMBLTK/Tools/rdVectorFunction.h>
#include <NMBLTK/Tools/rdFunctionSet.h>
#include "suForceApplier.h"


using namespace std;


//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
suForceApplier::~suForceApplier()
{
	deleteStorage();
}
//_____________________________________________________________________________
/**
 * Construct a derivative callback instance for applying external forces
 * during an integration.
 *
 * @param aModel Model for which external forces are to be applied.
 */
suForceApplier::
suForceApplier(rdModel *aModel,int aBody) :
	rdDerivCallback(aModel)
{
	setNull();

	// BASE-CLASS MEMBER VARIABLES
	setType("suForceApplier");
	
	// STORAGE
	setBody(aBody);
	allocateStorage();

	// DESCRIPTION AND LABELS
	constructDescription();
	constructColumnLabels();


}

//_____________________________________________________________________________
/**
 * Construct a derivative callback instance for applying external forces
 * during an integration.
 *
 * @param aModel Model for which external forces are to be applied.
 * @param aBody Body to which external forces are to be applied.
 * @param aPoint Point at which external forces are to be applied.  This point
 * can be expressed in either local or global coordinates, but be sure the
 * _inputPositionsInLocalFrame is set appropriately.
 */
suForceApplier::
suForceApplier(rdModel *aModel,int aBody,double aPoint[3]) :
	rdDerivCallback(aModel)
{
	setNull();

	// MEMBER VARIABLES
	setBody(aBody);
	setPoint(aPoint);

	// STORAGE
	allocateStorage();

	// DESCRIPTION AND LABELS
	constructDescription();
	constructColumnLabels();

}

//_____________________________________________________________________________
/**
 * Construct a derivative callback instance for applying external forces
 * during an integration.
 *
 * @param aModel Model for which external forces are to be applied.
 * @param aBody Body to which external forces are to be applied.
 * @param aPoint Point at which external forces are to be applied.  This point
 * can be expressed in either local or global coordinates, but be sure the
 * _inputPositionsInLocalFrame is set appropriately.
 *
 * @param aForce Force to be applied expressed in global coordinates.  This force
 * can be expressed in either local or global coordinates, but be sure the
 * _inputForcesInGlobalFrame is set appropriately.
 */
suForceApplier::
suForceApplier(rdModel *aModel,int aBody,double aPoint[3],double aForce[3]) :
	rdDerivCallback(aModel)
{
	setNull();

	// MEMBER VARIABLES
	setBody(aBody);
	setPoint(aPoint);
	setForce(aForce);

	// STORAGE
	allocateStorage();

	// DESCRIPTION AND LABELS
	constructDescription();
	constructColumnLabels();

}

//_____________________________________________________________________________
/**
 * Construct a derivative callback instance for applying external forces
 * during an integration.
 *
 * @param aModel Model for which external forces are to be applied.
 * @param aBody Body to which external forces are to be applied.
 * @param aPointFunction containing (t,x,y,z) of points at which external
 * forces are to be applied.  These points can be expressed in either local or global
 * coordinates, but be sure the _inputPositionsInLocalFrame is set appropriately. If a 
 * NULL point set is sent in, the  force will be applied at the body COM.
 * @param aForceFunction containing (t,x,y,z) of force to be applied.  This force
 * can be expressed in either local or global coordinates, but be sure the
 * _inputForcesInGlobalFrame is set appropriately.
 */
suForceApplier::
suForceApplier(rdModel *aModel,int aBody,rdVectorFunction* aPointFunction,rdVectorFunction* aForceFunction) :
	rdDerivCallback(aModel)
{
	setNull();

	// MEMBER VARIABLES
	setBody(aBody);
	if(aPointFunction != NULL)
		setPointFunction(aPointFunction);
	setForceFunction(aForceFunction);

	// STORAGE
	allocateStorage();

	// DESCRIPTION AND LABELS
	constructDescription();
	constructColumnLabels();

}

//_____________________________________________________________________________
/**
 * Construct a derivative callback instance for applying external forces
 * during an integration.
 *
 * @param aModel Model for which external forces are to be applied.
 * @param aBody Body to which external forces are to be applied.
 * @param aPoint Point at which external forces are to be applied.  This point
 * can be expressed in either local or global coordinates, but be sure the
 * _inputPositionsInLocalFrame is set appropriately.
 *
 * @param aForceFunction containing (t,x,y,z) of force to be applied.  This force
 * can be expressed in either local or global coordinates, but be sure the
 * _inputForcesInGlobalFrame is set appropriately.
 */
suForceApplier::
suForceApplier(rdModel *aModel,int aBody,double aPoint[3],rdVectorFunction* aForceFunction) :
	rdDerivCallback(aModel)
{
	setNull();

	// MEMBER VARIABLES
	setBody(aBody);
	setPoint(aPoint);
	setForceFunction(aForceFunction);
	
	// STORAGE
	allocateStorage();

	// DESCRIPTION AND LABELS
	constructDescription();
	constructColumnLabels();

}

//_____________________________________________________________________________
/**
 * Construct a derivative callback instance for applying external forces
 * during an integration.
 *
 * @param aModel Model for which external forces are to be applied.
 * @param aBody Body to which external forces are to be applied.
 * @param aPointStorage rdStorage containing (t,x,y,z) of points at which external
 * forces are to be applied.  These points can be expressed in either local or global
 * coordinates, but be sure the _inputPositionsInLocalFrame is set appropriately.
 *
 * @param aForceStorage rdStorage containing (t,x,y,z) of force to be applied.  This force
 * can be expressed in either local or global coordinates, but be sure the
 * _inputForcesInGlobalFrame is set appropriately.
 */
suForceApplier::
suForceApplier(rdModel *aModel,int aBody,rdStorage* aPointStorage,rdStorage* aForceStorage) :
	rdDerivCallback(aModel)
{
	setNull();

	// MEMBER VARIABLES
	setBody(aBody);
	if(aPointStorage != NULL)
		setPointStorage(aPointStorage);
	setForceStorage(aForceStorage);
	
	// STORAGE
	allocateStorage();

	// DESCRIPTION AND LABELS
	constructDescription();
	constructColumnLabels();

}

//_____________________________________________________________________________
/**
 * Construct a derivative callback instance for applying external forces
 * during an integration.
 *
 * @param aModel Model for which external forces are to be applied.
 * @param aBody Body to which external forces are to be applied.
 * @param aPoint Point at which external forces are to be applied.  This point
 * can be expressed in either local or global coordinates, but be sure the
 * _inputPositionsInLocalFrame is set appropriately.
 * @param aForceStorage rdStorage containing (t,x,y,z) of force to be applied.  This force
 * can be expressed in either local or global coordinates, but be sure the
 * _inputForcesInGlobalFrame is set appropriately.
 */
suForceApplier::
suForceApplier(rdModel *aModel,int aBody,double aPoint[3],rdStorage* aForceStorage) :
	rdDerivCallback(aModel)
{
	setNull();

	// MEMBER VARIABLES
	setBody(aBody);
	setPoint(aPoint);
	setForceStorage(aForceStorage);
	
	// STORAGE
	allocateStorage();

	// DESCRIPTION AND LABELS
	constructDescription();
	constructColumnLabels();

}
//_____________________________________________________________________________
/**
 * Construct a derivative callback instance for applying external forces
 * during an integration.
 *
 * @param aModel Model for which external forces are to be applied.
 * @param aBody Body to which external forces are to be applied.
 * @param aPointStorage rdStorage containing (t,x,y,z) of points at which external
 * forces are to be applied.  These points can be expressed in either local or global
 * coordinates, but be sure the _inputPositionsInLocalFrame is set appropriately.
 * @param aForceStorage rdStorage containing (t,x,y,z) of force to be applied.  This force
 * can be expressed in either local or global coordinates, but be sure the
 * _inputForcesInGlobalFrame is set appropriately.
 */
suForceApplier::
suForceApplier(rdModel *aModel,int aBody,rdFunctionSet* aPointSet,rdFunctionSet* aForceSet) :
	rdDerivCallback(aModel)
{
	setNull();

	// MEMBER VARIABLES
	setBody(aBody);
	if(aPointSet != NULL)
		setPointSet(aPointSet);
	setForceSet(aForceSet);
	
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
void suForceApplier::
setNull()
{
	setType("suForceApplier");
	_body = 0;	
	_point[0] = _point[1] = _point[2] = 0.0;
	_force[0] = _force[1] = _force[2] = 0.0;
	_forceFunction = NULL;
	_pointFunction = NULL;
	_forceStorage = NULL;
	_pointStorage = NULL;
	_inputPositionsInLocalFrame = true;
	_inputForcesInGlobalFrame = true;
	_pointSet = NULL;
	_forceSet = NULL;
}

//_____________________________________________________________________________
/**
 * Construct a description for the body kinematics files.
 */
void suForceApplier::
constructDescription()
{
	char descrip[1024];

	strcpy(descrip,"\nThis file contains the forces ");
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
void suForceApplier::
constructColumnLabels()
{
	char labels[2048];

	strcpy(labels,"time\tForce_x\tForce_y\tForce_z\n");

	_appliedForceStore->setColumnLabels(labels);
}

//_____________________________________________________________________________
/**
 * Allocate storage for the kinematics.
 */
void suForceApplier::
allocateStorage()
{
	char bodyName[2048];
	char title[2048];
	sprintf(title,"Forces applied to ");
	sprintf(bodyName,"body_%d",_body);
	strcat(title, bodyName);
	_appliedForceStore = new rdStorage(1000,title);
	_appliedForceStore->setDescription(getDescription());
	_appliedForceStore->setColumnLabels(_appliedForceStore->getColumnLabels());

//
}


//=============================================================================
// DESTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Delete storage objects.
 */
void suForceApplier::
deleteStorage()
{
	if(_appliedForceStore!=NULL) { delete _appliedForceStore;  _appliedForceStore=NULL; }
}

//=============================================================================
// GET AND SET
//=============================================================================
//-----------------------------------------------------------------------------
// BODY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set to which body an external force should be applied.
 *
 * @param aIndex Index of the body to which an external force should be applied.
 */
void suForceApplier::
setBody(int aBody)
{
	_body = aBody;
}
//_____________________________________________________________________________
/**
 * Get to which body an external force should be applied.
 *
 * @return aIndex Index of the body to which an external force should be applied.
 */
int suForceApplier::
getBody() const
{
	return(_body);
}

//-----------------------------------------------------------------------------
// POINT OF APPLICATION
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the point, in local body coordinates, at which the external force should
 * be applied.
 *
 * @param aPoint Point at which an external force should be applied.
 */
void suForceApplier::
setPoint(double aPoint[3])
{
	_point[0] = aPoint[0];
	_point[1] = aPoint[1];
	_point[2] = aPoint[2];

}
//_____________________________________________________________________________
/**
 * Get the point, in local body coordinates, at which the external force should
 * be applied..
 *
 * @return aPoint Point at which an external force should be applied.
 */
void suForceApplier::
getPoint(double rPoint[3]) const
{
	rPoint[0] = _point[0];
	rPoint[1] = _point[1];
	rPoint[2] = _point[2];
}

//-----------------------------------------------------------------------------
// COORDINATE FRAME OF INPUT POSITIONS AND FORCES
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set whether the input positions are expressed in the local body coordinate 
 * frame.
 *
 * @param inputPosiitonsInLocalFrame flag indicates whether whether input forces
 * are expressed in the local body coordinate frame
 */
void suForceApplier::
setInputPositionsInLocalFrame(bool aTrueFalse)
{
	_inputPositionsInLocalFrame = aTrueFalse;
}
//_____________________________________________________________________________
/**
 * Set whether the input positions are expressed in the local body coordinate 
 * frame.
 *
 * @return inputPositionsInLocalFrame Flag
 * @see setPointInLocalFrame()
 */
bool suForceApplier::
getInputPositionsInLocalFrame() const
{
	return(_inputPositionsInLocalFrame);
}
//_____________________________________________________________________________
/**
 * Set whether the input forces are expressed in the global coordinate 
 * frame.
 *
 * @param inputForcesInGlobalFrame flag indicates whether whether input forces
 * are expressed in the global coordinate frame
 */
void suForceApplier::
setInputForcesInGlobalFrame(bool aTrueFalse)
{
	_inputForcesInGlobalFrame = aTrueFalse;
}
//_____________________________________________________________________________
/**
 * Get whether the input forces are expressed in the global coordinate 
 * frame.
 *
 * @return inputForcesInGlobalFrame Flag
 * @see setInputForcesInGlobalFrame()
 */
bool suForceApplier::
getInputForcesInGlobalFrame() const
{
	return(_inputForcesInGlobalFrame);
}

//-----------------------------------------------------------------------------
// FORCE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the external force to be applied, in the inertial reference frame.
 * 
 * @param aForce External force to be applied.
 */
void suForceApplier::
setForce(double aForce[3])
{
	_force[0] = aForce[0];
	_force[1] = aForce[1];
	_force[2] = aForce[2];
}
//_____________________________________________________________________________
/**
 * Get the external force to be applied, in the inertial reference frame.
 *
 * @return aForce
 */
void suForceApplier::
getForce(double rForce[3]) const
{
	rForce[0] = _force[0];
	rForce[1] = _force[1];
	rForce[2] = _force[2];
}
//-----------------------------------------------------------------------------
// POINT FUNCTION
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the vector function containing the (t,x,y,z) of the point at which the force
 * should be applied in the local coordinate frame.
 *
 * @param aPointFunction containing force application point function.
 */
void suForceApplier::
setPointFunction(rdVectorFunction* aPointFunction)
{
	_pointFunction = aPointFunction;
}
//_____________________________________________________________________________
/**
 * Get the vector function containing the (t,x,y,z) of the point at which the force
 * should be applied in the local coordinate frame.
 *
 * @return aPointFunction.
 */
rdVectorFunction* suForceApplier::
getPointFunction() const
{
	return(_pointFunction);
}
//-----------------------------------------------------------------------------
// FORCE FUNCTION
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the vector function containing the (t,x,y,z) of the force
 * to applied.
 *
 * @param aForceFunction containing function describing the force to applied
 * in global coordinates.
 */
void suForceApplier::
setForceFunction(rdVectorFunction* aForceFunction)
{
	_forceFunction = aForceFunction;
}
//_____________________________________________________________________________
/**
 * Get the vector function containing the (t,x,y,z) of the force
 * to applied.
 *
 * @return aForceFunction.
 */
rdVectorFunction* suForceApplier::
getForceFunction() const
{
	return(_forceFunction);
}

//-----------------------------------------------------------------------------
// POINTSTORAGE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the rdStorage containing the (t,x,y,z) of the point at which the force
 * should be applied.
 *
 * @param aPointStorage rdStorage containing force application point function.
 */
void suForceApplier::
setPointStorage(rdStorage* aPointStorage)
{
	_pointStorage = aPointStorage;
}
//_____________________________________________________________________________
/**
 * Get the rdStorage containing the (t,x,y,z) of the point at which the force
 * should be applied.
 *
 * @return aPointStorage.
 */
rdStorage* suForceApplier::
getPointStorage() const
{
	return(_pointStorage);
}
//-----------------------------------------------------------------------------
// FORCESTORAGE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the rdStorage containing the (t,x,y,z) of the force
 * to applied.
 *
 * @param aForceStorage rdStorage containing  the force to applied
 * in global coordinates.
 */
void suForceApplier::
setForceStorage(rdStorage* aForceStorage)
{
	_forceStorage = aForceStorage;
}
//_____________________________________________________________________________
/**
 * Get the rdStoarge containing the (t,x,y,z) of the force
 * to applied.
 *
 * @return aForceStorage.
 */
rdStorage* suForceApplier::
getForceStorage() const
{
	return(_forceStorage);
}
//-----------------------------------------------------------------------------
// POINT SET
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the vector function containing the (t,x,y,z) of the point at which the force
 * should be applied in the local coordinate frame.
 *
 * @param aPointFunction containing force application point function.
 */
void suForceApplier::
setPointSet(rdFunctionSet* aPointSet)
{
	_pointSet = aPointSet;
}
//_____________________________________________________________________________
/**
 * Get the vector function containing the (t,x,y,z) of the point at which the force
 * should be applied in the local coordinate frame.
 *
 * @return aPointFunction.
 */
rdFunctionSet* suForceApplier::
getPointSet() const
{
	return(_pointSet);
}
//-----------------------------------------------------------------------------
// FORCE SET
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the vector function containing the (t,x,y,z) of the force
 * to applied.
 *
 * @param aForceFunction containing function describing the force to applied
 * in global coordinates.
 */
void suForceApplier::
setForceSet(rdFunctionSet* aForceSet)
{
	_forceSet = aForceSet;
}
//_____________________________________________________________________________
/**
 * Get the vector function containing the (t,x,y,z) of the force
 * to applied.
 *
 * @return aForceFunction.
 */
rdFunctionSet* suForceApplier::
getForceSet() const
{
	return(_forceSet);
}
//-----------------------------------------------------------------------------
// APPLIED FORCE STORAGE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the applied force storage.
 *
 * @return Applied force storage.
 */
rdStorage* suForceApplier::
getAppliedForceStorage()
{
	return(_appliedForceStore);
}
//-----------------------------------------------------------------------------
// STORAGE CAPACITY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the capacity increments of applied force storage.
 *
 * @param aIncrement Increment by which storage capacities will be increased
 * when storage capcities run out.
 */
void suForceApplier::
setStorageCapacityIncrements(int aIncrement)
{
	_appliedForceStore->setCapacityIncrement(aIncrement);
}

//-----------------------------------------------------------------------------
// RESET
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Reset the applied force storage
 *
 */
void suForceApplier::
reset()
{
	_appliedForceStore->reset();
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
void suForceApplier::
applyActuation(double aT,double *aX,double *aY)
{
	int i;
	double force[3] = {0,0,0};
	double point[3] = {0,0,0};
	const int ground = _model->getGroundID();
	double posBodyCOMLocal[3] = {0,0,0};
	double posBodyCOMGlobal[3];
	double posPointRelBodyCOMGlobal[3];
	double posPointRelBodyCOMLocal[3];
	double treal = aT*_model->getTimeNormConstant();
	
	if(_model==NULL) {
		printf("suForceApplier.applyActuation: WARN- no model.\n");
		return;
	}
	if(!getOn()) return;

	if((aT>=getStartTime()) && (aT<getEndTime())){

		if(_forceFunction!=NULL) {
			_forceFunction->evaluate(&treal,force);
			setForce(force);
		}
		if(_pointFunction!=NULL) {
			_pointFunction->evaluate(&treal,point);
			setPoint(point);
		}

		if(_forceStorage!=NULL) {
			_forceStorage->getDataAtTime(aT*_model->getTimeNormConstant(),3,force);
			setForce(force);
		}
		if(_pointStorage!=NULL) {
			_pointStorage->getDataAtTime(aT*_model->getTimeNormConstant(),3,point);
			setPoint(point);
		}

		if(_forceSet!=NULL) {
			for(i=0;i<3;i++){
				force[i] =_forceSet->evaluate(i,0,aT*_model->getTimeNormConstant());
			}
			setForce(force);
		}
		if(_pointSet!=NULL) {
			for(i=0;i<3;i++){
				point[i] =_pointSet->evaluate(i,0,aT*_model->getTimeNormConstant());
			}
			setPoint(point);
		}

		if(_inputPositionsInLocalFrame == false){
			_model->getPosition(_body,posBodyCOMLocal,posBodyCOMGlobal);
			//cout<<"bodyGlobal = "<<posBodyCOMGlobal[0]<<", "<<posBodyCOMGlobal[1]<<", "<<posBodyCOMGlobal[2]<<endl;
			rdMtx::Subtract(1,3,_point,posBodyCOMGlobal,posPointRelBodyCOMGlobal);
			//cout<<"pointRelBodyGlobal = "<<posPointRelBodyCOMGlobal[0]<<", "<<posPointRelBodyCOMGlobal[1]<<", "<<posPointRelBodyCOMGlobal[2]<<endl;
			_model->transform(ground,posPointRelBodyCOMGlobal,_body,posPointRelBodyCOMLocal);
			setPoint(posPointRelBodyCOMLocal);
		}

		if(_inputForcesInGlobalFrame == false){
			_model->applyForceBodyLocal(_body,_point,_force);
		} else {
			_model->applyForce(_body,_point,_force);
		}
		_appliedForceStore->append(aT,3,_force);
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
int suForceApplier::
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
	_appliedForceStore->scaleTime(_model->getTimeNormConstant());
	if(aExtension==NULL) {
		sprintf(name,"%s/%s_%s_appForce",path,aBaseName,bodyName);
	} else {
		sprintf(name,"%s/%s_%s_appForce%s",path,aBaseName,bodyName,aExtension);
	}
	if(aDT<=0.0) {
		if(_appliedForceStore!=NULL)  _appliedForceStore->print(name);
	} else {
		if(_appliedForceStore!=NULL)  _appliedForceStore->print(name,aDT);
	}

	return(0);
}





