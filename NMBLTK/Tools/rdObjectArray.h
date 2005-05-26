// rdObjectArray.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2003 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdObjectArray_h__
#define __rdObjectArray_h__


#include "rdTools.h"
#include "rdObject.h"

#define rdObjectArray_CAPMIN 1;

//=============================================================================
//=============================================================================
/**
 * A class for storing an array of rdObject's.  The capacity of the class
 * grows as needed.
 *
 * When an rdObjectArray object is deleted, the objects held by the array
 * are deleted.
 *
 * @version 1.0
 * @author Frank C. Anderson
 */
class RDTOOLS_API rdObjectArray : public rdObject
{

//=============================================================================
// DATA
//=============================================================================
private:
	/** Index of the first empty rdStateVector pointer. */
	int _firstEmpty;
protected:
	/** Minimum capacity. */
	static const int CAPMIN;
	/** Description. */
	char *_descrip;
	/** Current capacity. */
	int _capacity;
	/** Increment by which the current capacity is increased when the capacity
	of this storage instance is reached. */
	int _capacityIncrement;
	/** Array of pointers to rdObjects. */
	rdObject **_array;


//=============================================================================
// METHODS
//=============================================================================
public:
	rdObjectArray(int aCapacity=128,const char *aName="UNKNOWN");
	rdObjectArray(const char *aFileName);
	rdObjectArray(DOMElement *aElement);
	virtual ~rdObjectArray();

private:
	//--------------------------------------------------------------------------
	// CONSTRUCTION METHODS
	//--------------------------------------------------------------------------
	void allocateCapacity();
	void setNull();
public:

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	virtual void setDescription(const char *aDescrip=NULL);
	virtual const char* getDescription() const;
	virtual bool ensureCapacity(int aCapacity);
	virtual int getCapacity() const;
	virtual void setCapacityIncrement(int aIncrement=-1);
	virtual int getCapacityIncrement() const;

	//--------------------------------------------------------------------------
	// RESET
	//--------------------------------------------------------------------------
	virtual void reset();
	virtual void reset(int aIndex);

	//--------------------------------------------------------------------------
	// STORAGE
	//--------------------------------------------------------------------------
	virtual int getFirstEmpty() const;
	virtual int getIndex(const char *aName,int aStart=0) const;
	virtual int getIndex(rdObject *aObject) const;
	virtual rdObject* set(int aIndex,rdObject *aObject);
	virtual rdObject* get(int aIndex) const;
	virtual rdObject* getLast() const;
	virtual int append(rdObject *aObject);
	virtual int append(rdObjectArray *aArray);
	virtual rdObject* remove(int aIndex);
	virtual rdObject* remove(rdObject *aObject);

	//--------------------------------------------------------------------------
	// XML
	//--------------------------------------------------------------------------
	virtual void updateObject(bool aDeep=true);
	virtual void updateNode(bool aDeep=true);

//=============================================================================
};	// END of class rdObjectArray
//=============================================================================
//=============================================================================

#endif //__rdObjectArray_h__
