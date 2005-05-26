// suPipeline40.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Authors:  Peter V. Ehrhart, Frank C. Anderson, Saryn R. Goldberg
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include <string>
#include <iostream>
#include <RD/Tools/rdMath.h>
#include <RD/Simulation/Model/rdDerivCallbackSet.h>
#include <RD/Simulation/Model/rdActuatorSet.h>
#include <RD/Simulation/Model/rdContactForceSet.h>
#include "suPipeline40.h"
#include "suPipeline40-helper.h"
#include <RD/Tools/suScale.h>
#include <RD/Tools/suScaleSet.h>

extern "C" {
#include "./dp/mathtools.h"
}

using namespace std;
//namespace su {

//=============================================================================
// CONSTANTS
//=============================================================================

//=============================================================================
// STATICS
//=============================================================================
static char UNKNOWN[] = "UNKNOWN";



//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR (and cleanup)
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
suPipeline40::~suPipeline40()
{ 
   try {
      cleanup();
   } 
	catch (...) { }
}

//_____________________________________________________________________________
/**
 * Cleanup.
 */
void suPipeline40::cleanup()
{
   delete _dpd; // dtor cleans
   DP_MainShutdown(); // cleans globals
}


//_____________________________________________________________________________
/**
 * Constructor.
 *
 * Although this class is derived from rdActuatedModel_SDFast, this class
 * currently only supports the muscles that are part of the SIMM Dynamics
 * Pipeline.  Future revisions will allow for additional actuaors that
 * will be added to the actutor set in rdActuatedModel_SDFast.
 *
 * @param aWorkpath Path of the working directory.
 * @param aParamfile SIMM parameters file.
 * @param aContacts Set of contact force objects for a simulation.
 */
suPipeline40::suPipeline40(const string &workpath, const string &paramfile, 
   rdActuatorSet *aActuators,rdContactForceSet *aContacts,
	bool performInitialization) :
	rdActuatedModel_SDFast(aActuators,aContacts),_yi(0.0),_dpd(new DP_Data)
{
	setNull();

	if (performInitialization)
		initPipeline(workpath, paramfile);
}
/*
 * Virtualize and factor out initialization code so that it can be overridden 
 *
 * @param aWorkpath Path of the working directory.
 * @param aParamfile SIMM parameters file.
 */
void suPipeline40::
initPipeline(const string &workpath, const string &paramfile)
{
	// PIPELINE INITIALIZATION
	try {
      string path = workpath + '/';
      string file = paramfile;

		cout<<"\n\nStartup file = "<<file<<endl<<endl;
      DP_MainStartup(_dpd,path.c_str(),file.c_str() ); // populate globals and dpd_

	// ERROR - SHOULD EXIT
   } catch (...) {

		cout<<"\n\nThe SIMM Dynamics Pipeline did not initialize properly.";
		cout<<endl<<endl;
      cleanup();

		string msg = "Pipeline initialization failure.";
		throw rdException(msg,__FILE__,__LINE__);
   }  
	
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
 * Set all member variables to their NULL values.
 */
void suPipeline40::
setNull()
{
	_includePipelineActuators = true;
}
//_____________________________________________________________________________
/**
 * Construct the valid initial states.
 */
void suPipeline40::
constructInitialStates()
{
	// NUMBERS
	int i;
	int ny = getNY();
	int nqnu = getNQ() + getNU();
	int nyAct = rdActuatedModel_SDFast::getNY() - nqnu;
	int nyDP = sdm->neq - nqnu;
	cout<<"suPipeline40.constructInitialStates:  ny="<<ny;
	cout<<" nyAct="<<nyAct<<" nyDP="<<nyDP<<endl;

	// INITIALIZE
	_yi.setSize(ny);
	rdActuatedModel_SDFast::getInitialStates(&_yi[0]);
	// q and u
	for(i=0;i<nqnu;i++) {
		_yi[i] = _dpd->y[i];
	}
	// pipeline muscle states
	for(i=0;i<nyDP;i++) {
		_yi[nqnu + nyAct + i] = _dpd->y[nqnu + i];
	}
}

//_____________________________________________________________________________
/**
 * Construct the names of the various components of the model.
 */
void suPipeline40::
constructNames()
{
	printf("suPipeline40.constructControlNames: \n");

	// NAME
	setName("suPipeline40");
	
	// BODIES
	printf("suPipeline40.constructNames: nb = %d\n",getNB());
	int i;
	for(i=0;i<getNB();i++) {	// Use i+1 since SIMM has a segment for ground but RDI does not! -Ayman 11/04
		setBodyName(i,sdm->body_segment[i+1].name);
	}

	// GENERALIZED COORDINATES
	printf("suPipeline40.constructNames: nq = %d\n",getNQ());
	for(i=0;i<getNQ();i++) {
		setCoordinateName(i,sdm->q[i].name);
	}

	// GENERALIZED SPEEDS
	printf("suPipeline40.constructNames: nu = %d\n",getNU());
	char name[100];
	for(i=0;i<getNU();i++) {
		sprintf(name, "%s",sdm->q[i].name);
		setSpeedName(i,name);
	}
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
void suPipeline40::
setConfiguration(const double aQ[],const double aU[])
{
	int i;
	for(i=0;i<getNQ();i++)
		_dpd->y[i] = aQ[i];
	for(i=0;i<getNU();i++)
		_dpd->y[i+getNQ()] = aU[i];

	rdActuatedModel_SDFast::setConfiguration(aQ,aU);
}
//_____________________________________________________________________________
/**
 * Set the configuration of the model.
 *
 * @param aY Statevector.
 */
void suPipeline40::
setConfiguration(const double aY[])
{
	rdActuatedModel_SDFast::setConfiguration(aY);	
	int i, iAct = getNQ() + getNU();
	for(i=0;i<iAct;i++){	// This seems redundant, already done by setConfiguration
		_dpd->y[i] = aY[i];
	}
}

//-----------------------------------------------------------------------------
// NUMBERS OF THINGS 
//=============================================================================
//_____________________________________________________________________________
/**
 * Get the number of controls for this model.
 *
 */
int suPipeline40::
getNX() const
{
	int nx = rdActuatedModel_SDFast::getNX();
	if(getIncludePipelineActuators()) nx += sdm->num_muscles;
	return(nx);
}

//_____________________________________________________________________________
/**
 * Get the number of actuators for this model.
 *
 */
int suPipeline40::
getNA() const
{
	int na = rdActuatedModel_SDFast::getNA();
	if(getIncludePipelineActuators()) na += sdm->num_muscles;
	return(na);
}

//_____________________________________________________________________________
/**
 * Get the number of states for this model.
 *
 */
int suPipeline40::
getNY() const
{
	int ny = rdActuatedModel_SDFast::getNY();
	if(getIncludePipelineActuators()) {
		int nMuscleStates = sdm->neq - getNQ() - getNU();
		ny += nMuscleStates;
	}

	return(ny);
}


//-----------------------------------------------------------------------------
// NAMES
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the name of a control.
 *
 * @param aIndex Index of the control whose name is desired.  aIndex should
 * be greater than or equal to 0 and less than the number of controls.
 * @return Control name.
 * @see getNX()
 */
string suPipeline40::
getControlName(int aIndex) const
{
	string name = "";

	// BASE CLASS
	int nxBase = rdActuatedModel_SDFast::getNX();
	if(aIndex<nxBase) {
		name = rdActuatedModel_SDFast::getControlName(aIndex);

	// SIMM
	} else if(getIncludePipelineActuators()) {
		int index = aIndex - nxBase;
		name = sdm->muscles[index].name;
		name += ".excitation";
	}

	return(name);
}
//_____________________________________________________________________________
/**
 * Get the name of an actuator.
 *
 * @param aIndex Index of the actuator whose name is desired.  aIndex should
 * be greater than or equal to 0 and less than the number of actuators.
 * @return Control name.
 * @see getNA()
 */
string suPipeline40::
getActuatorName(int aIndex) const
{
	string name = "";

	// BASE CLASS
	int naBase = rdActuatedModel_SDFast::getNA();
	if(aIndex<naBase) {
		name = rdActuatedModel_SDFast::getActuatorName(aIndex);

	// SIMM
	} else if(getIncludePipelineActuators()) {
		int index = aIndex - naBase;
		name = sdm->muscles[index].name;
	}

	return(name);
}
//_____________________________________________________________________________
/**
 * Get the name of a state.
 *
 * @param aIndex Index of the state whose name is desired.  aIndex should
 * be greater than or equal to 0 and less than the number of states.
 * @return State name.  If aIndex is not valid an empty string "" is returned.
 *
 * @todo As written this code assumes that all of the muscles in the model are
 * using the same muscle model and have the same number of states.
 */
string suPipeline40::
getStateName(int aIndex) const
{
	string name = "";

	// BASE
	int nyBase = rdActuatedModel_SDFast::getNY();
	if(aIndex<nyBase){
		name = rdActuatedModel_SDFast::getStateName(aIndex);

	// DYNAMICS PIPELINE
	} else if(getIncludePipelineActuators()) {
		int nyPipeline = getNY() - nyBase;
		if(nyPipeline<=0) return(name);
		int naPipeline = getNA() - rdActuatedModel_SDFast::getNA();
		if(naPipeline<=0) return(name);
		int nyPerMuscle = nyPipeline / naPipeline; // States per muscle
		int muscle = (aIndex - nyBase) / nyPerMuscle;
		int state = (aIndex - nyBase) % nyPerMuscle;

		// At least allocate space for strState to handle 22 digits!
		char strState[128];
		sprintf(strState,"state_%d",state);

		name = sdm->muscles[muscle].name;
		name += ".";
		name += strState;
	}

	return(name);
}

//-----------------------------------------------------------------------------
// INDICES
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the index of an actuator given its name.
 *
 * Note that the actuator names need to be unique for this method
 * to work properly.
 *
 * @param aName Name of an actuator.
 * @return Index of the first actuator with the name aName; -1, if there is no
 * such actuator or if there is an error.
 */
int suPipeline40::
getActuatorIndex(const string &aName) const
{
	int i;
	for(i=0;i<getNA();i++) {
		if(aName == getActuatorName(i)) 
			return(i);
	}
	return(-1);
}
//_____________________________________________________________________________
/**
 * Get the index of a control given its name.
 * The returned indices start at 0: for the first, 0 is returned; for
 * the second, 1; etc.
 *
 * Note that the control names need to be unique for this method
 * to work properly.
 *
 * @param aName Name of a control.
 * @return Index of the first control with the name aName; -1, if there is no
 * such control or if there is an error.  Indicies start at 0.
 */
int suPipeline40::
getControlIndex(const string &aName) const
{
	int i;
	for(i=0;i<getNA();i++) {
		if(aName == getControlName(i)) 
			return(i);
	}
	return(-1);
}
//_____________________________________________________________________________
/**
 * Get the index of a state given its name.
 * The returned indices start at 0: for the first, 0 is returned; for
 * the second, 1; etc.
 *
 * Note that the state names need to be unique for this method
 * to work properly.
 *
 * @param aName Name of a state.
 * @return Index of the first state with the name aName; -1, if there is no
 * such state or if there is an error.  Indices start at 0.
 */
int suPipeline40::
getStateIndex(const string &aName) const
{
	int i;
	for(i=0;i<getNY();i++) {
		if(aName==getStateName(i)) 
			return(i);
	}
	return(-1);
}

//-----------------------------------------------------------------------------
// CONTROLS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the value of a control by index.
 *
 * @param aIndex Index of the control to be set:  0 <= aIndex < getNX().
 * @param aValue Value of the control.
 */
void suPipeline40::
setControl(int aIndex,double aValue)
{
	int nxBase = rdActuatedModel_SDFast::getNX();
	if(aIndex<nxBase) {
		rdActuatedModel_SDFast::setControl(aIndex,aValue);
	} else if(getIncludePipelineActuators()) {
		int index = aIndex - nxBase;
		sdm->muscles[index].excitation_level = aValue;
	}
}
//_____________________________________________________________________________
/**
 * Set the value of a control by name.
 * Note that this method is slow and should not be used in code where it
 * might be called repeatedly.
 *
 * @param aName Name of the control to be set.
 * @param aValue Value of the control.
 */
void suPipeline40::
setControl(const string &aName,double aValue)
{
	int index;
	index = getControlIndex(aName);
	setControl(index,aValue);
}
//_____________________________________________________________________________
/**
 * Get the current value of a control by index.
 *
 * @param aIndex Index of the control:  0 <= aIndex < getNX().
 * @return Value of the control.  rdMath::NAN is returned on an error.
 */
double suPipeline40::
getControl(int aIndex) const
{
	double value = rdMath::NAN;

	int nxBase = rdActuatedModel_SDFast::getNX();
	if(aIndex<nxBase) {
		value = rdActuatedModel_SDFast::getControl(aIndex);
	} else if(getIncludePipelineActuators()) {
		int index = aIndex - nxBase;
		value = sdm->muscles[index].excitation_level;
	}

	return(value);
}
//_____________________________________________________________________________
/**
 * Get the value of a control by name.
 * Note that this method is slow and should not be used in code where
 * it might be called repeatedly.
 *
 * @param aName Name of the control.
 * @return Value of the control.  rdMath::NAN is returned on an error.
 * @see getControls(double rX[])
 * @see getControl(int aIndex);
 */
double suPipeline40::
getControl(const std::string &aName) const
{
	int index = getControlIndex(aName);
	double value = getControl(index);	
	return(value);
}

//_____________________________________________________________________________
/**
 * Set the current controls for the model.
 *
 * The controls must be set for the model and the actuators.
 *
 * @param aX Array of controls.  The size of aX should be the value returned
 * by getNX().
 * @see rdActuatedModel_SDFast::setControls();
 */
void suPipeline40::
setControls(const double aX[])
{
	int i;
	for(i=0;i<getNA();i++) {
		setControl(i,aX[i]);
	}
}
//_____________________________________________________________________________
/**
 * Get the current controls for the model.
 *
 * The controls must be set for the model and the actuators.
 *
 * @param rX Array of controls.  The size of aX should be the value returned
 * by getNX().
 * @see rdActuatedModel_SDFast::setControls();
 */
void suPipeline40::
getControls(double rX[]) const
{
	int i;
	for(i=0;i<getNA();i++) rX[i] = getControl(i);
}

//-----------------------------------------------------------------------------
// INITIAL STATES
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the initial states for this model.
 *
 * This method sets the configuration (coordinates and speeds) of the model
 * and also the initial states of the actuators.
 *
 * @param aY Array of states. The size of aY should be the value returned by
 * getNY().
 */
void suPipeline40::
setInitialStates(const double aY[])
{
	// BASE
	rdActuatedModel_SDFast::setInitialStates(aY);

	// LOCAL
	int i,ny=suPipeline40::getNY();
	for(i=0;i<ny;i++) {
		_yi[i] = aY[i];
	}
}

//_____________________________________________________________________________
/**
 * Get the current states.
 *
 * @param aY Array of states.  The size of aYP should be the value
 * returned by getNY().
 * @see rdActuatedModel_SDFast::setStates();
 */
void suPipeline40::
getInitialStates(double rY[]) const
{
	int i,ny=suPipeline40::getNY();
	for(i=0;i<ny;i++) {
		rY[i] = _yi[i];
	}

}
//_____________________________________________________________________________
/**
 * Get the a state by index.
 *
 * @param aIndex  Array index of the desired state.
 * @return Value of the state.  On an error, rdMath::NAN is returned.
 */
double suPipeline40::
getInitialState(int aIndex) const
{
	return(_yi[aIndex]);
}

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
void suPipeline40::
setStates(const double aY[])
{
	// LOCAL ARRAY
	int i;
	int nunq = getNQ()+getNU();
	int iDP = rdActuatedModel_SDFast::getNY();
	// q and u
	for(i=0;i<nunq;i++)  _dpd->y[i] = aY[i];
	// pipeline actuator states
	int na = suPipeline40::getNY() - rdActuatedModel_SDFast::getNY();
	for(i=0;i<na;i++) {
		_dpd->y[i+nunq] = aY[iDP+i];
	}

	// PRINT
	//for(i=0;i<suPipeline40::getNY();i++) {
	//	cout<<"suPipeline40.setStates: y["<<i<<"]= "<<aY[i]<<endl;
	//}

	// BASE
	rdActuatedModel_SDFast::setStates(aY);

	// PIPELINE
	assign_muscle_states(sdm,_t,_dpd->y);
}

//_____________________________________________________________________________
/**
 * Get the current states.
 *
 * @param aY Array of states.  The size of aYP should be the value
 * returned by getNY().
 * @see rdActuatedModel_SDFast::setStates();
 */
void suPipeline40::
getStates(double rY[]) const
{

	// BASE
	rdActuatedModel_SDFast::getStates(rY);

	// LOCAL
	int i;
	int nyBase = rdActuatedModel_SDFast::getNY();
	int nqnu = getNQ() + getNU();
	int n = sdm->neq - nqnu;
	for(i=0;i<n;i++) {
		rY[nyBase+i] = _dpd->y[nqnu+i];
	}

}
//_____________________________________________________________________________
/**
 * Get the a state by index.
 *
 * @param aIndex  Array index of the desired state.
 * @return Value of the state.  On an error, rdMath::NAN is returned.
 */
double suPipeline40::
getState(int aIndex) const
{
	int ny = rdActuatedModel_SDFast::getNY();
	if(aIndex< ny){
		return rdActuatedModel_SDFast::getState(aIndex);
	} else {
		int state = aIndex - ny + getNQ() + getNU();
		return( _dpd->y[state]);
	}
}


//=============================================================================
// ACTUATION 
//=============================================================================
//_____________________________________________________________________________
/**
 * Set whether or not to include the SIMM pipeline actuators.
 *
 * @param aTrueFalse  Specifies to use pipeline actuators is true; specifies
 * not to use pipeline actuators if false.
 */
void suPipeline40::
setIncludePipelineActuators(bool aTrueFalse)
{
	_includePipelineActuators = aTrueFalse;
}
//_____________________________________________________________________________
/**
 * Get whether or not to include the SIMM pipeline actuators.
 *
 * @return True if pipeline actuators are included in a simulation, false
 * otherwise.
 */
bool suPipeline40::
getIncludePipelineActuators() const
{
	return(_includePipelineActuators);
}

//_____________________________________________________________________________
/**
 * Compute all quatities associated with actuation of the model.
 *
 * This method assumes that the configuration of the model has already
 * been set.
 *
 */
void suPipeline40::
computeActuation()
{
	rdActuatedModel_SDFast::computeActuation();

	if(getIncludePipelineActuators()) {

		// SET EXCITATION LEVELS
		int i,j;
		int err=0;
		double param[1] = { -1.0 };
		int nx = getNX();
		int nxBase = rdActuatedModel_SDFast::getNX();
		for (i=0,j=nxBase;j<nx;i++,j++) {
			sdm->muscles[i].excitation_level = getControl(j);
		}

		// NEW DGT - Compute the current muscle-tendon lengths and velocities a priori
		// since these are not computed in the derivs function used in cmc
		for (i=0;i<sdm->num_muscles;i++) {
			check_wrapping_points(&sdm->muscles[i],_dpd->y);
			calc_muscle_tendon_length(&sdm->muscles[i]);
			calc_muscle_tendon_velocity(&sdm->muscles[i]);
		}

		calc_muscle_derivatives(_t,_dpd->y,_dpd->dy,param, &err);
	}
}
//_____________________________________________________________________________
/**
 * Apply a particular actuator force to the model.
 *
 * @param aID The index of the actuator force to apply.
 * @todo Changed function calls from SDFast to RDI and made formatting comply
 * with RDI.  Check that the same results are obtained.
 */
void suPipeline40::
applyActuatorForce(int aID)
{
	int na = rdActuatedModel_SDFast::getNA();

	// RD
	if(aID<na) {
		rdActuatedModel_SDFast::applyActuatorForce(aID);

	// Pipeline
	} else {


		int iDP = aID - na;
		int k, sdbody1, sdbody2, start, end;
		double force_vector[3], norm_force_vector[3], body_force_vector[3];
		double inertial_pt1[3], inertial_pt2[3];
		double aForce=sdm->muscles[iDP].force;
		dpMuscleStruct *ms = &sdm->muscles[iDP];
		
		for(start = 0; start < ms->num_points - 1; start++) {
			
			end = start + 1;

			sdbody1 = ms->mp[start]->segment;
			sdbody2 = ms->mp[end]->segment;

			if (sdbody1 != sdbody2) {
				getPosition(sdbody1, ms->mp[start]->point, inertial_pt1);
				getPosition(sdbody2, ms->mp[end]->point, inertial_pt2);

				for (k=0; k<3; k++)
					force_vector[k] = inertial_pt2[k] - inertial_pt1[k];

				normalize_vector(force_vector, norm_force_vector);

				for (k = 0; k < 3; k++)
					body_force_vector[k] *= aForce;
				
				applyForce(sdbody1, ms->mp[start]->point, body_force_vector);

				for (k=0; k<3; k++)
						  body_force_vector[k] *= -aForce;
				applyForce(sdbody2,ms->mp[end]->point,body_force_vector);
			}
		}
	}
}
//_____________________________________________________________________________
/**
 * Apply all actuator forces to the model. Actuator forces include
 * muscle forces and ligament torques.
 */
void suPipeline40::
applyActuatorForces()
{
	// Set fixed and prescribed generalized forces 
	sdumotion(_t,&_dpd->y[0],&_dpd->y[getNQ()]);

	// RD Actuators
	rdActuatedModel_SDFast::applyActuatorForces();

	// Apply pipeline related forces
	if(getIncludePipelineActuators()) {
		sduforce(_t,&_dpd->y[0],&_dpd->y[getNQ()]);
	}
}
//_____________________________________________________________________________
/**
 * Set a force at a particular actuator with param aI 
 * the index of the actuator force to apply.
 */
void suPipeline40::
setActuatorForce(int aID,double aForce)
{
	int na = rdActuatedModel_SDFast::getNA();
	if(aID<na) {
		rdActuatedModel_SDFast::setActuatorForce(aID,aForce);
	} else {
		int iDP = aID - na;
		sdm->muscles[iDP].force = aForce;
	}

  // sdm->muscles[aID].force = aForce;
}
//_____________________________________________________________________________
/**
 * Get a force at a particular actuator with param aI 
 * the index of the actuator force to apply.
 */
double suPipeline40::
getActuatorForce(int aID) const
{
	int na = rdActuatedModel_SDFast::getNA();

	double force;

	// RD
	if(aID<na) {
		force = rdActuatedModel_SDFast::getActuatorForce(aID);

	// Pipeline
	} else {
		int iDP = aID - na;
		force = sdm->muscles[iDP].force;
	}

	return(force);
   //return(sdm->muscles[aID].force);
}
//_____________________________________________________________________________
/**
 * Get the stress in a particular actuator.
 */
//double suPipeline40::
//getActuatorStress(int aID) const
//{
//
//}
//_____________________________________________________________________________
/**
 * Get the speed at which a particular actuator force is applied.
 */
double suPipeline40::
getActuatorSpeed(int aID) const
{
 	int na = rdActuatedModel_SDFast::getNA();

	double speed;

	// RD
	if(aID<na) {
		speed = rdActuatedModel_SDFast::getActuatorSpeed(aID);

	// Pipeline
	} else {
		int iDP = aID - na;
		speed = sdm->muscles[iDP].muscle_tendon_vel;
	}

	return(speed);
   //return( sdm->muscles[aID].muscle_tendon_vel );
}

//_____________________________________________________________________________
/**
 * Get the power appled to body segments by a particular actuator.
 */
double suPipeline40::
getActuatorPower(int aID) const 
{
 	int na = rdActuatedModel_SDFast::getNA();

	double power;

	// RD
	if(aID<na) {
		power = rdActuatedModel_SDFast::getActuatorPower(aID);

	// Pipeline
	} else {
		int iDP = aID - na;
		power = sdm->muscles[iDP].applied_power;
	}

	return(power);
   //return( sdm->muscles[aID].applied_power );
}
//_____________________________________________________________________________
/**
 * Scale the model using a set of scale factors.
 * Parallels Darryl Thelen's implementation. Does not handle constraint objects, 
 * wrap objects or deform objects as these are not available to the pipeline model.
 * 
 * The code below is very SDFast specific and needs to be replaced by calls
 * to generic rdModel APIs to make it more general, however it's questionable
 * if other dynamics engines would have similar APIs to assemble/set axes, ...
 *
 * Leaving it sdfast specific for now until new DynamicsInterface is defined.
 * Also we have to deal with redundant representation where mass, inertia and center
 * of mass are stored in the sdm structure as well as the rdBody objects. The sdm guy
 * seems more relevent as it could be used by the rest of the pipeline code and as such
 * this's what gets scaled here. 
 */
bool   suPipeline40::
scale(const suScaleSet& aScaleSet)
{
	int i, j, k;
	int info[50], slider[6], inbody, outbody, segment;
	double itj[3], btj[3], segment_mass, inertia[3][3], pin[3], scale;
	double *y;
	dpMuscleStruct* ms;
	dpBodyStruct* seg;

	// Allocate and initialize arrays to be used by the scaling
	double*	muscle_length_scales = new double[sdm->num_muscles];
	for (i=0; i < sdm->num_muscles; i++) 
		muscle_length_scales[i] = 1.0;

	double	(*segment_scales)[3] = new double[sdm->num_body_segments][3];
	for (i=0; i < sdm->num_body_segments; i++){
		segment_scales[i][0]=segment_scales[i][1]=segment_scales[i][2]=1.0;
	}

	double *nominal_muscle_tendon_lengths = new double[sdm->num_muscles];
	for (i=0; i < sdm->num_muscles; i++) 
		nominal_muscle_tendon_lengths[i] = 0.0;

	// Map ScaleSet to an array of segment_scales that's based on index in sdm datastructure
	for(i=0; i < aScaleSet.getSize(); i++){
		// Scale factors
		suScale *aScale = aScaleSet.get(i);
		rdArray<double>	scaleFactors(1.0, 3);
		aScale->getScaleFactors(scaleFactors);
		// get name of segment and map it to an index
		const string& segName = aScale->getSegmentName();
		// We need to get the index from sdm->body_segment since we're using sdm 
		// or we can get index from rdBodySet and offset by 1 to account for ground 
		// not being a body.
		int segmentIndex = getBodySet()->getIndex(segName);
		for(j=0; j <3; j++)
			segment_scales[segmentIndex+1][j] = scaleFactors[j];
	}

	// Compute muscle-tendon lengths in an upright posture
	y = new double[sdm->neq];
	for (i=0;i<sdm->nq;i++)
		y[i]=y[i+sdm->nq]=0.;
	assemble_model(0.0, y);
	sdstate(0.,y,&y[sdm->nq]);
	for (i=0;i<sdm->num_muscles;i++)
		check_wrapping_points(&sdm->muscles[i],y);
	sdstate(0.,y,&y[sdm->nq]);
	for (i=0;i<sdm->num_muscles;i++)
		nominal_muscle_tendon_lengths[i]=calc_muscle_tendon_length(&sdm->muscles[i]);
	
	// Scale bodies and joints
	rdSDFast::scale(aScaleSet);

	// Scale the body segment inertial parameters and mass center using segment scaling factors
	// This must be done after the call to rdSDFast::scale as it assumes that mass, inertia 
	// and center of mass have been scaled already by rdSDFast::scale. The code below just synchronizes
	// SDFast and the sdm datastructure used by the pipeline to match the already scaled model.
	// I didn't make move sdfast calls to rdBody to have it Dynamics package agnostic.
	for (i=1;i<sdm->num_body_segments;i++) {
		seg=&sdm->body_segment[i];
		// Set mass in SDFast
		segment_mass=getBodySet()->get(i-1)->getMass();
		sdmass(i-1,segment_mass);
		// set mass in sdm
		sdm->body_segment[i].mass = segment_mass;
		// Set inertia in SDFast
		getBodySet()->get(i-1)->getInertia(inertia);
		sdiner(i-1, inertia);
		// set inertia in sdm
		for (j=0;j<3;j++) {
			for (k=0;k<3;k++) {
				sdm->body_segment[i].inertia[j][k] = inertia[j][k];
			}
		}
		double com[3];
		getBodySet()->get(i-1)->getCenterOfMass(com);
		for (j=0;j<3;j++)
			sdm->body_segment[i].mass_center[j] =com[j];

	}

	// Scale the muscle origin, insertion and via points using the segment scaling factors
	for (i=0;i<sdm->num_muscles;i++) {
		ms=&sdm->muscles[i];
		for (j=0;j<(*ms->num_orig_points);j++) {
			segment=ms->mp_orig[j].segment;
			for (k=0;k<3;k++) {
				ms->mp_orig[j].point[k]=ms->mp_orig[j].point[k]*segment_scales[segment+1][k];
			}
		}
	}

	// Scale the conversion factors for the constrained q's, this scales the corresponding constraint functions
	for (i=0;i<sdm->nq;i++) {
		if (sdm->q[i].type==dpConstrainedQ) {
				sdjnt(sdm->q[i].joint,info,slider);
				if (slider[sdm->q[i].axis]==1) {
					// Then this is a translation joint and needs to be scaled
					inbody=info[2];
					sdgetpin(sdm->q[i].joint,sdm->q[i].axis,pin);
					scale=(pin[0]*segment_scales[inbody+1][0]+
 						   pin[1]*segment_scales[inbody+1][1]+
						   pin[2]*segment_scales[inbody+1][2]);
					sdm->q[i].conversion = sdm->q[i].conversion/scale;	
				}
		}
	}

	sdinit();

	// Now compute the upright muscle-tendon lengths in an upright posture of the scaled model
	// and scale the fiber and tendon slack lengths accordingly
	assemble_model(0., y);
	sdstate(0.,y,&y[sdm->nq]);
	for (i=0;i<sdm->num_muscles;i++) {
		ms=&sdm->muscles[i];
		muscle_length_scales[i]= calc_muscle_tendon_length(ms)/nominal_muscle_tendon_lengths[i];
		*ms->optimal_fiber_length= muscle_length_scales[i]*(*ms->optimal_fiber_length);
		*ms->resting_tendon_length= muscle_length_scales[i]*(*ms->resting_tendon_length);
	}
	delete[] y;
	delete[] muscle_length_scales;
	delete[] segment_scales;
	delete[] nominal_muscle_tendon_lengths;
	return true;
}

//=============================================================================
// CONTACT
//=============================================================================
//-----------------------------------------------------------------------------
// COMPUTE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Compute all quantities associated with simulating contact between bodies.
 * These quantities include at least the contact bodies, contact points, and
 * contact forces.
 *
 * @see getNP()
 */
void suPipeline40::
computeContact()
{
	_contactSet.computeContact();
}
//-----------------------------------------------------------------------------
// APPLY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Apply a contacted force.
 *
 * For the correct contact forces to be applied correctly, computeContact()
 * must be called prior to calling this method.
 */
void suPipeline40::
applyContactForce(int aID)
{
	rdActuator *contact = _contactSet.get(aID);
	if(contact!=NULL) contact->apply();
}
//_____________________________________________________________________________
/**
 * Apply the computed contacted forces.
 *
 * For the correct contact forces to be applied correctly, computeContact()
 * must be called prior to calling this method.
 */
void suPipeline40::
applyContactForces()
{
	_contactSet.apply();
	if(getIncludePipelineActuators()) {

	}
}


//=============================================================================
// DERIVATIVES
//=============================================================================
//_____________________________________________________________________________
/**
 * Compute the derivatives of the states.
 */
int suPipeline40::
deriv(double t,double *xt,double *y,double *dy)
{
	int i,j;

	// TIME, CONTROLS, STATES
	set(t,xt,y);
	_derivCallbackSet->set(t,xt,y);

	// ACTUATION
	computeActuation();
	_derivCallbackSet->computeActuation(t,xt,y);
	applyActuatorForces();
	_derivCallbackSet->applyActuation(t,xt,y);

	// CONTACT
	computeContact();
	_derivCallbackSet->computeContact(t,xt,y);
	applyContactForces();
	_derivCallbackSet->applyContact(t,xt,y);

	// DERIVATIVES
	computeAccelerations(&dy[0],&dy[getNQ()]);
	// ActuatorSet
	int iAct = getNQ()+getNU();
	_actuatorSet.computeStateDerivatives(&dy[iAct]);
	// Pipeline Muscles 
	if(getIncludePipelineActuators()) {
		int err=0;
		double param[1] = { -1.0 };
		int nq = getNQ();
		int nu = getNU();
		int nqnu = nq + nu;
		int ny = suPipeline40::getNY();
		int nyBase = rdActuatedModel_SDFast::getNY();
		calc_muscle_derivatives(t,_dpd->y,_dpd->dy,param,&err);
		for(i=nyBase,j=nqnu;i<ny;i++,j++) dy[i] = _dpd->dy[j];
	}
	// Normalize
	double timeNormConst = getTimeNormConstant();
	for(i=0;i<getNY();i++) {
		dy[i] = dy[i] * timeNormConst;
	}
	_derivCallbackSet->computeDerivatives(t,xt,y,dy);

	return(0);
}




//} // namespace
