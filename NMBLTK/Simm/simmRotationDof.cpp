// simmRotationDof.cpp
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
#include "simmRotationDof.h"

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
simmRotationDof::simmRotationDof() :
   _axis(_axisProp.getValueDblArray())
{
	setNull();

}
//_____________________________________________________________________________
/**
 * Constructor from an XML node
 */
simmRotationDof::simmRotationDof(DOMElement *aElement) :
   simmDof(aElement),
   _axis(_axisProp.getValueDblArray())
{
	setNull();

	updateFromXMLNode();
}

//_____________________________________________________________________________
/**
 * Destructor.
 */
simmRotationDof::~simmRotationDof()
{
}

//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aDof simmRotationDof to be copied.
 */
simmRotationDof::simmRotationDof(const simmRotationDof &aDof) :
   simmDof(aDof),
   _axis(_axisProp.getValueDblArray())
{
	setupProperties();
	copyData(aDof);
}
//_____________________________________________________________________________
/**
 * Copy this dof and return a pointer to the copy.
 * The copy constructor for this class is used.
 *
 * @return Pointer to a copy of this simmRotationDof.
 */
rdObject* simmRotationDof::copy() const
{
	simmRotationDof *dof = new simmRotationDof(*this);
	return(dof);
}
//_____________________________________________________________________________
/**
 * Copy this simmRotationDof and modify the copy so that it is consistent
 * with a specified XML element node.
 *
 * The copy is constructed by first using
 * simmRotationDof::simmRotationDof(DOMElement*) in order to establish the
 * relationship of the simmRotationDof object with the XML node. Then, the
 * assignment operator is used to set all data members of the copy to the
 * values of this simmRotationDof object. Finally, the data members of the copy are
 * updated using simmRotationDof::updateFromXMLNode().
 *
 * @param aElement XML element. 
 * @return Pointer to a copy of this simmRotationDof.
 */
rdObject* simmRotationDof::copy(DOMElement *aElement) const
{
	simmRotationDof *dof = new simmRotationDof(aElement);
	*dof = *this;
	dof->updateFromXMLNode();
	return(dof);
}

void simmRotationDof::copyData(const simmRotationDof &aDof)
{
	_axis = aDof._axis;
}

void simmRotationDof::getAxis(double axis[3]) const
{
	axis[0] = _axis[0];
	axis[1] = _axis[1];
	axis[2] = _axis[2];
}

double simmRotationDof::getValue()
{
	if (_coordinate)
		return _functions[0]->evaluate(0, _coordinate->getValue(), 0.0, 0.0);
	else
		return _functions[0]->evaluate(0, 0.0, 0.0, 0.0);
}

//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set the data members of this simmRotationDof to their null values.
 */
void simmRotationDof::setNull()
{
	setupProperties();
	setType("rotationDof");
}
//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void simmRotationDof::setupProperties()
{
	const double defaultAxis[] = {1.0, 0.0, 0.0};
	_axisProp.setName("axis");
	_axisProp.setValue(3, defaultAxis);
	_propertySet.append(&_axisProp);
}

simmRotationDof& simmRotationDof::operator=(const simmRotationDof &aDof)
{
	// BASE CLASS
	simmDof::operator=(aDof);

	copyData(aDof);

	return(*this);
}

void simmRotationDof::peteTest()
{
	cout << "RotationDof: " << getName() << endl;
	cout << "   value: " << getValue() << endl;
	cout << "   coordinate: " << _coordinateName << endl;
	if (_functions.getSize() > 0)
		cout << "   function: " << *(_functions[0]) << endl;
}
