// suSlider.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Authors:  Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suSlider_h__
#define __suSlider_h__


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
class RDSDFAST_API suSlider : public rdActuatedModel_SDFast
{
//=============================================================================
// DATA
//=============================================================================
public:

//=============================================================================
// METHODS
//=============================================================================
	suSlider(rdActuatorSet *aActuators=NULL,rdContactForceSet *aContacts=NULL);
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
//=============================================================================
//=============================================================================


#endif // #ifndef __suSlider_h__
