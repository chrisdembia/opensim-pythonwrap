#ifndef __simmMuscleViaPoint_h__
#define __simmMuscleViaPoint_h__

// simmMuscleViaPoint.h
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
#include <NMBLTK/Tools/rdVisibleObject.h>
#include <NMBLTK/Tools/rdPropertyDblArray.h>
#include <NMBLTK/Tools/rdPropertyStr.h>
#include <NMBLTK/Tools/rdStorage.h>
#include <NMBLTK/Tools/rdXMLDocument.h>
#include "simmMusclePoint.h"
#include "simmCoordinate.h"

class simmModel;
class simmKinematicsEngine;

//=============================================================================
//=============================================================================
/**
 * A class implementing a SIMM muscle via point, which is a muscle point that
 * is active only for a specified range of a coordinate.
 *
 * @author Peter Loan
 * @version 1.0
 */
class simmMuscleViaPoint : public simmMusclePoint  
{

//=============================================================================
// DATA
//=============================================================================
private:

protected:
   rdPropertyDblArray _rangeProp;
   rdArray<double> &_range;

	rdPropertyStr _coordinateNameProp;
   std::string &_coordinateName;

	const simmCoordinate* _coordinate;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	simmMuscleViaPoint();
	simmMuscleViaPoint(DOMElement *aElement);
	simmMuscleViaPoint(const simmMuscleViaPoint &aPoint);
	virtual ~simmMuscleViaPoint();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;

	simmMuscleViaPoint& operator=(const simmMuscleViaPoint &aPoint);
   void simmMuscleViaPoint::copyData(const simmMuscleViaPoint &aPoint);

	rdArray<double>& getRange() const { return _range; }
	std::string& getCoordinateName() const { return _coordinateName; }

	virtual void writeSIMM(std::ofstream& out) const;
	virtual void setup(simmModel* model, simmKinematicsEngine* ke);

	virtual void peteTest() const;

protected:

private:
	void setNull();
	void setupProperties();
//=============================================================================
};	// END of class simmMuscleViaPoint
//=============================================================================
//=============================================================================

#endif // __simmMuscleViaPoint_h__


