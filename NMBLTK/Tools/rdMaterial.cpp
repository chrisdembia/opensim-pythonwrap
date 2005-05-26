// rdMaterial.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2002 Stanford University
// All rights reserved.
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//============================================================================
// INCLUDES
//============================================================================
#include "rdMaterial.h"
#include "rdException.h"
#include "rdPropertyDbl.h"
#include "rdPropertyDblArray.h"

using namespace std;

//============================================================================
// CONSTANTS
//============================================================================
rdMaterial *rdMaterial::_defaultMaterial=0;

//=============================================================================
// CONSTRUCTOR(S)
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
rdMaterial::~rdMaterial()
{
}

//_____________________________________________________________________________
/**
 * Default constructor.
 */
rdMaterial::rdMaterial():
_translucency(_propTranslucency.getValueDbl()),
_ambientColor(_propAmbientColor.getValueDblArray()),
_diffuseColor(_propDiffuseColor.getValueDblArray()),
_specularColor(_propSpecularColor.getValueDblArray())
{
	// NULL STATES
	setNull();

	// MEMBER VARIABLES
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
rdMaterial::rdMaterial(const string &aFileName):
rdObject(aFileName),
_translucency(_propTranslucency.getValueDbl()),
_ambientColor(_propAmbientColor.getValueDblArray()),
_diffuseColor(_propDiffuseColor.getValueDblArray()),
_specularColor(_propSpecularColor.getValueDblArray())
{
	// NULL STATES
	setNull();

	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Construct an object from an DOMElement.
 */
rdMaterial::rdMaterial(DOMElement *aElement):
rdObject(aElement),
_translucency(_propTranslucency.getValueDbl()),
_ambientColor(_propAmbientColor.getValueDblArray()),
_diffuseColor(_propDiffuseColor.getValueDblArray()),
_specularColor(_propSpecularColor.getValueDblArray())
{
	// NULL STATES
	setNull();

	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * Copy constructors for all rdMaterial's only copy the non-XML variable
 * members of the object; that is, the object's DOMnode and rdXMLDocument
 * are not copied but set to NULL.  The reason for this is that for the
 * object and all its derived classes to establish the correct connection
 * to the XML document nodes, the the object would need to reconstruct based
 * on the XML document not the values of the object's member variables.
 *
 * There are three proper ways to generate an XML document for an rdMaterial:
 *
 * 1) Construction based on XML file (@see rdMaterial(const char *aFileName)).
 * In this case, the XML document is created by parsing the XML file.
 *
 * 2) Construction by rdMaterial(const rdXMLDocument *aDocument).
 * This constructor explictly requests construction based on an
 * XML document.  In this way the proper connection between an object's node
 * and the corresponding node within the XML document is established.
 * This constructor is a copy constructor of sorts because all essential
 * rdMaterial member variables should be held within the XML document.
 * The advantage of this style of construction is that nodes
 * within the XML document, such as comments that may not have any
 * associated rdMaterial member variable, are preserved.
 *
 * 3) A call to generateDocument().
 * This method generates an XML document for the rdMaterial from scratch.
 * Only the essential document nodes are created (that is, nodes that
 * correspond directly to member variables.).
 *
 * @param aObject Object to be copied.
 * @see rdMaterial(const rdXMLDocument *aDocument)
 * @see rdMaterial(const char *aFileName)
 * @see generateDocument()
 */
rdMaterial::rdMaterial(const rdMaterial &aObject):
rdObject(aObject),
_translucency(_propTranslucency.getValueDbl()),
_ambientColor(_propAmbientColor.getValueDblArray()),
_diffuseColor(_propDiffuseColor.getValueDblArray()),
_specularColor(_propSpecularColor.getValueDblArray())
{
	// NULL MEMBER VARIABLES
	setNull();

	// COPY TYPE AND NAME
	*this = aObject;
}
//_____________________________________________________________________________
/**
 * Virtual copy constructor 
 */
rdObject* rdMaterial::
copy() const
{
	return(new rdMaterial(*this));
}
//_____________________________________________________________________________
/**
 * Virtual copy constructor from XMLNode
 */
rdObject* rdMaterial::
copy(DOMElement *aElement) const
{
	rdMaterial *m= new rdMaterial(aElement);
	*m= *this;
	m->updateFromXMLNode();
	return(m);

}

//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Set all member variables to their null or default values.
 */
void rdMaterial::
setNull()
{
	setType("rdMaterial");
	//...
	setupProperties();
}
//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void rdMaterial::
setupProperties()
{
   double white[3] = { 1.0, 1.0, 1.0 };

   _propertySet.append( new rdPropertyDbl("translucency",1.0) );
   _propertySet.append( new rdPropertyDblArray("ambient",3,white) );
   _propertySet.append( new rdPropertyDblArray("diffuse",3,white) );
   _propertySet.append( new rdPropertyDblArray("specular",3,white) );

    _propertySet.append( &_propTranslucency );
	_propTranslucency.setName("translucency");
	_propTranslucency.setValue(1.0);

	_propertySet.append( &_propAmbientColor);
	_propAmbientColor.setName("ambient");
	_propAmbientColor.setValue(3, white);

	_propertySet.append( &_propDiffuseColor);
	_propDiffuseColor.setName("diffuse");
	_propDiffuseColor.setValue(3, white);

	_propertySet.append( &_propSpecularColor );
	_propDiffuseColor.setName("specular");
	_propDiffuseColor.setValue(3, white);

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
rdMaterial& rdMaterial::
operator=(const rdMaterial &aObject)
{
	// BASE CLASS
	rdObject::operator=(aObject);

	// Class Members
	_translucency = (aObject._translucency);
	for(int i=0; i < 3; i++){
		_ambientColor[i] = aObject._ambientColor[i];
		_diffuseColor[i] = aObject._diffuseColor[i];
		_specularColor[i] = aObject._specularColor[i];
	}
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
bool rdMaterial::
operator==(const rdMaterial &aObject)
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
 * Set the Translucency for this Material.
 */
void rdMaterial::
setTranslucency(const double aTranslucency)
{
	_translucency=aTranslucency;
}

/**
 * Get the Translucency for this Material.
 */
double rdMaterial::
getTranslucency() const
{
	return _translucency;
}

/**
 * Set the Ambient Color for this Material.
 */

void rdMaterial::
setAmbientColor(const double aAmbientColor[3])
{
	for(int i=0; i < 3; i++)
		_ambientColor[i]=aAmbientColor[i];
}
/**
 * Get the Ambient Color for this Material.
 */
const double* rdMaterial::
getAmbientColor() const
{
	return &_ambientColor[0];
}

/**
 * Set the Diffuse Color for this Material.
 */
void rdMaterial::
setDiffuseColor(const double aDiffuseColor[3])
{
	for(int i=0; i < 3; i++)
		_diffuseColor[i]=aDiffuseColor[i];
}

/**
 * Get the Diffuse Color for this Material.
 */
const double* rdMaterial::
getDiffuseColor() const
{
	return &(_diffuseColor[0]);
}
/**
 * Set the Specular Color for this Material.
 */
void rdMaterial::
setSpecularColor(const double aSpecularColor[3])
{
	for(int i=0; i < 3; i++)
		_specularColor[i]=aSpecularColor[i];
}
/**
 * Get the Specular Color for this Material.
 */
const double* rdMaterial::
getSpecularColor() const
{
	return &(_specularColor[0]);
}

//-----------------------------------------------------------------------------
// NODE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the node set for this object.
 *
 * @return Node set for this object.
 */
DOMElement* rdMaterial::
getNode() const
{
	return(_node);
}


//=============================================================================
// XML serialization support
//=============================================================================
//=============================================================================
// Static functions to handle default Material
//=============================================================================
//_____________________________________________________________________________
/**
 * These methods use lazy evaluation so the default is created only on demand
 */
const string& rdMaterial::
GetDefaultMaterialName()
{
	// create default material here if needed then get its name
	const rdMaterial &defMat = GetDefaultMaterial();

	return(defMat.getName());
}
//_____________________________________________________________________________
/**
 * Return the default Material
 */
const rdMaterial &rdMaterial::
GetDefaultMaterial()
{
	if (_defaultMaterial)
		return (*_defaultMaterial);
	_defaultMaterial = new rdMaterial();
	_defaultMaterial->setName("DEFAULT");
	// Other properties are defaults generated in setNull function above
	return (*_defaultMaterial);
}
