// suGeneralizedForces.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson & Saryn Goldberg
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suGeneralizedForces_h__
#define __suGeneralizedForces_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include <RD/Tools/rdMath.h>
#include <RD/Tools/rdTools.h>
#include <RD/Simulation/Model/rdModel.h>
#include <RD/Simulation/Model/rdAnalysis.h>
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
	suGeneralizedForces(rdModel *aModel);
	virtual ~suGeneralizedForces();
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
