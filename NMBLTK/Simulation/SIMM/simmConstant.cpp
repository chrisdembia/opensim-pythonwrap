// simmConstant.cpp
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


// C++ INCLUDES
#include "simmConstant.h"


using namespace std;


//=============================================================================
// STATICS
//=============================================================================


//=============================================================================
// DESTRUCTOR AND CONSTRUCTORS
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
simmConstant::~simmConstant()
{
}
//_____________________________________________________________________________
/**
 * Default constructor.
 */
simmConstant::simmConstant() :
	_value(_valueProp.getValueDbl())
{
	setNull();
}
//_____________________________________________________________________________
/**
 */
simmConstant::simmConstant(int aN,const double *aX,const double *aY,	const string &aName) :
	_value(_valueProp.getValueDbl())
{
	setNull();

	// OBJECT TYPE AND NAME
	setName(aName);
}
//_____________________________________________________________________________
/**
 * Construct a function from an XML Element.
 *
 * @param aElement XML element.
 */
simmConstant::simmConstant(DOMElement *aElement) :
	rdFunction(aElement),
	_value(_valueProp.getValueDbl())
{
	setNull();
	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Copy constructor.
 * All data members of the specified simmConstant are copied.
 *
 * @param aConstant simmConstant object to be copied.
 */
simmConstant::simmConstant(const simmConstant &aConstant) :
	rdFunction(aConstant),
	_value(_valueProp.getValueDbl())
{
	setupProperties();
	copyData(aConstant);
}
//_____________________________________________________________________________
/**
 * Copy this object.
 *
 * @return Pointer to a copy of this object.
 */
rdObject* simmConstant::copy() const
{
	simmConstant *aConstant = new simmConstant(*this);
	return(aConstant);
}
//_____________________________________________________________________________
/**
 * Copy this object and modify the copy so that it is consistent
 * with a specified XML element node.
 *
 * The copy is constructed by first using
 * simmConstant::simmConstant(DOMElement*) in order to establish the
 * XML node. Then, the assignment operator is used to set all
 * data members of the copy to the values of this object. Finally, the
 * data members of the copy are updated using simmConstant::updateFromXMLNode().
 *
 * @param aElement XML element. 
 * @return Pointer to a copy of this object modified by the specified
 * XML element.
 */
rdObject* simmConstant::
copy(DOMElement *aElement) const
{
	// CONSTRUCT FUNCTION BASED ON XML ELEMENT
	simmConstant *func = new simmConstant(aElement);

	// ASSIGN DATA ACCORDING TO THIS simmConstant
	*func = *this;

	// UPDATE DATA CCORDING TO THE XML ELEMENT
	func->updateFromXMLNode();

	return(func);
}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set all member variables to their NULL or default values.
 */
void simmConstant::setNull()
{
	setupProperties();
	setType("constant");
	setName("");
}
//_____________________________________________________________________________
/**
 * Set up the serialized member variables.  This involves both generating
 * the properties and connecting them to the local pointers used to access
 * the serialized member variables.
 */
void simmConstant::setupProperties()
{
	_valueProp.setName("value");
	_valueProp.setValue(0);
	_propertySet.append(&_valueProp);
}
//_____________________________________________________________________________
/**
 * Set all member variables equal to the members of another object.
 * Note that this method is private.  It is only meant for copying the data
 * members defined in this class.  It does not, for example, make any changes
 * to data members of base classes.
 */
void simmConstant::copyData(const simmConstant &aConstant)
{
	_value = aConstant._value;
}


//=============================================================================
// OPERATORS
//=============================================================================
//_____________________________________________________________________________
/**
 * Assignment operator.
 * Note that data members of the base class are also assigned.
 *
 * @return Reference to this object.
 */
simmConstant& simmConstant::operator=(const simmConstant &aConstant)
{
	// BASE CLASS
	rdFunction::operator=(aConstant);

	// DATA
	copyData(aConstant);

	return(*this);
}


//=============================================================================
// SET AND GET
//=============================================================================

//-----------------------------------------------------------------------------
// UPDATE FROM XML NODE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Update this object based on its XML node.
 */
void simmConstant::updateFromXMLNode()
{
	rdFunction::updateFromXMLNode();
}	

//=============================================================================
// EVALUATION
//=============================================================================
//_____________________________________________________________________________
/**
 * Update the bounding box for this function.
 *
 * @see rdFunction
 */
void simmConstant::updateBoundingBox()
{
	setMinX(0.0);
	setMinY(0.0);
	setMinZ(0.0);
	setMaxX(0.0);
	setMaxY(0.0);
	setMaxZ(0.0);
}


void simmConstant::peteTest() const
{
	cout << "simmConstant" << endl;
	cout << "   value: " << _value << endl;
}

