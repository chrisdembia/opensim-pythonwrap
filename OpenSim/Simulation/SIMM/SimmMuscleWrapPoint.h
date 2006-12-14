#ifndef __SimmMuscleWrapPoint_h__
#define __SimmMuscleWrapPoint_h__

// SimmMuscleWrapPoint.h
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
#include <OpenSim/Simulation/rdSimulationDLL.h>
#include "SimmMusclePoint.h"

namespace OpenSim {

class AbstractCoordinate;
class AbstractModel;
class AbstractSimmMuscle;
class AbstractDynamicsEngine;

//=============================================================================
//=============================================================================
/**
 * A class implementing a SIMM muscle via point, which is a muscle point that
 * is active only for a specified range of a coordinate.
 *
 * @author Peter Loan
 * @version 1.0
 */
class RDSIMULATION_API SimmMuscleWrapPoint : public SimmMusclePoint  
{

//=============================================================================
// DATA
//=============================================================================
private:

protected:

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	SimmMuscleWrapPoint();
	SimmMuscleWrapPoint(const SimmMuscleWrapPoint &aPoint);
	virtual ~SimmMuscleWrapPoint();
	virtual Object* copy() const;

#ifndef SWIG
	SimmMuscleWrapPoint& operator=(const SimmMuscleWrapPoint &aPoint);
#endif
   void copyData(const SimmMuscleWrapPoint &aPoint);
	virtual void setup(AbstractModel* aModel, AbstractSimmMuscle* aMuscle);

	double getWrapLength() const;

	virtual void peteTest() const;

private:
	void setNull();
	void setupProperties();
//=============================================================================
};	// END of class SimmMuscleWrapPoint
//=============================================================================
//=============================================================================

} // end of namespace OpenSim

#endif // __SimmMuscleWrapPoint_h__


