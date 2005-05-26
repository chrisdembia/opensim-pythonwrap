// rdGBody.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2002 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdGBody_h__
#define __rdGBody_h__


// INCLUDES
#include "rdTools.h"
#include "rdObject.h"
#include "rdVertices.h"
#include "rdEdges.h"
#include "rdTriangles.h"


// DECLARATIONS
class rdGBodies;


//=============================================================================
//=============================================================================
/**
 * A graphical body.
 */
class RDTOOLS_API rdGBody : public rdObject
{
//=============================================================================
// DATA
//=============================================================================
private:
	/** Origin of the coordinate system for the body. */
	double _origin[3];
	/** X axis of the body. */
	double _x[3];
	/** Y axis of the body. */
	double _y[3];
	/** Z axis of the body. */
	double _z[3];
	/** The unit vector directed from the origin to px is the desired
	x axis. */
	double _px[3];
	/** The unit vector directed from the origin to py is the desired
	y axis. */
	double _py[3];
	/** The unit vector directed from the origin to pz is the desired
	z axis. */
	double _pz[3];
	/** List of vertices. */
	rdVertices *_vertices;
	/** List of edges. */
	rdEdges *_edges;
	/** List of triangles. */
	rdTriangles *_triangles;
	/** List of child bodies. */
	rdGBodies *_bodies;
	/** Lower bounds. */
	double _lower[3];
	/** Upper bounds. */
	double _upper[3];
	// INERTIAL PROPERTIES
	/** Density. */
	double _density;
	/** Mass. */
	double _mass;
	/** Center of mass. */
	double _com[3];
	/** Inertia tensor. */
	double _inertia[3][3];

//=============================================================================
// METHODS
//=============================================================================
public:
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
	rdGBody();
	rdGBody(DOMElement *aElement);
	virtual ~rdGBody();
private:
	void setNull();

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
public:
	void setOrigin(double aX,double aY,double aZ);
	void getOrigin(double rP[3]) const;
	void setPX(double aX,double aY,double aZ);
	void setPY(double aX,double aY,double aZ);
	void setPZ(double aX,double aY,double aZ);
	void setDensity(double aDensity);
	double getDensity() const;
	void setMass(double aMass);
	double getMass() const;
	void setCenterOfMass(const double aCOM[3]);
	void getCenterOfMass(double rCOM[3]) const;
	void setInertiaTensor(const double aI[6]);
	void getInertiaTensor(double rI[9]) const;

	//--------------------------------------------------------------------------
	// OPERATIONS
	//--------------------------------------------------------------------------
	void translate(double aX,double aY,double aZ);
	void rotate(int aXYZ,double aRadians);
	void rotate(int aXYZ,double aRadians,const double aP[3]);

	//--------------------------------------------------------------------------
	// UTILITIES
	//--------------------------------------------------------------------------
	bool isInside(const double aPoint[3]) const;
	void estimateInertialProperties(double aCubeSize=0.0);
	void computeNewFrame();
	void updateEdgeIndices();
	void updateTriangleIndices();
	void computeUpperBounds();
	void computeLowerBounds();
	void computeBounds();
	void printBoneFile(const char *aFileName=NULL);

	//--------------------------------------------------------------------------
	// XML
	//--------------------------------------------------------------------------
	virtual void updateObject(bool aDeep=true);
	virtual void updateNode(bool aDeep=true);
	void updateData();

//=============================================================================
};	// END class rdGBody
//=============================================================================
//=============================================================================

#endif  // __rdGBody_h__
