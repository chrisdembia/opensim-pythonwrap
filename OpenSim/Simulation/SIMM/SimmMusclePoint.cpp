// SimmMusclePoint.cpp
// Author: Peter Loan
/*
 * Copyright (c) 2006, Stanford University. All rights reserved. 
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
#include "SimmMusclePoint.h"
#include "BodySet.h"
#include "AbstractModel.h"
#include "AbstractSimmMuscle.h"
#include "AbstractDynamicsEngine.h"
#include "AbstractWrapObject.h"

//=============================================================================
// STATICS
//=============================================================================
using namespace std;
using namespace OpenSim;

Geometry *SimmMusclePoint::_defaultGeometry= AnalyticGeometry::createSphere(0.005);

//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Default constructor.
 */
SimmMusclePoint::SimmMusclePoint() :
   _attachment(_attachmentProp.getValueDblArray()),
	_bodyName(_bodyNameProp.getValueStr()),
	_displayerProp(PropertyObj("", VisibleObject())),
   _displayer((VisibleObject&)_displayerProp.getValueObj())
{
	setNull();
	setupProperties();
}
//_____________________________________________________________________________
/**
 * Constructor from an XML node
 */
SimmMusclePoint::SimmMusclePoint(DOMElement *aElement) :
   Object(aElement),
   _attachment(_attachmentProp.getValueDblArray()),
	_bodyName(_bodyNameProp.getValueStr()),
	_displayerProp(PropertyObj("", VisibleObject())),
   _displayer((VisibleObject&)_displayerProp.getValueObj())
{
	setNull();
	setupProperties();
	updateFromXMLNode();
}

//_____________________________________________________________________________
/**
 * Destructor.
 */
SimmMusclePoint::~SimmMusclePoint()
{
}

//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aPoint SimmMusclePoint to be copied.
 */
SimmMusclePoint::SimmMusclePoint(const SimmMusclePoint &aPoint) :
   Object(aPoint),
   _attachment(_attachmentProp.getValueDblArray()),
	_bodyName(_bodyNameProp.getValueStr()),
	_displayerProp(PropertyObj("", VisibleObject())),
   _displayer((VisibleObject&)_displayerProp.getValueObj())
{
	setNull();
	setupProperties();
	copyData(aPoint);
}

//_____________________________________________________________________________
/**
 * Copy this muscle point and return a pointer to the copy.
 * The copy constructor for this class is used.
 *
 * @return Pointer to a copy of this SimmMusclePoint.
 */
Object* SimmMusclePoint::copy() const
{
	SimmMusclePoint *pt = new SimmMusclePoint(*this);
	return(pt);
}

//_____________________________________________________________________________
/**
 * Copy this SimmMusclePoint and modify the copy so that it is consistent
 * with a specified XML element node.
 *
 * The copy is constructed by first using
 * SimmMusclePoint::SimmMusclePoint(DOMElement*) in order to establish the
 * relationship of the SimmMusclePoint object with the XML node. Then, the
 * assignment operator is used to set all data members of the copy to the
 * values of this SimmMusclePoint object. Finally, the data members of the
 * copy are updated using SimmMusclePoint::updateFromXMLNode().
 *
 * @param aElement XML element. 
 * @return Pointer to a copy of this SimmMusclePoint.
 */
Object* SimmMusclePoint::copy(DOMElement *aElement) const
{
	SimmMusclePoint *pt = new SimmMusclePoint(aElement);
	*pt = *this;
	pt->updateFromXMLNode();
	return(pt);
}

//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Copy data members from one SimmMusclePoint to another.
 *
 * @param aPoint SimmMusclePoint to be copied.
 */
void SimmMusclePoint::copyData(const SimmMusclePoint &aPoint)
{
	_attachment = aPoint._attachment;
	_displayer = aPoint._displayer;
	_bodyName = aPoint._bodyName;
	_body = aPoint._body;
}

//_____________________________________________________________________________
/**
 * Set the data members of this SimmMusclePoint to their null values.
 */
void SimmMusclePoint::setNull()
{
	setType("SimmMusclePoint");

	_body = NULL;
}

//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void SimmMusclePoint::setupProperties()
{
	const double defaultAttachment[] = {0.0, 0.0, 0.0};
	_attachmentProp.setName("location");
	_attachmentProp.setValue(3, defaultAttachment);
	_propertySet.append(&_attachmentProp);

	_displayerProp.setName("display");
	_propertySet.append(&_displayerProp);

	_bodyNameProp.setName("body");
	_propertySet.append(&_bodyNameProp);
}

//_____________________________________________________________________________
/**
 * Perform some set up functions that happen after the
 * object has been deserialized or copied.
 *
 * @param aModel model containing this SimmMusclePoint.
 */
void SimmMusclePoint::setup(AbstractModel* aModel, AbstractSimmMuscle* aMuscle)
{
	// Look up the body by name in the kinematics engine and
	// store a pointer to it.
	_body = aModel->getDynamicsEngine().getBodySet()->get(_bodyName);

	if (!_body)
	{
		string errorMessage = "Body " + _bodyName + " referenced in muscle " + aMuscle->getName() + " not found in model " + aModel->getName();
		throw Exception(errorMessage);
	}

	_displayer.setOwner(this);
	// Muscle points depend on body
	_body->getDisplayer()->addDependent(&_displayer);
	_displayer.addGeometry(_defaultGeometry);

	Transform position;
	position.translate(_attachment.get());
	getDisplayer()->setTransform(position);
	double defaultColor[3] = { 1.0, 0.0, 0.0 };
	_displayer.getVisibleProperties().setColor(defaultColor);
}
//_____________________________________________________________________________
/**
 * Update geometry of the muscle point.
 *
 */
void SimmMusclePoint::updateGeometry()
{
	Transform position;
	position.translate(_attachment.get());
	getDisplayer()->setTransform(position);
}
//=============================================================================
// OPERATORS
//=============================================================================
//_____________________________________________________________________________
/**
 * Assignment operator.
 *
 * @return Reference to this object.
 */
SimmMusclePoint& SimmMusclePoint::operator=(const SimmMusclePoint &aPoint)
{
	// BASE CLASS
	Object::operator=(aPoint);

	copyData(aPoint);

	return(*this);
}

//=============================================================================
// SCALING
//=============================================================================
//_____________________________________________________________________________
/**
 * Scale the muscle point.
 *
 * @param aScaleFactors the XYZ scale factors to scale the point by.
 */
void SimmMusclePoint::scale(Array<double>& aScaleFactors)
{
	for (int i = 0; i < 3; i++)
		_attachment[i] *= aScaleFactors[i];

	updateGeometry();
}

void SimmMusclePoint::peteTest() const
{
	cout << "   MusclePoint: " << getName() << endl;
	cout << "      point: " << getAttachment() << endl;
	if (_body)
		cout << "      body: " << _body->getName() << endl;
}
