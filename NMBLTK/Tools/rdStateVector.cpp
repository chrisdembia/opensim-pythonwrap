// rdStateVector.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2000 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// INCLUDES
#include "rdMath.h"
#include "rdIO.h"
#include "rdStateVector.h"

using namespace std;



//=============================================================================
// CONSTRUCTOR(S)
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
rdStateVector::~rdStateVector()
{
}

//_____________________________________________________________________________
/**
 * Default constructor.
 */
rdStateVector::rdStateVector(double aT,int aN,const double aData[]) :
	_data(0.0)
{
	// INITIAL VALUES
	setNull();

	// SET THE DATA
	setStates(aT,aN,aData);
}
//_____________________________________________________________________________
/**
 * Copy constructor.
 */
rdStateVector::rdStateVector(const rdStateVector &aVector) :
	_data(0.0)
{
	// INITIAL VALUES
	setNull();

	// SET STATES
	setStates(aVector.getTime(),aVector.getSize(),&aVector.getData()[0]);
}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set the null or default values of the states.
 */
void rdStateVector::
setNull()
{
	// DATA
	_t = 0.0;
	_data.setSize(0);
}


//=============================================================================
// OPERATORS
//=============================================================================
//-----------------------------------------------------------------------------
// ASSIGNMENT
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Assign this statevector to the values of another.
 *
 * @return Reference to this statevector.
 */
rdStateVector& rdStateVector::
operator=(const rdStateVector &aStateVector)
{
	_t = aStateVector._t;
	_data = aStateVector._data;
	return(*this);
}

//-----------------------------------------------------------------------------
// EQUALITY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Determine if two statevectors are equal.
 *
 * Equality is very restrictive.  To be equal, two statevectors must have
 * the same values for time and all states.
 *
 * @return True if the two statevectors are equal; false otherwise.
 */
bool rdStateVector::
operator==(const rdStateVector &aStateVector) const
{
	if((_t==aStateVector._t) && (_data==aStateVector._data)) return(true);
	return(false);
}

//-----------------------------------------------------------------------------
// LESS THAN
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Determine if this statevector is less than another.
 *
 * A statevector is less than another statevector if its time is less than
 * the other's time.
 *
 * @param aStateVector Statevector for which to make the less than test.
 * @return True if this statevector is less than the specified; false otherwise.
 */
bool rdStateVector::
operator<(const rdStateVector &aStateVector) const
{
	return(_t < aStateVector._t);
}


//=============================================================================
// GET AND SET
//=============================================================================
//_____________________________________________________________________________
/**
 * Set the time stamp of this vector.
 */
void rdStateVector::
setTime(double aT)
{
	_t = aT;
}
//_____________________________________________________________________________
/**
 * Get the time stamp of this vector.
 */
double rdStateVector::
getTime() const
{
	return(_t);
}
//_____________________________________________________________________________
/**
 * Set the state values of this vector.
 */
void rdStateVector::
setStates(double aT,int aN,const double *aData)
{
	_t = aT;
	_data.setSize(aN);
	int size = _data.getSize();
	for(int i=0;i<size;i++) {
		_data[i] = aData[i];
	}
}
//_____________________________________________________________________________
/**
 * Get the size of the data vector.
 */
int rdStateVector::
getSize() const
{
	return(_data.getSize());
}
//_____________________________________________________________________________
/**
 * Get the data values of this vector.
 */
rdArray<double>& rdStateVector::
getData()
{
	return(_data);
}
//_____________________________________________________________________________
/**
 * Get the data values of this vector.
 */
const rdArray<double>& rdStateVector::
getData() const
{
	return(_data);
}
//_____________________________________________________________________________
/**
 * Get the data value at a specified index.
 *
 * @param aIndex Index of the desired value:  0 < aIndex < getSize().
 * @param rValue Value of the data point if it is defined.
 * @return 1 on success, 0 on failure.
 */
int rdStateVector::
getDataValue(int aIndex,double &rValue)
{
	if(aIndex<0) return(0);
	if(aIndex>=_data.getSize()) return(0);

	rValue = _data[aIndex];
	return(1);
}

//_____________________________________________________________________________
/**
 * Set the data value at a specified index.
 *
 * @param aIndex Index of the desired value:  0 < aIndex < getSize().
 * @param aValue Value of the data point if it is defined.
 */
void rdStateVector::
setDataValue(int aIndex,double &aValue)
{
	if(aIndex<0) return;
	if(aIndex>=_data.getSize()) return;

	_data[aIndex]=aValue;
}

//=============================================================================
// OPERATIONS
//=============================================================================
//-----------------------------------------------------------------------------
// TIME
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Shift the time of this state vector.
 *
 * @param aValue Value by which to shift time.
 */
void rdStateVector::
shiftTime(double aValue)
{
	_t += aValue;
}
//_____________________________________________________________________________
/**
 * Scale the time of this state vector.
 *
 * @param aValue Value by which to scale time.
 */
void rdStateVector::
scaleTime(double aValue)
{
	_t *= aValue;
}

//-----------------------------------------------------------------------------
// ADD
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Add a value to each state.
 *
 * @param aValue Value to add to each state.
 */
void rdStateVector::
add(double aValue)
{
	int i;
	for(i=0;i<_data.getSize();i++)  _data[i] += aValue;
}
//_____________________________________________________________________________
/**
 * Add the values held in an array to the corresponding states.
 *
 * Only the first aN states are altered.
 *
 * @param aN Length of aY.
 * @param aY Array of values to add to the states.
 */
void rdStateVector::
add(int aN,double aY[])
{
	if(aY==NULL) return;
	int i,n=aN;
	if(n>_data.getSize()) n = _data.getSize();
	for(i=0;i<n;i++)  _data[i] += aY[i];
}
//_____________________________________________________________________________
/**
 * Add a value to a state.
 *
 * Only one state is altered.  This function was implemented so that 
 * a value could be added to an entire column of a rdStorage.
 *
 * @param aN Index of state to be altered.
 * @param aValue Values to add to the state.
 */
void rdStateVector::
add(int aN,double aValue)
{
	if(aValue==NULL) return;
	if(aN>_data.getSize()) return;
	_data[aN] += aValue;
}
//_____________________________________________________________________________
/**
 * Add the values held in a state vector to the corresponding states.
 *
 * @param aStateVector State vector to add to the states.
 */
void rdStateVector::
add(rdStateVector *aStateVector)
{
	if(aStateVector==NULL) return;

	// GET SIZE
	int n = aStateVector->getSize();
	if(n>_data.getSize()) n = _data.getSize();

	// GET DATA
	rdArray<double> &data = aStateVector->getData();

	// ADD
	int i;
	for(i=0;i<n;i++)  _data[i] += data[i];
}

//-----------------------------------------------------------------------------
// Subtract
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Subtract a value from each state.
 *
 * @param aValue Value to subtract from each state.
 */
void rdStateVector::
subtract(double aValue)
{
	int i;
	for(i=0;i<_data.getSize();i++)  _data[i] -= aValue;
}
//_____________________________________________________________________________
/**
 * Subtract the values held in an array from the corresponding states.
 *
 * Only the first aN states are altered.
 *
 * @param aN Length of aY.
 * @param aY Array of values to subtracted from the states.
 */
void rdStateVector::
subtract(int aN,double aY[])
{
	if(aY==NULL) return;
	int i,n=aN;
	if(n>_data.getSize()) n = _data.getSize();
	for(i=0;i<n;i++)  _data[i] -= aY[i];
}
//_____________________________________________________________________________
/**
 * Subtract the values held in a state vector from the corresponding states.
 *
 * @param aStateVector State vector to subtract from the states.
 */
void rdStateVector::
subtract(rdStateVector *aStateVector)
{
	if(aStateVector==NULL) return;

	// GET SIZE
	int n = aStateVector->getSize();
	if(n>_data.getSize()) n = _data.getSize();

	// GET DATA
	rdArray<double> &data = aStateVector->getData();

	// SUBTRACT
	int i;
	for(i=0;i<n;i++)  _data[i] -= data[i];
}

//-----------------------------------------------------------------------------
// MULTIPLY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Multiply the states by a value.
 *
 * @param aValue Value each state is to be multiplied by.
 */
void rdStateVector::
multiply(double aValue)
{
	int i;
	for(i=0;i<_data.getSize();i++)  _data[i] *= aValue;
}
//_____________________________________________________________________________
/**
 * Multiply the states by the corresponding values in an array.
 *
 * Only the first aN states are altered.
 *
 * @param aN Length of aY.
 * @param aY Array of values the states are multiplied by.
 */
void rdStateVector::
multiply(int aN,double aY[])
{
	if(aY==NULL) return;
	int i,n=aN;
	if(n>_data.getSize()) n = _data.getSize();
	for(i=0;i<n;i++)  _data[i] *= aY[i];
}
//_____________________________________________________________________________
/**
 * Multiply the states by the corresponding values in a state vector.
 *
 * @param aStateVector State vector by which to multiply the states.
 */
void rdStateVector::
multiply(rdStateVector *aStateVector)
{
	if(aStateVector==NULL) return;

	// GET SIZE
	int n = aStateVector->getSize();
	if(n>_data.getSize()) n = _data.getSize();

	// GET DATA
	rdArray<double> &data = aStateVector->getData();

	// MULTIPLY
	int i;
	for(i=0;i<n;i++)  _data[i] *= data[i];
}

//-----------------------------------------------------------------------------
// DIVIDE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Divide the states by a value.
 *
 * @param aValue Value each state is to be divided by.
 */
void rdStateVector::
divide(double aValue)
{
	if(aValue==0.0) {
		printf("rdStateVector.divide: ERROR- divide by zero\n");
		return;
	}

	int i;
	for(i=0;i<_data.getSize();i++) {
		_data[i] /= aValue;
	}
}
//_____________________________________________________________________________
/**
 * Divide the states by the corresponding values in an array.
 *
 * Only the first aN states are altered.
 *
 * @param aN Length of aY.
 * @param aY Array of values the states are divided by.
 */
void rdStateVector::
divide(int aN,double aY[])
{
	if(aY==NULL) return;
	int i,n=aN;
	if(n>_data.getSize()) n = _data.getSize();
	for(i=0;i<n;i++) {  
		if(aY[i]==0.0)	_data[i] = rdMath::NAN;
		else	_data[i] /= aY[i];
	}
		
}
//_____________________________________________________________________________
/**
 * Divide the states by the corresponding values in a state vector.
 *
 * @param aStateVector State vector by which to divide the states.
 */
void rdStateVector::
divide(rdStateVector *aStateVector)
{
	if(aStateVector==NULL) return;

	// GET SIZE
	int n = aStateVector->getSize();
	if(n>_data.getSize()) n = _data.getSize();

	// GET DATA
	rdArray<double> &data = aStateVector->getData();

	// DIVIDE
	int i;
	for(i=0;i<n;i++) {  
		if(data[i]==0.0)	_data[i] = rdMath::NAN;
		else	_data[i] /= data[i];
	}
}


//=============================================================================
// IO
//=============================================================================
//_____________________________________________________________________________
/**
 * Print the contents of this rdStateVector to standard out.
 */
void rdStateVector::
print()
{
	// TIME
	char format[rdIO_STRLEN];
	sprintf(format,"t=%s,\t\ty[%%d] =",rdIO::GetDoubleOutputFormat());
	printf(format,_t,_data.getSize());

	// DATA
	sprintf(format," %s",rdIO::GetDoubleOutputFormat());
	for(int i=0;i<_data.getSize();i++) {
		printf(format,_data[i]);
	}
	printf("\n");
}
//_____________________________________________________________________________
/**
 * Print the contents of this rdStateVector to file.
 *
 * The number of characters written to file is returned.  If an error
 * occurs, a negative value is returned.
 */
int rdStateVector::
print(FILE *fp)
{
	// CHECK FILE POINTER
	if(fp==NULL) {
		printf("rdStateVector.print(FILE*): null file pointer.\n");
		return(-1);
	}

	// TIME
	char format[rdIO_STRLEN];
	sprintf(format,"%s",rdIO::GetDoubleOutputFormat());
	int n=0,nTotal=0;
	n = fprintf(fp,format,_t);
	if(n<0) {
		printf("rdStateVector.print(FILE*): error writing to file.\n");
		return(n);
	}
	nTotal += n;

	// STATES
	sprintf(format,"\t%s",rdIO::GetDoubleOutputFormat());
	for(int i=0;i<_data.getSize();i++) {
		n = fprintf(fp,format,_data[i]);
		if(n<0) {
			printf("rdStateVector.print(FILE*): error writing to file.\n");
			return(n);
		}
		nTotal += n;
	}

	// CARRIAGE RETURN
	n = fprintf(fp,"\n");
	if(n<0) {
		printf("rdStateVector.print(FILE*): error writing to file.\n");
		return(n);
	}
	nTotal += n;

	return(nTotal);
}
