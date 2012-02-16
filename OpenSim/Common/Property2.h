#ifndef _Property2_h_
#define _Property2_h_
// Property.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*
* Copyright (c)  2005, Stanford University. All rights reserved. 
* Use of the OpenSim software in source form is permitted provided that the following
* conditions are met:
* 	1. The software is used only for non-commercial research and education. It may not
*     be used in relation to any commercial activity.
* 	2. The software is not distributed or redistributed.  Software distribution is allowed 
*     only through https://simtk.org/home/opensim.
* 	3. Use of the OpenSim software or derivatives must be acknowledged in all publications,
*      presentations, or documents describing work in which OpenSim or derivatives are used.
* 	4. Credits to developers may not be removed from executables
*     created from modifications of the source.
* 	5. Modifications of source code must retain the above copyright notice, this list of
*     conditions and the following disclaimer. 
* 
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
*  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
*  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
*  SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
*  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
*  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
*  OR BUSINESS INTERRUPTION) OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
*  WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/* Note: This code was originally developed by Realistic Dynamics Inc. 
 * Author: Frank C. Anderson 
 */


// INCLUDES
#include "osimCommonDLL.h"
#include "Array.h"
#include "ArrayPtrs.h"
#include "SimTKsimbody.h"

#include <string>
#include <cmath>

namespace OpenSim {

//=============================================================================
//=============================================================================
/**
 * A property consists of a type, name, and a value or an array of values.
 *
 * Class Property is an abstract base class that provides the functionality
 * common to all property types.
 *
 * At the time of the first formulation of the property classes, the only
 * property types that were envisioned are for a few fundamental data types
 * and for Object:
 * - bool
 * - int
 * - float
 * - double
 * - string
 * - Object
 * - Object pointer
 * - array of bools
 * - array of ints
 * - array of floats
 * - array of doubles
 * - array of strings
 * - array of Objects
 *
 * As additional property types are needed, they may be added however.
 *
 * @todo Make default constructors for all derived classes
 * @version 1.0
 * @author Frank C. Anderson
 */

class OSIMCOMMON_API AbstractProperty
{
private:
	std::string _name;
	std::string _type;
	std::string _comment;
	bool _useDefault;
	bool _matchName;
	int _index;
	int _minArraySize; // minimum number of elements for a property of array type
	int _maxArraySize; // maximum number of elements for a property of array type

public:
	/** Enumeration of recognized types. */
	enum PropertyType
	{
		None=0, Bool, Int, Dbl, Str, Obj, ObjPtr,
		BoolArray, IntArray, DblArray, StrArray, ObjArray,
		DblVec3,
		Transform // 3 BodyFixed X,Y,Z Rotations followed by 3 Translations
		//Station	   Point on a Body: String, Vec3 
	};

	AbstractProperty();
	AbstractProperty(const std::string &aName, const std::string &aType, const std::string &aComment);
	AbstractProperty(const AbstractProperty &aAbstractProperty);
	virtual ~AbstractProperty() {}
	virtual AbstractProperty& operator=(const AbstractProperty &aAbstractProperty);
	virtual AbstractProperty* copy() const = 0;
	virtual bool equals(AbstractProperty* aAbstractPropertyPtr) const = 0;
	std::string getName() const { return _name; }
	void setName(std::string aName){ _name = aName; }
	std::string getType() const { return _type; }
	void setType(std::string aType){ _type = aType; }
	virtual PropertyType getPropertyType() const = 0;
	std::string getComment() const { return _comment; }
	void setComment(std::string aComment){ _comment = aComment; }
	bool getUseDefault() const { return _useDefault; }
	void setUseDefault(bool aTrueFalse) { _useDefault = aTrueFalse; }
	bool getMatchName() const { return _matchName; }
	void setMatchName(bool aMatchName) { _matchName = aMatchName; }
	int getIndex() { return _index; }
	void setIndex(int aIndex) { _index = aIndex; }
	void setAllowableArraySize(int aMin, int aMax) { _minArraySize = aMin; _maxArraySize = aMax; }
	void setAllowableArraySize(int aNum) { _minArraySize = _maxArraySize = aNum; }
	int getMinArraySize() { return _minArraySize; }
	int getMaxArraySize() { return _maxArraySize; }

private:
	void setNull();
};

template <class T>
class Property2 : public AbstractProperty
{

//=============================================================================
// DATA
//=============================================================================
private:
	T* _valuePtr;

public:
	Property2();
	Property2(const std::string &aName, const std::string &aType, const std::string &aComment, const T &aValue);
	Property2(const Property2 &aProperty);
	virtual ~Property2() { delete _valuePtr; }
	virtual Property2& operator=(const Property2 &aProperty);
	virtual Property2* copy() const;
	virtual bool equals(AbstractProperty* aAbstractPropertyPtr) const;
	const T& getValue() const { return *_valuePtr; }
	T& updValue() { return *_valuePtr; }
	void setValue(const T &aValue) { *_valuePtr = aValue; }
	virtual PropertyType getPropertyType() const {throw Exception("Property2: Use of unspecified property."); return None;}
};

template <>
inline bool Property2<double>::equals(AbstractProperty *aAbstractPropertyPtr) const
{
	Property2<double> *aPropertyPtr = dynamic_cast<Property2<double> *>(aAbstractPropertyPtr);
	if (aPropertyPtr) {
		if (fabs(*_valuePtr - aPropertyPtr->getValue()) > 1e-7)
			return false;
		else
			return true;
	}
	return false;
}

template <>
inline AbstractProperty::PropertyType Property2<double>::getPropertyType() const { return Dbl; }

template <>
inline AbstractProperty::PropertyType Property2<bool>::getPropertyType() const { return Bool; }

template <>
inline AbstractProperty::PropertyType Property2<int>::getPropertyType() const { return Int; }

template <>
inline AbstractProperty::PropertyType Property2<std::string>::getPropertyType() const { return Str; }

template <>
inline AbstractProperty::PropertyType Property2< Array<bool> >::getPropertyType() const { return BoolArray; }

template <>
inline AbstractProperty::PropertyType Property2< Array<int> >::getPropertyType() const { return IntArray; }

template <>
inline AbstractProperty::PropertyType Property2< Array<double> >::getPropertyType() const { return DblArray; }

template <>
inline AbstractProperty::PropertyType Property2< Array<std::string> >::getPropertyType() const { return StrArray; }

template <>
inline AbstractProperty::PropertyType Property2<SimTK::Vec3>::getPropertyType() const { return DblVec3; }

/*
template <>
inline AbstractProperty::PropertyType Property2<Object>::getPropertyType() const { return Obj; }

template <>
inline AbstractProperty::PropertyType Property2< Array<Object> >::getPropertyType() const { return ObjArray; }

template <>
inline AbstractProperty::PropertyType Property2<Object *>::getPropertyType() const { return ObjPtr; }
*/

template <typename T>
Property2<T>::Property2()
{
	_valuePtr = new T;
}

template <typename T>
Property2<T>::Property2(const std::string &aName, const std::string &aType, const std::string &aComment, const T &aValue) : AbstractProperty(aName, aType, aComment)
{
	_valuePtr = new T(aValue);
}

template <typename T>
Property2<T>::Property2(const Property2<T> &aProperty) : AbstractProperty(aProperty)
{
	_valuePtr = new T(aProperty.getValue());
}

template <typename T>
Property2<T>& Property2<T>::operator=(const Property2<T> &aProperty)
{
	AbstractProperty::operator=(aProperty);
	*_valuePtr = aProperty.getValue();
	return *this;
}

template <typename T>
Property2<T>* Property2<T>::copy() const
{
	Property2<T> *prop = new Property2<T>(*this);
	return prop;
}

template <typename T>
bool Property2<T>::equals(AbstractProperty* aAbstractPropertyPtr) const
{
	Property2<T>* aPropertyPtr = dynamic_cast<Property2<T>*>(aAbstractPropertyPtr);
	if (aPropertyPtr)
		return *_valuePtr == aPropertyPtr->getValue();
	return false;
}

}; //namespace
//=============================================================================
//=============================================================================

#endif //__Property2_h__
