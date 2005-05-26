// rdValueArray.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2003 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdValueArray_h__
#define __rdValueArray_h__


#include "rdTools.h"
#include "rdObject.h"

#define rdValueArray_CAPMIN 1;

//=============================================================================
//=============================================================================
/**
 * Note- this class has been replaced by class rdArray<T>.
 * A class for storing an array of values of type T.  The capacity of the class
 * grows as needed.  To use this template for a class of type T, class T must
 * implement the following methods:  default constructor, copy constructor,
 * assignment operator (=), equality operator (==), and less than
 * operator (<).
 *
 * @version 1.0
 * @author Frank C. Anderson
 */
template <class T> class RDTOOLS_API rdValueArray : public rdObject
{

//=============================================================================
// DATA
//=============================================================================
public:
	/** Minimum capacity. */
	static const int CAPMIN;
private:
	/** Index of the first empty array element. */
	int _firstEmpty;
protected:
	/** Description. */
	char *_descrip;
	/** Current capacity. */
	int _capacity;
	/** Increment by which the current capacity is increased when the capacity
	of this storage instance is reached. */
	int _capacityIncrement;
	/** Array of values. */
	T *_array;

//=============================================================================
// METHODS
//=============================================================================
public:
	rdValueArray(int aCapacity=128,const char *aName="UNKNOWN");
	virtual ~rdValueArray();
private:
	void setNull();
public:

	//--------------------------------------------------------------------------
	// DESCRIPTION
	//--------------------------------------------------------------------------
	void setDescription(const char *aDescrip=NULL);
	const char* getDescription() const;

	//--------------------------------------------------------------------------
	// CAPACITY
	//--------------------------------------------------------------------------
	bool ensureCapacity(int aCapacity);
	int getCapacity() const;
	void setCapacityIncrement(int aIncrement=-1);
	int getCapacityIncrement() const;

	//--------------------------------------------------------------------------
	// STORAGE
	//--------------------------------------------------------------------------
	void setFirstEmpty(int aIndex=0);
	int getFirstEmpty() const;
	int append(const T &aValue);
	int append(const rdValueArray<T> &aArray);
	void set(int aIndex,const T &aValue);
	T& get(int aIndex) const;
	T& getLast() const;
	void insert(int aIndex,const T &aValue);
	void remove(int aIndex);
	void remove(const T &aValue);
	int searchSequential(const T &aValue,int aStartIndex=0);
	int searchBinary(const T &aValue);

	//--------------------------------------------------------------------------
	// XML
	//--------------------------------------------------------------------------
	virtual void updateObject(bool aDeep=true);
	virtual void updateNode(bool aDeep=true);

//=============================================================================
};	// END of class rdValueArray
//=============================================================================
//=============================================================================

#endif //__rdValueArray_h__
