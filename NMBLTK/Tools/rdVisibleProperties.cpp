// rdVisibleProperties.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2002 Stanford University
// All rights reserved.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//============================================================================
// INCLUDES
//============================================================================
#include "rdVisibleProperties.h"
#include "rdException.h"
#include "rdMaterial.h"
#include "rdPropertyInt.h"
#include "rdPropertyBool.h"
#include "rdPropertyStr.h"


using namespace std;


//============================================================================
// CONSTANTS
//============================================================================


//=============================================================================
// CONSTRUCTOR(S)
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
rdVisibleProperties::~rdVisibleProperties()
{
}

//_____________________________________________________________________________
/**
 * Default constructor.
 */
rdVisibleProperties::rdVisibleProperties():
_displayPreference((DisplayPreference&)_propDisplayPreference.getValueInt()),
_showNormals(_propShowNormals.getValueBool()),
_showAxes(_propShowAxes.getValueBool()),
_materialName(_propMaterialName.getValueStr())
{
	// NULL STATES
	setNull();

	// MEMBER VARIABLES
	setType("rdVisibleProperties");
	setName("");

}

//_____________________________________________________________________________
/**
 * Construct an object from file.
 *
 * The object is constructed from the root element of the XML document.
 * The type of object is the tag name of the XML root element.
 *
 * @param aFileName File name of the document.
 */
rdVisibleProperties::rdVisibleProperties(const string &aFileName):
rdObject(aFileName),
_displayPreference((DisplayPreference&)_propDisplayPreference.getValueInt()),
_showNormals(_propShowNormals.getValueBool()),
_showAxes(_propShowAxes.getValueBool()),
_materialName(_propMaterialName.getValueStr())
{
	// NULL STATES
	setNull();
	// Serialize from XML
	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Construct an object from a document.
 *
 * The document is copied and this object, including its derived classes,
 * are constructed based on the nodes within the document.
 */
rdVisibleProperties::rdVisibleProperties(const rdXMLDocument *aDocument):
_displayPreference((DisplayPreference&)_propDisplayPreference.getValueInt()),
_showNormals(_propShowNormals.getValueBool()),
_showAxes(_propShowAxes.getValueBool()),
_materialName(_propMaterialName.getValueStr())
{
	// NULL STATES
	setNull();
}
//_____________________________________________________________________________
/**
 * Construct an object from an DOMElement.
 */
rdVisibleProperties::rdVisibleProperties(DOMElement *aElement):
rdObject(aElement),
_displayPreference((DisplayPreference&)_propDisplayPreference.getValueInt()),
_showNormals(_propShowNormals.getValueBool()),
_showAxes(_propShowAxes.getValueBool()),
_materialName(_propMaterialName.getValueStr())
{
	// NULL STATES
	setNull();

	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * Copy constructors for all rdVisibleProperties's only copy the non-XML variable
 * members of the object; that is, the object's DOMnode and rdXMLDocument
 * are not copied but set to NULL.  The reason for this is that for the
 * object and all its derived classes to establish the correct connection
 * to the XML document nodes, the the object would need to reconstruct based
 * on the XML document not the values of the object's member variables.
 *
 * There are three proper ways to generate an XML document for an rdVisibleProperties:
 *
 * 1) Construction based on XML file (@see rdVisibleProperties(const char *aFileName)).
 * In this case, the XML document is created by parsing the XML file.
 *
 * 2) Construction by rdVisibleProperties(const rdXMLDocument *aDocument).
 * This constructor explictly requests construction based on an
 * XML document.  In this way the proper connection between an object's node
 * and the corresponding node within the XML document is established.
 * This constructor is a copy constructor of sorts because all essential
 * rdVisibleProperties member variables should be held within the XML document.
 * The advantage of this style of construction is that nodes
 * within the XML document, such as comments that may not have any
 * associated rdVisibleProperties member variable, are preserved.
 *
 * 3) A call to generateDocument().
 * This method generates an XML document for the rdVisibleProperties from scratch.
 * Only the essential document nodes are created (that is, nodes that
 * correspond directly to member variables.).
 *
 * @param aObject Object to be copied.
 * @see rdVisibleProperties(const rdXMLDocument *aDocument)
 * @see rdVisibleProperties(const char *aFileName)
 * @see generateDocument()
 */
rdVisibleProperties::rdVisibleProperties(const rdVisibleProperties &aObject):
_displayPreference((DisplayPreference&)_propDisplayPreference.getValueInt()),
_showNormals(_propShowNormals.getValueBool()),
_showAxes(_propShowAxes.getValueBool()),
_materialName(_propMaterialName.getValueStr())
{
	// NULL MEMBER VARIABLES
	setNull();

	// COPY TYPE AND NAME
	*this = aObject;
}
/**
 * virtual copy constructor
 */
rdObject* rdVisibleProperties::
copy() const
{

	rdVisibleProperties *object = new rdVisibleProperties(*this);
	return(object);
}
/**
 * virtual copy constructor from DOMElement
 */

rdObject* rdVisibleProperties::
copy(DOMElement *aElement) const
{
	rdVisibleProperties *object = new rdVisibleProperties(aElement);
	*object = *this;
	object->updateFromXMLNode();
	return(object);
}


//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Set all member variables to their null or default values.
 */
void rdVisibleProperties::
setNull()
{
	setupProperties();

	_displayPreference = GouraudShaded;
	_showNormals=false;
	_showAxes=false;
	_materialName="DEFAULT";
}

//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void rdVisibleProperties::
setupProperties()
{
	_propertySet.append( &_propDisplayPreference );
	_propDisplayPreference.setName("DisplayPreference");
	_propDisplayPreference.setValue(1);

	_propertySet.append( &_propShowNormals );
	_propShowNormals.setName("ShowNormals");
	_propShowNormals.setValue(false);

	_propertySet.append( &_propShowAxes );
	_propShowAxes.setName("ShowAxes");
	_propShowAxes.setValue(false);

	_propertySet.append( &_propMaterialName );
	_propMaterialName.setName("MaterialName");
	_propMaterialName.setValue("DEFAULT");

}

//=============================================================================
// OPERATORS
//=============================================================================
//-----------------------------------------------------------------------------
// ASSIGNMENT
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Assign this object to the values of another.
 *
 * @return Reference to this object.
 */
rdVisibleProperties& rdVisibleProperties::
operator=(const rdVisibleProperties &aObject)
{
	// BASE CLASS
	rdObject::operator=(aObject);

	// Class Members
	_displayPreference = (aObject._displayPreference);
	_showNormals = (aObject._showNormals);
	_showAxes = (aObject._showAxes);
	_materialName =  (aObject._materialName);
	return(*this);
}

//-----------------------------------------------------------------------------
// EQUALITY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Determine if two objects are equal.
 *
 * @return True if the two objects are equal, false otherwise.
 */
bool rdVisibleProperties::
operator==(const rdVisibleProperties &aObject)
{
	if(getType() != aObject.getType()) return(false);
	if(getName() != aObject.getName()) return(false);
	return(true);
}


//=============================================================================
// GET AND SET
//=============================================================================
//_____________________________________________________________________________
/**
 * setDisplayPreference: Wireframe, shaded, ...
 *
 */
void rdVisibleProperties::
setDisplayPreference(const DisplayPreference aDisplayPreference)
{
	_displayPreference =aDisplayPreference;
}

//_____________________________________________________________________________
/**
 * getDisplayPreference: Wireframe, shaded, ...
 *
 */
rdVisibleProperties::DisplayPreference rdVisibleProperties::
getDisplayPreference() const
{
	return _displayPreference;
}
//_____________________________________________________________________________
/**
 * setShowNormals flag
 *
 */
void rdVisibleProperties::
setShowNormals(const bool showNormals)
{
	_showNormals =showNormals;
}

//_____________________________________________________________________________
/**
 * getShowNormals flag
 *
 */
bool rdVisibleProperties::
getShowNormals() const
{
	return _showNormals;
}

//_____________________________________________________________________________
/**
 * setShowAxes flag
 *
 */
void rdVisibleProperties::
setShowAxes(const bool showAxes)
{
	_showAxes =showAxes;
}

//_____________________________________________________________________________
/**
 * getShowAxes flag
 *
 */
bool rdVisibleProperties::
getShowAxes() const
{
	return _showAxes;
}

//_____________________________________________________________________________
/**
 * get the name of the material associated with object
 *
 */
const char *rdVisibleProperties::
getMaterialName() const
{
	return _materialName.c_str();
}

//_____________________________________________________________________________
/**
 * set the name of the material associated with object
 *
 */
void rdVisibleProperties::
setMaterialName(const char *matName)
{
	_materialName = matName;
}
