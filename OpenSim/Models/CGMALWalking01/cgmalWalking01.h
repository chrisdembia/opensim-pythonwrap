#ifndef _cgmalWalking01_h_
#define _cgmalWalking01_h_
// cgmalWalking01.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include <OpenSim/Simulation/SDFast/rdSDFastDLL.h>
#include <OpenSim/Simulation/Model/Model.h>
#include <OpenSim/Simulation/SDFast/rdSDFast.h>
#include <OpenSim/Simulation/SDFast/ActuatedModel_SDFast.h>


//=============================================================================
//=============================================================================
/**
 * A class which represents a point mass free to move in one dimension.
 */
namespace OpenSim { 

class RDSDFAST_API cgmalWalking01 : public ActuatedModel_SDFast
{
//=============================================================================
// DATA
//=============================================================================
public:

//=============================================================================
// METHODS
//=============================================================================
public:
	cgmalWalking01(ActuatorSet *aActuatorSet=NULL,ContactForceSet *aContacts=NULL);
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
};

}; //namespace

//=============================================================================
//=============================================================================


//=============================================================================
// STATIC METHOD FOR CREATING THIS MODEL
//=============================================================================
extern "C" {
RDSDFAST_API OpenSim::Model* CreateModel();
}



#endif // #ifndef __cgmalWalking01_h__
