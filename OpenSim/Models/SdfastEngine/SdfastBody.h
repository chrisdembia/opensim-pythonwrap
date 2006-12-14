#ifndef __SdfastBody_h__
#define __SdfastBody_h__

// SdfastBody.h
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
#include <math.h>
#include "SdfastEngineDLL.h"
#include <OpenSim/Tools/VisibleObject.h>
#include <OpenSim/Tools/PropertyInt.h>
#include <OpenSim/Tools/PropertyDbl.h>
#include <OpenSim/Tools/PropertyDblArray.h>
#include <OpenSim/Tools/PropertyObj.h>
#include <OpenSim/Tools/XMLDocument.h>
#include <OpenSim/Simulation/SIMM/AbstractBody.h>
#include <OpenSim/Simulation/SDFast/sdfast.h>

namespace OpenSim {

class SdfastEngine;

//=============================================================================
//=============================================================================
/**
 * A class implementing a SIMM body segment.
 *
 * @author Peter Loan
 * @version 1.0
 */
class SDFAST_ENGINE_API SdfastBody : public AbstractBody  
{

//=============================================================================
// DATA
//=============================================================================
protected:
	PropertyDblArray _massCenterProp;
	Array<double> &_massCenter;

	// Support of display.
	PropertyObj _displayerProp;
	VisibleObject &_displayer;

	// index of this body in the SD/FAST code
	PropertyInt _indexProp;
	int &_index;

	// Sdfast engine that contains this body
	SdfastEngine* _SdfastEngine;
//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	SdfastBody();
	SdfastBody(DOMElement *aElement);
	SdfastBody(const SdfastBody &aBody);
	SdfastBody(const AbstractBody &aBody);
	virtual ~SdfastBody();
	virtual Object* copy() const;
	virtual Object* copy(DOMElement *aElement) const;

	SdfastBody& operator=(const SdfastBody &aBody);
	void copyData(const SdfastBody &aBody);
	void copyData(const AbstractBody &aBody);

	void setup(AbstractDynamicsEngine* aEngine);

	virtual double getMass() const;
	virtual bool setMass(double aMass);
	virtual void getMassCenter(double rVec[3]) const;
	virtual bool setMassCenter(double aVec[3]);
	virtual void getInertia(double rInertia[3][3]) const;
	virtual bool setInertia(const Array<double>& aInertia);
	virtual void scale(Array<double>& aScaleFactors, bool aScaleMass = false);
	virtual void scaleInertialProperties(Array<double>& aScaleFactors);
	virtual VisibleObject* getDisplayer() const { return &_displayer; }

	void setSdfastIndex(int aIndex) { _index = aIndex; }
	int getSdfastIndex() const { return _index; }
	void transformToSdfastFrame(const double aPos[3], double rPos[3]) const;
	void transformToSdfastFrame(const Array<double>& aPos, double rPos[3]) const;
	void transformFromSdfastFrame(const double aPos[3], double rPos[3]) const;
	void transformFromSdfastFrame(const Array<double>& aPos, double rPos[3]) const;

	virtual void peteTest() const;

private:
	void setNull();
	void setupProperties();
//=============================================================================
};	// END of class SdfastBody
//=============================================================================
//=============================================================================

} // end of namespace OpenSim

#endif // __SdfastBody_h__


