// rdAnalysis.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2001 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//============================================================================
#ifndef __rdAnalysis_h__
#define __rdAnalysis_h__

#include "rdIntegCallback.h"
#include <RD/Tools/rdPropertyBool.h>
#include <RD/Tools/rdPropertyStr.h>
#include <RD/Tools/rdPropertyInt.h>

class rdXMLDocument;


//=============================================================================
//=============================================================================
/**
 * An abstract class for specifying the interface for an analysis
 * plugin.
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class RDSIMULATION_API rdAnalysis: public rdIntegCallback
{
public:
	enum { DESCRIP_LENGTH=8192 };

//=============================================================================
// DATA
//=============================================================================
private:
	/** Whether or not to write output of angles in degrees. */
	rdPropertyBool _inDegreesProp;
	bool &_inDegrees;

	/** Column labels. */
	rdPropertyStr _labelsProp;
	std::string &_labels;

	/** Step interval at which analysis results are stored. */
	rdPropertyInt _storageIntervalProp;
	int &_storageInterval;

//=============================================================================
// METHODS
//=============================================================================
private:
	void setNull();
	void setupProperties();
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdAnalysis(rdModel *aModel=0);
	rdAnalysis(const std::string &aFileName);
	rdAnalysis(DOMElement *aElement);
	virtual ~rdAnalysis();
	// Copy constrctor and virtual copy 
	rdAnalysis(const rdAnalysis &aObject);
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
#ifndef SWIG
	rdAnalysis& operator=(const rdAnalysis &aAnalysis);
#endif

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	// MODEL
	virtual void setModel(rdModel *aModel);
	// DEGREES/RADIANS
	void setInDegrees(bool aTrueFalse);
	bool getInDegrees() const;
	// COLUMN LABLES
	void setColumnLabels(const char *aLabels);
	const char* getColumnLabels() const;
	// STORAGE INTERVAL
	void setStorageInterval(int aInterval);
	int getStorageInterval() const;

	//--------------------------------------------------------------------------
	// ANALYSIS
	//--------------------------------------------------------------------------
	virtual bool
		proceed(int aStep=0);

	//--------------------------------------------------------------------------
	// RESULTS
	//--------------------------------------------------------------------------
	virtual int
		printResults(const char *aBaseName,const char *aDir=NULL,
		double aDT=-1.0,const char *aExtension=".sto");

//=============================================================================
};	// END of class rdAnalysis
//=============================================================================
//=============================================================================

#endif // __rdAnalysis_h__


