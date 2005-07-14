// rdAnalysisFactory
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2004 Stanford University
// All rights reserved.
//=============================================================================
// INCLUDES
//=============================================================================
#include "rdAnalysisFactory.h"
#include <NMBLTK/Simulation/Model/rdAnalysis.h>

using namespace std;
//=============================================================================
// STATICS
//=============================================================================
rdAnalysisFactory *rdAnalysisFactory::_factoryInstance=0;
std::string rdAnalysisFactory::_displayName = "Analysis Manager";

//_____________________________________________________________________________
/**
 * Default constructor.
 *
 * clears the list of available analyses
 */
rdAnalysisFactory::rdAnalysisFactory()
{
	_analysesList.setSize(0);
}

//_____________________________________________________________________________
/**
 * Destructor.
 *
 * erases the list of available analyses and frees up memory used by them
 */
rdAnalysisFactory::~rdAnalysisFactory()
{
}
//_____________________________________________________________________________
/**
 * getInstance
 *
 * Method to obtain the sole instance of rdAnalysisFactory. Uses lazy evaluation
 * so that the rdAnalysisFactory is created only on demand. If we decide to have 
 * more than one instance of the rdAnalysisFactory this's the place to change.
 * Clients of this class get access to rdAnalysisFactory only through the call
 * to the static method rdAnalysisFactory::getInstance()
 */
rdAnalysisFactory*	rdAnalysisFactory::getInstance()
{
	if (_factoryInstance==0){
		_factoryInstance = new rdAnalysisFactory();
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
rdAnalysis*  rdAnalysisFactory::createAnalysis(const std::string &aAnalysisName) const
{
	bool found = false;
	rdAnalysis *retAnalysis=0;

	for(int i=0; i < _analysesList.getSize() && !found; i++){
		if (_analysesList[i]->getName()==aAnalysisName){
			found=true;
			retAnalysis = (rdAnalysis *)_analysesList[i]->copy();
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
bool  rdAnalysisFactory::analysisExists(const std::string &aAnalysisName) const
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
bool rdAnalysisFactory::registerAnalysis(rdAnalysis *aAnalysis)
{
	const string& analysisName = aAnalysis->getName();
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
const rdArrayPtrs<rdAnalysis> & rdAnalysisFactory::
getRegisteredAnalyses() const
{
	return _analysesList;
}
//_____________________________________________________________________________
/**
 * Get the name of the factory
 *
 * @return name of rdAnalysisFactory
 */

const std::string& rdAnalysisFactory::
toString() const
{
	return (_displayName);
}

