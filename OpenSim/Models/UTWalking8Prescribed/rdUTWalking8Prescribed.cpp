// rdUTWalking8Prescribed.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// AUTHOR: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include <string>
#include <math.h>
#include <OpenSim/Common/rdMath.h>
#include <OpenSim/Common/Mtx.h>
#include <OpenSim/Common/Memory.h>
#include <OpenSim/Actuators/Springs.h>
#include <OpenSim/Simulation/Model/Analysis.h>
#include <OpenSim/Simulation/Model/IntegCallbackSet.h>
#include <OpenSim/Simulation/Model/DerivCallbackSet.h>
#include <OpenSim/Simulation/SDFast/sdfast.h>
#include "rdUTWalking8Prescribed.h"
#include "rdUTWalkingPrescribedIntegCallback.h"
#include "utwalking.h"




using namespace OpenSim;
using namespace std;


//=============================================================================
// PLATFORM DEFINITIONS
//=============================================================================
#ifndef UNIX

#define intl23_ INTL23
#define sdinit_ SDINIT
#define sdinfo_ SDINFO
#define setmuson_ SETMUSON
#define setfom_ SETFOM
#define getfom_ GETFOM
#define mmfdot_ MMFDOT
#define mmatvdot_ MMATVDOT
#define musfrc_ MUSFRC
#define force23_ FORCE23
#define getactuatorlengths_ GETACTUATORLENGTHS
#define getactuatorvelocities_ GETACTUATORVELOCITIES

#endif


//=============================================================================
// CONSTANTS
//=============================================================================

// NUMBERS OF THINGS
const int rdUTWalking8Prescribed::NQ = rdUTWalking8Prescribed_NQ;
const int rdUTWalking8Prescribed::NU = rdUTWalking8Prescribed_NU;
const int rdUTWalking8Prescribed::NB = rdUTWalking8Prescribed_NB;
const int rdUTWalking8Prescribed::NJ = rdUTWalking8Prescribed_NJ;
const int rdUTWalking8Prescribed::NX = rdUTWalking8Prescribed_NX;
const int rdUTWalking8Prescribed::NA = rdUTWalking8Prescribed_NA;   
const int rdUTWalking8Prescribed::NY = rdUTWalking8Prescribed_NY;
const int rdUTWalking8Prescribed::NYP = rdUTWalking8Prescribed_NYP;
const int rdUTWalking8Prescribed::NN = rdUTWalking8Prescribed_NN;
const int rdUTWalking8Prescribed::NS = rdUTWalking8Prescribed_NS;
const int rdUTWalking8Prescribed::NI = NY - (NQ+NU+NX+NX);
const int rdUTWalking8Prescribed::IMSF = NQ+NU;
const int rdUTWalking8Prescribed::IATV = NQ+NU+NX;
const int rdUTWalking8Prescribed::IINT = NQ+NU+NX+NX;

// FOOT-GROUND SPRINGS
const double rdUTWalking8Prescribed::MU = 0.7;
const double rdUTWalking8Prescribed::SKV = 1.0e3;
//OVER DAMPED const double rdUTWalking8Prescribed::SKV = 1.0e4;
const double rdUTWalking8Prescribed::SKP = 6.9e4;
const double rdUTWalking8Prescribed::E0 =  6.5905e-3;
const double rdUTWalking8Prescribed::E1 =  0.5336322;
const double rdUTWalking8Prescribed::E2 = -1150.8002;
const double rdUTWalking8Prescribed::G0 =  0.02;
const double rdUTWalking8Prescribed::G1 =  10.0;
const double rdUTWalking8Prescribed::G2 =  500.0;

// LIGAMENTS
const int rdUTWalking8Prescribed::LIGU[] = { 6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22 };
const int rdUTWalking8Prescribed::LIGJOINT[] = { 2,2,2,3,3,3,4,5,5,6,7,7,7,8,9,9,10 };
const int rdUTWalking8Prescribed::LIGAXIS[] = { 1,2,3,1,2,3,1,1,2,1,1,2,3,1,1,2,1 };

// LIGAMENT TORQUES
const double rdUTWalking8Prescribed::k0lig[] = {
	0.1390577,0.0,0.0,
	0.0,0.0,0.0,0.0,
	0.49257884,0.0,-0.05,
	0.0,0.0,0.0,0.0,
	0.49257884,0.0,-0.05 };
const double rdUTWalking8Prescribed::theta1[] = {
	0.03,0.17,0.17,
	1.81,0.50,0.92,0.13,
	0.2618,0.65,0.21,
	1.81,0.50,0.92,0.13,
	0.2618,0.65,0.21 };
const double rdUTWalking8Prescribed::k1lig1[] = {
	-0.35,-0.25,-0.25,
	-2.44,-0.03, -0.03,-6.09,
	-4.0,-60.21,-0.9,
	-2.44,-0.03, -0.03,-6.09,
	-4.0,-60.21,-0.9 };
const double rdUTWalking8Prescribed::k2lig1[] = {
	30.72,20.36,20.36,
	5.05,14.94,14.94,33.94,
	8.0,16.32,14.87,
	5.05,14.94,14.94,33.94,
	8.0,16.32,14.87 };
const double rdUTWalking8Prescribed::theta2[] = {
	-0.35,-0.17,-0.17,
	-0.47,-0.50,-0.92,-2.40,
	-0.4712,-0.65,-0.02,
	-0.47,-0.50,-0.92,-2.40,
	-0.4712,-0.65,-0.02 };
const double rdUTWalking8Prescribed::k1lig2[] = {
	0.25,0.25,0.25,
	1.51,0.03, 0.03,11.03,
	1.0,60.21,0.18,
	1.51,0.03, 0.03,11.03,
	1.0,60.21,0.18 };
const double rdUTWalking8Prescribed::k2lig2[] = {
	-20.36,-20.36,-20.36,
	-21.88,-14.94,-14.94,-11.33,
	-22.0,-16.32,-70.08, 
	-21.88,-14.94,-14.94,-11.33,
	-22.0,-16.32,-70.08 };

// FOOT-GROUND SPRINGS
// FORTRAN int rdUTWalking8Prescribed::SBODY[] = { 5,5,5,5,6,9,9,9,9,10 };
//C const int rdUTWalking8Prescribed::SBODY[] = { 4,4,4,4,5,8,8,8,8,9 };
const int rdUTWalking8Prescribed::SBODY[] = { 4,4,4,4,5,8,8,8,8,9 };
const double rdUTWalking8Prescribed::SBODYPNT[][3] = {
	-0.071650,-0.038653,-0.050428,
	-0.091740,-0.038653,0.023202,
	 0.123629,-0.038653,-0.029196,
	 0.070755,-0.038653,0.069117,
	 0.050769,-0.018500,0.003468,
	-0.071650,-0.038653,0.050428,
	-0.091740,-0.038653,-0.023202,
	 0.123629,-0.038653,0.029196,
	 0.070755,-0.038653,-0.069117,
	 0.050769,-0.018500,-0.003468 };

// NAMES
// CONTROLS
static char* xNames[] = {
	"RFDH","REDH","RDFIN","RDFEV","ROPFIN","ROPFEV",
	"RSOL","RGAS","RBFSH","RVAS","RRF","RHAMS","RGRA","RTFL","RSAR",
	"RGMAXL","RGMAXM","RGMEDA","RGMEDP","RADM","RADLB","RILPSO",
	"RPECT","RPIRI","RERCSPN","RINTOBL","REXTOBL",
	"LFDH","LEDH","LDFIN","LDFEV","LOPFIN","LOPFEV",
	"LSOL","LGAS","LBFSH","LVAS","LRF","LHAMS","LGRA","LTFL","LSAR",
	"LGMAXL","LGMAXM","LGMEDA","LGMEDP","LADM","LADLB","LILPSO",
	"LPECT","LPIRI","LERCSPN","LINTOBL","LEXTOBL" 
	};

// BODIES
static char* bNames[] = {
	"pelvis","hat",
	"rfemur","rtibia","rhindfoot","rtoes",
	"lfemur","ltibia","lhindfoot","ltoes"
	};

// ACTUATORS
static char* aNames[] = {
	"RFDH","REDH","RDFIN","RDFEV","ROPFIN","ROPFEV",
	"RSOL","RGAS","RBFSH","RVAS","RRF","RHAMS","RGRA","RTFL","RSAR",
	"RGMAXL","RGMAXM","RGMEDA","RGMEDP","RADM","RADLB","RILPSO",
	"RPECT","RPIRI","RERCSPN","RINTOBL","REXTOBL",
	"LFDH","LEDH","LDFIN","LDFEV","LOPFIN","LOPFEV",
	"LSOL","LGAS","LBFSH","LVAS","LRF","LHAMS","LGRA","LTFL","LSAR",
	"LGMAXL","LGMAXM","LGMEDA","LGMEDP","LADM","LADLB","LILPSO",
	"LPECT","LPIRI","LERCSPN","LINTOBL","LEXTOBL",
	"LIG_back_extension","LIG_back_lateral","LIG_back_axial",
	"LIG_hip_r_extension","LIG_hip_r_adduction","LIG_hip_r_internal",
	"LIG_knee_r_angle","LIG_ankle_r_angle","LIG_subtalar_r_angle",
	"LIG_mtp_r_angle",
	"LIG_hip_l_extension","LIG_hip_l_adduction","LIG_hip_l_internal",
	"LIG_knee_l_angle","LIG_ankle_l_angle","LIG_subtalar_l_angle",
	"LIG_metatarsal_l_angle"
	};

// COORDINATES
static char* qNames[]  = {
	"pelvis_tx","pelvis_ty","pelvis_tz",
	"pelvis_Q1","pelvis_Q2","pelvis_Q3",
	"back_extension","back_lateral","back_axial",
	"hip_r_extension","hip_r_adduction","hip_r_internal",
	"knee_r_angle","ankle_r_angle","subtalar_r_angle",
	"mtp_r_angle",
	"hip_l_extension","hip_l_adduction","hip_l_internal",
	"knee_l_angle","ankle_l_angle","subtalar_l_angle",
	"metatarsal_l_angle",
	"pelvis_Q4"
	};

// SPEEDS
static char* uNames[]  = {
	"u_pelvis_tx","u_pelvis_ty","u_pelvis_tz",
	"u_pelvis_list","u_pelvis_transverse","u_pelvis_tilt",
	"u_back_extension","u_back_lateral","u_back_axial",
	"u_hip_r_extension","u_hip_r_adduction","u_hip_r_internal",
	"u_knee_r_angle","u_ankle_r_angle","u_subtalar_r_angle",
	"u_mtp_r_angle",
	"u_hip_l_extension","u_hip_l_adduction","u_hip_l_internal",
	"u_knee_l_angle","u_ankle_l_angle","u_subtalar_l_angle",
	"u_mtp_l_angle"
	};

// SPRINGS
static char* sNames[]  = {
	"s0x","s0y","s0z",
	"s1x","s1y","s1z",
	"s2x","s2y","s2z",
	"s3x","s3y","s3z",
	"s4x","s4y","s4z",
	"s5x","s5y","s5z",
	"s6x","s6y","s6z",
	"s7x","s7y","s7z",
	"s8x","s8y","s8z",
	"s9x","s9y","s9z"
	};

// PSEUDO-STATES
static char* ypNames[]  = {
	"s0x",
	"s1x",
	"s2x",
	"s3x",
	"s4x",
	"s5x",
	"s6x",
	"s7x",
	"s8x",
	"s9x",
	"s0z",
	"s1z",
	"s2z",
	"s3z",
	"s4z",
	"s5z",
	"s6z",
	"s7z",
	"s8z",
	"s9z",
	};


//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
rdUTWalking8Prescribed::~rdUTWalking8Prescribed()
{
	if(_ynode!=NULL) { delete[] _ynode;  _ynode=NULL; }
	if(_yp!=NULL) { delete[] _yp;  _yp=NULL; }
	if(_y!=NULL) { delete[] _y;  _y=NULL; }
	if(_tqlig!=NULL) { delete[] _tqlig;  _tqlig=NULL; }
	if(_actlen!=NULL) { delete[] _actlen;  _actlen=NULL; }
	if(_actsv!=NULL) { delete[] _actsv;  _actsv=NULL; }
}
//_____________________________________________________________________________
/**
 * Default constructor.
 */
rdUTWalking8Prescribed::rdUTWalking8Prescribed(const ActuatorSet *aActuatorSet,
									const ContactForceSet *aContactSet) :
	ActuatedModel_SDFast(aActuatorSet,aContactSet),
	_yNames(""),_yiUT(0.0),_ypiUT(0.0),_xUT(0.02)
{
	int i;

	// NODES
	//_nn = NN;

	// ALLOCATIONS
	printf("getNY() = %d\n",getNY());
	_xUT.setSize(NX);
	_yiUT.setSize(NY);
	_y = new double[NY];
	_ypiUT.setSize(NYP);
	_yp = new double[NYP];

	// INITIALIZE THE MODEL
	int maxiter,drvtype,sclflg,inf;
	double x[2*NX*NN],dx[2*NX*NN];
	_ynode = new double[NY*NN];
	intl23_(x,_ynode,&maxiter,&drvtype,dx,&sclflg,&inf,&_ypiUT[0],&_ypiUT[NS]);

	// CHECK THE VALUE OF GRAVITY
	double g[3];
	getGravity(g);
	printf("rdUTWalking8Prescribed: Gravity = %lf %lf %lf\n",g[0],g[1],g[2]);

	// LIGAMENT TORQUES
	_tqlig = new double[NJ];
	for(i=0;i<NJ;i++) _tqlig[i] = 0.0;

	// ACTUATOR LENGTHS AND VELOCITIES
	_actlen = new double[NX];
	_actsv = new double[NX];

	// INITIALIZE PARAMETERS
	initializeParameters();
	setTimeNormConstant(_tFinal);

	// INITIAL STATES
	initializeUTInitialStates();
	Array<double> yi(0.0,getNY());
	getInitialStates(&yi[0]);
	int nqnu = getNQ() + getNU();
	for(i=0;i<nqnu;i++) yi[i] = _yiUT[i];
	setInitialStates(&yi[0]);

	// STATES
	setStates(&yi[0]);

	// INITIAL PSEUDO-STATES
	Array<double> ypi(0.0,getNYP());

	// PSEUDO-STATES
	getInitialPseudoStates(&ypi[0]);
	setPseudoStates(&ypi[0]);

	// MAKE SURE ALL INITIAL HORIZONTAL SPRING ZEROS ARE VALID
	double svel[NS][3],spos[NS][3],sfrc[NS][3];
	computeSpringPointKinematics(svel,spos);
	computeGroundForces(svel,spos,sfrc);
	updateGroundZeros(svel,spos,sfrc);

	// NAMES
	setName("rdUTWalking8Prescribed");
	constructNames();

	// STORAGE
	char universal[2048];
	strcpy(universal,"S.I. Units\nTime");
	char tmp[10000];
	_store = false;

	// SPRINGS
	strcpy(tmp,universal);
	for(i=0;i<3*NS;i++) {
		strcat(tmp,"\t");
		strcat(tmp,sNames[i]);
	}

	// ADD INTEGRATION CALLBACK
	rdUTWalkingPrescribedIntegCallback *callback = new rdUTWalkingPrescribedIntegCallback(this);
	addIntegCallback(callback);

	// GRAPHICS
	_draw = false;

}


//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Initialize parameters.
 */
void rdUTWalking8Prescribed::
initializeParameters()
{
	// FINAL TIME
	_tFinal = 0.56;

	// ACTIVATION DYNAMICS
	// ORIGINAL
	_tcFall = 5.0;
	_tcRise = 45.0;
	// MORE TYPICAL
	//_tcFall = 1.0/0.050;
	//_tcRise = 1.0/0.010;
	// FAST RISE AND FALL FOR TRACKING
	//_tcFall = 200.0;
	//_tcRise = 200.0;

	// LIGAMENTS
	//_jdamp = 1.0e-3;
	_jdamp = 0.0;

	// FOOT-GROUND SPRINGS
	int i;
	for(i=0;i<NS;i++) {
		_sBodies[i] = SBODY[i];
		_sPoints[i][0] = SBODYPNT[i][0];
		_sPoints[i][1] = SBODYPNT[i][1];
		_sPoints[i][2] = SBODYPNT[i][2];
	}

	// ALLOW LEFT FOOT CONTACT
	_allowLeftContact = true;

	// ALLOW CONTACT FORCES TO BE APPLIED
	_allowApplyContactForces = true;
}

//_____________________________________________________________________________
/**
 * Initialize the initial states.
 */
void rdUTWalking8Prescribed::
initializeUTInitialStates()
{
	int i,I;
	int nq = getNQ();
	int nu = getNU();

	for(i=0;i<NY;i++) {
		I = Mtx::ComputeIndex(i,NN,0);
		_yiUT[i] = _ynode[I];
	}
}
//_____________________________________________________________________________
/**
 * Construct the names of the various components of the model.
 */
void rdUTWalking8Prescribed::
constructNames()
{
	int i;

	// BODIES
	for(i=0;i<getNB();i++) {
		setBodyName(i,bNames[i]);
	}

	// COORDINATES
	for(i=0;i<getNQ();i++) {
		setCoordinateName(i,qNames[i]);
	}

	// SPEEDS
	for(i=0;i<getNU();i++) {
		setSpeedName(i,uNames[i]);
	}

	// LOCAL STATES
	// Forces (54)
	for(i=0;i<NX;i++) {
		_yNames.append(aNames[i]);
	}
	// Activations (54)
	for(i=0;i<NX;i++) {
		_yNames.append(aNames[i]);
	}
	// Activation heat (54)
	for(i=0;i<NX;i++) {
		_yNames.append(aNames[i]);
	}
	// Maintenance heat (54)
	for(i=0;i<NX;i++) {
		_yNames.append(aNames[i]);
	}
	// Shortening heat (54)
	for(i=0;i<NX;i++) {
		_yNames.append(aNames[i]);
	}
	// Positive work (54)
	for(i=0;i<NX;i++) {
		_yNames.append(aNames[i]);
	}
	// Basal heat (54)
	for(i=0;i<NX;i++) {
		_yNames.append(aNames[i]);
	}
}


//=============================================================================
// GET AND SET
//=============================================================================
//-----------------------------------------------------------------------------
// NUMBERS OF THINGS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the number of controls for this model.
 *
 * @return Number of model controls.
 */
int rdUTWalking8Prescribed::
getNX() const
{
	return(NX + ActuatedModel_SDFast::getNX() );
}
//_____________________________________________________________________________
/**
 * Get the number of actuators in this model.
 *
 * @return Number of actuators.
 */
int rdUTWalking8Prescribed::
getNA() const
{
	return(NA + ActuatedModel_SDFast::getNA());
}
//_____________________________________________________________________________
/**
 * Get the number of contact points that are present given the current
 * state of the model.
 *
 * This method returns a valid result only after the contact points
 * have been computed.
 *
 * @return Number of contact points.
 * @see getContactPointsBodyLocal()
 */
int rdUTWalking8Prescribed::
getNP() const
{
	return(NS + ActuatedModel_SDFast::getNP());
}
//_____________________________________________________________________________
/**
 * Get the total number of states.
 *
 * @return Number of model states.
 */
int rdUTWalking8Prescribed::
getNY() const
{
	return(NY - getNQ() - getNU() + ActuatedModel_SDFast::getNY());
}
//_____________________________________________________________________________
/**
 * Get the total number of pseudo-states.
 *
 * @return Number of pseudo-states.
 */
int rdUTWalking8Prescribed::
getNYP() const
{
	return(NYP + ActuatedModel_SDFast::getNYP());
}

//-----------------------------------------------------------------------------
// NAMES
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the name of a control.
 *
 * @param aIndex Index of the control whose name is desired.  aIndex should
 * be greater than or equal to 0 and less than the number of model controls.
 * @return Control name.
 * @see getNX()
 */
string rdUTWalking8Prescribed::
getControlName(int aIndex) const
{

	if(aIndex < ActuatedModel_SDFast::getNX()) {
		return( ActuatedModel_SDFast::getControlName(aIndex) );

	} else if(aIndex<getNX()) {
		int index = aIndex - ActuatedModel_SDFast::getNX();
		return( xNames[index] );
	}

	return("");
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
string rdUTWalking8Prescribed::
getActuatorName(int aIndex) const
{
	if(aIndex < ActuatedModel_SDFast::getNA()) {
		return( ActuatedModel_SDFast::getActuatorName(aIndex) );

	} else if(aIndex<getNA()) {
		int index = aIndex - ActuatedModel_SDFast::getNA();
		return( aNames[index] );
	}

	return("");
}
//_____________________________________________________________________________
/**
 * Get the name of a state.
 *
 * @param aIndex Index of the state whose name is desired.  aIndex should
 * be greater than or equal to 0 and less than the number of states.
 * @return State name.  If aIndex is not valid an empty string "" is returned.
 */
string rdUTWalking8Prescribed::
getStateName(int aIndex) const
{
	// LOCAL STATE
	if(aIndex < ActuatedModel_SDFast::getNY()) {
		return( ActuatedModel_SDFast::getStateName(aIndex) );

	// ACTUATOR AND CONTACT SETS
	} else if(aIndex < getNY()) {
		int index = aIndex - ActuatedModel_SDFast::getNY();
		return(_yNames[index]);
	}

	return("");
}
//_____________________________________________________________________________
/**
 * Get the name of a pseudo-state.
 *
 * @param aIndex Index of the pseudo-state whose name is desired.  aIndex
 * should be greater than or equal to 0 and less than the number of states.
 * @return Pseudo-state name.
 * @see getNYP()
 */
string rdUTWalking8Prescribed::
getPseudoStateName(int aIndex) const
{
	if(aIndex<ActuatedModel_SDFast::getNYP()) {
		return( ActuatedModel_SDFast::getPseudoStateName(aIndex) );

	} else if(aIndex<getNYP()) {
		int index = aIndex - ActuatedModel_SDFast::getNYP();
		return( ypNames[index] );
	}

	return("");
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
int rdUTWalking8Prescribed::
getActuatorIndex(const string &aName) const
{
	int i;
	for(i=0;i<getNA();i++) {
		if(aName == getActuatorName(i)) return(i);
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
int rdUTWalking8Prescribed::
getControlIndex(const string &aName) const
{
	int i;
	for(i=0;i<getNX();i++) {
		if(aName == getControlName(i)) return(i);
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
int rdUTWalking8Prescribed::
getStateIndex(const string &aName) const
{
	int i;
	for(i=0;i<getNY();i++) {
		if(aName == getStateName(i)) return(i);
	}
	return(-1);
}
//_____________________________________________________________________________
/**
 * Get the index of a pseudo-state given its name.
 * The returned indices start at 0: for the first, 0 is returned; for
 * the second, 1; etc.
 *
 * Note that the pseudo-state names need to be unique for this method
 * to work properly.
 *
 * @param aName Name of a pseudo-state.
 * @return Index of the first pseudo-state with the name aName; -1, if there
 * is no such pseudo-state or if there is an error.  Indices start at 0.
 */
int rdUTWalking8Prescribed::
getPseudoStateIndex(const string &aName) const
{
	int i;
	for(i=0;i<getNYP();i++) {
		if(aName == getPseudoStateName(i)) return(i);
	}
	return(-1);
}

//-----------------------------------------------------------------------------
// CONTROLS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the current controls for the model.
 *
 * @param aX Array of controls.  The size of aX should be the value returned
 * by getNX().
 */
void rdUTWalking8Prescribed::
setControls(const double aX[])
{
	// BASE
	ActuatedModel_SDFast::setControls(aX);

	// UT
	int i;
	int base = ActuatedModel_SDFast::getNX();
	for(i=0;i<NX;i++) _xUT[i] = aX[base+i];
}
//_____________________________________________________________________________
/**
 * Get the current controls for the model.
 *
 * The controls must be set for the model and the actuators.
 *
 * @param rX Array of controls.  The size of aX should be the value returned
 * by getNX().
 * @see ActuatedModel_SDFast::setControls();
 */
void rdUTWalking8Prescribed::
getControls(double rX[]) const
{
	// BASE
	ActuatedModel_SDFast::getControls(rX);

	// UT
	int i;
	int base = ActuatedModel_SDFast::getNX();
	for(i=0;i<NX;i++) rX[i+base] = _xUT[i];
}
//_____________________________________________________________________________
/**
 * Get the current value of a control by index.
 *
 * @param aIndex Index of the control:  0 <= aIndex < getNX().
 * @return Value of the control.  rdMath::NAN is returned on an error.
 */
double rdUTWalking8Prescribed::
getControl(int aIndex) const
{
	double value = rdMath::NAN;
	int base = ActuatedModel_SDFast::getNX();

	// NEGATIVE INDEX
	if(aIndex<0) {
	
	// BASE
	} else if(aIndex<base) {
		value = _actuatorSet.getControl(aIndex);

	// UT
	} else if(aIndex<getNX()) {
		value = _xUT[aIndex - base];
	}

	return(value);
}

//-----------------------------------------------------------------------------
// INITIAL STATES
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the initial states for this model.
 *
 * @param aYI Array of states.  The size of rY must be at least the number
 * of states, which can be found by calling getNY().
 */
void rdUTWalking8Prescribed::
setInitialStates(const double aYI[])
{
	if(aYI==NULL) return;

	// BASE
	ActuatedModel_SDFast::setInitialStates(aYI);

	// UT MODEL
	int i;
	int nq = getNQ();
	int nu = getNU();
	int start = ActuatedModel_SDFast::getNY();
	for(i=0;i<nq;i++) {
		_yiUT[i] = aYI[i];
	}
	for(i=0;i<nu;i++) {
		_yiUT[i+nq] = aYI[i+nq];
	}
	for(i=0;i<NY;i++) {
		_yiUT[i+nq+nu] = aYI[i+start];
	}
}
//_____________________________________________________________________________
/**
 * Get the initial states currently set for this model.
 *
 * @param rYI Array to be filled with the initial states.  The size of rY must
 * be at least the number of states, which can be found by calling getNY().
 */
void rdUTWalking8Prescribed::
getInitialStates(double rYI[]) const
{
	if(rYI==NULL) return;

	// BASE
	ActuatedModel_SDFast::getInitialStates(rYI);

	// UT MODEL
	int nqnu = getNQ() + getNU();
	int start = ActuatedModel_SDFast::getNY();
	int i,n=NY-nqnu;
	for(i=0;i<n;i++) {
		rYI[i+start] = _yiUT[i+nqnu];
	}
}

//-----------------------------------------------------------------------------
// STATES
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the current states.  The states are the generalized coordinates,
 * followed by the generalized speeds, followed by the muscle forces,
 * followed by the muscle activations, followed by other stuff.
 *
 * @param aY Array of states.  The size of aY should be the value
 * returned by getNY().
 */
void rdUTWalking8Prescribed::
setStates(const double aY[])
{
	if(aY==NULL) return;

	ActuatedModel_SDFast::setStates(aY);

	// Qs and Us
	int i;
	int nqnu = getNQ() + getNU();
	for(i=0;i<nqnu;i++) _y[i] = aY[i];

	// OTHER UT MODEL STATES
	int nyBase = ActuatedModel_SDFast::getNY();
	int nyOther = getNY() - nyBase;
	for(i=0;i<nyOther;i++) _y[i+nqnu] = aY[i+nyBase];
}
//_____________________________________________________________________________
/**
 * Get the current states.  The states are the generalized coordinates,
 * followed by the generalized speeds, followed by the muscle forces,
 * followed by the muscle activations, followed by other stuff.
 *
 * @param rY Array to be filled with copies of the states.  The length
 * of rY must be at least as large as the value returned by getNY().
 */
void rdUTWalking8Prescribed::
getStates(double rY[]) const
{
	if(rY==NULL) return;

	// BASE STATES
	ActuatedModel_SDFast::getStates(rY);

	// UT MODEL STATES
	int i,j;
	int nyBase = ActuatedModel_SDFast::getNY();
	int nqnu = getNQ() + getNU();
	for(j=0,i=nyBase;i<getNY();j++,i++) rY[i] = _y[j+nqnu];
}
//_____________________________________________________________________________
/**
 * Get the current value of a state by index.  The states are the generalized
 * coordinates, followed by the generalized speeds, followed by the muscle
 * forces, followed by the muscle activations, followed by other stuff.
 *
 * @param aIndex Index of the state:  0 <= aIndex < getNY().
 * @return Value of the state.  rdMath::NAN is returned on an error.
 * @see getStates(double rY[])
 * @see getState(const char* aName);
 */
double rdUTWalking8Prescribed::
getState(int aIndex) const
{
	if(aIndex<0) return(rdMath::NAN);
	if(aIndex>getNY()) return(rdMath::NAN);

	// BASE
	if(aIndex<ActuatedModel_SDFast::getNY()) {
		return( ActuatedModel_SDFast::getState(aIndex) );

	// UT MODEL
	} else {
		int index = aIndex - ActuatedModel_SDFast::getNY();
		return(_y[index + getNQ() + getNU()]);
	}
}


//-----------------------------------------------------------------------------
// INITIAL PSEUDO-STATES
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the initial pseudo-states for this model.
 *
 * @param aYPI Array of pseudo-states.  The size of aYPI must be at least the
 * number of pseudo-states, which can be found by calling getNYP().
 */
void rdUTWalking8Prescribed::
setInitialPseudoStates(const double aYPI[])
{
	if(aYPI==NULL) return;

	// BASE
	ActuatedModel_SDFast::setInitialPseudoStates(aYPI);

	// UT MODEL
	int i;
	int nyp = rdUTWalking8Prescribed::getNYP();
	int start = ActuatedModel_SDFast::getNYP();
	int n = nyp - start;
	for(i=0;i<n;i++) {
		_ypiUT[i] = aYPI[i+start];
	}
}
//_____________________________________________________________________________
/**
 * Get the initial pseudo-states currently set for this model.
 *
 * @param rYPI Array to be filled with the initial pseudo-states.  The size of
 * rYPI must be at least the number of pseudo-states, which can be found by
 * calling getNYP().
 */
void rdUTWalking8Prescribed::
getInitialPseudoStates(double rYPI[]) const
{
	if(rYPI==NULL) return;

	// BASE
	ActuatedModel_SDFast::getInitialPseudoStates(rYPI);

	// UT MODEL
	int i;
	int nyp = rdUTWalking8Prescribed::getNYP();
	int start = ActuatedModel_SDFast::getNYP();
	int n = nyp - start;
	for(i=0;i<n;i++) {
		rYPI[i+start] = _ypiUT[i];
	}
}


//-----------------------------------------------------------------------------
// PSEUDO-STATES
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the current pseudo-states.  The pseudo-states for this model are the
 * horizontal spring zeros.  The fist 10 are the spring zeros in the X
 * direction; the second 10 are the spring zeros in the Z direction.
 *
 * @param aYP Array of pseudo-states.  The size of aYP should be the value
 * returned by getNYP().
 */
void rdUTWalking8Prescribed::
setPseudoStates(const double aYP[])
{
	if(aYP==NULL) return;

	// BASE CLASS
	ActuatedModel_SDFast::setPseudoStates(aYP);

	// OTHER UT MODEL STATES
	int i;
	int nypBase = ActuatedModel_SDFast::getNYP();
	int n = 2*NS;
	for(i=0;i<n;i++) _yp[i] = aYP[i+nypBase];

}
//_____________________________________________________________________________
/**
 * Get the current pseudo-states.  The pseudo-states for this model are the
 * horizontal spring zeros.  The fist 10 are the spring zeros in the X
 * direction; the second 10 are the spring zeros in the Z direction.
 *
 * @param rYP Array to be filled with copies of the pseudo-states.  The length
 * of rYP must be at least as large as the value returned by getNYP()-
 * there are 20 for this model.
 */
void rdUTWalking8Prescribed::
getPseudoStates(double rYP[]) const
{
	if(rYP==NULL) return;

	// BASE CLASS
	ActuatedModel_SDFast::getPseudoStates(rYP);

	// UT MODEL
	int i;
	int nypBase = ActuatedModel_SDFast::getNYP();
	int n = 2*NS;
	for(i=0;i<n;i++) rYP[i+nypBase] = _yp[i];
}
//_____________________________________________________________________________
/**
 * Get the current value of a pseudo-state by index.  The pseudo-states for
 * this model are the horizontal spring zeros.  The fist 10 are the spring
 * zeros in the X direction; the second 10 are the spring zeros in the
 * Z direction.
 *
 * @param aIndex Index of the pseudo-state:  0 <= aIndex < getNYP().
 * @return Value of the pseudo-state.  rdMath::NAN is returned on an error.
 * @see getPseudoStates(double rYP[])
 * @see getPseudoState(const char* aName);
 */
double rdUTWalking8Prescribed::
getPseudoState(int aIndex) const
{
	if(aIndex<0) return(rdMath::NAN);
	if(aIndex>getNYP()) return(rdMath::NAN);

	// BASE CLASS
	if(aIndex < ActuatedModel_SDFast::getNYP()) {
		return( ActuatedModel_SDFast::getPseudoState(aIndex) );

	} else {
		int index = aIndex - ActuatedModel_SDFast::getNYP();
		return(_yp[index]);
	}
}

//-----------------------------------------------------------------------------
// STORAGE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Turn on or off whether the model stores simulation data.
 */
void rdUTWalking8Prescribed::
setStore(bool aTrueFalse)
{
	_store = aTrueFalse;
}
//_____________________________________________________________________________
/**
 * Turn on or off whether the model stores simulation data.
 */
bool rdUTWalking8Prescribed::
getStore()
{
	return(_store);
}

//-----------------------------------------------------------------------------
// GRAPHICS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set whether or not to draw the model.
 */
void rdUTWalking8Prescribed::
setDraw(bool aTrueFalse)
{
	_draw = aTrueFalse;
}
//_____________________________________________________________________________
/**
 * Get whether or not the model is set to be drawn.
 */
bool rdUTWalking8Prescribed::
getDraw()
{
	return(_draw);
}

//-----------------------------------------------------------------------------
// PARAMETERS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the maximum isometric strength.
 */
void rdUTWalking8Prescribed::
setFOM(int aMuscle,double aFOM)
{
	if(aMuscle<getNX()) {
		aMuscle += 1;
		setfom_(&aMuscle,&aFOM);
	}
}
//_____________________________________________________________________________
/**
 * Get the maximum isometric strength.
 */
double rdUTWalking8Prescribed::
getFOM(int aMuscle) const
{
	double fom;
	if(aMuscle<getNX()) {
		aMuscle += 1;
		fom = getfom_(&aMuscle);
	} else {
		fom = 1.0;
	}

	return(fom);
}

//_____________________________________________________________________________
/**
 * Set the rise time of muscle activation.
 *
 * @param aTRise Rise time in seconds.  The lower limit is 0.0001 seconds.
 */
void rdUTWalking8Prescribed::
setTRise(double aTRise)
{
	double limit = 0.0001;
	if(aTRise<limit) aTRise = limit;
	_tcRise = 1.0 / limit;
}
//_____________________________________________________________________________
/**
 * Get the rise time of muscle activation.
 *
 * @return Rise time in seconds.
 */
double rdUTWalking8Prescribed::
getTRise() const
{
	return(1.0/_tcRise);
}

//_____________________________________________________________________________
/**
 * Set the fall time of muscle activation.
 *
 * @param aTFall Fall time in seconds.  The lower limit is 0.0001 seconds.
 */
void rdUTWalking8Prescribed::
setTFall(double aTFall)
{
	double limit = 0.0001;
	if(aTFall<limit) aTFall = limit;
	_tcFall = 1.0 / limit;
}
//_____________________________________________________________________________
/**
 * Get the fall time of muscle activation.
 *
 * @return Fall time in seconds.
 */
double rdUTWalking8Prescribed::
getTFall() const
{
	return(1.0/_tcFall);
}

//-----------------------------------------------------------------------------
// CONTACT FORCES
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set whether the contact forces will be applied
 * @param allowApplyContactForces flag indicates whether contact forces will be 
 * applied.
 */
void rdUTWalking8Prescribed::
setAllowApplyContactForces(bool aTrueFalse)
{
	_allowApplyContactForces = aTrueFalse;
}
//_____________________________________________________________________________
/**
 * Get whether the contact forces will be applied
 *
 * @return inputPositionsInLocalFrame Flag
 * @see setInputPositionsInLocalFrame()
 */
bool rdUTWalking8Prescribed::
getAllowApplyContactForces() const
{
	return(_allowApplyContactForces);
}

//=============================================================================
// PERFORMANCE
//=============================================================================
//_____________________________________________________________________________
/**
 * Compute the derivatives of the states.
int rdUTWalking8Prescribed::
computePerformance(double t,double *x,double *y,double *p,void *cd)
{
	// CAST CLIENT DATA
	if(cd==NULL) return(-1);
	rdDynamicFilter *filter = (rdDynamicFilter *)cd;

	//-------------------------------------------------
	// ACCELERATIONS
	//-------------------------------------------------

	// ESTIMATE GROUND FORCES AT t+dt
	double dt = filter->getDT();
	double sfrc[NS][3];
	estimateGroundForces(dt,t,x,y,sfrc);

	// SET
	set(t,x,y);

	// GROUND SPRINGS
	applyForces(NS,_sBodies,_sPoints,sfrc);

	// ACTUATOR FORCES
	applyActuatorForces();

	// DERIVATIVES OF GEN. COORDINATES AND SPEEDS
	double dqdt[NQ],dudt[NU];
	computeAccelerations(dqdt,dudt);

	//-------------------------------------------------
	// PERFORMANCE
	//-------------------------------------------------

	// GET WHICH COORDINATES ARE TRACKED
	bool *track = filter->getTrack();

	// SET UP LOOP TRACKING
	bool loop[NU];
	int i;
	for(i=0;i<NU;i++) loop[i] = track[i];

	// ACCELERATIONS
	double pAcc;
	double *dudt_c = filter->getCorrectedAccelerations();
	for(pAcc=0.0,i=0;i<_nu;i++) {

		// CHECK IF TRACKING IS TURNED OFF
		if(!loop[i]) continue;

		// ACCELERATION ERRORS
		pAcc += (dudt_c[i]-dudt[i])*(dudt_c[i]-dudt[i]);
	}

	// SUM OF SQUARES OF CONTROLS
	double pX;
	for(pX=0.0,i=0;i<_nx;i++) {
		pX += x[i]*x[i];
	}

	// TOTAL
	double kAcc = filter->getTrackingPerformanceWeight();
	double kX = filter->getControlsPerformanceWeight();
	*p = kAcc*pAcc + kX*pX;

	return(0);
}
 */
//_____________________________________________________________________________
/**
 * Estimate the ground forces at time t+dt.
 * This is done to anticipate the response of external reactions and, therefore,
 * to better control the trajectory of the center of mass.
void rdUTWalking8Prescribed::
estimateGroundForces(double dt,double t,double *x,double *y,double aFrc[][3])
{
	int i,j;

	// GET ACCELERATIONS
	double dqdt[NQ],dudt[NU];
	deriv(_t,x,y,dqdt,dudt);

	// COMPUTE SPRING POINT VELOCITIES AND POSITIONS
	double svel[NS][3],spos[NS][3];
	computeSpringPointKinematics(svel,spos);

	// COMPUE SPRING FORCES AT TIME t
	double sfrc[NS][3];
	computeGroundForces(svel,spos,sfrc);
	limitGroundForces(sfrc);

	// COMPUTE SPRING POINT ACCELERATIONS
	double sacc[NS][3];
	for(i=0;i<NS;i++) getAcceleration(_sBodies[i],&_sPoints[i][0],sacc[i]);

	// ESTIMATE SPRING POINT KINEMATICS AT t+dt
	// THIS IS DONE USING A SIMPLE 2ND ORDER APPROXIMATION
	double svel_dt[NS][3],spos_dt[NS][3];
	for(i=0;i<NS;i++) {
		for(j=0;j<3;j++) {
			spos_dt[i][j] = spos[i][j] + svel[i][j]*dt + 0.5*sacc[i][j]*dt*dt;
			svel_dt[i][j] = svel[i][j] + sacc[i][j]*dt;
			//printf("delta pos[%d][%d] = %lf\n",i,j,spos_dt[i][j]-spos[i][j]);
			//printf("delta vel[%d][%d] = %lf\n",i,j,svel_dt[i][j]-svel[i][j]);
		}
	}

	// COMPUTE NEW SPRING FORCES AT TIME t+dt
	double sfrc_dt[NS][3];
	computeGroundForces(svel_dt,spos_dt,sfrc_dt);
	limitGroundForces(sfrc_dt);

	// BE CONSERVATIVE AND AVERAGE t AND t+dt
	for(i=0;i<NS;i++) {
		for(j=0;j<3;j++) {
			aFrc[i][j] = 0.5*(sfrc[i][j]+sfrc_dt[i][j]);
			//printf("delta frc[%d][%d] = %lf\n",i,j,sfrc_dt[i][j]-sfrc[i][j]);
		}
	}
}
 */


//=============================================================================
// DERIVATIVES
//=============================================================================
//_____________________________________________________________________________
/**
 * Compute the derivatives of the auxiliary states.  The auxiliary states
 * are any integrated variables that are not the coordinates or speeds.
 *
 * @param dydt Array of the time derivatives of the auxiliary states.  The
 * auxiliary state derivatives should start at the beginning of the dydt
 * array.
 */
void rdUTWalking8Prescribed::
computeAuxiliaryDerivatives(double *dydt)
{
	// BASE
	_actuatorSet.computeStateDerivatives(dydt);

	// UT MODEL ADOT
	double adot[NX];
	int imsf = ActuatedModel_SDFast::getNY();
	int iatv = ActuatedModel_SDFast::getNY() + NX;
	mmatvdot_(&NX,&_xUT[0],&_y[iatv],&_tcRise,&_tcFall,adot);

	// UT MODEL FDOT AND EDOT
	double fdot[NX];
	double edot[NI];
	getactuatorlengths_(_actlen);
	getactuatorvelocities_(_actsv);
	mmfdot_(&NX,_actlen,_actsv,&_y[imsf],&_y[iatv],&_xUT[0],fdot,edot);

	// ASSIGN DERIVATIVES ----
	// CLAY -- left off here.
	int i;
	int I1 = imsf - getNQ() - getNU();
	int I2 = I1 + NX;
	int I3 = I2 + NX;
	for(i=0;i<NX;i++)  dydt[i+I1] = fdot[i];
	for(i=0;i<NX;i++)  dydt[i+I2] = adot[i];
	for(i=0;i<NI;i++)  dydt[i+I3] = edot[i];
}


//=============================================================================
// ACTUATION
//=============================================================================
//-----------------------------------------------------------------------------
// COMPUTE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Bring all quantities associate with actuting the model to a
 * valid internal state.
 */
void rdUTWalking8Prescribed::
computeActuation()
{
	// BASE CLASS
	ActuatedModel_SDFast::computeActuation();

	// MUSCLES
	computeMuscleForces();

	// LIGAMENTS
	computeLigamentTorques();
}
//_____________________________________________________________________________
/**
 * Compute the muscle forces.
 */
void rdUTWalking8Prescribed::
computeMuscleForces()
{
	Array<double> y(0.0,getNY());
	getStates(&y[0]);
	applyMuscleForces();
	setStates(&y[0]);
}
//_____________________________________________________________________________
/**
 * Compute the ligament torques.
 */
void rdUTWalking8Prescribed::
computeLigamentTorques()
{
	double qang[NU];
	convertQuaternionsToAngles(&_q[0],qang);
	computeLigamentTorques(qang,&_u[0],_tqlig);
}
//_____________________________________________________________________________
/**
 * Compute ligament torques.
 */
void rdUTWalking8Prescribed::
computeLigamentTorques(double *qang,double *u,double *trq)
{
	double damp,xlig1,xlig2;
	int i;
	for(i=0;i<NJ;i++) {
		damp = -_jdamp * u[6+i];
      xlig1 = qang[6+i] - theta1[i];
		xlig2 = qang[6+i] - theta2[i];
		trq[i] = k0lig[i] + k1lig1[i]*exp(k2lig1[i]*xlig1) +
                          k1lig2[i]*exp(k2lig2[i]*xlig2) + 
					damp;
	}
}

//-----------------------------------------------------------------------------
// APPLY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Apply a particular actuator force to the model.
 *
 * @param aIndex The index of the actuator force to apply.
 */
void rdUTWalking8Prescribed::
applyActuatorForce(int aIndex)
{
	// CHECK THE RANGE OF aI
	if(aIndex < 0) return;
	if(aIndex >= getNA()) return;

	// BASE
	if(aIndex<ActuatedModel_SDFast::getNA()) {
		ActuatedModel_SDFast::applyActuatorForce(aIndex);
		return;
	}

	// NEW INDEX
	int index = aIndex - ActuatedModel_SDFast::getNA();

	// LIGAMENTS
	if(index >= NX) {
		//printf("applyActuatorForce:  t=%lf  actuator=%d\n",_t,index);
		applyLigamentTorque(index-NX);
		return;
	}

	// GET COPY OF THE LOCAL UT MODEL STATES
	double y[NY];
	memcpy(y,_y,NY*sizeof(double));

	// SET ALL MUSCLE FORCES TO ZERO EXCEPT THE ONE INDEXED BY aIndex
	int i;
	for(i=0;i<NX;i++) {
		y[IMSF+i] = 0.0;
	}
	y[IMSF+index] = _y[IMSF+index];

	// APPLY MUSCLE FORCE
	//printf("applyActuatorForce:  t=%lf  actuator=%d\n",_t,index);
	force23_(&_t,y,&_q[0],&_u[0]);
}
//_____________________________________________________________________________
/**
 * Apply all actuator forces to the model.  Actuator forces include
 * muscle forces and ligament torques.
 */
void rdUTWalking8Prescribed::
applyActuatorForces()
{
	// BASE CLASS
	ActuatedModel_SDFast::applyActuatorForces();

	// MUSCLES
	applyMuscleForces();

	// LIGAMENT TORQUES
	applyLigamentTorque();
}
//_____________________________________________________________________________
/**
 * Apply the muscle forces to the skeleton and compute actuator lengths and
 * shortening velocities.
 */
void rdUTWalking8Prescribed::
applyMuscleForces()
{
	//int m = 6;
	//double f = getFOM(m)*_y[IMSF+m];
	//printf("%s force = %lf\n",getActuatorName(m),f);
	force23_(&_t,_y,&_q[0],&_u[0]);
}
//_____________________________________________________________________________
/**
 * Apply a ligament torque.
 *
 * @param ID of the ligament torque to apply- should be between 0 and 16.
 * If aID is negative, all ligament torques are applied.
 */
void rdUTWalking8Prescribed::
applyLigamentTorque(int aID)
{
	if(aID<0) {
		applyGeneralizedForces(NJ,LIGU,_tqlig);
	} else {
		applyGeneralizedForces(1,LIGU,&_tqlig[aID]);
	}
}

//-----------------------------------------------------------------------------
// SCALARS- FORCE, SPEED, POWER
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the magnitude of force experted by a particular actuator.
 *
 * @param aID Index of the actuator- should be greater than or
 * equal to zero and less than the value returned by getNA().
 * @param aForce Magnitude of actuator force.
 */
void rdUTWalking8Prescribed::
setActuatorForce(int aID,double aForce)
{
	if(aID<0) return;
	if(aID>=getNA()) return;

	// BASE
	if(aID<ActuatedModel_SDFast::getNA()) {
		ActuatedModel_SDFast::setActuatorForce(aID,aForce);
	}

	// UT MODEL
	int id = aID - ActuatedModel_SDFast::getNA();
	if(id<NX) {
		_y[IMSF+id] = aForce/getFOM(id);
	} else {
		_tqlig[id-NX] = aForce;
	}
}
//_____________________________________________________________________________
/**
 * Get the magnitude of force experted by a particular actuator.
 *
 * For the returned information to be valid, computeActuation() must be called
 * prior to calling this method.
 *
 * @param aID Index of the actuator- should be greater than or
 * equal to zero and less than the value returned by getNA().
 * @return Magnitude of actuator force.
 */
double rdUTWalking8Prescribed::
getActuatorForce(int aID) const
{
	if(aID<0) return(rdMath::NAN);
	if(aID>=getNA()) return(rdMath::NAN);

	// BASE
	if(aID<ActuatedModel_SDFast::getNA()) {
		return(ActuatedModel_SDFast::getActuatorForce(aID));
	}

	// UT MODEL
	int id = aID - ActuatedModel_SDFast::getNA();
	double force;
	if(id<NX) {
		force = getFOM(id)*_y[IMSF+id];
	} else {
		force = _tqlig[id-NX];
	}

	return(force);
}
//_____________________________________________________________________________
/**
 * Get the stress in a specified actuator.
 *
 * The ligament torques are divided by 300.0.
 *
 * @param aID Index of the actuator- should be greater than or
 * equal to zero and less than the value returned by getNA().
 * @return Magnitude of actuator force.
 */
double rdUTWalking8Prescribed::
getActuatorStress(int aID) const
{
	if(aID<0) return(rdMath::NAN);
	if(aID>=getNA()) return(rdMath::NAN);

	// BASE
	if(aID<ActuatedModel_SDFast::getNA()) {
		return(ActuatedModel_SDFast::getActuatorStress(aID));
	}

	// UT MODEL
	int id = aID - ActuatedModel_SDFast::getNA();
	double stress;
	if(id<NX) {
		stress = _y[IMSF+id];
	} else {
		stress = _tqlig[id-NX] / 300.0;
	}

	return(stress);
}
//_____________________________________________________________________________
/**
 * Get the speed at which a particular actuator force is applied.
 *
 * For the returned information to be valid, computeActuation() must be called
 * prior to calling this method.
 *
 * @param aID Index of the desired contact force- should be greater than or
 * equal to zero and less than the value returned by getNP().
 * @return Speed at which actuator force is applied.
 */
double rdUTWalking8Prescribed::
getActuatorSpeed(int aID) const
{
	if(aID<0) return(rdMath::NAN);
	if(aID>=getNA()) return(rdMath::NAN);

	// BASE
	if(aID<ActuatedModel_SDFast::getNA()) {
		return(ActuatedModel_SDFast::getActuatorSpeed(aID));
	}

	// UT MODEL
	int id = aID - ActuatedModel_SDFast::getNA();
	double speed;
	if(id<NX) {
		getactuatorvelocities_(_actsv);
		speed = _actsv[id];
	} else {
		int uID = 6 + id - NX;
		speed = getSpeed(uID);
	}

	return(speed);
}
//_____________________________________________________________________________
/**
 * Get the power delivered or absorbed by a particular actuator.
 * A positive power means the actuator is doing work on the model;
 * negative power means that the actuator is absorbing energy from the
 * model.
 *
 * For the returned information to be valid, computeActuation() must be called
 * prior to calling this method.
 *
 * @param aID Index of the desired contact force- should be greater than or
 * equal to zero and less than the value returned by getNP().
 * @return Power delivered (positive) or absorbed (negative).
 */
double rdUTWalking8Prescribed::
getActuatorPower(int aID) const
{
	if(aID<0) return(rdMath::NAN);
	if(aID>=getNA()) return(rdMath::NAN);

	// POWER
	double power = getActuatorForce(aID)*getActuatorSpeed(aID);

	return(power);
}


//=============================================================================
// CONTACT
//=============================================================================
//-----------------------------------------------------------------------------
// COMPUTE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Compute all quantities associated with contact.
 */
void rdUTWalking8Prescribed::
computeContact()
{
	ActuatedModel_SDFast::computeContact();

	// KINEMATICS
	computeSpringPointKinematics(_svel,_spos);

	// FORCES
	computeGroundForces(_svel,_spos,_sfrc);
	limitGroundForces(_sfrc);
}
//_____________________________________________________________________________
/**
 * Compute spring point positions and velocities in the inertial frame.
 */
void rdUTWalking8Prescribed::
computeSpringPointKinematics(double aVel[][3],double aPos[][3])
{
	int i;
	for(i=0;i<NS;i++) {
		getPosition(_sBodies[i],&_sPoints[i][0],aPos[i]);
		getVelocity(_sBodies[i],&_sPoints[i][0],aVel[i]);
	}
}
//_____________________________________________________________________________
/**
 * Compute ground forces given the current position and velocity of the
 * spring points.
 *
 * Note that horizontal forces are NOT limited in this method.  IF
 * friction is being modeled, limitGroundForces() and updateGroundZeros()
 * must be called.
 */
void rdUTWalking8Prescribed::
computeGroundForces(const double aVel[][3],const double aPos[][3],
	double aFrc[][3])
{
	int i;
	for(i=0;i<NS;i++) {

		// X: FORE-AFT FORCE
		aFrc[i][0] =
			Springs::DampedLinear(SKV,aVel[i][0],SKP,_yp[i],aPos[i][0]);

		// Y: VERTICAL FORCE
		aFrc[i][1] = Springs::ExponentialBarrier(G0,G1,G2,E0,E1,E2,
			SKV,aVel[i][1],aPos[i][1]);

		// Z: MEDIO-LATERAL FORCE
		aFrc[i][2] =
			Springs::DampedLinear(SKV,aVel[i][2],SKP,_yp[NS+i],aPos[i][2]);
	}

	if(_allowLeftContact) return;

	// CLUDGE- DON'T ALLOW LEFT-FOOT CONTACT
	for(i=NS/2;i<NS;i++) {

		// X: FORE-AFT FORCE
		aFrc[i][0] = 0.0;

		// Y: VERTICAL FORCE
		aFrc[i][1] = 0.0;

		// Z: MEDIO-LATERAL FORCE
		aFrc[i][2] = 0.0;
	}
}
//_____________________________________________________________________________
/**
 * Limit the horizontal ground forces so as to model friction.
 */
void rdUTWalking8Prescribed::
limitGroundForces(double aFrc[][3])
{
	double limit;
	int i;
	for(i=0;i<NS;i++) {

		// FORCE LIMIT
		limit = MU*aFrc[i][1];
		if(limit<0.0) limit=0.0;

		// X: FORE-AFT FORCE
		if(fabs(aFrc[i][0])>limit) {
			aFrc[i][0] = rdMath::CopySign(limit,aFrc[i][0]);
		}

		// Z: MEDIO-LATERAL FORCE
		if(fabs(aFrc[i][2])>limit) {
			aFrc[i][2] = rdMath::CopySign(limit,aFrc[i][2]);
		}
	}
}
//_____________________________________________________________________________
/**
 * Update the ground spring zeros in the horizontal plane.  The horizontal
 * forces are not allowed to exceed MU times the vertical force, so the 
 * horizontal spring zeros are computed to be consistent with this
 * constraint.
 */
void rdUTWalking8Prescribed::
updateGroundZeros(double svel[][3],double spos[][3],double sfrc[][3])
{
	int i;
	double limit,f;

	for(i=0;i<NS;i++) {

		// HORIZONTAL FORCE LIMIT
		limit = MU*sfrc[i][1];
		if(limit<0.0) limit=0.0;

		// X: FORE-AFT
		if(fabs(sfrc[i][0])>limit) {
			f = rdMath::CopySign(limit,sfrc[i][0]);
			_yp[i] = Springs::
			 ZeroForDampedLinear(SKV,svel[i][0],SKP,spos[i][0],f);
		}

		// Z: MEDIO-LATERAL
		if(fabs(sfrc[i][2])>limit) {
			f = rdMath::CopySign(limit,sfrc[i][2]);
			_yp[NS+i] = Springs::
			 ZeroForDampedLinear(SKV,svel[i][2],SKP,spos[i][2],f);
		}
	}
}
//_____________________________________________________________________________
/**
 * Set ground zeros to current positions of the springs.
 */
void rdUTWalking8Prescribed::
setGroundZerosToCurrentPosition(double t,double *y)
{
	// SET CONFIGURATION
	setTime(t);
	setStates(y);

	// SET ZEROS
	double pos[3];
	int i;
	for(i=0;i<NS;i++) {

		// INERTIAL POSITION AND VELOCITY
		getPosition(_sBodies[i],&_sPoints[i][0],pos);

		// SET
		_yp[i] = pos[0];
		_yp[NS+i] = pos[2];
	}
}
//_____________________________________________________________________________
/**
 * Compute the resultant forces and moments applied by the springs to the
 * bodies.
 *
 * Note that this method requires that the configuration of the body has been
 * set so that the inertial positions of the spring points can be computed.
 */
void rdUTWalking8Prescribed::
computeResultantBodyForces(double aFE[][3],double aFB[][6])
{
	int b,xyz;
	double m[3];

	// GROUND SPRINGS POSITIONS
	double svel[NS][3],spos[NS][3];
	computeSpringPointKinematics(svel,spos);

	// ZERO
	for(b=0;b<_nb;b++) for(xyz=0;xyz<6;xyz++) aFB[b][xyz]=0.0;

	// LOOP OVER SPRING ELEMENTS
	int e;
	double zero[3] = { 0.0, 0.0, 0.0 };
	double r[3],com[3];
	for(e=0;e<NS;e++) {

		// FORCE
		for(xyz=0;xyz<3;xyz++) {
			aFB[_sBodies[e]-1][xyz] += aFE[e][xyz];
		}

		// MOMENT
		getPosition(_sBodies[e],zero,com);
		for(xyz=0;xyz<3;xyz++) {
			r[xyz] = spos[e][xyz] - com[xyz];
		}
		Mtx::CrossProduct(r,aFE[e],m);
		for(xyz=0;xyz<3;xyz++) {
			aFB[_sBodies[e]-1][xyz+3] += m[xyz];
		}
	}
}

//-----------------------------------------------------------------------------
// APPLY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Apply a contact force.
 *
 * For the correct contact forces to be applied correctly, computeContact()
 * must be called prior to calling this method.
 *
 * @param aID ID of the contact force to be applied.
 */
void rdUTWalking8Prescribed::
applyContactForce(int aID)
{
	// CHECK ID
	if((aID<0)||(aID>=getNP())) {
		printf("rdUTWalking8Prescribed.getContactPointA: ERROR- invalid contact (%d).\n",
			aID);
		return;
	}

	// BASE
	if(aID<ActuatedModel_SDFast::getNP()) {
		ActuatedModel_SDFast::applyContactForce(aID);
	}

	// APPLY
	int id = aID - NS;
	applyForce(_sBodies[id],_sPoints[id],_sfrc[id]);
}
//_____________________________________________________________________________
/**
 * Apply the computed contacted forces.
 *
 * For the correct contact forces to be applied correctly, computeContact()
 * must be called prior to calling this method.
 */
void rdUTWalking8Prescribed::
applyContactForces()
{
	ActuatedModel_SDFast::applyContactForces();

	if(_allowLeftContact) {
		applyForces(getNP(),_sBodies,_sPoints,_sfrc);
	} else {
		// CLUDGE- Only apply the contact forces of the right foot
		applyForces(5,_sBodies,_sPoints,_sfrc);
	}
}

//_____________________________________________________________________________
/**
 * Set whether or not to allow left-foot contact forces.
 *
 * @param aTrueFalse If true, left-foot contact forces are allowed.  If false,
 * they are not allowed.
 */
void rdUTWalking8Prescribed::
setAllowLeftContact(bool aTrueFalse)
{
	_allowLeftContact = aTrueFalse;
}
//_____________________________________________________________________________
/**
 * Get whether or not to allow left-foot contact forces.
 *
 * @return True if left-foot contact forces are allowed; false otherwise.
 */
bool rdUTWalking8Prescribed::
getAllowLeftContact() const
{
	return(_allowLeftContact);
}

//-----------------------------------------------------------------------------
// BODY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the body number of BodyA for a particular contact force.
 *
 * For the returned information to be valid, computeContact() must be called
 * prior to calling this method.
 *
 * @param aID Index of the desired contact force- should be greater than or
 * equal to zero and less than the value returned by getNP().
 * @return Body ID of BodyA.
 */
AbstractBody* rdUTWalking8Prescribed::
getContactBodyA(int aID) const
{
	if((aID<0)||(aID>=getNP())) return &getDynamicsEngine().getGroundBody();

	// BASE
	if(aID<ActuatedModel_SDFast::getNP()) {
		return( ActuatedModel_SDFast::getContactBodyA(aID) );
	}

	// UT MODEL
	return &getDynamicsEngine().getGroundBody();
}
//_____________________________________________________________________________
/**
 * Get the body number of BodyB for a particular contact force.
 *
 * For the returned information to be valid, computeContact() must be called
 * prior to calling this method.
 *
 * @param aID Index of the desired contact force- should be greater than or
 * equal to zero and less than the value returned by getNP().
 * @return Body ID of BodyB.
 */
AbstractBody* rdUTWalking8Prescribed::
getContactBodyB(int aID) const
{
	if((aID<0)||(aID>=getNP())) return &getDynamicsEngine().getGroundBody();
	// BASE
	if(aID<ActuatedModel_SDFast::getNP()) {
		return( ActuatedModel_SDFast::getContactBodyA(aID) );
	}

	// UT MODEL
	//int id = aID - ActuatedModel_SDFast::getNP(); TODOAUG
	//return(_sBodies[id]);
}

//-----------------------------------------------------------------------------
// POINT
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the contact point on BodyA expressed in the local frame of BodyA
 * for a particular contact force.
 *
 * @param aID Index of the desired contact force- should be greater than or
 * equal to zero and less than the value returned by getNP().
 * @param aPoint Contact point on BodyA expressed in the local frame of
 * BodyA.
 */
void rdUTWalking8Prescribed::
setContactPointA(int aID,const double aPoint[3])
{
	// CHECK ID
	if((aID<0)||(aID>=getNP())) {
		printf("rdUTWalking8Prescribed.setContactPointA: ERROR- invalid contact (%d).\n",
			aID);
		return;
	}

	// BASE
	if(aID<ActuatedModel_SDFast::getNP()) {
		ActuatedModel_SDFast::setContactPointA(aID,aPoint);
	}

	// UT MODEL
	int id = aID - ActuatedModel_SDFast::getNP();
	_yp[id] = aPoint[0];
	_yp[NS+id] = aPoint[2];
}
//_____________________________________________________________________________
/**
 * Get the contact point on BodyA expressed in the local frame of BodyA
 * for a particular contact force.
 * 
 * For the returned information to be valid, computeContact() must be called
 * prior to calling this method.
 *
 * @param aID Index of the desired contact force- should be greater than or
 * equal to zero and less than the value returned by getNP().
 * @param rPoint Contact point on BodyA expressed in the local frame of
 * BodyA.
 */
void rdUTWalking8Prescribed::
getContactPointA(int aID,double rPoint[3]) const
{
	// CHECK ID
	if((aID<0)||(aID>=getNP())) {
		printf("rdUTWalking8Prescribed.getContactPointA: ERROR- invalid contact (%d).\n",
			aID);
		return;
	}

	// BASE
	if(aID<ActuatedModel_SDFast::getNP()) {
		ActuatedModel_SDFast::getContactPointA(aID,rPoint);
	}

	// UT MODEL
	int id = aID - ActuatedModel_SDFast::getNP();
	rPoint[0] = _yp[id];
	rPoint[1] = 0.0;
	rPoint[2] = _yp[NS+id];
}
//_____________________________________________________________________________
/**
 * Set the contact point on BodyB expressed in the local frame of BodyB
 * for a particular contact force.
 *
 * @param aID Index of the desired contact force- should be greater than or
 * equal to zero and less than the value returned by getNP().
 * @param aPoint Contact point on BodyA expressed in the local frame of
 * BodyA.
 */
void rdUTWalking8Prescribed::
setContactPointB(int aID,const double aPoint[3])
{
	// CHECK ID
	if((aID<0)||(aID>=getNP())) {
		printf("rdUTWalking8Prescribed.setContactPointB: ERROR- invalid contact (%d).\n",
			aID);
		return;
	}

	// BASE
	if(aID<ActuatedModel_SDFast::getNP()) {
		ActuatedModel_SDFast::setContactPointB(aID,aPoint);
	}

	// UT MODEL
	int id = aID - ActuatedModel_SDFast::getNP();
	_sPoints[id][0] = aPoint[0];
	_sPoints[id][1] = aPoint[1];
	_sPoints[id][2] = aPoint[2];
}
//_____________________________________________________________________________
/**
 * Get the contact point on BodyB expressed in the local frame of BodyB
 * for a particular contact force.
 * 
 * For the returned information to be valid, computeContact() must be called
 * prior to calling this method.
 *
 * @param aID Index of the desired contact force- should be greater than or
 * equal to zero and less than the value returned by getNP().
 * @param rPoint Contact point on BodyB expressed in the local frame of
 * BodyB.
 */
void rdUTWalking8Prescribed::
getContactPointB(int aID,double rPoint[3]) const
{
	// CHECK ID
	if((aID<0)||(aID>=getNP())) {
		printf("rdUTWalking8Prescribed.getContactPointB: ERROR- invalid contact (%d).\n",
			aID);
		return;
	}

	// BASE
	if(aID<ActuatedModel_SDFast::getNP()) {
		ActuatedModel_SDFast::getContactPointB(aID,rPoint);
	}

	// UT MODEL
	int id = aID - ActuatedModel_SDFast::getNP();
	rPoint[0] = _sPoints[id][0];
	rPoint[1] = _sPoints[id][1];
	rPoint[2] = _sPoints[id][2];
}

//-----------------------------------------------------------------------------
// FORCE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the contact force acting on BodyB expressed in the local frame of
 * BodyA for a particular contact force.
 *
 * For the returned information to be valid, computeContact() must be called
 * prior to calling this method.
 *
 * @param aID Index of the desired contact force- should be greater than or
 * equal to zero and less than the value returned by getNP().
 * @param rForce Contact force acting on BodyA expressed in the local frame of
 * BodyA.
 */
void rdUTWalking8Prescribed::
getContactForce(int aID,double rForce[3]) const
{
	// CHECK ID
	if((aID<0)||(aID>=getNP())) {
		printf("rdUTWalking8Prescribed.getContactForceA: ERROR- invalid contact (%d).\n",
			aID);
		return;
	}

	// BASE
	if(aID<ActuatedModel_SDFast::getNP()) {
		ActuatedModel_SDFast::getContactForce(aID,rForce);
	}

	// UT MODEL
	int id = aID - ActuatedModel_SDFast::getNP();
	rForce[0] = _sfrc[id][0];
	rForce[1] = _sfrc[id][1];
	rForce[2] = _sfrc[id][2];
}

//-----------------------------------------------------------------------------
// STIFFNESS AND VISCOSITY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the instantaneous stiffness of a particular contact force expressed in
 * the local frame of BodyA.
 *
 * For the returned information to be valid, computeContact() must be called
 * prior to calling this method.
 *
 * @param aID Index of the desired contact- should be greater than or
 * equal to zero and less than the value returned by getNP().
 * @param aDX Displacement of the BodyB contact point expressed in the
 * local frame of BodyA.
 * @param rDF Change in force applied to BodyB for the given displacement
 * (or stiffness if |aDX| = 1.0) expressed in the local frame of BodyA.
 */
void rdUTWalking8Prescribed::
getContactStiffness(int aID,const double aDX[3],double rDF[3]) const
{
	// CHECK ID
	if((aID<0)||(aID>=getNP())) {
		printf("rdUTWalking8Prescribed.getContactStiffnessA: ERROR- invalid contact ID ");
		printf("(%d).\n",aID);
		return;
	}

	// BASE
	if(aID<ActuatedModel_SDFast::getNP()) {
		ActuatedModel_SDFast::getContactStiffness(aID,aDX,rDF);
	}

	// UT MODEL
	int id = aID - ActuatedModel_SDFast::getNP();
	rDF[0] = SKP;
	rDF[1] = Springs::
		ExponentialBarrierDX(G0,G1,G2,E0,E1,E2,SKV,
		_svel[id][1],_spos[id][1]);
	rDF[2] = SKP;
}
//_____________________________________________________________________________
/**
 * Get the instantaneous viscosity of a particular contact force expressed in
 * the local frame of BodyA.
 *
 * For the returned information to be valid, computeContact() must be called
 * prior to calling this method.
 *
 * @param aID Index of the desired contact force- should be greater than or
 * equal to zero and less than the value returned by getNP().
 * @param aDV Change in velocity of the BodyB contact point expressed in the
 * local frame of BodyA.
 * @param rDF Change in force applied to BodyB for the given velocity change
 * (or viscosity if |aDX| = 1.0) expressed in the local frame of BodyA.
 */
void rdUTWalking8Prescribed::
getContactViscosity(int aID,const double aDV[3],double rDF[3]) const
{
	// CHECK ID
	if((aID<0)||(aID>=getNP())) {
		printf("rdUTWalking8Prescribed.getContactViscosityA: ERROR- invalid contact ID ");
		printf("(%d).\n",aID);
		return;
	}

	// BASE
	if(aID<ActuatedModel_SDFast::getNP()) {
		ActuatedModel_SDFast::getContactViscosity(aID,aDV,rDF);
	}

	// UT MODEL
	int id = aID - ActuatedModel_SDFast::getNP();
	rDF[0] = SKP;
	rDF[1] = Springs::
		ExponentialBarrierDV(G0,G1,G2,E0,E1,E2,SKV,
		_svel[id][1],_spos[id][1]);
	rDF[2] = SKP;
}

//-----------------------------------------------------------------------------
// SCALARS- FORCE, SPEED, POWER
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the magnitude of force experted by a particular contact force.
 *
 * For the returned information to be valid, computeContact() must be called
 * prior to calling this method.
 *
 * @param aID Index of the desired contact force- should be greater than or
 * equal to zero and less than the value returned by getNP().
 * @return Magnitude of contact force.
 */
double rdUTWalking8Prescribed::
getContactForce(int aID) const
{
	// CHECK ID
	if((aID<0)||(aID>=getNP())) {
		printf("rdUTWalking8Prescribed.getContactForce: ERROR- invalid contact ID ");
		printf("(%d).\n",aID);
		return(0.0);
	}

	// BASE
	if(aID<ActuatedModel_SDFast::getNP()) {
		return( ActuatedModel_SDFast::getContactForce(aID) );
	}

	// UT MODEL
	int id = aID - ActuatedModel_SDFast::getNP();
	return(Mtx::Magnitude(3,_sfrc[id]));
}
//_____________________________________________________________________________
/**
 * Get the speed at which a particular contact force is applied.
 *
 * For the returned information to be valid, computeContact() must be called
 * prior to calling this method.
 *
 * @param aID Index of the desired contact force- should be greater than or
 * equal to zero and less than the value returned by getNP().
 * @return Speed at which contact force is applied.
 */
double rdUTWalking8Prescribed::
getContactSpeed(int aID) const
{
	// CHECK ID
	if((aID<0)||(aID>=getNP())) {
		printf("rdUTWalking8Prescribed.getContactSpeed: ERROR- invalid contact ID ");
		printf("(%d).\n",aID);
		return(0.0);
	}

	// BASE
	if(aID<ActuatedModel_SDFast::getNP()) {
		ActuatedModel_SDFast::getContactSpeed(aID);
	}

	// UT MODEL
	int id = aID - ActuatedModel_SDFast::getNP();
	double speed =
		Mtx::DotProduct(3,_sfrc[id],_svel[id]) / getContactForce(id);
	return(speed);
}
//_____________________________________________________________________________
/**
 * Get the power delivered or absorbed by a particular contact force.
 * A positive power means the contact force is doing work on the model;
 * negative power means that the contact force is absorbing energy from the
 * model.
 *
 * For the returned information to be valid, computeContact() must be called
 * prior to calling this method.
 *
 * @param aID Index of the desired contact force- should be greater than or
 * equal to zero and less than the value returned by getNP().
 * @return Power delivered (positive) or absorbed (negative).
 */
double rdUTWalking8Prescribed::
getContactPower(int aID) const
{
	// CHECK ID
	if((aID<0)||(aID>=getNP())) {
		printf("rdUTWalking8Prescribed.getContactSpeed: ERROR- invalid contact ID ");
		printf("(%d).\n",aID);
		return(0.0);
	}

	// BASE
	if(aID<ActuatedModel_SDFast::getNP()) {
		ActuatedModel_SDFast::getContactPower(aID);
	}

	// UT MODEL
	int id = aID - ActuatedModel_SDFast::getNP();
	double power = Mtx::DotProduct(3,_sfrc[id],_svel[id]);
	return(power);
}


//=============================================================================
// UTILITY
//=============================================================================
//_____________________________________________________________________________
/**
 * Promote the controls to states.
 * This method assumes that the states of the model have been set using,
 * for example, set() or setStates().
 */
void rdUTWalking8Prescribed::
promoteControlsToStates(const double aX[],double aDT)
{
	// ACTIVATIONS
	int i;
	for(i=0;i<NX;i++) {
		_y[IATV+i] = aX[i];
	}

	// MUSCLE FORCES
	//int mus;
	//double atv;
	//computeActuation();
	//getactuatorlengths_(_actlen);
	//getactuatorvelocities_(_actsv);
	for(i=0;i<NX;i++) {
		//mus = i + 1;
		//atv = aX[i];
		//_actsv[i] = 0.0;	// CONTROL DECISIONS MADE AS THOUGH NO VELOCITY
		//_y[IMSF+i] = musfrc_(&mus,&atv,&_actlen[i],&_actsv[i]);
		//printf("%d: atv=%lf frc=%lf\n",i,atv,_y[IMSF+i]);
		_y[IMSF+i] = aX[i];
	}
}


//=============================================================================
// GRAPHICS
//=============================================================================
//_____________________________________________________________________________
/**
 * Draw the model
 */
int rdUTWalking8Prescribed::
draw(double t,double *x,double *y,double *sfrc,double *spnt)
{
	// SET STATES
	set(t,x,y);

	// DRAW
	int status = -1;
	//status = drawutwalking_(&t,x,y,sfrc,spnt);
#ifdef UNIX
	status = drawutwalking_(&t,x,y,sfrc,spnt);
#endif
	
	return(status);
}
//_____________________________________________________________________________
/**
 * Draw the model
 */
int rdUTWalking8Prescribed::
draw(double t,double *x,double *y)
{
	// SET STATES
	set(t,x,y);

	// COMPUTE SPRING FORCES
	double svel[NS][3],spos[NS][3],sfrc[NS][3];
	computeSpringPointKinematics(svel,spos);
	computeGroundForces(svel,spos,sfrc);
	limitGroundForces(sfrc);
	
	// DRAW
	int status = -1;
	//status = drawutwalking_(&t,x,y,&sfrc[0][0],&spos[0][0]);
#ifdef UNIX
	status = drawutwalking_(&t,x,y,&sfrc[0][0],&spos[0][0]);
#endif
	
	return(status);
}

//_____________________________________________________________________________
/**
 * Set which muscles are drawn.
 * A value of 1 is on, 0 off.
 */
void rdUTWalking8Prescribed::
setMuson(int aMus,int aOnOff)
{
	aMus += 1;
	setmuson_(&aMus,&aOnOff);
}


//=============================================================================
// CALLBACKS
//=============================================================================
//_____________________________________________________________________________
/**
 * After each integration step, update the horizontal spring zeros and
 * draw the model.
 *
 * @todo A separate IntegCallback should be written to replace this
 * method.
void rdUTWalking8Prescribed::
integStepCallback(double *aXPrev,double *aYPrev,
	int aStep,double aDT,double aT,double *aX,double *aY,
	void *aClientData)
{
	//printf("rdUTWalking8Prescribed.integStepCallback: t=%lf\n",aT);

	// SET
	set(aT,aX,aY);

	// UPDATE CONTACTS
	_contactSet.updatePseudoStates();

	// EXTRACT THE GENERALIZED COORDINATES AND SPEEDS
	double q[24],u[23];
	getCoordinates(q);
	getSpeeds(u);

	// COMPUTE THE SPRING FORCES
	double svel[NS][3],spos[NS][3],sfrc[NS][3];
	computeSpringPointKinematics(svel,spos);
	computeGroundForces(svel,spos,sfrc);

	// UPDATE THE HORIZONTAL SPRING ZEROS
	updateGroundZeros(svel,spos,sfrc);

	// LIMIT THE GROUND FORCES
	limitGroundForces(sfrc);

	// DRAW THE MODEL
	if(_draw) {
#ifdef UNIX
		if((aStep%20)==0) drawutwalking_(&aT,aX,aY,&sfrc[0][0],&spos[0][0]);
#endif
	}
}
*/
