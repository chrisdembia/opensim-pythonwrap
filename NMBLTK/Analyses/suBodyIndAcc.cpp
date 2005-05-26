// suBodyIndAcc.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson and Saryn Goldberg
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include <iostream>
#include <string>
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Tools/rdMtx.h>
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include "suBodyIndAcc.h"


using namespace std;


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
suBodyIndAcc::~suBodyIndAcc()
{
	// STORAGE
	deleteBodyStorage();
}
//_____________________________________________________________________________
/**
 * Construct an induced acceleration instance for performing an induced
 * acceleration analysis on the bodies of a model.
 *
 * @param aModel Model on which the analyses are to be performed.
 */
suBodyIndAcc::suBodyIndAcc(rdModel *aModel) :
	suIndAcc(aModel)
{
	setName("BodyIndAcc");

	// MEMBERS
	_aeBodyStore = NULL;

	// DESCRIPTION
	constructDescription();
	constructColumnLabels();

	// STORAGE
	allocateBodyStorage();
}
//_____________________________________________________________________________
/**
 * Construct an induced acceleration instance from a set of force
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
 * @todo	verify induced accelerations are correct
 * @todo	check that code is correct for generalized force case
 */
suBodyIndAcc::suBodyIndAcc(rdModel *aModel,rdStorage *aStates,rdStorage *aControls,
	char *aBaseName,char *aDir,char *aExtension) :
	suIndAcc(aModel,aStates,aControls,aBaseName,aDir,aExtension)
{
	printf("suBodyIndAcc: constructing induced acceleration analysis from file.\n");
	printf("baseName = %s  aDir = %s  aExtension= %s\n",
		aBaseName,aDir,aExtension);

	// DESCRIPTION
	constructDescription();
	constructColumnLabels();

	// STORAGE
	allocateBodyStoragePointers();
}


//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Construct a description for the body kinematics files.
 */
void suBodyIndAcc::
constructDescription()
{
	char descrip[1024];
	char tmp[MAXLEN];

	strcpy(descrip,"\nThis file contains the induced accelerations");
	sprintf(tmp," of the body segments in model %s.\n",
		_model->getName().c_str());
	strcat(descrip,tmp);
	strcat(descrip,"\nInduced angular accelerations are given about");
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
 * Construct column labels for the body kinematics files.
 */
void suBodyIndAcc::
constructColumnLabels()
{

	// GET STATE NAMES
	int i;
	string labels;
	string name;
	if(_model->getBodyName(0).empty()) {
		setColumnLabels(NULL);

	} else {
		labels = "time";
		for(i=0;i<_model->getNB();i++) {
			labels += "\t" + _model->getBodyName(i) + "_X";
			labels += "\t" + _model->getBodyName(i) + "_Y";
			labels += "\t" + _model->getBodyName(i) + "_Z";
			labels += "\t" + _model->getBodyName(i) + "_Ox";
			labels += "\t" + _model->getBodyName(i) + "_Oy";
			labels += "\t" + _model->getBodyName(i) + "_Oz";
		}
		labels += "\n";
	}

	setColumnLabels(labels.c_str());
}

//_____________________________________________________________________________
/**
 * Allocate storage pointers for the induced accelerations of the bodies.
 */
void suBodyIndAcc::
allocateBodyStoragePointers()
{
	_aeBodyStore = new rdStorage*[_nc];
	int c;
	for(c=0;c<_nc;c++) {
		_aeBodyStore[c] = NULL;
	}
}
//_____________________________________________________________________________
/**
 * Allocate storage.
 */
void suBodyIndAcc::
allocateBodyStorage()
{
	// ALLOCATE STORAGE POINTERS
	allocateBodyStoragePointers();

	// ALLOCATE STORAGE
	int c;
	for(c=0;c<_nc;c++) {
		_aeBodyStore[c] = new rdStorage(500,"BodyInducedAccelerations");
		_aeBodyStore[c]->setCapacityIncrement(100);
		_aeBodyStore[c]->setDescription(getDescription());
		_aeBodyStore[c]->setColumnLabels(getColumnLabels());
	}
}


//=============================================================================
// DESTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Delete storage objects.
 */
void suBodyIndAcc::
deleteBodyStorage()
{
	// INDUCED ACCELERATIONS
	int c;
	if(_aeBodyStore!=NULL) {
		for(c=0;c<_nc;c++) {
			if(_aeBodyStore[c]!=NULL) { delete _aeBodyStore[c];  _aeBodyStore[c]=NULL; }
		}
		delete []_aeBodyStore;
	}
}


//=============================================================================
// GET AND SET
//=============================================================================
/**
 * Returns a pointer to an _aeBodyStore.
 *
 * @param index The index of the aeBodyStore to return
 */

rdStorage* suBodyIndAcc::
getBodyStore(int index)
{
	if(index < 0 || index >= _nc)
		return(NULL);
	else
		return(_aeBodyStore[index]);
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
void suBodyIndAcc::
setStorageCapacityIncrements(int aIncrement)
{
	// BASE CLASS
	suIndAcc::setStorageCapacityIncrements(aIncrement);

	// THIS CLASS
	int c;
	for(c=0;c<_nc;c++) {
		_aeBodyStore[c]->setCapacityIncrement(aIncrement);
	}
}


//=============================================================================
// OPERATIONS
//=============================================================================
//_____________________________________________________________________________
/**
 * Compute the induced accelerations of the bodies of a model from a
 * force decomposition and a set of states.
 *
 * @return 0 on success, -1 on error.
 */
int suBodyIndAcc::
computeBodyAccelerations()
{
	if(_yStore==NULL) return(-1);

	// CHECK FOR TIME CORRESPONDENCE
	if(!getUseNullDecomposition()) {
		double ti = _feStore[0]->getFirstTime();
		double tf = _feStore[0]->getLastTime();
		if((ti!=_yStore->getFirstTime())||(tf!=_yStore->getLastTime())) {
			printf("suBodyIndAcc.computeAccelerations: WARN-\n");
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
	int nx = _model->getNX();
	int np = _model->getNP();

	// GRAVITY
	double g[3];
	double g0[] = { 0.0, 0.0, 0.0 };
	_model->getGravity(g);
	printf("gravity = %lf %lf %lf\n",g[0],g[1],g[2]);

	// LOOP OVER TIME
	int i,j,c,body,I,J;
	int bodyB;
	double pointB[3];
	double t;
	rdStateVector *yVec;
	double *y = new double[ny];
	double *x = new double[nx];
	double *fe = new double[3*np];
	double *dqdt = new double[nq];
	double *dudt = new double[nu];
	double *indAcc = new double[6*nb];
	double *initVel = new double[6*nb];
	double *initPos = new double[6*nb];
	double com[] = { 0.0, 0.0, 0.0 };
	double acc[3],angAcc[3], vel[3], angVel[3], pos[3], angPos[3];
	double dirCos[3][3];
	for(i=0;i<_yStore->getSize();i++) {

		// LOOP OVER INDEPENDENT COMPONENTS
		for(c=0;c<_nic;c++) {

			// SET GRAVITY
			if(c!=getGravityIndex()) {
				_model->setGravity(g0);
			} else {
				_model->setGravity(g);
			}

			// GET STATES
			yVec = _yStore->getStateVector(i);
			t = yVec->getTime();
			if(i==0) _ti = t;
			if(i==(_yStore->getSize() - 1)) _tf = t;
			_yStore->getDataAtTime(t,ny,y);

			// GET CONTROLS
			if(_xStore!=NULL)
				_xStore->getDataAtTime(t,nx,x);

			// GET CONTACT POINT FORCES
			if(!getUseNullDecomposition()) {
				_feStore[c]->getDataAtTime(t,3*np,fe);
			}

			// SET
			if(c!=getVelocityIndex()) {
				for(j=0;j<nu;j++) y[nq+j] = 0.0;
			}
			_model->set(t,x,y);

			// COMPUTE ACTUATION
			_model->computeActuation();

			// NEED TO RECORD THE INITIAL BODY VELOCITIES AND POSITIONS
				if(c==getVelocityIndex() && t==_ti){
					_model->applyActuatorForces();
					_model->computeAccelerations(dqdt,dudt);

					for(body=0;body<nb;body++) {
						_model->getVelocity(body,com,vel);
						_model->getAngularVelocityBodyLocal(body,angVel);

						_model->getPosition(body,com,pos);	
						_model->getDirectionCosines(body, dirCos);
						_model->convertDirectionCosinesToAngles(dirCos,&angPos[0],&angPos[1],
								&angPos[2]);
		
						// DEGREES?
						if(getInDegrees()) {
							for(j=0;j<3;j++) {
								angVel[j] *= rdMath::RTD;
								angPos[j] *= rdMath::RTD;	
							}
						}
	
						// FILL ARRAY
						I = rdMtx::ComputeIndex(body,6,0);
						memcpy(&initVel[I],vel,3*sizeof(double));
						memcpy(&initVel[I+3],angVel,3*sizeof(double));
					
						memcpy(&initPos[I],pos,3*sizeof(double));
						memcpy(&initPos[I+3],angPos,3*sizeof(double));
					}

					// RESET STATES
					_model->set(t,x,y);

					// RECOMPUTE ACTUATION
					_model->computeActuation();		
				}

			// APPLY ACTUATOR FORCE
			if(c<=getLastActuatorIndex()) {
				_model->applyActuatorForce(c);
			}

			// APPLY ELEMENT FORCES
			if(!getUseNullDecomposition()) {
				for(j=0;j<np;j++) {
					J = rdMtx::ComputeIndex(j,3,0);
					bodyB = _model->getContactBodyB(j);
					_model->getContactPointB(j,pointB);
					_model->applyForce(bodyB,pointB,&fe[J]);
				}
			}

			// COMPUTE THE ACCELERATIONS
			_model->computeAccelerations(dqdt,dudt);

			// COMPUTE THE BODY ACCELERATIONS
			for(body=0;body<nb;body++) {

				// COMPUTE
				_model->getAcceleration(body,com,acc);
				_model->getAngularAccelerationBodyLocal(body,angAcc);

				// DEGREES?
				if(getInDegrees()) {
					for(j=0;j<3;j++) {
						angAcc[j] *= rdMath::RTD;
					}
				}

				// FILL ARRAY
				I = rdMtx::ComputeIndex(body,6,0);
				memcpy(&indAcc[I],acc,3*sizeof(double));
				memcpy(&indAcc[I+3],angAcc,3*sizeof(double));
			}
	
			// STORE THE BODY ACCELERATIONS
			if(_aeBodyStore[c]==NULL) {
				_aeBodyStore[c] = new
					rdStorage(1000,"BodyInducedAccelerations");
				_aeBodyStore[c]->setDescription(getDescription());
				_aeBodyStore[c]->setColumnLabels(getColumnLabels());
			}
			_aeBodyStore[c]->append(t,6*nb,indAcc);
		}
	}

	// COMPUTE THE INDUCED VELOCITIES AND POSITIONS
	for(c=0;c<_nic;c++) {
		
		// INTEGRATE TO GET VELOCITIES
		_velStore[c] = _aeBodyStore[c]->integrate(_ti,_tf);

		// INTEGRATE TO GET POSITIONS
		_posStore[c] = _velStore[c]->integrate(_ti,_tf);
	}

	// INDUCED POSITION DUE TO INITIAL POSITION AND INITIAL VELOCITY
	
		//STORE INITIAL VELOCITIES
		_iVelStore = new rdStorage(*_yStore, false);
		_iVelStore->append(_ti,6*nb,&initVel[0]);

		// "INTEGRATE" INITIAL VELOCITES TO YIELD INITIAL POSITIONS
		_iPosStore = new rdStorage(*_yStore, false);
		_iPosStore->append(_ti,6*nb,&initPos[0]);
		_iPosStore->append(_tf,6*nb,&initVel[0]);
		_iPosStore->getStateVector(1)->multiply(_tf -_ti);
		_iPosStore->getStateVector(1)->add(nu,_iPosStore->getStateVector(0)->getData().get());

	// RESET GRAVITY
	_model->setGravity(g);

	// CLEANUP
	if(y!=NULL) { delete[] y;  y=NULL; }
	if(dqdt!=NULL) { delete[] dqdt;  dqdt=NULL; }
	if(dudt!=NULL) { delete[] dudt;  dudt=NULL; }
	if(indAcc!=NULL) { delete[] indAcc;  indAcc=NULL; }

	return(0);
}


//=============================================================================
// UTILITY
//=============================================================================
//_____________________________________________________________________________
/**
 * Sum the accelerations results.
 */
void suBodyIndAcc::
sumBodyAccelerationResults()
{
	if(_aeBodyStore[0]==NULL) return;

	// SUM ACROSS ACTUATORS
	int c;
	int cAct = getAllActuatorsIndex();
	if(_aeBodyStore[cAct]!=NULL) delete _aeBodyStore[cAct];
	_aeBodyStore[cAct] = new rdStorage(*_aeBodyStore[0]);
	for(c=1;c<=getLastActuatorIndex();c++) {
		if(_aeBodyStore[c]!=NULL) _aeBodyStore[cAct]->add(_aeBodyStore[c]);
	}
			
		// INTEGRATE TO GET VELOCITIES
		_velStore[cAct] = _aeBodyStore[cAct]->integrate(_ti,_tf);

		// INTEGRATE TO GET POSITIONS
		_posStore[cAct] = _velStore[cAct]->integrate(_ti,_tf);

	// SUM ALL COMPONENTS
	int cAll = getAllIndex();
	if(_aeBodyStore[cAll]!=NULL) delete _aeBodyStore[cAll];
	_aeBodyStore[cAll] = new rdStorage(*_aeBodyStore[cAct]);
	_aeBodyStore[cAll]->add(_aeBodyStore[_cGrav]);
	_aeBodyStore[cAll]->add(_aeBodyStore[_cVel]);
	_aeBodyStore[cAll]->add(_aeBodyStore[_cIner]);

		// INTEGRATE TO GET VELOCITIES
		_velStore[cAll] = _aeBodyStore[cAll]->integrate(_ti,_tf);

		// INTEGRATE TO GET POSITIONS
		_posStore[cAll] = _velStore[cAll]->integrate(_ti,_tf);

		// ADD INITIAL VELOCITIES
		rdStateVector *vVec;
		vVec = _iVelStore->getStateVector(0);
		_velStore[cAll]->add(vVec);

		// ADD POSITION DUE TO INITIAL VELOCITIES AND POSITIONS
		_posStore[cAll]->add(_iPosStore);
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
int suBodyIndAcc::
printResults(const char *aBaseName,const char *aDir,double aDT,
				 const char *aExtension)
{
	if(aBaseName==NULL) return(-1);

	// CONSTRUCT PATH
	char path[2048];
	if(aDir==NULL) {
		strcpy(path,".");
	} else {
		strcpy(path,aDir);
	}

	// SUM RESULTS
	sumBodyAccelerationResults();

	// COMPONENTS
	int c;
	char name[2048];
	for(c=0;c<_nc;c++) {

		// ACCELERATIONS
		if(aExtension==NULL) {
			sprintf(name,"%s/abody_%s_%s",path,aBaseName,_cNames[c]);
		} else {
			sprintf(name,"%s/abody_%s_%s%s",path,aBaseName,_cNames[c],
				aExtension);
		}
		if(aDT<=0.0) {
			if(_aeBodyStore[c]!=NULL) _aeBodyStore[c]->print(name);
		} else {
			if(_aeBodyStore[c]!=NULL) _aeBodyStore[c]->print(name,aDT);
		}

		// VELOCITIES
		if(aExtension==NULL) {
			sprintf(name,"%s/vbody_%s_%s",path,aBaseName,_cNames[c]);
		} else {
			sprintf(name,"%s/vbody_%s_%s%s",path,aBaseName,_cNames[c],aExtension);
		}
		if(aDT<=0.0) {
			if(_velStore[c]!=NULL) _velStore[c]->print(name);
		} else {
			if(_velStore[c]!=NULL) _velStore[c]->print(name,aDT);
		}

		// POSITIONS
		if(aExtension==NULL) {
			sprintf(name,"%s/pbody_%s_%s",path,aBaseName,_cNames[c]);
		} else {
			sprintf(name,"%s/pbody_%s_%s%s",path,aBaseName,_cNames[c],aExtension);
		}
		if(aDT<=0.0) {
			if(_posStore[c]!=NULL) _posStore[c]->print(name);
		} else {
			if(_posStore[c]!=NULL) _posStore[c]->print(name,aDT);
		}
	}

	//INITIAL VELOCITY
	if(aExtension==NULL) {
		sprintf(name,"%s/%s_initVelBody",path,aBaseName);
	} else {
		sprintf(name,"%s/%s_initVelBody%s",path,aBaseName,aExtension);
	}
	if(aDT<=0.0) {
		if(_iVelStore!=NULL) _iVelStore->print(name);
	} else {
		if(_iVelStore!=NULL) _iVelStore->print(name,aDT);
	}

	//INDUCED POSTION DUE TO INITIAL VELOCITY AND POSITION
	if(aExtension==NULL) {
		sprintf(name,"%s/pbody_%s_initVelPos",path,aBaseName);
	} else {
		sprintf(name,"%s/p_%s_initVelPos%s",path,aBaseName,aExtension);
	}
	if(aDT<=0.0) {
		if(_iPosStore!=NULL) _iPosStore->print(name, 0.005);
	} else {
		if(_iPosStore!=NULL) _iPosStore->print(name,aDT);
	}		


	return(0);
}
