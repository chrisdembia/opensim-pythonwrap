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
#include <NMBLTK/Tools/rdVectorGCVSplineR1R3.h>
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
	_inputForcesInGlobalFrame = true;
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



//-----------------------------------------------------------------------------
// COMPUTE POSITION AND VELOCITY FUNCTIONS 
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Compute the position and velocity functions that set the position and
 * velocity of the point at which the linear spring applies its force.
 * This method takes the time histories of a point's
 * position and velocity in the inertial frame and converts them to the local
 * (body) frame.
 *
 * @param aQStore Storage containing the time history of generalized
 * coordinates for the model. Note that all generalized coordinates must
 * be specified and in radians and Euler parameters.
 * @param aUStore Stoarge containing the time history of generalized
 * speeds for the model.  Note that all generalized speeds must
 * be specified and in radians.
 * @param aPStore Storage containing the time history of the position at
 * which the force is to be applied in the global frame.
 */
void suForceApplier::
computePointFunction(
	rdStorage *aQStore,rdStorage *aUStore,rdVectorFunction &aPGlobal)
{
	int i;
	int nq = _model->getNQ();
	int nu = _model->getNU();
	int size = aQStore->getSize();
	int ground = _model->getGroundID();
	rdArray<int> derivWRT(0,1);
	rdArray<double> t(0.0,1);
	rdArray<double> q(0.0,nq),u(0.0,nu);
	rdArray<double> comGlobal(0.0,3),origin(0.0,3);
	rdArray<double> pGlobal(0.0,3),pLocal(0.0,3);
	rdArray<double> vGlobal(0.0,3),vLocal(0.0,3);
	rdStorage pStore,vStore;
	for(i=0;i<size;i++) {
		// Set the model state
		aQStore->getTime(i,*(&t[0]));
		aQStore->getData(i,nq,&q[0]);
		aUStore->getData(i,nu,&u[0]);
		_model->setConfiguration(&q[0],&u[0]);

		// Position
		_model->getPosition(_body,&origin[0],&comGlobal[0]);
		aPGlobal.evaluate(t,pGlobal);
		rdMtx::Subtract(1,3,&pGlobal[0],&comGlobal[0],&pLocal[0]);
		_model->transform(ground,&pLocal[0],_body,&pLocal[0]);
		pStore.append(t[0],3,&pLocal[0]);
	}

	// CREATE POSITION FUNCTION
	double *time=NULL;
	double *p0=0,*p1=0,*p2=0;
	int padSize = size / 2;
	if(padSize>100) padSize = 100;
	pStore.pad(padSize);
	size = pStore.getTimeColumn(time);
	pStore.getDataColumn(0,p0);
	pStore.getDataColumn(1,p1);
	pStore.getDataColumn(2,p2);
	rdVectorGCVSplineR1R3 *pFunc = new rdVectorGCVSplineR1R3(3,size,time,p0,p1,p2);
	setPointFunction(pFunc);

	for(i=0;i<size;i++) {
		aQStore->getTime(i,*(&t[0]));
		pFunc->evaluate(t,pLocal);
		pFunc->evaluate(t,vLocal,derivWRT);
	}
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
	double force[3] = {0,0,0};
	double point[3] = {0,0,0};
	const int ground = _model->getGroundID();
	double posBodyCOMLocal[3] = {0,0,0};
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





