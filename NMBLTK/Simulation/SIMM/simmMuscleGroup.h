#ifndef __simmMuscleGroup_h__
#define __simmMuscleGroup_h__

// simmMuscleGroup.h
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
#include <NMBLTK/Tools/rdObject.h>
#include <NMBLTK/Tools/rdXMLDocument.h>

class simmModel;
class simmMuscle;

//=============================================================================
//=============================================================================
/**
 * A class implementing a SIMM muscle group. Muscle groups are used in SIMM
 * to make muscle menus in the GUI more user-friendly.
 *
 * @author Peter Loan
 * @version 1.0
 */
class RDSIMULATION_API simmMuscleGroup : public rdObject  
{

//=============================================================================
// DATA
//=============================================================================
private:

protected:
	rdArray<simmMuscle*> _muscles;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	simmMuscleGroup();
	simmMuscleGroup(const simmMuscleGroup &aGroup);
	simmMuscleGroup(DOMElement *aElement);
	virtual ~simmMuscleGroup();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;

	simmMuscleGroup& operator=(const simmMuscleGroup &aGroup);
   void simmMuscleGroup::copyData(const simmMuscleGroup &aGroup);

   void setup(simmModel* aModel);

	bool contains(const std::string& aName) const;

	void peteTest() const;

protected:

private:
	void setNull();
	void setupProperties();
//=============================================================================
};	// END of class simmMuscleGroup
//=============================================================================
//=============================================================================

#endif // __simmMuscleGroup_h__


