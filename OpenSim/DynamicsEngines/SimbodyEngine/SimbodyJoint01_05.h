#ifndef __SimbodyJoint01_05_h__
#define __SimbodyJoint01_05_h__
// SimbodyJoint01_05.h
// Author: Frank C. Anderson, Peter Loan
/*
 * Copyright (c)  2007, Stanford University. All rights reserved. 
* Use of the OpenSim software in source form is permitted provided that the following
* conditions are met:
* 	1. The software is used only for non-commercial research and education. It may not
*     be used in relation to any commercial activity.
* 	2. The software is not distributed or redistributed.  Software distribution is allowed 
*     only through https://simtk.org/home/opensim.
* 	3. Use of the OpenSim software or derivatives must be acknowledged in all publications,
*      presentations, or documents describing work in which OpenSim or derivatives are used.
* 	4. Credits to developers may not be removed from executables
*     created from modifications of the source.
* 	5. Modifications of source code must retain the above copyright notice, this list of
*     conditions and the following disclaimer. 
* 
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
*  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
*  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
*  SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
*  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
*  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
*  OR BUSINESS INTERRUPTION) OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
*  WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


// INCLUDE
#include <string>
#include "osimSimbodyEngineDLL.h"
#include <OpenSim/Common/PropertyStr.h>
#include <OpenSim/Common/PropertyStrArray.h>
#include <OpenSim/Common/Transform.h>
#include <OpenSim/Common/ScaleSet.h>
#include <OpenSim/Simulation/Model/AbstractJoint.h>
#include <OpenSim/Simulation/Model/DofSet01_05.h>
#include "SimbodyBody01_05.h"
#include "SimbodyCoordinate01_05.h"

namespace OpenSim {

//=============================================================================
//=============================================================================
/**
 * A class implementing a Simbody joint.
 *
 * @author Frank C. Anderson, Peter Loan
 * @version 1.0
 */
class OSIMSIMBODYENGINE_API SimbodyJoint01_05 : public AbstractJoint  
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
	PropertyDblVec3 _locationInParentProp;
	SimTK::Vec3& _locationInParent;

	/** Location of the joint in the child body specified in the child
	reference frame.  For SIMM models, this vector is always the zero vector
	(i.e., the body reference frame coincides with the joint).  */
	PropertyDblVec3 _locationInChildProp;
	SimTK::Vec3& _locationInChild;

	/** Set of degrees of freedom.  These specify the six degrees of freedom
	between the parent body and child body. */
	PropertyObj _dofSetProp;
	DofSet01_05 &_dofSet;

	/** ID of the child body that this joint connects to a parent body. */
	SimTK::MobilizedBodyIndex _bodyId;

	/** Child body. */
   SimbodyBody01_05 *_childBody;

	/** Parent body. */
   SimbodyBody01_05 *_parentBody;

	/** Transform for expressing a vector given in the child frame in
	the parent fram. */
	Transform _forwardTransform;

	/** Transform for expressing a vector given in the parent frame in
	the child frame. */
	Transform _inverseTransform;

	/** Simbody engine that contains this joint. */
	SimbodyEngine01_05* _engine;

	const static std::string _NewType;
//=============================================================================
// METHODS
//=============================================================================
public:
	// CONSTRUCTION
	SimbodyJoint01_05();
	SimbodyJoint01_05(const SimbodyJoint01_05 &aJoint);
	virtual ~SimbodyJoint01_05();
	virtual Object* copy() const;
	void setup(AbstractDynamicsEngine* aEngine);
	SimbodyJoint01_05& operator=(const SimbodyJoint01_05 &aJoint);
	void copyData(const SimbodyJoint01_05 &aJoint);

	virtual const std::string& getNewType() const { return _NewType; };
	// GET & SET
	void setParentBodyName(const std::string& aName);
	std::string getParentBodyName();
	void setBodyName(const std::string& aName);
	std::string getBodyName();
	virtual SimbodyBody01_05* getBody() const { return _childBody; }
	virtual SimbodyBody01_05* getParentBody() const { return _parentBody; }
	virtual DofSet01_05* getDofSet() const { return &_dofSet; }
	virtual void setLocationInParent(const SimTK::Vec3& aLocation);
	virtual void getLocationInParent(SimTK::Vec3& rLocation) const;
	virtual void setLocationInChild(const SimTK::Vec3& aLocation);
	virtual void getLocationInChild(SimTK::Vec3& rLocation) const;

	virtual void getLocationInParent(double rLocation[]) const {};
	virtual void getLocationInChild(double rLocation[]) const {};

	virtual const Transform& getForwardTransform();
	virtual const Transform& getInverseTransform();

	// SCALE
	virtual void scale(const ScaleSet& aScaleSet);

	// UTILITY
	bool isTreeJoint() const;
	virtual bool isCoordinateUsed(AbstractCoordinate* aCoordinate) const { return false; }
	virtual bool hasXYZAxes() const;

private:
	void setNull();
	void setupProperties();
	void calcTransforms();
	void updateSimbody();
	friend class SimbodyEngine01_05;
	friend class SimbodyEngine;

//=============================================================================
};	// END of class SimbodyJoint01_05
//=============================================================================
//=============================================================================

} // end of namespace OpenSim

#endif // __SimbodyJoint01_05_h__

