// Marker.cpp
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
#include "Marker.h"
#include "AbstractModel.h"
#include "AbstractDynamicsEngine.h"
#include "BodySet.h"

//=============================================================================
// STATICS
//=============================================================================
using namespace std;
using namespace OpenSim;

Geometry *Marker::_defaultGeometry = AnalyticSphere::createSphere(0.01);
//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Default constructor.
 */
Marker::Marker() :
   _offset(_offsetProp.getValueDblArray()),
	_fixed(_fixedProp.getValueBool()),
	_bodyName(_bodyNameProp.getValueStr()),
	_displayerProp(PropertyObj("", VisibleObject())),
   _displayer((VisibleObject&)_displayerProp.getValueObj())
{
	setNull();
	setupProperties();
	_displayer.setOwner(this);
}

//_____________________________________________________________________________
/**
 * Destructor.
 */
Marker::~Marker()
{
}

//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aMarker Marker to be copied.
 */
Marker::Marker(const Marker &aMarker) :
   AbstractMarker(aMarker),
   _offset(_offsetProp.getValueDblArray()),
	_fixed(_fixedProp.getValueBool()),
	_bodyName(_bodyNameProp.getValueStr()),
	_displayerProp(PropertyObj("", VisibleObject())),
   _displayer((VisibleObject&)_displayerProp.getValueObj())
{
	setNull();
	setupProperties();
	copyData(aMarker);
	_displayer.setOwner(this);
}

//_____________________________________________________________________________
/**
 * Copy this Marker and return a pointer to the copy.
 * The copy constructor for this class is used.
 *
 * @return Pointer to a copy of this Marker.
 */
Object* Marker::copy() const
{
	Marker *marker = new Marker(*this);
	return(marker);
}

//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Copy data members from one Marker to another.
 *
 * @param aMarker Marker to be copied.
 */
void Marker::copyData(const Marker &aMarker)
{
	_offset = aMarker._offset;
	_fixed = aMarker._fixed;
	_bodyName = aMarker._bodyName;
	_displayer = aMarker._displayer;
	_virtual = aMarker._virtual;
}

//_____________________________________________________________________________
/**
 * Set the data members of this Marker to their null values.
 */
void Marker::setNull()
{
	setType("Marker");
	setVirtual(true);
	_body = 0;
}

//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void Marker::setupProperties()
{
	_bodyNameProp.setComment("VisibleBody segment in the model on which the marker resides.");
	_bodyNameProp.setName("body");
	_propertySet.append(&_bodyNameProp);

	_offsetProp.setComment("Location of a marker on the body segment.");
	const double defaultAttachment[] = {0.0, 0.0, 0.0};
	_offsetProp.setName("location");
	_offsetProp.setValue(3, defaultAttachment);
	_propertySet.append(&_offsetProp);

	_fixedProp.setComment("Flag (true or false) specifying whether or not a marker "
		"should be kept fixed in the marker placement step.  i.e. If false, the marker is allowed to move.");
	_fixedProp.setName("fixed");
	_fixedProp.setValue(false);
	_propertySet.append(&_fixedProp);

	_displayerProp.setComment("Used for displaying a marker in the visuals.");
	_displayerProp.setName("Displayer");
	_propertySet.append(&_displayerProp);
}

//_____________________________________________________________________________
/**
 * Perform some set up functions that happen after the
 * object has been deserialized or copied.
 *
 * @param aEngine dynamics engine containing this Marker.
 */
void Marker::setup(AbstractDynamicsEngine* aEngine)
{
	if (_bodyName != "")
	{
		AbstractBody *oldBody = _body;
		_body = aEngine->getBodySet()->get(_bodyName);

		if (!_body)
		{
			string errorMessage = "Error: VisibleBody " + _bodyName + " referenced in marker " + getName() +
				" does not exist in model " +	aEngine->getModel()->getName();
			throw Exception(errorMessage);
		}
		// If marker jumped between bodies we need to fix display stuff
		if (oldBody && oldBody != _body){
			oldBody->getDisplayer()->removeDependent(&_displayer);
		}
		//TODO: make code below safe to call multiple times (since this setup() method may be
		//called multiple times for a simm marker).  Should also try to handle case where a marker
		// is deleted (e.g. in AbstractDynamicsEngine::updateMarkerSet) because then may end up with
		// stale pointers.
		VisibleObject* ownerBodyDisplayer;
		if (_body && (ownerBodyDisplayer = _body->getDisplayer())){
			if(! ownerBodyDisplayer->hasDependent(&_displayer)){	// Only if first time to be encountered 
				ownerBodyDisplayer->addDependent(&_displayer);
				_displayer.addGeometry(_defaultGeometry);
			}
		}
		_displayer.setOwner(this);
		double defaultColor[3] = { 0.0, 0.0, 1.0 };
		_displayer.getVisibleProperties().setColor(defaultColor);
		updateGeometry();
			
	}
	else
	{
		string errorMessage = "Error: No body name specified for marker " + getName() + " in model " +
			aEngine->getModel()->getName();
		throw Exception(errorMessage);
	}
}
//_____________________________________________________________________________
/**
 * Remove self from the list of displayable objects and free resources
 */
void Marker::removeSelfFromDisplay()
{
		VisibleObject* ownerBodyDisplayer;
		if (_body && (ownerBodyDisplayer = _body->getDisplayer())){
			if (ownerBodyDisplayer->hasDependent(&_displayer)){
				ownerBodyDisplayer->removeDependent(&_displayer);
			}
		}
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
Marker& Marker::operator=(const Marker &aMarker)
{
	// BASE CLASS
	AbstractMarker::operator=(aMarker);

	copyData(aMarker);

	return(*this);
}

//=============================================================================
// UTILITY
//=============================================================================
//_____________________________________________________________________________
/**
 * Update an existing marker with parameter values from a
 * new one, but only for the parameters that were explicitly
 * specified in the XML node.
 *
 * @param aMarker marker to update from
 */
void Marker::updateFromMarker(const AbstractMarker &aMarker)
{
	if (!aMarker.getOffsetUseDefault())
	{
		const double* off = aMarker.getOffset();
		setOffset(off);
		_offsetProp.setUseDefault(false);
	}

	if (!aMarker.getFixedUseDefault())
	{
		_fixed = aMarker.getFixed();
		_fixedProp.setUseDefault(false);
	}

	if (!aMarker.getBodyNameUseDefault())
	{	
		_bodyName = *aMarker.getBodyName();
		_bodyNameProp.setUseDefault(false);
	}
}

//=============================================================================
// GET AND SET
//=============================================================================
//_____________________________________________________________________________
/**
 * Get the marker's XYZ offset from the body it's attached to.
 *
 * @param rOffset XYZ offset is returned here.
 */
void Marker::getOffset(double *rOffset) const
{
	if (rOffset)
	{
		for (int i = 0; i < 3; i++)
			rOffset[i] = _offset[i];
	}
}

//_____________________________________________________________________________
/**
 * Set the marker's XYZ offset from the body it's attached to.
 *
 * @param aOffset XYZ offset to set to.
 * @return Whether or not the offset was set.
 */
bool Marker::setOffset(Array<double>& aOffset)
{
	_offset[0] = aOffset[0];
	_offset[1] = aOffset[1];
	_offset[2] = aOffset[2];

	updateGeometry();
	return true;
}

//_____________________________________________________________________________
/**
 * Set the marker's XYZ offset from the body it's attached to.
 *
 * @param aPoint XYZ offset to set to.
 * @return Whether or not the offset was set.
 */
bool Marker::setOffset(const double aPoint[3])
{
	for (int i = 0; i < 3; i++)
		_offset[i] = aPoint[i];

	updateGeometry();
	return true;
}

//_____________________________________________________________________________
/**
 * Set the marker's fixed status.
 *
 * @param aFixed boolean value to set to.
 * @return Whether or not the fixed status was set.
 */
bool Marker::setFixed(bool aFixed)
{
	_fixed = aFixed;
	return true;
}

//_____________________________________________________________________________
/**
 * Set the 'body name' field, which is used when the marker is added to
 * an existing model.
 *
 * @param aName name of body
 * @return Whether or not the body name was set.
 */
bool Marker::setBodyName(const string& aName)
{
	_bodyName = aName;

	return true;
}

//_____________________________________________________________________________
/**
 * Get the 'body name' field, which is used when the marker is added to
 * an existing model.
 *
 * @return Pointer to the body name.
 */
const string* Marker::getBodyName() const
{
	if (_bodyNameProp.getUseDefault())
		return NULL;

	return &_bodyName;
}

//_____________________________________________________________________________
/**
 * Set the 'body name' field to use or not use the default value.
 *
 * @return Whether or not the flag was set properly.
 */
bool Marker::setBodyNameUseDefault(bool aValue)
{
	_bodyNameProp.setUseDefault(aValue);

	return true;
}

//_____________________________________________________________________________
/**
 * Set the body that this marker is attached to.
 *
 * @param aBody Pointer to the body.
 */
void Marker::setBody(AbstractBody* aBody)
{
	_body = aBody;
	// TODO: should body and bodyName be synced when either one is changed?
}

//=============================================================================
// SCALING
//=============================================================================
//_____________________________________________________________________________
/**
 * Scale the marker.
 *
 * @param aScaleFactors XYZ scale factors.
 */
void Marker::scale(const Array<double>& aScaleFactors)
{
	for (int i = 0; i < 3; i++)
		_offset[i] *= aScaleFactors[i];
}

//_____________________________________________________________________________
/**
 * Update the geometry to correspond to position changes
 */
void Marker::updateGeometry()
{
	Transform position;
	position.translate(getOffset());
	getDisplayer()->setTransform(position);

}
void Marker::peteTest() const
{
	cout << "   VisibleMarker: " << getName() << endl;
	cout << "      location: " << _offset << endl;
	cout << "      fixed: " << ((_fixed) ? ("true") : ("false")) << endl;
}
