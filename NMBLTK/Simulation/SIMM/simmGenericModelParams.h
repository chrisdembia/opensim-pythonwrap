#ifndef __simmGenericModelParams_h__
#define __simmGenericModelParams_h__

// simmGenericModelParams.h
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
#include <NMBLTK/Tools/rdPropertyStr.h>
#include <NMBLTK/Tools/rdPropertyObjArray.h>
#include <NMBLTK/Tools/rdXMLDocument.h>
#include "simmModel.h"
#include "simmMarker.h"

//=============================================================================
//=============================================================================
/**
 * A class implementing a set of parameters describing
 * a generic musculoskeletal model.
 *
 * @author Peter Loan
 * @version 1.0
 */
class RDSIMULATION_API simmGenericModelParams : public rdObject  
{

//=============================================================================
// DATA
//=============================================================================
private:

protected:
	rdPropertyStr _fileNameProp;
	std::string &_fileName;

	rdPropertyObjArray _markerSetProp;
	rdArrayPtrs<simmMarker> &_markerSet;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	simmGenericModelParams();
	simmGenericModelParams(DOMElement *aElement);
	simmGenericModelParams(const simmGenericModelParams &aGenericModelParams);
	virtual ~simmGenericModelParams();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;

	simmGenericModelParams& operator=(const simmGenericModelParams &aGenericModelParams);
	void copyData(const simmGenericModelParams &aGenericModelParams);

	simmModel* processModel();

	/* Register types to be used when reading a simmGenericModelParams object from xml file. */
	static void registerTypes();

	void peteTest() const;

protected:

private:
	void setNull();
	void setupProperties();
//=============================================================================
};	// END of class simmGenericModelParams
//=============================================================================
//=============================================================================

#endif // __simmGenericModelParams_h__


