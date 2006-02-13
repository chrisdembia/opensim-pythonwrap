// simmMarker.cpp
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
#include "simmMarker.h"
#include "simmKinematicsEngine.h"

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
simmMarker::simmMarker() :
   _weight(_weightProp.getValueDbl()),
   _attachment(_attachmentProp.getValueDblArray()),
	_fixed(_fixedProp.getValueBool()),
	_bodyName(_bodyNameProp.getValueStr())
{
	setNull();
}
//_____________________________________________________________________________
/**
 * Constructor from an XML node
 */
simmMarker::simmMarker(DOMElement *aElement) :
   rdObject(aElement),
   _weight(_weightProp.getValueDbl()),
   _attachment(_attachmentProp.getValueDblArray()),
	_fixed(_fixedProp.getValueBool()),
	_bodyName(_bodyNameProp.getValueStr())
{
	setNull();

	updateFromXMLNode();
}

//_____________________________________________________________________________
/**
 * Destructor.
 */
simmMarker::~simmMarker()
{
}

//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aMarker simmMarker to be copied.
 */
simmMarker::simmMarker(const simmMarker &aMarker) :
   rdObject(aMarker),
   _weight(_weightProp.getValueDbl()),
   _attachment(_attachmentProp.getValueDblArray()),
	_fixed(_fixedProp.getValueBool()),
	_bodyName(_bodyNameProp.getValueStr())
{
	setupProperties();
	copyData(aMarker);
}
//_____________________________________________________________________________
/**
 * Copy this simmMarker and return a pointer to the copy.
 * The copy constructor for this class is used.
 *
 * @return Pointer to a copy of this simmMarker.
 */
rdObject* simmMarker::copy() const
{
	simmMarker *marker = new simmMarker(*this);
	return(marker);
}
//_____________________________________________________________________________
/**
 * Copy this simmMarker and modify the copy so that it is consistent
 * with a specified XML element node.
 *
 * The copy is constructed by first using
 * simmMarker::simmMarker(DOMElement*) in order to establish the
 * relationship of the simmMarker object with the XML node. Then, the
 * assignment operator is used to set all data members of the copy to the
 * values of this simmMarker object. Finally, the data members of the copy are
 * updated using simmMarker::updateFromXMLNode().
 *
 * @param aElement XML element. 
 * @return Pointer to a copy of this simmMarker.
 */
rdObject* simmMarker::copy(DOMElement *aElement) const
{
	simmMarker *marker = new simmMarker(aElement);
	*marker = *this;
	marker->updateFromXMLNode();
	return(marker);
}

void simmMarker::copyData(const simmMarker &aMarker)
{
	_attachment = aMarker._attachment;
	_weight = aMarker._weight;
	_fixed = aMarker._fixed;
	_bodyName = aMarker._bodyName;
}

/* Update an existing marker with parameter values from a
 * new one, but only for the parameters that were explicitly
 * specified in the XML node.
 */
void simmMarker::updateFromMarker(const simmMarker &aMarker)
{
	if (!aMarker._attachmentProp.getUseDefault())
		_attachment = aMarker._attachment;

	if (!aMarker._weightProp.getUseDefault())
		_weight = aMarker._weight;

	if (!aMarker._fixedProp.getUseDefault())
		_fixed = aMarker._fixed;

	if (!aMarker._bodyNameProp.getUseDefault())
		_bodyName = aMarker._bodyName;
}

//_____________________________________________________________________________
/**
 * Set the data members of this simmMarker to their null values.
 */
void simmMarker::setNull()
{
	setupProperties();
	setType("marker");
	setName("");
}
//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void simmMarker::setupProperties()
{
	_weightProp.setName("weight");
	_weightProp.setValue(0.0);
	_propertySet.append(&_weightProp);

	const double defaultAttachment[] = {0.0, 0.0, 0.0};
	_attachmentProp.setName("location");
	_attachmentProp.setValue(3, defaultAttachment);
	_propertySet.append(&_attachmentProp);

	_fixedProp.setName("fixed");
	_fixedProp.setValue(false);
	_propertySet.append(&_fixedProp);

	_bodyNameProp.setName("body");
	_propertySet.append(&_bodyNameProp);
}

simmMarker& simmMarker::operator=(const simmMarker &aMarker)
{
	// BASE CLASS
	rdObject::operator=(aMarker);

	copyData(aMarker);

	return(*this);
}

void simmMarker::getOffset(double *aOffset) const
{
	if (aOffset)
	{
		for (int i = 0; i < 3; i++)
			aOffset[i] = _attachment[i];
	}
}

void simmMarker::setOffset(double aPoint[3])
{
	for (int i = 0; i < 3; i++)
		_attachment[i] = aPoint[i];
}

void simmMarker::scale(rdArray<double>& aScaleFactors)
{
	for (int i = 0; i < 3; i++)
		_attachment[i] *= aScaleFactors[i];
}

/* Perform some set up functions that happen after the
 * object has been deserialized or copied.
 */
void simmMarker::setup(simmKinematicsEngine* aEngine)
{
}

const string* simmMarker::getBodyName() const
{
	if (_bodyNameProp.getUseDefault())
		return NULL;

	return &_bodyName;
}

void simmMarker::writeSIMM(ofstream& out) const
{
	out << "marker " << getName() << '\t' << _attachment[0] << " " << _attachment[1] << " " << _attachment[2] << " " << _weight;
	if (_fixed)
		out << " fixed";
	out << endl;
}

void simmMarker::peteTest() const
{
	cout << "   Marker: " << getName() << endl;
	cout << "      location: " << _attachment << endl;
	cout << "      weight: " << _weight << endl;
	cout << "      fixed: " << ((_fixed) ? ("true") : ("false")) << endl;
}

