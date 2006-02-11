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
#include <string>
#include <NMBLTK/Tools/rdSet.h>
#include "rdModel.h"
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
class RDSIMULATION_API rdAnalysisSet : public rdSet<rdAnalysis>
{
//=============================================================================
// DATA
//=============================================================================
protected:
	/** Model on which the callbacks have been set. */
	rdModel *_model;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdAnalysisSet(rdModel *aModel=0);
	rdAnalysisSet(const std::string &aFileName);
	rdAnalysisSet(DOMElement *aElement);
	rdAnalysisSet(const rdAnalysisSet &aSet);
	virtual ~rdAnalysisSet();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;
private:
	void setNull();
public:

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	void setModel(rdModel *aModel);
	rdModel* getModel();
	void setOn(bool aTrueFalse);

	//--------------------------------------------------------------------------
	// CALLBACKS
	//--------------------------------------------------------------------------
	virtual void
		begin(int aStep,double aDT,double aT,
		double *aX,double *aY,void *aClientData=NULL);
	virtual void
		step(double *aXPrev,double *aYPrev,int aStep,double aDT,double aT,
		double *aX,double *aY,void *aClientData=NULL);
	virtual void
		end(int aStep,double aDT,double aT,
		double *aX,double *aY,void *aClientData=NULL);

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


