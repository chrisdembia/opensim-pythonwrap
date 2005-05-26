// suSIMMPipeline323.cpp
// Joon H. Shim shimm@stanford.edu

//=============================================================================
// INCLUDES
//=============================================================================

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <RD/Simulation/SDFast/sdfast.h>
#include <RD/Tools/rdMath.h>
#include <RD/Simulation/Model/rdModel.h>
#include <RD/Simulation/Model/rdAnalysis.h>
#include <RD/Simulation/SDFast/rdSDFast.h>
#include <RD/Simulation/SDFast/rdActuatedModel_SDFast.h>
#include <RD/Simulation/SDFast/rdSDFastDLL.h>
#include "suSIMMPipeline323.h"

//-----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//-----------------------------------------------------------------------------

//=============================================================================
// SIMM RELATED
//=============================================================================

void sdstab(double velin,double posin);

//=============================================================================
// EXTERNALS
//=============================================================================
extern SDModelStruct sdm;

//-----------------------------------------------------------------------------
#ifdef __cplusplus
}
#endif
//-----------------------------------------------------------------------------


//=============================================================================
// STATICS
//=============================================================================
static char UNKNOWN[] = "UNKNOWN";


//=============================================================================
// CONSTANTS
//=============================================================================



//=============================================================================
// STATICS
//=============================================================================


//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
suSIMMPipeline323::~suSIMMPipeline323()
{
	if(_y!=NULL) { delete[] _y;  _y=NULL; }
	if(_dy!=NULL) { delete[] _dy; _dy=NULL; }
}

//_____________________________________________________________________________
/**
 * Default constructor.
 *
 * @param aContacts Set of contact force objects for a simulation.
 */
suSIMMPipeline323::suSIMMPipeline323(char *aParametersFileName,rdContactForceSet *aContacts) :
	rdActuatedModel_SDFast(NULL,aContacts)
{
   setNull();

   // INITIALIZE THE MODEL
	char *aMuscle_file=NULL;
   char *kinetics_file=NULL;
   char *output_motion_file = NULL;
   char *output_kinetics_file = NULL;
   char *parameters_file_name = "params.txt";
   ReturnCode rc;
   MotionData* kinetics_data = NULL;
   
   // INITIALIZE SIMM MODEL
   init_model();
	
   // READ PARAM.TXT FILE
   rc=read_parameters_file(aParametersFileName, &sdm, &aMuscle_file,
	   &kinetics_file, &output_motion_file, &output_kinetics_file);

   // INITIALIZE DYNAMIC FUNCTIONS
   init_joint_functions();
   init_q_restraint_functions();
   
   // READ SIMM MUSCLE FILE
   if (aMuscle_file)
		rc=read_muscle_file(&sdm, aMuscle_file);

   sdm.neq = sdm.nu + sdm.nq + count_muscle_states(&sdm);

   // SET NUMBERS
	_nx = sdm.num_muscles;		// CONTROLS
	_na = sdm.num_muscles;		// ACTUATORS
	_ny = sdm.neq;				// STATES
	//_nq = sdm.nq;				// GENCOORDS
	_q.setSize(sdm.nq);
	//_nu = sdm.nu;				// GENERALIZED SPEED
	_u.setSize(sdm.nu);

   // ALLOCATIONS
   if(getNX()>0) _x = new double[getNX()];
   if(getNY()>0)  { 
		_y = new double[getNY()];
		_dy = new double[getNY()];   // ARRAY OF STATE DERIVATIVES
   }
   
   // READ KINETICS FILE
   if (kinetics_file)
      set_up_kinetics_input(kinetics_file, &kinetics_data);

   // INITIAL STATES
   constructInitialStates();
   
   // CONSTRUCT NAMES
   constructNames();
}

//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Set member variables to their appropriate null values.
 */
void suSIMMPipeline323::
setNull()
{
	_y = NULL;
	_dy = NULL;
}

//_____________________________________________________________________________
/**
 * Construct the valid initial states.
 */
void suSIMMPipeline323::
constructInitialStates()
{
	if(getNY()<=0) return;

	// ALLOCATE MEMORY FOR POINTERS AND ALLOCATE MEMORY FOR INITIAL STATES
	_yi = new double[getNY()];

	// SET INITIAL CONDITIONS
	set_initial_conditions(&_t,_y,_dy);

	// INITIAL MOTION
	init_motion();
	sdinit();
   
	// CONTRAINTS STABLIZATION
	sdstab(2.0 * 20, 20 * 20);

	// ASSEMBLE THE MODEL
	assemble_model(_t, _y);

	// STORE STATES IN SDGSTATE
	sdstate(_t, _y, &_dy[_q.getSize()]);

	// INITIALIZE ACTUATIONS
	init_muscle_states(&sdm, _y);

	// INITIAL STATES
	int i;
	for(i=0;i<getNY();i++)  _yi[i] = _y[i];

}

//_____________________________________________________________________________
/**
 * Construct the names of the various components of the model.
 */
void suSIMMPipeline323::
constructNames()
{
	printf("suSIMMPipeline323.constructControlNames: \n");

	// NAME
	setName("suSIMMPipeline323");
	
	// CONTROLS
	int i;
	printf("suSIMMPipeline323.constructNames: nx = %d\n",getNX());
	_xNames = new char*[getNX()];
	for(i=0;i<getNX();i++) {
		_xNames[i] = sdm.muscles[i].name;
	}

	// BODIES
	printf("suSIMMPipeline323.constructNames: nb = %d\n",getNB());
	_bNames = new char*[getNB()];
	for(i=0;i<getNB();i++) {
		_bNames[i] = sdm.body_segment[i].name;
	}

	// ACTUATORS
	printf("suSIMMPipeline323.constructNames: na = %d\n",getNA());
	_aNames = new char*[getNA()];
	for(i=0;i<getNA();i++) {
		_aNames[i] = sdm.muscles[i].name;
	}

	// GENERALIZED COORDINATES
	printf("suSIMMPipeline323.constructNames: nq = %d\n",getNQ());
	//_qNames = new char*[getNQ()];
	for(i=0;i<getNQ();i++) {
		_q.setNameAt(i, sdm.q[i].name);
	}

	// GENERALIZED SPEEDS
	printf("suSIMMPipeline323.constructNames: nu = %d\n",getNU());
	//_uNames = new char*[getNU()];
	for(i=0;i<getNU();i++) {
		_u.setNameAt(i, sdm.q[i].name);

	}

	// STATES
	// BUG? - Clay & Joon
	// The names of the U's are not necessarily the same as the
	// names of the Q's.  Also, the names of the muscle states
	// have not been set.
	printf("suSIMMPipeline323.constructNames: ny = %d\n",getNY());
	_yNames = new char*[getNY()];
	for(i=0;i<getNY();i++) _yNames[i] = UNKNOWN;
	for(i=0;i<getNQ();i++) {
		_yNames[i] = sdm.q[i].name;
	}
	for(i=0;i<getNU();i++) {
		_yNames[i+getNQ()] = sdm.q[i].name;
	}

}

//=============================================================================
// GET AND SET
//=============================================================================
//-----------------------------------------------------------------------------
// STATES
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the current states for this model.
 *
 * This method sets the configuration (coordinates and speeds) of the model
 * and also the states of the actuators.
 *
 * @param aY Array of states.  The size of aY should be the value returned by
 * getNY().
 * @see rdActuatedModel_SDFast::setStates();
 * @see rdModel::setConfiguration().
 * @see rdSDFast::setConfiguration().
 */
void suSIMMPipeline323::
setStates(const double aY[])
{
	int ny = getNY();
	if(ny>0) memcpy(_y,aY,ny*sizeof(double));
	rdActuatedModel_SDFast::setStates(aY);
}

//-----------------------------------------------------------------------------
// CONFIGURATION
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the configuration of the model.
 *
 * @param aQ Generalized coordinates.
 * @param aU Generalized speeds.
 * @todo Should the states (y) be set when q and u are set?
 */
void suSIMMPipeline323::
setConfiguration(const double aQ[],const double aU[])
{
	int nq = getNQ();
	if(nq>0) memcpy(_y,aQ,nq*sizeof(double));

	int nu = getNU();
	if(nu>0) memcpy(&_y[nq],aU,nu*sizeof(double));

	rdSDFast::setConfiguration(aQ,aU);
}
//_____________________________________________________________________________
/**
 * Set the configuration of the model.
 *
 * @param aY Statevector.
 */
void suSIMMPipeline323::
setConfiguration(const double aY[])
{
	int ny = getNY();
	if(ny>0) memcpy(_y,aY,ny*sizeof(double));

	rdSDFast::setConfiguration(aY);
}


//=============================================================================
// CONTACT : see rdActuatedModel_SDFast.cpp
//=============================================================================



//=============================================================================
// ACTUATION : Muscles
//=============================================================================
//_____________________________________________________________________________
/**
 * Compute all quatities associated with actuation of the model.
 *
 * This method assumes that the configuration of the model has already
 * been set.
 *
 * @see rdModel::set();
 * @see rdModel::setConfiguration();
 */
void suSIMMPipeline323::
computeActuation()
{
	// SET EXCITATION LEVELS
	int err=0;
	int i;
	double param[1] = { -1.0 };
	
	for (i=0;i<getNX();i++) {
		//sdm.muscles[j].excitation_level 
		//= calc_excitation(&sdm.muscles[j], _t, _y);
		sdm.muscles[i].excitation_level = getControl(i);
	}

	// SET CONFIGURATION OF MODEL
	//sdstate(_t, _y, &_y[_nq]);  This should not be called here.  It was already called.

	// COMPUTE DERIVATIVES OF ACTUATIONS
	calc_muscle_derivatives(_t, _y, _dy, param, &err);
}

//_____________________________________________________________________________
/**
 * Apply a particular actuator force to the model.
 *
 * @param aI The index of the actuator force to apply
 */
void suSIMMPipeline323::
applyActuatorForce(int aID)
{
	int k, sdbody1, sdbody2, start, end;
	double force_vector[3], norm_force_vector[3], body_force_vector[3];
	double inertial_pt1[3], inertial_pt2[3];
	double aForce=sdm.muscles[aID].force;
	MuscleStruct *ms = &sdm.muscles[aID];
	
	for(start = 0; start < ms->num_points - 1; start++) {
	   
		end = start + 1;

		sdbody1 = ms->mp[start]->segment;
		sdbody2 = ms->mp[end]->segment;

		if (sdbody1 != sdbody2) {
			sdpos(sdbody1, ms->mp[start]->point, inertial_pt1);
			sdpos(sdbody2, ms->mp[end]->point, inertial_pt2);

			for (k=0; k<3; k++)
				force_vector[k] = inertial_pt2[k] - inertial_pt1[k];

			normalize_vector(force_vector, norm_force_vector);

			sdtrans(GROUND, norm_force_vector, sdbody1, body_force_vector);

			for (k = 0; k < 3; k++)
				body_force_vector[k] *= aForce;
			
			sdpointf(sdbody1, ms->mp[start]->point, body_force_vector);

			sdtrans(GROUND,norm_force_vector,sdbody2,body_force_vector);
			for (k=0; k<3; k++)
                 body_force_vector[k] *= -aForce;
              sdpointf(sdbody2,ms->mp[end]->point,body_force_vector);
		}
	}
}

//_____________________________________________________________________________
/**
 * Apply all actuator forces to the model. Actuator forces include
 * muscle forces and ligament torques.
 */
void suSIMMPipeline323::
applyActuatorForces()
{
	int i;
	for (i=0;i<getNA();i++)  applyActuatorForce(i); 
}

//_____________________________________________________________________________
/**
 * Set a force at a particular actuator with param aI 
 * the index of the actuator force to apply.
 */
void suSIMMPipeline323::
setActuatorForce(int aID,double aForce)
{
   sdm.muscles[aID].force = aForce;
}

//_____________________________________________________________________________
/**
 * Get the magnitude of force expected by a particular actuator.
 */
double suSIMMPipeline323::
getActuatorForce(int aID) const
{
   return( sdm.muscles[aID].force );
}

//_____________________________________________________________________________
/**
 * Get the speed at which a particular actuator force is applied.
 */
double suSIMMPipeline323::
getActuatorSpeed(int aID) const
{
   return( sdm.muscles[aID].muscle_tendon_vel );
}

//_____________________________________________________________________________
/**
 * Get the power appled to body segments by a particular actuator.
 */
double suSIMMPipeline323::
getActuatorPower(int aID) const 
{
   return( sdm.muscles[aID].applied_power );
}


//=============================================================================
// DERIVATIVES : see rdActuatedModel_SDFast.cpp
//=============================================================================
//_____________________________________________________________________________
/**
 * Compute the derivatives of the states.
 *
 * @param t Current time in the simulation.
 * @param xt Controls.
 * @param y States.
 * @param dy Time derivatives of states in normalized time.
 */
int suSIMMPipeline323::
deriv(double t,double *xt,double *y,double *dy)
{
	// SET REAL TIME
	// CONVERT NORMALIZED TIME TO REAL TIME
	// _t IS GLOBAL
	_t = t * getTimeNormConstant();

	// SET TIME, CONTROLS, AND STATES
	set(t,xt,y);
	callSetCallbacks(t,xt,y);

	// ACTUATORS FORCES
	computeActuation(); 
	callComputeActuationCallbacks(t,xt,y);
	applyActuatorForces(); 
	callApplyActuationCallbacks(t,xt,y);

	// CONTACT FORCES
	computeContact();
	callComputeContactCallbacks(t,xt,y);
	applyContactForces();
	callApplyContactCallbacks(t,xt,y);

	// COMPUTE DERIVATIVES OF Q AND U
	computeAccelerations(&dy[0],&dy[getNQ()]);

	// COMPUTE DERIVATIVES OF ACTUATIONS
	int err=0;
	double param[1] = { -1.0 };
	calc_muscle_derivatives(_t,y,dy,param,&err);

	// SET DERIVATIVES
	int i;
	for(i=0;i<getNY();i++) 
		dy[i] = dy[i] * getTimeNormConstant();

	// CALL COMPUTE DERIVATIVES CALLBACKS
	callComputeDerivativesCallbacks(t,xt,y,dy);

	return(0);
}

//_____________________________________________________________________________
/**
 * Compute the derivatives of the states.
 *
 * @param t Current time in the simulation.
 * @param xt Controls.
 * @param y States.
 * @param dqdt Time derivatives of generalized coordinates in normalized time.
 * @param dudt Time derivatives of generalized speeds in normalized time.
 */
int suSIMMPipeline323::
deriv(double t, double *xt, double *y, double *dqdt, double *dudt)
{
	// SET CONFIGURATION
	set(t,xt,y);

	// ACTUATION
	computeActuation();
	applyActuatorForces(); 

	// CONTACT
	computeContact();
	applyContactForces();

	// DERIVATIVES OF GEN. COORDINATES AND SPEEDS
	computeAccelerations(dqdt,dudt); 

	return(0);
}

//=============================================================================
// CALLBACK : see rdActuatedModel_SDFast.cpp
//=============================================================================
//_____________________________________________________________________________
/**
 * Take care of any initializations needed before an integration.
 *
 * @param aStep Step number in the simulation.
 * @param aDT Size of the intended time step.
 * @param aT Current time in the simulation.
 * @param aX Controls.
 * @param aY States.
 * @param aClientData Void pointer so that the user can send in any
 * desired data.
 */
void suSIMMPipeline323::
integBeginCallback(int aStep, double aDT, double aT, double *aX, 
				   double *aY, void *aClientData) 
{
	// BEGIN ANAYSES
	int i,j;
	for(i=0;i<_nAnalyses;i++) {
		if(_analyses[i]==NULL) continue;
		j=_analyses[i]->begin(aStep,aDT,aT,aX,aY,aClientData);
	}
}


//_____________________________________________________________________________
/**
 * Perform calculations after ever integration time step.
 *
 * @param aXPrev Values of the controls at the beginning of the previous
 * integration step.
 * @param aYPrev Values of the states at the beginning of the previous
 * integration step.
 * @param aStep Step number in the simulation.
 * @param aDT Size of the time step that was just taken in the previous
 * integration time step.
 * @param aT Current time in the simulation.
 * @param aX Current controls.
 * @param aY Current states.
 * @param aClientData Void pointer so that the user can send in any
 * desired data.
 */
void suSIMMPipeline323::
integStepCallback(double *aXPrev,double *aYPrev, 
				  int aStep,double aDT,double aT,double *aX,double *aY, 
				  void *aClientData) 
{
	//PERFORM ANALYSES
	int i,j;
	for(i=0;i<_nAnalyses;i++) {
		if(_analyses[i]==NULL) continue;
		j=_analyses[i]->analyze(aXPrev,aYPrev,aStep,aDT,aT,aX,aY,aClientData);
	}
}

//_____________________________________________________________________________
/**
 * Perform actions after an integration has completed.
 *
 * @param aStep Step number in the simulation.
 * @param aDT Size of the intended time step.
 * @param aT Current time in the simulation.
 * @param aX Controls.
 * @param aY States.
 * @param aClientData Void pointer so that the user can send in any
 * desired data.
 */
void suSIMMPipeline323::
integEndCallback(int aStep, double aDT, double aT, double *aX, 
				 double *aY, void *aClientData) {
	// BEGIN ANAYSES
	int i,j;
	for(i=0;i<_nAnalyses;i++) {
		if(_analyses[i]==NULL) continue;
		j=_analyses[i]->end(aStep,aDT,aT,aX,aY,aClientData);
	}
}