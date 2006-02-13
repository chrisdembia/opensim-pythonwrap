// simmMeasurement.cpp
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
#include "simmMeasurement.h"

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
simmMeasurement::simmMeasurement() :
	_markerPairSet((rdArrayPtrs<simmMarkerPair>&)_markerPairSetProp.getValueObjArray()),
	_bodyScaleSet((rdArrayPtrs<simmBodyScale>&)_bodyScaleSetProp.getValueObjArray()),
	_apply(_applyProp.getValueBool())
{
	setNull();
}
//_____________________________________________________________________________
/**
 * Constructor from an XML node
 */
simmMeasurement::simmMeasurement(DOMElement *aElement) :
   rdObject(aElement),
	_markerPairSet((rdArrayPtrs<simmMarkerPair>&)_markerPairSetProp.getValueObjArray()),
	_bodyScaleSet((rdArrayPtrs<simmBodyScale>&)_bodyScaleSetProp.getValueObjArray()),
	_apply(_applyProp.getValueBool())
{
	setNull();
	updateFromXMLNode();
}

//_____________________________________________________________________________
/**
 * Destructor.
 */
simmMeasurement::~simmMeasurement()
{
}

//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aMeasurement simmMeasurement to be copied.
 */
simmMeasurement::simmMeasurement(const simmMeasurement &aMeasurement) :
   rdObject(aMeasurement),
	_markerPairSet((rdArrayPtrs<simmMarkerPair>&)_markerPairSetProp.getValueObjArray()),
	_bodyScaleSet((rdArrayPtrs<simmBodyScale>&)_bodyScaleSetProp.getValueObjArray()),
	_apply(_applyProp.getValueBool())
{
	setupProperties();
	copyData(aMeasurement);
}
//_____________________________________________________________________________
/**
 * Copy this measurement and return a pointer to the copy.
 * The copy constructor for this class is used.
 *
 * @return Pointer to a copy of this simmMeasurement.
 */
rdObject* simmMeasurement::copy() const
{
	simmMeasurement *measurement = new simmMeasurement(*this);
	return(measurement);
}
//_____________________________________________________________________________
/**
 * Copy this simmMeasurement and modify the copy so that it is consistent
 * with a specified XML element node.
 *
 * The copy is constructed by first using
 * simmMeasurement::simmMeasurement(DOMElement*) in order to establish the
 * relationship of the simmMeasurement object with the XML node. Then, the
 * assignment operator is used to set all data members of the copy to the
 * values of this simmMeasurement object. Finally, the data members of the
 * copy are updated using simmMeasurement::updateFromXMLNode().
 *
 * @param aElement XML element. 
 * @return Pointer to a copy of this simmMeasurement.
 */
rdObject* simmMeasurement::copy(DOMElement *aElement) const
{
	simmMeasurement *measurement = new simmMeasurement(aElement);
	*measurement = *this;
	measurement->updateFromXMLNode();
	return(measurement);
}

void simmMeasurement::copyData(const simmMeasurement &aMeasurement)
{
	_markerPairSet = aMeasurement._markerPairSet;
	_bodyScaleSet = aMeasurement._bodyScaleSet;
	_apply = aMeasurement._apply;
}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set the data members of this simmMeasurement to their null values.
 */
void simmMeasurement::setNull()
{
	setupProperties();
	setType("measurement");
	setName("");
}
//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void simmMeasurement::setupProperties()
{
	_markerPairSetProp.setName("MarkerPairSet");
	rdArrayPtrs<rdObject> mps;
	_markerPairSetProp.setValue(mps);
	_propertySet.append(&_markerPairSetProp);

	_bodyScaleSetProp.setName("BodyScaleSet");
	rdArrayPtrs<rdObject> bss;
	_bodyScaleSetProp.setValue(bss);
	_propertySet.append(&_bodyScaleSetProp);

	_applyProp.setName("apply");
	_applyProp.setValue(true);
	_propertySet.append(&_applyProp);
}

void simmMeasurement::registerTypes()
{
	rdObject::RegisterType(simmMarkerPair());
	rdObject::RegisterType(simmBodyScale());
}

simmMeasurement& simmMeasurement::operator=(const simmMeasurement &aMeasurement)
{
	// BASE CLASS
	rdObject::operator=(aMeasurement);

	copyData(aMeasurement);

	return(*this);
}

/* Apply a scale factor to a scale set, according to the elements of
 * the simmMeasurement's BodyScaleSet.
 */
void simmMeasurement::applyScaleFactor(double aFactor, suScaleSet& aScaleSet)
{
	for (int i = 0; i < _bodyScaleSet.getSize(); i++)
	{
		const string& bodyName = _bodyScaleSet[i]->getName();
		for (int j = 0; j < aScaleSet.getSize(); j++)
		{
			if (aScaleSet[j]->getSegmentName() == bodyName)
			{
				const rdArray<std::string>& axisNames = _bodyScaleSet[i]->getAxisNames();
				rdArray<double> factors(1.0, 3);
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

void simmMeasurement::peteTest() const
{
	int i;

	cout << "      Measurement: " << getName() << endl;
	cout << "         apply: " << _apply << endl;
	for (i = 0; i < _markerPairSet.getSize(); i++)
		_markerPairSet[i]->peteTest();
	for (i = 0; i < _bodyScaleSet.getSize(); i++)
		_bodyScaleSet[i]->peteTest();
}
