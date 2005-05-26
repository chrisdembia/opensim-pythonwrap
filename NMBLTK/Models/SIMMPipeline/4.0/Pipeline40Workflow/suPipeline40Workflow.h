// suPipeline40Workflow.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Authors:  Ayman Habib
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suPipeline40Workflow_h__
#define __suPipeline40Workflow_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include <SU/Models/SIMMPipeline/4.0/suPipeline40/suPipeline40.h>


//=============================================================================
//=============================================================================
/**
 * A class that wraps suPipeline40 and includes changes made by
 * Darryl and Clay to support CMC, REA, RRA
 *
 * @author Ayman Habib, Clay Anderson
 * @version 1.0
 */

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
		rdActuatorSet *aActuators=0,rdContactForceSet *aContacts=0);
	virtual ~suPipeline40Workflow();
public:
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	virtual void initPipeline(const std::string &workpath, const std::string &paramfile);
	// DERIVATIVES
	virtual int deriv(double t,double *xt,double *y,double *dy);

//=============================================================================
};	// END of class suPipeline40Workflow
//=============================================================================
//=============================================================================


#endif // #ifndef __suPipeline40Workflow_h__
