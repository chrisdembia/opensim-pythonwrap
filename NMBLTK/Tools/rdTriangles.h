// rdTriangles.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2002 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdTriangles_h__
#define __rdTriangles_h__


#include "rdTools.h"
#include "rdPtrArray.h"
#include "rdTriangle.h"


//=============================================================================
//=============================================================================
/**
 * A class for storing an array of rdTriangle objects.
 *
 * @version 1.0
 * @author Frank C. Anderson
 */
class RDTOOLS_API rdTriangles : public rdPtrArray
{

//=============================================================================
// DATA
//=============================================================================
public:

protected:


//=============================================================================
// METHODS
//=============================================================================
public:
	virtual ~rdTriangles();
	rdTriangles();
	rdTriangles(DOMElement *aElement);
private:
	void setNull();

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
public:
	void setVertices(rdVertices *aVertices);
	virtual rdTriangle* getTriangle(int aIndex);

	//--------------------------------------------------------------------------
	// OPERATIONS
	//--------------------------------------------------------------------------
	void updateIndices();

	//--------------------------------------------------------------------------
	// DOCUMENT AND NODE
	//--------------------------------------------------------------------------
	virtual void updateNode(bool aDeep=true);


//=============================================================================
};	// END of class rdTriangles
//=============================================================================
//=============================================================================

#endif //__rdTriangles_h__
