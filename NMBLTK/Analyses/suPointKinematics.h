// suPointKinematics.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suPointKinematics_h__
#define __suPointKinematics_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include <RD/Tools/rdMath.h>
#include <RD/Tools/rdTools.h>
#include <RD/Tools/rdStorage.h>
#include <RD/Simulation/Model/rdModel.h>
#include <RD/Simulation/Model/rdAnalysis.h>
#include "suAnalysesDLL.h"


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
	int _body;
	double _point[3];
	char _pointName[suPointKinematicsNAME_LENGTH];
	double *_dy;
	double *_kin;
	rdStorage *_pStore;
	rdStorage *_vStore;
	rdStorage *_aStore;

//=============================================================================
// METHODS
//=============================================================================
public:
	suPointKinematics(rdModel *aModel);
	virtual ~suPointKinematics();
private:
	void setNull();
	void constructDescription();
	void constructColumnLabels();
	void allocateStorage();
	void deleteStorage();

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
