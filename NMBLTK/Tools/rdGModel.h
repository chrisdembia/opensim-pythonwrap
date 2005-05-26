// rdGModel.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2002 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdGModel_h__
#define __rdGModel_h__

// INCLUDES
#include "rdTools.h"
#include "rdObject.h"
#include "rdGBodies.h"

//=============================================================================
//=============================================================================
/**
 * A graphical model.  A graphical model consists of a collection of 
 * bodies, each of which consists of geometric primatives like triangles
 * and lines.
 */
class RDTOOLS_API rdGModel : public rdObject
{
//=============================================================================
// DATA
//=============================================================================
private:
	/** List of bodies. */
	rdGBodies *_bodies;

//=============================================================================
// METHODS
//=============================================================================
public:
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
	rdGModel();
	rdGModel(const char *aFileName);
	virtual ~rdGModel();
private:
	void setNull();

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
public:
	rdGBodies* getBodies() const;

	//--------------------------------------------------------------------------
	// XML
	//--------------------------------------------------------------------------
	virtual void updateObject(bool aDeep=true);
	virtual void updateNode(bool aDeep=true);

//=============================================================================
};	// END class rdGModel
//=============================================================================
//=============================================================================

#endif  // __rdGModel_h__
