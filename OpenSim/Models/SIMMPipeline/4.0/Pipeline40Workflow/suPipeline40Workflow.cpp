// suPipeline40Workflow.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Author:  Ayman Habib
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================

#include <cstdio>
#include <OpenSim/Models/SIMMPipeline/4.0/suPipeline40/suPipeline40.h>
#include <OpenSim/Models/SIMMPipeline/4.0/suPipeline40/suPipeline40-helper.h>
#include "suPipeline40Workflow.h"
#include "suPipeline40Workflow-helper.h"



using namespace OpenSim;
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
	ActuatorSet *aActuators,ContactForceSet *aContacts) :
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
		throw Exception(msg,__FILE__,__LINE__);
   }  
	
	// INITIAL STATES
   constructInitialStates();
   
   // CONSTRUCT NAMES
   constructNames();
}


//=============================================================================
// GET AND SET
//=============================================================================


//=============================================================================
// FOR RRA - ADDED BY CHAND, 2/3/2006
//=============================================================================
//_____________________________________________________________________________
/**
 * Compute the constrained coordinates for a simulation.
 *
 * @param y Array of states containing all coordinates.
 */
void suPipeline40Workflow::
computeConstrainedCoordinates(double* y)
{
	computeConstrainedCoords(sdm,y);
}
