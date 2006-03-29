// simmGenericModelParams.cpp
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
#include "simmGenericModelParams.h"

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
simmGenericModelParams::simmGenericModelParams() :
   _fileName(_fileNameProp.getValueStr()),
   _markerSet((rdArrayPtrs<simmMarker>&)_markerSetProp.getValueObjArray())
{
	setNull();
}
//_____________________________________________________________________________
/**
 * Constructor from an XML node
 */
simmGenericModelParams::simmGenericModelParams(DOMElement *aElement) :
   rdObject(aElement),
   _fileName(_fileNameProp.getValueStr()),
   _markerSet((rdArrayPtrs<simmMarker>&)_markerSetProp.getValueObjArray())
{
	setNull();

	updateFromXMLNode();
}

//_____________________________________________________________________________
/**
 * Destructor.
 */
simmGenericModelParams::~simmGenericModelParams()
{
}

//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aGenericModelParams simmGenericModelParams to be copied.
 */
simmGenericModelParams::simmGenericModelParams(const simmGenericModelParams &aGenericModelParams) :
   rdObject(aGenericModelParams),
   _fileName(_fileNameProp.getValueStr()),
   _markerSet((rdArrayPtrs<simmMarker>&)_markerSetProp.getValueObjArray())
{
	setupProperties();
	copyData(aGenericModelParams);
}
//_____________________________________________________________________________
/**
 * Copy this simmGenericModelParams and return a pointer to the copy.
 * The copy constructor for this class is used.
 *
 * @return Pointer to a copy of this simmGenericModelParams.
 */
rdObject* simmGenericModelParams::copy() const
{
	simmGenericModelParams *genericModelParams = new simmGenericModelParams(*this);
	return(genericModelParams);
}
//_____________________________________________________________________________
/**
 * Copy this simmGenericModelParams and modify the copy so that it is consistent
 * with a specified XML element node.
 *
 * The copy is constructed by first using
 * simmGenericModelParams::simmGenericModelParams(DOMElement*) in order to establish the
 * relationship of the simmGenericModelParams object with the XML node. Then, the
 * assignment operator is used to set all data members of the copy to the
 * values of this simmGenericModelParams object. Finally, the data members of the copy are
 * updated using simmGenericModelParams::updateFromXMLNode().
 *
 * @param aElement XML element. 
 * @return Pointer to a copy of this simmGenericModelParams.
 */
rdObject* simmGenericModelParams::copy(DOMElement *aElement) const
{
	simmGenericModelParams *genericModelParams = new simmGenericModelParams(aElement);
	*genericModelParams = *this;
	genericModelParams->updateFromXMLNode();
	return(genericModelParams);
}

void simmGenericModelParams::copyData(const simmGenericModelParams &aGenericModelParams)
{
	_fileName = aGenericModelParams._fileName;
	_markerSet = aGenericModelParams._markerSet;
}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set the data members of this simmGenericModelParams to their null values.
 */
void simmGenericModelParams::setNull()
{
	setupProperties();
	setType("GenericModelParameters");
	setName("");
}
//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void simmGenericModelParams::setupProperties()
{
	_fileNameProp.setName("filename");
	_fileNameProp.setComment("name of xml file for nominal model"); 
	_propertySet.append(&_fileNameProp);

	_markerSetProp.setName("MarkerSet");
	rdArrayPtrs<rdObject> markers;
	_markerSetProp.setValue(markers);
	_propertySet.append(&_markerSetProp);
}

void simmGenericModelParams::registerTypes()
{
	rdObject::RegisterType(simmMarker());
}

simmGenericModelParams& simmGenericModelParams::operator=(const simmGenericModelParams &aGenericModelParams)
{
	// BASE CLASS
	rdObject::operator=(aGenericModelParams);

	copyData(aGenericModelParams);

	return(*this);
}

simmModel* simmGenericModelParams::processModel()
{
	simmModel* model = NULL;

	cout << endl << "Step 1: Loading generic model" << endl;

	try
	{
		model = new simmModel(_fileName);
		model->setup();

		if (model->builtOK())
			model->updateMarkers(_markerSet);
	}
	catch (rdException &x)
	{
		x.print(cout);
		cout << "Press any key to continue.. " << endl;
		cout.flush();
		int c = getc( stdin );
		return NULL;
	}

	return model;
}

void simmGenericModelParams::peteTest() const
{
	cout << "   GenericModel: " << getName() << endl;
	cout << "      fileName: " << _fileName << endl;
	cout << "      markers:" << endl;

	for (int i = 0; i < _markerSet.getSize(); i++)
		_markerSet[i]->peteTest();
}

