#ifndef __simmMotionEvent_h__
#define __simmMotionEvent_h__

// simmMotionEvent.h
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
#include <iostream>
#include <math.h>
#include <NMBLTK/Simulation/rdSimulationDLL.h>
#include <NMBLTK/Tools/rdObject.h>
#include <NMBLTK/Tools/rdPropertyDbl.h>
#include <NMBLTK/Tools/rdPropertyDblArray.h>
#include <NMBLTK/Tools/rdXMLDocument.h>

//=============================================================================
//=============================================================================
/**
 * A class implementing an event in a SIMM motion.
 *
 * @author Peter Loan
 * @version 1.0
 */
class RDSIMULATION_API simmMotionEvent : public rdObject  
{

//=============================================================================
// DATA
//=============================================================================
private:

protected:
	rdPropertyDbl _timeProp;
	double& _time;

	rdPropertyDblArray _colorProp;
	rdArray<double> _color;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	simmMotionEvent();
	simmMotionEvent(DOMElement *aElement);
	simmMotionEvent(const simmMotionEvent &aEvent);
	virtual ~simmMotionEvent();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;

	simmMotionEvent& operator=(const simmMotionEvent &aEvent);
	void copyData(const simmMotionEvent &aEvent);
	void setName(std::string aName) { _name = aName; }
	void setTime(double aTime) { _time = aTime; }
	double getTime() const { return _time; }
	void setColor(double* aColor);
	const double* getColor() const { return &_color[0]; }

	void peteTest() const;

protected:

private:
	void setNull();
	void setupProperties();
//=============================================================================
};	// END of class simmMotionEvent
//=============================================================================
//=============================================================================

#endif // __simmMotionEvent_h__


