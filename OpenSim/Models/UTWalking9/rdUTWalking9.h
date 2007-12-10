#ifndef _rdUTWalking9_h_
#define _rdUTWalking9_h_
// rdUTWalking9.h
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
