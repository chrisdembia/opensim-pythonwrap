// suDecomp.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Tools/rdMtx.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include "suDecomp.h"


using namespace std;


//=============================================================================
// CONSTANTS
//=============================================================================

// NAMES
const char *suDecomp::ADDON_COMPONENT_NAMES[] = {
	"Gravity","Velocity","Inertial","Actuators","All"
};



//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
suDecomp::~suDecomp()
{
	// CONTACT FLAG
	if(_contactEstablished!=NULL)
		{ delete []_contactEstablished;  _contactEstablished=NULL; }
	
	// FORCE ELEMENT ARRAYS
	int c;
	if(_fContig!=NULL) { delete []_fContig;  _fContig=NULL; }
	if(_f!=NULL) {
		for(c=0;c<_nc;c++) {
			if(_f[c]!=NULL) { delete []_f[c];  _f[c]=NULL; }
		}
		delete []_f;  _f=NULL;
	}

	// STORAGE
	deleteStorage();
}
//_____________________________________________________________________________
/**
 * Construct an decomposition instance for a model.
 * This constructor is used if the decomposition analysis is going to
 * be performed during the course of a simulation.
 *
 * @param aModel Model on which the analyses are to be performed.
 */
suDecomp::suDecomp(rdModel *aModel) :
	rdAnalysis(aModel),
	_cNames("")
{
	int i;

	setNull();

	// NAME
	setName("Decomp");

	// INITIALIZE NUMBERS
	initializeNumbers();

	// CONTACT
	_contactEstablished = new bool[_np];
	for(i=0;i<_np;i++) {
		_contactEstablished[i] = false;
	}

	// ALLOCATE ELEMENT VECTORS
	allocateElementVectors();

	// COMPONENT NAMES
	constructComponentNames();

	// DESCRIPTION AND LABELS
	constructDescription();
	constructColumnLabels();

	// STORAGE
	allocateStorage();
}
//_____________________________________________________________________________
/**
 * Construct an induced acceleration instance for a model.  This constructor
 * is used when the analysis is to be performed following a simulation.
 * The states recorded during the simulation as well as an
 * appropriate force decomposition must be used to construct the induced
 * acceleration instance.  The induced accelerations are not read in from
 * file.  They are recomputed based on the force decomposition.
 *
 * If NULL is sent in as the base name for the force decomposition
 * files, it is assumed that induced accelerations are to be computed
 * based on a NULL decomposition.  A NULL decomposition is one in which
 * all induced contact forces are assmed to be zero:  each actuator
 * accelerates the model in a pure sense, without its associated reaction
 * forces.
 *
 * @param aModel Model on which the simulation was run.
 * @param aStates Set of model states.
 * @param aBaseName Base name for the force decompositon files.  If NULL,
 * accelerations are computed based on a NULL decompostion.
 * @param aDir Directory in which the results reside.
 * @param aExtension File extension of the force decomposition files.
 */
suDecomp::suDecomp(rdModel *aModel,char *aBaseName,char *aDir,char *aExtension) :
	rdAnalysis(aModel),
	_cNames("")
{
	printf("suDecomp: constructing induced acceleration analysis from file.\n");
	printf("baseName = %s  aDir = %s  aExtension= %s\n",
		aBaseName,aDir,aExtension);

	setNull();

	// NAME
	setName("indAcc");

	// INITIALIZE NUMBERS
	initializeNumbers();

	// CONTACT
	_contactEstablished = new bool[_np];
	int i;
	for(i=0;i<_np;i++) {
		_contactEstablished[i] = false;
	}

	// ALLOCATE ELEMENT VECTORS
	allocateElementVectors();

	// COMPONENT NAMES
	constructComponentNames();

	// DESCRIPTION AND LABELS
	constructDescription();
	constructColumnLabels();

	// STORAGE
	allocateStoragePointers();

	// READ DECOMPOSITION
	if(aBaseName==NULL) {
		_useNullDecomposition = true;
		createNullDecomposition();
	} else {
		readDecomposition(aBaseName,aDir,aExtension);
	}
}


//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Set member variables to approprate NULL values.
 */
void suDecomp::
setNull()
{
	_nc = 0;
	_nic = 0;
	_np = 0;
	_cAct = 0;
	_cGrav = 0;
	_cVel = 0;
	_cIner = 0;
	_cAllAct = 0;
	_cAll = 0;

	_contactThreshold = 0.0;
	_usePresetContactEstablishedSettings = false;
	_contactEstablished = NULL;
	_fContig = NULL;
	_f = NULL;
	_fStore = NULL;
	_useNullDecomposition = false;
	_cpaStore = NULL;
	_recordContactPointAccelerations = false;
}
//_____________________________________________________________________________
/**
 * Initialize numbers of things.
 */
void suDecomp::
initializeNumbers()
{
	// NUMBERS OF THINGS
	int na = _model->getNA();
	_nc = na + 5;
	_nic = _nc - 2;
	_np = _model->getNP();

	// INDICES
	_cAct = na - 1;
	_cGrav = na;
	_cVel = na + 1;
	_cIner = na + 2;
	_cAllAct = na + 3;
	_cAll = na + 4;
}
//_____________________________________________________________________________
/**
 * Construct component names
 */
void suDecomp::
constructComponentNames()
{
	cout<<"\n\nsuDecomp.constructComponentNames: ...\n";

	// SET COMPONENTS NAMES
	int c;
	_cNames.setSize(_nc);
	for(c=0;c<_nc;c++) {
		if(c<=_cAct) {
			_cNames[c] = _model->getActuatorName(c);
		} else {
			_cNames[c] = ADDON_COMPONENT_NAMES[c-_cAct-1];
		}
		cout<<_cNames[c]<<endl;
	}
}
//-----------------------------------------------------------------------------
// DESCRIPTION
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Construct a description.
 */
void suDecomp::
constructDescription()
{
	printf("suDecomp.constructDescription:\n");
	char tmp[1024],descrip[1024];

	strcpy(descrip,"\nThis file contains the reaction forces induced by\n");
	sprintf(tmp,"a particular action force of model %s.\n\n",
		_model->getName().c_str());
	strcat(descrip,tmp);
	strcat(descrip,"\nUnits are S.I. units (seconds, meters, Newtons, ...)");
	strcat(descrip,"\n\n");

	setDescription(descrip);
}
//_____________________________________________________________________________
/**
 * Construct the column labels.
 */
void suDecomp::
constructColumnLabels()
{
	// CREATE FORCE HEADERS
	int i;
	char label[256],labels[2048];
	strcpy(labels,"time");
	for(i=0;i<_np;i++) {
		sprintf(label,"\tp%dx\tp%dy\tp%dz",i,i,i);
		strcat(labels,label);
	}

	setColumnLabels(labels);
}

//_____________________________________________________________________________
/**
 * Allocate element vectors.
 */
void suDecomp::
allocateElementVectors()
{
	int c,i,j,I;

	// FORCE
	// Note- memory must be contiguous!
	_fContig = new double[_nc*_np*3];
	_f = new double**[_nc];
	for(c=0;c<_nc;c++) {
		_f[c] = new double*[_np];
		for(i=0;i<_np;i++) {
			I = rdMtx::ComputeIndex(c,_np,i,3,0);
			_f[c][i] = &_fContig[I];
			for(j=0;j<3;j++) _f[c][i][j] = 0.0;
		}
	}
}
//_____________________________________________________________________________
/**
 * Allocate storage pointers for the force decomposition and induced
 * accelerations.
 */
void suDecomp::
allocateStoragePointers()
{
	_fStore = new rdStorage*[_nc];

	int c;
	for(c=0;c<_nc;c++) {
		_fStore[c] = NULL;
	}
}
//_____________________________________________________________________________
/**
 * Allocate storage for the decomposition.
 */
void suDecomp::
allocateStorage()
{
	// ALLOCATE STORAGE POINTERS
	allocateStoragePointers();

	// ALLOCATE STORAGE
	int c;
	for(c=0;c<_nc;c++) {
		_fStore[c] = new rdStorage(1000,"ForceDecomposition");
		_fStore[c]->setDescription(getDescription());
		_fStore[c]->setColumnLabels(getColumnLabels());
		_fStore[c]->setCapacityIncrement(1000);
	}
}
//_____________________________________________________________________________
/**
 * Create a NULL decomposition.
 */
void suDecomp::
createNullDecomposition()
{
	// ZERO VECTOR
	int i;
	int n = 3*_model->getNP();
	if(n<=0) return;
	double *zero = new double[n];
	for(i=0;i<n;i++) zero[i] = 0.0;

	// ALLOCATE STORAGE
	int c;
	for(c=0;c<_nc;c++) {
		_fStore[c] = new rdStorage(1,"NullDecomposition");
		_fStore[c]->append(0.0,n,zero);
	}

	// CLEANUP
	delete[] zero;
}


//=============================================================================
// DESTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Delete storage objects.
 */
void suDecomp::
deleteStorage()
{
	// FORCE DECOMPOSITION
	int c;
	if(_fStore!=NULL) {
		for(c=0;c<_nc;c++) {
			if(_fStore[c]!=NULL) { delete _fStore[c];  _fStore[c]=NULL; }
		}
		delete []_fStore;
	}
	if(_cpaStore!=NULL) {
		for(c=0;c<_nc;c++) {
			if(_cpaStore[c]!=NULL) { delete _cpaStore[c];  _cpaStore[c]=NULL; }
		}
		delete []_cpaStore;
	}
}


//=============================================================================
// GET AND SET
//=============================================================================
//-----------------------------------------------------------------------------
// COMPONENTS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the number of components
 */
int suDecomp::
getNumComponents()
{
	return(_nc);
}
//_____________________________________________________________________________
/**
 * Get the number of independent components.
 */
int suDecomp::
getNumIndependentComponents()
{
	return(_nic);
}
//_____________________________________________________________________________
/**
 * Get the number of contact elements.
 */
int suDecomp::
getNumElements()
{
	return(_np);
}
//_____________________________________________________________________________
/**
 * Get the index of the last actuator component.
 */
int suDecomp::
getLastActuatorIndex()
{
	return(_cAct);
}
//_____________________________________________________________________________
/**
 * Get the index of the gravity component.
 */
int suDecomp::
getGravityIndex()
{
	return(_cGrav);
}
//_____________________________________________________________________________
/**
 * Get the index of the velocity component.
 */
int suDecomp::
getVelocityIndex()
{
	return(_cVel);
}
//_____________________________________________________________________________
/**
 * Get the index of the inertial component.
 */
int suDecomp::
getInertialIndex()
{
	return(_cIner);
}
//_____________________________________________________________________________
/**
 * Get the index of the total of all actuator components.
 */
int suDecomp::
getAllActuatorsIndex()
{
	return(_cAllAct);
}
//_____________________________________________________________________________
/**
 * Get the index of the total of all components.
 */
int suDecomp::
getAllIndex()
{
	return(_cAll);
}
//_____________________________________________________________________________
/**
 * GET THE NAME OF A COMPONENT
 */
string suDecomp::
getComponentName(int aC)
{
	if(aC<0) return("");
	if(aC>=_nc) return("");
	return(_cNames[aC]);
}

//-----------------------------------------------------------------------------
// CONTACT THREASHOLD
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the force threashold above which contact is assumed to be established.
 *
 * @param aThreashold Force threashold above which contact is established.
 */
void suDecomp::
setContactThreshold(double aThreshold)
{
	_contactThreshold = aThreshold;
}
//_____________________________________________________________________________
/**
 * Get the force threashold above which contact is assumed to be established.
 *
 * @return Force threashold above which contact is established.
 */
double suDecomp::
getContactThreshold()
{
	return(_contactThreshold);
}

//-----------------------------------------------------------------------------
// USE PRESET CONTACT ESTABLISHED SETTINGS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set whether or not to use preset contact established settings.
 * If this flag is set to true, computation of contact forces
 * is not performed in order to determine if contact has been established.
 * Rather, it is assumed that the caller has preset the desired
 * contact-established settings.
 *
 * @param aTrueFalse If true, preset contact established settings are used
 * in the decomposition.  If false, contact forces are computed to determine
 * if contact has been established.
 * @see setContactEstablished()
 */
void suDecomp::
setUsePresetContactEstablishedSettings(bool aTrueFalse)
{
	_usePresetContactEstablishedSettings = aTrueFalse;
}
//_____________________________________________________________________________
/**
 * Get whether or not to use preset contact established settings.
 * If this flag is set to true, computation of contact forces
 * is not performed in order to determine if contact has been established.
 * Rather, it is assumed that the caller has preset the desired
 * contact-established settings.
 *
 * @return True if preset contact established settings are used
 * in the decomposition.  False if contact forces are computed to determine
 * if contact has been established.
 * @see setContactEstablished()
 */
bool suDecomp::
getUsePresetContactEstablishedSettings() const
{
	return(_usePresetContactEstablishedSettings);
}

//-----------------------------------------------------------------------------
// CONTACT ESTABLISHED
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set whether or not contact has been established at a specified
 * contact point.
 *
 * @param aIndex Index of the contact point: 0 <= aIndex < rdModel::getNP().
 * @param aTrueFalse Wheter or not contact has been established.
 * @see setUsePresetContactEstablished()
 */
void suDecomp::
setContactEstablished(int aIndex,bool aTrueFalse)
{
	if((aIndex<0)||(aIndex>=_model->getNP())) {
		printf("suDecomp.setContactEstablished: WARN- index out of range.\n");
		return;
	}

	_contactEstablished[aIndex] = aTrueFalse;
}
//_____________________________________________________________________________
/**
 * Get whether or not contact has been established at a specified
 * contact point.
 *
 * @param aIndex Index of the contact point: 0 <= aIndex < rdModel::getNP().
 * @return True if contact has been established; false if not or on an error.
 * @see setUsePresetContactEstablished()
 */
bool suDecomp::
getContactEstablished(int aIndex) const
{
	if((aIndex<0)||(aIndex>=_model->getNP())) {
		printf("suDecomp.getContactEstablished: WARN- index out of range.\n");
		return(false);
	}

	return(_contactEstablished[aIndex]);
}

//-----------------------------------------------------------------------------
// RECORD CONTACT POINT ACCELERATIONS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Determine whether or not contact point accelerations will be recorded.  If
 * set to true, space is allocated to store them.
 *
 * @param aTrueFalse 
 */
void suDecomp::
setRecordContactPointAccelerations(bool aTrueFalse)
{
	_recordContactPointAccelerations = aTrueFalse;

	if(_recordContactPointAccelerations)
	{
		_cpaStore = new rdStorage*[_nc];

		int c;
		for(c=0;c<_nc;c++) {
		_cpaStore[c] = new rdStorage(1000,"ContactPointAccelerations");
		_cpaStore[c]->setColumnLabels(getColumnLabels());
		_cpaStore[c]->setCapacityIncrement(1000);
		}
	}
}

//_____________________________________________________________________________
/**
 * Get whether or not the contact points are being recorded.
 *
 * @return bool
 */
bool suDecomp::
getRecordContactPointAccelerations()
{
	return(_recordContactPointAccelerations);
}

//-----------------------------------------------------------------------------
// FORCE STORAGE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the force decomposition for a particular component.
 *
 * @return Pointer to the force decomposition for component aC.
 */
const rdStorage* suDecomp::
getDecomposition(int aC) const
{
	if((aC<0)||(aC>=_nc)) return(NULL);
	return(_fStore[aC]);
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
void suDecomp::
setStorageCapacityIncrements(int aIncrement)
{
	int c;
	for(c=0;c<_nc;c++) {
		if(_fStore[c]!=NULL) _fStore[c]->setCapacityIncrement(aIncrement);
	}
}

//-----------------------------------------------------------------------------
// NULL DECOMPOSITION
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get whether or not accelerations are being computed using a
 * NULL decomposition.  A NULL decomposition is one in which all
 * induced contact forces are assumed to be zero.
 *
 * The value returned by this method can be used to decide whether or not
 * it is necessary to apply contact forces.
 *
 * @return True when a NULL decomposition is used, false otherwise.
 */
bool suDecomp::
getUseNullDecomposition()
{
	return(_useNullDecomposition);
}


//=============================================================================
// UTILITY
//=============================================================================
//_____________________________________________________________________________
/**
 * Sum the separate components of a force decompositon to get the
 * decomposition due to all actuators and to all components.
 */
void suDecomp::
sum()
{
	if(getUseNullDecomposition()) return;
	if(_fStore==NULL) return;
	if(_fStore[0]==NULL) return;

	// ALLOCATE ALL ACTUATOR STORAGE
	int C = getAllActuatorsIndex();
	if(_fStore[C]!=NULL) delete _fStore[C];
	_fStore[C] = new rdStorage(*_fStore[0]);

	// SUM ACROSS ACTUATORS
	int c;
	for(c=1;c<=getLastActuatorIndex();c++) {
		if(_fStore[c]!=NULL) _fStore[C]->add(_fStore[c]);
	}

	// ALLOCATE ALL STORAGE
	C = getAllIndex();
	if(_fStore[C]!=NULL) delete _fStore[C];
	_fStore[C] = new rdStorage(*_fStore[0]);

	// SUM ACROSS ALL COMPONENTS
	for(c=1;c<_nic;c++) {
		if(_fStore[c]!=NULL) _fStore[C]->add(_fStore[c]);
	}
}


//=============================================================================
// ANALYSIS
//=============================================================================
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
int suDecomp::
begin(int aStep,double aDT,double aT,double *aX,double *aY,
		void *aClientData)
{
	if(!proceed()) return(0);

	compute(aX,aY,aStep,aDT,aT,aX,aY);

	return(0);
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
int suDecomp::
step(double *aXPrev,double *aYPrev,
	int aStep,double aDT,double aT,double *aX,double *aY,
	void *aClientData)
{
	if(!proceed(aStep)) return(0);

	compute(aX,aY,aStep,aDT,aT,aX,aY);

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
int suDecomp::
end(int aStep,double aDT,double aT,double *aX,double *aY,
		void *aClientData)
{
	if(!proceed()) return(0);
	printf("suDecomp.end: Finalizing analysis %s.\n",getName().c_str());
	return(0);
}


//=============================================================================
// IO
//=============================================================================
//_____________________________________________________________________________
/**
 * Read the results of a force decomposition from file.
 *
 * Note that the induced accelerations are not read in from file.  The
 * induced accelerations are recomputed based on the force decomposition.
 *
 * The file names are constructed as
 * aDir + "/" + aBaseName + "_" + ComponentName + aExtension
 *
 * @param aDir Directory in which the results reside.
 * @param aBaseName Base file name of the files.
 * @param aExtension File extension.
 *
 * @return 0 on success, -1 on error.
 */
int suDecomp::
readDecomposition(char *aBaseName,char *aDir,char *aExtension)
{
	if(aBaseName==NULL) return(-1);

	// CONSTRUCT PATH
	char path[2048];
	if(aDir==NULL) {
		strcpy(path,".");
	} else {
		strcpy(path,aDir);
	}

	// COMPONENTS
	int c;
	char name[2048];
	for(c=0;c<_nc;c++) {

		// FORCE DECOMPOSITION
		if(aExtension==NULL) {
			sprintf(name,"%s/%s_%s",path,aBaseName,_cNames[c]);
		} else {
			sprintf(name,"%s/%s_%s%s",path,aBaseName,_cNames[c],aExtension);
		}
		_fStore[c] = new rdStorage(name);
	}

	return(0);
}
//_____________________________________________________________________________
/**
 * Print results.
 * 
 * The file names are constructed as
 * aDir + "/" + aBaseName + "_" + ComponentName + aExtension
 *
 * @param aDir Directory in which the results reside.
 * @param aBaseName Base file name.
 * @param aExtension File extension.
 *
 * @return 0 on success, -1 on error.
 */
int suDecomp::
printResults(const char *aBaseName,const char *aDir,double aDT,
				 const char *aExtension)
{
	if(!getOn()) {
		printf("suDecomp.printResults: Off- not printing.\n");
		return(-1);
	}
	if(getUseNullDecomposition()) return(-1);

	char baseName[NAME_LENGTH];
	if(aBaseName==NULL) {
		strcpy(baseName,"null");
	} else {
		strncpy(baseName,aBaseName,NAME_LENGTH);
		baseName[NAME_LENGTH-1] = NULL;
	}

	// CONSTRUCT PATH
	char path[NAME_LENGTH];
	if(aDir==NULL) {
		strcpy(path,".");
	} else {
		strcpy(path,aDir);
	}

	// SUM RESULTS
	sum();

	// COMPONENTS
	int c;
	char name[2048];
	for(c=0;c<_nc;c++) {

		if(_fStore[c]==NULL) continue;

		// FILE NAME
		if(aExtension==NULL) {
			sprintf(name,"%s/%s_%s_%s",path,baseName,getName().c_str(),_cNames[c].c_str());
		} else {
			sprintf(name,"%s/%s_%s_%s%s",path,baseName,getName().c_str(),_cNames[c].c_str(),
				aExtension);
		}

		// PRINT
		if(aDT<=0.0) {
			_fStore[c]->print(name);
		} else {
			_fStore[c]->print(name,aDT);
		}


		continue;

		if(_cpaStore[c]==NULL) continue;

		// FILE NAME
		if(aExtension==NULL) {
			sprintf(name,"%s/%s_%s_cpAccel_%s",path,baseName,getName().c_str(),_cNames[c].c_str());
		} else {
			sprintf(name,"%s/%s_%s_cpAccel_%s%s",path,baseName,getName().c_str(),_cNames[c].c_str(),
				aExtension);
		}

		// PRINT
		if(aDT<=0.0) {
			_cpaStore[c]->print(name);
		} else {
			_cpaStore[c]->print(name,aDT);
		}
	}

	return(0);
}


