#ifndef __SimbodyJoint_h__
#define __SimbodyJoint_h__
// SimbodyJoint.h
// Author: Frank C. Anderson
/*
 * Copyright (c) 2006, Stanford University. All rights reserved. 
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including 
 * without limitation the rights to use, copy, modify, merge, publish, 
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included 
 * in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


// INCLUDE
#include <string>
#include "osimSimbodyEngineDLL.h"
#include <OpenSim/Common/PropertyStr.h>
#include <OpenSim/Common/PropertyStrArray.h>
#include <OpenSim/Common/Transform.h>
#include <OpenSim/Common/ScaleSet.h>
#include <OpenSim/Simulation/Model/AbstractJoint.h>
#include "SimbodyBody.h"
#include "SimbodyCoordinate.h"

namespace OpenSim {

//=============================================================================
//=============================================================================
/**
 * A class implementing a Simbody joint.
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class OSIMSIMBODYENGINE_API SimbodyJoint : public AbstractJoint  
{

//=============================================================================
// DATA
//=============================================================================
protected:
	/** Names of bodies that this joint connects. */
	PropertyStrArray _bodiesProp;
	Array<std::string>& _bodies;

	/** Location of the joint in the parent body specified in the parent
	reference frame. */
	PropertyDblArray _locationInParentProp;
	Array<double> &_locationInParent;

	/** Location of the joint in the child body specified in the child
	reference frame.  For SIMM models, this vector is always the zero vector
	(i.e., the body reference frame coincides with the joint).  */
	PropertyDblArray _locationInChildProp;
	Array<double> &_locationInChild;

	/** ID of the child body that this joint connects to a parent body. */
	SimTK::BodyId _bodyId;

	/** Child body. */
   SimbodyBody *_childBody;

	/** Parent body. */
   SimbodyBody *_parentBody;

	/** Forward transform. */
	Transform _forwardTransform;

	/** Inverse transforms. */
	Transform _inverseTransform;

	/** Simbody engine that contains this joint. */
	SimbodyEngine* _engine;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	SimbodyJoint();
	SimbodyJoint(const SimbodyJoint &aJoint);
	virtual ~SimbodyJoint();
	virtual Object* copy() const;

	void setup(AbstractDynamicsEngine* aEngine);

	SimbodyJoint& operator=(const SimbodyJoint &aJoint);
	void copyData(const SimbodyJoint &aJoint);

	virtual DofSet* getDofSet() const { return NULL; }
	virtual SimbodyBody* getChildBody() const { return _childBody; }
	virtual SimbodyBody* getParentBody() const { return _parentBody; }
	virtual void setLocationInParent(const double aLocation[3]);
	virtual void getLocationInParent(double rLocation[3]) const;
	virtual void setLocationInChild(const double aLocation[3]);
	virtual void getLocationInChild(double rLocation[3]) const;
	virtual const Transform& getForwardTransform();
	virtual const Transform& getInverseTransform();
	virtual bool isCoordinateUsed(AbstractCoordinate* aCoordinate) const { return false; }
	virtual bool hasXYZAxes() const;
	virtual void scale(const ScaleSet& aScaleSet);

	void setParentBodyName(const std::string& aName);
	void setChildBodyName(const std::string& aName);
	void setSimbodyType(const char* aName);
	bool isTreeJoint() const;

	virtual void peteTest();

private:
	void setNull();
	void setupProperties();
	void calcTransforms();
	void updateSimbody();

//=============================================================================
};	// END of class SimbodyJoint
//=============================================================================
//=============================================================================

} // end of namespace OpenSim

#endif // __SimbodyJoint_h__


