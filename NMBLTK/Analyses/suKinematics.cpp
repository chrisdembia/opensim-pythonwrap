// suKinematics.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include <iostream>
#include <string>
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include "suKinematics.h"

using namespace std;


//=============================================================================
// CONSTANTS
//=============================================================================



//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
suKinematics::~suKinematics()
{
	if(_y!=NULL) { delete[] _y;  _y=NULL; }
	if(_dy!=NULL) { delete[] _dy;  _dy=NULL; }
	deleteStorage();
}
//_____________________________________________________________________________
/**
 * Construct an suKinematics object for recording the kinematics of
 * a model's generalized coodinates during a simulation.
 *
 * @param aModel Model for which the kinematics are to be recorded.
 */
suKinematics::suKinematics(rdModel *aModel) :
	rdAnalysis(aModel)
{
	setNull();

	if (_model != 0){
		// ALLOCATE STATE VECTOR
		_y = new double[_model->getNY()];
		_dy = new double[_model->getNY()];
	}
	// CONSTRUCT DESCRIPTION AND LABELS
	constructDescription();
	constructColumnLabels();

	// STORAGE
	allocateStorage();
}
//=============================================================================
// rdObject Overrides
//=============================================================================
//_____________________________________________________________________________
/**
 * Construct an object from file.
 *
 * The object is constructed from the root element of the XML document.
 * The type of object is the tag name of the XML root element.
 *
 * @param aFileName File name of the document.
 */
suKinematics::suKinematics(const std::string &aFileName):
rdAnalysis(aFileName)
{
	setNull();

	// Serialize from XML
	updateFromXMLNode();

	// CONSTRUCT DESCRIPTION AND LABELS
	constructDescription();
	constructColumnLabels();

	// STORAGE
	allocateStorage();
}
//_____________________________________________________________________________
/**
 * Construct an object from an DOMElement.
 */
suKinematics::suKinematics(DOMElement *aElement):
rdAnalysis(aElement)
{
	setNull();

	// Serialize from XML
	updateFromXMLNode();

	// CONSTRUCT DESCRIPTION AND LABELS
	constructDescription();
	constructColumnLabels();

	// STORAGE
	allocateStorage();
}

// Copy constrctor and virtual copy 
//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 */
suKinematics::suKinematics(const suKinematics &aKinematics):
rdAnalysis(aKinematics)
{
	setNull();
	// COPY TYPE AND NAME
	*this = aKinematics;
}
//_____________________________________________________________________________
/**
 * Clone
 *
 */
rdObject* suKinematics::copy() const
{
	suKinematics *object = new suKinematics(*this);
	return(object);

}
//_____________________________________________________________________________
/**
 * Instantiate from DOMElement
 *
 */
rdObject* suKinematics::copy(DOMElement *aElement) const
{
	suKinematics *object = new suKinematics(aElement);
	*object = *this;
	object->updateFromXMLNode();
	return(object);
}
//_____________________________________________________________________________
/**
 * Set all member variables to their null or default values.
 */
void suKinematics::
setNull()
{
	setType("suKinematics");

	setName("Kinematics");

	_y=0;
	_dy=0;

	_pStore=_vStore=_aStore=0;

}
//--------------------------------------------------------------------------
// OPERATORS
//--------------------------------------------------------------------------
suKinematics& suKinematics::operator=(const suKinematics &aKinematics)
{
	// BASE CLASS
	rdAnalysis::operator=(aKinematics);

	// Deallocate _y & _dy if already allocated
	if(_y!=NULL) { delete[] _y;  _y=NULL; }
	if(_dy!=NULL) { delete[] _dy;  _dy=NULL; }

	if (_model){
		// ALLOCATE STATE VECTOR
		_y = new double[_model->getNY()];
		_dy = new double[_model->getNY()];
	}
	deleteStorage();
	allocateStorage();
	return (*this);
}

//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Allocate storage for the kinematics.
 */
void suKinematics::
allocateStorage()
{
	// ACCELERATIONS
	_aStore = new rdStorage(1000,"Accelerations");
	_aStore->setDescription(getDescription());
	_aStore->setColumnLabels(getColumnLabels());

	// VELOCITIES
	_vStore = new rdStorage(1000,"Speeds");
	_vStore->setDescription(getDescription());
	_vStore->setColumnLabels(getColumnLabels());

	// POSITIONS
	_pStore = new rdStorage(1000,"Coordinates");
	_pStore->setDescription(getDescription());
	_pStore->setColumnLabels(getColumnLabels());
}


//=============================================================================
// DESTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Delete storage objects.
 */
void suKinematics::
deleteStorage()
{
	if(_aStore!=NULL) { delete _aStore;  _aStore=NULL; }
	if(_vStore!=NULL) { delete _vStore;  _vStore=NULL; }
	if(_pStore!=NULL) { delete _pStore;  _pStore=NULL; }
}


//=============================================================================
// GET AND SET
//=============================================================================
//-----------------------------------------------------------------------------
// DESCRIPTION
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Construct the description for the kinematics files.
 */
void suKinematics::
constructDescription()
{
	char descrip[1024];

	strcpy(descrip,"\nUnits are S.I. units (second, meters, Newtons, ...)");
	if(getInDegrees()) {
		strcat(descrip,"\nAngles are in degrees.");
	} else {
		strcat(descrip,"\nAngles are in radians.");
	}
	strcat(descrip,"\n\n");

	setDescription(descrip);
}

//-----------------------------------------------------------------------------
// COLUMN LABELS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Construct the column labels for the kinematics files.
 */
void suKinematics::
constructColumnLabels()
{
	// CHECK FOR NULL
	if (_model ==0) return;

	if(_model->getSpeedName(0).empty()) { setColumnLabels(NULL);  return; }

	// ASSIGN
	int i;
	string labels = "time";
	for(i=0;i<_model->getNU();i++) {
		labels += "\t";
		labels += _model->getSpeedName(i);
	}
	labels += "\n";

	setColumnLabels(labels.c_str());
}


//-----------------------------------------------------------------------------
// STORAGE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the acceleration storage.
 *
 * @return Acceleration storage.
 */
rdStorage* suKinematics::
getAccelerationStorage()
{
	return(_aStore);
}
//_____________________________________________________________________________
/**
 * Get the velocity storage.
 *
 * @return Velocity storage.
 */
rdStorage* suKinematics::
getVelocityStorage()
{
	return(_vStore);
}
//_____________________________________________________________________________
/**
 * Get the position storage.
 *
 * @return Position storage.
 */
rdStorage* suKinematics::
getPositionStorage()
{
	return(_pStore);
}
//_____________________________________________________________________________
/**
 * Set the model pointer for analyzing kinematics.
 */
void suKinematics::setModel(rdModel *aModel)
{
	// BASE CLASS
	rdAnalysis::setModel(aModel);

	// DATA MEMBERS
	if(_y!=NULL) { delete[] _y;  _y=NULL; }
	if(_dy!=NULL) { delete[] _dy;  _dy=NULL; }

	if (_model){
		// ALLOCATE STATE VECTOR
		_y = new double[_model->getNY()];
		_dy = new double[_model->getNY()];
	}
	
}

//-----------------------------------------------------------------------------
// STORAGE CAPACITY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the capacity increments of all storage instances.
 *
 * @param aIncrement Increment by which storage capacities will be increased
 * when storage capcities run out.
 */
void suKinematics::
setStorageCapacityIncrements(int aIncrement)
{
	_aStore->setCapacityIncrement(aIncrement);
	_vStore->setCapacityIncrement(aIncrement);
	_pStore->setCapacityIncrement(aIncrement);
}



//=============================================================================
// ANALYSIS
//=============================================================================
//_____________________________________________________________________________
/**
 * Record the kinematics.
 *
 * @return 0 of success, -1 on error.
 */
int suKinematics::
record(double aT,double *aX,double *aY)
{
	// NUMBERS
	int nq = _model->getNQ();
	int nu = _model->getNU();
	int ny = _model->getNY();

	// COMPUTE DERIVATIVES
	_model->deriv(aT,aX,aY,_dy);

	// UN-NORMALIZE
	int i;
	double tNormConst = 1.0 / _model->getTimeNormConstant();
	for(i=0;i<ny;i++) _dy[i] *= tNormConst;

	// CONVERT RESULTS TO ANGLES
	memcpy(_y,aY,ny*sizeof(double));
	_model->convertQuaternionsToAngles(_y,_y);

	// CONVERT TO DEGREES
	if(getInDegrees()) {
		_model->convertRadiansToDegrees(_y,_y);
		_model->convertRadiansToDegrees(&_y[nq],&_y[nq]);
		_model->convertRadiansToDegrees(&_dy[nq],&_dy[nq]);
	}

	// RECORD RESULTS
	_pStore->append(aT,nu,_y);
	_vStore->append(aT,nu,&_y[nq]);
	_aStore->append(aT,nu,&_dy[nq]);

	return(0);
}
//_____________________________________________________________________________
/**
 * This method is called at the beginning of an analysis so that any
 * necessary initializations may be performed.
 *
 * This method is meant to be called at the begining of an integration in
 * rdModel::integBeginCallback() and has the same argument list.
 *
 * This method should be overriden in the child class.  It is
 * included here so that the child class will not have to implement it if it
 * is not necessary.
 *
 * @param aStep Step number of the integration.
 * @param aDT Size of the time step that will be attempted.
 * @param aT Current time in the integration.
 * @param aX Current control values.
 * @param aY Current states.
 * @param aClientData General use pointer for sending in client data.
 *
 * @return -1 on error, 0 otherwise.
 */
int suKinematics::
begin(int aStep,double aDT,double aT,double *aX,double *aY,
		void *aClientData)
{
	if(!proceed()) return(0);

	// RESET STORAGE
	_pStore->reset(aT);
	_vStore->reset(aT);
	_aStore->reset(aT);

	// RECORD
	int status = 0;
	if(_pStore->getSize()<=0) {
		status = record(aT,aX,aY);
	}

	return(status);
}
//_____________________________________________________________________________
/**
 * This method is called to perform the analysis.  It can be called during
 * the execution of a forward integrations or after the integration by
 * feeding it the necessary data.
 *
 * When called during an integration, this method is meant to be called in
 * rdModel::integStepCallback(), which has the same argument list.
 *
 * This method should be overriden in derived classes.  It is
 * included here so that the derived class will not have to implement it if
 * it is not necessary.
 *
 * @param aXPrev Controls at the beginining of the current time step.
 * @param aYPrev States at the beginning of the current time step.
 * @param aStep Step number of the integration.
 * @param aDT Size of the time step that was just taken.
 * @param aT Current time in the integration.
 * @param aX Current control values.
 * @param aY Current states.
 * @param aClientData General use pointer for sending in client data.
 *
 * @return -1 on error, 0 otherwise.
 */
int suKinematics::
step(double *aXPrev,double *aYPrev,
	int aStep,double aDT,double aT,double *aX,double *aY,
	void *aClientData)
{
	if(!proceed(aStep)) return(0);

	int status = record(aT,aX,aY);

	return(0);
}
//_____________________________________________________________________________
/**
 * This method is called at the end of an analysis so that any
 * necessary finalizations may be performed.
 *
 * This method is meant to be called at the end of an integration in
 * rdModel::integEndCallback() and has the same argument list.
 *
 * This method should be overriden in the child class.  It is
 * included here so that the child class will not have to implement it if it
 * is not necessary.
 *
 * @param aStep Step number of the integration.
 * @param aDT Size of the time step that was just completed.
 * @param aT Current time in the integration.
 * @param aX Current control values.
 * @param aY Current states.
 * @param aClientData General use pointer for sending in client data.
 *
 * @return -1 on error, 0 otherwise.
 */
int suKinematics::
end(int aStep,double aDT,double aT,double *aX,double *aY,
		void *aClientData)
{
	return(0);
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
int suKinematics::
printResults(const char *aBaseName,const char *aDir,double aDT,
				 const char *aExtension)
{
	if(!getOn()) {
		printf("suKinematics.printResults: Off- not printing.\n");
		return(0);
	}
	if(aBaseName==NULL) return(-1);

	// CONSTRUCT PATH
	char path[2048],name[2048];
	if(aDir==NULL) {
		strcpy(path,".");
	} else {
		strcpy(path,aDir);
	}

	// ACCELERATIONS
	_aStore->scaleTime(_model->getTimeNormConstant());
	if(aExtension==NULL) {
		sprintf(name,"%s/%s_%s_dudt",path,aBaseName,getName().c_str());
	} else {
		sprintf(name,"%s/%s_%s_dudt%s",path,aBaseName,getName().c_str(),aExtension);
	}
	if(aDT<=0.0) {
		if(_aStore!=NULL)  _aStore->print(name);
	} else {
		if(_aStore!=NULL)  _aStore->print(name,aDT);
	}

	// VELOCITIES
	_vStore->scaleTime(_model->getTimeNormConstant());
	if(aExtension==NULL) {
		sprintf(name,"%s/%s_%s_u",path,aBaseName,getName().c_str());
	} else {
		sprintf(name,"%s/%s_%s_u%s",path,aBaseName,getName().c_str(),aExtension);
	}
	if(aDT<=0.0) {
		if(_vStore!=NULL)  _vStore->print(name);
	} else {
		if(_vStore!=NULL)  _vStore->print(name,aDT);
	}

	// POSITIONS
	_pStore->scaleTime(_model->getTimeNormConstant());
	if(aExtension==NULL) {
		sprintf(name,"%s/%s_%s_q",path,aBaseName,getName().c_str());
	} else {
		sprintf(name,"%s/%s_%s_q%s",path,aBaseName,getName().c_str(),aExtension);
	}
	if(aDT<=0.0) {
		if(_pStore!=NULL)  _pStore->print(name);
	} else {
		if(_pStore!=NULL)  _pStore->print(name,aDT);
	}

	return(0);
}


