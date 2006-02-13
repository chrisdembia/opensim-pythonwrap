#ifndef __simmPoint_h__
#define __simmPoint_h__

// simmPoint.h
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
#include <iostream>
#include <string>
#include <fstream>
#include <NMBLTK/Simulation/rdSimulationDLL.h>
#include <NMBLTK/Tools/rdObject.h>


//=============================================================================
//=============================================================================
/**
 * A class implementing a 3D point.
 *
 * @author Peter Loan
 * @version 1.0
 */
class RDSIMULATION_API simmPoint : public rdObject
{

//=============================================================================
// DATA
//=============================================================================
private:
	double _location[3];

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	simmPoint();
	simmPoint(double coords[3]);
	simmPoint(const simmPoint& aPoint);
	virtual ~simmPoint();
	virtual rdObject* copy() const;
	simmPoint& operator=(const simmPoint &aPoint);
	simmPoint& operator+=(const simmPoint &aPoint);
	simmPoint& operator/=(double factor);
	void set(double x, double y, double z);
	double* get() { return _location; }
	bool isVisible() const;
	void peteTest() const;

//=============================================================================
};	// END of class simmPoint
//=============================================================================
//=============================================================================

#endif // __simmPoint_h__


