#ifndef _suSlider_h_
#define _suSlider_h_
// suSlider.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Authors:  Frank C. Anderson
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
 * A simple model of a block that slides back and forth in the X direction.
 *
 * Bodies:
 * 1) block
 *
 * Generalized Coordinates:
 * 1) X
 *
 * Generalized Speeds:
 * 1) VX
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
namespace OpenSim { 

class RDSDFAST_API suSlider : public ActuatedModel_SDFast
{
//=============================================================================
// DATA
//=============================================================================
public:

//=============================================================================
// METHODS
//=============================================================================
	suSlider(ActuatorSet *aActuators=NULL,ContactForceSet *aContacts=NULL);
	virtual ~suSlider();
private:
	void setNull();
	void constructInitialStates();
	void constructNames();

public:
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------

//=============================================================================
};	// END of class suSlider

}; //namespace
//=============================================================================
//=============================================================================


#endif // #ifndef __suSlider_h__
