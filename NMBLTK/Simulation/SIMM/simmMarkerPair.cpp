// simmMarkerPair.cpp
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
#include "simmMarkerPair.h"

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
simmMarkerPair::simmMarkerPair() :
	_markerNames(_markerNamesProp.getValueStrArray())
{
	setNull();
}
//_____________________________________________________________________________
/**
 * Constructor from an XML node
 */
simmMarkerPair::simmMarkerPair(DOMElement *aElement) :
   rdObject(aElement),
	_markerNames(_markerNamesProp.getValueStrArray())
{
	setNull();

	updateFromXMLNode();
}

//_____________________________________________________________________________
/**
 * Destructor.
 */
simmMarkerPair::~simmMarkerPair()
{
}

//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aMarkerPair simmMarkerPair to be copied.
 */
simmMarkerPair::simmMarkerPair(const simmMarkerPair &aMarkerPair) :
   rdObject(aMarkerPair),
	_markerNames(_markerNamesProp.getValueStrArray())
{
	setupProperties();
	copyData(aMarkerPair);
}
//_____________________________________________________________________________
/**
 * Copy this simmMarkerPair and return a pointer to the copy.
 * The copy constructor for this class is used.
 *
 * @return Pointer to a copy of this simmMarkerPair.
 */
rdObject* simmMarkerPair::copy() const
{
	simmMarkerPair *markerPair = new simmMarkerPair(*this);
	return(markerPair);
}
//_____________________________________________________________________________
/**
 * Copy this simmMarkerPair and modify the copy so that it is consistent
 * with a specified XML element node.
 *
 * The copy is constructed by first using
 * simmMarkerPair::simmMarkerPair(DOMElement*) in order to establish the
 * relationship of the simmMarkerPair object with the XML node. Then, the
 * assignment operator is used to set all data members of the copy to the
 * values of this simmMarkerPair object. Finally, the data members of the copy are
 * updated using simmMarkerPair::updateFromXMLNode().
 *
 * @param aElement XML element. 
 * @return Pointer to a copy of this simmMarkerPair.
 */
rdObject* simmMarkerPair::copy(DOMElement *aElement) const
{
	simmMarkerPair *markerPair = new simmMarkerPair(aElement);
	*markerPair = *this;
	markerPair->updateFromXMLNode();
	return(markerPair);
}

void simmMarkerPair::copyData(const simmMarkerPair &aMarkerPair)
{
	_markerNames = aMarkerPair._markerNames;
}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set the data members of this simmMarkerPair to their null values.
 */
void simmMarkerPair::setNull()
{
	setupProperties();
	setType("markerPair");
	setName("");
}
//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void simmMarkerPair::setupProperties()
{
	_markerNamesProp.setName("markers");
	_propertySet.append(&_markerNamesProp);
}

simmMarkerPair& simmMarkerPair::operator=(const simmMarkerPair &aMarkerPair)
{
	// BASE CLASS
	rdObject::operator=(aMarkerPair);

	copyData(aMarkerPair);

	return(*this);
}

void simmMarkerPair::getMarkerNames(const string*& aName1, const string*& aName2) const
{
	aName1 = &_markerNames[0];
	aName2 = &_markerNames[1];
}

void simmMarkerPair::peteTest() const
{
	cout << "         MarkerPair: " << getName() << endl;
	cout << "            _markerNames: " << _markerNames << endl;
}

