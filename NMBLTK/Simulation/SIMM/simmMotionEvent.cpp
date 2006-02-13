// simmMotionEvent.cpp
// Author: Peter Loan
/* Copyright (c) 2005, Stanford University and Peter Loan.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including 
 * without limitation the rights to use, copy, modify, merge, publish, 
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included 
 * in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


//=============================================================================
// INCLUDES
//=============================================================================
#include "simmMotionEvent.h"

//=============================================================================
// STATICS
//=============================================================================
using namespace std;

//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Default constructor.
 */
simmMotionEvent::simmMotionEvent() :
	_time(_timeProp.getValueDbl()),
	_color(_colorProp.getValueDblArray())
{
	setNull();
}
//_____________________________________________________________________________
/**
 * Constructor from an XML node
 */
simmMotionEvent::simmMotionEvent(DOMElement *aElement) :
   rdObject(aElement),
	_time(_timeProp.getValueDbl()),
	_color(_colorProp.getValueDblArray())
{
	setNull();
	updateFromXMLNode();
}

//_____________________________________________________________________________
/**
 * Destructor.
 */
simmMotionEvent::~simmMotionEvent()
{
}

//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aEvent simmMotionEvent to be copied.
 */
simmMotionEvent::simmMotionEvent(const simmMotionEvent &aEvent) :
   rdObject(aEvent),
	_time(_timeProp.getValueDbl()),
	_color(_colorProp.getValueDblArray())
{
	setupProperties();
	copyData(aEvent);
}
//_____________________________________________________________________________
/**
 * Copy this simmMotionEvent and return a pointer to the copy.
 * The copy constructor for this class is used.
 *
 * @return Pointer to a copy of this simmMotionEvent.
 */
rdObject* simmMotionEvent::copy() const
{
	simmMotionEvent *event = new simmMotionEvent(*this);
	return(event);
}
//_____________________________________________________________________________
/**
 * Copy this simmMotionEvent and modify the copy so that it is consistent
 * with a specified XML element node.
 *
 * The copy is constructed by first using
 * simmGenericModelParams::simmGenericModelParams(DOMElement*) in order to establish the
 * relationship of the simmGenericModelParams object with the XML node. Then, the
 * assignment operator is used to set all data members of the copy to the
 * values of this simmGenericModelParams object. Finally, the data members of the copy are
 * updated using simmGenericModelParams::updateFromXMLNode().
 *
 * @param aElement XML element. 
 * @return Pointer to a copy of this simmMotionEvent.
 */
rdObject* simmMotionEvent::copy(DOMElement *aElement) const
{
	simmMotionEvent *event = new simmMotionEvent(aElement);
	*event = *this;
	event->updateFromXMLNode();
	return(event);
}

void simmMotionEvent::copyData(const simmMotionEvent &aEvent)
{
	_time = aEvent._time;
	_color = aEvent._color;
}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set the data members of this simmMotionEvent to their null values.
 */
void simmMotionEvent::setNull()
{
	setupProperties();
	setType("event");
	setName("");
}
//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void simmMotionEvent::setupProperties()
{
	_timeProp.setName("time");
	_propertySet.append(&_timeProp);

	_colorProp.setName("color");
	_propertySet.append(&_colorProp);
}

simmMotionEvent& simmMotionEvent::operator=(const simmMotionEvent &aEvent)
{
	// BASE CLASS
	rdObject::operator=(aEvent);

	copyData(aEvent);

	return(*this);
}

void simmMotionEvent::setColor(double* aColor)
{
	for (int i = 0; i < 3; i++)
		_color[i] = aColor[i];
}

void simmMotionEvent::peteTest() const
{
	cout << "   Event: " << getName() << endl;
	cout << "      time: " << _time << endl;
	cout << "      color: " << _color << endl;
}

