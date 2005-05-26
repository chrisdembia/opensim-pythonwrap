// rdVertices.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2002 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdVertices_h__
#define __rdVertices_h__


#include "rdTools.h"
#include "rdPtrArray.h"
#include "rdV3D.h"


//=============================================================================
//=============================================================================
/**
 * A class for storing an array of rdV3D (3D vertices of type double).
 *
 * @version 1.0
 * @author Frank C. Anderson
 */
class RDTOOLS_API rdVertices : public rdPtrArray
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
	virtual ~rdVertices();
	rdVertices();
	rdVertices(DOMElement *aElement);
private:
	void setNull();

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
public:
	virtual rdV3D* getVertex(int aIndex);

	//--------------------------------------------------------------------------
	// OPERATIONS
	//--------------------------------------------------------------------------
	void translate(double aX,double aY,double aZ);
	void rotate(int aXYZ,double aRadians);

	//--------------------------------------------------------------------------
	// XML
	//--------------------------------------------------------------------------
	virtual void updateObject(bool aDeep=true);
	virtual void updateNode(bool aDeep=true);

//=============================================================================
};	// END of class rdVertices
//=============================================================================
//=============================================================================

#endif //__rdVertices_h__
