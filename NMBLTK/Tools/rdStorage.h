// rdStorage.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2000 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdStorage_h__
#define __rdStorage_h__


#include "rdTools.h"
#include "rdObject.h"
#include "rdStateVector.h"


const int rdStorage_DEFAULT_CAPACITY = 256;

template class RDTOOLS_API rdArray<rdStateVector>;

//=============================================================================
//=============================================================================
/**
 * A class for storing an array of statevectors.  A statevector is an
 * array of data that has an associated time stamp (see rdStateVector).
 * Generally, it is used to store the time histories of the states during
 * an integration, but may be used for a variety of applications.  Note that
 * it is assumed by several methods in this class that the time stamps of
 * stored statevectors are monotonically increasing.
 *
 * When stored as a file, the statevectors are stored in rows.  This first
 * value in a row is the time stamp at which the states occured.  The
 * rest of the elements in a row are the states.  Therefore, each column of
 * data in a file corresponds to a particular state.
 *
 * In an rdStorage object, statevectors (or rows) are indexed by the
 * TimeIndex, and a particular state (or column) is indexed by the
 * StateIndex.
 *
 * @version 1.0
 * @author Frank C. Anderson
 */
class RDTOOLS_API rdStorage : public rdObject
{

//=============================================================================
// DATA
//=============================================================================
public:
	/** Large negative number. */
	static const double LARGE_NEGATIVE;
	/** Large positive number. */
	static const double LARGE_POSITIVE;
	/** Default token used to mark the end of the storage description in
	a file. */
	static const char *DEFAULT_HEADER_TOKEN;
	static const char* DEFAULT_HEADER_SEPARATOR;
protected:
	/** Array of rdStateVectors. */
	rdArray<rdStateVector> _storage;
	/** Token used to mark the end of the description in a file. */
	char _headerToken[rdObject::NAME_LENGTH];
	/** Column labels for the states, usually tab delimited. */
	char *_columnLabels;
	/** Parsed version of _columnLabels to be used to query data by column */
	rdArray<std::string> _columnLabelsArray;
	/** Step interval at which states in a simulation are stored. See
	store(). */
	int _stepInterval;
	/** Last index at which a search was started. */
	int _lastI;
	/** Flag for whether or not to insert a SIMM style header. */
	bool _writeSIMMHeader;

//=============================================================================
// METHODS
//=============================================================================
public:
	rdStorage(int aCapacity=rdStorage_DEFAULT_CAPACITY,
		const char *aName="UNKNOWN");
	rdStorage(const char* aFileName);
	rdStorage(const rdStorage &aStorage,bool aCopyData=true);
	rdStorage(const rdStorage &aStorage,int aStateIndex,int aN,
		const char *aDelimiter="\t");
	virtual rdObject* copy() const;
	virtual ~rdStorage();

private:
	//--------------------------------------------------------------------------
	// CONSTRUCTION METHODS
	//--------------------------------------------------------------------------
	void allocateCapacity();
	void setNull();
	void copyData(const rdStorage &aStorage);
	void parseColumnLabels(const char *aLabels);
public:

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	// SIZE
	int getSize() { return(_storage.getSize()); }
	// STATEVECTOR
	int getSmallestNumberOfStates();
	rdStateVector* getStateVector(int aTimeIndex) const;
	rdStateVector* getLastStateVector() const;
	// TIME
	double getFirstTime();
	double getLastTime();
	int getTime(int aTimeIndex,double &rTime,int aStateIndex=-1) const;
	int getTimeColumn(double *&rTimes,int aStateIndex=-1);
	// DATA
	int getData(int aTimeIndex,int aStateIndex,double &rValue) const;
	int getData(int aTimeIndex,int aStateIndex,int aN,double *rData) const;
	int getData(int aTimeIndex,int aN,double **rData) const;
	int getData(int aTimeIndex,int aN,double *rData) const;
	int getDataAtTime(double aTime,int aN,double **rData);
	int getDataAtTime(double aTime,int aN,double *rData);
	int getDataColumn(int aStateIndex,double *&rData) const;
	void setDataColumn(int aStateIndex,const rdArray<double> &aData);
	int getDataColumn(std::string& columnName,double *&rData) const;
	// STEP INTERVAL
	void setStepInterval(int aStepInterval);
	int getStepInterval() const;
	// CAPACITY INCREMENT
	void setCapacityIncrement(int aIncrement);
	int getCapacityIncrement() const;
	// IO
	void setWriteSIMMHeader(bool aTrueFalse);
	bool getWriteSIMMHeader() const;
	void setHeaderToken(const char *aToken);
	const char* getHeaderToken() const;
	// COLUMN LABELS
	const int getColumnIndex(const std::string &aColumnName) const;
	void setColumnLabels(const char *aLabels=NULL);
	const char* getColumnLabels() const;
	const rdArray<std::string> &getColumnLabelsArray() const;
	//--------------------------------------------------------------------------
	// RESET
	//--------------------------------------------------------------------------
	int reset(int aIndex=0);
	int reset(double aTime);

	//--------------------------------------------------------------------------
	// STORAGE
	//--------------------------------------------------------------------------
	virtual int append(const rdStateVector &aVec);
	virtual int append(const rdArray<rdStateVector> &aArray);
	virtual int append(double aT,int aN,const double *aY);
	virtual int store(int aStep,double aT,int aN,const double *aY);

	//--------------------------------------------------------------------------
	// OPERATIONS
	//--------------------------------------------------------------------------
	void shiftTime(double aValue);
	void scaleTime(double aValue);
	void add(double aValue);
	void add(int aN,double aY[]);
	void add(int aN,double aValue);
	void add(rdStateVector *aStateVector);
	void add(rdStorage *aStorage);
	void subtract(double aValue);
	void subtract(int aN,double aY[]);
	void subtract(rdStateVector *aStateVector);
	void subtract(rdStorage *aStorage);
	void multiply(double aValue);
	void multiplyColumn(int aIndex, double aValue);
	void multiply(int aN,double aY[]);
	void multiply(rdStateVector *aStateVector);
	void multiply(rdStorage *aStorage);
	void divide(double aValue);
	void divide(int aN,double aY[]);
	void divide(rdStateVector *aStateVector);
	void divide(rdStorage *aStorage);
	rdStorage* integrate(int aI1=-2,int aI2=-1);
	rdStorage* integrate(double aT1,double aT2);
	int computeArea(int aN,double *aArea);
	int computeArea(double aTI,double aTF,int aN,double *aArea);
	int computeAverage(int aN,double *aAve);
	int computeAverage(double aTI,double aTF,int aN,double *aAve);
	void pad(int aPadSize);
	void lowpassFIR(int aOrder,double aCutoffFequency);

	//--------------------------------------------------------------------------
	// UTILITY
	//--------------------------------------------------------------------------
	int findIndex(double aT);
	int findIndex(int aI,double aT);
	void resample(const double aDT, const int aDegree);
	//--------------------------------------------------------------------------
	// IO
	//--------------------------------------------------------------------------
	void print();
	int print(const char *aFileName,const char *aMode="w");
	int print(const char *aFileName,double aDT,const char *aMode="w");
private:
	int writeHeader(FILE *rFP,double aDT=-1);
	int writeSIMMHeader(FILE *rFP,double aDT=-1);
	int writeDescription(FILE *rFP);
	int writeColumnLabels(FILE *rFP);
	int writeDefaultColumnLabels(FILE *rFP);

//=============================================================================
};	// END of class rdStorage
//=============================================================================
//=============================================================================

#endif //__rdStorage_h__
