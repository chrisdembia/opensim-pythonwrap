#ifndef __simmTranslationDof_h__
#define __simmTranslationDof_h__

// simmTranslationDof.h
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
#include <NMBLTK/Tools/rdStorage.h>
#include <NMBLTK/Tools/rdXMLDocument.h>
#include "simmDof.h"

#define TX_NAME "tx"
#define TY_NAME "ty"
#define TZ_NAME "tz"

//=============================================================================
//=============================================================================
/**
 * A class implementing a SIMM translational DOF.
 *
 * @author Peter Loan
 * @version 1.0
 */
class RDSIMULATION_API simmTranslationDof : public simmDof  
{
public:
	enum AxisIndex
	{
		xTranslation = 0,
		yTranslation,
		zTranslation
	};

//=============================================================================
// DATA
//=============================================================================
private:

protected:
	double _axis[3];
	AxisIndex _axisIndex;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	simmTranslationDof();
	simmTranslationDof(DOMElement *aElement);
	simmTranslationDof(const simmTranslationDof &aDof);
	virtual ~simmTranslationDof();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;
	virtual void updateFromXMLNode();

	simmTranslationDof& operator=(const simmTranslationDof &aDof);
   void simmTranslationDof::copyData(const simmTranslationDof &aDof);

	virtual void getAxis(double axis[3]) const;
	virtual const double* getAxisPtr() const { return &_axis[0]; }
	virtual double getValue();
	virtual DofType getType() const { return DofType::Translational; }
	void getTranslation(double vec[4]);
	AxisIndex getAxisIndex() const { return _axisIndex; }

	virtual void peteTest();

protected:

private:
	void setNull();
	void setupProperties();
//=============================================================================
};	// END of class simmDof
//=============================================================================
//=============================================================================

#endif // __simmTranslationDof_h__


