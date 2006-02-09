// rdObject.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2002-2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdObject_h__
#define __rdObject_h__

#ifdef WIN32
#pragma warning( disable : 4251 )
#pragma warning( disable : 4786 )
#pragma warning( disable : 4660 )
#endif

// INCLUDES
#include <assert.h>
#include <map>
#include "rdObservable.h"
#include "rdEvent.h"
#include "rdTools.h"
#include "rdPropertySet.h"
#include "rdXMLNode.h"
#include "rdXMLDocument.h"


// DISABLES MULTIPLE INSTANTIATION WARNINGS


// EXPORT LINE FOR MICROSOFT VISUAL C++
#ifdef WIN32
#ifndef SWIG
template class RDTOOLS_API rdArrayPtrs<rdObject>;
#endif
#endif

typedef std::map<std::string, rdObject*, std::less<std::string> > stringsToObjects;
typedef std::map<std::string, bool, std::less<std::string> > defaultsReadFromFile;


// CONSTANTS
const char rdObjectDEFAULT_NAME[] = "default";

#ifdef SWIG
	#ifdef RDTOOLS_API
		#undef RDTOOLS_API
		#define RDTOOLS_API
	#endif
#endif

//=============================================================================
//=============================================================================
/**
 * Class rdOject is intended to be used as the base class for all
 * Realistic Dynamics, Inc. objects.  It provides a common object from which
 * to derive and also some basic functionality, such as writing to files
 * in XML format and the equality, less than, and output operators.
 * Future enhancements to rdObject might include thread functionality.
 *
 * @version 1.0
 * @author Frank C. Anderson
 * @todo Use a hash table to store registered object types.
 */
class RDTOOLS_API rdObject  
{

//=============================================================================
// DATA
//=============================================================================
private:
	/** Array of all registered object types.  Each object type only appears
	once in this array.  Future enhancements could be using a hash table
	instead of an array. */
	static rdArrayPtrs<rdObject> _Types;

	static rdArray<XMLCh *> _typeNames;
	/** 
	 * A Hash map that maps an std::string& to the corresponding default object.
	 */
	static stringsToObjects _mapTypesToDefaultObjects;
	/**
	 * A Hash map that maps an std::string& to the flag specifying if default objects are user specified in file
	 */
	static defaultsReadFromFile	_defaultsReadFromFile;
	/**
	 * Global flag to indicate if all registered objects are written in the defaults section
	 */
	static bool _serializeAllDefaults;
	/**
	* A pointer to the observable object implementation. Null if not needed to minimize
	* memory overhead 
	*/
	rdObservable	*_observable;
public:
	/** A length limit for a name. */
#ifndef SWIG
	enum { NAME_LENGTH=128 };
	/** Name used for default objects when they are serialized. */
	static const std::string DEFAULT_NAME;
#endif
protected:
	/** Property set for serializable member variables of this and
	derived classes. */
	rdPropertySet _propertySet;
	/** Type. */
	std::string _type;
	/** Name. Made protected so that classes can customize their setName.  
	-Ayman 04/04 */
	std::string _name;
	/** A description of the object. -> rdSerializable interface */
	std::string _description;
	/** XML document. -> rdSerializable interface */
	rdXMLDocument *_document;
	/** XML element node. -> rdSerializable interface */
	DOMElement *_node;
	/** Inlined object -> rdSerializable interface */
	bool _inLined;
	/** For non inlined objects their _node and _document refer to external file
	 * _refNode contains the type and reference to file name -> rdSerializable interface */
	DOMElement *_refNode;
//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	virtual ~rdObject();
	rdObject();
	rdObject(const std::string &aFileName);
	rdObject(const rdXMLDocument *aDocument);
	rdObject(DOMElement *aNode);
	rdObject(const rdObject &aObject);
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aNode) const;
//	static rdObject* ConstructObject(DOMElement *aNode);
private:
	void setNull();
	void setupProperties();
	void init();
	void buildTypeNamesTable();

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
#ifndef SWIG
	rdObject& operator=(const rdObject &aObject);
	virtual bool operator==(const rdObject &aObject) const;
	virtual bool operator<(const rdObject &aObject) const;
	friend std::ostream& operator<<(std::ostream &aOut,
												const rdObject &aObject) {
		aOut << aObject.getType() << " " << aObject.getName();
		return(aOut);
	};
#endif

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
protected:
	void setType(const std::string &aType);
public:
	const std::string& getType() const;
	void setName(const std::string &aName);
	const std::string& getName() const;
	void setDescription(const std::string &aDescrip);
	const std::string& getDescription() const;
	const std::string& toString() const;
	rdPropertySet& getPropertySet() { return(_propertySet); }
#ifndef SWIG
	const rdPropertySet& getPropertySet() const { return(_propertySet); }
#endif

	//--------------------------------------------------------------------------
	// REGISTRATION OF TYPES AND DEFAULT OBJECTS
	//--------------------------------------------------------------------------
	static void RegisterType(const rdObject &aObject);

	//--------------------------------------------------------------------------
	// XML NEW
	//--------------------------------------------------------------------------
	virtual bool isValidDefaultType(const rdObject *aObject) const;
	virtual void updateFromXMLNode();
	virtual void updateDefaultObjectsFromXMLNode();
	virtual void updateXMLNode(DOMElement *aParent);
	virtual void generateXMLNode(DOMElement *aParent);
	// Inline support
	void setInlined(const bool aInLined, const char *aFileName=NULL);
	bool getInlined() const;
	const char *getOffLineFileName() const;
	void clearXMLNodes();
	rdXMLDocument* getDocument() const;
	DOMElement* getXMLNode() const;
protected:
	void setXMLNode(DOMElement *aNode);
private:
	void generateXMLDocument();
	void generateDocument();

	//--------------------------------------------------------------------------
	// IO
	//--------------------------------------------------------------------------
public:
	bool print(const std::string &aFileName);
	// Observable Interface
	//--------------------------------------------------------------------------
	// Manage Observers
	//--------------------------------------------------------------------------
	void addObserver(rdObject& aObserver)
	{
		if (!_observable)
			_observable = new rdObservable(*this);	// Lazy creation of observable
		assert(_observable);
		_observable->addObserver(aObserver);
	};
	void deleteObserver(rdObject& aObserver)
	{
		assert(_observable);
		_observable->deleteObserver(aObserver);
	};
	/**
	 * Eventually observers will have to specify what event to observe so that they're not
	 * called unnecessarily. Will do this after the rdEvent class hierarchy matures.
	 */
	void addObserverEvent(rdObject& aObserver, rdEvent& aEvent)
	{};
	void notifyObservers(rdEvent& aEvent)
	{
		if (!_observable)	// No observer has been added
			return;
		assert(_observable);
		_observable->notifyObservers(aEvent);
	};

	void deleteObservers()
	{
		assert(_observable);
		_observable->deleteObservers();
	};
	int countObservers() const
	{
		if (!_observable)	// No observer has been added
			return 0;		
		assert(_observable);
		return _observable->countObservers();
	};
protected:
	//--------------------------------------------------------------------------
	// Manage _changed flag
	//--------------------------------------------------------------------------
	void setChanged()
	{
		if (!_observable)	// No observer has been added
			return;		
		assert(_observable);
		_observable->setChanged();
	};
	void clearChanged()
	{
		if (!_observable)	// No observer has been added
			return;		
		assert(_observable);
		_observable->clearChanged();
	};
	bool hasChanged()
	{
		if (!_observable)	// No observer has been added
			return false;		
		assert(_observable);
		return (_observable->hasChanged());
	};
public:
	virtual void update(const rdObject& aObject, rdEvent& aEvent) {};
	/* Static functions to specify and query if all registered objects are written 
	 * to the defaults section of output files rather than only those 
	 * explicitly specified by the user in input files */
	static void setSerializeAllDefaults(bool aBoolean)
	{
		_serializeAllDefaults = aBoolean;
	}
	static bool getSerializeAllDefaults()
	{
		return _serializeAllDefaults;
	}
//=============================================================================
};	// END of class rdObject
//=============================================================================
//=============================================================================
/**
 * Add public static method declaration in class derived from an abstract
 * parent to assist in downcasting objects of the parent type to the 
 * derived type.
 */
#define NMBLTK_DERIVED(Derived,Parent) \
    static bool isA(const Parent& p)                        \
        { return dynamic_cast<const Derived*>(&p) != 0; }   \
    static const Derived& downcast(const Parent& p)         \
        { return dynamic_cast<const Derived&>(p); }         \
    static Derived& downcast(Parent& p)                     \
        { return dynamic_cast<Derived&>(p); }

/**
 * This is like NMBLTK_DERIVED except it allows for an intermediate
 * "helper" class between Derived and Parent.
 */
#define NMBLTK_DERIVED2(Derived,Helper,Parent) \
    static bool isA(const Parent& p)                                        \
        { return Helper::isA(p); }                                          \
    static const Derived& downcast(const Parent& p)                         \
        { return reinterpret_cast<const Derived&>(Helper::downcast(p)); }   \
    static Derived& downcast(Parent& p)                                     \
        { return reinterpret_cast<Derived&>(Helper::downcast(p)); }

#endif //__rdObject_h__
