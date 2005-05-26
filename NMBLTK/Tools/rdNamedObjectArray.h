// rdNamedObjectArray.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2003 Stanford University, Inc.
// All rights reserved.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdNamedObjectArray_h__
#define __rdNamedObjectArray_h__


#include <vector>
#include "rdTools.h"
#include "rdException.h"

//=============================================================================
//=============================================================================
/**
* A class for maintaining an array of rdObject*. Used to provide base class 
* for lookup operations by rdModel
* 
* @version 1.0
* @author Ayman Habib
*
* 
*/
template <class T> class rdNamedObjectArray
{
private:
	std::vector<T*>	_objects;
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// METHODS
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//=============================================================================
	// CONTRUCTION
	//=============================================================================
public:
	rdNamedObjectArray() {};
	//____________________________________________________________________________
	/**
	* Constructor with pre-specified size
	*/
	rdNamedObjectArray(int aSize) { _objects.resize(aSize);};
	
	//____________________________________________________________________________
	/**
	* Destructor.
	*/
	virtual ~rdNamedObjectArray()
	{
		_objects.erase(_objects.begin(), _objects.end());
	};

	//____________________________________________________________________________
	/**
	* This function frees the memory used by pointers saved in the array
	* callers should keep track if pointers maintained by this object have been freed
	* or not to avoid double deletion.
	*/
	void clearAndDestroy()
	{
		for(std::vector<T*>::iterator iter = _objects.begin(); 
								 iter != _objects.end(); 
								 iter++){
			delete (*iter);
		}
		_objects.erase(_objects.begin(), _objects.end());

	}
	//=============================================================================
	// Operations
	//=============================================================================
	//____________________________________________________________________________
	/**
	 * Check if vector is empty
	 */
	bool empty() const
	{
		return _objects.empty();
	}

	//____________________________________________________________________________
	/**
	 * Append to the end of the vector
	 */
	void append(T* aObjectPtr) { _objects.push_back(aObjectPtr); };
	//____________________________________________________________________________
	/**
	 * Get number of objects in Vector
	 */
	int getSize() const
	{
		return _objects.size();
	};

	//____________________________________________________________________________
	/**
	 * Get objects that live in Vector as a raw array of pointers
	 */
	void getObjects(T*& aObjectsArray) const
	{
		int idx=0;
		for(std::vector<T*>::iterator iter = _objects.begin(); 
								 iter != _objects.end(); 
								 iter++, idx++){
			aObjectsArray[idx] = _objects[idx];
		}
	};

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	//____________________________________________________________________________
	/**
	 * Get object with index idx
	 * returns 0 if not found.
	 */
	T *getByIndex(int idx) const
	{
		if (idx <0 || idx > getSize()-1){
			return ((T *)0);
		}
		// index is in range
		return _objects[idx];
	};

	//____________________________________________________________________________
	/**
	 * Get object based on name.
	 * returns 0 if not found.
	 */
	T *getByName(std::string &aName)const
	{
		T *returnObject=0;

		for(std::vector<T*>::const_iterator iter = _objects.begin(); 
								 iter != _objects.end(); 
								 iter++){
			if ((*iter)->getName() == aName){
				returnObject = (*iter);
				break;
			}
		}
		return returnObject;
	};

	//____________________________________________________________________________
	/**
	 * Set the name of the object at position idx.
	 */
	void setObjectName(int idx, std::string& aName) 
	{
		T* object= getByIndex(idx);
		if (object)
			object->setName(aName);
	};

	//____________________________________________________________________________
	/**
	 * Get the name of the object at position idx.
	 */
	const char *getObjectName(int idx) const
	{
		T* object= getByIndex(idx);
		if (object)
			return (object->getName());
	};

	//____________________________________________________________________________
	/**
	 * Get the index of an object given its name.
	 */
	int getIndex(const std::string& objName) 
	{
		int returnIndex=-1;
		int idx=0;
			
		for(std::vector<T*>::iterator iter = _objects.begin(); 
			iter != _objects.end();
			iter++, idx++){
				if (strcmp((*iter)->getName(), objName.c_str())==0){
					returnIndex  = idx;
					break;
				}
			}

		return returnIndex;
	};
	/**
	 * Indexing with aIndex, const object
	 */
	const T* operator[](int aIndex) const
	{
		return(_objects[aIndex]);
	}
	/**
	 * Indexing by name, const object
	 * If name is not found this will index out of bounds and throw an exception
	 */
	const T* operator[](const std::string& aName) const
	{
		int aIndex = getIndex(aName);
		return (_objects[aIndex]);

	}

	/**
	 * Indexing with aIndex, non-const object
	 */
	T* operator[](int aIndex)
	{
		return(_objects[aIndex]);
	}
	/**
	 * Indexing by name, non-const object
	 * If name is not found this will index out of bounds and throw an exception
	 */
	T* operator[](const std::string& aName)
	{
		int aIndex = getIndex(aName);
		return (_objects[aIndex]);
	}

	//=============================================================================
};	// END of class rdNamedObjectArray






#endif //__rdNamedObjectArray_h__
