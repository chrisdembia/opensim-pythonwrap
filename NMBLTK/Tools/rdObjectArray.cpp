// rdObjectArray.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2003 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// INCLUDES
#include "rdTools.h"
#include "rdObjectArray.h"


//============================================================================
// DEFINES
//============================================================================


//============================================================================
// CONSTANTS
//============================================================================
const int rdObjectArray::CAPMIN = rdObjectArray_CAPMIN;


//=============================================================================
// CONSTRUCTOR(S)
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 *
 * The destructor does NOT call the destructor for the pointer elements held
 * in the array.  It simply deletes the array itself.
 */
rdObjectArray::~rdObjectArray()
{
	// CHARACTER STRINGS
	if(_descrip!=NULL) { delete[] _descrip;  _descrip=NULL; }

	// OBJECTS
	int i;
	rdObject *object;
	for(i=0;i<getFirstEmpty();i++) {
		object = get(i);
		if(object==NULL) continue;
		delete object;
		set(i,NULL);
	}

	// STORAGE
	if(_array!=NULL) { delete[] _array;  _array = NULL; }
}
//_____________________________________________________________________________
/**
 * Default constructor.
 */
rdObjectArray::rdObjectArray(int aCapacity,const char *aName)
{
	setNull();

	// TYPE
	setType("rdObjectArray");

	// NAME
	setName(aName);

	// CAPACITY
	ensureCapacity(aCapacity);
	setCapacityIncrement();
}
//_____________________________________________________________________________
/**
 * Construct from a file.
 *
 * @param aElement 
 */
rdObjectArray::rdObjectArray(const char *aFileName) :
	rdObject(aFileName)
{
	setNull();
	if(_node==NULL) return;

	// HOW MANY CHILDREN
	DOMNodeList *childList = _node->getChildNodes();
	int capacity = childList->getLength() + CAPMIN;

	// CAPACITY
	ensureCapacity(capacity);
	setCapacityIncrement();
}
//_____________________________________________________________________________
/**
 * Construct based on an XML element.
 *
 * @param aElement 
 */
rdObjectArray::rdObjectArray(DOMElement *aElement) :
	rdObject(aElement)
{
	setNull();
	if(_node==NULL) return;

	// HOW MANY CHILDREN
	DOMNodeList *childList = _node->getChildNodes();
	int capacity = childList->getLength() + CAPMIN;

	// CAPACITY
	ensureCapacity(capacity);
	setCapacityIncrement();
}


//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Set all member variables to their null or default values.
 */
void rdObjectArray::
setNull()
{
	_descrip = NULL;
	_capacity = 0;
	_capacityIncrement = -1;
	_firstEmpty = 0;
	_array = NULL;
}


//=============================================================================
// GET AND SET
//=============================================================================
//-----------------------------------------------------------------------------
// DESCRIPTION
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the description of this storage.
 *
 * If the last character of a description is a carriage return, it is 
 * stripped.
 *
 * @param aDescrip Description.
 */
void rdObjectArray::
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
const char* rdObjectArray::
getDescription() const
{
	return(_descrip);
}


//-----------------------------------------------------------------------------
// CAPACITY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Ensure that the capacity of this expandable array is at least
 * the specified amount.
 *
 * @param aCapacity Desired capacity.
 * @return true if the capacity was successfully obtained, false otherwise.
 */
bool rdObjectArray::
ensureCapacity(int aCapacity)
{
	// CHECK REQUESTED CAPACITY
	if(aCapacity<CAPMIN) aCapacity=CAPMIN;
	if(_capacity>=aCapacity) return(true);

	// ALLOCATE NEW ARRAY
	int i;
	rdObject **newArray = new rdObject*[aCapacity];
	if(newArray==NULL) return(false);
	for(i=0;i<aCapacity;i++)  newArray[i] = NULL;

	// COPY CURRENT ARRAY
	if(_array!=NULL) {
		for(i=0;i<_capacity;i++) newArray[i] = _array[i];
		delete []_array;  _array=NULL; 
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
int rdObjectArray::
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
 * If an increment is sent in that is less than 0 or this method
 * is called with no argument, the capacity is set to double whenever
 * the capacity is exceeded.
 *
 * @param aIncrement Desired capacity increment.  By default, the capacity
 * increment is set to double.
 */
void rdObjectArray::
setCapacityIncrement(int aIncrement)
{
	_capacityIncrement = aIncrement;
}
//_____________________________________________________________________________
/**
 * Get the amount by which the capacity is increased.
 */
int rdObjectArray::
getCapacityIncrement() const
{
	return(_capacityIncrement);
}


//=============================================================================
// RESET
//=============================================================================
//_____________________________________________________________________________
/**
 * Reset the storage to start storing at index 0.
 */
void rdObjectArray::
reset()
{
	_firstEmpty = 0;
}
//_____________________________________________________________________________
/**
 * Reset the storage to start storing after the specified index.
 */
void rdObjectArray::
reset(int aIndex)
{
	int i = aIndex + 1;
	if(i<0) {
		_firstEmpty = 0;
	} else if(i<_firstEmpty) {
		_firstEmpty = i;
	}
}


//=============================================================================
// STORAGE OPERATIONS
//=============================================================================
//_____________________________________________________________________________
/**
 * Get the index of the first empty array element.
 *
 * @return Index of the first empty array element.
 */
int rdObjectArray::
getFirstEmpty() const
{
	return(_firstEmpty);
}
//-----------------------------------------------------------------------------
// INDEX
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the index of the first object with the specified name.
 * A case-sensitive comparison of the specified name is performed to
 * identify the object.
 *
 * @param aName Name of the object.
 * @param aStart Index at which to start searching.  If no match is found,
 * the search restarts at index 0.  aStart has a default value of 0.
 * @return Index of the first object with the specified name.  If no
 * object is found with a matching name, -1 is returned.
 */
int rdObjectArray::
getIndex(const char *aName,int aStart) const
{
	if(aName==NULL) return(-1);
	if(aStart<0) aStart = 0;
	if(aStart>=getFirstEmpty()) aStart = 0;

	int i;
	rdObject *object;

	// SEARCH FROM aStart
	for(i=aStart;i<getFirstEmpty();i++) {
		object = get(i);
		if(object==NULL) continue;
		if(strcmp(aName,object->getName())==0) {
			return(i);
		}
	}

	// SEARCH FROM BEGINNING
	for(i=0;i<aStart;i++) {
		object = get(i);
		if(object==NULL) continue;
		if(strcmp(aName,object->getName())==0) {
			return(i);
		}
	}

	return(-1);
}
//_____________________________________________________________________________
/**
 * Get the index of an object by pointer value.
 *
 * @param aObject Pointer value of the object whose index is desired.
 * @return Index of the object; -1 if no such object is in the array.
 */
int rdObjectArray::
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
 * Set the pointer at a specified array index.
 *
 * If the index is greater than or equal to the capacity, sufficient capacity
 * is added.  It is permissible to set the value of an array element to NULL.
 *
 * @param aIndex Index of the array element being set.
 * @param aObject Pointer to an object or NULL.
 * @return Pointer to the object formerly at aIndex.  The caller is
 * responsible for deleting any non-null returned object.
 */
rdObject* rdObjectArray::
set(int aIndex,rdObject *aObject)
{
	if(aIndex<0) return(NULL);

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
rdObject* rdObjectArray::
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
rdObject* rdObjectArray::
getLast() const
{
	if(_firstEmpty<=0) return(NULL);
	return(_array[_firstEmpty-1]);
}
//_____________________________________________________________________________
/**
 * Append an object.
 *
 * @param aObject Object to be appended.
 * @return Index to the first empty element in the array (i.e., the end of
 * the array).
 */
int rdObjectArray::
append(rdObject *aObject)
{
	if(aObject==NULL) return(_firstEmpty);

	// CHECK FOR OVERFLOW
	if(_firstEmpty>=_capacity) {
		int newCapacity;
		if(_capacityIncrement < 0) {
			newCapacity = 2 * _capacity;

		} else if(_capacityIncrement == 0) {
			printf("rdObjectArray.append: WARN- capacity exceeded and ");
			printf("capacity increment is set to 0.\n");
			return(_firstEmpty);

		} else {
			newCapacity = _capacity + _capacityIncrement;
		}

		printf("rdObjectArray.append: ");
		printf("%s increasing capacity from %d to %d.\n",getName(),_capacity,
		 newCapacity);
		bool success = ensureCapacity(newCapacity);
		if(!success) {
			printf("rdObjectArray.append: WARN- ");
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
 * Append all the objects in an rdObjectArray object.
 */
int rdObjectArray::
append(rdObjectArray *aArray)
{
	if(aArray==NULL) return(_firstEmpty);

	// LOOP THROUGH THE STORED VECTORS
	int i;
	int n = aArray->getFirstEmpty();
	for(i=0;i<n;i++) {
		append(aArray->get(i));
	}

	return(_firstEmpty);
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
rdObject* rdObjectArray::
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
rdObject* rdObjectArray::
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


//=============================================================================
// XML
//=============================================================================
//-----------------------------------------------------------------------------
// UPDATE OBJECT
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Update this object based on its XML node.
 *
 * @param aDeep If true, update this object and all its child objects
 * (that is, member variables that are rdObject's); if false, update only
 * the member variables that are not rdObject's.
 */
void rdObjectArray::
updateObject(bool aDeep)
{
	if(_node==NULL) return;

	// BASE CLASS
	rdObject::updateObject(aDeep);

	// MEMBER DATA


	// MEMBER OBJECTS

}

//-----------------------------------------------------------------------------
// UPDATE NODE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Update the XML node representing this object.
 *
 * @param aDeep If true, update the XML node of this object AND the XML nodes
 * of all class members that are rdObjects (child nodes);  if false, update
 * only the XML node of this object without updating the XML nodes of its
 * children.
 */
void rdObjectArray::
updateNode(bool aDeep)
{
	// BASE CLASS
	rdObject::updateNode();
}













