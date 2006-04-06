#ifndef __simmIKParams_h__
#define __simmIKParams_h__

// simmIKParams.h
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
#include <NMBLTK/Tools/rdPropertyDblArray.h>
#include <NMBLTK/Tools/rdPropertyObjArray.h>
#include <NMBLTK/Tools/rdPropertyBool.h>
#include <NMBLTK/Tools/rdPropertyStr.h>
#include <NMBLTK/Tools/rdPropertyStrArray.h>
#include <NMBLTK/Tools/rdStorage.h>
#include <NMBLTK/Tools/rdXMLDocument.h>

#include "simmCoordinate.h"
#include "simmMarker.h"
#include "simmIKTrialParams.h"
#include "simmModel.h"

//=============================================================================
//=============================================================================
/**
 * A class implementing a set of parameters describing how to perform
 * a group of inverse kinematics trials on a model and a marker set.
 *
 * @author Peter Loan
 * @version 1.0
 */
class RDSIMULATION_API simmIKParams : public rdObject  
{

//=============================================================================
// DATA
//=============================================================================
private:

protected:
	// name of model file to use for IK (optional)
	rdPropertyStr _modelFileNameProp;
	std::string &_modelFileName;

	// marker set for updating markers in model before doing IK
	rdPropertyObjArray _markerSetProp;
	rdArrayPtrs<simmMarker> &_markerSet;

	// coordinate set for updating coordinates in model before doing IK
	rdPropertyObjArray _coordinateSetProp;
	rdArrayPtrs<simmCoordinate> &_coordinateSet;

	// parameters for the set of IK trials to perform
	rdPropertyObjArray _IKTrialParamsSetProp;
	rdArrayPtrs<simmIKTrialParams> &_IKTrialParamsSet;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	simmIKParams();
	simmIKParams(DOMElement *aElement);
	simmIKParams(const simmIKParams &aIKParams);
	virtual ~simmIKParams();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;

#ifndef SWIG
	simmIKParams& operator=(const simmIKParams &aIKParams);
#endif
   void simmIKParams::copyData(const simmIKParams &aIKParams);

	bool solveIK(IKSolverInterface *aSolver,simmModel* aModel);

	/* Register types to be used when reading a simmIKParams object from xml file. */
	static void registerTypes();

	void peteTest() const;

protected:

private:
	void setNull();
	void setupProperties();
//=============================================================================
};	// END of class simmIKParams
//=============================================================================
//=============================================================================

#endif // __simmIKParams_h__


