// rdValueArray.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2003 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// INCLUDES
#include "rdTools.h"
#include "rdValueArray.h"


//============================================================================
// DEFINES
//============================================================================


//============================================================================
// CONSTANTS
//============================================================================
const int rdValueArray::CAPMIN = rdValueArray_CAPMIN;


//=============================================================================
// CONSTRUCTOR(S)
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 *
 * When the array is deleted, references to elements of this array become
 * invalid.
 */
rdValueArray::~rdValueArray()
{
	if(_descrip!=NULL) { delete[] _descrip;  _descrip=NULL; }
	if(_array!=NULL) { delete[] _array;  _array = NULL; }
}
//_____________________________________________________________________________
/**
 * Default constructor.
 * Note- this class has been replaced by class rdArray<T>.
 */
rdValueArray::rdValueArray(int aCapacity,const char *aName) :
{
	setNull();

	// TYPE
	setType("rdValueArray");

	// NAME
	setName(aName);

	// CAPACITY
	ensureCapacity(aCapacity);
	setCapacityIncrement();
}


//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Set all member variables to their null or default values.
 */
void rdValueArray::
setNull()
{
	_firstEmpty = 0;
	_descrip = NULL;
	_capacity = 0;
	_capacityIncrement = -1;
	_array = NULL;
}


//=============================================================================
// DESCRIPTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set the description of this storage.
 *
 * If the last character of a description is a carriage return, it is 
 * stripped.
 *
 * @param aDescrip Description.
 */
void rdValueArray::
setDescription(const char *aDescrip)
{
	// HANDLE NULL POINTER
	if(aDescrip==NULL) {
		if(_descrip!=NULL) { delete[] _descrip; _descrip = NULL; }
		return;
	}

	// HANDLE ZERO LENGTH STRING
	int len = strlen(aDescrip);
	if(len==0) {
		if(_descrip!=NULL) { delete[] _descrip; _descrip = NULL; }
		return;
	}

	// DELETE OLD DESCRIPTION
	if(_descrip!=NULL) delete[] _descrip;

	// SET NEW DESCRIPTION
	_descrip = new char[len+1];
	strcpy(_descrip,aDescrip);
}
//_____________________________________________________________________________
/**
 * Get a description of this storage.
 *
 * @return Description.
 */
const char* rdValueArray::
getDescription() const
{
	return(_descrip);
}


//=============================================================================
// CAPACITY
//=============================================================================
//_____________________________________________________________________________
/**
 * Ensure that the capacity of this array is at least the specified amount.
 *
 * @param aCapacity Desired capacity.
 * @return true if the capacity was successfully obtained, false otherwise.
 */
bool rdValueArray::
ensureCapacity(int aCapacity)
{
	// CHECK REQUESTED CAPACITY
	if(aCapacity<CAPMIN) aCapacity=CAPMIN;
	if(_capacity>=aCapacity) return(true);

	// ALLOCATE AND INITIALIZE THE NEW ARRAY
	int i;
	T defaultValue;
	T *newArray = new T[aCapacity];
	if(newArray==NULL) return(false);

	// COPY CURRENT ARRAY
	if(_array!=NULL) {
		for(i=0;i<_capacity;i++) newArray[i] = _array[i];
		for(i=_capacity;i<aCapacity;i++) newArray[i] = defaultValue;
		delete []_array;  _array=NULL; 
	} else {
		for(i=0;i<aCapacity;i++) newArray[i] = defaultValue;
	}
	
	// REASSIGN
	_capacity = aCapacity;
	_array = newArray;

	return(true);
}
//_____________________________________________________________________________
/**
 * Get the capacity of this storage instance.
 */
int rdValueArray::
getCapacity() const
{
	return(_capacity);
}

//-----------------------------------------------------------------------------
// CAPACITY INCREMENT
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the amount by which the capacity is increased.
 *
 * If the specified increment is less than 0 or this method
 * is called with no argument, the capacity is set to double whenever
 * the capacity is exceeded.
 *
 * @param aIncrement Desired capacity increment.
 */
void rdValueArray::
setCapacityIncrement(int aIncrement)
{
	_capacityIncrement = aIncrement;
}
//_____________________________________________________________________________
/**
 * Get the amount by which the capacity is increased.
 */
int rdValueArray::
getCapacityIncrement() const
{
	return(_capacityIncrement);
}


//=============================================================================
// STORAGE OPERATIONS
//=============================================================================
//-----------------------------------------------------------------------------
// FIRST EMPTY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the first empty element of the array to a specified value.  This method
 * essentially resets the array so that all elements stored at a specified
 * index or after are no longer considered valid:  append() will simply
 * over-write these elements.
 *
 * @param aIndex Index at which to start appending new values onto the
 * array.  The default value is 0.
 * If aIndex is greater than or equal to the current value of _firstEmpty,
 * no change is made.
 * If aIndex is less than 0, the array is set to start storing at index 0.
 * @see getFirstEmpty()
 */
void rdValueArray::
setFirstEmpty(int aIndex)
{
	if(aIndex<0) {
		_firstEmpty = 0;
	} else if(aIndex<_firstEmpty) {
		_firstEmpty = aIndex;
	} else {
		printf("rdValueArray.setFirstEmpty(): WARN- attempt to set ");
		printf("first empty index to %d,\n",aIndex);
		printf("which is greater than the current value of %d.\n",
			_firstEmpty);
		printf("  This is not allowed.\n");
	}
}
//_____________________________________________________________________________
/**
 * Get the index of the first empty array element.
 *
 * @return Index of the first empty array element.
 */
int rdValueArray::
getFirstEmpty() const
{
	return(_firstEmpty);
}

//-----------------------------------------------------------------------------
// APPEND
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Append a value onto the array.
 *
 * @param aValue Value to be appended.
 * @return Index to the new first empty element (or end) of the array.
 */
int rdValueArray::
append(const T &aValue)
{
	// CHECK FOR OVERFLOW
	if(_firstEmpty>=_capacity) {
		int newCapacity;
		if(_capacityIncrement < 0) {
			newCapacity = 2 * _capacity;

		} else if(_capacityIncrement == 0) {
			printf("rdValueArray.append: WARN- capacity exceeded and ");
			printf("capacity increment equals 0, so value not appended.\n");
			return(_firstEmpty);

		} else {
			newCapacity = _capacity + _capacityIncrement;
		}

		printf("rdValueArray.append: ");
		printf("%s increasing capacity from %d to %d.\n",getName(),_capacity,
		 newCapacity);
		bool success = ensureCapacity(newCapacity);
		if(!success) {
			printf("rdValueArray.append: WARN- ");
			printf("failed to increase capacity.\n");
			return(_firstEmpty);
		}
	}

	// SET
	_array[_firstEmpty] = aObject;
	_firstEmpty++;

	return(_firstEmpty);
}
//_____________________________________________________________________________
/**
 * Append an array of values.
 */
int rdValueArray::
append(const rdValueArray<T> &aArray)
{
	// LOOP THROUGH THE ELEMENTS
	int i,n=aArray->getFirstEmpty();
	for(i=0;i<n;i++) {
		append(aArray->get(i));
	}

	return(_firstEmpty);
}

//-----------------------------------------------------------------------------
// SET AND GET
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the value at a specified index.
 *
 * @param aIndex Index of the array element to be set.  It is permissible
 * for aIndex to be past the current end of the array.  Values in the
 * array from _firstEmpty to aIndex will be intialized using the default
 * constructor of class T.
 * @param aValue Value.
 */
void rdValueArray::
set(int aIndex,const T &aValue)
{
	if(aIndex<0) return;

	// ENSURE CAPACITY
	bool success = false;
	if(aIndex>=_capacity) {
		success = ensureCapacity(aIndex+getCapacityIncrement());
		if(!success) return(NULL);
	}

	// SET
	rdObject *object = _array[aIndex];
	_array[aIndex] = aObject;

	// FIRST EMPTY
	if(aIndex>=_firstEmpty)  _firstEmpty = aIndex+1;

	return(object);
}
//_____________________________________________________________________________
/**
 * Get the pointer at a specified array index.
 *
 * If the index is greater than or equal to the capacity of the array,
 * NULL is returned.
 *
 * @param aIndex Index of the desired array element.
 * @return Pointer at aIndex or NULL.
 */
rdObject* rdValueArray::
get(int aIndex) const
{
	if(aIndex<0) return(NULL);
	if(aIndex>=_capacity) return(NULL);
	return(_array[aIndex]);
}
//_____________________________________________________________________________
/**
 * Get the last pointer in the array.
 *
 * @return Last pointer in the array.
 */
rdObject* rdValueArray::
getLast() const
{
	if(_firstEmpty<=0) return(NULL);
	return(_array[_firstEmpty-1]);
}

//-----------------------------------------------------------------------------
// INDEX
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the index of the first element with a specified value.
 *
 * @param aObject Pointer value of the object whose index is desired.
 * @return Index of the object; -1 if no such object is in the array.
 */
int rdValueArray::
getIndex(rdObject *aObject) const
{
	int i;
	for(i=0;i<_firstEmpty;i++) {
		if(aObject == _array[i]) return(i);
	}

	return(-1);
}
//_____________________________________________________________________________
/**
 * Remove an object by index.
 * When an object is removed, the array locations of all objects following the
 * removed object are shifted down by 1.
 *
 * The caller is responsible for deleting the removed object.
 *
 * To remove an object without shifting the array locations of all objects
 * following the removed object, use the method set().
 *
 * @param aIndex Index of the object to remove.
 * @return Pointer to the removed object; NULL if there was no object at
 * aIndex.
 * @see set()
 */
rdObject* rdValueArray::
remove(int aIndex)
{
	// CHECK FOR VALID INDEX
	if((aIndex<0)||(aIndex>=_firstEmpty)) {
		return(NULL);
	}

	// REMOVE
	rdObject *object = _array[aIndex];

	// SHIFT BALANCE OF ARRAY ELEMENTS DOWN
	int i;
	int end=_firstEmpty-1;
	for(i=aIndex;i<end;i++) {
		_array[i] = _array[i+1];
	}
	_array[_firstEmpty-1] = NULL;

	// REDUCE NUMBER OF OBJECTS
	_firstEmpty--;
	
	return(object);
}
//_____________________________________________________________________________
/**
 * Remove an object based on the object's pointer.
 * When an object is removed, the array locations of all objects following the
 * removed object are shifted down by 1.
 *
 * This method is fairly expensive to call at this time because the entire
 * array is searched sequentially.  The caller is responsible for deleting
 * the removed object.
 * 
 * To remove an object without shifting the array locations of all objects
 * following the removed object, use the method set().
 *
 * @param aObject Pointer to the object to be removed.
 * @return Pointer to the object that was removed.  If no object was found,
 * NULL is returned.
 * @see set()
 */
rdObject* rdValueArray::
remove(rdObject *aObject)
{
	if(aObject==NULL) return(NULL);

	// GET OBJECT INDEX
	int index = getIndex(aObject);
	if(index==-1) return(NULL);

	// REMOVE
	rdObject *object = remove(index);

	return(object);
}
