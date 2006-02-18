// simmMuscleViaPoint.cpp
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
#include "simmMuscleViaPoint.h"
#include "simmModel.h"
#include "simmKinematicsEngine.h"

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
simmMuscleViaPoint::simmMuscleViaPoint() :
   _range(_rangeProp.getValueDblArray()),
	_coordinateName(_coordinateNameProp.getValueStr()),
	_coordinate(NULL)
{
	setNull();

}
//_____________________________________________________________________________
/**
 * Constructor from an XML node
 */
simmMuscleViaPoint::simmMuscleViaPoint(DOMElement *aElement) :
   simmMusclePoint(aElement),
   _range(_rangeProp.getValueDblArray()),
	_coordinateName(_coordinateNameProp.getValueStr()),
	_coordinate(NULL)
{
	setNull();

	updateFromXMLNode();
}

//_____________________________________________________________________________
/**
 * Destructor.
 */
simmMuscleViaPoint::~simmMuscleViaPoint()
{
}

//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aPoint simmMuscleViaPoint to be copied.
 */
simmMuscleViaPoint::simmMuscleViaPoint(const simmMuscleViaPoint &aPoint) :
   simmMusclePoint(aPoint),
   _range(_rangeProp.getValueDblArray()),
	_coordinateName(_coordinateNameProp.getValueStr()),
	_coordinate(NULL)
{
	setupProperties();
	copyData(aPoint);
}
//_____________________________________________________________________________
/**
 * Copy this muscle via point and return a pointer to the copy.
 * The copy constructor for this class is used.
 *
 * @return Pointer to a copy of this simmMuscleViaPoint.
 */
rdObject* simmMuscleViaPoint::copy() const
{
	simmMuscleViaPoint *pt = new simmMuscleViaPoint(*this);
	return(pt);
}
//_____________________________________________________________________________
/**
 * Copy this simmMuscleViaPoint and modify the copy so that it is consistent
 * with a specified XML element node.
 *
 * The copy is constructed by first using
 * simmMuscleViaPoint::simmMuscleViaPoint(DOMElement*) in order to establish the
 * relationship of the simmMuscleViaPoint object with the XML node. Then, the
 * assignment operator is used to set all data members of the copy to the
 * values of this simmMuscleViaPoint object. Finally, the data members of the copy are
 * updated using simmMuscleViaPoint::updateFromXMLNode().
 *
 * @param aElement XML element. 
 * @return Pointer to a copy of this simmMuscleViaPoint.
 */
rdObject* simmMuscleViaPoint::copy(DOMElement *aElement) const
{
	simmMuscleViaPoint *pt = new simmMuscleViaPoint(aElement);
	*pt = *this;
	pt->updateFromXMLNode();
	return(pt);
}

void simmMuscleViaPoint::copyData(const simmMuscleViaPoint &aPoint)
{
	_range = aPoint._range;
	_coordinateName = aPoint._coordinateName;
	_coordinate = aPoint._coordinate;
}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set the data members of this simmMuscleViaPoint to their null values.
 */
void simmMuscleViaPoint::setNull()
{
	setupProperties();
	setType("muscleViaPoint");
	setName("");
}
//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void simmMuscleViaPoint::setupProperties()
{
	const double defaultRange[] = {0.0, 0.0};
	_rangeProp.setName("range");
	_rangeProp.setValue(2, defaultRange);
	_propertySet.append(&_rangeProp);

	_coordinateNameProp.setName("coordinate");
	_propertySet.append(&_coordinateNameProp);
}

simmMuscleViaPoint& simmMuscleViaPoint::operator=(const simmMuscleViaPoint &aPoint)
{
	// BASE CLASS
	simmMusclePoint::operator=(aPoint);

	copyData(aPoint);

	return(*this);
}

void simmMuscleViaPoint::writeSIMM(ofstream& out) const
{
	out << _attachment[0] << " " << _attachment[1] << " " << _attachment[2] << " segment " << _bodyName;
	out << " ranges 1 " << _coordinateName << " (" << _range[0] << ", " << _range[1] << ")" << endl;
}

/* Perform some set up functions that happen after the
 * object has been deserialized or copied.
 */
void simmMuscleViaPoint::setup(simmModel* model, simmKinematicsEngine* ke)
{
	// base class
	simmMusclePoint::setup(model, ke);

	/* Look up the coordinate by name in the kinematics engine and
	 * store a pointer to it.
	 */
	_coordinate = dynamic_cast<simmCoordinate *> (ke->getCoordinate(_coordinateName));
}

void simmMuscleViaPoint::peteTest() const
{
	cout << "   MuscleViaPoint: " << getName() << endl;
	cout << "      point: " << getAttachment() << endl;
	cout << "      body: " << _body->getName() << endl;
	cout << "      range: " << getRange() << endl;
	cout << "      coordinate: " << _coordinate->getName() << endl;
}
