// rdTriangles.cpp
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
#include "rdTriangles.h"


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
rdTriangles::~rdTriangles()
{
	// TRIANGLES
	int i;
	rdTriangle *tri;
	for(i=0;i<getFirstEmpty();i++) {
		tri = getTriangle(i);
		if(tri==NULL) continue;
		delete tri;
	}
}


//=============================================================================
// CONSTRUCTOR(S)
//=============================================================================
//_____________________________________________________________________________
/**
 * Default constructor.
 */
rdTriangles::rdTriangles()
{
	// SET NULL STATES
	setNull();

	// TYPE
	setType("rdTriangles");
}
//_____________________________________________________________________________
/**
 * Construct an rdTriangles instance from an XML element.
 *
 * @param aElement XML element.
 */
rdTriangles::rdTriangles(DOMElement *aElement) :
	rdPtrArray(aElement)
{
	// SET NULL STATES
	setNull();
	if(aElement==NULL) return;

	// CHECK TYPE
	const char *type = getType();
	if(strcmp(type,"rdTriangles")!=0) {
		printf("rdTriangles(aElement): ERROR- wrong document type!\n");
		printf("\tDocument is of type %s.\n",type);
	}

	// GET rdTriangle CHILD NODES
	XMLCh *name = XMLString::transcode("rdTriangle");
	DOMNodeList *list = aElement->getElementsByTagName(name);
	if(name!=NULL) delete[] name;

	// LOOP THROUGH CHILDREN
	DOMElement *elmt;
	rdTriangle *tri;
	unsigned int i;
	for(i=0;i<list->getLength();i++) {
		elmt = (DOMElement*)list->item(i);
		if(elmt==NULL) continue;
		tri = new rdTriangle(elmt);
		append(tri);
	}
}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set all states to their null or default values.
 */
void rdTriangles::
setNull()
{

}


//=============================================================================
// GET AND SET
//=============================================================================
//-----------------------------------------------------------------------------
// VERTICES
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the vertices for all triangles.
 *
 * @param aVertices Vertices.
 */
void rdTriangles::
setVertices(rdVertices *aVertices)
{
	int i;
	rdTriangle *tri;
	for(i=0;i<getFirstEmpty();i++) {

		tri = getTriangle(i);
		if(tri==NULL) continue;

		tri->setVertices(aVertices);
	}
}

//-----------------------------------------------------------------------------
// TRIANGLE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the triangle at a particular index.
 *
 * @param aIndex Array index of the desired triangle.
 * @see rdPtrArray::get()
 */
rdTriangle* rdTriangles::
getTriangle(int aIndex)
{
	rdTriangle *tri = (rdTriangle*)rdPtrArray::get(aIndex);
	return(tri);
}


//=============================================================================
// OPERATIONS
//=============================================================================
//-----------------------------------------------------------------------------
// INDICES
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Update the indices of all triangles.
 *
 * @param aVerts List of vertices.
 * @see rdTriangle::updateIndices()
 */
void rdTriangles::
updateIndices()
{
	rdTriangle *tri;
	int i;
	for(i=0;i<getFirstEmpty();i++) {
		tri = getTriangle(i);
		if(tri==NULL) continue;
		tri->updateIndicies();
	}
}


//=============================================================================
// DOCUMENT AND NODE
//=============================================================================
//_____________________________________________________________________________
/**
 * Update the XML node representing this object.
 *
 * @param aDeep If true, update the XML node of this object AND the XML nodes
 * of all class members that are rdObjects (child nodes);  if false, update
 * only the XML node of this object without updating the XML nodes of its
 * children.
 */
void rdTriangles::
updateNode(bool aDeep)
{
	// BASE CLASS
	rdPtrArray::updateNode();

	// DEEP?
	if(!aDeep) return;

	// TRIANGLES
	int i;
	rdTriangle *tri;
	for(i=0;i<getFirstEmpty();i++) {
		tri = getTriangle(i);
		if(tri==NULL) continue;
		tri->updateNode();
	}
}


