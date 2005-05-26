// rdVisibleObject.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2004 Stanford University
// All rights reserved.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdVisibleObject_h__
#define __rdVisibleObject_h__


// INCLUDES
#include "rdToolsDLL.h"
#include "rdObject.h"
#include "rdTransform.h"
#include "rdVisibleProperties.h"
#include "rdPropertyStrArray.h"
#include "rdPropertyObj.h"
#include "rdPropertyDblArray.h"

class rdXMLNode;
class rdXMLDocument;


// CONSTANTS

//=============================================================================
//=============================================================================
/**
 * Class rdVisibleObject is intended to be used as the base class for all
 * Visible objects that subclass rdObject.  It provides a common object from which
 * to derive and also some basic functionality, such as maintaining geometry
 *
 * @version 1.0
 * @author Ayman Habib
 */
class RDTOOLS_API rdVisibleObject: public rdObject
{

//=============================================================================
// DATA
//=============================================================================
public:
private:
	// PROPERTIES
	/** Name of geometry file name(s) */
	rdPropertyStrArray	_propGeometryFileNames;
	/** Object that represents shading, material, colors */
	rdPropertyObj		_propVisibleProp;
	/** Scale factors for geometry */
	rdPropertyDblArray	_propScaleFactors;

	// REFERENCES
	rdArray<std::string>&	_geometryFileNames;	
	rdVisibleProperties&	_visibleProp;
	rdArray<double>&		_scaleFactors;

	/** transform relative to global frame. unserialized */
	rdTransform			_transform;
protected:

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdVisibleObject();
	rdVisibleObject(const std::string &aFileName);
	rdVisibleObject(DOMElement *aNode);
	rdVisibleObject(const rdVisibleObject &aVisibleObject);
	virtual ~rdVisibleObject();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;
private:
	void setNull();

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
#ifndef SWIG
	rdVisibleObject& operator=(const rdVisibleObject &aObject);
	virtual bool operator==(const rdVisibleObject &aObject);
#endif
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
public:
	void setNumGeometryFiles(int n);
	void setGeometryFileName(int i, const std::string &aGeometryFileName);
	const int getNumGeometryFiles() const;
	const char *getGeometryFileName(int i) const;

	void setVisibleProperties(const rdVisibleProperties &aVisibleProperties);
	rdVisibleProperties& getVisibleProperties();

	void setTransform(const rdTransform &aTransform);
	virtual rdTransform& getTransform();

	void setScaleFactors(const double aScaleFactors[3]);
	void getScaleFactors(double aScaleFactors[3]) const;

	// More interfaces for transform as other interfaces (Angles based) are needed
	void rotateRadians(const double rR[3]);
	void rotateRadians(const double rR[3], const rdTransform::RotationOrder order);
	void rotateRadiansX(const double rR);
	void rotateRadiansY(const double rR);
	void rotateRadiansZ(const double rR);
	void rotateRadiansAxis(const double rR, const double axis[3]);
	void rotateDegrees(const double rR[3]);
	void rotateDegrees(const double rR[3], const rdTransform::RotationOrder order);
	void rotateDegreesX(const double rR);
	void rotateDegreesY(const double rR);
	void rotateDegreesZ(const double rR);
	void rotateDegreesAxis(const double rR, const double axis[3]);
	void translate(const double t[3]);

	//--------------------------------------------------------------------------
	// XML
	//--------------------------------------------------------------------------
	void setupProperties();
	
private:
	void generateDocument();


//=============================================================================
};	// END of class rdVisibleObject
//=============================================================================
//=============================================================================

#endif //__rdVisibleObject_h__
