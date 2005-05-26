// rdEdges.cpp
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
#include "rdEdges.h"


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
rdEdges::~rdEdges()
{

}


//=============================================================================
// CONSTRUCTOR(S)
//=============================================================================
//_____________________________________________________________________________
/**
 * Default constructor.
 */
rdEdges::rdEdges()
{
	// SET NULL STATES
	setNull();

	// TYPE
	setType("rdEdges");
}
//_____________________________________________________________________________
/**
 * Construct an rdEdges instance from an XML element.
 *
 * @param aElement XML element.
 */
rdEdges::rdEdges(DOMElement *aElement) :
	rdPtrArray(aElement)
{
	// SET NULL STATES
	setNull();
	if(_node==NULL) return;

	// CHECK TYPE
	const char *type = getType();
	if(strcmp(type,"rdEdges")!=0) {
		printf("rdEdges(aElement): ERROR- wrong document type!\n");
		printf("\tDocument is of type %s.\n",type);
	}

	// GET rdEdge CHILD NODES
	XMLCh *name = XMLString::transcode("rdEdge");
	DOMNodeList *list = _node->getElementsByTagName(name);
	if(name!=NULL) delete[] name;

	// LOOP THROUGH CHILDREN
	DOMElement *elmt;
	rdEdge *edge;
	unsigned int i;
	for(i=0;i<list->getLength();i++) {
		elmt = (DOMElement*)list->item(i);
		if(elmt==NULL) continue;
		edge = new rdEdge(elmt);
		append(edge);
	}
}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set all member variables to their null or default values.
 */
void rdEdges::
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
 * Get the edge at a particular index.
 *
 * @param aIndex Array index of the desired edge.
 * @see rdPtrArray::get()
 */
rdEdge* rdEdges::
getEdge(int aIndex)
{
	rdEdge *edge = (rdEdge*)rdPtrArray::get(aIndex);
	return(edge);
}


//=============================================================================
// OPERATIONS
//=============================================================================
//-----------------------------------------------------------------------------
// INDICES
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Update the indices of all edgeangles.
 *
 * @param aVerts List of vertices.
 * @see rdEdge::updateIndices()
 */
void rdEdges::
updateIndices(rdVertices *aVerts)
{
	rdEdge *edge;
	int i;
	for(i=0;i<getFirstEmpty();i++) {
		edge = getEdge(i);
		if(edge==NULL) continue;
		edge->updateIndicies(aVerts);
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
void rdEdges::
updateObject(bool aDeep)
{
	if(_node==NULL) return;

	// BASE CLASS
	rdPtrArray::updateObject(aDeep);

	// EDGES
	if(!aDeep) return;
	int i;
	rdEdge *edge;
	for(i=0;i<getFirstEmpty();i++) {
		edge = getEdge(i);
		if(edge==NULL) continue;
		edge->updateObject();
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
void rdEdges::
updateNode(bool aDeep)
{
	// BASE CLASS
	rdPtrArray::updateNode();

	// EDGES
	if(!aDeep) return;
	int i;
	rdEdge *edge;
	for(i=0;i<getFirstEmpty();i++) {
		edge = getEdge(i);
		if(edge==NULL) continue;
		edge->updateNode();
	}
}


