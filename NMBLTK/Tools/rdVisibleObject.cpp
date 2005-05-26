// rdVisibleObject.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2004 Stanford University
// All rights reserved.
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//============================================================================
// INCLUDES
//============================================================================
#include "rdVisibleObject.h"
#include "rdException.h"
#include "rdPropertyInt.h"
#include "rdPropertyStr.h"
#include "rdPropertyObj.h"
#include "rdPropertyStrArray.h"
#include "rdPropertyDblArray.h"

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
rdVisibleObject::~rdVisibleObject()
{
}

//_____________________________________________________________________________
/**
 * Default constructor.
 */
rdVisibleObject::rdVisibleObject():
_geometryFileNames(_propGeometryFileNames.getValueStrArray()),
_propVisibleProp(rdPropertyObj("VisibleProperties", rdVisibleProperties())),
_visibleProp((rdVisibleProperties&)_propVisibleProp.getValueObj()),
_scaleFactors(_propScaleFactors.getValueDblArray())
{
	// NULL STATES
	setNull();

	// MEMBER VARIABLES
	setType("rdVisibleObject");
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
rdVisibleObject::rdVisibleObject(const string &aFileName):
rdObject(aFileName),
_geometryFileNames(_propGeometryFileNames.getValueStrArray()),
_propVisibleProp(rdPropertyObj("VisibleProperties", rdVisibleProperties())),
_visibleProp((rdVisibleProperties&)_propVisibleProp.getValueObj()),
_scaleFactors(_propScaleFactors.getValueDblArray())
{
	// NULL STATES
	setNull();

	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Construct an object from an DOMElement.
 */
rdVisibleObject::rdVisibleObject(DOMElement *aElement):
rdObject(aElement),
_geometryFileNames(_propGeometryFileNames.getValueStrArray()),
_propVisibleProp(rdPropertyObj("VisibleProperties", rdVisibleProperties())),
_visibleProp((rdVisibleProperties&)_propVisibleProp.getValueObj()),
_scaleFactors(_propScaleFactors.getValueDblArray())
{
	// NULL STATES
	setNull();

	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * Copy constructors for all rdVisibleObject's only copy the non-XML variable
 * members of the object; that is, the object's DOMnode and rdXMLDocument
 * are not copied but set to NULL.  The reason for this is that for the
 * object and all its derived classes to establish the correct connection
 * to the XML document nodes, the the object would need to reconstruct based
 * on the XML document not the values of the object's member variables.
 *
 * There are three proper ways to generate an XML document for an rdVisibleObject:
 *
 * 1) Construction based on XML file (@see rdVisibleObject(const char *aFileName)).
 * In this case, the XML document is created by parsing the XML file.
 *
 * 2) Construction by rdVisibleObject(const rdXMLDocument *aDocument).
 * This constructor explictly requests construction based on an
 * XML document.  In this way the proper connection between an object's node
 * and the corresponding node within the XML document is established.
 * This constructor is a copy constructor of sorts because all essential
 * rdVisibleObject member variables should be held within the XML document.
 * The advantage of this style of construction is that nodes
 * within the XML document, such as comments that may not have any
 * associated rdVisibleObject member variable, are preserved.
 *
 * 3) A call to generateDocument().
 * This method generates an XML document for the rdVisibleObject from scratch.
 * Only the essential document nodes are created (that is, nodes that
 * correspond directly to member variables.).
 *
 * @param aObject Object to be copied.
 * @see rdVisibleObject(const rdXMLDocument *aDocument)
 * @see rdVisibleObject(const char *aFileName)
 * @see generateDocument()
 */
rdVisibleObject::rdVisibleObject(const rdVisibleObject &aObject):
rdObject(aObject),
_geometryFileNames(_propGeometryFileNames.getValueStrArray()),
_propVisibleProp(rdPropertyObj("VisibleProperties", rdVisibleProperties())),
_visibleProp((rdVisibleProperties&)_propVisibleProp.getValueObj()),
_scaleFactors(_propScaleFactors.getValueDblArray())
{
	// NULL MEMBER VARIABLES
	setNull();

	// COPY TYPE AND NAME
	*this = aObject;
}


//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Set all member variables to their null or default values.
 */
void rdVisibleObject::
setNull()
{
	setupProperties();
}
/**
 * virtual copy constructor
 */
rdObject* rdVisibleObject::
copy() const
{

	rdVisibleObject *object = new rdVisibleObject(*this);
	return(object);
}
/**
 * virtual copy constructor from DOMElement
 */

rdObject* rdVisibleObject::
copy(DOMElement *aElement) const
{
	rdVisibleObject *object = new rdVisibleObject(aElement);
	*object = *this;
	object->updateFromXMLNode();
	return(object);
}
//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void rdVisibleObject::setupProperties()
{

	_propertySet.append(&_propGeometryFileNames);
	_propGeometryFileNames.setName("GeometryFiles");

	_propertySet.append(&_propVisibleProp);
	_propVisibleProp.setName("VisibleProperties");

	rdArray<double> unit3(1.0, 3);
	_propertySet.append(&_propScaleFactors);
	_propScaleFactors.setName("ScaleFactors");
	_propScaleFactors.setValue(unit3);
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
rdVisibleObject& rdVisibleObject::
operator=(const rdVisibleObject &aObject)
{
	// BASE CLASS
	rdObject::operator=(aObject);

	setNumGeometryFiles(aObject.getNumGeometryFiles());
	for(int i=0; i < aObject.getNumGeometryFiles(); i++)
		setGeometryFileName(i, aObject.getGeometryFileName(i));

	_transform = aObject._transform;
	_visibleProp = aObject._visibleProp;

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
bool rdVisibleObject::
operator==(const rdVisibleObject &aObject)
{
	return(rdObject::operator==(aObject));
}


//=============================================================================
// GET AND SET
//=============================================================================
//------------- Geometry files mgmt. -------------------------------------------
/**
 * set the number of geometry files associated with visible object
 */
void rdVisibleObject::
setNumGeometryFiles(int n)
{
	_geometryFileNames.setSize(n);
}
/**
 * Get the number of geometry files associated with visible object
 */
const int rdVisibleObject::
getNumGeometryFiles() const
{
	return (_geometryFileNames.getSize());
}
/**
 * set the name of ith geometry files associated with visible object
 */
void rdVisibleObject::
setGeometryFileName(int i, const string &aGeometryFileName)
{
	_geometryFileNames.set(i,aGeometryFileName);
}
/**
 * Get the name of ith geometry files associated with visible object
 */

const char *rdVisibleObject::
getGeometryFileName(int i) const
{
	return _geometryFileNames[i].c_str();
}

/**
 * set the visible properties of a visible object
 */
//------------- Properties: Shading, Color, etc. -------------------------------
void rdVisibleObject::
setVisibleProperties(const rdVisibleProperties &aVisibleProperties)
{
	_visibleProp = aVisibleProperties;
}
/**
 * Retrieve the visible properties of a visible object
 */
rdVisibleProperties& rdVisibleObject::
getVisibleProperties()
{
	return (_visibleProp);
}
//_____________________________________________________________________________
/**
 * Set Scale factors for geometry.
 *
 */
void rdVisibleObject::
setScaleFactors(const double aScaleFactors[3])
{
	for(int i=0; i < 3; i++)
		_scaleFactors[i]=(aScaleFactors[i]);
}
//_____________________________________________________________________________
/**
 * Get Scale factors for geometry.
 *
 */
void rdVisibleObject::
getScaleFactors(double aScaleFactors[3]) const
{
	for(int i=0; i < 3; i++)
		aScaleFactors[i] = _scaleFactors[i];
}
//------------- Transform -----------------------------------------------------
/**
 * Set the transform of a visible object
 */
void rdVisibleObject::
setTransform(const rdTransform &aTransform)
{
	_transform = aTransform;
	setChanged();
}
/**
 * Retrieve the transform of a visible object
 */

rdTransform& rdVisibleObject::
getTransform() 
{
	return _transform;
}
//------------- Transform -----------------------------------------------------
// More interfaces for transform as other interfaces (Angles based) are needed
// Rotations in Radians
// three rotation angles, assumed order XYZ
/**
 * Rotate a visible object by 3 angles in radians around XYZ in order
 */
void rdVisibleObject::
rotateRadians(const double rR[3])
{
	getTransform().rotate(rR, rdTransform::Radians, rdTransform::XYZ);
}

/**
 * Rotate a visible object by 3 angles in radians with user specified order
 */
void rdVisibleObject::
rotateRadians(const double rR[3], const rdTransform::RotationOrder order)
{
	getTransform().rotate(rR, rdTransform::Radians, order);
}
/**
 * Rotate a visible object by an angle in radians around X axis
 */
void rdVisibleObject::
rotateRadiansX(const double rR)
{
	getTransform().rotateX(rR, rdTransform::Radians);
}
/**
 * Rotate a visible object by an angle in radians around Y axis
 */
void rdVisibleObject::
rotateRadiansY(const double rR)
{
	getTransform().rotateY(rR, rdTransform::Radians);
}
/**
 * Rotate a visible object by an angle in radians around Z axis
 */
void rdVisibleObject::
rotateRadiansZ(const double rR)
{
	getTransform().rotateZ(rR, rdTransform::Radians);
}
/**
 * Rotate a visible object by an angle in radians around an axis
 */
void rdVisibleObject::
rotateRadiansAxis(const double rR, const double axis[3])
{
	getTransform().rotateAxis(rR, rdTransform::Radians, axis);
}

/**
 * Rotate a visible object by three euler angle in degrees around in XYZ order
 */

void rdVisibleObject::
rotateDegrees(const double rD[3])
{
	getTransform().rotate(rD, rdTransform::Degrees, rdTransform::XYZ);
}
/**
 * Rotate a visible object by three euler angle in degrees around in specified order
 */
void rdVisibleObject::
rotateDegrees(const double rD[3], const rdTransform::RotationOrder order)
{
	getTransform().rotate(rD, rdTransform::Degrees, order);
}
/**
 * Rotate a visible object by an angle in degrees around X axis
 */
void rdVisibleObject::
rotateDegreesX(const double rD)
{
	getTransform().rotateX(rD, rdTransform::Degrees);
}
/**
 * Rotate a visible object by an angle in degrees around Y axis
 */
void rdVisibleObject::
rotateDegreesY(const double rD)
{
	getTransform().rotateY(rD, rdTransform::Degrees);
}
/**
 * Rotate a visible object by an angle in degrees around Z axis
 */
void rdVisibleObject::
rotateDegreesZ(const double rD)
{
	getTransform().rotateZ(rD, rdTransform::Degrees);
}
/**
 * Rotate a visible object by an angle in degrees around an axis
 */
void rdVisibleObject::
rotateDegreesAxis(const double rD, const double axis[3])
{
	getTransform().rotateAxis(rD, rdTransform::Degrees, axis);
}
/**
 * Translate a visible object by a translation vector
 */
void rdVisibleObject::
translate(const double t[3])
{
	getTransform().translate(t);
}


