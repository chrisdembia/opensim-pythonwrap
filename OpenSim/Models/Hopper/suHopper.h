#ifndef _suHopper_h_
#define _suHopper_h_
// suHopper.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Authors:  Ines Barbosa and Clay Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include <OpenSim/Simulation/SDFast/rdSDFastDLL.h>
#include <OpenSim/Simulation/Model/Model.h>
#include <OpenSim/Simulation/Model/ActuatorSet.h>
#include <OpenSim/Simulation/Model/ContactForceSet.h>
#include <OpenSim/Simulation/SDFast/rdSDFast.h>
#include <OpenSim/Simulation/SDFast/ActuatedModel_SDFast.h>


//=============================================================================
//=============================================================================
/**
 * A simple model of a hopping person.
 */
namespace OpenSim { 

class RDSDFAST_API suHopper : public ActuatedModel_SDFast
{
//=============================================================================
// DATA
//=============================================================================
public:

//=============================================================================
// METHODS
//=============================================================================
	suHopper(ActuatorSet *aActuators=NULL,ContactForceSet *aContacts=NULL);
	virtual ~suHopper();
private:
	void setNull();
	void constructInitialStates();
	void constructNames();

public:
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------

//=============================================================================
};	// END of class suHopper

}; //namespace
//=============================================================================
//=============================================================================


#endif // #ifndef __suHopper_h__
