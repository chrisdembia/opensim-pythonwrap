// suAnalysisFactory
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2004 Stanford University
// All rights reserved.
//=============================================================================
// INCLUDES
//=============================================================================
#include <NMBLTK/Simulation/Model/rdModel.h>
#include <NMBLTK/Simulation/Model/rdAnalysis.h>
#include "suAnalysisFactory.h"
#include "suActuation.h"
#include "suKinematics.h"
#include "suIndAcc.h"
#include "suGeneralizedForces.h"

using namespace std;
//=============================================================================
// STATICS
//=============================================================================
suAnalysisFactory *suAnalysisFactory::_factoryInstance=0;
std::string suAnalysisFactory::_displayName = "Analysis Manager";

//_____________________________________________________________________________
/**
 * Default constructor.
 *
 * clears the list of available analyses
 */
suAnalysisFactory::suAnalysisFactory(rdModel *aModel)
{
	_analysesList.setSize(0);
	rdAnalysis *analysis = new suActuation(aModel);
	analysis->setOn(false);
	registerAnalysis(analysis);
	analysis = new suKinematics(aModel);
	analysis->setOn(false);
	registerAnalysis(analysis);
	analysis = new suGeneralizedForces(aModel);
	analysis->setOn(false);
	registerAnalysis(analysis);
}

//_____________________________________________________________________________
/**
 * Destructor.
 *
 * erases the list of available analyses and frees up memory used by them
 */
suAnalysisFactory::~suAnalysisFactory()
{
}
//_____________________________________________________________________________
/**
 * getInstance
 *
 * Method to obtain the sole instance of suAnalysisFactory. Uses lazy evaluation
 * so that the suAnalysisFactory is created only on demand. If we decide to have 
 * more than one instance of the suAnalysisFactory this's the place to change.
 * Clients of this class get access to suAnalysisFactory only through the call
 * to the static method suAnalysisFactory::getInstance()
 */
suAnalysisFactory*	suAnalysisFactory::getInstance(rdModel *aModel)
{
	if (_factoryInstance==0){
		_factoryInstance = new suAnalysisFactory(aModel);
	}
	return _factoryInstance;
}
//_____________________________________________________________________________
/**
 * createAnalysis
 *
 * @parm aAnalysisName is the name of the analysis to construct
 *
 * @return a pointer to a newly instantiated rdAnalysis with name
 * equal to aAnalysisName or 0 if the analysis is not found.
 * 
 * CALLER IS REPONSIBLE FOR FREEING UP RETURNED ANALYSIS
 */
rdAnalysis*  suAnalysisFactory::createAnalysis(const string &aAnalysisType) const
{
	bool found = false;
	rdAnalysis *retAnalysis=0;

	for(int i=0; i < _analysesList.getSize() && !found; i++){
		const rdAnalysis *nextAnalysis = _analysesList.get(i);
		if (nextAnalysis->getType()==aAnalysisType){
			found=true;
			retAnalysis = (rdAnalysis *)nextAnalysis->copy();
		}
	}
	return retAnalysis;
}

//_____________________________________________________________________________
/**
 * analysisExists
 *
 * @parm aAnalysisName is the Name of the analysis to construct
 *
 * @return a pointer to a newly instantiated rdAnalysis with name
 * (case insitive) equal to aAnalysisName or 0 if the analysis is not found.
 * 
 */
bool  suAnalysisFactory::analysisExists(const std::string &aAnalysisName) const
{
	bool found = false;

	for(int i=0; i < _analysesList.getSize() && !found; i++){
		found=(_analysesList[i]->getName()==aAnalysisName);
	}
	return found;
}


//_____________________________________________________________________________
/**
 * registerAnalysis registers an instance of an rdAnalysis for future use by
 * the framework.
 *
 * @parm aAnalysis pointer to analysis to be registered
 *
 * @return bool on success of registration, false otherwise. Main reason registration 
 * can fail is if the name already exists
 */
bool suAnalysisFactory::registerAnalysis(rdAnalysis *aAnalysis)
{
	const std::string& analysisName = aAnalysis->getType();
	bool success=false;
	if (analysisExists(analysisName)==false){
		_analysesList.append(aAnalysis);
		success=true;
	}
	return success;
}
//_____________________________________________________________________________
/**
 * getRegisteredAnalyses returns an const ref to the set of rdAnalysis registered with
 * the factory.
 *
 *
 * Users should not change the list directly, they should use the registeration 
 * mechanism instead (that's why the return value is const)
 */
const rdArrayPtrs<rdAnalysis>& suAnalysisFactory::
getRegisteredAnalyses() const
{
	return _analysesList;
}
//_____________________________________________________________________________
/**
 * Get the name of the factory
 *
 * @return name of suAnalysisFactory
 */

const std::string& suAnalysisFactory::
toString() const
{
	return (_displayName);
}
