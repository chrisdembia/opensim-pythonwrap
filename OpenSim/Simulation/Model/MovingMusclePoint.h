#ifndef __MovingMusclePoint_h__
#define __MovingMusclePoint_h__

// MovingMusclePoint.h
// Author: Peter Loan
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
#include <iostream>
#include <string>
#include <math.h>
#include <OpenSim/Simulation/osimSimulationDLL.h>
#include <OpenSim/Common/VisibleObject.h>
#include <OpenSim/Common/PropertyObjPtr.h>
#include <OpenSim/Common/PropertyStr.h>
#include <OpenSim/Common/Storage.h>
#include <OpenSim/Common/Function.h>
#include <OpenSim/Simulation/Model/MusclePoint.h>

#ifdef SWIG
	#ifdef OSIMSIMULATION_API
		#undef OSIMSIMULATION_API
		#define OSIMSIMULATION_API
	#endif
#endif

namespace OpenSim {

class AbstractCoordinate;
class Model;
class AbstractMuscle;
class AbstractDynamicsEngine;

//=============================================================================
//=============================================================================
/**
 * A class implementing a moving muscle point, which is a muscle point that
 * moves in a body's reference frame as a function of a coordinate.
 *
 * @author Peter Loan
 * @version 1.0
 */
class OSIMSIMULATION_API MovingMusclePoint : public MusclePoint  
{

//=============================================================================
// DATA
//=============================================================================
private:

protected:
	PropertyObjPtr<Function> _XAttachmentProp;
	Function* &_XAttachment;

	PropertyStr _XCoordinateNameProp;
   std::string &_XCoordinateName;

	const AbstractCoordinate* _XCoordinate;

	PropertyObjPtr<Function> _YAttachmentProp;
	Function* &_YAttachment;

	PropertyStr _YCoordinateNameProp;
   std::string &_YCoordinateName;

	const AbstractCoordinate* _YCoordinate;

	PropertyObjPtr<Function> _ZAttachmentProp;
	Function* &_ZAttachment;

	PropertyStr _ZCoordinateNameProp;
   std::string &_ZCoordinateName;

	const AbstractCoordinate* _ZCoordinate;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	MovingMusclePoint();
	MovingMusclePoint(const MovingMusclePoint &aPoint);
	virtual ~MovingMusclePoint();
	virtual Object* copy() const;

#ifndef SWIG
	MovingMusclePoint& operator=(const MovingMusclePoint &aPoint);
#endif
   void copyData(const MovingMusclePoint &aPoint);

	const AbstractCoordinate* getXCoordinate() const { return _XCoordinate; }
	const AbstractCoordinate* getYCoordinate() const { return _YCoordinate; }
	const AbstractCoordinate* getZCoordinate() const { return _ZCoordinate; }
	void setXCoordinate(AbstractCoordinate& aCoordinate);
	void setYCoordinate(AbstractCoordinate& aCoordinate);
	void setZCoordinate(AbstractCoordinate& aCoordinate);
	const std::string& getXCoordinateName() const { return _XCoordinateName; }
	const std::string& getYCoordinateName() const { return _YCoordinateName; }
	const std::string& getZCoordinateName() const { return _ZCoordinateName; }

	virtual bool isActive() const { return true; }
	virtual void setup(Model* aModel, AbstractMuscle* aMuscle);
	virtual void update();
	virtual void getVelocity(double aVelocity[3]);

	OPENSIM_DECLARE_DERIVED(MovingMusclePoint, MusclePoint);
private:
	void setNull();
	void setupProperties();
//=============================================================================
};	// END of class MovingMusclePoint
//=============================================================================
//=============================================================================

} // end of namespace OpenSim

#endif // __MovingMusclePoint_h__

