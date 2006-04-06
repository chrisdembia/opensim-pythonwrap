// simmIKParams.cpp
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
#include "simmIKParams.h"

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
simmIKParams::simmIKParams() :
   _modelFileName(_modelFileNameProp.getValueStr()),
	_markerSet((rdArrayPtrs<simmMarker>&)_markerSetProp.getValueObjArray()),
	_coordinateSet((rdArrayPtrs<simmCoordinate>&)_coordinateSetProp.getValueObjArray()),
	_IKTrialParamsSet((rdArrayPtrs<simmIKTrialParams>&)_IKTrialParamsSetProp.getValueObjArray())
{
	setNull();
}
//_____________________________________________________________________________
/**
 * Constructor from an XML node
 */
simmIKParams::simmIKParams(DOMElement *aElement) :
   rdObject(aElement),
   _modelFileName(_modelFileNameProp.getValueStr()),
	_markerSet((rdArrayPtrs<simmMarker>&)_markerSetProp.getValueObjArray()),
	_coordinateSet((rdArrayPtrs<simmCoordinate>&)_coordinateSetProp.getValueObjArray()),
	_IKTrialParamsSet((rdArrayPtrs<simmIKTrialParams>&)_IKTrialParamsSetProp.getValueObjArray())
{
	setNull();
	updateFromXMLNode();
}

//_____________________________________________________________________________
/**
 * Destructor.
 */
simmIKParams::~simmIKParams()
{
}

//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aMarkerPlacementParams simmIKParams to be copied.
 */
simmIKParams::simmIKParams(const simmIKParams &aIKParams) :
   rdObject(aIKParams),
   _modelFileName(_modelFileNameProp.getValueStr()),
	_markerSet((rdArrayPtrs<simmMarker>&)_markerSetProp.getValueObjArray()),
	_coordinateSet((rdArrayPtrs<simmCoordinate>&)_coordinateSetProp.getValueObjArray()),
	_IKTrialParamsSet((rdArrayPtrs<simmIKTrialParams>&)_IKTrialParamsSetProp.getValueObjArray())
{
	setupProperties();
	copyData(aIKParams);
}
//_____________________________________________________________________________
/**
 * Copy this IK params and return a pointer to the copy.
 * The copy constructor for this class is used.
 *
 * @return Pointer to a copy of this simmIKParams.
 */
rdObject* simmIKParams::copy() const
{
	simmIKParams *IKParams = new simmIKParams(*this);
	return(IKParams);
}
//_____________________________________________________________________________
/**
 * Copy this simmIKParams and modify the copy so that it is consistent
 * with a specified XML element node.
 *
 * The copy is constructed by first using
 * simmIKParams::simmIKParams(DOMElement*) in order to establish the
 * relationship of the simmIKParams object with the XML node. Then, the
 * assignment operator is used to set all data members of the copy to the
 * values of this simmIKParams object. Finally, the data members of the
 * copy are updated using simmIKParams::updateFromXMLNode().
 *
 * @param aElement XML element. 
 * @return Pointer to a copy of this simmIKParams.
 */
rdObject* simmIKParams::copy(DOMElement *aElement) const
{
	simmIKParams *IKParams = new simmIKParams(aElement);
	*IKParams = *this;
	IKParams->updateFromXMLNode();
	return(IKParams);
}

void simmIKParams::copyData(const simmIKParams &aIKParams)
{
	_modelFileName = aIKParams._modelFileName;
	_markerSet = aIKParams._markerSet;
	_coordinateSet = aIKParams._coordinateSet;
	_IKTrialParamsSet = aIKParams._IKTrialParamsSet;
}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set the data members of this simmIKParams to their null values.
 */
void simmIKParams::setNull()
{
	setupProperties();
	setType("IKParameters");
	setName("");
}
//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void simmIKParams::setupProperties()
{
	_modelFileNameProp.setName("modelFile");
	_propertySet.append(&_modelFileNameProp);

	_markerSetProp.setName("MarkerSet");
	rdArrayPtrs<rdObject> ms;
	_markerSetProp.setValue(ms);
	_propertySet.append(&_markerSetProp);

	_coordinateSetProp.setName("CoordinateSet");
	rdArrayPtrs<rdObject> cs;
	_coordinateSetProp.setValue(cs);
	_propertySet.append(&_coordinateSetProp);

	_IKTrialParamsSetProp.setName("IKTrialSet");
	_IKTrialParamsSetProp.setComment("Trial paramaters, one block per trial");
	rdArrayPtrs<rdObject> iktps;
	_IKTrialParamsSetProp.setValue(iktps);
	_propertySet.append(&_IKTrialParamsSetProp);
}

void simmIKParams::registerTypes()
{
	rdObject::RegisterType(simmIKTrialParams());
}

simmIKParams& simmIKParams::operator=(const simmIKParams &aIKParams)
{
	// BASE CLASS
	rdObject::operator=(aIKParams);

	copyData(aIKParams);

	return(*this);
}

bool simmIKParams::solveIK(IKSolverInterface *aSolver,simmModel* aModel)
{
	cout << endl << "Step 4: Solving IK trials" << endl;

	if (!aModel && _modelFileNameProp.getUseDefault())
	{
		cout << "===ERROR===: To process an IK trial, you must specify GenericModelParameters or a file name in IKParameters." << endl;
		return false;
	}

	try
	{
		/* If the user specified a model file name,
		 * delete the passed-in model and create a new
		 * one from the file.
		 */
		if (!_modelFileNameProp.getUseDefault())
		{
			simmModel* newModel = new simmModel(_modelFileName);
			if (newModel)
			{
				newModel->setup();
				if (aModel)
					delete aModel;
				aModel = newModel;
			}
		}
	}
	catch (rdException &x)
	{
		x.print(cout);
		cout << "Press Return to continue." << endl;
		cout.flush();
		int c = getc( stdin );
		return false;
	}

	// SET IK SOLVER
	aModel->getKinematicsEngine().setIKSolver(aSolver);

	/* Update the markers. */
	aModel->updateMarkers(_markerSet);

	/* Now perform the IK trials on the updated model. */
	for (int i = 0; i < _IKTrialParamsSet.getSize(); i++)
	{
		if (_IKTrialParamsSet[i]->processTrial(*aModel, _coordinateSet))
			cout << "Trial " << _IKTrialParamsSet[i]->getName() << " processed successfully." << endl;
		else
			cout << "Trial " << _IKTrialParamsSet[i]->getName() << " processing failed." << endl;
	}

	return true;
}

void simmIKParams::peteTest() const
{
	int i;

	cout << "   IKParameters: " << getName() << endl;
	cout << "      modelFileName: " << _modelFileName << endl;
	for (i = 0; i < _markerSet.getSize(); i++)
		_markerSet[i]->peteTest();
	for (i = 0; i < _coordinateSet.getSize(); i++)
		_coordinateSet[i]->peteTest();
	for (i = 0; i < _IKTrialParamsSet.getSize(); i++)
		_IKTrialParamsSet[i]->peteTest();
}
