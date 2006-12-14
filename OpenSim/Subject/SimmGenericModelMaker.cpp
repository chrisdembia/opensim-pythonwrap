// SimmGenericModelMaker.cpp
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
#include "SimmGenericModelMaker.h"
#include <OpenSim/Simulation/SIMM/AbstractModel.h>
#include <OpenSim/Simulation/SIMM/SimmMarker.h>

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
SimmGenericModelMaker::SimmGenericModelMaker() :
   _fileName(_fileNameProp.getValueStr()),
	_markerSetProp(PropertyObj("", MarkerSet())),
	_markerSet((MarkerSet&)_markerSetProp.getValueObj())
{
	setNull();
	setupProperties();
}

//_____________________________________________________________________________
/**
 * Constructor from an XML node
 */
SimmGenericModelMaker::SimmGenericModelMaker(DOMElement *aElement) :
   Object(aElement),
   _fileName(_fileNameProp.getValueStr()),
	_markerSetProp(PropertyObj("", MarkerSet())),
	_markerSet((MarkerSet&)_markerSetProp.getValueObj())
{
	setNull();
	setupProperties();
	updateFromXMLNode();
}

//_____________________________________________________________________________
/**
 * Destructor.
 */
SimmGenericModelMaker::~SimmGenericModelMaker()
{
}

//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aGenericModelMaker SimmGenericModelMaker to be copied.
 */
SimmGenericModelMaker::SimmGenericModelMaker(const SimmGenericModelMaker &aGenericModelMaker) :
   Object(aGenericModelMaker),
   _fileName(_fileNameProp.getValueStr()),
	_markerSetProp(PropertyObj("", MarkerSet())),
	_markerSet((MarkerSet&)_markerSetProp.getValueObj())
{
	setNull();
	setupProperties();
	copyData(aGenericModelMaker);
}

//_____________________________________________________________________________
/**
 * Copy this SimmGenericModelMaker and return a pointer to the copy.
 * The copy constructor for this class is used.
 *
 * @return Pointer to a copy of this SimmGenericModelMaker.
 */
Object* SimmGenericModelMaker::copy() const
{
	SimmGenericModelMaker *genericModelMaker = new SimmGenericModelMaker(*this);
	return(genericModelMaker);
}

//_____________________________________________________________________________
/**
 * Copy this SimmGenericModelMaker and modify the copy so that it is consistent
 * with a specified XML element node.
 *
 * The copy is constructed by first using
 * SimmGenericModelMaker::SimmGenericModelMaker(DOMElement*) in order to establish the
 * relationship of the SimmGenericModelMaker object with the XML node. Then, the
 * assignment operator is used to set all data members of the copy to the
 * values of this SimmGenericModelMaker object. Finally, the data members of the copy are
 * updated using SimmGenericModelMaker::updateFromXMLNode().
 *
 * @param aElement XML element. 
 * @return Pointer to a copy of this SimmGenericModelMaker.
 */
Object* SimmGenericModelMaker::copy(DOMElement *aElement) const
{
	SimmGenericModelMaker *genericModelMaker = new SimmGenericModelMaker(aElement);
	*genericModelMaker = *this;
	genericModelMaker->updateFromXMLNode();
	return(genericModelMaker);
}

//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Copy data members from one SimmGenericModelMaker to another.
 *
 * @param aGenericModelMaker SimmGenericModelMaker to be copied.
 */
void SimmGenericModelMaker::copyData(const SimmGenericModelMaker &aGenericModelMaker)
{
	_fileName = aGenericModelMaker._fileName;
	_markerSet = aGenericModelMaker._markerSet;
}

//_____________________________________________________________________________
/**
 * Set the data members of this SimmGenericModelMaker to their null values.
 */
void SimmGenericModelMaker::setNull()
{
	setType("SimmGenericModelMaker");
}

//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void SimmGenericModelMaker::setupProperties()
{
	_fileNameProp.setName("file_name");
	_fileNameProp.setComment("name of xml file for nominal model"); 
	_propertySet.append(&_fileNameProp);

	_markerSetProp.setName("MarkerSet");
	_propertySet.append(&_markerSetProp);
}

//_____________________________________________________________________________
/**
 * Register the types used by this class.
 */
void SimmGenericModelMaker::registerTypes()
{
	//Object::RegisterType(SimmMarker());
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
SimmGenericModelMaker& SimmGenericModelMaker::operator=(const SimmGenericModelMaker &aGenericModelMaker)
{
	// BASE CLASS
	Object::operator=(aGenericModelMaker);

	copyData(aGenericModelMaker);

	return(*this);
}

//=============================================================================
// UTILITY
//=============================================================================
//_____________________________________________________________________________
/**
 * Execute the model making process, which involves reading
 * an XML model file and possible updating its marker set.
 *
 * @return Pointer to the AbstractModel that is constructed.
 */
AbstractModel* SimmGenericModelMaker::processModel(const string& aPathToSubject)
{
	AbstractModel* model = NULL;

	cout << endl << "Step 1: Loading generic model" << endl;

	try
	{
		_fileName = aPathToSubject + _fileName;

		model = new AbstractModel(_fileName);
		model->setup();

		if (model->builtOK())
			model->getDynamicsEngine().updateMarkerSet(_markerSet);
	}
	catch (Exception &x)
	{
		x.print(cout);
		return NULL;
	}

	return model;
}

void SimmGenericModelMaker::peteTest() const
{
	cout << "   GenericModel: " << getName() << endl;
	cout << "      fileName: " << _fileName << endl;
	cout << "      markers:" << endl;

	for (int i = 0; i < _markerSet.getSize(); i++)
		_markerSet.get(i)->peteTest();
}

