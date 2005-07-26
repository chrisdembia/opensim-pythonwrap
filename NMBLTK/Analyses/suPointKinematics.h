// suPointKinematics.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suPointKinematics_h__
#define __suPointKinematics_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include "suAnalysesDLL.h"
#ifdef SWIG
	#ifdef SUANALYSES_API
		#undef SUANALYSES_API
		#define SUANALYSES_API
	#endif
#endif
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Tools/rdStorage.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include <NMBLTK/Simulation/Model/rdAnalysis.h>

const int suPointKinematicsNAME_LENGTH = 256;
const int suPointKinematicsBUFFER_LENGTH = 2048;

//=============================================================================
//=============================================================================
/**
 * A class for recording the kinematics of a point on a body
 * of a model during a simulation.
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class SUANALYSES_API suPointKinematics : public rdAnalysis 
{
//=============================================================================
// DATA
//=============================================================================
public:
	static const int NAME_LENGTH;
	static const int BUFFER_LENGTH;
private:
	char _buffer[suPointKinematicsBUFFER_LENGTH];
	char _tmp[suPointKinematicsBUFFER_LENGTH];
protected:
	// Properties
	rdPropertyInt _bodyProp;
	rdPropertyDblArray _pointProp;
	rdPropertyStr _pointNameProp;
	// References
	int &_body;
	rdArray<double>& _point;
	std::string &_pointName;

	double *_dy;
	double *_kin;
	rdStorage *_pStore;
	rdStorage *_vStore;
	rdStorage *_aStore;

//=============================================================================
// METHODS
//=============================================================================
public:
	suPointKinematics(rdModel *aModel=0);
	suPointKinematics(const std::string &aFileName);
	suPointKinematics(DOMElement *aElement);
	// Copy constrctor and virtual copy 
	suPointKinematics(const suPointKinematics &aObject);
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;
	virtual ~suPointKinematics();
private:
	void setNull();
	void setupProperties();
	void constructDescription();
	void constructColumnLabels();
	void allocateStorage();
	void deleteStorage();
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
#ifndef SWIG
	suPointKinematics& operator=(const suPointKinematics &aPointKinematics);
#endif
public:
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	// BODY
	void setBody(int aBody);
	int getBody();
	// POINT
	void setPoint(double aPoint[3]);
	void getPoint(double rPoint[3]);
	// POINT NAME
	void setPointName(const char *aName);
	const char* getPointName();
	// STORAGE
	void setStorageCapacityIncrements(int aIncrement);
	rdStorage* getAccelerationStorage();
	rdStorage* getVelocityStorage();
	rdStorage* getPositionStorage();

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
};	// END of class suPointKinematics
//=============================================================================
//=============================================================================


#endif // #ifndef __suPointKinematics_h__
