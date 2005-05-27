// suHopper.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Authors:  Ines Barbosa and Clay Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suHopper_h__
#define __suHopper_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include <NMBLTK/Simulation/SDFast/rdSDFastDLL.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include <NMBLTK/Simulation/Model/rdActuatorSet.h>
#include <NMBLTK/Simulation/Model/rdContactForceSet.h>
#include <NMBLTK/Simulation/SDFast/rdSDFast.h>
#include <NMBLTK/Simulation/SDFast/rdActuatedModel_SDFast.h>


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
