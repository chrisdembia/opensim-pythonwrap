// suAnalysisFactory
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2004 Stanford University
// All rights reserved.
//
// Author: Ayman Habib
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suAnalysisFactory_h__
#define __suAnalysisFactory_h__
#include "suAnalysesDLL.h"

#ifdef SWIG
	#ifdef SUANALYSES_API
		#undef SUANALYSES_API
		#define SUANALYSES_API
	#endif
#endif

#include <NMBLTK/Simulation/Model/rdAnalysisSet.h>
#include <NMBLTK/Simulation/rdSimulationDLL.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
//=============================================================================
//=============================================================================
/**
 *
 * A factory class to be used to maintain/extend the map of available analyses
 * The class is implemented following the Singleton pattern (to make sure a single instance
 * of the class lives in the system).
 * Singleton Pattern (Design Patterns GoF)
 *
 * suAnalysisFactory instantiates the factory for and makes registered analyses available 
 * for users. All created analyses will implement the rdAnalysis interface (virtual functions)
 * and clients will not care about which concrete analysis class is in use.
 *
 * @version 1.0
 * @author Ayman Habib
 */

class rdAnalysis;

class SUANALYSES_API suAnalysisFactory
{
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// DATA
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
private:
	static suAnalysisFactory *_factoryInstance;
	rdArrayPtrs<rdAnalysis> _analysesList;
	/** Name to be shown by the UI */
	static std::string _displayName;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// METHODS
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=============================================================================
// CONTRUCTION
//=============================================================================
protected:
	suAnalysisFactory(rdModel *aModel);   //Protected constructor as per singletons
public:
	virtual ~suAnalysisFactory();	
	/** No need for the virtual modifier for now but in case 
	 * A class is written that derives from suAnalysisFactory */

	/** Singleton support. Sole method to instantiate and access suAnalysisFactory*/
	static suAnalysisFactory*	getInstance(rdModel *aModel);

	/** Factory method used to create Analyses of specified name */
	rdAnalysis*  createAnalysis(const std::string &aAnalysisName) const;

	/** Register an analysis type with the fcatory so that it can be instantiated later */
	bool registerAnalysis(rdAnalysis *aAnalysis);

	// Name for display purposes
	const std::string& toString() const;

	const rdArrayPtrs<rdAnalysis> &getRegisteredAnalyses() const;
protected:
	// Method to find out if an aAnalysisName is already registered */
	bool  analysisExists(const std::string &aAnalysisName) const;

//=============================================================================
};	// END of class suAnalysisFactory
//=============================================================================
//=============================================================================


#endif //__suAnalysisFactory_h__
