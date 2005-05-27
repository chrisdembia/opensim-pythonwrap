// cgmalWalking01.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __cgmalWalking01_h__
#define __cgmalWalking01_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include <NMBLTK/Simulation/SDFast/rdSDFastDLL.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include <NMBLTK/Simulation/SDFast/rdSDFast.h>
#include <NMBLTK/Simulation/SDFast/rdActuatedModel_SDFast.h>


//=============================================================================
//=============================================================================
/**
 * A class which represents a point mass free to move in one dimension.
 */
class RDSDFAST_API cgmalWalking01 : public rdActuatedModel_SDFast
{
//=============================================================================
// DATA
//=============================================================================
public:

//=============================================================================
// METHODS
//=============================================================================
public:
	cgmalWalking01(rdActuatorSet *aActuatorSet=NULL,rdContactForceSet *aContacts=NULL);
	virtual ~cgmalWalking01();
private:
	void setNull();
	void constructInitialStates();
	void constructNames();
	void constructGeometry();
public:
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------

//=============================================================================
};	// END of class cgmalWalking01
//=============================================================================
//=============================================================================


#endif // #ifndef __cgmalWalking01_h__
