// su900061.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Authors:  Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __su900061_h__
#define __su900061_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include <NMBLTK/Models/SIMMPipeline/4.0/Pipeline40Workflow/suPipeline40Workflow.h>


//=============================================================================
//=============================================================================

class RDSDFAST_API su900061 : public suPipeline40Workflow
{
//=============================================================================
// DATA
//=============================================================================
public:

//=============================================================================
// METHODS
//=============================================================================
	su900061(const std::string &aParametersFileName,
		rdActuatorSet *aActuators=0,rdContactForceSet *aContacts=0);
	virtual ~su900061();
private:
	void setNull();

//=============================================================================
};	// END of class su900061
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


#endif // #ifndef __su900061_h__
