#ifndef __simmMusclePoint_h__
#define __simmMusclePoint_h__

// simmMusclePoint.h
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
#include <string>
#include <math.h>
#include <NMBLTK/Simulation/rdSimulationDLL.h>
#include <NMBLTK/Tools/rdArray.h>
#include <NMBLTK/Tools/rdVisibleObject.h>
#include <NMBLTK/Tools/rdPropertyDblArray.h>
#include <NMBLTK/Tools/rdPropertyStr.h>
#include <NMBLTK/Tools/rdStorage.h>
#include <NMBLTK/Tools/rdXMLDocument.h>
#include "simmBody.h"

class simmModel;
class simmKinematicsEngine;

//=============================================================================
//=============================================================================
/**
 * A class implementing a SIMM muscle point.
 *
 * @author Peter Loan
 * @version 1.0
 */
class RDSIMULATION_API simmMusclePoint : public rdVisibleObject  
{

//=============================================================================
// DATA
//=============================================================================
private:

protected:
   rdPropertyDblArray _attachmentProp;
   rdArray<double> &_attachment;

	rdPropertyStr _bodyNameProp;
   std::string &_bodyName;

   const simmBody *_body;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	simmMusclePoint();
	simmMusclePoint(DOMElement *aElement);
	simmMusclePoint(const simmMusclePoint &aPoint);
	virtual ~simmMusclePoint();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;

#ifndef SWIG
	simmMusclePoint& operator=(const simmMusclePoint &aPoint);
#endif
   void simmMusclePoint::copyData(const simmMusclePoint &aPoint);

	rdArray<double>& getAttachment() const { return _attachment; }
	const simmBody* getBody() const { return _body; }
	std::string& getBodyName() const { return _bodyName; }
	void scale(rdArray<double>& aScaleFactors);

	virtual void writeSIMM(std::ofstream& out) const;
	virtual void setup(simmModel* model, simmKinematicsEngine* ke);

	virtual void peteTest() const;

protected:

private:
	void setNull();
	void setupProperties();
//=============================================================================
};	// END of class simmMusclePoint
//=============================================================================
//=============================================================================

#endif // __simmMusclePoint_h__


