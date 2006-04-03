// simmSubject.cpp
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
#include "simmSubject.h"

const double simmSubject::DefaultMass=-1.0;
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
simmSubject::simmSubject() :
	_mass(_massProp.getValueDbl()),
	_height(_heightProp.getValueDbl()),
	_age(_ageProp.getValueDbl()),
	_notes(_notesProp.getValueStr()),
   _genericModelParamsProp(rdPropertyObj("", simmGenericModelParams())),
	_genericModelParams((simmGenericModelParams&)_genericModelParamsProp.getValueObj()),
   _scalingParamsProp(rdPropertyObj("", simmScalingParams())),
	_scalingParams((simmScalingParams&)_scalingParamsProp.getValueObj()),
   _markerPlacementParamsProp(rdPropertyObj("", simmMarkerPlacementParams())),
	_markerPlacementParams((simmMarkerPlacementParams&)_markerPlacementParamsProp.getValueObj()),
   _IKParamsProp(rdPropertyObj("", simmIKParams())),
	_IKParams((simmIKParams&)_IKParamsProp.getValueObj())
{
	setNull();
}

//_____________________________________________________________________________
/**
 * Constructor from an XML file
 */
simmSubject::simmSubject(const string &aFileName) :
   rdObject(aFileName),
	_mass(_massProp.getValueDbl()),
	_height(_heightProp.getValueDbl()),
	_age(_ageProp.getValueDbl()),
	_notes(_notesProp.getValueStr()),
   _genericModelParamsProp(rdPropertyObj("", simmGenericModelParams())),
	_genericModelParams((simmGenericModelParams&)_genericModelParamsProp.getValueObj()),
   _scalingParamsProp(rdPropertyObj("", simmScalingParams())),
	_scalingParams((simmScalingParams&)_scalingParamsProp.getValueObj()),
   _markerPlacementParamsProp(rdPropertyObj("", simmMarkerPlacementParams())),
	_markerPlacementParams((simmMarkerPlacementParams&)_markerPlacementParamsProp.getValueObj()),
   _IKParamsProp(rdPropertyObj("", simmIKParams())),
	_IKParams((simmIKParams&)_IKParamsProp.getValueObj())
{
	setNull();

	updateFromXMLNode();
}

//_____________________________________________________________________________
/**
 * Constructor from an XML node
 */
simmSubject::simmSubject(DOMElement *aElement) :
   rdObject(aElement),
	_mass(_massProp.getValueDbl()),
	_height(_heightProp.getValueDbl()),
	_age(_ageProp.getValueDbl()),
	_notes(_notesProp.getValueStr()),
   _genericModelParamsProp(rdPropertyObj("", simmGenericModelParams())),
	_genericModelParams((simmGenericModelParams&)_genericModelParamsProp.getValueObj()),
   _scalingParamsProp(rdPropertyObj("", simmScalingParams())),
	_scalingParams((simmScalingParams&)_scalingParamsProp.getValueObj()),
   _markerPlacementParamsProp(rdPropertyObj("", simmMarkerPlacementParams())),
	_markerPlacementParams((simmMarkerPlacementParams&)_markerPlacementParamsProp.getValueObj()),
   _IKParamsProp(rdPropertyObj("", simmIKParams())),
	_IKParams((simmIKParams&)_IKParamsProp.getValueObj())
{
	setNull();

	updateFromXMLNode();
}

//_____________________________________________________________________________
/**
 * Destructor.
 */
simmSubject::~simmSubject()
{
}

//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aSubject simmSubject to be copied.
 */
simmSubject::simmSubject(const simmSubject &aSubject) :
   rdObject(aSubject),
	_mass(_massProp.getValueDbl()),
	_height(_heightProp.getValueDbl()),
	_age(_ageProp.getValueDbl()),
	_notes(_notesProp.getValueStr()),
   _genericModelParamsProp(rdPropertyObj("", simmGenericModelParams())),
	_genericModelParams((simmGenericModelParams&)_genericModelParamsProp.getValueObj()),
   _scalingParamsProp(rdPropertyObj("", simmScalingParams())),
	_scalingParams((simmScalingParams&)_scalingParamsProp.getValueObj()),
   _markerPlacementParamsProp(rdPropertyObj("", simmMarkerPlacementParams())),
	_markerPlacementParams((simmMarkerPlacementParams&)_markerPlacementParamsProp.getValueObj()),
   _IKParamsProp(rdPropertyObj("", simmIKParams())),
	_IKParams((simmIKParams&)_IKParamsProp.getValueObj())
{
	setupProperties();
	copyData(aSubject);
}
//_____________________________________________________________________________
/**
 * Copy this subject and return a pointer to the copy.
 * The copy constructor for this class is used.
 *
 * @return Pointer to a copy of this simmSubject.
 */
rdObject* simmSubject::copy() const
{
	simmSubject *subject = new simmSubject(*this);
	return(subject);
}
//_____________________________________________________________________________
/**
 * Copy this simmSubject and modify the copy so that it is consistent
 * with a specified XML element node.
 *
 * The copy is constructed by first using
 * simmSubject::simmSubject(DOMElement*) in order to establish the
 * relationship of the simmSubject object with the XML node. Then, the
 * assignment operator is used to set all data members of the copy to the
 * values of this simmSubject object. Finally, the data members of the
 * copy are updated using simmSubject::updateFromXMLNode().
 *
 * @param aElement XML element. 
 * @return Pointer to a copy of this simmSubject.
 */
rdObject* simmSubject::copy(DOMElement *aElement) const
{
	simmSubject *subject = new simmSubject(aElement);
	*subject = *this;
	subject->updateFromXMLNode();
	return(subject);
}

void simmSubject::copyData(const simmSubject &aSubject)
{
	_mass = aSubject._mass;
	_height = aSubject._height;
	_age = aSubject._age;
	_notes = aSubject._notes;
	_genericModelParams = aSubject._genericModelParams;
	_scalingParams = aSubject._scalingParams;
	_markerPlacementParams = aSubject._markerPlacementParams;
	_IKParams = aSubject._IKParams;
}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set the data members of this simmSubject to their null values.
 */
void simmSubject::setNull()
{
	setupProperties();
	setType("Subject");
	setName("");
}
//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void simmSubject::setupProperties()
{
	_massProp.setName("mass");
	_massProp.setValue(simmSubject::DefaultMass);
	_massProp.setComment("Mass of the subject in kgs.");
	_propertySet.append(&_massProp);

	_heightProp.setName("height");
	_heightProp.setValue(-1.0);
	_heightProp.setComment("Height of the subject in cms.");
	_propertySet.append(&_heightProp);

	_ageProp.setName("age");
	_ageProp.setValue(-1.0);
	_propertySet.append(&_ageProp);

	_notesProp.setName("notes");
	_notesProp.setComment("Save record-keeping info. here.");
	_propertySet.append(&_notesProp);

	_genericModelParamsProp.setName("");
	_genericModelParamsProp.setComment("File name for the (nominal model).sim to use is specified here.");
	_propertySet.append(&_genericModelParamsProp);

	_scalingParamsProp.setName("");
	_scalingParamsProp.setComment("Parameters to control nominal model scaling go here.");
	_propertySet.append(&_scalingParamsProp);

	_markerPlacementParamsProp.setName("");
	_markerPlacementParamsProp.setComment("Parameters needed to move model's marker locations to match recorded ones from a static trial.");
	_propertySet.append(&_markerPlacementParamsProp);

	_IKParamsProp.setName("");
	_IKParamsProp.setComment("Parameters pertinent to solving IK are specified here.");
	_propertySet.append(&_IKParamsProp);
}

void simmSubject::registerTypes()
{
	rdObject::RegisterType(simmGenericModelParams());
	rdObject::RegisterType(simmScalingParams());
	rdObject::RegisterType(simmMarkerPlacementParams());
	rdObject::RegisterType(simmIKParams());
	simmGenericModelParams::registerTypes();
	simmScalingParams::registerTypes();
	simmIKParams::registerTypes();
}

simmSubject& simmSubject::operator=(const simmSubject &aSubject)
{
	// BASE CLASS
	rdObject::operator=(aSubject);

	copyData(aSubject);

	return(*this);
}
#if 0

bool simmSubject::processModel()
{
	cout << "Processing subject " << getName() << endl;

	/* Make the generic model. */
	if (!_genericModelParamsProp.getUseDefault())
	{
		_model = _genericModelParams.processModel();
		if (!_model)
		{
			cout << "===ERROR===: Unable to load generic model." << endl;
			return false;
		}
	}

	/* Scale the generic model. */
	if (!_scalingParamsProp.getUseDefault())
	{
		if (_genericModelParamsProp.getUseDefault())
		{
			cout << "===ERROR===: To use ScalingParameters, you must specify GenericModelParameters." << endl;
			return false;
		}
		else
		{
			/* If a generic model was specified, but the model
			 * was not created successfully, you won't make it
			 * to this point. So here you know that _model is
			 * a proper model.
			 */
			if (!_scalingParams.processModel(_model))
			{
				cout << "===ERROR===: Unable to scale generic model." << endl;
				return false;
			}
		}
	}

	/* Place the markers on the scaled model. */
	if (!_markerPlacementParamsProp.getUseDefault())
	{
		if (_genericModelParamsProp.getUseDefault())
		{
			cout << "===ERROR===: To use MarkerPlacementParameters, you must specify GenericModelParameters." << endl;
			return false;
		}
		else
		{
			/* If a generic model was specified, but the model
			 * was not created successfully, you won't make it
			 * to this point. So here you know that _model is
			 * a proper model.
			 */
			if (!_markerPlacementParams.processModel(_model))
			{
				cout << "===ERROR===: Unable to place markers on model." << endl;
				return false;
			}
		}
	}

	/* Process the IK trials. The generic model is not
	 * needed for this because a model file can be specified
	 * as an IK parameter.
	 */
	if (!_IKParamsProp.getUseDefault())
		_IKParams.processModel(_model);

	/* Clean up. */
	delete _model;

	return true;
}
#endif

simmModel* simmSubject::createModel()
{
	cout << "Processing subject " << getName() << endl;

	/* Make the generic model. */
	if (!_genericModelParamsProp.getUseDefault())
	{
		simmModel *model = _genericModelParams.processModel();
		if (model==0)
		{
			cout << "===ERROR===: Unable to load generic model." << endl;
			return 0;
		}
		else
			return model;
	}
	return 0;
}

void simmSubject::peteTest() const
{
	cout << "   Subject: " << getName() << endl;
	_genericModelParams.peteTest();
	_scalingParams.peteTest();
	_markerPlacementParams.peteTest();
	_IKParams.peteTest();
}

/**
 * Check if MarkerPlacementParams settings in file are different from defaults
 */
bool simmSubject::isDefaultMarkerPlacementParams() const
{ 
	
	return (_markerPlacementParamsProp.getUseDefault()==true || _markerPlacementParams.isDefault()); 
}
