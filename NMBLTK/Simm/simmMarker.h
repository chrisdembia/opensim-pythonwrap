#ifndef __simmMarker_h__
#define __simmMarker_h__

// simmMarker.h
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
#include <math.h>
#include <NMBLTK/Simulation/rdSimulationDLL.h>
#include <NMBLTK/Tools/rdPropertyDbl.h>
#include <NMBLTK/Tools/rdPropertyStr.h>
#include <NMBLTK/Tools/rdPropertyDblArray.h>
#include <NMBLTK/Tools/rdPropertyBool.h>
#include <NMBLTK/Tools/rdStorage.h>
#include <NMBLTK/Tools/rdXMLDocument.h>

class simmKinematicsEngine;

//=============================================================================
//=============================================================================
/**
 * A class implementing a SIMM [mocap] marker.
 *
 * @author Peter Loan
 * @version 1.0
 */
class simmMarker : public rdObject
{

//=============================================================================
// DATA
//=============================================================================
private:

protected:
	rdPropertyDblArray _attachmentProp;
	rdArray<double> &_attachment;

	rdPropertyDbl _weightProp;
	double &_weight;

	rdPropertyBool _fixedProp;
	bool &_fixed;

	// The bodyName property is used only for markers that are part of a
	// simmMarkerSet, not for ones that are part of a simmModel.
	rdPropertyStr _bodyNameProp;
	std::string &_bodyName;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	simmMarker();
	simmMarker(DOMElement *aElement);
	simmMarker(const simmMarker &aMarker);
	virtual ~simmMarker();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;

	simmMarker& operator=(const simmMarker &aMarker);
	void copyData(const simmMarker &aMarker);
	void updateFromMarker(const simmMarker &aMarker);

	void getOffset(double *aOffset) const;
	const double* getOffset() const { return &_attachment[0]; }
	void setOffset(double pt[3]);
	bool getFixed() const { return _fixed; }
	double getWeight() const { return _weight; }
	const std::string* getBodyName() const;
	void setup(simmKinematicsEngine* aEngine);
	void scale(rdArray<double>& aScaleFactors);

	void writeSIMM(std::ofstream& out) const;

	void peteTest() const;

protected:

private:
	void setNull();
	void setupProperties();
//=============================================================================
};	// END of class simmMarker
//=============================================================================
//=============================================================================

#endif // __simmMarker_h__


