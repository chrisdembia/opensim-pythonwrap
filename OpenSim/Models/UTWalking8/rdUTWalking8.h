#ifndef _rdUTWalking8_h_
#define _rdUTWalking8_h_
// rdUTWalking8.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
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

/* Note: This code was originally developed by Realistic Dynamics Inc. 
 * Author: Frank C. Anderson 
 */


//=============================================================================
// INCLUDES
//=============================================================================
//#include <Storage.h>
#include <OpenSim/Simulation/SDFast/rdSDFastDLL.h>
#include <OpenSim/Simulation/Model/Model.h>
#include <OpenSim/Simulation/SDFast/ActuatedModel_SDFast.h>

// NUMBERS OF THINGS
const int rdUTWalking8_NQ = 24;
const int rdUTWalking8_NU = 23;
const int rdUTWalking8_NB = 10;
const int rdUTWalking8_NJ = 17;
const int rdUTWalking8_NX = 54;
const int rdUTWalking8_NA = 71;
const int rdUTWalking8_NY = 425;
const int rdUTWalking8_NYP = 20;
const int rdUTWalking8_NN = 15;
const int rdUTWalking8_NS = 10;
const int rdUTWalking8_IMSF = rdUTWalking8_NQ + rdUTWalking8_NU;


//=============================================================================
//=============================================================================
/**
 * A three dimensional model of the human body.  The model has 23 degrees
 * of freedom: 6 DOF pelvis, 3 DOF back joint, 3 DOF hips, 1 DOF knees,
 * 2 DOF ankles, 1 DOF metatarsal.  It is actuated by 54 lumped-parameter
 * muscle-tendon units.  The controls of the model are the net
 * excitation levels (0 to 1) of the muscles.  Force interactions
 * between the feet and ground are mediated by 5 spring-and-damper units on
 * the sole of each foot.
 */
namespace OpenSim { 

class AbstractBody;

class RDSDFAST_API rdUTWalking8 : public ActuatedModel_SDFast
{
//=============================================================================
// DATA
//=============================================================================
public:
	static const int NQ;
	static const int NU;
	static const int NB;
	static const int NJ;
	static const int NX;
	static const int NA;
	static const int NY;
	static const int NYP;
	static const int NS;
	static const int NN;
	static const int NI;
	static const int IMSF;
	static const int IATV;
	static const int IINT;
	static const int LIGU[];
	static const int LIGJOINT[];
	static const int LIGAXIS[];
	static const double theta1[];
	static const double theta2[];
	static const double k0lig[];
	static const double k1lig1[];
	static const double k2lig1[];
	static const double k1lig2[];
	static const double k2lig2[];
	static const double MU;
	static const double SKV;
	static const double SKP;
	static const double E0;
	static const double E1;
	static const double E2;
	static const double G0;
	static const double G1;
	static const double G2;
	static const int SBODY[];
	static const double SBODYPNT[][3];
	double _tFinal;
	double _tcRise;
	double _tcFall;
	double _jdamp;
	int _sBodies[rdUTWalking8_NS];
	double _sPoints[rdUTWalking8_NS][3];

protected:
	/** Whether or not to draw the model. */
	bool _draw;
	/** Allow the left foot to contact the ground. */
	bool _allowLeftContact;
	/** Controls (muscle excitations). */
	Array<double> _xUT;
	/** States stored at the node times. */
	double *_ynode;
	/** State names. */
	Array<std::string> _yNames;
	/** Initial states. */
	Array<double> _yiUT;
	/** States. */
	double *_y;
	/** Initial pseudo-states. */
	Array<double> _ypiUT;
	/** Pseudo-states.  These are the spring zeros. */
	double *_yp;
	/** Ligament torques. */
	double *_tqlig;
	/** Actuator lengths. */
	double *_actlen;
	/** Actuator shortening velocities. */
	double *_actsv;
	/** Spring positions. */
	double _spos[rdUTWalking8_NS][3];
	/** Spring velocities. */
	double _svel[rdUTWalking8_NS][3];
	/** Spring forces. */
	double _sfrc[rdUTWalking8_NS][3];
	bool _store;
	/** Flag to turn off application of contact forces **/
	bool _allowApplyContactForces;

public:
	//Storage *_svelStore;
	//Storage *_sposStore;
	//Storage *_sfrcStore;
	//Storage *_bfrcStore;
	//Storage *_sxoStore;
	//Storage *_szoStore;
	//Storage *_actlenStore;
	//Storage *_actsvStore;
	//Storage *_actfrcStore;
	//Storage *_actpowStore;

//=============================================================================
// METHODS
//=============================================================================
public:
	virtual ~rdUTWalking8();
	rdUTWalking8(const AbsActuatorSet *aActuatorSet=NULL,
		const ContactForceSet *aContactSet=NULL);
protected:
	void initializeParameters();
	void initializeUTInitialStates();
	void constructNames();
	void setSpringZeros();

public:
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	// NUMBERS OF THINGS
	virtual int getNX() const;
	virtual int getNA() const;
	virtual int getNP() const;
	virtual int getNY() const;
	virtual int getNYP() const;
	// NAMES
	virtual std::string getActuatorName(int aIndex) const;
	virtual std::string getControlName(int aIndex) const;
	virtual std::string getStateName(int aIndex) const;
	virtual std::string getPseudoStateName(int aIndex) const;
	// INDICES
	virtual int getActuatorIndex(const std::string &aName) const;
	virtual int getControlIndex(const std::string &aName) const;
	virtual int getStateIndex(const std::string &aName) const;
	virtual int getPseudoStateIndex(const std::string &aName) const;
	// CONTROLS
	virtual void setControls(const double aX[]);
	virtual void getControls(double rX[]) const;
	virtual double getControl(int aIndex) const;
	// INITIAL STATES
	virtual void setInitialStates(const double aYI[]);
	virtual void getInitialStates(double rYI[]) const;
	// STATES
	virtual void setStates(const double aY[]);
	virtual void getStates(double rY[]) const;
	virtual double getState(int aIndex) const;
	// INITIAL PSEUDO-STATES
	virtual void setInitialPseudoStates(const double aYI[]);
	virtual void getInitialPseudoStates(double rYI[]) const;
	// PSEUDO-STATES
	virtual void setPseudoStates(const double aYP[]);
	virtual void getPseudoStates(double rYP[]) const;
	virtual double getPseudoState(int aIndex) const;
	// PARAMETERS
	void setFOM(int aMuscle,double aFOM);
	double getFOM(int aMuscle) const;
	void setTRise(double aT);
	double getTRise() const;
	void setTFall(double aT);
	double getTFall() const;
	// STORAGE
	void setStore(bool aTrueFalse);
	bool getStore();
	// GRAPHICS
	void setDraw(bool aTrueFalse);
	bool getDraw();


	//--------------------------------------------------------------------------
	// ACTUATION
	//--------------------------------------------------------------------------
	virtual void computeActuation();
	virtual void computeMuscleForces();
	virtual void computeLigamentTorques();
	virtual void computeLigamentTorques(double *qang,double *u,double *trq);
	virtual void applyActuatorForce(int aID);
	virtual void applyActuatorForces();
	virtual void setActuatorForce(int aID,double aForce);
	virtual double getActuatorForce(int aID) const;
	virtual double getActuatorStress(int aID) const;
	virtual double getActuatorSpeed(int aID) const;
	virtual double getActuatorPower(int aID) const;
protected:
	virtual void applyMuscleForces();
	virtual void applyLigamentTorque(int aID=-1);

	//--------------------------------------------------------------------------
	// CONTACT
	//--------------------------------------------------------------------------
public:
	void setAllowLeftContact(bool aTrueFalse);
	bool getAllowLeftContact() const;
	virtual void computeContact();
	virtual void computeSpringPointKinematics(double aVel[][3],double aPos[][3]);
	virtual void computeGroundForces(const double aVel[][3],
			const double aPos[][3],double aFrc[][3]);
	virtual void limitGroundForces(double aFrc[][3]);
	//virtual void estimateGroundForces(double dt,double t,double *x,double *y,
	//		double aFrc[][3]);
	virtual void updateGroundZeros(double svel[][3],double spos[][3],
			double sfrc[][3]);
	virtual void setGroundZerosToCurrentPosition(double t,double *y);
	virtual void computeResultantBodyForces(double aFE[][3],double aFB[][6]);
	virtual void applyContactForce(int aID);
	virtual void applyContactForces();
	virtual AbstractBody* getContactBodyA(int aID) const;
	virtual AbstractBody* getContactBodyB(int aID) const;
	virtual void setContactPointA(int aID,const double rPoint[3]);
	virtual void getContactPointA(int aID,double rPoint[3]) const;
	virtual void setContactPointB(int aID,const double rPoint[3]);
	virtual void getContactPointB(int aID,double rPoint[3]) const;
	virtual void getContactForce(int aID,double rForce[3]) const;
	virtual void
		getContactStiffness(int aID,const double aDX[3],double rDF[3]) const;
	virtual void
		getContactViscosity(int aID,const double aDV[3],double rDF[3]) const;
	virtual double getContactForce(int aID) const;
	virtual double getContactSpeed(int aID) const;
	virtual double getContactPower(int aID) const;
	void setAllowApplyContactForces(bool aTrueFalse);
	bool getAllowApplyContactForces() const;

	//--------------------------------------------------------------------------
	// DERIVATIVES
	//--------------------------------------------------------------------------
	virtual void
		computeAuxiliaryDerivatives(double *dydt);

	//--------------------------------------------------------------------------
	// UTILITY
	//--------------------------------------------------------------------------
	void promoteControlsToStates(const double aX[],double aDT);

	//--------------------------------------------------------------------------
	// GRAPHICS
	//--------------------------------------------------------------------------
	int draw(double t,double *x,double *y);
	int draw(double t,double *x,double *y,double *sfrc,double *spnt);
	void setMuson(int aMus,int aOnOff);

//=============================================================================
};	// END of class rdUTWalking8

}; //namespace
//=============================================================================
//=============================================================================


#endif // #ifndef __rdUTWalking8_h__
