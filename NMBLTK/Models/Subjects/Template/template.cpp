// _Template_.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Author:  Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================

#include <NMBLTK/Models/SIMMPipeline/4.0/Pipeline40Workflow/suPipeline40Workflow.h>
#include "_Template_.h"

//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
_Template_::~_Template_()
{
}
//_____________________________________________________________________________
/**
 * Default constructor.
 */
_Template_::
_Template_(const std::string &aParametersFileName,
	rdActuatorSet *aActuators,rdContactForceSet *aContacts) :
	suPipeline40Workflow(aParametersFileName,aActuators,aContacts)
{
	setNull();
}


//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Set member variables to their appropriate null values.
 */
void _Template_::
setNull()
{
}


//=============================================================================
// STATIC METHOD FOR CREATING THIS MODEL
//=============================================================================
extern "C" {

RDSDFAST_API rdModel* CreateModel()
{
	_Template_ *model = new _Template_("params.txt");
	return(model);
}

}


