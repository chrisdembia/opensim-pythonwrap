// rdUTWalking8.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2000 Realistic Dynamics, Inc.
// All rights reserved.
//
// CONFIDENTIAL
//
// The material contain within this file is the sole property of
// Realistic Dynamics, Inc., and may not be read, copied, or distributed
// without the expressed writen consent of Realistic Dynamics, Inc.
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdUTWalking8_h__
#define __rdUTWalking8_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include <RD/Tools/rdTools.h>
//#include <rdStorage.h>
#include <RD/Simulation/SDFast/rdSDFastDLL.h>
#include <RD/Simulation/Model/rdModel.h>
#include <RD/Simulation/SDFast/rdActuatedModel_SDFast.h>

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
class RDSDFAST_API rdUTWalking8 : public rdActuatedModel_SDFast
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
	rdArray<double> _xUT;
	/** States stored at the node times. */
	double *_ynode;
	/** State names. */
	rdArray<std::string> _yNames;
	/** Initial states. */
	rdArray<double> _yiUT;
	/** States. */
	double *_y;
	/** Initial pseudo-states. */
	rdArray<double> _ypiUT;
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
	//rdStorage *_svelStore;
	//rdStorage *_sposStore;
	//rdStorage *_sfrcStore;
	//rdStorage *_bfrcStore;
	//rdStorage *_sxoStore;
	//rdStorage *_szoStore;
	//rdStorage *_actlenStore;
	//rdStorage *_actsvStore;
	//rdStorage *_actfrcStore;
	//rdStorage *_actpowStore;

//=============================================================================
// METHODS
//=============================================================================
public:
	virtual ~rdUTWalking8();
	rdUTWalking8(const rdActuatorSet *aActuatorSet=NULL,
		const rdContactForceSet *aContactSet=NULL);
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
	virtual int getContactBodyA(int aID) const;
	virtual int getContactBodyB(int aID) const;
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
	virtual int deriv(double t,double *xt,double *y,double *dy);
	virtual int deriv(double t,double *xt,double *y,double *dqdt,double *dudt);

	//--------------------------------------------------------------------------
	// PERFORMANCE
	//--------------------------------------------------------------------------
	//int
	//	computePerformance(double t,double *x,double *y,double *p,void *cd=NULL);

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

	//--------------------------------------------------------------------------
	// IO
	//--------------------------------------------------------------------------
	//virtual void store(double t,double *x,double *y);
	//virtual void printStorage(const char *aPath=NULL,double aDT=-1.0);

	//--------------------------------------------------------------------------
	// CALLBACKS
	//--------------------------------------------------------------------------
	//virtual void
	//	integStepCallback(double *xPrev,double *yPrev,
	//	 int i,double dt,double t,double *x,double *y,
	//	 void *cd=NULL);

//=============================================================================
};	// END of class rdUTWalking8
//=============================================================================
//=============================================================================


#endif // #ifndef __rdUTWalking8_h__
