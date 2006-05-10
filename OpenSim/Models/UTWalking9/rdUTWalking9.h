#ifndef _rdUTWalking9_h_
#define _rdUTWalking9_h_
// rdUTWalking9.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Frank C. Anderson
/*
* Copyright (c) 2005, Stanford University. All rights reserved. 
* Redistribution and use in source and binary forms, with or without 
* modification, are permitted provided that the following conditions
* are met: 
*  - Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer. 
*  - Redistributions in binary form must reproduce the above copyright 
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the distribution. 
*  - Neither the name of the Stanford University nor the names of its 
*    contributors may be used to endorse or promote products derived 
*    from this software without specific prior written permission. 
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN 
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
* POSSIBILITY OF SUCH DAMAGE. 
*/

/*  
 * Author:  
 */


//=============================================================================
// INCLUDES
//=============================================================================
#include <RD/Tools/rdTools.h>
//#include <Storage.h>
#include <RD/Simulation/SDFast/SDFastDLL.h>
#include <RD/Simulation/Model/Model.h>
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
namespace OpenSim { 

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
	rdUTWalking9(const ActuatorSet *aActuatorSet=NULL,
		const ContactForceSet *aContactSet=NULL);

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

}; //namespace
//=============================================================================
//=============================================================================


#endif // #ifndef __rdUTWalking9_h__
