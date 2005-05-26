// rdGModel.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2002 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


#include "rdGModel.h"


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
rdGModel::~rdGModel()
{
	if(_bodies!=NULL) { delete _bodies;  _bodies=NULL; }
}

//_____________________________________________________________________________
/**
 * Construct an empty graphics model.
 */
rdGModel::rdGModel()
{
	setNull();

	// TYPE
	setType("rdGModel");
}

//_____________________________________________________________________________
/**
 * Construct a graphics model from file.
 *
 * @param aFileName File name.
 */
rdGModel::rdGModel(const char *aFileName) :
	rdObject(aFileName)
{
	setNull();

	// BODIES
	DOMElement *elmt;
	elmt = rdXMLNode::GetFirstChildElementByTagName(_node,"rdGBodies");
	if(elmt==NULL) {
		printf("rdGBody(aElement): ERROR- no bodies found.\n");
		return;
	}
	_bodies = new rdGBodies(elmt);
}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set NULL values for all member variables.
 */
void rdGModel::
setNull()
{
	_bodies = NULL;
}


//=============================================================================
// SET / GET
//=============================================================================
//-----------------------------------------------------------------------------
// BODIES
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the bodies that make up this graphics model.
 */
rdGBodies* rdGModel::
getBodies() const
{
	return(_bodies);
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
void rdGModel::
updateObject(bool aDeep)
{
	if(_node==NULL) return;

	// BASE CLASS
	rdObject::updateObject(aDeep);

	// MEMBER DATA

	// DEEP?
	if(!aDeep) return;

	// BODIES
	if(_bodies!=NULL) _bodies->updateObject();
}

//-----------------------------------------------------------------------------
// UPDATE NODE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Update the XML node for this object.
 *
 * @param aDeep If true, update the XML node of this object AND the XML nodes
 * of all class members that are rdObjects (child nodes);  if false, update
 * only the XML node of this object without updating the XML nodes of its
 * children.
 */
void rdGModel::
updateNode(bool aDeep)
{
	// BASE CLASS
	rdObject::updateNode();

	// DEEP?
	if(!aDeep) return;

	// BODIES
	if(_bodies!=NULL) _bodies->updateNode();
}


