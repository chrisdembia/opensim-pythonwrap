// rdAnalysisSet.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdAnalysisSet_h__
#define __rdAnalysisSet_h__


// INCLUDES
#include "rdModel.h"
#include "rdIntegCallbackSet.h"
#include "rdAnalysis.h"


//=============================================================================
//=============================================================================
/**
 * A class for holding and managing a set of integration callbacks for
 * a model.
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class RDSIMULATION_API rdAnalysisSet : public rdIntegCallbackSet 
{

//=============================================================================
// DATA
//=============================================================================
public:
protected:

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdAnalysisSet(rdModel *aModel=0);
	virtual ~rdAnalysisSet();
private:
	void setNull();
public:

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	rdAnalysis* getAnalysis(int aIndex) const;

	//--------------------------------------------------------------------------
	// RESULTS
	//--------------------------------------------------------------------------
	virtual void
		printResults(const char *aBaseName,const char *aPath=NULL,
		double aDT=-1.0,const char *aExtension=".sto");


//=============================================================================
};	// END of class rdAnalysisSet
//=============================================================================
//=============================================================================

#endif // __rdAnalysisSet_h__


