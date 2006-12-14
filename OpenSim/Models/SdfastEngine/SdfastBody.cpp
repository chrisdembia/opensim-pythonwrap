// SdfastBody.cpp
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
#include "SdfastBody.h"
#include "SdfastEngine.h"
#include <OpenSim/Simulation/SIMM/SimmMacros.h>

//=============================================================================
// STATICS
//=============================================================================
using namespace std;
using namespace OpenSim;

//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Default constructor.
 */
SdfastBody::SdfastBody() :
   _massCenter(_massCenterProp.getValueDblArray()),
	_displayerProp(PropertyObj("", VisibleObject())),
   _displayer((VisibleObject&)_displayerProp.getValueObj()),
	_index(_indexProp.getValueInt()),
	_SdfastEngine(NULL)
{
	setNull();
	setupProperties();
}

//_____________________________________________________________________________
/**
 * Constructor from an XML node
 */
SdfastBody::SdfastBody(DOMElement *aElement) :
   AbstractBody(aElement),
   _massCenter(_massCenterProp.getValueDblArray()),
	_displayerProp(PropertyObj("", VisibleObject())),
   _displayer((VisibleObject&)_displayerProp.getValueObj()),
	_index(_indexProp.getValueInt()),
	_SdfastEngine(NULL)
{
	setNull();
	setupProperties();
	updateFromXMLNode();
}

//_____________________________________________________________________________
/**
 * Destructor.
 */
SdfastBody::~SdfastBody()
{
}

//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aBody SdfastBody to be copied.
 */
SdfastBody::SdfastBody(const SdfastBody &aBody) :
   AbstractBody(aBody),
   _massCenter(_massCenterProp.getValueDblArray()),
	_displayerProp(PropertyObj("", VisibleObject())),
   _displayer((VisibleObject&)_displayerProp.getValueObj()),
	_index(_indexProp.getValueInt()),
	_SdfastEngine(NULL)
{
	setNull();
	setupProperties();
	copyData(aBody);
}

//_____________________________________________________________________________
/**
 * Copy constructor from an AbstractBody.
 *
 * @param aBody SdfastBody to be copied.
 */
SdfastBody::SdfastBody(const AbstractBody &aBody) :
   AbstractBody(aBody),
   _massCenter(_massCenterProp.getValueDblArray()),
	_displayerProp(PropertyObj("", VisibleObject())),
   _displayer((VisibleObject&)_displayerProp.getValueObj()),
	_index(_indexProp.getValueInt()),
	_SdfastEngine(NULL)
{
	setNull();
	setupProperties();
	copyData(aBody);
}

//_____________________________________________________________________________
/**
 * Copy this body and return a pointer to the copy.
 * The copy constructor for this class is used.
 *
 * @return Pointer to a copy of this SdfastBody.
 */
Object* SdfastBody::copy() const
{
	SdfastBody *body = new SdfastBody(*this);
	return(body);
}

//_____________________________________________________________________________
/**
 * Copy this SdfastBody and modify the copy so that it is consistent
 * with a specified XML element node.
 *
 * The copy is constructed by first using
 * SdfastBody::SdfastBody(DOMElement*) in order to establish the
 * relationship of the SdfastBody object with the XML node. Then, the
 * assignment operator is used to set all data members of the copy to the
 * values of this SdfastBody object. Finally, the data members of the copy are
 * updated using SdfastBody::updateFromXMLNode().
 *
 * @param aElement XML element. 
 * @return Pointer to a copy of this SdfastBody.
 */
Object* SdfastBody::copy(DOMElement *aElement) const
{
	SdfastBody *body = new SdfastBody(aElement);
	*body = *this;
	body->updateFromXMLNode();
	return(body);
}

//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Copy data members from one SdfastBody to another.
 *
 * @param aBody SdfastBody to be copied.
 */
void SdfastBody::copyData(const SdfastBody &aBody)
{
	_massCenter = aBody._massCenter;
	_displayer = aBody._displayer;
	_index = aBody._index;
	_SdfastEngine = aBody._SdfastEngine;
}

//_____________________________________________________________________________
/**
 * Copy data members from an AbstractBody to an SdfastBody.
 *
 * @param aBody AbstractBody to be copied.
 */
void SdfastBody::copyData(const AbstractBody &aBody)
{
	aBody.getMassCenter(&_massCenter[0]);
	_displayer = *aBody.getDisplayer();
}

//_____________________________________________________________________________
/**
 * Set the data members of this SdfastBody to their null values.
 */
void SdfastBody::setNull()
{
	setType("SdfastBody");
}

//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void SdfastBody::setupProperties()
{
	const double defaultMC[] = {0.0, 0.0, 0.0};
	_massCenterProp.setName("mass_center");
	_massCenterProp.setValue(3, defaultMC);
	_propertySet.append(&_massCenterProp);

	_displayerProp.setName("Displayer");
	_propertySet.append(&_displayerProp);

	_indexProp.setName("index");
	_propertySet.append(&_indexProp);
}

//_____________________________________________________________________________
/**
 * Perform some set up functions that happen after the
 * object has been deserialized or copied.
 *
 * @param aEngine dynamics engine containing this SdfastBody.
 */
void SdfastBody::setup(AbstractDynamicsEngine* aEngine)
{
	// Base class
	AbstractBody::setup(aEngine);

	_displayer.setOwner(this);

	_SdfastEngine = dynamic_cast<SdfastEngine*>(aEngine);
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
SdfastBody& SdfastBody::operator=(const SdfastBody &aBody)
{
	// BASE CLASS
	AbstractBody::operator=(aBody);

	copyData(aBody);

	return(*this);
}

//=============================================================================
// GET AND SET
//=============================================================================
//_____________________________________________________________________________
/**
 * Get the mass of the body.
 *
 * @return Mass of body from SD/FAST code.
 */
double SdfastBody::getMass() const
{
	if (_index < 0)
		return 0.0;

	double mass = 0.0;

	sdgetmass(_index, &mass);

	return mass;
}

//_____________________________________________________________________________
/**
 * Set the mass of the body.
 *
 * @param aMass mass of body.
 * @return Whether mass was successfully changed.
 */
bool SdfastBody::setMass(double aMass)
{
	if (aMass >= 0.0)
	{
		sdmass(_index, aMass);
		sdinit();
		return true;
	}

	return false;
}

//_____________________________________________________________________________
/**
 * Get the mass center of the body.
 *
 * @param rVec XYZ coordinates of mass center are returned here.
 */
void SdfastBody::getMassCenter(double rVec[3]) const
{
	rVec[0] = _massCenter[0];
	rVec[1] = _massCenter[1];
	rVec[2] = _massCenter[2];
}
 
//_____________________________________________________________________________
/**
 * Set the mass center of the body.
 *
 * @param aVec XYZ coordinates of mass center.
 * @return Whether mass center was successfully changed.
 */
bool SdfastBody::setMassCenter(double aVec[3])
{
	_massCenter[0] = aVec[0];
	_massCenter[1] = aVec[1];
	_massCenter[2] = aVec[2];

	SdfastEngine* engine = dynamic_cast<SdfastEngine*>(_dynamicsEngine);
	if (engine) return engine->adjustJointVectorsForNewMassCenter(this, aVec);
	else return false;
}

//_____________________________________________________________________________
/**
 * Get the inertia matrix of the body.
 *
 * @param 3x3 inertia matrix.
 */
void SdfastBody::getInertia(double rInertia[3][3]) const
{
	sdiner(_index, rInertia);
}

//_____________________________________________________________________________
/**
 * Set the inertia matrix of the body.
 *
 * @param aInertia 9-element inertia matrix.
 * @return Whether inertia matrix was successfully changed.
 */
bool SdfastBody::setInertia(const Array<double>& aInertia)
{
	if (aInertia.getSize() >= 9)
	{
		double inertia[3][3];
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				inertia[i][j] = aInertia[i*3+j];

		sdiner(_index, inertia);
		sdinit();
		return true;
	}

	return false;
}

//=============================================================================
// BONES
//=============================================================================
//_____________________________________________________________________________
/**
 * Add a bone to the body.
 *
 * @param aBone bone to be added.
void SdfastBody::addBone(VisibleObject* aBone)
{
	VisibleObject* newBone = new VisibleObject(*aBone);

	// note: _boneSet takes over ownership of newMarker
	_boneSet.append(newBone);
}
 */

//=============================================================================
// SCALING
//=============================================================================
//_____________________________________________________________________________
/**
 * Scale the body.
 *
 * @param aScaleFactors XYZ scale factors.
 * @param aScaleMass whether or not to scale mass properties
 */
void SdfastBody::scale(Array<double>& aScaleFactors, bool aScaleMass)
{
	int i;

	double oldScaleFactors[3];
	getDisplayer()->getScaleFactors(oldScaleFactors);

	for (i = 0; i < 3; i++)
	{
		_massCenter[i] *= aScaleFactors[i];
		oldScaleFactors[i] *= aScaleFactors[i];
	}
	// Update scale factors for displayer
	getDisplayer()->setScaleFactors(aScaleFactors.get());

	if (aScaleMass)
		scaleInertialProperties(aScaleFactors);
}

//_____________________________________________________________________________
/**
 * Scale the body's mass and inertia.
 *
 * @param aScaleFactors XYZ scale factors.
 */
void SdfastBody::scaleInertialProperties(Array<double>& aScaleFactors)
{
	int i, j;
	double mass, inertia[3][3];

	sdgetmass(_index, &mass);
	sdgetiner(_index, inertia);

	/* If the mass is zero, then make the inertia tensor zero as well.
	 * If the X, Y, Z scale factors are equal, then you can scale the
	 * inertia tensor exactly by the square of the scale factor, since
	 * each element in the tensor is proportional to the square of one
	 * or more dimensional measurements. For determining if the scale
	 * factors are equal, ignore reflections-- look only at the
	 * absolute value of the factors.
	 */
	if (mass <= ROUNDOFF_ERROR)
	{
		for (i = 0; i < 3; i++)
			for (j = 0; j < 3; j++)
				inertia[i][j] = 0.0;
	}
	else if (EQUAL_WITHIN_ERROR(DABS(aScaleFactors[0]), DABS(aScaleFactors[1])) &&
		      EQUAL_WITHIN_ERROR(DABS(aScaleFactors[1]), DABS(aScaleFactors[2])))
	{
		mass *= DABS((aScaleFactors[0] * aScaleFactors[1] * aScaleFactors[2]));

		for (i = 0; i < 3; i++)
			for (j = 0; j < 3; j++)
				inertia[i][j] *= (aScaleFactors[0] * aScaleFactors[0]);
	}
	else
	{
		/* If the scale factors are not equal, then assume that the segment
		 * is a cylinder and the inertia is calculated about one end of it.
		 */
		int axis;

		/* 1. Find the smallest diagonal component. This dimension is the axis
		 *    of the cylinder.
		 */
		if (inertia[0][0] <= inertia[1][1])
		{
			if (inertia[0][0] <= inertia[2][2])
				axis = 0;
			else
				axis = 2;
		}
		else if (inertia[1][1] <= inertia[2][2])
		{
			axis = 1;
		}
		else
		{
			axis = 2;
		}

		/* 2. The smallest inertial component is equal to 0.5 * mass * radius * radius,
		 *    so you can rearrange and solve for the radius.
		 */
		int oa;
		double radius, rad_sqr, length;
		double term = 2.0 * inertia[axis][axis] / mass;
		if (term < 0.0)
			radius = 0.0;
		else
			radius = sqrt(term);

		/* 3. Choose either of the other diagonal components and use it to solve for the
		*    length of the cylinder. This component is equal to:
		*    0.333 * mass * length * length  +  0.25 * mass * radius * radius
		*/
		if (axis == 0)
			oa = 1;
		else
			oa = 0;
		term = 3.0 * (inertia[oa][oa] - 0.25 * mass * radius * radius) / mass;
		if (term < 0.0)
			length = 0.0;
		else
			length = sqrt(term);

		/* 4. Scale the mass, radius, and length, and recalculate the diagonal inertial terms. */
		mass *= DABS((aScaleFactors[0] * aScaleFactors[1] * aScaleFactors[2]));
		length *= DABS(aScaleFactors[axis]);

		if (axis == 0)
		{
			rad_sqr = radius * DABS(aScaleFactors[1]) * radius * DABS(aScaleFactors[2]);
			inertia[0][0] = 0.5 * mass * rad_sqr;
			inertia[1][1] = mass * ((length * length / 3.0) + 0.25 * rad_sqr);
			inertia[2][2] = mass * ((length * length / 3.0) + 0.25 * rad_sqr);
		}
		else if (axis == 1)
		{
			rad_sqr = radius * DABS(aScaleFactors[0]) * radius * DABS(aScaleFactors[2]);
			inertia[0][0] = mass * ((length * length / 3.0) + 0.25 * rad_sqr);
			inertia[1][1] = 0.5 * mass * rad_sqr;
			inertia[2][2] = mass * ((length * length / 3.0) + 0.25 * rad_sqr);
		}
		else
		{
			rad_sqr = radius * DABS(aScaleFactors[0]) * radius * DABS(aScaleFactors[1]);
			inertia[0][0] = mass * ((length * length / 3.0) + 0.25 * rad_sqr);
			inertia[1][1] = mass * ((length * length / 3.0) + 0.25 * rad_sqr);
			inertia[2][2] = 0.5 * mass * rad_sqr;
		}

		/* 5. Scale the cross terms, in case some are non-zero. */
		inertia[0][1] *= DABS((aScaleFactors[0] * aScaleFactors[1]));
		inertia[0][2] *= DABS((aScaleFactors[0] * aScaleFactors[2]));
		inertia[1][0] *= DABS((aScaleFactors[1] * aScaleFactors[0]));
		inertia[1][2] *= DABS((aScaleFactors[1] * aScaleFactors[2]));
		inertia[2][0] *= DABS((aScaleFactors[2] * aScaleFactors[0]));
		inertia[2][1] *= DABS((aScaleFactors[2] * aScaleFactors[1]));
	}

	sdmass(_index, mass);
	sdiner(_index, inertia);
	// TODO: check for SD/FAST errors
}

//=============================================================================
// ITERATORS FOR COMPONENTS
//=============================================================================
//_____________________________________________________________________________
/**
 * Make an iterator for the body's bone set.
 *
 * @return Pointer to the bone iterator.
BoneIterator* SdfastBody::newBoneIterator() const
{
	return new BoneSetIterator(_boneSet);
}
 */

//=============================================================================
// I/O
//=============================================================================
//=============================================================================
// UTILITY
//=============================================================================
//_____________________________________________________________________________
/**
 * Transform a point from the body's frame to the body's SD/FAST frame.
 * This entails subtracting the mass center coordinates from the point
 * because the SD/FAST frame is lined up with the body frame, but has
 * its origin at the center of mass.
 *
 * @param aPos The point in the body frame to transform
 * @param rPos The point transformed into the SD/FAST frame
 */
void SdfastBody::transformToSdfastFrame(const double aPos[3], double rPos[3]) const
{
	for (int i = 0; i < 3; i++)
		rPos[i] = aPos[i] - _massCenter[i];
}

//_____________________________________________________________________________
/**
 * Transform a point from the body's frame to the body's SD/FAST frame.
 * This entails subtracting the mass center coordinates from the point
 * because the SD/FAST frame is lined up with the body frame, but has
 * its origin at the center of mass.
 *
 * @param aPos The point in the body frame to transform
 * @param rPos The point transformed into the SD/FAST frame
 */
void SdfastBody::transformToSdfastFrame(const Array<double>& aPos, double rPos[3]) const
{
	for (int i = 0; i < 3; i++)
		rPos[i] = aPos[i] - _massCenter[i];
}

//_____________________________________________________________________________
/**
 * Transform a point from the body's SD/FAST frame to the body's frame.
 * This entails adding the mass center coordinates to the point
 * because the SD/FAST frame is lined up with the body frame, but has
 * its origin at the center of mass.
 *
 * @param aPos The point in the body's SD/FAST frame to transform
 * @param rPos The point transformed into the body's frame
 */
void SdfastBody::transformFromSdfastFrame(const double aPos[3], double rPos[3]) const
{
	for (int i = 0; i < 3; i++)
		rPos[i] = aPos[i] + _massCenter[i];
}

//_____________________________________________________________________________
/**
 * Transform a point from the body's SD/FAST frame to the body's frame.
 * This entails adding the mass center coordinates to the point
 * because the SD/FAST frame is lined up with the body frame, but has
 * its origin at the center of mass.
 *
 * @param aPos The point in the body's SD/FAST frame to transform
 * @param rPos The point transformed into the body's frame
 */
void SdfastBody::transformFromSdfastFrame(const Array<double>& aPos, double rPos[3]) const
{
	for (int i = 0; i < 3; i++)
		rPos[i] = aPos[i] + _massCenter[i];
}

void SdfastBody::peteTest() const
{
	cout << "Body: " << getName() << endl;
	cout << "   massCenter: " << _massCenter << endl;
}
