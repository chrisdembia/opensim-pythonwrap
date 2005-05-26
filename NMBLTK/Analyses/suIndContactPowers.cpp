// suIndContactPowers.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <RD/Tools/rdMath.h>
#include <RD/Tools/rdMtx.h>
#include <RD/Tools/rdTools.h>
#include <RD/Simulation/Model/rdModel.h>
#include "suIndContactPowers.h"

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
suIndContactPowers::~suIndContactPowers()
{
	deleteStorage();
}
//_____________________________________________________________________________
/**
 * Construct an induced contact powers object based on a set of contact point
 * velocities, model states, and a contact force decomposition.
 *
 * @param aContactVelocities Velocities of the contact point expressed in the
 * global frame.  See class suContact.
 * @param aModel Model on which the simulation was run.
 * @param aStates Set of model states.
 * @param aBaseName Base name for the force decompositon files.  If NULL,
 * accelerations are computed based on a NULL decompostion.
 * @param aDir Directory in which the results reside.
 * @param aExtension File extension of the force decomposition files.
 * @see suContact, suIndAcc
 */
suIndContactPowers::suIndContactPowers(rdStorage *aContactVelocities,
	rdModel *aModel,rdStorage *aStates,rdStorage *aControls,char *aBaseName,
	char *aDir,char *aExtension) :
	suIndAcc(aModel,aStates,aControls,aBaseName,aDir,aExtension)
{
	printf("suIndContactPowers: constructing from file.\n");
	printf("baseName = %s  aDir = %s  aExtension= %s\n",
		aBaseName,aDir,aExtension);

	setNull();

	// NAME
	setName("InducedContactPowers");

	// CONTACT POINT VELOCITIES
	_velStore = aContactVelocities;

	// DESCRIPTION AND LABELS
	constructDescription();
	constructColumnLabels();

	// STORAGE
	allocateStorage();
}


//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Set member variables to approprate NULL values.
 */
void suIndContactPowers::
setNull()
{
	_velStore = NULL;
	_pwrStore = NULL;
}

//_____________________________________________________________________________
/**
 * Construct a description.
 */
void suIndContactPowers::
constructDescription()
{
	char descrip[DESCRIP_LENGTH];

	strcpy(descrip,"\nThis file contains the powers delivered to contact");
	strcat(descrip," elements\nby the individual actuators of a model");
	strcat(descrip," during a simulation.\n");
	strcat(descrip,"\nUnits are S.I. units (second, meters, Newtons, ...)");
	strcat(descrip,"\n\n");

	setDescription(descrip);
}

//_____________________________________________________________________________
/**
 * Construct the column labels.
 */
void suIndContactPowers::
constructColumnLabels()
{
	char labels[DESCRIP_LENGTH];
	char tmp[DESCRIP_LENGTH];

	// GET GENERALIZED SPEED NAMES
	int i,a,b;
	strcpy(labels,"Time");
	for(i=0;i<_model->getNP();i++) {
		a = _model->getContactBodyA(i);
		b = _model->getContactBodyB(i);
		sprintf(tmp,"\t%d_%s_%s",i,
			_model->getBodyName(a).c_str(),_model->getBodyName(b).c_str());
		strcat(labels,tmp);
	}
	strcat(labels,"\tTotal\n");

	setColumnLabels(labels);
}

//_____________________________________________________________________________
/**
 * Allocate storage pointers for the contact powers.
 */
void suIndContactPowers::
allocateStoragePointers()
{
	_pwrStore = new rdStorage*[_nc];

	int c;
	for(c=0;c<_nc;c++) {
		_pwrStore[c] = NULL;
	}
}
//_____________________________________________________________________________
/**
 * Allocate storage for the decomposition.
 */
void suIndContactPowers::
allocateStorage()
{
	// POINTERS
	allocateStoragePointers();

	// CONSTRUCT
	int c;
	for(c=0;c<_nc;c++) {

		// FORCE
		_pwrStore[c] = new rdStorage(1000,"InducedContactPowers");
		_pwrStore[c]->setCapacityIncrement(1000);
		_pwrStore[c]->setDescription(getDescription());
		_pwrStore[c]->setColumnLabels(getColumnLabels());
	}
}

//=============================================================================
// DESTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Delete storage objects.
 */
void suIndContactPowers::
deleteStorage()
{
	// FORCE DECOMPOSITION
	int c;
	if(_pwrStore!=NULL) {
		for(c=0;c<_nc;c++) {
			if(_pwrStore[c]!=NULL) { delete _pwrStore[c];  _pwrStore[c]=NULL; }
		}
		delete []_pwrStore;
	}
}


//=============================================================================
// GET AND SET
//=============================================================================
//-----------------------------------------------------------------------------
// CONTACT VELOCITIES
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the contact velocities.
 *
 * @return Contact velocities.
 */
rdStorage* suIndContactPowers::
getContactVelocities()
{
	return(_velStore);
}


//=============================================================================
// OPERATIONS
//=============================================================================
//_____________________________________________________________________________
/**
 * Compute induced contact powers.
 */
void suIndContactPowers::
computeContactPowers()
{
	// CHECK
	if(_velStore==NULL) {
		printf("suIndContactPowers.computeContactPowers: ERROR- no contact ");
		printf("velocities.");
		return;
	}
	if(getUseNullDecomposition()) {
		printf("suIndContactPowers.computeContactPowers: ERROR- NULL ");
		printf("decomposition.  Induced contact powers are zero.\n");
		return;
	}

	// NUMBERS
	int np = _model->getNP();

	// LOOP OVER TIME
	int i,c,p;
	int V,F;
	int nfrc = 3*np;
	double t;
	double v[3],*vel;
	double *frc = new double[nfrc];
	double *pwr = new double[np+1];
	rdStateVector *velVec;
	for(i=0;i<_velStore->getSize();i++) {

		// GET TIME AND VELOCITIES
		velVec = _velStore->getStateVector(i);
		t = velVec->getTime();
		vel = velVec->getData().get();

		// LOOP OVER INDEPENDENT COMPONENTS
		for(c=0;c<_nc;c++) {

			// GET CONTACT FORCES
			if(!getUseNullDecomposition()) {
				_feStore[c]->getDataAtTime(t,nfrc,frc);
			}

			// CONTACT POWERS
			for(pwr[np]=0.0,p=0;p<np;p++) {
				V = rdMtx::ComputeIndex(p,6,0);
				F = rdMtx::ComputeIndex(p,3,0);
				rdMtx::Subtract(1,3,&vel[V+3],&vel[V],v);
				pwr[p] = rdMtx::DotProduct(3,v,&frc[F]);
				pwr[np] += pwr[p];
			}

			// STORE
			_pwrStore[c]->append(t,np+1,pwr);
		}
	}

	// CLEANUP
	if(pwr!=NULL) { delete[] pwr;  pwr=NULL; }
	if(frc!=NULL) { delete[] frc;  frc=NULL; }

	return;
}


//=============================================================================
// UTILITY
//=============================================================================


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
int suIndContactPowers::
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

	// COMPONENTS
	int c;
	char name[2048];
	for(c=0;c<_nc;c++) {

		// INDUCED CONTACT POWERS
		if(!getUseNullDecomposition()) {
			if(aExtension==NULL) {
				sprintf(name,"%s/%s_%s_%s",path,baseName,getName().c_str(),_cNames[c]);
			} else {
				sprintf(name,"%s/%s_%s_%s%s",path,baseName,getName().c_str(),_cNames[c],
				aExtension);
			}
			if(aDT<=0.0) {
				if(_pwrStore[c]!=NULL)  _pwrStore[c]->print(name);
			} else {
				if(_pwrStore[c]!=NULL)  _pwrStore[c]->print(name,aDT);
			}
		}
	}

	return(0);
}


