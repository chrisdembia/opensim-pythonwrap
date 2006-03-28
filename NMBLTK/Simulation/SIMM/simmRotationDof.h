#ifndef __simmRotationDof_h__
#define __simmRotationDof_h__

// simmRotationDof.h
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
#include <NMBLTK/Tools/rdPropertyDblArray.h>
#include <NMBLTK/Tools/rdStorage.h>
#include <NMBLTK/Tools/rdXMLDocument.h>
#include "simmDof.h"

//=============================================================================
//=============================================================================
/**
 * A class implementing a SIMM rotational DOF.
 *
 * @author Peter Loan
 * @version 1.0
 */
class RDSIMULATION_API simmRotationDof : public simmDof  
{

//=============================================================================
// DATA
//=============================================================================
private:

protected:
	rdPropertyDblArray _axisProp;
	rdArray<double> &_axis;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	simmRotationDof();
	simmRotationDof(DOMElement *aElement);
	simmRotationDof(const simmRotationDof &aDof);
	virtual ~simmRotationDof();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;

#ifndef SWIG
	simmRotationDof& operator=(const simmRotationDof &aDof);
#endif
   void simmRotationDof::copyData(const simmRotationDof &aDof);

	virtual void getAxis(double axis[3]) const;
	const rdArray<double>& getAxis() const { return _axis; }
	virtual const double* getAxisPtr() const { return &_axis[0]; }
	virtual double getValue();
	virtual DofType getType() const { return DofType::Rotational; }

	virtual void peteTest();

protected:

private:
	void setNull();
	void setupProperties();
//=============================================================================
};	// END of class simmDof
//=============================================================================
//=============================================================================

#endif // __simmRotationDof_h__


