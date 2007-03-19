#ifndef __WrapResult_h__
#define __WrapResult_h__

// WrapResult.h
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
#include <OpenSim/Simulation/osimSimulationDLL.h>
#include <OpenSim/Common/Array.h>
#include <OpenSim/Common/SimmPoint.h>

namespace OpenSim {

//=============================================================================
//=============================================================================
/**
 * A class for holding the results of a wrapping calculation.
 *
 * @author Peter Loan
 * @version 1.0
 */
class OSIMSIMULATION_API WrapResult
{

//=============================================================================
// DATA
//=============================================================================
public:
	int startPoint;            // first point in muscle line that is wrapped
	int endPoint;              // second point in muscle line that is wrapped
	Array<SimmPoint> wrap_pts; // array of wrapping path points
   double wrap_path_length;   // distance along curved r1->r2 path
   double r1[3];              // wrap tangent point nearest to p1
   double r2[3];              // wrap tangent point nearest to p2
	double c1[3];              // intermediate point used by some wrap objects
	double sv[3];              // intermediate point used by some wrap objects
	double factor;             // scale factor used to normalize parameters

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	WrapResult();
	virtual ~WrapResult();
	void copyData(const WrapResult& aWrapResult);
	WrapResult& operator=(const WrapResult& aWrapResult);

//=============================================================================
};	// END of class WrapResult
//=============================================================================
//=============================================================================

} // end of namespace OpenSim

#endif // __WrapResult_h__


