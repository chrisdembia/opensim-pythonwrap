// suPointKinematics.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include <string>
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include <NMBLTK/Simulation/Model/rdDerivCallbackSet.h>
#include "suPointKinematics.h"


using namespace std;


//=============================================================================
// CONSTANTS
//=============================================================================
const int suPointKinematics::NAME_LENGTH = suPointKinematicsNAME_LENGTH;
const int suPointKinematics::BUFFER_LENGTH = suPointKinematicsBUFFER_LENGTH;


//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
suPointKinematics::~suPointKinematics()
{
	if(_dy!=NULL) { delete[] _dy;  _dy=NULL; }
	deleteStorage();
}
//_____________________________________________________________________________
/**
 * Construct an suPointKinematics instance for recording the kinematics of
 * the bodies of a model during a simulation.
 *
 * @param aModel Model for which the analyses are to be recorded.
 */
suPointKinematics::suPointKinematics(rdModel *aModel) :
rdAnalysis(aModel),
_body(_bodyProp.getValueInt()),
_point((rdArray<double>&)_pointProp.getValueDblArray()),
_pointName(_pointNameProp.getValueStr())
{
	// NULL
	setNull();

	// ALLOCATIONS
	_dy = new double[_model->getNY()];

	// DESCRIPTION AND LABELS
	constructDescription();
	constructColumnLabels();

	// STORAGE
	allocateStorage();
}


//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
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
suPointKinematics::suPointKinematics(const std::string &aFileName):
rdAnalysis(aFileName),
_body(_bodyProp.getValueInt()),
_point((rdArray<double>&)_pointProp.getValueDblArray()),
_pointName(_pointNameProp.getValueStr())
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
suPointKinematics::suPointKinematics(DOMElement *aElement):
rdAnalysis(aElement),
_body(_bodyProp.getValueInt()),
_point((rdArray<double>&)_pointProp.getValueDblArray()),
_pointName(_pointNameProp.getValueStr())
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
suPointKinematics::suPointKinematics(const suPointKinematics &aPointKinematics):
rdAnalysis(aPointKinematics),
_body(_bodyProp.getValueInt()),
_point((rdArray<double>&)_pointProp.getValueDblArray()),
_pointName(_pointNameProp.getValueStr())
{
	setNull();
	// COPY TYPE AND NAME
	*this = aPointKinematics;
}
//_____________________________________________________________________________
/**
 * Clone
 *
 */
rdObject* suPointKinematics::copy() const
{
	suPointKinematics *object = new suPointKinematics(*this);
	return(object);

}
//_____________________________________________________________________________
/**
 * Instantiate from DOMElement
 *
 */
rdObject* suPointKinematics::copy(DOMElement *aElement) const
{
	suPointKinematics *object = new suPointKinematics(aElement);
	*object = *this;
	object->updateFromXMLNode();
	return(object);
}
//_____________________________________________________________________________
/**
 * SetNull().
 */
void suPointKinematics::
setNull()
{
	double point[] = { 0.0, 0.0, 0.0 };

	// POINTERS
	_dy = NULL;
	_pStore = NULL;
	_vStore = NULL;
	_aStore = NULL;

	// OTHER VARIABLES
	setName("PointKinematics");
	setBody(_model->getGroundID());
	setPoint(point);
	setPointName("Point4Kinematics");
}
//=============================================================================
// OPERATORS
//=============================================================================
//-----------------------------------------------------------------------------
// ASSIGNMENT
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Assign this object to the values of another.
 *
 * @return Reference to this object.
 */
suPointKinematics& suPointKinematics::
operator=(const suPointKinematics &aPointKinematics)
{
	// BASE CLASS
	rdAnalysis::operator=(aPointKinematics);
	_body = aPointKinematics._body;
	_point = aPointKinematics._point;
	_pointName = aPointKinematics._pointName;
	return(*this);
}
//_____________________________________________________________________________
/**
 * Construct a description for the body kinematics files.
 */
void suPointKinematics::
constructDescription()
{
	char descrip[BUFFER_LENGTH];
	char tmp[BUFFER_LENGTH];

	// BODY NAME
	string bodyName;
	if(_body<0) {
		bodyName = "ground";
	} else {
		bodyName = _model->getBodyName(_body);
	}

	strcpy(descrip,"\nThis file contains the kinematics ");
	strcat(descrip,"(position, velocity, or acceleration) of\n");
	sprintf(tmp,"point (%lf, %lf, %lf) on the %s of model %s.\n",
		_point[0],_point[1],_point[2],bodyName.c_str(),
		_model->getName().c_str());
	strcat(descrip,tmp);
	strcat(descrip,"\nUnits are S.I. units (seconds, meters, Newtons,...)\n\n");

	setDescription(descrip);
}

//_____________________________________________________________________________
/**
 * Construct column labels for the body kinematics files.
 */
void suPointKinematics::
constructColumnLabels()
{
	char labels[BUFFER_LENGTH];

	// GET STATE NAMES
	char name[NAME_LENGTH];
	strcpy(labels,"time");
	sprintf(name,"\t%s_X",getPointName());
	strcat(labels,name);
	sprintf(name,"\t%s_Y",getPointName());
	strcat(labels,name);
	sprintf(name,"\t%s_Z",getPointName());
	strcat(labels,name);
	strcat(labels,"\n");

	setColumnLabels(labels);
}

//_____________________________________________________________________________
/**
 * Allocate storage for the kinematics.
 */
void suPointKinematics::
allocateStorage()
{
	// ACCELERATIONS
	_aStore = new rdStorage(1000,"PointAcceleration");
	_aStore->setDescription(getDescription());
	_aStore->setColumnLabels(getColumnLabels());

	// VELOCITIES
	_vStore = new rdStorage(1000,"PointVelocity");
	_vStore->setDescription(getDescription());
	_vStore->setColumnLabels(getColumnLabels());

	// POSITIONS
	_pStore = new rdStorage(1000,"PointPosition");
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
void suPointKinematics::
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
// BODY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the body for which the induced accelerations are to be computed.
 *
 * @param aBody Body ID
 */
void suPointKinematics::
setBody(int aBody)
{
	if((aBody<_model->getGroundID())||(aBody>=_model->getNB())) {
		printf("suPointKinematics.setBody:  WARN- invalid body ID %d.\n",aBody);
		printf("\tSetting body id to -1.\n");
		_body = -1;
	} else {
		_body = aBody;
	}

	// RESET STORAGE
	if(_aStore!=NULL) {
		constructDescription();
		_aStore->reset();
		_vStore->reset();
		_pStore->reset();
		_aStore->setDescription(getDescription());
		_vStore->setDescription(getDescription());
		_pStore->setDescription(getDescription());
	}
}
//_____________________________________________________________________________
/**
 * Get the body for which the induced accelerations are to be computed.
 *
 * @return Body ID
 */
int suPointKinematics::
getBody()
{
	return(_body);
}

//-----------------------------------------------------------------------------
// POINT
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the point for which the induced accelerations are to be computed.
 *
 * @param aPoint X-Y-Z Point
 */
void suPointKinematics::
setPoint(double aPoint[3])
{
	_point[0] = aPoint[0];
	_point[1] = aPoint[1];
	_point[2] = aPoint[2];

	// RESET STORAGE
	if(_aStore!=NULL) {
		constructDescription();
		_aStore->reset();
		_vStore->reset();
		_pStore->reset();
		_aStore->setDescription(getDescription());
		_vStore->setDescription(getDescription());
		_pStore->setDescription(getDescription());
	}
}
//_____________________________________________________________________________
/**
 * Get the point for which the induced accelerations are to be computed.
 *
 * @param rPoint X-Y-Z Point
 */
void suPointKinematics::
getPoint(double rPoint[3])
{
	rPoint[0] = _point[0];
	rPoint[1] = _point[1];
	rPoint[2] = _point[2];
}

//-----------------------------------------------------------------------------
// POINT NAME
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set a name for the point.
 *
 * @param aName Name for the point.
 */
void suPointKinematics::
setPointName(const char *aName)
{
	_pointName = string(aName);
	constructColumnLabels();
	if(_aStore!=NULL) _aStore->setColumnLabels(getColumnLabels());
	if(_vStore!=NULL) _vStore->setColumnLabels(getColumnLabels());
	if(_pStore!=NULL) _pStore->setColumnLabels(getColumnLabels());
}
//_____________________________________________________________________________
/**
 * Get the point name.
 *
 * @param aName Name for the point.
 */
const char* suPointKinematics::
getPointName()
{
	return(_pointName.c_str());
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
rdStorage* suPointKinematics::
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
rdStorage* suPointKinematics::
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
rdStorage* suPointKinematics::
getPositionStorage()
{
	return(_pStore);
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
void suPointKinematics::
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
 */
int suPointKinematics::
record(double aT,double *aX,double *aY)
{
	// COMPUTE ACCELERATIONS
	// ----------------------------------
	// SET
	_model->set(aT,aX,aY);
	_model->getDerivCallbackSet()->set(aT,aX,aY);

	// ACTUATION
	_model->computeActuation();
	_model->getDerivCallbackSet()->computeActuation(aT,aX,aY);
	_model->applyActuatorForces();
	_model->getDerivCallbackSet()->applyActuation(aT,aX,aY);

	// CONTACT
	_model->computeContact();
	_model->getDerivCallbackSet()->computeContact(aT,aX,aY);
	_model->applyContactForces();
	_model->getDerivCallbackSet()->applyContact(aT,aX,aY);

	// ACCELERATIONS
	_model->computeAccelerations(_dy,&_dy[_model->getNQ()]);
	// ----------------------------------

	// VARIABLES
	double vec[3];
	double origin[] = { 0.0, 0.0, 0.0 };

	// POSITION
	_model->getPosition(_body,_point.get(),vec);
	_pStore->append(aT,3,vec);

	// VELOCITY
	_model->getVelocity(_body,_point.get(),vec);
	_vStore->append(aT,3,vec);

	// ACCELERATIONS
	_model->getAcceleration(_body,_point.get(),vec);
	_aStore->append(aT,3,vec);

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
int suPointKinematics::
begin(int aStep,double aDT,double aT,double *aX,double *aY,
		void *aClientData)
{
	if(!proceed()) return(0);

	int status = record(aT,aX,aY);

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
int suPointKinematics::
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
int suPointKinematics::
end(int aStep,double aDT,double aT,double *aX,double *aY,
		void *aClientData)
{
	cout<<"suPointKinematics.end: Finalizing analysis "<<getName()<<".\n";
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
int suPointKinematics::
printResults(const char *aBaseName,const char *aDir,double aDT,
				 const char *aExtension)
{
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
		sprintf(name,"%s/%s_%s_%s_acc",path,aBaseName,getName().c_str(),getPointName());
	} else {
		sprintf(name,"%s/%s_%s_%s_acc%s",path,aBaseName,getName().c_str(),
			getPointName(),aExtension);
	}
	if(aDT<=0.0) {
		if(_aStore!=NULL)  _aStore->print(name);
	} else {
		if(_aStore!=NULL)  _aStore->print(name,aDT);
	}

	// VELOCITIES
	_vStore->scaleTime(_model->getTimeNormConstant());
	if(aExtension==NULL) {
		sprintf(name,"%s/%s_%s_%s_vel",path,aBaseName,getName().c_str(),getPointName());
	} else {
		sprintf(name,"%s/%s_%s_%s_vel%s",path,aBaseName,getName().c_str(),
			getPointName(),aExtension);
	}
	if(aDT<=0.0) {
		if(_vStore!=NULL)  _vStore->print(name);
	} else {
		if(_vStore!=NULL)  _vStore->print(name,aDT);
	}

	// POSITIONS
	_pStore->scaleTime(_model->getTimeNormConstant());
	if(aExtension==NULL) {
		sprintf(name,"%s/%s_%s_%s_pos",path,aBaseName,getName().c_str(),getPointName());
	} else {
		sprintf(name,"%s/%s_%s_%s_pos%s",path,aBaseName,getName().c_str(),
			getPointName(),aExtension);
	}
	if(aDT<=0.0) {
		if(_pStore!=NULL)  _pStore->print(name);
	} else {
		if(_pStore!=NULL)  _pStore->print(name,aDT);
	}

	return(0);
}


