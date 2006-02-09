#ifndef __simmMeasurement_h__
#define __simmMeasurement_h__

// simmMeasurement.h
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
#include <NMBLTK/Simulation/rdSimulationDLL.h>
#include <NMBLTK/Tools/rdPropertyObjArray.h>
#include <NMBLTK/Tools/rdPropertyBool.h>
#include <NMBLTK/Tools/rdStorage.h>
#include <NMBLTK/Tools/rdXMLDocument.h>
#include <NMBLTK/Tools/suScale.h>
#include <NMBLTK/Tools/suScaleSet.h>

#include "simmMarkerPair.h"
#include "simmBodyScale.h"

//=============================================================================
//=============================================================================
/**
 * A class implementing a measurement (the distance between one or more pairs
 * of markers, used to scale a model).
 *
 * @author Peter Loan
 * @version 1.0
 */
class simmMeasurement : public rdObject  
{

//=============================================================================
// DATA
//=============================================================================
private:

protected:
	rdPropertyObjArray _markerPairSetProp;
	rdArrayPtrs<simmMarkerPair> &_markerPairSet;

	rdPropertyObjArray _bodyScaleSetProp;
	rdArrayPtrs<simmBodyScale> &_bodyScaleSet;

	rdPropertyBool _applyProp;
	bool &_apply;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	simmMeasurement();
	simmMeasurement(DOMElement *aElement);
	simmMeasurement(const simmMeasurement &aMeasurement);
	virtual ~simmMeasurement();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;

	simmMeasurement& operator=(const simmMeasurement &aMeasurement);
   void simmMeasurement::copyData(const simmMeasurement &aMeasurement);

	int getNumMarkerPairs() const { return _markerPairSet.getSize(); }
	const simmMarkerPair& getMarkerPair(int aIndex) const { return *_markerPairSet[aIndex]; }
	bool getApply() const { return _apply; }
	void applyScaleFactor(double aFactor, suScaleSet& aScaleSet);

	/* Register types to be used when reading a simmMeasurement object from xml file. */
	static void registerTypes();

	void peteTest() const;

protected:

private:
	void setNull();
	void setupProperties();
//=============================================================================
};	// END of class simmMeasurement
//=============================================================================
//=============================================================================

#endif // __simmMeasurement_h__


