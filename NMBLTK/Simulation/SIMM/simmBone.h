#ifndef __simmBone_h__
#define __simmBone_h__

// simmBone.h
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
#include <NMBLTK/Tools/rdPropertyStrArray.h>
#include <NMBLTK/Tools/rdStorage.h>
#include <NMBLTK/Tools/rdXMLDocument.h>
#include <NMBLTK/Tools/rdVisibleObject.h>
#include <NMBLTK/Tools/rdArrayPtrs.h>
#ifdef BUILD_GUI
	#include <vtkXMLPolyDataReader.h>
	#include <vtkPolyData.h>
#endif
class simmKinematicsEngine;

//=============================================================================
//=============================================================================
/**
 * A class implementing a SIMM bone. Because the user can interact with the
 * geometry of a bone while manipulating the model, it needs to be accesible
 * within the simm/rd framework (not just on the Java side). simmBone is
 * a type of rdVisibleObject, with additional private data members for holding
 * the bone geometry.
 *
 * @author Peter Loan
 * @version 1.0
 */
class RDSIMULATION_API simmBone : public rdVisibleObject  
{

//=============================================================================
// DATA
//=============================================================================
private:
#ifdef BUILD_GUI
	rdArray<vtkPolyData*> _vtkBones;
	rdArray<vtkXMLPolyDataReader*> _vtkReaders;
#endif
protected:

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	simmBone();
	simmBone(DOMElement *aElement);
	simmBone(const simmBone &aBone);
	virtual ~simmBone();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;

#ifndef SWIG
	simmBone& operator=(const simmBone &aBone);
#endif
   void simmBone::copyData(const simmBone &aBone);

   void setup(simmKinematicsEngine* aEngine);
	void scale(rdArray<double>& aScaleFactors);

	void writeSIMM(std::ofstream& out) const;

	void peteTest() const;

protected:

private:
	void setNull();
	void setupProperties();
//=============================================================================
};	// END of class simmBone
//=============================================================================
//=============================================================================

#endif // __simmBone_h__


