#ifndef _Pipeline40Workflow_h_
#define _Pipeline40Workflow_h_
// Pipeline40Workflow.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Authors:  Ayman Habib
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include <OpenSim/Models/SIMMPipeline/4.0/suPipeline40/suPipeline40.h>



//=============================================================================
//=============================================================================
/**
 * A class that wraps Pipeline40 and includes changes made by
 * Darryl and Clay to support CMC, REA, RRA
 *
 * @author Ayman Habib, Clay Anderson
 * @version 1.0
 */

namespace OpenSim { 

class RDSDFAST_API suPipeline40Workflow : public suPipeline40
{
//=============================================================================
// DATA
//=============================================================================
public:

//=============================================================================
// METHODS
//=============================================================================
	suPipeline40Workflow(const std::string &aParametersFileName,
		ActuatorSet *aActuators=0,ContactForceSet *aContacts=0);
	virtual ~suPipeline40Workflow();
public:
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	virtual void initPipeline(const std::string &workpath, const std::string &paramfile);

	//--------------------------------------------------------------------------
	// FOR RRA - ADDED BY CHAND, 2/3/2006
	//--------------------------------------------------------------------------
	virtual void computeConstrainedCoordinates(double* y);

//=============================================================================
};	// END of class Pipeline40Workflow

}; //namespace
//=============================================================================
//=============================================================================


#endif // #ifndef __Pipeline40Workflow_h__
