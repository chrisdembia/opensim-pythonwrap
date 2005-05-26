// rdStateVector.h: interface for the rdStateVector class.
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2000 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdStateVector_h__
#define __rdStateVector_h__


#include "rdTools.h"
#include "rdArray.h"


//template class RDTOOLS_API rdArray<double>;


//=============================================================================
//=============================================================================
/**
 * A class which stores a vector of states or data at a specified time.
 * Generally, it is used to store the time histories of the states during
 * an integration.
 *
 * The format of the numerical output for this class is specified by the
 * settings in rdIO.
 *
 * @author Frank C. Anderson
 * @version 1.0
 * @see rdIO
 */
class RDTOOLS_API rdStateVector
{
//=============================================================================


//=============================================================================
// DATA
//=============================================================================
private:
	/** Time stamp of the statevector. */
	double _t;
	/** Array of states. */
	rdArray<double> _data;

//=============================================================================
// METHODS
//=============================================================================
public:
	rdStateVector(double aT=0.0,int aN=0,const double *aData=NULL);
	rdStateVector(const rdStateVector &aVector);
	virtual ~rdStateVector();

	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
private:
	void setNull();

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
#ifndef SWIG
	rdStateVector& operator=(const rdStateVector &aStateVector);
	bool operator==(const rdStateVector &aStateVector) const;
	bool operator<(const rdStateVector &aStateVector) const;
	friend std::ostream& operator<<(std::ostream &aOut,
									const rdStateVector &aStateVector) {
		aOut<<"rdStateVector: t="<<aStateVector._t<<", "<<aStateVector._data;
		return(aOut);
	};
#endif
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
public:
	void setStates(double aT,int aN,const double aY[]);
	int getSize() const;
	void setTime(double aT);
	double  getTime() const;
	int getDataValue(int aIndex,double &rValue);
	void setDataValue(int aIndex,double &aValue);
	rdArray<double>& getData();
#ifndef SWIG
	const rdArray<double>& getData() const;
#endif
	//--------------------------------------------------------------------------
	// OPERATIONS
	//--------------------------------------------------------------------------
	void shiftTime(double aValue);
	void scaleTime(double aValue);
	void add(double aValue);
	void add(int aN,double aY[]);
	void add(int aN,double aValue);
	void add(rdStateVector *aStateVector);
	void subtract(double aValue);
	void subtract(int aN,double aY[]);
	void subtract(rdStateVector *aStateVector);
	void multiply(double aValue);
	void multiply(int aN,double aY[]);
	void multiply(rdStateVector *aStateVector);
	void divide(double aValue);
	void divide(int aN,double aY[]);
	void divide(rdStateVector *aStateVector);

	//--------------------------------------------------------------------------
	// IO
	//--------------------------------------------------------------------------
	void print();
	int print(FILE *fp);


//=============================================================================
};	// END of class rdStateVector
//=============================================================================
//=============================================================================

#endif //__rdStateVector_h__
