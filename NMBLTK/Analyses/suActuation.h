// suActuation.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suActuation_h__
#define __suActuation_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Tools/rdStorage.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include <NMBLTK/Simulation/Model/rdAnalysis.h>
#include "suAnalysesDLL.h"


#ifdef SWIG
	#ifdef SUANALYSES_API
		#undef SUANALYSES_API
		#define SUANALYSES_API
	#endif
#endif
//=============================================================================
//=============================================================================
/**
 * A class for recording the basic actuator information for a model
 * during a simulation.
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class SUANALYSES_API suActuation : public rdAnalysis 
{
//=============================================================================
// DATA
//=============================================================================
private:

protected:
	/** Number of actuators. */
	int _na;
	/** Work array for storing forces, speeds, or powers. */
	double *_fsp;
	/** Force storage. */
	rdStorage *_forceStore;
	/** Speed storage. */
	rdStorage *_speedStore;
	/** Power storage. */
	rdStorage *_powerStore;

//=============================================================================
// METHODS
//=============================================================================
public:
	suActuation(rdModel *aModel=0);
	suActuation(const std::string &aFileName);
	suActuation(DOMElement *aElement);
	// Copy constrctor and virtual copy 
	suActuation(const suActuation &aObject);
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;
	virtual ~suActuation();
private:
	void setNull();
	void constructDescription();
	void constructColumnLabels();
	void allocateStorage();
	void deleteStorage();

public:
	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
#ifndef SWIG
	suActuation& operator=(const suActuation &aActuation);
#endif
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	// STORAGE
	void setStorageCapacityIncrements(int aIncrement);
	rdStorage* getForceStorage() const;
	rdStorage* getSpeedStorage() const;
	rdStorage* getPowerStorage() const;
	// MODEL
	virtual void setModel(rdModel *aModel);

	//--------------------------------------------------------------------------
	// ANALYSIS
	//--------------------------------------------------------------------------
	virtual int
		begin(int aStep,double aDT,double aT,double *aX,double *aY,
		void *aClientData=NULL);
	virtual int
		step(double *aXPrev,double *aYPrev,
		int aStep,double aDT,double aT,double *aX,double *aY,
		void *aClientData=NULL);
	virtual int
		end(int aStep,double aDT,double aT,double *aX,double *aY,
		void *aClientData=NULL);
protected:
	virtual int
		record(double aT,double *aX,double *aY);

	//--------------------------------------------------------------------------
	// IO
	//--------------------------------------------------------------------------
public:
	virtual int
		printResults(const char *aBaseName,const char *aDir=NULL,
		double aDT=-1.0,const char *aExtension=".sto");

//=============================================================================
};	// END of class suActuation
//=============================================================================
//=============================================================================


#endif // #ifndef __suActuation_h__
