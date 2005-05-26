// suHopper.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Authors:  Ines Barbosa and Clay Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suHopper_h__
#define __suHopper_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include <RD/Simulation/SDFast/rdSDFastDLL.h>
#include <RD/Simulation/Model/rdModel.h>
#include <RD/Simulation/Model/rdActuatorSet.h>
#include <RD/Simulation/Model/rdContactForceSet.h>
#include <RD/Simulation/SDFast/rdSDFast.h>
#include <RD/Simulation/SDFast/rdActuatedModel_SDFast.h>


//=============================================================================
//=============================================================================
/**
 * A simple model of a hopping person.
 */
class RDSDFAST_API suHopper : public rdActuatedModel_SDFast
{
//=============================================================================
// DATA
//=============================================================================
public:

//=============================================================================
// METHODS
//=============================================================================
	suHopper(rdActuatorSet *aActuators=NULL,rdContactForceSet *aContacts=NULL);
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
//=============================================================================
//=============================================================================


#endif // #ifndef __suHopper_h__
