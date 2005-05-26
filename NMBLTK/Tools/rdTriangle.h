// rdTriangle.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2002 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdTriangle_h__
#define __rdTriangle_h__

// INCLUDES
#include "rdTools.h"
#include "rdObject.h"
#include "rdLine.h"
#include "rdVertices.h"

//=============================================================================
//=============================================================================
/**
 * A graphical body.
 */
class RDTOOLS_API rdTriangle : public rdObject
{
//=============================================================================
// DATA
//=============================================================================
public:
	enum INTERSECTION { NONE=0,
		POINT_INTERIOR,
		POINT_VERTEX0,POINT_VERTEX1,POINT_VERTEX2,
		POINT_EDGE01,POINT_EDGE12,POINT_EDGE20,
		LINE_INTERIOR,
		LINE_VERTEX0,LINE_VERTEX1,LINE_VERTEX2,
		LINE_EDGE01,LINE_EDGE12,LINE_EDGE20 };
private:
	rdVertices *_verts;
	char* _v3dNames[3];
	int	_v3dIndex[3];

//=============================================================================
// METHODS
//=============================================================================
public:
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
	rdTriangle();
	rdTriangle(DOMElement *aElement);
	virtual ~rdTriangle();
private:
	void setNull();

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
public:
	void setVertices(rdVertices *aVertices);
	rdVertices* getVertices();
	int getVertex(int aWhich,double rV[3]) const;
	int getVertexIndex(int aWhich) const;

	//--------------------------------------------------------------------------
	// UTILITIES
	//--------------------------------------------------------------------------
	void computeLowerBounds(double rLower[3]) const;
	void computeUpperBounds(double rUpper[3]) const;
	INTERSECTION
		computeIntersection(const rdLine *aLine,double rP1[3],double rP2[3])
		const;
	INTERSECTION
		computeIntersection(const double aP[3]) const;
	void
		updateIndicies();

	//--------------------------------------------------------------------------
	// XML
	//--------------------------------------------------------------------------
	virtual void updateObject(bool aDeep=true);
	virtual void updateNode(bool aDeep=true);
	void updateData();

//=============================================================================
};	// END class rdTriangle
//=============================================================================
//=============================================================================

#endif  // __rdTriangle_h__
