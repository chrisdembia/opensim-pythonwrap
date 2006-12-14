#ifndef _suS26_h_
#define _suS26_h_
// suS26.h
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

class RDSDFAST_API suS26 : public suPipeline40Workflow
{
//=============================================================================
// DATA
//=============================================================================
public:

//=============================================================================
// METHODS
//=============================================================================
	suS26(const std::string &aParametersFileName,ContactForceSet *aContacts=0);
	virtual ~suS26();
private:
	void setNull();

public:
	void constructGeometry();
	static void RegisterTypes();
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------

//=============================================================================

};	// END of class suS26

}; //namespace

//=============================================================================
//=============================================================================


#endif // #ifndef __suS26_h__
