#ifndef _template_h_
#define _template_h_
// _Template_.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Authors:  Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include <OpenSim/Models/SIMMPipeline/4.0/Pipeline40Workflow/suPipeline40Workflow.h>


//=============================================================================
//=============================================================================

namespace OpenSim { 

class RDSDFAST_API _Template_ : public suPipeline40Workflow
{
//=============================================================================
// DATA
//=============================================================================
public:

//=============================================================================
// METHODS
//=============================================================================
	_Template_(const std::string &aParametersFileName,
		ActuatorSet *aActuators=0,ContactForceSet *aContacts=0);
	virtual ~_Template_();
private:
	void setNull();

//=============================================================================
};



//=============================================================================
//=============================================================================


//=============================================================================
// STATIC METHOD FOR CREATING THIS MODEL
//=============================================================================
extern "C" {
	RDSDFAST_API OpenSim::Model* CreateModel();
RDSDFAST_API OpenSim::Model* CreateModel_File(const std::string &aModelFile);
RDSDFAST_API OpenSim::Model* CreateModel_ActuatorsContacts(OpenSim::ActuatorSet *aActuatorSet,OpenSim::ContactForceSet *aContactSet);
RDSDFAST_API OpenSim::Model* CreateModel_ParamsActuatorsContacts(const std::string &aParamsFile,OpenSim::ActuatorSet *aActuatorSet,OpenSim::ContactForceSet *aContactSet);
}

}; //namespace

#endif // #ifndef ___Template__h__
