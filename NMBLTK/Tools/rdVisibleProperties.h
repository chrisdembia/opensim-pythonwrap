// rdVisibleProperties.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2004 Stanford University
// All rights reserved.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdVisibleProperties_h__
#define __rdVisibleProperties_h__

#include "rdTools.h"
#include "rdObject.h"
#include "rdPropertyInt.h"
#include "rdPropertyBool.h"
#include "rdPropertyStr.h"

class rdXMLNode;
class rdXMLDocument;
class rdMaterial;

// CONSTANTS

//=============================================================================
//=============================================================================
/**
 * Class rdVisibleProperties is intended to contain all visible properties of an object
 * including Wireframe/Surface Shading-Quality,..
 *
 * @version 1.0
 * @author Ayman Habib
 */
class RDTOOLS_API rdVisibleProperties: public rdObject
{
public:
	enum  DisplayPreference {
			None=0,
			WireFrame=1,
			SolidFill=2,
			FlatShaded=3,
			GouraudShaded=4,
			PhongShaded=5,
			BoundingBox=6
	};

//=============================================================================
// DATA
//=============================================================================
private:
	// PROPERTIES
	/** DisplayPreference */
	rdPropertyInt	_propDisplayPreference;
	/** Whether to show normals when displaying the visible object */
	rdPropertyBool	_propShowNormals;
	/** Whether to show coordinate axes when displaying the visible object */
	rdPropertyBool	_propShowAxes;
	/** Name of the material assigned to this object */
	rdPropertyStr	_propMaterialName;

	// REFERENCES
	DisplayPreference&	_displayPreference;
	bool&				_showNormals;
	bool&				_showAxes;
	std::string&		_materialName;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdVisibleProperties();
	rdVisibleProperties(const std::string &aFileName);
	rdVisibleProperties(const rdXMLDocument *aDocument);
	rdVisibleProperties(DOMElement *aNode);
	rdVisibleProperties(const rdVisibleProperties &aVisibleProperties);
	virtual ~rdVisibleProperties();

	rdObject* copy() const;
	rdObject* copy(DOMElement *aElement) const;
	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
#ifndef SWIG
	rdVisibleProperties& operator=(const rdVisibleProperties &aVisibleProperties);
	bool operator==(const rdVisibleProperties &aObject);
#endif
private:
	void setNull();
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
public:
	void setDisplayPreference(const DisplayPreference aDisplayPreference);
	DisplayPreference getDisplayPreference() const;

	void setShowNormals(const bool showNormals);
	bool getShowNormals() const;

	void setShowAxes(const bool showAxes);
	bool getShowAxes() const;

	void setMaterialName(const char *matName);
	const char *getMaterialName() const;
	
private:
	const rdMaterial &getMaterial(const char *matName) const;
	//--------------------------------------------------------------------------
	// XML
	//--------------------------------------------------------------------------
	void setupProperties();
	void generateDocument();

//=============================================================================
};	// END of class rdVisibleProperties
//=============================================================================
//=============================================================================

#endif //__rdVisibleProperties_h__
