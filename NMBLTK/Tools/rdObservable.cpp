// rdObservable.cpp

//============================================================================
// INCLUDES
//============================================================================
#include "rdObject.h"
#include "rdObservable.h"

//============================================================================
// CONSTANTS
//============================================================================

//=============================================================================
// CONSTRUCTOR(S)
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
rdObservable::~rdObservable()
{
	// rdArrayPtrs deletes memory on its own	
}

//_____________________________________________________________________________
/**
 * Default constructor.
 */
rdObservable::rdObservable(const rdObject& aObject):
_subject(aObject),
_changed(false)
{
	_observers.setMemoryOwner(false);
}

void rdObservable::
addObserver(rdObject& aObserver)
{
	if (_observers.getIndex(&aObserver)== -1)
		_observers.append(&aObserver);
}

void rdObservable::
deleteObserver(rdObject& aObserver)
{
	_observers.remove(&aObserver);
}

void rdObservable::
notifyObservers(rdEvent& aEvent)
{
	if (!_changed)
			return;
	clearChanged();

	for (int i =0; i< _observers.getSize(); i++){
		_observers.get(i)->update(_subject, aEvent);
	}

}
int rdObservable::
countObservers()
{
	return _observers.getSize();
}

void rdObservable::
deleteObservers()
{
	_observers.setSize(0);
}

void rdObservable::
setChanged()
{
	_changed=true;
}
void rdObservable::
clearChanged()
{
	_changed=false;
}
bool rdObservable::
hasChanged()
{
	return _changed;
}
