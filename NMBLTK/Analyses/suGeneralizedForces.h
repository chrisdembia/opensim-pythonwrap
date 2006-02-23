// suGeneralizedForces.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson & Saryn Goldberg
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suGeneralizedForces_h__
#define __suGeneralizedForces_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include <NMBLTK/Simulation/Model/rdAnalysis.h>
#include "suAnalysesDLL.h"


//=============================================================================
//=============================================================================
/**
 * A class for recording the joint torques of the generalized coordinates
 * of a model during a simulation.
 *
 * @author Frank C. Anderson & Saryn Goldberg
 * @version 1.0
 */
class SUANALYSES_API suGeneralizedForces : public rdAnalysis 
{
//=============================================================================
// DATA
//=============================================================================
private:

protected:
	double *_dqdt;
	double *_dudt;
	double *_zero_aY;
	double *_gravGenForces;
	double *_velGenForces;
	double *_actuatorGenForces;
	double *_contactGenForces;
	rdStorage *_gravGenForcesStore;
	rdStorage *_velGenForcesStore;
	rdStorage *_actuatorGenForcesStore;
	rdStorage *_contactGenForcesStore;

//=============================================================================
// METHODS
//=============================================================================
public:
	suGeneralizedForces(rdModel *aModel=0);
	suGeneralizedForces(const std::string &aFileName);
	suGeneralizedForces(DOMElement *aElement);
	// Copy constrctor and virtual copy 
	suGeneralizedForces(const suGeneralizedForces &aObject);
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;
	virtual ~suGeneralizedForces();
	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
#ifndef SWIG
	suGeneralizedForces& operator=(const suGeneralizedForces &aGeneralizedForces);
#endif
private:
	void constructDescription();
	void constructColumnLabels();
	void allocateStorage();
	void deleteStorage();

public:
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	// STORAGE
	void setStorageCapacityIncrements(int aIncrement);
	rdStorage* getGravGenForcesStorage();
	rdStorage* getVelGenForcesStorage();
	rdStorage* getActuatorGenForcesStorage();
	rdStorage* getContactGenForcesStorage();

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
};	// END of class suGeneralizedForces
//=============================================================================
//=============================================================================


#endif // #ifndef __suGeneralizedForces_h__
