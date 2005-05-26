// rdMaterial.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2004 Stanford University
// All rights reserved.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdMaterial_h__
#define __rdMaterial_h__

#include "rdTools.h"
#include "rdObject.h"
#include "rdPropertyDbl.h"
#include "rdPropertyDblArray.h"
class rdXMLNode;
class rdXMLDocument;

//=============================================================================
//=============================================================================
/**
 * A class for representing the material properties of an object.
 *
 * @author Ayman Habib
 * @version 1.0
 */
class RDTOOLS_API rdMaterial: public rdObject
{
//=============================================================================
// DATA
//=============================================================================
public:
	/* serialized data members */
	// PROPERTIES
	/** Translucency. */
	rdPropertyDbl		_propTranslucency;
	/** Ambient color */
	rdPropertyDblArray  _propAmbientColor;
	/* Diffuse Color */
	rdPropertyDblArray _propDiffuseColor;
	/* Specular Color */
	rdPropertyDblArray _propSpecularColor;

	// REFERENCES
	double&					_translucency;
	rdArray<double>&		_ambientColor;
	rdArray<double>&		_diffuseColor;
	rdArray<double>&		_specularColor;

	// Could also include texture here.
	static rdMaterial *_defaultMaterial;
protected:

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdMaterial();
	rdMaterial(const std::string &aFileName);
	rdMaterial(DOMElement *aNode);
	rdMaterial(const rdMaterial &aMaterial);
	virtual ~rdMaterial();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;
private:
	void setNull();
protected:
	// Serialization support
	virtual void setupProperties();

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
#ifndef SWIG
	rdMaterial& operator=(const rdMaterial &aObject);
	virtual bool operator==(const rdMaterial &aObject);
#endif
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	void setTranslucency(const double aTranslucency);
	double getTranslucency() const;

	void setAmbientColor(const double aAmbientColor[3]);
	const double* getAmbientColor() const;

	void setDiffuseColor(const double aDiffuseColor[3]);
	const double* getDiffuseColor() const;

	void setSpecularColor(const double aSpecularColor[3]);
	const double* getSpecularColor() const;

	static const std::string& GetDefaultMaterialName();
	static const rdMaterial &GetDefaultMaterial();
	//--------------------------------------------------------------------------
	// XML
	//--------------------------------------------------------------------------
public:
	DOMElement* getNode() const;

private:
	void generateDocument();

//=============================================================================
};	// END of class rdMaterial
//=============================================================================
//=============================================================================

#endif //__rdMaterial_h__
