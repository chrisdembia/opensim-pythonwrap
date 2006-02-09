// simmBodyScale.cpp
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
#include "simmBodyScale.h"

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
simmBodyScale::simmBodyScale() :
	_axisNames(_axisNamesProp.getValueStrArray())
{
	setNull();
}
//_____________________________________________________________________________
/**
 * Constructor from an XML node
 */
simmBodyScale::simmBodyScale(DOMElement *aElement) :
   rdObject(aElement),
	_axisNames(_axisNamesProp.getValueStrArray())
{
	setNull();

	updateFromXMLNode();
}

//_____________________________________________________________________________
/**
 * Destructor.
 */
simmBodyScale::~simmBodyScale()
{
}

//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aBodyScale simmBodyScale to be copied.
 */
simmBodyScale::simmBodyScale(const simmBodyScale &aBodyScale) :
   rdObject(aBodyScale),
	_axisNames(_axisNamesProp.getValueStrArray())
{
	setupProperties();
	copyData(aBodyScale);
}
//_____________________________________________________________________________
/**
 * Copy this simmBodyScale and return a pointer to the copy.
 * The copy constructor for this class is used.
 *
 * @return Pointer to a copy of this simmBodyScale.
 */
rdObject* simmBodyScale::copy() const
{
	simmBodyScale *bodyScale = new simmBodyScale(*this);
	return(bodyScale);
}
//_____________________________________________________________________________
/**
 * Copy this simmBodyScale and modify the copy so that it is consistent
 * with a specified XML element node.
 *
 * The copy is constructed by first using
 * simmBodyScale::simmBodyScale(DOMElement*) in order to establish the
 * relationship of the simmBodyScale object with the XML node. Then, the
 * assignment operator is used to set all data members of the copy to the
 * values of this simmBodyScale object. Finally, the data members of the copy are
 * updated using simmBodyScale::updateFromXMLNode().
 *
 * @param aElement XML element. 
 * @return Pointer to a copy of this simmBodyScale.
 */
rdObject* simmBodyScale::copy(DOMElement *aElement) const
{
	simmBodyScale *bodyScale = new simmBodyScale(aElement);
	*bodyScale = *this;
	bodyScale->updateFromXMLNode();
	return(bodyScale);
}

void simmBodyScale::copyData(const simmBodyScale &aBodyScale)
{
	_axisNames = aBodyScale._axisNames;
}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set the data members of this simmBodyScale to their null values.
 */
void simmBodyScale::setNull()
{
	setupProperties();
	setType("bodyScale");
	setName("");
}
//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void simmBodyScale::setupProperties()
{
	_axisNamesProp.setName("axes");
	_propertySet.append(&_axisNamesProp);
}

simmBodyScale& simmBodyScale::operator=(const simmBodyScale &aBodyScale)
{
	// BASE CLASS
	rdObject::operator=(aBodyScale);

	copyData(aBodyScale);

	return(*this);
}

void simmBodyScale::peteTest() const
{
	cout << "         BodyScale: " << getName() << endl;
	cout << "            _axes: " << _axisNames << endl;
}

