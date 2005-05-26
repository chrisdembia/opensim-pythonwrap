// suBodyIndPowers.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHORS: Frank C. Anderson, Saryn R. Goldberg
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <RD/Tools/rdMath.h>
#include <RD/Tools/rdTools.h>
#include <RD/Simulation/Model/rdModel.h>
#include <RD/Tools/rdMtx.h>
#include "suBodyIndPowers.h"


//=============================================================================
// DEFINES
//=============================================================================
#define MAXLEN 2048


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
suBodyIndPowers::~suBodyIndPowers()
{
	// STORAGE
	deleteStorage();
}
//_____________________________________________________________________________
/**
 * Construct an induced power instance for performing an induced
 * power analysis on the bodies of a model.
 *
 * @param aModel Model on which the analyses are to be performed.
 */
suBodyIndPowers::suBodyIndPowers(rdModel *aModel) :
	suBodyIndAcc(aModel)
{
	setName("BodyInducedPowers");

	// MEMBERS
	_powerStore = NULL;

	// DESCRIPTION
	constructDescription();
	constructColumnLabels();

	// STORAGE
	allocateStorage();
}
//_____________________________________________________________________________
/**
 * Construct an induced powers instance from a set of force
 * decomposition files.
 *
 * Note that the induced accelerations are not read in from file.  The
 * induced accelerations are recomputed based on the force decomposition.
 *
 * @param aModel Model on which the analyses were performed.
 * @param aStates Set of model states.
 * @param aBaseName Base name for the force decompositon files.
 * @param aDir Directory in which the results reside.
 * @param aExtension File extension.
 */
suBodyIndPowers::suBodyIndPowers(rdModel *aModel,rdStorage *aStates,rdStorage *aControls,
	char *aBaseName,char *aDir,char *aExtension) :
	suBodyIndAcc(aModel,aStates,aControls,aBaseName,aDir,aExtension)
{
	printf("suBodyIndAcc: constructing from file.\n");
	printf("baseName = %s  aDir = %s  aExtension= %s\n",
		aBaseName,aDir,aExtension);

	// NAME
	setName("BodyInducedPowers");

		// DESCRIPTION
	constructDescription();
	constructColumnLabels();

	// STORAGE
	allocateStoragePointers();
}


//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Construct a description for the body powers files.
 */
void suBodyIndPowers::
constructDescription()
{
	char descrip[1024];
	char tmp[MAXLEN];

	strcpy(descrip,"\nThis file contains the induced powers");
	sprintf(tmp," of the body segments in model %s.\n",
		_model->getName().c_str());
	strcat(descrip,tmp);
	strcat(descrip,"\nInduced powers are given about");
	strcat(descrip," the body-local axes.\n");
	strcat(descrip,"\nUnits are S.I. units (seconds, meters, Newtons, ...)");
	if(getInDegrees()) {
		strcat(descrip,"\nAngles are in degrees.");
	} else {
		strcat(descrip,"\nAngles are in radians.");
	}
	strcat(descrip,"\n\n");

	setDescription(descrip);
}

//_____________________________________________________________________________
/**
 * Construct column labels for the body powers files.
 */
void suBodyIndPowers::
constructColumnLabels()
{
	char labels[MAXLEN];

	// GET STATE NAMES
	int i;
	char name[MAXLEN];
	strcpy(labels,"time");
	for(i=0;i<_model->getNB();i++) {
		sprintf(name,"\t%s",_model->getBodyName(i).c_str());
		strcat(labels,name);
	}
	strcat(labels,"\tTotal\n");

	setColumnLabels(labels);
}

//_____________________________________________________________________________
/**
 * Allocate storage pointers for the induced powers of the bodies.
 */
void suBodyIndPowers::
allocateStoragePointers()
{
	_powerStore = new rdStorage*[_nc];
	int c;
	for(c=0;c<_nc;c++) {
		_powerStore[c] = NULL;
	}
}
//_____________________________________________________________________________
/**
 * Allocate storage.
 */
void suBodyIndPowers::
allocateStorage()
{
	// ALLOCATE STORAGE POINTERS
	allocateStoragePointers();

	// ALLOCATE STORAGE
	int c;
	for(c=0;c<_nc;c++) {
		_powerStore[c] = new rdStorage(500,"BodyInducedPowers");
		_powerStore[c]->setCapacityIncrement(100);
		_powerStore[c]->setDescription(getDescription());
		_powerStore[c]->setColumnLabels(getColumnLabels());
	}
}


//=============================================================================
// DESTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Delete storage objects.
 */
void suBodyIndPowers::
deleteStorage()
{
	// INDUCED POWERS
	int c;
	if(_powerStore!=NULL) {
		for(c=0;c<_nc;c++) {
			if(_powerStore[c]!=NULL) { delete _powerStore[c];  _powerStore[c]=NULL; }
		}
		delete []_powerStore;
	}
}


//=============================================================================
// GET AND SET
//=============================================================================
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
void suBodyIndPowers::
setStorageCapacityIncrements(int aIncrement)
{
	// BASE CLASS
	suIndAcc::setStorageCapacityIncrements(aIncrement);

	// THIS CLASS
	int c;
	for(c=0;c<_nc;c++) {
		_powerStore[c]->setCapacityIncrement(aIncrement);
	}
}


//=============================================================================
// OPERATIONS
//=============================================================================
//_____________________________________________________________________________
/**
 * Compute the induced powers of the bodies of a model from a
 * force decomposition and a set of states.
 *
 * @return 0 on success, -1 on error.
 */
int suBodyIndPowers::
computeBodyPowers()
{
	if(_yStore==NULL) return(-1);

	// CHECK FOR TIME CORRESPONDENCE
	if(!getUseNullDecomposition()) {
		double ti = _feStore[0]->getFirstTime();
		double tf = _feStore[0]->getLastTime();
		if((ti!=_yStore->getFirstTime())||(tf!=_yStore->getLastTime())) {
			printf("suBodyIndPowers.computeBodyPowers: WARN-\n");
			printf("\tTime range for states is %lf to %lf\n",
				_yStore->getFirstTime(),_yStore->getLastTime());
			printf("\tTime range for force decomposition is %lf to %lf\n",
				ti,tf);
		}
	}

	// NUMBERS
	int nq = _model->getNQ();
	int nu = _model->getNU();
	int nb = _model->getNB();
	int ny = _model->getNY();
	int np = _model->getNP();

	// GRAVITY
	double g0[] = { 0.0, 0.0, 0.0 };
	double g[3],grav[3];
	_model->getGravity(g);
	printf("gravity = %lf %lf %lf\n",g[0],g[1],g[2]);

	// LOOP OVER TIME
	int i,j,J,c,body;
	int bodyB;
	double pointB[3];
	double t;
	double *y = new double[ny];
	double *fe = new double[3*np];
	double *dqdt = new double[nq];
	double *dudt = new double[nu];
	int npwr = nb + 1;
	double *indPower = new double[npwr];
	double com[] = { 0.0, 0.0, 0.0 };
	double acc[3],angAcc[3];
	double *vel = new double[nb*3];
	double *angVel = new double[nb*3];
	rdStateVector *yVec;
	for(i=0;i<_yStore->getSize();i++) {

		// GET STATES
		yVec = _yStore->getStateVector(i);
		t = yVec->getTime();
		_yStore->getDataAtTime(t,ny,y);

		// SET STATES
		_model->setTime(t);
		_model->setStates(y);
		
		// GET VELOCITIES
		// Need to store them for each body for power calculation 
		//	before we set them to zero for acceleration calculation
		for(body=0;body<nb;body++) {	
			int k = rdMtx::ComputeIndex(body,3,0);
			_model->getVelocity(body,com,&vel[k]);
			_model->getAngularVelocityBodyLocal(body,&angVel[k]);
		}

		// LOOP OVER INDEPENDENT COMPONENTS
		for(c=0;c<_nic;c++) {

			// SET GRAVITY
			if(c!=getGravityIndex()) {
				_model->setGravity(g0);
			} else {
				_model->setGravity(g);
			}

			// GET ELEMENT FORCES
			if(!getUseNullDecomposition()) {
				_feStore[c]->getDataAtTime(t,3*np,fe);
			}

			// GET STATES
			_yStore->getDataAtTime(t,ny,y);

			// SET TIME AND STATES
			if(c!=getVelocityIndex()) {
				for(j=0;j<nu;j++) y[nq+j] = 0.0;
			}
			_model->setTime(t);
			_model->setStates(y);

			// APPLY ACTUATOR FORCE
			if(c<=getLastActuatorIndex()) {
				_model->applyActuatorForce(c);
			}

			// APPLY ELEMENT FORCES
			for(j=0;j<_model->getNP();j++) {
				J = rdMtx::ComputeIndex(j,3,0);
				bodyB = _model->getContactBodyB(j);
				_model->getContactPointB(j,pointB);
				_model->applyForce(bodyB,pointB,&fe[J]);
			}

			// COMPUTE THE ACCELERATIONS
			_model->computeAccelerations(dqdt,dudt);
		
			// COMPUTE THE BODY POWERS
			for(body=0;body<nb;body++) {

				// GET ACCELERATIONS
				_model->getAcceleration(body,com,acc);
				_model->getAngularAccelerationBodyLocal(body,angAcc);
	
				// COMPUTE POWER
				double gravPower, linPower, angPower, power;
				double inertia[3][3];
				double result[3];
				
				int k = rdMtx::ComputeIndex(body,3,0);

				// GRAVITY
				_model->getGravity(grav);
				gravPower = 
					-_model->getMass(body) *rdMtx::DotProduct(3,grav,&vel[k]);

				// LINEAR KINETIC
				linPower =
					_model->getMass(body) * rdMtx::DotProduct(3,&vel[k],acc);

				// ANGULAR KINETIC
				_model->getInertiaBodyLocal(body,inertia);
				rdMtx::Multiply(3,3,1,&inertia[0][0],angAcc,result);
				angPower =  rdMtx::DotProduct(3,&angVel[k],result);

				// TOTAL
				power = gravPower + linPower + angPower;

				// FILL ARRAY
				indPower[body] = power;
			}

			// SUM POWERS
			for(indPower[npwr-1]=0.0,body=0;body<nb;body++) {
				indPower[npwr-1] += indPower[body];
			}

			// STORE THE BODY ACCELERATIONS
			if(_powerStore[c]==NULL) {
				_powerStore[c] = new
					rdStorage(1000,"BodyInducedPowers");
				_powerStore[c]->setDescription(getDescription());
				_powerStore[c]->setColumnLabels(getColumnLabels());
			}
			_powerStore[c]->append(t,npwr,indPower);
		}
	}

	// RESET GRAVITY
	_model->setGravity(g);

	// CLEANUP
	if(y!=NULL) { delete[] y;  y=NULL; }
	if(fe!=NULL) { delete[] fe;  fe=NULL; }
	if(dqdt!=NULL) { delete[] dqdt;  dqdt=NULL; }
	if(dudt!=NULL) { delete[] dudt;  dudt=NULL; }
	if(indPower!=NULL) { delete[] indPower;  indPower=NULL; }
	if(vel!=NULL) { delete[] vel;  vel=NULL; }
	if(angVel!=NULL) { delete[] angVel;  angVel=NULL; }

	return(0);
}


//=============================================================================
// UTILITY
//=============================================================================
//_____________________________________________________________________________
/**
 * Sum the power results.
 */
void suBodyIndPowers::
sumPowerResults()
{
	if(_powerStore[0]==NULL) return;

	// SUM ACROSS ACTUATORS
	int c;
	int cAct = getAllActuatorsIndex();
	if(_powerStore[cAct]!=NULL) delete _powerStore[cAct];
	_powerStore[cAct] = new rdStorage(*_powerStore[0]);
	for(c=1;c<=getLastActuatorIndex();c++) {
		if(_powerStore[c]!=NULL) _powerStore[cAct]->add(_powerStore[c]);
	}

	// SUMM ALL COMPONENTS
	int cAll = getAllIndex();
	if(_powerStore[cAll]!=NULL) delete _powerStore[cAll];
	_powerStore[cAll] = new rdStorage(*_powerStore[cAct]);
	_powerStore[cAll]->add(_powerStore[_cGrav]);
	_powerStore[cAll]->add(_powerStore[_cVel]);
	_powerStore[cAll]->add(_powerStore[_cIner]);
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
 * @param aExtension File extension.
 *
 * @return 0 on success, -1 on error.
 */
int suBodyIndPowers::
printResults(const char *aBaseName,const char *aDir,double aDT,
				 const char *aExtension)
{
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
	sumPowerResults();

	// COMPONENTS
	int c;
	char name[2048];
	for(c=0;c<_nc;c++) {

		// POWERS
		if(aExtension==NULL) {
			sprintf(name,"%s/%s_%s_%s",path,baseName,getName().c_str(),_cNames[c]);
		} else {
			sprintf(name,"%s/%s_%s_%s%s",path,baseName,getName().c_str(),_cNames[c],
				aExtension);
		}
		if(aDT<=0.0) {
			if(_powerStore[c]!=NULL) _powerStore[c]->print(name);
		} else {
			if(_powerStore[c]!=NULL) _powerStore[c]->print(name,aDT);
		}

	}

	return(0);
}
