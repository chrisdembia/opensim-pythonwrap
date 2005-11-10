// rdProperty.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdProperty_h__
#define __rdProperty_h__


// INCLUDES
#include "rdTools.h"
#include <string>
#include "rdArray.h"
#include "rdArrayPtrs.h"

class rdObject;

#ifdef SWIG
	#ifdef RDTOOLS_API
		#undef RDTOOLS_API
		#define RDTOOLS_API
	#endif
#endif

//=============================================================================
//=============================================================================
/**
 * A property consists of a type, name, and a value or an array of values.
 *
 * Class rdProperty is an abstract base class that provides the functionality
 * common to all property types.
 *
 * At the time of the first formulation of the property classes, the only
 * property types that were envisioned are for a few fundamental data types
 * and for rdObject:\n\n
 * \tbool\n
 * \tint\n
 * \tfloat\n
 * \tdouble\n
 * \tstring\n
 * \trdObject\n
 * \tarray of bools\n
 * \tarray of ints\n
 * \tarray of floats\n
 * \tarray of doubles\n
 * \tarray of strings\n
 * \tarray of rdObjects\n\n
 *
 * As additional property types are needed, they may be added however.
 *
 * @todo Make default constructors for all derived classes
 * @version 1.0
 * @author Frank C. Anderson
 */
class RDTOOLS_API rdProperty  
{

//=============================================================================
// DATA
//=============================================================================
public:
	/** Enumeration of recognized types. */
	enum rdPropertyType
	{
		None=0,Bool, Int, Flt, Dbl, Str, Obj,
		BoolArray, IntArray, FltArray, DblArray, StrArray, ObjArray
	};

private:
	/** Type of the property. */
	rdPropertyType _type;
	/** Name of the property. */
	std::string _name;
	/** Flag indicating whether or not this property uses some
	default property for initializing its value. */
	bool _useDefault;
protected:
	/** String representation of property */
	std::string _valueString;
//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdProperty();
	rdProperty(rdPropertyType aType,const std::string &aName);
	rdProperty(const rdProperty &aProperty);
	virtual rdProperty* copy() const=0;
	virtual ~rdProperty() {};
	void setNull();

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
#ifndef SWIG
	rdProperty& operator=(const rdProperty &aProperty);
	virtual bool operator==(const rdProperty &aProperty) const;
	virtual bool operator<(const rdProperty &aProperty) const;
	friend std::ostream& operator<<(std::ostream &aOut,const rdProperty &aProperty) {
		aOut << aProperty.getTypeAsString() << " " << aProperty.getName();
		return(aOut);
	};
#endif
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
public:

	// TYPE
	void setType(rdPropertyType aType);
	rdPropertyType getType() const;
	virtual const char* getTypeAsString() const;

	// NAME
	void setName(const std::string &aName);
	const std::string& getName() const;

	// VALUE
	// Textual representation
	virtual const std::string &toString()=0;
	// Bool
	virtual void setValue(bool aValue);
	virtual bool& getValueBool();
#ifndef SWIG
	virtual const bool& getValueBool() const;
#endif
	// Int
	virtual void setValue(int aValue);
	virtual int& getValueInt();
#ifndef SWIG
	virtual const int& getValueInt() const;
#endif
	// Dbl
	virtual void setValue(double aValue);
	virtual double& getValueDbl();
#ifndef SWIG
	virtual const double& getValueDbl() const;
#endif
	// Str
	virtual void setValue(const std::string &aValue);
	virtual std::string& getValueStr();
#ifndef SWIG
	virtual const std::string& getValueStr() const;
#endif
	// Obj
	virtual void setValue(const rdObject &aValue);
	virtual rdObject& getValueObj();
#ifndef SWIG
	virtual const rdObject& getValueObj() const;
#endif
	// Bool Array
	virtual void setValue(int aSize,const bool aArray[]);
	virtual void setValue(const rdArray<bool> &aArray);
	virtual rdArray<bool>& getValueBoolArray();
#ifndef SWIG
	virtual const rdArray<bool>& getValueBoolArray() const;
#endif
	// Int Array
	virtual void setValue(int aSize,const int aArray[]);
	virtual void setValue(const rdArray<int> &aArray);
	virtual rdArray<int>& getValueIntArray();
#ifndef SWIG
	virtual const rdArray<int>& getValueIntArray() const;
#endif
	// Dbl Array
	virtual void setValue(int aSize,const double aArray[]);
	virtual void setValue(const rdArray<double> &aArray);
	virtual rdArray<double>& getValueDblArray();
#ifndef SWIG
	virtual const rdArray<double>& getValueDblArray() const;
#endif
	// Str Array
	virtual void setValue(int aSize,const std::string aArray[]);
	virtual void setValue(const rdArray<std::string> &aArray);
	virtual rdArray<std::string>& getValueStrArray();
#ifndef SWIG
	virtual const rdArray<std::string>& getValueStrArray() const;
#endif
	// Obj Array
	virtual void setValue(int aSize,rdObject **aArray);
	virtual void setValue(const rdArrayPtrs<rdObject> &aArray);
	virtual rdArrayPtrs<rdObject>& getValueObjArray();
#ifndef SWIG
	virtual const rdArrayPtrs<rdObject>& getValueObjArray() const;
#endif
	// USE DEFAULT
	void setUseDefault(bool aTrueFalse);
	bool getUseDefault() const;

//=============================================================================
};	// END of class rdProperty
//=============================================================================
//=============================================================================

#endif //__rdProperty_h__
