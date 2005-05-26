// rdObservable.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2005- Stanford University
// All rights reserved.
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdObservable_h__
#define __rdObservable_h__

// INCLUDES
#include "rdArrayPtrs.h"
class rdEvent;
class rdObject;


// EXPORT LINE FOR MICROSOFT VISUAL C++
#ifndef UNIX
#ifndef SWIG
template class RDTOOLS_API rdArrayPtrs<rdObject>;
#endif
#endif


#ifdef SWIG
	#ifdef RDTOOLS_API
		#undef RDTOOLS_API
		#define RDTOOLS_API
	#endif
#endif

//=============================================================================
//=============================================================================
/**
 */
class RDTOOLS_API rdObservable  
{

//=============================================================================
// DATA
//=============================================================================
private:
	/** Array of all registered observers to the object */
	rdArrayPtrs<rdObject>	_observers;
	/** Subject being observed */
	const rdObject&			_subject;
	bool _changed;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	virtual ~rdObservable();
	rdObservable(const rdObject& aObject);
public:
	//--------------------------------------------------------------------------
	// Manage Observers
	//--------------------------------------------------------------------------
	void addObserver(rdObject& aObserver);
	void deleteObserver(rdObject& aObserver);
	void notifyObservers() const;
	/**
	 * Eventually observers will have to specify what event to observe so that they're not
	 * called unnecessarily. Will do this after the rdEvent class hierarchy matures. For now 
	 * we'll observe everything.
	 */
	void addEventObserver(rdObject& aObserver, rdEvent& aEvent) {};
	void notifyObservers(rdEvent& aEvent);
	void deleteObservers();
	int countObservers();

	//--------------------------------------------------------------------------
	// Manage _changed flag
	//--------------------------------------------------------------------------
	void setChanged();
	void clearChanged();
	bool hasChanged();

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
protected:

//=============================================================================
};	// END of class rdObservable
//=============================================================================
//=============================================================================

#endif //__rdObservable_h__
