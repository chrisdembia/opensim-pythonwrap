// suGeneralizedForceApplier.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson and Saryn Goldberg
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
#include "suGeneralizedForceApplier.h"

//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
suGeneralizedForceApplier::~suGeneralizedForceApplier()
{
	deleteStorage();
}
//_____________________________________________________________________________
/**
 * Construct a derivative callback instance for applying a generalized force
 * during an integration.
 *
 * @param aModel Model for which generalized forces are to be applied.
 */
suGeneralizedForceApplier::
suGeneralizedForceApplier(rdModel *aModel) :
	rdDerivCallback(aModel)
{
	setNull();

	// BASE-CLASS MEMBER VARIABLES
	setType("suGeneralizedForceApplier");

	// STORAGE
	allocateStorage();

	// DESCRIPTION AND LABELS
	constructDescription();
	constructColumnLabels();
}

//_____________________________________________________________________________
/**
 * Construct a derivative callback instance for applying a generalized forces
 * during an integration.
 *
 * @param aModel Model for which generalized forces are to be applied.
 * @param aGenCoord Generalized coordinate to which generalized forces are to be applied.
 */
suGeneralizedForceApplier::
suGeneralizedForceApplier(rdModel *aModel,int aGenCoord) :
	rdDerivCallback(aModel)
{
	setNull();

	// MEMBER VARIABLES
	setGeneralizedCoordinate(aGenCoord);

	// STORAGE
	allocateStorage();

	// DESCRIPTION AND LABELS
	constructDescription();
	constructColumnLabels();
}

//_____________________________________________________________________________
/**
 * Construct a derivative callback instance for applying generalized forces
 * during an integration.
 *
 * @param aModel Model for which generalized forces are to be applied.
 * @param aGenCoord Generalized coordinate to which generalized forces are to be applied.
 * @param aGeneralizedForce Generalized force to be applied
 */
suGeneralizedForceApplier::
suGeneralizedForceApplier(rdModel *aModel,int aGenCoord,double aGeneralizedForce) :
	rdDerivCallback(aModel)
{
	setNull();

	// MEMBER VARIABLES
	setGeneralizedCoordinate(aGenCoord);
	setGeneralizedForce(aGeneralizedForce);

	// STORAGE
	allocateStorage();

	// DESCRIPTION AND LABELS
	constructDescription();
	constructColumnLabels();

}

//_____________________________________________________________________________
/**
 * Construct a derivative callback instance for applying generalized forces
 * during an integration. 
 *
 * @param aModel Model for which generalized forces are to be applied.
 * @param aGenCoord Generalized coordinate to which generalized forces are to be applied.
 * @param aGeneralizedForceStorage rdStorage containing (t,x,y,z) of generalized force to be applied 
 * @param aIndex Collumn of storage corresponding to generalized force
 */
suGeneralizedForceApplier::
suGeneralizedForceApplier(rdModel *aModel,int aGenCoord,rdStorage* aGeneralizedForceStorage,int aIndex) :
	rdDerivCallback(aModel)
{
	setNull();

	// MEMBER VARIABLES
	setGeneralizedCoordinate(aGenCoord);
	setGeneralizedForceStorage(aGeneralizedForceStorage);
	setGeneralizedForceIndex(aIndex);

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
void suGeneralizedForceApplier::
setNull()
{
	setType("suGeneralizedForceApplier");
	_genCoord = 0;
	_scaleFactor = 1.0;
	_generalizedForce = 0.0;
	setStartTime(0.0);
	setEndTime(1.0);
	_genForceIndex = 0;
	_generalizedForceStorage = NULL;
	_appliedGeneralizedForceStore = NULL;
	_aTSet = -1.0;
}
//_____________________________________________________________________________
/**
 * Construct a description for the generalized force files.
 */
void suGeneralizedForceApplier::
constructDescription()
{
	char descrip[1024];
	char tmp[2048];

	strcpy(descrip,"\nThis file contains the generalized forces ");
	strcat(descrip,"that were applied to the body segment,\n");
	strcat(descrip,"as a function of time.\n");
	strcat(descrip,"\nUnits are S.I. units (seconds, meters, Newtons, ...)");
	strcat(descrip,"\n\n");

	setDescription(descrip);
}

//_____________________________________________________________________________
/**
 * Construct column labels for the generalized force files.
 */
void suGeneralizedForceApplier::
constructColumnLabels()
{
	char labels[2048];

	strcpy(labels,"time\tGenForce\n");

	_appliedGeneralizedForceStore->setColumnLabels(labels);
}

//_____________________________________________________________________________
/**
 * Allocate storage for the generalized forces.
 */
void suGeneralizedForceApplier::
allocateStorage()
{
	char genCoordName[2048];
	char title[2048];
	sprintf(title,"Generalized forces applied to ");
	sprintf(genCoordName,"genCoord_%d",_genCoord);
	strcat(title, genCoordName);
	_appliedGeneralizedForceStore = new rdStorage(1000,title);
	_appliedGeneralizedForceStore->setDescription(getDescription());
	_appliedGeneralizedForceStore->setColumnLabels(_appliedGeneralizedForceStore->getColumnLabels());

//
}


//=============================================================================
// DESTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Delete storage objects.
 */
void suGeneralizedForceApplier::
deleteStorage()
{
	if(_appliedGeneralizedForceStore!=NULL) { delete _appliedGeneralizedForceStore;  _appliedGeneralizedForceStore=NULL; }
}


//=============================================================================
// GET AND SET
//=============================================================================
//-----------------------------------------------------------------------------
// GENERALIZED COORDINATE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set to which generalized coordinate a generalized force should be applied.
 *
 * @param aIndex Index of the generalized coordinate to which a generalized force should be applied.
 */
void suGeneralizedForceApplier::
setGeneralizedCoordinate(int aGenCoord)
{
	_genCoord = aGenCoord;
}
//_____________________________________________________________________________
/**
 * Get to which generalized coordinate a generalized force should be applied.
 *
 * @return aIndex Index of the generalized coordinate to which a generalized force should be applied.
 */
int suGeneralizedForceApplier::
getGeneralizedCoordinate() const
{
	return(_genCoord);
}


//-----------------------------------------------------------------------------
// SCALE FACTOR
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the scale factor that the generalized force will be multiplied by
 * 
 * @param aFactor Scale factor that the generalized force will be multiplied by
 */
void suGeneralizedForceApplier::
setScaleFactor(double aFactor)
{
	_scaleFactor = aFactor;
}
//_____________________________________________________________________________
/**
 * Get the scale factor that the generalized force will be multiplied by
 * @return rFactor
 */
double suGeneralizedForceApplier::
getScaleFactor() const
{
	return(_generalizedForce);

}
//-----------------------------------------------------------------------------
// GENERALIZED FORCE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the generalized force to be applied
 * 
 * @param aGeneralizedForce Generalized force to be applied.
 */
void suGeneralizedForceApplier::
setGeneralizedForce(double aGeneralizedForce)
{
	_generalizedForce = aGeneralizedForce;
}
//_____________________________________________________________________________
/**
 * Get the generalized force to be applied
 * @return aGeneralizedForce
 */
double suGeneralizedForceApplier::
getGeneralizedForce() const
{
		return(_generalizedForce);

}

//-----------------------------------------------------------------------------
// GENERALIZED FORCE STORAGE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the rdStorage containing the generalized force
 * to be applied.
 *
 * @param aGeneralizedForceStorage rdStorage containing the generalized force
 * to be applied
 */
void suGeneralizedForceApplier::
setGeneralizedForceStorage(rdStorage* aGeneralizedForceStorage)
{
	_generalizedForceStorage = aGeneralizedForceStorage;
}
//_____________________________________________________________________________
/**
 * Get the rdStorage containing the generalized force
 * to applied.
 *
 * @return aGeneralizedForceStorage.
 */
rdStorage* suGeneralizedForceApplier::
getGeneralizedForceStorage() const
{
	return(_generalizedForceStorage);
}
//_____________________________________________________________________________
/**
 * Set the index corresponding to the collumn of the generalized force storage
 * that contains the generalized force to be applied
 * 
 * @param aIndex Collumn in storage that contains the generalized force to apply.
 */
void suGeneralizedForceApplier::
setGeneralizedForceIndex(int aIndex)
{
	_genForceIndex = aIndex;
}
//_____________________________________________________________________________
/**
 * Set the index corresponding to the collumn of the generalized force storage
 * that contains the generalized force to be applied
 *
 * @return rIndex
 */
int suGeneralizedForceApplier::
getGeneralizedForceIndex() const
{
	return(_genForceIndex);

}
//-----------------------------------------------------------------------------
// APPLIED GENERALIZED FORCE STORAGE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the generalized force storage.
 *
 * @return Applied generalized force storage.
 */
rdStorage* suGeneralizedForceApplier::
getAppliedGeneralizedForceStorage()
{
	return(_appliedGeneralizedForceStore);
}
//-----------------------------------------------------------------------------
// STORAGE CAPACITY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the capacity increments of applied generalized force storage.
 *
 * @param aIncrement Increment by which storage capacities will be increased
 * when storage capcities run out.
 */
void suGeneralizedForceApplier::
setStorageCapacityIncrements(int aIncrement)
{
	_appliedGeneralizedForceStore->setCapacityIncrement(aIncrement);
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
void suGeneralizedForceApplier::
applyActuation(double aT,double *aX,double *aY)
{
	int i;
	double genForce = 0.0;
	double genForceToStore[1];
	double *genForceArray = new double[_model->getNQ()];
	double time;

	if(_model==NULL) {
		printf("suGeneralizedForceApplier.applyActuation: WARN- no model.\n");
		return;
	}
	if(!getOn()) return;

	if((aT>=getStartTime()) && (aT<getEndTime())){

		if(aT>_aTSet){
			time = aT*_model->getTimeNormConstant();
			_aTSet = aT;
		}

		if(_generalizedForceStorage!=NULL) {
			_generalizedForceStorage->getDataAtTime(aT*_model->getTimeNormConstant(),_genForceIndex+1,genForceArray);
			setGeneralizedForce(genForceArray[_genForceIndex]);
		}
		
		_model->applyGeneralizedForce(_genCoord,_generalizedForce*_scaleFactor);

		genForceToStore[0] = _generalizedForce;

		_appliedGeneralizedForceStore->append(aT,1,genForceToStore);

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
int suGeneralizedForceApplier::
printResults(char *aBaseName,char *aDir,double aDT,char *aExtension)
{
	if(aBaseName==NULL) return(-1);

	// CONSTRUCT PATH
	char path[2048],name[2048],genCoordName[2048];
	if(aDir==NULL) {
		strcpy(path,".");
	} else {
		strcpy(path,aDir);
	}

	sprintf(genCoordName,"body_%d",_genCoord);


	// ACCELERATIONS
	_appliedGeneralizedForceStore->scaleTime(_model->getTimeNormConstant());
	if(aExtension==NULL) {
		sprintf(name,"%s/%s_%s_appTorque",path,aBaseName,genCoordName);
	} else {
		sprintf(name,"%s/%s_%s_appTorque%s",path,aBaseName,genCoordName,aExtension);
	}
	if(aDT<=0.0) {
		if(_appliedGeneralizedForceStore!=NULL)  _appliedGeneralizedForceStore->print(name);
	} else {
		if(_appliedGeneralizedForceStore!=NULL)  _appliedGeneralizedForceStore->print(name,aDT);
	}

	return(0);
}




