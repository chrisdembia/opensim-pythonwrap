#ifndef _rdBlock_h_
#define _rdBlock_h_
// rdBlock.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
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

/* Note: This code was originally developed by Realistic Dynamics Inc. 
 * Author: Frank C. Anderson 
 */


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
 * A class which represents a point mass free to move in one dimension.
 */
namespace OpenSim { 

class RDSDFAST_API rdBlock : public ActuatedModel_SDFast
{
//=============================================================================
// DATA
//=============================================================================
public:

//=============================================================================
// METHODS
//=============================================================================
public:
	rdBlock(ActuatorSet *aActuatorSet=NULL,ContactForceSet *aContacts=NULL);
	rdBlock(const std::string &aFileName,
		ActuatorSet *aActuatorSet=NULL,ContactForceSet *aContacts=NULL);
	virtual ~rdBlock();
	static void RegisterTypes();
private:
	void setNull();
	void constructInitialStates();
	void constructNames();
	void constructGeometry();
//=============================================================================
};	// END of class rdBlock

}; //namespace
//=============================================================================
//=============================================================================


//=============================================================================
// STATIC METHOD FOR CREATING THIS MODEL
//=============================================================================
extern "C" {
RDSDFAST_API OpenSim::Model* CreateModel();
RDSDFAST_API OpenSim::Model* CreateModel_File(const std::string &aModelFile);
RDSDFAST_API OpenSim::Model* CreateModel_ActuatorsContacts(OpenSim::ActuatorSet *aActuatorSet,OpenSim::ContactForceSet *aContactSet);
//RDSDFAST_API Model* CreateModel_ParamsActuatorsContacts(const std::string &aParamsFile,ActuatorSet *aActuatorSet,ContactForceSet *aContactSet);
}

#endif // #ifndef __rdBlock_h__
