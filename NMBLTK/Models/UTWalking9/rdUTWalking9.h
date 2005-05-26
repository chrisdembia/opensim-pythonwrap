// rdUTWalking9.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Frank C. Anderson
//	Copyright 2004
// All rights reserved.
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdUTWalking9_h__
#define __rdUTWalking9_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include <RD/Tools/rdTools.h>
//#include <rdStorage.h>
#include <RD/Simulation/SDFast/rdSDFastDLL.h>
#include <RD/Simulation/Model/rdModel.h>
#include <RD/Models/UTWalking8/rdUTWalking8.h>


const int rdUTWalking9_NA = 54;
const int rdUTWalking9_NS = 10;
const int rdUTWalking9_NL = 17;


//=============================================================================
//=============================================================================
/**
 * This model is the same as the rdUTWalking8 model except that the ligaments
 * have been recategorized as passive contact elements as opposed to
 * actuators.  This change affects mainly any analyses that distinguish
 * actuators and contact elements.  The change does not affect the results
 * a the optimal simulation.
 *
 * The model has 23 degrees of freedom: 6 DOF pelvis, 3 DOF back joint,
 * 3 DOF hips, 1 DOF knees, 2 DOF ankles, 1 DOF metatarsal.
 * It is actuated by 54 lumped-parameter muscle-tendon units.
 * The controls of the model are the net excitation levels (0 to 1) of the
 * muscles.  Force interactions between the feet and ground are mediated
 * by 5 spring-and-damper units on the sole of each foot.  Joints are
 * prevented from hyperextending by torsional springs (implemented with
 * exponental functions) at each of the joints.
 */
class RDSDFAST_API rdUTWalking9 : public rdUTWalking8
{
//=============================================================================
// DATA
//=============================================================================
private:
	/** Number of actuators. */
	static const int NA9;
	/** Number of foot-ground springs. */
	static const int NS9;
	/** Number of ligaments. */
	static const int NL9;

//=============================================================================
// METHODS
//=============================================================================
public:
	virtual ~rdUTWalking9();
	rdUTWalking9(const rdActuatorSet *aActuatorSet=NULL,
		const rdContactForceSet *aContactSet=NULL);

public:
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	// NUMBERS OF THINGS
	virtual int getNA() const;
	virtual int getNP() const;
	// NAMES
	virtual std::string getActuatorName(int aIndex) const;

	//--------------------------------------------------------------------------
	// ACTUATION
	//--------------------------------------------------------------------------
	virtual void computeActuation();
	virtual void applyActuatorForce(int aID);
	virtual void applyActuatorForces();
	virtual void setActuatorForce(int aID,double aForce);
	virtual double getActuatorForce(int aID) const;
	virtual double getActuatorStress(int aID) const;
	virtual double getActuatorSpeed(int aID) const;

	//--------------------------------------------------------------------------
	// CONTACT
	//--------------------------------------------------------------------------
public:
	virtual void computeContact();
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

//=============================================================================
};	// END of class rdUTWalking9
//=============================================================================
//=============================================================================


#endif // #ifndef __rdUTWalking9_h__
