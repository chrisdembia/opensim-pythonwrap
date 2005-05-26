// rdV3D.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2002 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "rdMtx.h"
#include "rdV3D.h"


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
rdV3D::~rdV3D()
{
}

//_____________________________________________________________________________
/**
 * Default constructor.  By default, the value of the vertex is {0.0,0.0,0.0};
 */
rdV3D::rdV3D()
{
	setNull();

	// TYPE
	setType("rdV3D");
}

//_____________________________________________________________________________
/**
 * Construct a vertex with a specified value.
 *
 * @param aVertex Vertex to which to initialize this vertex.
 */
rdV3D::rdV3D(const double aVertex[3])
{
	setNull();

	// TYPE
	setType("rdV3D");

	// VERTEX
	setVertex(aVertex);
}

//_____________________________________________________________________________
/**
 * Construct a vertex from an XML Element.
 *
 * @param aElement XML element.
 */
rdV3D::rdV3D(DOMElement *aElement) :
	rdObject(aElement)
{
	setNull();

	// NODE
	updateData();
}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set NULL values for all member variables.
 */
void rdV3D::
setNull()
{
	_v3d[0] = _v3d[1] = _v3d[2] = 0.0;
}


//=============================================================================
// SET / GET
//=============================================================================
//-----------------------------------------------------------------------------
// VERTEX
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the XYZ coordinates of this vertex.
 *
 * @param aVertex Vertex.
 */
void rdV3D::
setVertex(const double aVertex[3])
{
	if(aVertex==NULL) return;
	int i;
	for(i=0;i<3;i++) {
		_v3d[i] = aVertex[i];
	}
}
//_____________________________________________________________________________
/**
 * Get the XYZ coordinates of this vertex.
 *
 * @param rVertex Array in which the coordinates are returned.
 */
void rdV3D::
getVertex(double rVertex[3]) const
{
	if(rVertex==NULL) return;
	int i;
	for(i=0;i<3;i++) {
		rVertex[i] = _v3d[i];
	}
}
//_____________________________________________________________________________
/**
 * Get the X coordinate of this vertex.
 *
 * @return X coordinate.
 */
double rdV3D::
getX() const
{
	return(_v3d[0]);
}
//_____________________________________________________________________________
/**
 * Get the Y coordinate of this vertex.
 *
 * @return Y coordinate.
 */
double rdV3D::
getY() const
{
	return(_v3d[1]);
}
//_____________________________________________________________________________
/**
 * Get the Z coordinate of this vertex.
 *
 * @return Z coordinate.
 */
double rdV3D::
getZ() const
{
	return(_v3d[2]);
}


//=============================================================================
// OPERATIONS
//=============================================================================
//-----------------------------------------------------------------------------
// TRANSLATE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Translate a the vertex by a specified amount.
 *
 * @param aX Amount to translate in the X direction.
 * @param aY Amount to translate in the Y direction.
 * @param aZ Amount to translate in the Z direction.
 */
void rdV3D::
translate(double aX,double aY,double aZ)
{
	rdMtx::Translate(aX,aY,aZ,_v3d,_v3d);
}

//-----------------------------------------------------------------------------
// ROTATE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Rotate a point about the X, Y, or Z axis by a specified amount.
 *
 * @param aXYZ Specify whether to rotate about the X (aXYZ=0), Y (aXYZ=1),
 * or Z (aXYZ=2) axes.  If aXYZ is not 0, 1, or 2, no rotation is performed.
 * @param aRadians Amount of rotation in radians.
 */
void rdV3D::
rotate(int aXYZ,double aRadians)
{
	rdMtx::Rotate(aXYZ,aRadians,_v3d,_v3d);
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
void rdV3D::
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
void rdV3D::
updateData()
{
	if(_node==NULL) return;

	// GET DATA
	double *data;
	int n = rdXMLNode::GetDblArray(_node,data);
	if(data==NULL) {
		printf("rdV3D(aElement): ERROR- no data.\n");
		return;
	}
	if(n<3) {
		printf("rdV3D(aElement): ERROR- has %d vertices. It should have 3.\n",n);
		delete[] data;
		return;
	}
	if(n>3) {
		printf("rdV3D(aElement): WARN- has %d vertices. It should have 3.\n",n);
	}

	// ASSIGN
	int i;
	for(i=0;i<3;i++) {
		_v3d[i] = data[i];
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
void rdV3D::
updateNode(bool aDeep)
{
	// BASE CLASS
	rdObject::updateNode();

	// CHECK FOR NULL NODE
	DOMNode *node = getNode();
	if(node==NULL) return;

	// V3D
	rdXMLNode::SetDblArray(node,3,_v3d);
}






