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

using namespace std;


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
 * Construct an empty analysis set.
 *
 * @param aModel Model for the analysis set.
 */
rdAnalysisSet::rdAnalysisSet(rdModel *aModel)
{
	setType("rdAnalysisSet");
	setNull();
}
//_____________________________________________________________________________
/**
 * Construct an analysis set from file.
 *
 * @param aFileName Name of the file.
 */
rdAnalysisSet::rdAnalysisSet(const string &aFileName) :
	rdSet<rdAnalysis>(aFileName)
{
	setType("rdAnalysisSet");
	setNull();
	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Construct from a DOM element.
 *
 * @param aElement DOM element
 */
rdAnalysisSet::rdAnalysisSet(DOMElement *aElement) :
	rdSet<rdAnalysis>(aElement)
{
	setType("rdAnalysisSet");
	setNull();
	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aSet Analysis set to be copied.
 */
rdAnalysisSet::rdAnalysisSet(const rdAnalysisSet &aSet) :
	rdSet<rdAnalysis>(aSet)
{
	setNull();
}
//_____________________________________________________________________________
/**
 * Copy this analysis set.
 *
 * @return Copy of this analysis set.
 */
rdObject* rdAnalysisSet::
copy() const
{
	rdAnalysisSet *set = new rdAnalysisSet(*this);
	return(set);
}
//_____________________________________________________________________________
/**
 * Copy this analysis set and modify the copy so that it is consistent
 * with a specified XML element node.
 *
 * @param aElement XML element. 
 * @return Pointer to a copy of this actuator.
 */
rdObject* rdAnalysisSet::
copy(DOMElement *aElement) const
{
	rdAnalysisSet *set = new rdAnalysisSet(aElement);
	*set = *this;
	set->updateFromXMLNode();
	return(set);
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
}


//=============================================================================
// GET AND SET
//=============================================================================
//_____________________________________________________________________________
/**
 * Set the model for all analyses in the set.
 *
 * @param aModel Pointer to the model.
 */
void rdAnalysisSet::
setModel(rdModel *aModel)
{
	int i;
	int size = getSize();
	rdAnalysis *analysis;
	for(i=0;i<size;i++) {
		analysis = get(i);
		if(analysis==NULL) continue;
		analysis->setModel(aModel);
	}
}
//_____________________________________________________________________________
/**
 * Get a pointer to the model which is actuated.
 *
 * @return Pointer to the model.
 */
rdModel* rdAnalysisSet::
getModel()
{
	return(_model);
}

//-----------------------------------------------------------------------------
// ON & OFF
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set all the callbacks either on or off.
 *
 * @param aTrueFalse Arguement that, if true, results in all callbacks
 * being turned on; if false, all callbacks are turned off.
 */
void rdAnalysisSet::
setOn(bool aTrueFalse)
{
	int i;
	rdCallback *callback;
	for(i=0;i<getSize();i++) {
		callback = get(i);
		if(callback==NULL) continue;
		callback->setOn(aTrueFalse);
	}
}


//=============================================================================
// CALLBACKS
//=============================================================================
//_____________________________________________________________________________
/**
 * Call the begin method for all integration callbacks.  This method is
 * called at the beginning of an integration and is intended to be used for
 * any initializations that are necessary.
 *
 * @param aStep Number of integrations steps that have been completed.
 * @param aDT Size of the integration time step that will be attempted.
 * @param aT Current time in the integration.
 * @param aX Current control values.
 * @param aY Current states.
 * @param aClientData General use pointer for sending in client data.
 */
void rdAnalysisSet::
begin(int aStep,double aDT,double aT,double *aX,double *aY,void *aClientData)
{
	int i;
	rdIntegCallback *callback;
	for(i=0;i<getSize();i++) {
		callback = get(i);
		if(callback == NULL) continue;
		callback->begin(aStep,aDT,aT,aX,aY,aClientData);
	}
}
//_____________________________________________________________________________
/**
 * Call the step method for all integration callbacks.  This method is called
 * after each successful integration time step and is intended to be used for
 * conducting analyses, driving animations, etc.
 *
 * @param aXPrev Control values at the previous time step.
 * @param aYPrev State values at the previous time step.
 * @param aStep Number of integrations steps that have been completed.
 * @param aDT Size of the time step that WAS just completed.
 * @param aT Current time in the integration.
 * @param aX Current control values.
 * @param aY Current states.
 * @param aClientData General use pointer for sending in client data.
 */
void rdAnalysisSet::
step(double *aXPrev,double *aYPrev,int aStep,double aDT,double aT,
	double *aX,double *aY,void *aClientData)
{
	int i;
	rdIntegCallback *callback;
	for(i=0;i<getSize();i++) {
		callback = get(i);
		if(callback == NULL) continue;
		callback->step(aXPrev,aYPrev,aStep,aDT,aT,aX,aY,aClientData);
	}
}
//_____________________________________________________________________________
/**
 * Call the end method for all integration callbacks.  This method is called
 * after an integration has been completed and is intended to be used for
 * performing any finalizations necessary.
 *
 * @param aStep Number of integrations steps that have been completed.
 * @param aDT Size of the time step that WAS just completed.
 * @param aT Current time in the integration.
 * @param aX Current control values.
 * @param aY Current states.
 * @param aClientData General use pointer for sending in client data.
 */
void rdAnalysisSet::
end(int aStep,double aDT,double aT,double *aX,double *aY,void *aClientData)
{
	int i;
	rdIntegCallback *callback;
	for(i=0;i<getSize();i++) {
		callback = get(i);
		if(callback == NULL) continue;
		callback->end(aStep,aDT,aT,aX,aY,aClientData);
	}
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
		analysis = get(i);
		if(analysis==NULL) continue;
		analysis->printResults(aBaseName,aDir,aDT,aExtension);
	}
}
