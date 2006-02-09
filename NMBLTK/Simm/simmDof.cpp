// simmDof.cpp
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
#include "simmDof.h"
#include "simmKinematicsEngine.h"
#include "simmJoint.h"

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
simmDof::simmDof(void) :
	_functions((rdArrayPtrs<rdFunction>&)_functionsProp.getValueObjArray()),
	_coordinateName((std::string&)_coordinateNameProp.getValueStr()),
	_coordinate(NULL)
{
	setNull();
}

//_____________________________________________________________________________
/**
 * Construct a simmDof from an XML Element.
 */
simmDof::simmDof(DOMElement *aElement) :
	rdObject(aElement),
	_functions((rdArrayPtrs<rdFunction>&)_functionsProp.getValueObjArray()),
	_coordinateName((std::string&)_coordinateNameProp.getValueStr()),
	_coordinate(NULL)
{
	setNull();
	updateFromXMLNode();
}

//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aDof simmDof to be copied.
 */
simmDof::simmDof(const simmDof &aDof) :
   rdObject(aDof),
	_functions((rdArrayPtrs<rdFunction>&)_functionsProp.getValueObjArray()),
	_coordinateName((std::string&)_coordinateNameProp.getValueStr()),
	_coordinate(NULL)
{
	setupProperties();
	copyData(aDof);
}

//_____________________________________________________________________________
/**
 * Destructor.
 */
simmDof::~simmDof(void)
{
}

void simmDof::copyData(const simmDof &aDof)
{
	_functions = aDof._functions;
	_coordinateName = aDof._coordinateName;
	_coordinate = aDof._coordinate;
}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set the data members of this simmDof to their null values.
 */
void simmDof::setNull(void)
{
	setupProperties();
	setType("dof");
	setName("");
}
//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void simmDof::setupProperties(void)
{
	_functionsProp.setName("Values");
	rdArrayPtrs<rdObject> func;
	_functionsProp.setValue(func);
	_propertySet.append(&_functionsProp);

	_coordinateNameProp.setName("DOFcoordinate");
	_propertySet.append(&_coordinateNameProp);
}

/* Perform some set up functions that happen after the
 * object has been deserialized or copied.
 */
void simmDof::setup(simmKinematicsEngine* aEngine, simmJoint* aJoint)
{
	string errorMessage;

	/* Look up the coordinate by name in the kinematics
	 * engine and store a pointer to it.
	 */
	_coordinate = aEngine->getCoordinate(_coordinateName);

	/* _coordinate will be NULL if _coordinateName is not the
	 * name of a valid model coordinate. This is OK, unless
	 * the user specified the coordinate name in the model file.
	 */
	if (!_coordinateNameProp.getUseDefault() && !_coordinate)
	{
		errorMessage += "Invalid coordinate (" + _coordinateName + ") specified in dof " + getName() + " in joint " + aJoint->getName();
		throw (rdException(errorMessage.c_str()));
	}
}

simmDof& simmDof::operator=(const simmDof &aDof)
{
	// BASE CLASS
	rdObject::operator=(aDof);

	copyData(aDof);

	return(*this);
}

rdFunction* simmDof::getFunction() const
{
	if (_functions.getSize() < 0)
		return NULL;

	return _functions[0];
}

void simmDof::peteTest(void)
{
	cout << "DOF base class" << endl;
}
