#ifndef __simmMarkerFrame_h__
#define __simmMarkerFrame_h__

// simmMarkerFrame.h
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
#include <NMBLTK/Tools/rdArrayPtrs.h>
#include "simmPoint.h"
#include "simmUnits.h"


//=============================================================================
//=============================================================================
/**
 * A class implementing a frame of marker data from a TRC/TRB file.
 *
 * @author Peter Loan
 * @version 1.0
 */
class simmMarkerFrame
{

//=============================================================================
// DATA
//=============================================================================
private:
	int _numMarkers;
	int _frameNumber;
	double _frameTime;
	simmUnits _units;
	rdArrayPtrs<simmPoint> _markers;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	simmMarkerFrame();
	simmMarkerFrame(int aNumMarkers, int aFrameNumber, double aTime, simmUnits& aUnits);
	simmMarkerFrame(const simmMarkerFrame& aFrame);
	virtual ~simmMarkerFrame();
	void addMarker(double coords[3]);
	simmPoint& getMarker(int aIndex) { return *_markers[aIndex]; }
	int getFrameNumber() const { return _frameNumber; }
	void setFrameNumber(int aNumber) { _frameNumber = aNumber; }
	double getFrameTime() const { return _frameTime; }
	void scale(double aScaleFactor);

	void peteTest() const;

private:

//=============================================================================
};	// END of class simmMarkerFrame
//=============================================================================
//=============================================================================

#endif // __simmMarkerFrame_h__


