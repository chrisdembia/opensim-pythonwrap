// rdProperty.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//============================================================================
// INCLUDES
//============================================================================
#include "rdProperty.h"


using namespace std;


//=============================================================================
// CONSTRUCTOR(S)
//=============================================================================
//_____________________________________________________________________________
/**
 * Default constructor.
 */
rdProperty::
rdProperty()
{
	setNull();
}
//_____________________________________________________________________________
/**
 * Constructor.
 */
rdProperty::
rdProperty(rdPropertyType aType,const string &aName)
{
	setNull();
	_type = aType;
	_name = aName;
}
//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aProperty Property to be copied.
 */
rdProperty::rdProperty(const rdProperty &aProperty)
{
	setNull();
	*this = aProperty;
	_comment = aProperty.getComment();
}
//_____________________________________________________________________________
/**
 * Construct and return a copy of this property.
 *
 * The property is allocated using the new operator, so the caller is
 * responsible for deleting the returned object.
 *
 * @return Copy of this property.
 *
rdProperty* rdProperty::copy() const
{
	rdProperty *property = new rdProperty(*this);
	return(property);
}
*/

//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set member variables to their null values.
 */
void rdProperty::
setNull()
{
	_type = rdProperty::None;
	_name = "unknown";
	_useDefault = false;
}



//=============================================================================
// OPERATORS
//=============================================================================
//-----------------------------------------------------------------------------
// ASSIGNMENT
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Assign this property to another.
 *
 * @param aProperty Property to which to assign this property.
 * @return Reference to this property.
 */
rdProperty& rdProperty::
operator=(const rdProperty &aProperty)
{
	setType(aProperty.getType());
	setName(aProperty.getName());
	setUseDefault(aProperty.getUseDefault());
	_comment = aProperty.getComment();
	return(*this);
}

//-----------------------------------------------------------------------------
// EQUALITY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Determine if two properties are equal.
 *
 * Two properties are equal if their names are the same; the types do not
 * need to be the same.
 *
 * @param aProperty Property for which to make the equality test.
 * @return True if the specified property and this property are equal, false
 * otherwise.
 */
bool rdProperty::
operator==(const rdProperty &aProperty) const
{
	if(_name != aProperty.getName()) return(false);
	return(true);
}

//-----------------------------------------------------------------------------
// LESS THAN
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Determine if this property is less than another.
 *
 * This property is less than another if the name of this string is less
 * than the name of the other property.
 *
 * @param aProperty Property for which to make the less than test.
 * @return True if this property is less than the other, false otherwise.
 */
bool rdProperty::
operator<(const rdProperty &aProperty) const
{
	return(_name < aProperty.getName());
}

//-----------------------------------------------------------------------------
// OUTPUT (<<)
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Implementation of the output operator.
 * The output consists of the type and name:\n\n
 *
 * @param aOut Output stream.
 * @param aProperty Property to be output.
 * @return Reference to the output stream.
ostream& operator<<(ostream &aOut,const rdProperty &aProperty)
{
	aOut << aProperty.getTypeAsString() << " " << aProperty.getName();
	return(aOut);
}
 */


//=============================================================================
// GET AND SET
//=============================================================================
//-----------------------------------------------------------------------------
// TYPE AS STRING
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the type of this property as a string.
 *
 * @return Type of the property.
 */
const char* rdProperty::
getTypeAsString() const
{
	return("None");
}

//-----------------------------------------------------------------------------
// TYPE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the type of this property.
 *
 * @param aType Type of this object represented as a string.  In most all
 * cases, the type should be the name of the class.
 */
void rdProperty::
setType(rdPropertyType aType)
{
	_type = aType;
}
//_____________________________________________________________________________
/**
 * Get the type of this property.
 *
 * @return Type of the property.
 */
rdProperty::rdPropertyType rdProperty::
getType() const
{
	return(_type);
}

//-----------------------------------------------------------------------------
// NAME
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the name of this property.
 *
 * @param aName Name to which to set this property.
 */
void rdProperty::
setName(const string &aName)
{
	_name = aName;
}
//_____________________________________________________________________________
/**
 * Get the name of this property.
 *
 * @retrun Name of this property
 */
const string& rdProperty::
getName() const
{
	return(_name);
}

//-----------------------------------------------------------------------------
// VALUE BOOL
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the value of this property.
 *
 * This method does nothing; it is just a place holder for
 * rdPropertyInt::setValue(), which is the only intended meaningful
 * implementation of this method.
 *
 * This method has been implemented in rdProperty, rather than made pure
 * virtual, so that all classes derived from rdProperty will not have to
 * implement this method.
 *
 * @param aValue Value to which this property is to be assigned.
 * @see rdPropertyInt
 */
void rdProperty::
setValue(bool aValue)
{
	string msg;
	msg = "rdProperty.SetValue(bool): Property type mismatch. ";
	msg += "This property is of type ";
	msg += getTypeAsString();
	msg += ".";

	throw rdException(msg,__FILE__,__LINE__);
}
//_____________________________________________________________________________
/**
 * Get a reference to the value of this property.  Note that the returned
 * reference can be used to change the value of this property.
 *
 * @return Reference to the value of this property.
 * @throws rdException When the property is not an rdPropertyInt.
 * @see rdPropertyInt
 */
bool& rdProperty::
getValueBool()
{
	string msg;
	msg = "rdProperty.getValueBool(): Property type mismatch. ";
	msg += "This property is of type ";
	msg += getTypeAsString();
	msg += ".";

	throw rdException(msg,__FILE__,__LINE__);
}
//_____________________________________________________________________________
/**
 * Get a constant reference to the value of this property.
 *
 * @return Constant reference to the value of this property.
 * @throws rdException When the property is not an rdPropertyInt.
 * @see rdPropertyInt
 */
const bool& rdProperty::
getValueBool() const
{
	string msg;
	msg = "rdProperty.getValueBool(): Property type mismatch. ";
	msg += "This property is of type ";
	msg += getTypeAsString();
	msg += ".";

	throw rdException(msg,__FILE__,__LINE__);
}

//-----------------------------------------------------------------------------
// VALUE INT
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the value of this property.
 *
 * This method does nothing; it is just a place holder for
 * rdPropertyInt::setValue(), which is the only intended meaningful
 * implementation of this method.
 *
 * This method has been implemented in rdProperty, rather than made pure
 * virtual, so that all classes derived from rdProperty will not have to
 * implement this method.
 *
 * @param aValue Value to which this property is to be assigned.
 * @see rdPropertyInt
 */
void rdProperty::
setValue(int aValue)
{
	string msg;
	msg = "rdProperty.SetValue(int): Property type mismatch. ";
	msg += "This property is of type ";
	msg += getTypeAsString();
	msg += ".";

	throw rdException(msg,__FILE__,__LINE__);
}
//_____________________________________________________________________________
/**
 * Get a reference to the value of this property.  Note that the returned
 * reference can be used to change the value of this property.
 *
 * @return Reference to the value of this property.
 * @throws rdException When the property is not an rdPropertyInt.
 * @see rdPropertyInt
 */
int& rdProperty::
getValueInt()
{
	string msg;
	msg = "rdProperty.getValueInt(): Property type mismatch. ";
	msg += "This property is of type ";
	msg += getTypeAsString();
	msg += ".";

	throw rdException(msg,__FILE__,__LINE__);
}
//_____________________________________________________________________________
/**
 * Get a constant reference to the value of this property.
 *
 * @return Constant reference to the value of this property.
 * @throws rdException When the property is not an rdPropertyInt.
 * @see rdPropertyInt
 */
const int& rdProperty::
getValueInt() const
{
	string msg;
	msg = "rdProperty.getValueInt(): Property type mismatch. ";
	msg += "This property is of type ";
	msg += getTypeAsString();
	msg += ".";

	throw rdException(msg,__FILE__,__LINE__);
}

//-----------------------------------------------------------------------------
// VALUE DOUBLE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the value of this property.
 *
 * This method does nothing; it is just a place holder for
 * rdPropertyDbl::setValue(), which is the only intended meaningful
 * implementation of this method.
 *
 * This method has been implemented in rdProperty, rather than made pure
 * virtual, so that all classes derived from rdProperty will not have to
 * implement this method.
 *
 * @param aValue Value to which this property is to be assigned.
 * @see rdPropertyDbl
 */
void rdProperty::
setValue(double aValue)
{
	string msg;
	msg = "rdProperty.setValue(double): Property type mismatch. ";
	msg += "This property is of type ";
	msg += getTypeAsString();
	msg += ".";

	throw rdException(msg,__FILE__,__LINE__);
}
//_____________________________________________________________________________
/**
 * Get a reference to the value of this property.  Note that the returned
 * reference can be used to change the value of this property.
 *
 * @return Reference to the value of this property.
 * @throws rdException When the property is not an rdPropertyDbl.
 * @see rdPropertyDbl
 */
double& rdProperty::
getValueDbl()
{
	string msg;
	msg = "rdProperty.getValueDbl(): Property type mismatch. ";
	msg += "This property is of type ";
	msg += getTypeAsString();
	msg += ".";

	throw rdException(msg,__FILE__,__LINE__);
}
//_____________________________________________________________________________
/**
 * Get a constant reference to the value of this property.
 *
 * @return Const reference to the value of this property.
 * @throws rdException When the property is not an rdPropertyDbl.
 * @see rdPropertyDbl
 */
const double& rdProperty::
getValueDbl() const
{
	string msg;
	msg = "rdProperty.getValueDbl(): Property type mismatch. ";
	msg += "This property is of type ";
	msg += getTypeAsString();
	msg += ".";

	throw rdException(msg,__FILE__,__LINE__);
}

//-----------------------------------------------------------------------------
// VALUE STRING
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the value of this property.
 *
 * This method does nothing; it is just a place holder for
 * rdPropertyStr::setValue(), which is the only intended meaningful
 * implementation of this method.
 *
 * This method has been implemented in rdProperty, rather than made pure
 * virtual, so that all classes derived from rdProperty will not have to
 * implement this method.
 *
 * @param aValue Value to which this property is to be assigned.
 * @see rdPropertyStr
 */
void rdProperty::
setValue(const string &aValue)
{
	string msg;
	msg = "rdProperty.setValue(string): Property type mismatch. ";
	msg += "This property is of type ";
	msg += getTypeAsString();
	msg += ".";

	throw rdException(msg,__FILE__,__LINE__);
}
//_____________________________________________________________________________
/**
 * Get a reference to the value of this property.  Note that the returned
 * reference can be used to change the value of this property.
 *
 * @return Reference to the value of this property.
 * @throws rdException When the property is not an rdPropertyInt.
 * @see rdPropertyStr
 */
string& rdProperty::
getValueStr()
{
	string msg;
	msg = "rdProperty.getValueStr(): Property type mismatch. ";
	msg += "This property is of type ";
	msg += getTypeAsString();
	msg += ".";

	throw rdException(msg,__FILE__,__LINE__);
}
//_____________________________________________________________________________
/**
 * Get a constant reference to the value of this property.
 *
 * @return Constant reference to the value of this property.
 * @throws rdException When the property is not an rdPropertyInt.
 * @see rdPropertyStr
 */
const string& rdProperty::
getValueStr() const
{
	string msg;
	msg = "rdProperty.getValueStr(): Property type mismatch. ";
	msg += "This property is of type ";
	msg += getTypeAsString();
	msg += ".";

	throw rdException(msg,__FILE__,__LINE__);
}

//-----------------------------------------------------------------------------
// VALUE OBJECT
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the value of this property.
 *
 * This method does nothing; it is just a place holder for
 * rdPropertyObj::setValue(), which is the only intended
 * meaningful implementation of this method.
 *
 * This method has been implemented in rdProperty, rather than made pure
 * virtual, so that all classes derived from rdProperty will not have to
 * implement this method.
 *
 * @param aValue Value to which this property is to be assigned.
 * @see rdPropertyObj
 */
void rdProperty::
setValue(const rdObject &aValue)
{
	string msg;
	msg = "rdProperty.setValue(const rdObject&): Property type mismatch. ";
	msg += "This property is of type ";
	msg += getTypeAsString();
	msg += ".";

	throw rdException(msg,__FILE__,__LINE__);
}
//_____________________________________________________________________________
/**
 * Get a reference to the value of this property.  Note that the returned
 * reference can be used to change the value of this property.
 *
 * @return Reference to the value of this property.
 * @throws rdException When the property is not an rdPropertyObj.
 * @see rdPropertyObj
 */
rdObject& rdProperty::
getValueObj()
{
	string msg;
	msg = "rdProperty.getValueObj(): Property type mismatch. ";
	msg += "This property is of type ";
	msg += getTypeAsString();
	msg += ".";

	throw rdException(msg,__FILE__,__LINE__);
}
//_____________________________________________________________________________
/**
 * Get a constant reference to the value of this property.
 *
 * @return Constant reference to the value of this property.
 * @throws rdException When the property is not an rdPropertyObj.
 * @see rdPropertyObj
 */
const rdObject& rdProperty::
getValueObj() const
{
	string msg;
	msg = "rdProperty.getValueObj(): Property type mismatch. ";
	msg += "This property is of type ";
	msg += getTypeAsString();
	msg += ".";

	throw rdException(msg,__FILE__,__LINE__);
}

//-----------------------------------------------------------------------------
// VALUE BOOL ARRAY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the value of this property.
 *
 * This method does nothing; it is just a place holder for
 * rdPropertyBoolArray::setValue(), which is the only intended meaningful
 * implementation of this method.
 *
 * This method has been implemented in rdProperty, rather than made pure
 * virtual, so that all classes derived from rdProperty will not have to
 * implement this method.
 *
 * @param aSize Size of the array.
 * @param aArray Array to which this property is to be assigned.
 * @throws rdException When the property is not an rdPropertyBoolArray.
 * @see rdPropertyBoolArray
 */
void rdProperty::
setValue(int aSize,const bool aArray[])
{
	string msg;
	msg = "rdProperty.setValue(int,bool[]): Property type mismatch. ";
	msg += "This property is of type ";
	msg += getTypeAsString();
	msg += ".";

	throw rdException(msg,__FILE__,__LINE__);
}
//_____________________________________________________________________________
/**
 * Set the value of this property.
 *
 * This method does nothing; it is just a place holder for
 * rdPropertyBoolArray::setValue, which is the only intended meaningful
 * implementation of this method.
 *
 * This method has been implemented in rdProperty, rather than made pure
 * virtual, so that all classes derived from rdProperty will not have to
 * implement this method.
 *
 * @param aArray Array to which this property is to be assigned.
 * @throws rdException When the property is not an rdPropertyBoolArray.
 * @see rdPropertyBoolArray
 */
void rdProperty::
setValue(const rdArray<bool> &aArray)
{
	string msg;
	msg = "rdProperty.getValue(const rdArray<bool>&): Property type mismatch. ";
	msg += "This property is of type ";
	msg += getTypeAsString();
	msg += ".";

	throw rdException(msg,__FILE__,__LINE__);
}
//_____________________________________________________________________________
/**
 * Get a reference to the value of this property.  Note that the returned
 * reference can be used to change the value of this property.
 *
 * @return Reference to the value of this property.
 * @throws rdException When the property is not an rdPropertyBoolArray.
 * @see rdPropertyBoolArray
 */
rdArray<bool>& rdProperty::
getValueBoolArray()
{
	string msg;
	msg = "rdProperty.getValueBoolArray(): Property type mismatch. ";
	msg += "This property is of type ";
	msg += getTypeAsString();
	msg += ".";

	throw rdException(msg,__FILE__,__LINE__);
}
//_____________________________________________________________________________
/**
 * Get a constant reference to the value of this property.
 *
 * @return Constant reference to the value of this property.
 * @throws rdException When the property is not an rdPropertyBoolArray.
 * @see rdPropertyBoolArray
 */
const rdArray<bool>& rdProperty::
getValueBoolArray() const
{
	string msg;
	msg = "rdProperty.getValueBoolArray(): Property type mismatch. ";
	msg += "This property is of type ";
	msg += getTypeAsString();
	msg += ".";

	throw rdException(msg,__FILE__,__LINE__);
}

//-----------------------------------------------------------------------------
// VALUE INT ARRAY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the value of this property.
 *
 * This method does nothing; it is just a place holder for
 * rdPropertyIntArray::setValue(), which is the only intended meaningful
 * implementation of this method.
 *
 * This method has been implemented in rdProperty, rather than made pure
 * virtual, so that all classes derived from rdProperty will not have to
 * implement this method.
 *
 * @param aSize Size of the array.
 * @param aArray Array to which this property is to be assigned.
 * @throws rdException When the property is not an rdPropertyIntArray.
 * @see rdPropertyIntArray
 */
void rdProperty::
setValue(int aSize,const int aArray[])
{
	string msg;
	msg = "rdProperty.setValue(int,int[]): Property type mismatch. ";
	msg += "This property is of type ";
	msg += getTypeAsString();
	msg += ".";

	throw rdException(msg,__FILE__,__LINE__);
}
//_____________________________________________________________________________
/**
 * Set the value of this property.
 *
 * This method does nothing; it is just a place holder for
 * rdPropertyIntArray::setValue, which is the only intended meaningful
 * implementation of this method.
 *
 * This method has been implemented in rdProperty, rather than made pure
 * virtual, so that all classes derived from rdProperty will not have to
 * implement this method.
 *
 * @param aArray Array to which this property is to be assigned.
 * @throws rdException When the property is not an rdPropertyIntArray.
 * @see rdPropertyIntArray
 */
void rdProperty::
setValue(const rdArray<int> &aArray)
{
	string msg;
	msg = "rdProperty.getValue(const rdArray<int>&): Property type mismatch. ";
	msg += "This property is of type ";
	msg += getTypeAsString();
	msg += ".";

	throw rdException(msg,__FILE__,__LINE__);
}
//_____________________________________________________________________________
/**
 * Get a reference to the value of this property.  Note that the returned
 * reference can be used to change the value of this property.
 *
 * @return Reference to the value of this property.
 * @throws rdException When the property is not an rdPropertyIntArray.
 * @see rdPropertyIntArray
 */
rdArray<int>& rdProperty::
getValueIntArray()
{
	string msg;
	msg = "rdProperty.getValueIntArray(): Property type mismatch. ";
	msg += "This property is of type ";
	msg += getTypeAsString();
	msg += ".";

	throw rdException(msg,__FILE__,__LINE__);
}
//_____________________________________________________________________________
/**
 * Get a constant reference to the value of this property.
 *
 * @return Constant reference to the value of this property.
 * @throws rdException When the property is not an rdPropertyIntArray.
 * @see rdPropertyIntArray
 */
const rdArray<int>& rdProperty::
getValueIntArray() const
{
	string msg;
	msg = "rdProperty.getValueIntArray(): Property type mismatch. ";
	msg += "This property is of type ";
	msg += getTypeAsString();
	msg += ".";

	throw rdException(msg,__FILE__,__LINE__);
}

//-----------------------------------------------------------------------------
// VALUE DOUBLE ARRAY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the value of this property.
 *
 * This method does nothing; it is just a place holder for
 * rdPropertyDblArray::setValue(), which is the only intended meaningful
 * implementation of this method.
 *
 * This method has been implemented in rdProperty, rather than made pure
 * virtual, so that all classes derived from rdProperty will not have to
 * implement this method.
 *
 * @param aSize Size of the array.
 * @param aArray Array to which this property is to be assigned.
 * @throws rdException When the property is not an rdPropertyDblArray.
 * @see rdPropertyDblArray
 */
void rdProperty::
setValue(int aSize,const double aArray[])
{
	string msg;
	msg = "rdProperty.setValue(int,double[]): Property type mismatch. ";
	msg += "This property is of type ";
	msg += getTypeAsString();
	msg += ".";

	throw rdException(msg,__FILE__,__LINE__);
}
//_____________________________________________________________________________
/**
 * Set the value of this property.
 *
 * This method does nothing; it is just a place holder for
 * rdPropertyDblArray::setValue, which is the only intended meaningful
 * implementation of this method.
 *
 * This method has been implemented in rdProperty, rather than made pure
 * virtual, so that all classes derived from rdProperty will not have to
 * implement this method.
 *
 * @param aArray Array to which this property is to be assigned.
 * @throws rdException When the property is not an rdPropertyDblArray.
 * @see rdPropertyDblArray
 */
void rdProperty::
setValue(const rdArray<double> &aArray)
{
	string msg;
	msg = "rdProperty.getValue(const rdArray<double>&): Property type mismatch. ";
	msg += "This property is of type ";
	msg += getTypeAsString();
	msg += ".";

	throw rdException(msg,__FILE__,__LINE__);
}
//_____________________________________________________________________________
/**
 * Get a reference to the value of this property.  Note that the returned
 * reference can be used to change the value of this property.
 *
 * @return Reference to the value of this property.
 * @throws rdException When the property is not an rdPropertyDblArray.
 * @see rdPropertyDblArray
 */
rdArray<double>& rdProperty::
getValueDblArray()
{
	string msg;
	msg = "rdProperty.getValueDblArray(): Property type mismatch. ";
	msg += "This property is of type ";
	msg += getTypeAsString();
	msg += ".";

	throw rdException(msg,__FILE__,__LINE__);
}
//_____________________________________________________________________________
/**
 * Get a constant reference to the value of this property.
 *
 * @return Constant reference to the value of this property.
 * @throws rdException When the property is not an rdPropertyDblArray.
 * @see rdPropertyDblArray
 */
const rdArray<double>& rdProperty::
getValueDblArray() const
{
	string msg;
	msg = "rdProperty.getValueDblArray(): Property type mismatch. ";
	msg += "This property is of type ";
	msg += getTypeAsString();
	msg += ".";

	throw rdException(msg,__FILE__,__LINE__);
}

//-----------------------------------------------------------------------------
// VALUE STRING ARRAY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the value of this property.
 *
 * This method does nothing; it is just a place holder for
 * rdPropertyStrArray::setValue(), which is the only intended meaningful
 * implementation of this method.
 *
 * This method has been implemented in rdProperty, rather than made pure
 * virtual, so that all classes derived from rdProperty will not have to
 * implement this method.
 *
 * @param aSize Size of the array.
 * @param aArray Array to which this property is to be assigned.
 * @throws rdException When the property is not an rdPropertyStrArray.
 * @see rdPropertyStrArray
 */
void rdProperty::
setValue(int aSize,const string aArray[])
{
	string msg;
	msg = "rdProperty.setValue(int,string[]): Property type mismatch. ";
	msg += "This property is of type ";
	msg += getTypeAsString();
	msg += ".";

	throw rdException(msg,__FILE__,__LINE__);
}
//_____________________________________________________________________________
/**
 * Set the value of this property.
 *
 * This method does nothing; it is just a place holder for
 * rdPropertyStrArray::setValue, which is the only intended meaningful
 * implementation of this method.
 *
 * This method has been implemented in rdProperty, rather than made pure
 * virtual, so that all classes derived from rdProperty will not have to
 * implement this method.
 *
 * @param aArray Array to which this property is to be assigned.
 * @throws rdException When the property is not an rdPropertyStrArray.
 * @see rdPropertyStrArray
 */
void rdProperty::
setValue(const rdArray<string> &aArray)
{
	string msg;
	msg = "rdProperty.getValue(const rdArray<string>&): Property type mismatch. ";
	msg += "This property is of type ";
	msg += getTypeAsString();
	msg += ".";

	throw rdException(msg,__FILE__,__LINE__);
}
//_____________________________________________________________________________
/**
 * Get a reference to the value of this property.  Note that the returned
 * reference can be used to change the value of this property.
 *
 * @return Reference to the value of this property.
 * @throws rdException When the property is not an rdPropertyStrArray.
 * @see rdPropertyStrArray
 */
rdArray<string>& rdProperty::
getValueStrArray()
{
	string msg;
	msg = "rdProperty.getValueStrArray(): Property type mismatch. ";
	msg += "This property is of type ";
	msg += getTypeAsString();
	msg += ".";

	throw rdException(msg,__FILE__,__LINE__);
}
//_____________________________________________________________________________
/**
 * Get a constant reference to the value of this property.
 *
 * @return Constant reference to the value of this property.
 * @throws rdException When the property is not an rdPropertyStrArray.
 * @see rdPropertyStrArray
 */
const rdArray<string>& rdProperty::
getValueStrArray() const
{
	string msg;
	msg = "rdProperty.getValueStrArray(): Property type mismatch. ";
	msg += "This property is of type ";
	msg += getTypeAsString();
	msg += ".";

	throw rdException(msg,__FILE__,__LINE__);
}

//-----------------------------------------------------------------------------
// VALUE RDOBJECT ARRAY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the value of this property.
 *
 * This method does nothing; it is just a place holder for
 * rdPropertyObjArray::setValue(), which is the only intended meaningful
 * implementation of this method.
 *
 * This method has been implemented in rdProperty, rather than made pure
 * virtual, so that all classes derived from rdProperty will not have to
 * implement this method.
 *
 * @param aSize Size of the array.
 * @param aArray Array to which this property is to be assigned.
 * @throws rdException When the property is not an rdPropertyObjArray.
 * @see rdPropertyObjArray
 */
void rdProperty::
setValue(int aSize,rdObject **aArray)
{
	string msg;
	msg = "rdProperty.setValue(int,rdObject**): Property type mismatch. ";
	msg += "This property is of type ";
	msg += getTypeAsString();
	msg += ".";

	throw rdException(msg,__FILE__,__LINE__);
}
//_____________________________________________________________________________
/**
 * Set the value of this property.
 *
 * This method does nothing; it is just a place holder for
 * rdPropertyObjArray::setValue, which is the only intended meaningful
 * implementation of this method.
 *
 * This method has been implemented in rdProperty, rather than made pure
 * virtual, so that all classes derived from rdProperty will not have to
 * implement this method.
 *
 * @param aArray Array to which this property is to be assigned.
 * @throws rdException When the property is not an rdPropertyObjArray.
 * @see rdPropertyObjArray
 */
void rdProperty::
setValue(const rdArrayPtrs<rdObject> &aArray)
{
	string msg;
	msg = "rdProperty.getValue(const rdArrayPtrs<rdObject>&):";
	msg += "Property type mismatch. ";
	msg += "This property is of type ";
	msg += getTypeAsString();
	msg += ".";

	throw rdException(msg,__FILE__,__LINE__);
}
//_____________________________________________________________________________
/**
 * Get a reference to the value of this property.  Note that the returned
 * reference can be used to change the value of this property.
 *
 * @return Reference to the value of this property.
 * @throws rdException When the property is not an rdPropertyObjArray.
 * @see rdPropertyObjArray
 */
rdArrayPtrs<rdObject>& rdProperty::
getValueObjArray()
{
	string msg;
	msg = "rdProperty.getValueObjArray(): Property type mismatch. ";
	msg += "This property is of type ";
	msg += getTypeAsString();
	msg += ".";

	throw rdException(msg,__FILE__,__LINE__);
}
//_____________________________________________________________________________
/**
 * Get a constant reference to the value of this property.
 *
 * @return Constant reference to the value of this property.
 * @throws rdException When the property is not an rdPropertyObjArray.
 * @see rdPropertyObjArray
 */
const rdArrayPtrs<rdObject>& rdProperty::
getValueObjArray() const
{
	string msg;
	msg = "rdProperty.getValueObjArray(): Property type mismatch. ";
	msg += "This property is of type ";
	msg += getTypeAsString();
	msg += ".";

	throw rdException(msg,__FILE__,__LINE__);
}

//-----------------------------------------------------------------------------
// USE DEFAULT
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set whether or not this property uses a "default" property for its value.
 *
 * True means that this property should have the same value as
 * some default property.  False means that the value of this property is
 * independent of the value of any other property.
 *
 * @param aTrueFalse True means this property uses another property for its
 * value.  False means this property does not use another property for its
 * value.
 */
void rdProperty::
setUseDefault(bool aTrueFalse)
{
	_useDefault = aTrueFalse;
}
//_____________________________________________________________________________
/**
 * Get whether or not this property uses a "default" property for its value.
 *
 * True means that this property should have the same value as
 * some default property.  False means that the value of this property is
 * independent of the value of any other property.
 *
 * @return True if this property uses another property for its value; false if
 * this property does not use another property for its value.
 */
bool rdProperty::
getUseDefault() const
{
	return(_useDefault);
}



