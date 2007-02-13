// SimmMeasurement.cpp
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
#include "SimmMeasurement.h"

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
SimmMeasurement::SimmMeasurement() :
	_markerPairSetProp(PropertyObj("", SimmMarkerPairSet())),
	_markerPairSet((SimmMarkerPairSet&)_markerPairSetProp.getValueObj()),
	_bodyScaleSetProp(PropertyObj("", BodyScaleSet())),
	_bodyScaleSet((BodyScaleSet&)_bodyScaleSetProp.getValueObj()),
	_apply(_applyProp.getValueBool())
{
	setNull();
	setupProperties();
}

//_____________________________________________________________________________
/**
 * Destructor.
 */
SimmMeasurement::~SimmMeasurement()
{
}

//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aMeasurement SimmMeasurement to be copied.
 */
SimmMeasurement::SimmMeasurement(const SimmMeasurement &aMeasurement) :
   Object(aMeasurement),
	_markerPairSetProp(PropertyObj("", SimmMarkerPairSet())),
	_markerPairSet((SimmMarkerPairSet&)_markerPairSetProp.getValueObj()),
	_bodyScaleSetProp(PropertyObj("", BodyScaleSet())),
	_bodyScaleSet((BodyScaleSet&)_bodyScaleSetProp.getValueObj()),
	_apply(_applyProp.getValueBool())
{
	setNull();
	setupProperties();
	copyData(aMeasurement);
}
//_____________________________________________________________________________
/**
 * Copy this measurement and return a pointer to the copy.
 * The copy constructor for this class is used.
 *
 * @return Pointer to a copy of this SimmMeasurement.
 */
Object* SimmMeasurement::copy() const
{
	SimmMeasurement *measurement = new SimmMeasurement(*this);
	return(measurement);
}

//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Copy data members from one SimmMeasurement to another.
 *
 * @param aMeasurement SimmMeasurement to be copied.
 */
void SimmMeasurement::copyData(const SimmMeasurement &aMeasurement)
{
	_markerPairSet = aMeasurement._markerPairSet;
	_bodyScaleSet = aMeasurement._bodyScaleSet;
	_apply = aMeasurement._apply;
}

//_____________________________________________________________________________
/**
 * Set the data members of this SimmMeasurement to their null values.
 */
void SimmMeasurement::setNull()
{
	setType("SimmMeasurement");
}

//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void SimmMeasurement::setupProperties()
{
	_markerPairSetProp.setComment("Set of marker pairs used to determine the scale factors.");
	_markerPairSetProp.setName("SimmMarkerPairSet");
	_propertySet.append(&_markerPairSetProp);

	_bodyScaleSetProp.setComment("Set of bodies to be scaled by this measurement.");
	_bodyScaleSetProp.setName("BodyScaleSet");
	_propertySet.append(&_bodyScaleSetProp);

	_applyProp.setComment("Flag to turn on and off scaling for this measurement.");
	_applyProp.setName("apply");
	_applyProp.setValue(true);
	_propertySet.append(&_applyProp);
}

//_____________________________________________________________________________
/**
 * Register the types used by SimmMeasurement.
 */
void SimmMeasurement::registerTypes()
{
	Object::RegisterType(SimmMarkerPair());
	Object::RegisterType(BodyScale());
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
SimmMeasurement& SimmMeasurement::operator=(const SimmMeasurement &aMeasurement)
{
	// BASE CLASS
	Object::operator=(aMeasurement);

	copyData(aMeasurement);

	return(*this);
}

/* Apply a scale factor to a scale set, according to the elements of
 * the SimmMeasurement's BodyScaleSet.
 */
//_____________________________________________________________________________
/**
 * Apply a scale factor to a scale set, according to the elements of
 * the SimmMeasurement's _bodyScaleSet.
 *
 * @param aFactor the scale factor to apply
 * @param aScaleSet the set of scale factors to modify
 */
void SimmMeasurement::applyScaleFactor(double aFactor, ScaleSet& aScaleSet)
{
	for (int i = 0; i < _bodyScaleSet.getSize(); i++)
	{
		const string& bodyName = _bodyScaleSet[i]->getName();
		for (int j = 0; j < aScaleSet.getSize(); j++)
		{
			if (aScaleSet[j]->getSegmentName() == bodyName)
			{
				const Array<std::string>& axisNames = _bodyScaleSet[i]->getAxisNames();
				Array<double> factors(1.0, 3);
				aScaleSet[j]->getScaleFactors(factors);

				for (int k = 0; k < axisNames.getSize(); k++)
				{
					if (axisNames[k] == "x" || axisNames[k] == "X")
						factors[0] = aFactor;
					else if (axisNames[k] == "y" || axisNames[k] == "Y")
						factors[1] = aFactor;
					else if (axisNames[k] == "z" || axisNames[k] == "Z")
						factors[2] = aFactor;
				}
				aScaleSet[j]->setScaleFactors(factors);
			}
		}
	}
}

void SimmMeasurement::peteTest() const
{
	int i;

	cout << "      Measurement: " << getName() << endl;
	cout << "         apply: " << _apply << endl;
	for (i = 0; i < _markerPairSet.getSize(); i++)
		_markerPairSet[i]->peteTest();
	for (i = 0; i < _bodyScaleSet.getSize(); i++)
		_bodyScaleSet[i]->peteTest();
}
