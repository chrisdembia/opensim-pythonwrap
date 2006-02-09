// simmMusclePoint.cpp
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
#include "simmMusclePoint.h"
#include "simmModel.h"
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
simmMusclePoint::simmMusclePoint() :
   _attachment(_attachmentProp.getValueDblArray()),
	_bodyName(_bodyNameProp.getValueStr())
{
	setNull();

}
//_____________________________________________________________________________
/**
 * Constructor from an XML node
 */
simmMusclePoint::simmMusclePoint(DOMElement *aElement) :
   rdVisibleObject(aElement),
   _attachment(_attachmentProp.getValueDblArray()),
	_bodyName(_bodyNameProp.getValueStr())
{
	setNull();

	updateFromXMLNode();
}

//_____________________________________________________________________________
/**
 * Destructor.
 */
simmMusclePoint::~simmMusclePoint()
{
}

//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aPoint simmMusclePoint to be copied.
 */
simmMusclePoint::simmMusclePoint(const simmMusclePoint &aPoint) :
   rdVisibleObject(aPoint),
   _attachment(_attachmentProp.getValueDblArray()),
	_bodyName(_bodyNameProp.getValueStr())
{
	setupProperties();
	copyData(aPoint);
}
//_____________________________________________________________________________
/**
 * Copy this muscle point and return a pointer to the copy.
 * The copy constructor for this class is used.
 *
 * @return Pointer to a copy of this simmMusclePoint.
 */
rdObject* simmMusclePoint::copy() const
{
	simmMusclePoint *pt = new simmMusclePoint(*this);
	return(pt);
}
//_____________________________________________________________________________
/**
 * Copy this simmMusclePoint and modify the copy so that it is consistent
 * with a specified XML element node.
 *
 * The copy is constructed by first using
 * simmMusclePoint::simmMusclePoint(DOMElement*) in order to establish the
 * relationship of the simmMusclePoint object with the XML node. Then, the
 * assignment operator is used to set all data members of the copy to the
 * values of this simmMusclePoint object. Finally, the data members of the
 * copy are updated using simmMusclePoint::updateFromXMLNode().
 *
 * @param aElement XML element. 
 * @return Pointer to a copy of this simmMusclePoint.
 */
rdObject* simmMusclePoint::copy(DOMElement *aElement) const
{
	simmMusclePoint *pt = new simmMusclePoint(aElement);
	*pt = *this;
	pt->updateFromXMLNode();
	return(pt);
}

void simmMusclePoint::copyData(const simmMusclePoint &aPoint)
{
	_attachment = aPoint._attachment;
	_bodyName = aPoint._bodyName;
	_body = aPoint._body;
}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set the data members of this simmMusclePoint to their null values.
 */
void simmMusclePoint::setNull()
{
	setupProperties();
	setType("musclePoint");
	setName("");
}
//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void simmMusclePoint::setupProperties()
{
	const double defaultAttachment[] = {0.0, 0.0, 0.0};
	_attachmentProp.setName("location");
	_attachmentProp.setValue(3, defaultAttachment);
	_propertySet.append(&_attachmentProp);

	_bodyNameProp.setName("body");
	_propertySet.append(&_bodyNameProp);
}

simmMusclePoint& simmMusclePoint::operator=(const simmMusclePoint &aPoint)
{
	// BASE CLASS
	rdVisibleObject::operator=(aPoint);

	copyData(aPoint);

	return(*this);
}

void simmMusclePoint::scale(rdArray<double>& aScaleFactors)
{
	for (int i = 0; i < 3; i++)
		_attachment[i] *= aScaleFactors[i];
}

void simmMusclePoint::writeSIMM(ofstream& out) const
{
	out << _attachment[0] << " " << _attachment[1] << " " << _attachment[2] << " segment " << _bodyName << endl;
}

/* Perform some set up functions that happen after the
 * object has been deserialized or copied.
 */
void simmMusclePoint::setup(simmModel* model, simmKinematicsEngine* ke)
{
	/* Look up the body by name in the kinematics engine and
	 * store a pointer to it.
	 */
	_body = ke->getBody(_bodyName);
}

void simmMusclePoint::peteTest() const
{
	cout << "   MusclePoint: " << getName() << endl;
	cout << "      point: " << getAttachment() << endl;
	cout << "      body: " << _body->getName() << endl;
}
