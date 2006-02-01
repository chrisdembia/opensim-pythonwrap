// _Template_.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Authors:  Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef ___Template__h__
#define ___Template__h__


//=============================================================================
// INCLUDES
//=============================================================================
#include <NMBLTK/Models/SIMMPipeline/4.0/Pipeline40Workflow/suPipeline40Workflow.h>


//=============================================================================
//=============================================================================

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
		rdActuatorSet *aActuators=0,rdContactForceSet *aContacts=0);
	virtual ~_Template_();
private:
	void setNull();

//=============================================================================
};	// END of class _Template_
//=============================================================================
//=============================================================================


//=============================================================================
// STATIC METHOD FOR CREATING THIS MODEL
//=============================================================================
extern "C" {
RDSDFAST_API rdModel* CreateModel();
RDSDFAST_API rdModel* CreateModel_File(const std::string &aModelFile);
RDSDFAST_API rdModel* CreateModel_ActuatorsContacts(rdActuatorSet *aActuatorSet,rdContactForceSet *aContactSet);
RDSDFAST_API rdModel* CreateModel_ParamsActuatorsContacts(const std::string &aParamsFile,rdActuatorSet *aActuatorSet,rdContactForceSet *aContactSet);
}


#endif // #ifndef ___Template__h__
