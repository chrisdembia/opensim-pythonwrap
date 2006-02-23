// suBodyKinematics.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suBodyKinematics_h__
#define __suBodyKinematics_h__


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
 * A class for recording the kinematics of the bodies
 * of a model during a simulation.
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class SUANALYSES_API suBodyKinematics : public rdAnalysis 
{
//=============================================================================
// DATA
//=============================================================================
private:

protected:
	double *_dy;
	double *_kin;
	rdStorage *_pStore;
	rdStorage *_vStore;
	rdStorage *_aStore;
	/** Whether or not to write output of angles in degrees. */
	rdPropertyBool _angVelInLocalFrameProp;
	bool &_angVelInLocalFrame;


//=============================================================================
// METHODS
//=============================================================================
public:
	suBodyKinematics(rdModel *aModel=0, bool aInDegrees=true);
	suBodyKinematics(const std::string &aFileName);
	suBodyKinematics(DOMElement *aElement);
	// Copy constrctor and virtual copy 
	suBodyKinematics(const suBodyKinematics &aObject);
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;
	virtual ~suBodyKinematics();
	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
#ifndef SWIG
	suBodyKinematics& operator=(const suBodyKinematics &aBodyKinematics);
#endif
private:
	void setNull();
	void setupProperties();
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
	rdStorage* getAccelerationStorage();
	rdStorage* getVelocityStorage();
	rdStorage* getPositionStorage();
	void setAngVelInLocalFrame(bool aTrueFalse);
	bool getAngVelInLocalFrame();

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
};	// END of class suBodyKinematics
//=============================================================================
//=============================================================================


#endif // #ifndef __suBodyKinematics_h__
