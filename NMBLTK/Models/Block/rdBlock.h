// rdBlock.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2000 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdBlock_h__
#define __rdBlock_h__


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
class RDSDFAST_API rdBlock : public rdActuatedModel_SDFast
{
//=============================================================================
// DATA
//=============================================================================
public:

//=============================================================================
// METHODS
//=============================================================================
public:
	rdBlock(rdActuatorSet *aActuatorSet=NULL,rdContactForceSet *aContacts=NULL);
	rdBlock(const std::string &aFileName,
		rdActuatorSet *aActuatorSet=NULL,rdContactForceSet *aContacts=NULL);
	virtual ~rdBlock();
	static void RegisterTypes();
private:
	void setNull();
	void constructInitialStates();
	void constructNames();
	void constructGeometry();
//=============================================================================
};	// END of class rdBlock
//=============================================================================
//=============================================================================


#endif // #ifndef __rdBlock_h__
