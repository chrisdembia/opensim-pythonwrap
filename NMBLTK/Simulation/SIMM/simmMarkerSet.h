#ifndef __simmMarkerSet_h__
#define __simmMarkerSet_h__

// simmMarkerSet.h
// Author: Ayman Habib, Peter Loan
/* Copyright (c) 2005, Stanford University, Ayman Habib, and Peter Loan.
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

#include <NMBLTK/Simulation/rdSimulationDLL.h>
#include <NMBLTK/Tools/rdSet.h>
#include "simmMarker.h"

/* A set of markers to be used for inverse kinematics */
class RDSIMULATION_API simmMarkerSet :	public rdSet<simmMarker>
{
private:
	void setNull();
public:
	simmMarkerSet();
	simmMarkerSet(const std::string& aMarkersFileName);
	~simmMarkerSet(void);
};
#endif