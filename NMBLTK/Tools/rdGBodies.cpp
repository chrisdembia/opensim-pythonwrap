// rdGBodies.cpp
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
#include "rdGBodies.h"


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
rdGBodies::~rdGBodies()
{
	// BODIES
	int i;
	rdGBody *bod;
	for(i=0;i<getFirstEmpty();i++) {
		bod = getBody(i);
		if(bod==NULL) continue;
		printf("rdGBodies.~rdGBodies: deleting body %d\n",i);
		delete bod;
	}

}


//=============================================================================
// CONSTRUCTOR(S)
//=============================================================================
//_____________________________________________________________________________
/**
 * Default constructor.
 */
rdGBodies::rdGBodies()
{
	// SET NULL STATES
	setNull();

	// TYPE
	setType("rdGBodies");
}
//_____________________________________________________________________________
/**
 * Construct an rdGBodies instance from an XML element.
 *
 * @param aElement XML element.
 */
rdGBodies::rdGBodies(DOMElement *aElement) :
	rdPtrArray(aElement)
{
	// SET NULL STATES
	setNull();
	if(aElement==NULL) return;

	// GET BODY NODES
	XMLCh *name = XMLString::transcode("rdGBody");
	DOMNodeList *list = aElement->getElementsByTagName(name);
	if(name!=NULL) delete[] name;

	// LOOP THROUGH CHILDREN
	DOMElement *elmt;
	rdGBody *bod;
	unsigned int i;
	for(i=0;i<list->getLength();i++) {
		elmt = (DOMElement*)list->item(i);
		if(elmt==NULL) continue;
		bod = new rdGBody(elmt);
		append(bod);
	}
}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set all states to their null or default values.
 */
void rdGBodies::
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
 * Get the graphics body at a particular index.
 *
 * @param aIndex Array index of the desired body.
 * @see rdPtrArray::get()
 */
rdGBody* rdGBodies::
getBody(int aIndex)
{
	rdGBody *bod = (rdGBody*)rdPtrArray::get(aIndex);
	return(bod);
}


//=============================================================================
// OPERATIONS
//=============================================================================
//-----------------------------------------------------------------------------
// BONE FILES
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Print SIMM-style bone files for all bodies.
 */
void rdGBodies::
printBoneFiles()
{
	int i;
	rdGBody *bod;
	for(i=0;i<getFirstEmpty();i++) {
		bod = getBody(i);
		if(bod==NULL) continue;
		bod->printBoneFile();
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
void rdGBodies::
updateObject(bool aDeep)
{
	if(_node==NULL) return;

	// BASE CLASS
	rdPtrArray::updateObject(aDeep);

	// MEMBER DATA


	// VERTICES
	if(!aDeep) return;
	int i;
	rdGBody *bod;
	for(i=0;i<getFirstEmpty();i++) {
		bod = getBody(i);
		if(bod==NULL) continue;
		bod->updateObject();
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
void rdGBodies::
updateNode(bool aDeep)
{
	// BASE CLASS
	rdPtrArray::updateNode();

	// DEEP?
	if(!aDeep) return;

	// BODIES
	int i;
	rdGBody *bod;
	for(i=0;i<getFirstEmpty();i++) {
		bod = getBody(i);
		if(bod==NULL) continue;
		bod->updateNode();
	}
}

