// suPipeline40Workflow.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Author:  Ayman Habib
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================

#include <cstdio>
#include <NMBLTK/Models/SIMMPipeline/4.0/suPipeline40/suPipeline40.h>
#include <NMBLTK/Models/SIMMPipeline/4.0/suPipeline40/suPipeline40-helper.h>
#include "suPipeline40Workflow.h"
#include "suPipeline40Workflow-helper.h"

using namespace std;
//=============================================================================
// CONSTANTS
//=============================================================================



//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
suPipeline40Workflow::~suPipeline40Workflow()
{
}
//_____________________________________________________________________________
/**
 * Default constructor.
 */
suPipeline40Workflow::
suPipeline40Workflow(const std::string &aParametersFileName,
	rdActuatorSet *aActuators,rdContactForceSet *aContacts) :
	suPipeline40("",aParametersFileName,aActuators,aContacts,false)
{
	initPipeline("", aParametersFileName);
}


//_____________________________________________________________________________
/**
 * Initialize the SIMM Dynamics Pipeline.
 */
void suPipeline40Workflow::
initPipeline(const std::string &workpath, const std::string &paramfile)
{
	// PIPELINE INITIALIZATION
	try {
      string path = workpath + '/';
      string file = paramfile;

	  cout<<"\n\nStartup file = "<<file<<endl<<endl;
      DP_MainStartup_Workflow(_dpd,path.c_str(),file.c_str() ); // populate globals and dpd_

	// ERROR - SHOULD EXIT
   } catch (...) {

		cout<<"\n\nThe SIMM Dynamics Pipeline did not initialize properly.";
		cout<<endl<<endl;
      cleanup();

		string msg = "Pipeline initialization failure.";
		throw rdException(msg,__FILE__,__LINE__);
   }  
	
	// INITIAL STATES
   constructInitialStates();
   
   // CONSTRUCT NAMES
   constructNames();
}


//=============================================================================
// GET AND SET
//=============================================================================
