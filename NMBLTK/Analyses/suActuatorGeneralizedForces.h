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

	// Properties
	rdPropertyStrArray	_propActuatorNames;
	// REFERENCES
	rdArray<std::string>&	_actuatorNames;	
//=============================================================================
// METHODS
//=============================================================================
public:
	suActuatorGeneralizedForces(rdModel *aModel=0);
	suActuatorGeneralizedForces(const std::string &aFileName);
	suActuatorGeneralizedForces(DOMElement *aElement);
	// Copy constrctor and virtual copy 
	suActuatorGeneralizedForces(const suActuatorGeneralizedForces &aObject);
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;
	virtual ~suActuatorGeneralizedForces();
private:
	void setNull();
	void setupProperties();
	void constructDescription();
	void constructColumnLabels();
	void allocateStorage();

public:
	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
#ifndef SWIG
	suActuatorGeneralizedForces& operator=(const suActuatorGeneralizedForces &aActuatorGeneralizedForces);
#endif
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	// STORAGE
	void setStorageCapacityIncrements(int aIncrement);
	rdStorage* getActuatorGenForcesStorage();

	virtual void setModel(rdModel *aModel);
	void setActuatorList(const rdArray<std::string>& aActuatorNames);
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
