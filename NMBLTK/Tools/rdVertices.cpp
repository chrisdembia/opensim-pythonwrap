// rdVertices.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2002 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// INCLUDES
#include "rdTools.h"
#include "rdIO.h"
#include "rdVertices.h"


//============================================================================
// DEFINES
//============================================================================


//============================================================================
// CONSTANTS
//============================================================================


//=============================================================================
// DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
rdVertices::~rdVertices()
{
	// VERTICES
	int i;
	rdV3D *v3d;
	for(i=0;i<getFirstEmpty();i++) {
		v3d = getVertex(i);
		if(v3d==NULL) continue;
		delete v3d;
	}
}


//=============================================================================
// CONSTRUCTOR(S)
//=============================================================================
//_____________________________________________________________________________
/**
 * Default constructor.
 */
rdVertices::rdVertices()
{
	// SET NULL STATES
	setNull();

	// TYPE
	setType("rdVertices");
}
//_____________________________________________________________________________
/**
 * Construct an rdVertices instance from an XML element.
 *
 * @param aElement XML element.
 */
rdVertices::rdVertices(DOMElement *aElement) :
	rdPtrArray(aElement)
{
	// SET NULL STATES
	setNull();
	if(_node==NULL) return;

	// GET rdV3D CHILD NODES
	XMLCh *name = XMLString::transcode("rdV3D");
	DOMNodeList *list = _node->getElementsByTagName(name);
	if(name!=NULL) delete[] name;

	// LOOP THROUGH CHILDREN
	DOMElement *elmt;
	rdV3D *v3d;
	unsigned int i;
	for(i=0;i<list->getLength();i++) {
		elmt = (DOMElement*)list->item(i);
		if(elmt==NULL) continue;
		v3d = new rdV3D(elmt);
		append(v3d);
	}
}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set all states to their null or default values.
 */
void rdVertices::
setNull()
{

}


//=============================================================================
// GET AND SET
//=============================================================================
//-----------------------------------------------------------------------------
// GET
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the vertex at a particular index.
 *
 * @param aIndex Array index of the desired vertex.
 * @see rdPtrArray::get()
 */
rdV3D* rdVertices::
getVertex(int aIndex)
{
	rdV3D *v3d = (rdV3D*)rdPtrArray::get(aIndex);
	return(v3d);
}


//=============================================================================
// OPERATIONS
//=============================================================================
//-----------------------------------------------------------------------------
// TRANSLATE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Translate the vertices by a specified amount.
 *
 * @param aX Amount to translate in the X direction.
 * @param aY Amount to translate in the Y direction.
 * @param aZ Amount to translate in the Z direction.
 */
void rdVertices::
translate(double aX,double aY,double aZ)
{
	int i;
	rdV3D *v3d;
	for(i=0;i<getFirstEmpty();i++) {
		v3d = getVertex(i);
		if(v3d==NULL) continue;
		v3d->translate(aX,aY,aZ);
	}
}

//-----------------------------------------------------------------------------
// ROTATE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Rotate a the vertices about the X, Y, or Z axis by a specified amount.
 *
 * @param aXYZ Specify whether to rotate about the X (aXYZ=0), Y (aXYZ=1),
 * or Z (aXYZ=2) axes.  If aXYZ is not 0, 1, or 2, no rotation is performed.
 * @param aRadians Amount of rotation in radians.
 */
void rdVertices::
rotate(int aXYZ,double aRadians)
{
	int i;
	rdV3D *v3d;
	for(i=0;i<getFirstEmpty();i++) {
		v3d = getVertex(i);
		if(v3d==NULL) continue;
		v3d->rotate(aXYZ,aRadians);
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
void rdVertices::
updateObject(bool aDeep)
{
	if(_node==NULL) return;

	// BASE CLASS
	rdPtrArray::updateObject(aDeep);

	// MEMBER DATA


	// VERTICES
	if(!aDeep) return;
	int i;
	rdV3D *v3d;
	for(i=0;i<getFirstEmpty();i++) {
		v3d = getVertex(i);
		if(v3d==NULL) continue;
		v3d->updateObject();
	}
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
void rdVertices::
updateNode(bool aDeep)
{
	// BASE CLASS
	rdPtrArray::updateNode();

	// DEEP?
	if(!aDeep) return;

	// VERTICES
	int i;
	rdV3D *v3d;
	for(i=0;i<getFirstEmpty();i++) {
		v3d = getVertex(i);
		if(v3d==NULL) continue;
		v3d->updateNode();
	}
}


