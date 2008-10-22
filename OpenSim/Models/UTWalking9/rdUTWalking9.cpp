// rdUTWalking9.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Frank C. Anderson
/*
* Copyright (c)  2005, Stanford University. All rights reserved. 
* Use of the OpenSim software in source form is permitted provided that the following
* conditions are met:
* 	1. The software is used only for non-commercial research and education. It may not
*     be used in relation to any commercial activity.
* 	2. The software is not distributed or redistributed.  Software distribution is allowed 
*     only through https://simtk.org/home/opensim.
* 	3. Use of the OpenSim software or derivatives must be acknowledged in all publications,
*      presentations, or documents describing work in which OpenSim or derivatives are used.
* 	4. Credits to developers may not be removed from executables
*     created from modifications of the source.
* 	5. Modifications of source code must retain the above copyright notice, this list of
*     conditions and the following disclaimer. 
* 
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
*  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
*  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
*  SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
*  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
*  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
*  OR BUSINESS INTERRUPTION) OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
*  WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*  
 * Author:  
 */


//=============================================================================
// INCLUDES
//=============================================================================
#include <string>
#include <math.h>
#include <RD/Tools/rdTools.h>
#include <RD/Tools/Math.h>
#include <RD/Tools/Mtx.h>
#include <RD/Tools/Memory.h>
#include <RD/Simulation/Model/Model.h>
#include <RD/Simulation/Model/Analysis.h>
#include <RD/Simulation/Model/Springs.h>
#include <RD/Simulation/SDFast/sdfast.h>
#include "rdUTWalking9.h"
#include <SU/Models/UTWalk8IATaylor/utwalking.h>




using namespace OpenSim;
using namespace std;


//=============================================================================
// CONSTANTS
//=============================================================================
// NUMBERS OF THINGS
const int rdUTWalking9::NA9 = rdUTWalking9_NA;   
const int rdUTWalking9::NS9 = rdUTWalking9_NS;
const int rdUTWalking9::NL9 = rdUTWalking9_NL;


// LIGAMENTS
/*
static char* ligNames[] =	{
	"LIG_back_extension","LIG_back_lateral","LIG_back_axial",
	"LIG_hip_r_extension","LIG_hip_r_adduction","LIG_hip_r_internal",
	"LIG_knee_r_angle","LIG_ankle_r_angle","LIG_subtalar_r_angle",
	"LIG_mtp_r_angle",
	"LIG_hip_l_extension","LIG_hip_l_adduction","LIG_hip_l_internal",
	"LIG_knee_l_angle","LIG_ankle_l_angle","LIG_subtalar_l_angle",
	"LIG_metatarsal_l_angle"
	};
*/

static int ligBodyA[] = {
	0, 0, 0,
	0, 0, 0,
	2, 3, 3,
	4,
	0, 0, 0,
	6, 7, 7,
	8,
	};

static int ligBodyB[] = {
	1, 1, 1,
	2, 2, 2,
	3, 4, 4,
	5,
	6, 6, 6,
	7, 8, 8,
	9,
	};

//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
rdUTWalking9::~rdUTWalking9()
{
}
//_____________________________________________________________________________
/**
 * Default constructor.
 */
rdUTWalking9::rdUTWalking9(const ActuatorSet *aActuatorSet,
									const ContactForceSet *aContactSet) :
	rdUTWalking8(aActuatorSet,aContactSet)
{
	setName("rdUTWalking9");
}


//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================



//=============================================================================
// GET AND SET
//=============================================================================
//-----------------------------------------------------------------------------
// NUMBERS OF THINGS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the number of actuators in this model.
 *
 * @return Number of actuators.
 */
int rdUTWalking9::
getNA() const
{
	return(ActuatedModel_SDFast::getNA() + NA9);
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
int rdUTWalking9::
getNP() const
{
	return(ActuatedModel_SDFast::getNP() + NS9 + NL9);
}

//-----------------------------------------------------------------------------
// NAMES
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the name of an actuator.
 *
 * @param aIndex Index of the actuator whose name is desired.  aIndex should
 * be greater than or equal to 0 and less than the number of actuators.
 * @return Control name.
 * @see getNA()
 */
string rdUTWalking9::
getActuatorName(int aIndex) const
{
	if(aIndex<rdUTWalking9::getNA()) {
		return( rdUTWalking8::getActuatorName(aIndex) );
	}

	return("");
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
void rdUTWalking9::
computeActuation()
{
	// BASE CLASS
	ActuatedModel_SDFast::computeActuation();

	// MUSCLES
	computeMuscleForces();
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
void rdUTWalking9::
applyActuatorForce(int aIndex)
{
	// CHECK THE RANGE OF aI
	if(aIndex < 0) return;
	if(aIndex >= rdUTWalking9::getNA()) return;

	rdUTWalking8::applyActuatorForce(aIndex);
}
//_____________________________________________________________________________
/**
 * Apply all actuator forces to the model.  Actuator forces include only
 * muscle forces.
 */
void rdUTWalking9::
applyActuatorForces()
{
	// BASE CLASS
	ActuatedModel_SDFast::applyActuatorForces();

	// MUSCLES
	applyMuscleForces();
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
void rdUTWalking9::
setActuatorForce(int aID,double aForce)
{
	if(aID<0) return;
	if(aID>=rdUTWalking9::getNA()) return;

	rdUTWalking8::setActuatorForce(aID,aForce);
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
double rdUTWalking9::
getActuatorForce(int aID) const
{
	if(aID<0) return(rdMath::getNAN());
	if(aID>=rdUTWalking9::getNA()) return(rdMath::getNAN());

	double force = rdUTWalking8::getActuatorForce(aID);

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
double rdUTWalking9::
getActuatorStress(int aID) const
{
	if(aID<0) return(rdMath::getNAN());
	if(aID>=rdUTWalking9::getNA()) return(rdMath::getNAN());

	double stress = rdUTWalking8::getActuatorStress(aID);
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
double rdUTWalking9::
getActuatorSpeed(int aID) const
{
	if(aID<0) return(rdMath::getNAN());
	if(aID>=rdUTWalking9::getNA()) return(rdMath::getNAN());

	double speed = rdUTWalking8::getActuatorSpeed(aID);
	return(speed);
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
void rdUTWalking9::
computeContact()
{
	ActuatedModel_SDFast::computeContact();

	// KINEMATICS
	computeSpringPointKinematics(_svel,_spos);

	// GROUND FORCES
	computeGroundForces(_svel,_spos,_sfrc);
	limitGroundForces(_sfrc);

	// LIGAMENTS
	computeLigamentTorques();
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
void rdUTWalking9::
applyContactForce(int aID)
{
	// CHECK ID
	if((aID<0)||(aID>=rdUTWalking9::getNP())) {
		printf("rdUTWalking9.getContactPointA: ERROR- invalid contact (%d).\n",
			aID);
		return;
	}

	// BASE
	int npBase = ActuatedModel_SDFast::getNP();
	if(aID<npBase) {
		ActuatedModel_SDFast::applyContactForce(aID);

	// UT SPRING
	} else if(aID < (npBase+NS9)) {
		int id = aID - npBase;
		applyForce(_sBodies[id],_sPoints[id],_sfrc[id]);

	// UT LIGAMENTS
	} else {
		int id = aID - npBase - NS9;
		applyLigamentTorque(id);
	}
}
//_____________________________________________________________________________
/**
 * Apply the computed contacted forces.
 *
 * For the correct contact forces to be applied correctly, computeContact()
 * must be called prior to calling this method.
 */
void rdUTWalking9::
applyContactForces()
{
	ActuatedModel_SDFast::applyContactForces();

	if(_allowLeftContact) {
		applyForces(NS9,_sBodies,_sPoints,_sfrc);
	} else {
		// CLUDGE- Only apply the contact forces of the right foot
		applyForces(5,_sBodies,_sPoints,_sfrc);
	}

	// LIGAMENT TORQUES
	applyLigamentTorque();
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
int rdUTWalking9::
getContactBodyA(int aID) const
{
	if((aID<0)||(aID>=rdUTWalking9::getNP())) return(getGroundID()-1);

	// BASE
	int npBase = ActuatedModel_SDFast::getNP();
	if(aID<npBase) {
		return( ActuatedModel_SDFast::getContactBodyA(aID) );

	// UT SPRINGS
	} else if(aID < (npBase+NS9)) {
		return(getGroundID());

	// UT LIGAMENTS
	} else {
		int id = npBase - NS9;
		return(ligBodyA[id]); 
	}
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
int rdUTWalking9::
getContactBodyB(int aID) const
{
	if((aID<0)||(aID>=rdUTWalking9::getNP())) return(getGroundID()-1);

	// BASE
	int npBase = ActuatedModel_SDFast::getNP();
	if(aID<npBase) {
		return( ActuatedModel_SDFast::getContactBodyB(aID) );

	// UT SPRINGS
	} else if(aID < (npBase+NS9)) {
		int id = aID - npBase;
		return(_sBodies[id]);

	// UT LIGAMENTS
	} else {
		int id = npBase - NS9;
		return(ligBodyB[id]); 
	}
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
void rdUTWalking9::
setContactPointA(int aID,const double aPoint[3])
{
	// CHECK ID
	if((aID<0)||(aID>=rdUTWalking9::getNP())) {
		printf("rdUTWalking9.setContactPointA: ERROR- invalid contact (%d).\n",
			aID);
		return;
	}

	// BASE
	int npBase = ActuatedModel_SDFast::getNP();
	if(aID<npBase) {
		ActuatedModel_SDFast::setContactPointA(aID,aPoint);

	// UT SPRINGS
	} else if(aID < (npBase+NS9)) {
		int id = aID - npBase;
		_yp[id] = aPoint[0];
		_yp[NS9+id] = aPoint[2];
	}

	// UT LIGAMENTS- Nothing to be done.
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
void rdUTWalking9::
getContactPointA(int aID,double rPoint[3]) const
{
	// CHECK ID
	if((aID<0)||(aID>=rdUTWalking9::getNP())) {
		printf("rdUTWalking9.getContactPointA: ERROR- invalid contact (%d).\n",
			aID);
		return;
	}

	// BASE
	int npBase = ActuatedModel_SDFast::getNP();
	if(aID<npBase) {
		ActuatedModel_SDFast::getContactPointA(aID,rPoint);

	// UT SPRINGS
	} else if(aID < (npBase+NS9)) {
		int id = aID - npBase;
		rPoint[0] = _yp[id];
		rPoint[1] = 0.0;
		rPoint[2] = _yp[NS9+id];

	// UT LIGAMENTS
	} else {
		rPoint[0] = 0.0;
		rPoint[1] = 0.0;
		rPoint[2] = 0.0;
	}	
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
void rdUTWalking9::
setContactPointB(int aID,const double aPoint[3])
{
	// CHECK ID
	if((aID<0)||(aID>=rdUTWalking9::getNP())) {
		printf("rdUTWalking9.setContactPointB: ERROR- invalid contact (%d).\n",
			aID);
		return;
	}

	// BASE
	int npBase = ActuatedModel_SDFast::getNP();
	if(aID<npBase) {
		ActuatedModel_SDFast::setContactPointB(aID,aPoint);

	// UT SPRINGS
	} else if(aID < (npBase+NS9)) {
		int id = aID - npBase;
		_sPoints[id][0] = aPoint[0];
		_sPoints[id][1] = aPoint[1];
		_sPoints[id][2] = aPoint[2];
	}

	// UT LIGAMENTS- Nothing to be done.

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
void rdUTWalking9::
getContactPointB(int aID,double rPoint[3]) const
{

	// CHECK ID
	if((aID<0)||(aID>=rdUTWalking9::getNP())) {
		printf("rdUTWalking9.getContactPointA: ERROR- invalid contact (%d).\n",
			aID);
		return;
	}

	// BASE
	int npBase = ActuatedModel_SDFast::getNP();
	if(aID<npBase) {
		ActuatedModel_SDFast::getContactPointA(aID,rPoint);

	// UT SPRINGS
	} else if(aID < (npBase+NS9)) {
		int id = aID - npBase;
		rPoint[0] = _sPoints[id][0];
		rPoint[1] = _sPoints[id][1];
		rPoint[2] = _sPoints[id][2];

	// UT LIGAMENTS
	} else {
		rPoint[0] = 0.0;
		rPoint[1] = 0.0;
		rPoint[2] = 0.0;
	}	
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
 *
 * @todo Ligament torques are not implemented as a vector.  For now, the
 * first component of rForce (i.e., rForce[0]) is set to the ligament
 * torque, and rForce[1] and rForce[2] are set to zero.  This should be
 * improved.
 */
void rdUTWalking9::
getContactForce(int aID,double rForce[3]) const
{
	// CHECK ID
	if((aID<0)||(aID>=rdUTWalking9::getNP())) {
		printf("rdUTWalking9.getContactForceA: ERROR- invalid contact (%d).\n",
			aID);
		return;
	}

	// BASE
	int npBase = ActuatedModel_SDFast::getNP();
	if(aID<npBase) {
		ActuatedModel_SDFast::getContactForce(aID,rForce);
	
	// UT SPRINGS
	} else if(aID<(npBase+NS9)) {
		int id = aID - npBase;
		rForce[0] = _sfrc[id][0];
		rForce[1] = _sfrc[id][1];
		rForce[2] = _sfrc[id][2];

	// UT LIGAMENTS
	} else {
		int id = aID - npBase - NS9;
		rForce[0] = _tqlig[id];
		rForce[0] = 0.0;
		rForce[0] = 0.0;
	}
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
void rdUTWalking9::
getContactStiffness(int aID,const double aDX[3],double rDF[3]) const
{
	// CHECK ID
	if((aID<0)||(aID>=rdUTWalking9::getNP())) {
		printf("rdUTWalking9.getContactStiffnessA: ERROR- invalid contact ID ");
		printf("(%d).\n",aID);
		return;
	}

	// BASE
	int npBase = rdUTWalking8::getNP();
	if(aID<npBase) {
		rdUTWalking8::getContactStiffness(aID,aDX,rDF);

	// UT LIGAMENTS
	} else {
		rDF[0] = rDF[1] = rDF[2] = 0.0;
	}
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
void rdUTWalking9::
getContactViscosity(int aID,const double aDV[3],double rDF[3]) const
{
	// CHECK ID
	if((aID<0)||(aID>=rdUTWalking9::getNP())) {
		printf("rdUTWalking9.getContactViscosityA: ERROR- invalid contact ID ");
		printf("(%d).\n",aID);
		return;
	}

	// BASE
	int npBase = rdUTWalking8::getNP();
	if(aID<npBase) {
		rdUTWalking8::getContactViscosity(aID,aDV,rDF);

	// UT LIGAMENTS
	} else {
		rDF[0] = rDF[1] = rDF[2] = 0.0;
	}
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
double rdUTWalking9::
getContactForce(int aID) const
{
	// CHECK ID
	if((aID<0)||(aID>=rdUTWalking9::getNP())) {
		printf("rdUTWalking9.getContactForce: ERROR- invalid contact ID ");
		printf("(%d).\n",aID);
		return(0.0);
	}

	// BASE
	int npBase = ActuatedModel_SDFast::getNP();
	if(aID<npBase) {
		return( ActuatedModel_SDFast::getContactForce(aID) );

	// UT MODEL
	// Foot-ground springs
	} else if(aID<(npBase+NS9)) {
		int id = aID - npBase;
		return(Mtx::Magnitude(3,_sfrc[id]));

	// Ligaments
	} else {
		int id = aID - npBase - NS9;
		return(_tqlig[id]);
	}
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
double rdUTWalking9::
getContactSpeed(int aID) const
{
	// CHECK ID
	if((aID<0)||(aID>=rdUTWalking9::getNP())) {
		printf("rdUTWalking9.getContactSpeed: ERROR- invalid contact ID ");
		printf("(%d).\n",aID);
		return(0.0);
	}

	// BASE
	int npBase = ActuatedModel_SDFast::getNP();
	if(aID<npBase) {
		double speed = ActuatedModel_SDFast::getContactSpeed(aID);
		return(speed);

	// UT SPRINGS
	} else if(aID<(npBase+NS9)) {
		int id = aID - npBase;
		double speed =
			Mtx::DotProduct(3,_sfrc[id],_svel[id]) / getContactForce(id);
		return(speed);

	// UT LIGAMENTS
	} else {
		int id = aID - npBase - NS9;
		return( getSpeed(id+6) );
	}
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
double rdUTWalking9::
getContactPower(int aID) const
{
	// CHECK ID
	if((aID<0)||(aID>=rdUTWalking9::getNP())) {
		printf("rdUTWalking9.getContactSpeed: ERROR- invalid contact ID ");
		printf("(%d).\n",aID);
		return(0.0);
	}

	// BASE
	int npBase = ActuatedModel_SDFast::getNP();
	if(aID<npBase) {
		double power = ActuatedModel_SDFast::getContactPower(aID);
		return(power);

	// UT SPRINGS
	} else if(aID<(npBase+NS9)) {
		int id = aID - npBase;
		double power = Mtx::DotProduct(3,_sfrc[id],_svel[id]);
		return(power);

	// UT LIGAMENTS
	} else {
		double force = getContactForce(aID);
		double speed = getContactSpeed(aID);
		return(force*speed);
	}
}


