// suIndAcc.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson and Saryn R. Goldberg
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
#include "suIndAcc.h"


using namespace std;


//=============================================================================
// CONSTANTS
//=============================================================================

// NAMES
char *cNames[] = {
	"Gravity","Velocity","Inertial","Actuators","All"
};



//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
suIndAcc::~suIndAcc()
{
	// NAMES AND DESCRIPTIONS
	if(_cNames!=NULL) { delete []_cNames;  _cNames=NULL; }

	// CONTACT FLAG
	if(_contactEstablished!=NULL)
		{ delete []_contactEstablished;  _contactEstablished=NULL; }
	
	// FORCE ELEMENT ARRAYS
	int c;
	if(_feContig!=NULL) { delete []_feContig;  _feContig=NULL; }
	if(_fe!=NULL) {
		for(c=0;c<_nc;c++) {
			if(_fe[c]!=NULL) { delete []_fe[c];  _fe[c]=NULL; }
		}
		delete []_fe;  _fe=NULL;
	}

	// STORAGE
	deleteStorage();
}
//_____________________________________________________________________________
/**
 * Construct an induced acceleration instance for a model.
 * This constructor is used if the induced acceleration analysis is going to
 * be performed during the course of a simulation.
 *
 * @param aModel Model on which the analyses are to be performed.
 */
suIndAcc::suIndAcc(rdModel *aModel) :
	rdAnalysis(aModel)
{
	int i;

	setNull();

	// NAME
	setName("IndAcc");

	// MEMBERS
	_yStore = NULL;
	_xStore = NULL;

	// INITIALIZE NUMBERS
	initializeNumbers();

	// CONTACT TOLERANCE
	setContactThreshold(1.0);

	// CONTACT
	_contactEstablished = new bool[_ne];
	for(i=0;i<_ne;i++) {
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
 * @param aStates Set of model controls.
 * @param aBaseName Base name for the force decompositon files.  If NULL,
 * accelerations are computed based on a NULL decompostion.
 * @param aDir Directory in which the results reside.
 * @param aExtension File extension of the force decomposition files.
 */
suIndAcc::suIndAcc(rdModel *aModel,rdStorage *aStates, rdStorage *aControls,
	char *aBaseName,char *aDir,char *aExtension) :
	rdAnalysis(aModel)
{
	printf("suIndAcc: constructing induced acceleration analysis from file.\n");
	printf("baseName = %s  aDir = %s  aExtension= %s\n",
		aBaseName,aDir,aExtension);

	setNull();

	// NAME
	setName("indAcc");

	// MEMBERS
	_yStore = aStates;
	_xStore = aControls;

	// INITIALIZE NUMBERS
	initializeNumbers();

	// CONTACT TOLERANCE
	setContactThreshold(1.0);

	// CONTACT
	_contactEstablished = new bool[_ne];
	int i;
	for(i=0;i<_ne;i++) {
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
void suIndAcc::
setNull()
{
	_nc = 0;
	_nic = 0;
	_ne = 0;
	_cAct = 0;
	_cGrav = 0;
	_cVel = 0;
	_cIner = 0;
	_cAllAct = 0;
	_cAll = 0;

	_cNames = NULL;
	_contactThreshold = 0.0;
	_contactEstablished = NULL;
	_feContig = NULL;
	_fe = NULL;
	_yStore = NULL;
	_xStore = NULL;
	_aeStore = NULL;
	_velStore = NULL;
	_posStore = NULL;
	_iPosStore = NULL;
	_iVelStore = NULL;
	_feStore = NULL;
	_aeDescrip = NULL;
	_aeLabels = NULL;
	_useNullDecomposition = false;
	_computeNormalizedAccelerations = false;
}
//_____________________________________________________________________________
/**
 * Initialize numbers of things.
 */
void suIndAcc::
initializeNumbers()
{
	// NUMBERS OF THINGS
	int na = _model->getNA();
	_nc = na + 5;
	_nic = _nc - 2;
	_ne = _model->getNP();

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
void suIndAcc::
constructComponentNames()
{
	// SET COMPONENTS NAMES
	int c;
	_cNames = new const char*[_nc];
	for(c=0;c<_nc;c++) {
		if(c<=_cAct) {
			_cNames[c] = _model->getActuatorName(c).c_str();
		} else {
			_cNames[c] = cNames[c-_cAct-1];
		}
	}
}
//-----------------------------------------------------------------------------
// DESCRIPTION
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Construct a description.
 */
void suIndAcc::
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
//_____________________________________________________________________________
/**
 * Construct the column labels.
 */
void suIndAcc::
constructColumnLabels()
{
	// GET GENERALIZED SPEED NAMES
	int i;
	string labels = "time";
	for(i=0;i<_model->getNU();i++) {
		labels += "\t";
		labels += _model->getSpeedName(i);
	}
	labels += "\n";

	setColumnLabels(labels.c_str());
}

//_____________________________________________________________________________
/**
 * Allocate element vectors.
 */
void suIndAcc::
allocateElementVectors()
{
	int c,i,j,I;

	// FORCE
	// Note- memory must be contiguous!
	_feContig = new double[_nc*_ne*3];
	_fe = new double**[_nc];
	for(c=0;c<_nc;c++) {
		_fe[c] = new double*[_ne];
		for(i=0;i<_ne;i++) {
			I = rdMtx::ComputeIndex(c,_ne,i,3,0);
			_fe[c][i] = &_feContig[I];
			for(j=0;j<3;j++) _fe[c][i][j] = 0.0;
		}
	}
}
//_____________________________________________________________________________
/**
 * Allocate storage pointers for the force decomposition and induced
 * accelerations.
 */
void suIndAcc::
allocateStoragePointers()
{
	_feStore = new rdStorage*[_nc];
	_aeStore = new rdStorage*[_nc];
	_velStore = new rdStorage*[_nc];
	_posStore = new rdStorage*[_nc];

	int c;
	for(c=0;c<_nc;c++) {
		_feStore[c] = NULL;
		_aeStore[c] = NULL;
		_velStore[c] = NULL;
		_posStore[c] = NULL;
	}
}
//_____________________________________________________________________________
/**
 * Allocate storage for the decomposition.
 */
void suIndAcc::
allocateStorage()
{
	// ALLOCATE STORAGE POINTERS
	allocateStoragePointers();

	// CREATE FORCE HEADERS
	int i;
	char tmp[2048],tmp1[2048];
	strcpy(tmp1,"time");
	for(i=0;i<_ne;i++) {
		sprintf(tmp,"\ts%dx\ts%dy\ts%dz",i,i,i);
		strcat(tmp1,tmp);
	}

	// ALLOCATE STORAGE
	int c;
	for(c=0;c<_nc;c++) {

		// FORCE
		_feStore[c] = new rdStorage(1000,"ForceDecomposition");
		_feStore[c]->setCapacityIncrement(1000);
		_feStore[c]->setColumnLabels(tmp1);
		
		// ACCELERATION
		_aeStore[c] = new rdStorage(1000,"InducedAccelerations");
		_aeStore[c]->setCapacityIncrement(1000);
		_aeStore[c]->setColumnLabels(getColumnLabels());
	}
}
//_____________________________________________________________________________
/**
 * Create a NULL decomposition.
 */
void suIndAcc::
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
		_feStore[c] = new rdStorage(1,"NullDecomposition");
		_feStore[c]->append(0.0,n,zero);
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
void suIndAcc::
deleteStorage()
{
	// FORCE DECOMPOSITION
	int c;
	if(_feStore!=NULL) {
		for(c=0;c<_nc;c++) {
			if(_feStore[c]!=NULL) { delete _feStore[c];  _feStore[c]=NULL; }
		}
		delete []_feStore;
	}

	// INDUCED ACCELERATIONS
	if(_aeStore!=NULL) {
		for(c=0;c<_nc;c++) {
			if(_aeStore[c]!=NULL) { delete _aeStore[c];  _aeStore[c]=NULL; }
		}
		delete []_aeStore;
	}

	// INDUCED VELOCITIES
	if(_velStore!=NULL) {
		for(c=0;c<_nc;c++) {
			if(_velStore[c]!=NULL) { delete _velStore[c];  _velStore[c]=NULL; }
		}
		delete []_velStore;
	}

	// INDUCED POSITIONS
	if(_posStore!=NULL) {
		for(c=0;c<_nc;c++) {
			if(_posStore[c]!=NULL) { delete _posStore[c];  _posStore[c]=NULL; }
		}
		delete []_posStore;
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
int suIndAcc::
getNumComponents()
{
	return(_nc);
}
//_____________________________________________________________________________
/**
 * Get the number of independent components.
 */
int suIndAcc::
getNumIndependentComponents()
{
	return(_nic);
}
//_____________________________________________________________________________
/**
 * Get the number of contact elements.
 */
int suIndAcc::
getNumElements()
{
	return(_ne);
}
//_____________________________________________________________________________
/**
 * Get the index of the last actuator component.
 */
int suIndAcc::
getLastActuatorIndex()
{
	return(_cAct);
}
//_____________________________________________________________________________
/**
 * Get the index of the gravity component.
 */
int suIndAcc::
getGravityIndex()
{
	return(_cGrav);
}
//_____________________________________________________________________________
/**
 * Get the index of the velocity component.
 */
int suIndAcc::
getVelocityIndex()
{
	return(_cVel);
}
//_____________________________________________________________________________
/**
 * Get the index of the inertial component.
 */
int suIndAcc::
getInertialIndex()
{
	return(_cIner);
}
//_____________________________________________________________________________
/**
 * Get the index of the total of all actuator components.
 */
int suIndAcc::
getAllActuatorsIndex()
{
	return(_cAllAct);
}
//_____________________________________________________________________________
/**
 * Get the index of the total of all components.
 */
int suIndAcc::
getAllIndex()
{
	return(_cAll);
}
//_____________________________________________________________________________
/**
 * GET THE NAME OF A COMPONENT
 */
const char* suIndAcc::
getComponentName(int aC)
{
	if(aC<0) return(NULL);
	if(aC>=_nc) return(NULL);
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
void suIndAcc::
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
double suIndAcc::
getContactThreshold()
{
	return(_contactThreshold);
}

//-----------------------------------------------------------------------------
// FORCE STORAGE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the force decomposition storage.
 *
 * @return Array of pointers to the force decomposition storage objects.
 */
rdStorage** suIndAcc::
getForceStorage()
{
	return(_feStore);
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
void suIndAcc::
setStorageCapacityIncrements(int aIncrement)
{
	int c;
	for(c=0;c<_nc;c++) {
		if(_feStore[c]!=NULL) _feStore[c]->setCapacityIncrement(aIncrement);
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
bool suIndAcc::
getUseNullDecomposition()
{
	return(_useNullDecomposition);
}

//-----------------------------------------------------------------------------
// NORMALIZED ACCELERATIONS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set whether or not accelerations are being normalized by actuator
 * force.  
 *
 * @param aBool Determines whether accelerations are normalized by actuator
 * force.
 */
void suIndAcc::
setComputeNormalizedAccelerations(bool aBool)
{
	_computeNormalizedAccelerations = aBool;
}
//_____________________________________________________________________________
/**
 * Get whether or not accelerations are being normalized by actuator
 * force.  
 *
 * @return True when the accelerations are being normalized by actuator
 * force 
 */
bool suIndAcc::
getComputeNormalizedAccelerations()
{
	return(_computeNormalizedAccelerations);
}


//=============================================================================
// OPERATIONS
//=============================================================================
//_____________________________________________________________________________
/**
 * Compute induced accelerations given the force decomposition and
 * set of states.
 *
 * @return 0 on success, -1 on error.
 */
int suIndAcc::
computeAccelerations()
{
	if(_yStore==NULL) return(-1);

	// CHECK FOR TIME CORRESPONDENCE
	if(!getUseNullDecomposition()) {
		double ti = _feStore[0]->getFirstTime();
		double tf = _feStore[0]->getLastTime();
		if((ti!=_yStore->getFirstTime())||(tf!=_yStore->getLastTime())) {
			printf("suIndAcc.computeAccelerations: WARN-\n");
			printf("\tTime range for states is %lf to %lf\n",
				_yStore->getFirstTime(),_yStore->getLastTime());
			printf("\tTime range for force decomposition is %lf to %lf\n",
				ti,tf);
		}
	}

	// NUMBERS
	int nq = _model->getNQ();
	int nu = _model->getNU();
	int ny = _model->getNY();
	int nx = _model->getNX();
	int np = _model->getNP();
	int n = nq + nu;

	// GRAVITY
	double g[3];
	double g0[] = { 0.0, 0.0, 0.0 };
	_model->getGravity(g);
	printf("gravity = %lf %lf %lf\n",g[0],g[1],g[2]);

	// LOOP OVER TIME
	int i,j,c,J,k;
	int bodyB;
	double pointB[3];
	double t, actuatorForce;
	double *fe = new double[3*np];
	double *y = new double[ny];
	double *x = new double[nx];
	double *dqdt = new double[nq];
	double *dudt = new double[nu];
	rdStateVector *yVec;
	for(i=0;i<_yStore->getSize();i++) {

		// LOOP OVER INDEPENDENT COMPONENTS
		for(c=0;c<_nic;c++) {

			// SET GRAVITY
			if(c!=getGravityIndex()) {
				_model->setGravity(g0);
			} else {
				_model->setGravity(g);
				_model->getGravity(g);
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
			if(c<_model->getNA())
				actuatorForce = _model->getActuatorForce(c);

			// APPLY ACTUATOR FORCE
			if(c<=getLastActuatorIndex()) {
				_model->applyActuatorForce(c);
			}

			// APPLY ELEMENT FORCES
			if(!getUseNullDecomposition()) {
				for(j=0;j<_model->getNP();j++) {
					J = rdMtx::ComputeIndex(j,3,0);
					bodyB = _model->getContactBodyB(j);
					_model->getContactPointB(j,pointB);
					_model->applyForce(bodyB,pointB,&fe[J]);
				}
			}

			// COMPUTE THE ACCELERATION
			_model->computeAccelerations(dqdt,dudt);

			// NORMALIZE ACCELERATIONS BY ACTUATOR FORCE
			if(_computeNormalizedAccelerations){
				if(c<_model->getNA()){
					for(k=0; k<_model->getNU();k++){
						if(actuatorForce > 0.0 || actuatorForce < 0.0)
							dudt[k] = dudt[k]/actuatorForce;
						else
							dudt[k] = 0.0;
					}
				}
			}		

			// DEGREES?
			if(getInDegrees()) {
				_model->convertRadiansToDegrees(dudt,dudt);
			}

			// STORE THE ACCELERATIONS
			if(_aeStore[c]==NULL) {
				_aeStore[c] = new rdStorage(1000,"InducedAccelerations");
				_aeStore[c]->setDescription(getDescription());
				_aeStore[c]->setColumnLabels(getColumnLabels());
			}
			_aeStore[c]->append(t,_model->getNU(),dudt);
		}
	}

	// COMPUTE THE INDUCED VELOCITIES AND POSITIONS
	for(c=0;c<_nic;c++) {
		
		// INTEGRATE TO GET VELOCITIES
		_velStore[c] = _aeStore[c]->integrate(_ti,_tf);

		// INTEGRATE TO GET POSITIONS
		_posStore[c] = _velStore[c]->integrate(_ti,_tf);
	}

	// INDUCED POSITION DUE TO INITIAL POSITION AND INITIAL VELOCITY
	
		//CONVERT STATE RDSTORAGE TO DEGREES
		double *rtd = new double[n];
		for(i=0;i<n;i++) rtd[i] = rdMath::RTD;
		rtd[0] = rtd[1] = rtd[2] = 1.0;
		rtd[nu] = rtd[nu+1] = rtd[nu+2] = rtd[nu+3] = 1.0;
		_yStore->multiply(n,rtd);
		double *stateVec = new double[n];
		_yStore->getDataAtTime(_ti,n,stateVec);

		//STORE INITIAL VELOCITIES
		_iVelStore = new rdStorage(*_yStore, false);
		_iVelStore->append(_ti,nu,&stateVec[nq]);

		// "INTEGRATE" INITIAL VELOCITES TO YIELD INITIAL POSITIONS
		// NOTE: position vector is only nu long to neglect last euler angle
		_model->convertQuaternionsToAngles(stateVec,stateVec);
		_iPosStore = new rdStorage(*_yStore, false);
		_iPosStore->append(_ti,nu,&stateVec[0]);
		_iPosStore->append(_tf,nu,&stateVec[nq]);
		_iPosStore->getStateVector(1)->multiply(_tf -_ti);
		_iPosStore->getStateVector(1)->add(nu,
			_iPosStore->getStateVector(0)->getData().get());

	// RESET GRAVITY
	_model->setGravity(g);

	// CLEANUP
	if(y!=NULL) { delete[] y;  y=NULL; }
	if(fe!=NULL) { delete[] fe;  y=NULL; }
	if(dqdt!=NULL) { delete[] dqdt;  dqdt=NULL; }
	if(dudt!=NULL) { delete[] dudt;  dudt=NULL; }

	return(0);
}


//=============================================================================
// UTILITY
//=============================================================================
//_____________________________________________________________________________
/**
 * Sum the force decompositon results.
 */
void suIndAcc::
sumForceResults()
{
	if(getUseNullDecomposition()) return;
	if(_feStore==NULL) return;
	if(_feStore[0]==NULL) return;

	// ALLOCATE ALL ACTUATOR STORAGE
	int C = getAllActuatorsIndex();
	if(_feStore[C]!=NULL) delete _feStore[C];
	_feStore[C] = new rdStorage(*_feStore[0]);

	// SUM ACROSS ACTUATORS
	int c;
	for(c=1;c<=getLastActuatorIndex();c++) {
		if(_feStore[c]!=NULL) _feStore[C]->add(_feStore[c]);
	}

	// ALLOCATE ALL STORAGE
	C = getAllIndex();
	if(_feStore[C]!=NULL) delete _feStore[C];
	_feStore[C] = new rdStorage(*_feStore[0]);

	// SUM ACROSS ACTUATORS
	for(c=1;c<_nic;c++) {
		if(_feStore[c]!=NULL) _feStore[C]->add(_feStore[c]);
	}
}
//_____________________________________________________________________________
/**
 * Sum the accelerations results.
 */
void suIndAcc::
sumAccelerationResults()
{
	if(_aeStore[0]==NULL) return;

	// SUM ACROSS ACTUATORS
	int c;
	int cAct = getAllActuatorsIndex();

	if(_aeStore[cAct]!=NULL) delete _aeStore[cAct];
	_aeStore[cAct] = new rdStorage(*_aeStore[0]);
	for(c=1;c<=getLastActuatorIndex();c++) {
		if(_aeStore[c]!=NULL) _aeStore[cAct]->add(_aeStore[c]);
	}
			
		// INTEGRATE TO GET VELOCITIES
		_velStore[cAct] = _aeStore[cAct]->integrate(_ti,_tf);

		// INTEGRATE TO GET POSITIONS
		_posStore[cAct] = _velStore[cAct]->integrate(_ti,_tf);

	// SUM ALL COMPONENTS
	int cAll = getAllIndex();

	if(_aeStore[cAll]!=NULL) delete _aeStore[cAll];
	_aeStore[cAll] = new rdStorage(*_aeStore[cAct]);
	_aeStore[cAll]->add(_aeStore[_cGrav]);
	_aeStore[cAll]->add(_aeStore[_cVel]);
	_aeStore[cAll]->add(_aeStore[_cIner]);

		// INTEGRATE TO GET VELOCITIES
		_velStore[cAll] = _aeStore[cAll]->integrate(_ti,_tf);

		// INTEGRATE TO GET POSITIONS
		_posStore[cAll] = _velStore[cAll]->integrate(_ti,_tf);

		// ADD INITIAL VELOCITIES
		rdStateVector *vVec;
		vVec = _iVelStore->getStateVector(0);
		_velStore[cAll]->add(vVec);

		// ADD POSITION DUE TO INITIAL VELOCITIES AND POSITIONS
		_posStore[cAll]->add(_iPosStore);
}
//_____________________________________________________________________________
/**
 * Sum the independent component forces to get the contribution of all
 * actuators and all components.
 */
void suIndAcc::
sumDecomposition()
{
	int c,i,j;

	// SUM FORCES ACROSS ALL ACTUATORS
	for(i=0;i<_ne;i++) {
		for(j=0;j<3;j++)  _fe[_cAllAct][i][j] = 0.0;
	}
	for(c=0;c<=_cAct;c++) {
		for(i=0;i<_ne;i++) {
			for(j=0;j<3;j++)  _fe[_cAllAct][i][j] += _fe[c][i][j];
		}
	}

	// SUPERPOSITION- SUM ACROSS ALL ELEMENTS
	for(i=0;i<_ne;i++) {
		for(j=0;j<3;j++)  _fe[_cAll][i][j] = 0.0;
	}
	for(c=0;c<_nic;c++) {
		for(i=0;i<_ne;i++) {
			for(j=0;j<3;j++) {
				_fe[_cAll][i][j] += _fe[c][i][j];
			}
		}
	}
}


//=============================================================================
// IO
//=============================================================================
//_____________________________________________________________________________
/**
 * Store various model quantities.
 */
void suIndAcc::
store()
{
	if(_feStore==NULL) return;

	// REAL TIME
	double tReal = _model->getTime() * _model->getTimeNormConstant();

	// SUM TOTAL FORCES WITHIN EACH COMPONENT
	sumDecomposition();

	// STORE ELEMENT INFORMATION
	int c;
	int nf=_ne*3;
	for(c=0;c<_nc;c++) {
		if(_feStore[c]!=NULL) _feStore[c]->append(tReal,nf,&_fe[c][0][0]);
	}
}
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
int suIndAcc::
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
		_feStore[c] = new rdStorage(name);
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
int suIndAcc::
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
	sumForceResults();
	sumAccelerationResults();

	// COMPONENTS
	int c;
	char name[2048];
	char label[120];

	if(_computeNormalizedAccelerations)
		strcpy(label,"_norm_");
	else
		strcpy(label,"_");

	for(c=0;c<_nc;c++) {

		// ACCELERATIONS
		if(aExtension==NULL) {
			sprintf(name,"%s/a%s%s_%s",path,label,baseName,_cNames[c]);
		} else {
			sprintf(name,"%s/a%s%s_%s%s",path,label,baseName,_cNames[c],aExtension);
		}
		if(aDT<=0.0) {
			if(_aeStore[c]!=NULL) _aeStore[c]->print(name);
		} else {
			if(_aeStore[c]!=NULL) _aeStore[c]->print(name,aDT);
		}

		// VELOCITIES
		if(aExtension==NULL) {
			sprintf(name,"%s/v%s%s_%s",path,label,baseName,_cNames[c]);
		} else {
			sprintf(name,"%s/v%s%s_%s%s",path,label,baseName,_cNames[c],aExtension);
		}
		if(aDT<=0.0) {
			if(_velStore[c]!=NULL) _velStore[c]->print(name);
		} else {
			if(_velStore[c]!=NULL) _velStore[c]->print(name,aDT);
		}

		// POSITIONS
		if(aExtension==NULL) {
			sprintf(name,"%s/p%s%s_%s",path,label,baseName,_cNames[c]);
		} else {
			sprintf(name,"%s/p%s%s_%s%s",path,label,baseName,_cNames[c],aExtension);
		}
		if(aDT<=0.0) {
			if(_posStore[c]!=NULL) _posStore[c]->print(name);
		} else {
			if(_posStore[c]!=NULL) _posStore[c]->print(name,aDT);
		}
	}

	//STATES IN DEGREES
	if(aExtension==NULL) {
		sprintf(name,"%s/%s_states",path,baseName);
	} else {
		sprintf(name,"%s/%s_states%s",path,baseName,aExtension);
	}
	if(aDT<=0.0) {
		if(_yStore!=NULL) _yStore->print(name);
	} else {
		if(_yStore!=NULL) _yStore->print(name,aDT);
	}

	//INITIAL VELOCITY
	if(aExtension==NULL) {
		sprintf(name,"%s/%s_initVel",path,baseName);
	} else {
		sprintf(name,"%s/%s_initVel%s",path,baseName,aExtension);
	}
	if(aDT<=0.0) {
		if(_iVelStore!=NULL) _iVelStore->print(name);
	} else {
		if(_iVelStore!=NULL) _iVelStore->print(name,aDT);
	}

	//INDUCED POSTION DUE TO INITIAL VELOCITY AND POSITION
	if(aExtension==NULL) {
		sprintf(name,"%s/p%s%s_initVelPos",path,label,baseName);
	} else {
		sprintf(name,"%s/p%s%s_initVelPos%s",path,label,baseName,aExtension);
	}
	if(aDT<=0.0) {
		if(_iPosStore!=NULL) _iPosStore->print(name, 0.005);
	} else {
		if(_iPosStore!=NULL) _iPosStore->print(name,aDT);
	}		

	return(0);
}


