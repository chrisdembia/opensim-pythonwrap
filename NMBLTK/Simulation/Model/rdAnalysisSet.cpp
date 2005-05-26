// rdAnalysisSet.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include "rdAnalysisSet.h"


//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 * Note that the individual callbacks are not deleted by
 * this destructor.  To delete the callbacks, the caller must do so
 * individually, or the method rdCallback::deleteCallbacks() may be called.
 */
rdAnalysisSet::~rdAnalysisSet()
{
}
//_____________________________________________________________________________
/**
 * Construct an empty callback set for a model.
 */
rdAnalysisSet::rdAnalysisSet(rdModel *aModel) :
	rdIntegCallbackSet(aModel)
{
	// NULL
	setNull();
}


//=============================================================================
// CONSTRUCTION AND DESTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set the data members of this actuator to their null values.
 */
void rdAnalysisSet::
setNull()
{
	// TYPE
	setType("rdAnalysisSet");

	// MODEL 
	//_model = NULL;
}


//=============================================================================
// GET AND SET
//=============================================================================
//-----------------------------------------------------------------------------
// ANALYSIS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the analysis at a specified index.  This method uses the method
 * rdArrayPtrs::get() and casts the returned void pointer as an
 * rdAnalysis.
 *
 * @param aIndex Array index of the callback to be returned.
 * @return Callback at index aIndex.
 */
rdAnalysis* rdAnalysisSet::
getAnalysis(int aIndex) const
{
	return((rdAnalysis*)get(aIndex));
}


//=============================================================================
// RESULTS
//=============================================================================
//_____________________________________________________________________________
/**
 * Print the results of all analyses in the set.
 *
 * @param aIndex Array index of the callback to be returned.
 * @return Callback at index aIndex.
 */
void rdAnalysisSet::
printResults(const char *aBaseName,const char *aDir,double aDT,
				 const char *aExtension)
{
	int i;
	int size = getSize();
	rdAnalysis *analysis;
	for(i=0;i<size;i++) {
		analysis = getAnalysis(i);
		if(analysis==NULL) continue;
		analysis->printResults(aBaseName,aDir,aDT,aExtension);
	}
}
