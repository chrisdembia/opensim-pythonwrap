#ifndef __simmStep_h__
#define __simmStep_h__

// simmStep.h
// Author: Peter Loan
/* Copyright (c) 2005, Stanford University and Peter Loan.
 * 
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
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <NMBLTK/Simulation/rdSimulationDLL.h>
#include <NMBLTK/Tools/rdTransform.h>
#include <NMBLTK/Tools/rdStorage.h>

class simmJoint;

//=============================================================================
//=============================================================================
/**
 * A class implementing one step in a simmPath; that is, a joint and direction
 * from a body to an adjacent body.
 *
 * @author Peter Loan
 * @version 1.0
 */
class RDSIMULATION_API simmStep
{
public:
	typedef enum
	{
		forward,
		inverse
	} Direction;

//=============================================================================
// DATA
//=============================================================================
private:
	simmJoint* _joint;
	Direction _direction;
	rdTransform  _transformCache;
//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	simmStep();
	simmStep(simmJoint* aJoint, Direction aDirection);
	virtual ~simmStep();

	Direction getDirection() const { return _direction; }
	simmJoint* getJoint() const { return _joint; }
	rdTransform& getJointTransform();
	void peteTest() const;

private:
	void calcTransforms();

//=============================================================================
};	// END of class simmStep
//=============================================================================
//=============================================================================

#endif // __simmStep_h__


