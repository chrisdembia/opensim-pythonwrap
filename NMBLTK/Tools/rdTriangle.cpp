// rdTriangle.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2002 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "rdMath.h"
#include "rdMtx.h"
#include "rdTriangle.h"
#include "rdPlane.h"
#include "rdMemory.h"


//=============================================================================
// STATIC VARIABLES
//=============================================================================


//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
rdTriangle::~rdTriangle()
{
	int i;
	for(i=0;i<3;i++) {
		if(_v3dNames[i]!=NULL) { delete[] _v3dNames[i];  _v3dNames[i]=NULL; }
	}
}

//_____________________________________________________________________________
/**
 * Construct an empty graphics model.
 */
rdTriangle::rdTriangle()
{
	setNull();

	// TYPE
	setType("rdTriangle");
}

//_____________________________________________________________________________
/**
 * Construct a graphics model from an XML Element.
 *
 * @param aElement XML element.
 */
rdTriangle::rdTriangle(DOMElement *aElement) :
	rdObject(aElement)
{
	setNull();
	updateData();
}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set NULL values for all member variables.
 */
void rdTriangle::
setNull()
{
	_verts = NULL;
	_v3dNames[0] = _v3dNames[1] = _v3dNames[2] = NULL;
	_v3dIndex[0] = _v3dIndex[1] = _v3dIndex[2] = 0;
}



//=============================================================================
// SET / GET
//=============================================================================
//-----------------------------------------------------------------------------
// VERTICES
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the vertices for this triangle.
 *
 * @param aVertices Vertices to which this triangle points.
 */
void rdTriangle::
setVertices(rdVertices *aVertices)
{
	_verts = aVertices;
}
//_____________________________________________________________________________
/**
 * Get the vertices for this triangle.
 *
 * @return Vertices to which this triangle points.
 */
rdVertices* rdTriangle::
getVertices()
{
	return(_verts);
}

//-----------------------------------------------------------------------------
// VERTEX
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get a specified vertex of the triangle.
 *
 * @param aWhich Which vertex- 0, 1, or 2.
 * @param rV Vertex.
 * @return -1 on error; 0 otherwise.  If an error is encountered the values
 * returned in rV are undefined.
 */
int rdTriangle::
getVertex(int aWhich,double rV[3]) const
{
	if(rV==NULL) return(-1);
	if((aWhich<0)||(aWhich>=3)) {
		printf("rdTriangle.getVertex: ERROR- vertex index out of bounds.\n");
		return(-1);
	}

	// GET VERTICES
	rdV3D *v3d = _verts->getVertex(_v3dIndex[aWhich]);
	if(v3d==NULL) {
		printf("rdTriangle.getVertex: ERROR- null vertex.\n");
		return(-1);
	}
	v3d->getVertex(rV);

	return(0);
}

//-----------------------------------------------------------------------------
// INDICES
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the index of a vertex.
 *
 * @param aWhich Which vertex index to get- 0, 1, or 2.
 * @return Vertiex index.
 */
int rdTriangle::
getVertexIndex(int aWhich) const
{
	if((aWhich<0)||(aWhich>=3)) return(0);
	return(_v3dIndex[aWhich]);
}


//=============================================================================
// UTILITIES
//=============================================================================
//-----------------------------------------------------------------------------
// BOUNDS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Compute the lower bounds of this triangle.
 *
 * @param rLower Lower bounds.
 */
void rdTriangle::
computeLowerBounds(double rLower[3]) const
{
	// 0
	int i;
	double v[3];
	getVertex(0,rLower);

	// 1
	getVertex(1,v);
	for(i=0;i<3;i++) {
		if(v[i]<rLower[i])  rLower[i] = v[i];
	}

	// 2
	getVertex(2,v);
	for(i=0;i<3;i++) {
		if(v[i]<rLower[i])  rLower[i] = v[i];
	}
}
//_____________________________________________________________________________
/**
 * Compute the upper bounds of this triangle.
 *
 * @param rUpper Upper bounds.
 */
void rdTriangle::
computeUpperBounds(double rUpper[3]) const
{
	// 0
	int i;
	double v[3];
	getVertex(0,rUpper);

	// 1
	getVertex(1,v);
	for(i=0;i<3;i++) {
		if(v[i]>rUpper[i])  rUpper[i] = v[i];
	}

	// 2
	getVertex(2,v);
	for(i=0;i<3;i++) {
		if(v[i]>rUpper[i])  rUpper[i] = v[i];
	}
}

//-----------------------------------------------------------------------------
// INTERSECTION
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Compute how a point intersects this triangle.  It is assumed that
 * the point lies in the plane of the triangle.
 *
 * The following types of intersections are possible:
 *		1) NONE
 *		2) POINT_INTERIOR
 *		3) POINT_VERTEX0
 *		4) POINT_VERTEX1
 *		5) POINT_VERTEX2
 *		6) POINT_EDGE01
 *		7) POINT_EDGE12
 *		8) POINT_EDGE20
 *
 * @param aP Point in question.
 * @return Intersection type (@see INTERSECTION).
 */
rdTriangle::INTERSECTION rdTriangle::
computeIntersection(const double aP[3]) const
{
	// BOUNDS
	int i;
	double lower[3],upper[3];
	computeLowerBounds(lower);
	computeUpperBounds(upper);
	for(i=0;i<3;i++) {
		if((aP[i]<(lower[i]-rdMath::ZERO)) || (aP[i]>(upper[i]+rdMath::ZERO))) {
			//printf("rdTriangle.computeIntersection(aPoint): out of bounds\n");
			return(NONE);
		}
	}

	// VERTEX INTERSECTION
	double v0[3],v1[3],v2[3];
	getVertex(0,v0);
	if((aP[0]==v0[0]) && (aP[1]==v0[1]) && (aP[2]==v0[2])) return(POINT_VERTEX0);
	getVertex(1,v1);
	if((aP[0]==v1[0]) && (aP[1]==v1[1]) && (aP[2]==v1[2])) return(POINT_VERTEX1);
	getVertex(2,v2);
	if((aP[0]==v2[0]) && (aP[1]==v2[1]) && (aP[2]==v2[2])) return(POINT_VERTEX2);

	// COMPUTE TRIANGLE NORMAL
	double n[3];
	double r01[3],r12[3],r20[3];
	rdMtx::Subtract(1,3,v1,v0,r01);
	rdMtx::Subtract(1,3,v2,v1,r12);
	rdMtx::CrossProduct(r01,r12,n);
	double length = rdMtx::Normalize(3,n,n);
	if(length==0.0) {
		//printf("rdTriangle.computeIntersection(aPoint): ERROR- no normal.\n");
		return(NONE);
	}

	// EDGE01
	double rp[3],np[3];
	rdMtx::Subtract(1,3,aP,v0,rp);
	rdMtx::CrossProduct(r01,rp,np);
	length = rdMtx::DotProduct(3,n,np);
	if(length<0.0) {
		//printf("rdTriangle.computeIntersection(aPoint): outside edge01\n");
		return(NONE);
	}
	else if(length==0.0) return(POINT_EDGE01);

	// EDGE12
	rdMtx::Subtract(1,3,aP,v1,rp);
	rdMtx::CrossProduct(r12,rp,np);
	length = rdMtx::DotProduct(3,n,np);
	if(length<0.0) {
		//printf("rdTriangle.computeIntersection(aPoint): outside edge12\n");
		return(NONE);
	}
	else if(length==0.0) return(POINT_EDGE12);

	// EDGE20
	rdMtx::Subtract(1,3,v0,v2,r20);
	rdMtx::Subtract(1,3,aP,v2,rp);
	rdMtx::CrossProduct(r20,rp,np);
	length = rdMtx::DotProduct(3,n,np);
	if(length<0.0) {
		//printf("rdTriangle.computeIntersection(aPoint): outside edge20\n");
		return(NONE);
	}
	else if(length==0.0) return(POINT_EDGE20);

	return(POINT_INTERIOR);
}
//_____________________________________________________________________________
/**
 * Compute the intersection of a specified line and this triangle.
 *
 * The following types of intersections are possible:
 *		1) NONE
 *		2) POINT_INTERIOR
 *		3) POINT_VERTEX0
 *		4) POINT_VERTEX1
 *		5) POINT_VERTEX2
 *		6) POINT_EDGE01
 *		7) POINT_EDGE12
 *		8) POINT_EDGE20
 *		9) LINE_INTERIOR
 *		10) LINE_VERTEX0
 *		11) LINE_VERTEX1
 *		12) LINE_VERTEX2
 *		13) LINE_EDGE01
 *		14) LINE_EDGE12
 *		15) LINE_EDGE20
 *
 * If there is a point intersection, the value of this intersection point
 * is returned in rP1.
 *
 * If there is a line intersection, the first point of the line segment is
 * returned in rP1 and the second point of the line segment is returned
 * in rP2.
 *
 * @param aLine Line for which to compute the intersection.
 * @param rP1 First point of intersection.  If there is no intersection,
 * the value returned in rP1 is meaningless.
 * @param rP2 Second point of intersection.  If the intersection is not a line,
 * the value returned in rP2 is meaningless.
 * @return Intersection type (@see INTERSECTION).
 */
rdTriangle::INTERSECTION rdTriangle::
computeIntersection(const rdLine *aLine,double rP1[3],double rP2[3]) const
{
	if(aLine==NULL) return(NONE);
	if(_verts==NULL) return(NONE);

	// GET VERTICES
	int error;
	double v0[3],v1[3],v2[3];
	error = getVertex(0,v0);  if(error) return(NONE);
	error = getVertex(1,v1);  if(error) return(NONE);
	error = getVertex(2,v2);  if(error) return(NONE);

	// CONSTRUCT A PLANE FROM THIS TRIANGLE
	rdPlane plane(v0[0],v0[1],v0[2],v1[0],v1[1],v1[2],v2[0],v2[1],v2[2]);

	// INTERSECT LINE WITH PLANE
	int type = plane.computeIntersection(aLine,rP1);

	// NO INTERSECTION WITH PLANE
	if(type==-1) return(NONE);

	// POINT INTERSECTION WITH PLANE
	if(type==0) {
		return(computeIntersection(rP1));
	}

	// LINE INTERSECTION WITH PLANE
	if(type==1) {
		printf("rdTriangle.computeIntersection(rdLine): WARN- line intersection ");
		printf("not currently handled.\n");
	}
	
	return(NONE);
}

//-----------------------------------------------------------------------------
// Indices
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Update the triangle indices based on the names of the vertices.
 */
void rdTriangle::
updateIndicies()
{
	if(_verts==NULL) return;

	// VARIABLES
	int i,v;
	rdV3D *v3d;

	// LOOP THROUGH TRIANGLE INDICES
	for(i=0;i<3;i++) {

		// INITIALIZE
		_v3dIndex[i] = 0;

		// LOOP THROUGH 
		for(v=0;v<_verts->getFirstEmpty();v++) {

			// GET VERTEX
			v3d = _verts->getVertex(v);
			if(v3d==NULL) continue;

			// COMPARE NAME
			if(strcmp(v3d->getName(),_v3dNames[i]) == 0) {
				_v3dIndex[i] = v;
				break;
			}
		}
	}
}


//=============================================================================
// XML
//=============================================================================
//-----------------------------------------------------------------------------
// UPDATE OBJECT
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Update this object based on its XML node.
 *
 * @param aDeep If true, update this object and all its child objects
 * (that is, member variables that are rdObject's); if false, update only
 * the member variables that are not rdObject's.
 */
void rdTriangle::
updateObject(bool aDeep)
{
	if(_node==NULL) return;

	// BASE CLASS
	rdObject::updateObject(aDeep);

	// MEMBER DATA
	updateData();

	// MEMBER OBJECTS

}
//_____________________________________________________________________________
/**
 * Update the member data of this object based on its XML node.  Member
 * objects (children) are not updated.
 */
void rdTriangle::
updateData()
{
	if(_node==NULL) return;

	// GET DATA
	char **data;
	int n = rdXMLNode::GetStrArray(_node,data);
	if(data==NULL) {
		printf("rdTriangle(aElement): ERROR- no data.\n");
		return;
	}
	if(n!=3) {
		printf("rdTriangle(aElement): ERROR- has %d vertices.\n",n);
		rdMemory::DeleteArrayOfStrings(n,data);
		return;
	}

	// ASSIGN
	int i;
	for(i=0;i<3;i++) {
		_v3dNames[i] = data[i];
	}

	// CLEANUP
	delete[] data;
}

//-----------------------------------------------------------------------------
// UPDATE NODE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Update the XML node representing this object.
 *
 * @param aDeep If true, update the XML node of this object AND the XML nodes
 * of all class members that are rdObjects (child nodes);  if false, update
 * only the XML node of this object without updating the XML nodes of its
 * children.
 */
void rdTriangle::
updateNode(bool aDeep)
{
	// BASE CLASS
	rdObject::updateNode();

	// CHECK FOR NULL NODE
	DOMNode *node = getNode();
	if(node==NULL) return;

	// TRIANGLE
	rdXMLNode::SetStrArray(node,3,&_v3dNames[0]);
}


