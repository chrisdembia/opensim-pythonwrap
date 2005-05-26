// suActuatorGeneralizedForces.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson & Saryn Goldberg
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suActuatorGeneralizedForces_h__
#define __suActuatorGeneralizedForces_h__


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
 * A class for recording the generalized force due to an actuator or set of actuators..
 *
 * @author Frank C. Anderson & Saryn Goldberg
 * @version 1.0
 */
class SUANALYSES_API suActuatorGeneralizedForces : public rdAnalysis 
{
//=============================================================================
// DATA
//=============================================================================
public:


protected:
	double *_dqdt;
	double *_dudt;
	rdArray<int> _actuatorList;
	double *_actuatorGenForces;
	rdStorage *_actuatorGenForcesStore;

//=============================================================================
// METHODS
//=============================================================================
public:
	suActuatorGeneralizedForces(rdModel *aModel,const rdArray<int> &aActuatorList);
	virtual ~suActuatorGeneralizedForces();
private:
	void constructDescription();
	void constructColumnLabels();
	void allocateStorage();

public:
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	// STORAGE
	void setStorageCapacityIncrements(int aIncrement);
	rdStorage* getActuatorGenForcesStorage();

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
};	// END of class suActuatorGeneralizedForces
//=============================================================================
//=============================================================================


#endif // #ifndef __suActuatorGeneralizedForces_h__
