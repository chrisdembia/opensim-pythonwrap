#ifndef __simmMuscle_h__
#define __simmMuscle_h__

// simmMuscle.h
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
#include <NMBLTK/Tools/rdPropertyDbl.h>
#include <NMBLTK/Tools/rdPropertyObjArray.h>
#include <NMBLTK/Tools/rdStorage.h>
#include <NMBLTK/Tools/rdArrayPtrs.h>
#include <NMBLTK/Tools/rdXMLDocument.h>
#include <NMBLTK/Tools/suScaleSet.h>
#include <NMBLTK/Simulation/Model/rdActuator.h>
#include <NMBLTK/Tools/rdFunction.h>
#include "simmMusclePoint.h"

class simmKinematicsEngine;
class simmMuscleGroup;

//=============================================================================
//=============================================================================
/**
 * A class implementing a SIMM muscle.
 *
 * @author Peter Loan
 * @version 1.0
 */
class RDSIMULATION_API simmMuscle : public rdActuator  
{

//=============================================================================
// DATA
//=============================================================================
private:

protected:
	rdPropertyObjArray _attachmentsProp;
	rdArrayPtrs<simmMusclePoint> &_attachments;

	rdPropertyDbl _maxIsometricForceProp;
	double &_maxIsometricForce;

	rdPropertyDbl _optimalFiberLengthProp;
	double &_optimalFiberLength;

	rdPropertyDbl _tendonSlackLengthProp;
	double &_tendonSlackLength;

	rdPropertyDbl _pennationAngleProp;
	double &_pennationAngle;

	rdPropertyDbl _maxContractionVelocityProp;
	double &_maxContractionVelocity;

	rdPropertyObjArray _tendonForceLengthCurveProp;
	rdArrayPtrs<rdFunction> &_tendonForceLengthCurve;

	rdPropertyObjArray _activeForceLengthCurveProp;
	rdArrayPtrs<rdFunction> &_activeForceLengthCurve;

	rdPropertyObjArray _passiveForceLengthCurveProp;
	rdArrayPtrs<rdFunction> &_passiveForceLengthCurve;

	rdPropertyObjArray _forceVelocityCurveProp;
	rdArrayPtrs<rdFunction> &_forceVelocityCurve;

	rdPropertyStrArray _groupNamesProp;
	rdArray<std::string>& _groupNames;
	rdArray<simmMuscleGroup*> _groups;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	simmMuscle();
	simmMuscle(DOMElement *aElement);
	simmMuscle(const simmMuscle &aMuscle);
	virtual ~simmMuscle();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;

#ifndef SWIG
	simmMuscle& operator=(const simmMuscle &aMuscle);
#endif

   void simmMuscle::copyData(const simmMuscle &aMuscle);

#ifndef SWIG
	const rdArrayPtrs<simmMusclePoint>& getAttachmentArray() const { return _attachments; }
#endif

	virtual void computeActuation() { }
	virtual void apply() { }

	double getLength(simmKinematicsEngine* ke) const;
	const rdArray<std::string>& getGroupNames() const { return _groupNames; }

	/* Register types to be used when reading an simmModel object from xml file. */
	static void registerTypes();

	void scale(const suScaleSet& aScaleSet);
	void setup(simmModel* model, simmKinematicsEngine* ke);

	void writeSIMM(std::ofstream& out) const;

	void peteTest(simmKinematicsEngine* ke) const;

protected:

private:
	void setNull();
	void setupProperties();
//=============================================================================
};	// END of class simmMuscle
//=============================================================================
//=============================================================================

#endif // __simmMuscle_h__


