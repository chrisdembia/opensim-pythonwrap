#ifndef __simmJoint_h__
#define __simmJoint_h__

// simmJoint.h
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
#include <NMBLTK/Tools/rdPropertyObjArray.h>
#include <NMBLTK/Tools/rdPropertyStrArray.h>
#include <NMBLTK/Tools/rdStorage.h>
#include <NMBLTK/Tools/rdArrayPtrs.h>
#include <NMBLTK/Tools/rdTransform.h>
#include <NMBLTK/Tools/rdXMLDocument.h>
#include <NMBLTK/Tools/suScaleSet.h>
#include "dp.h"
#include "simmCoordinate.h"
#include "simmRotationDof.h"
#include "simmTranslationDof.h"
#include "simmBody.h"
#include "simmStep.h"
#include "simmSdfastBody.h"

class simmKinematicsEngine;
class simmModel;

//=============================================================================
//=============================================================================
/**
 * A class implementing a SIMM joint.
 *
 * @author Peter Loan
 * @version 1.0
 */
class RDSIMULATION_API simmJoint : public rdObject  
{

//=============================================================================
// DATA
//=============================================================================
public:
	typedef struct
	{
		bool used;
		std::string name;
		dpJointType type;
		int index;
		simmStep::Direction direction;
		std::string inbname;
		std::string outbname;
		bool closesLoop;
	} sdfastJointInfo;

	sdfastJointInfo _sdfastInfo;

protected:
	rdPropertyStrArray _bodiesProp;
	rdArray<std::string>& _bodies;

	rdPropertyObjArray _dofsProp;
	rdArrayPtrs<simmDof>& _dofs;

   simmBody *_childBody;
   simmBody *_parentBody;

	rdTransform _forwardTransform;
	rdTransform _inverseTransform;

	bool _transformsValid;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	simmJoint();
	simmJoint(DOMElement *aElement);
	simmJoint(const simmJoint &aJoint);
	virtual ~simmJoint();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;

   void setup(simmKinematicsEngine* aEngine);

	simmJoint& operator=(const simmJoint &aJoint);
   void copyData(const simmJoint &aJoint);

	void invalidate() { _transformsValid = false; }
	rdArray<std::string>& getBodyNames() const { return _bodies; }
	rdArrayPtrs<simmDof>& getDofs() const { return _dofs; }
	simmBody* getChildBody() const { return _childBody; }
	simmBody* getParentBody() const { return _parentBody; }
	const rdTransform& getForwardTransform();
	const rdTransform& getInverseTransform();
	bool isCoordinateUsed(simmCoordinate* aCoordinate) const;
	void identifyDpType(simmModel* aModel);
	void makeSdfastJoint(std::ofstream& out, rdArrayPtrs<simmSdfastBody>& sdfastBodies, int* dofCount, int* constrainedCount, bool writeFile);
	void scale(const suScaleSet& aScaleSet);

	void writeSIMM(std::ofstream& out, int& aFunctionIndex) const;

	void peteTest();

private:
	void setNull();
	void setupProperties();
	void calcTransforms();
	bool isSdfastCompatible(void);
   bool hasXYZAxes(void);
	simmRotationDof* findNthFunctionRotation(int n) const;
	simmTranslationDof* findNthFunctionTranslation(int n) const;
	simmTranslationDof* getTranslationDof(int axis) const;
	simmTranslationDof* findMatchingTranslationDof(simmRotationDof* rotDof);
	void makeSdfastWeld(std::ofstream& out, int* dofCount, int* constrainedCount, bool writeFile);
	void makeSdfastPin(std::ofstream& out, int* dofCount, int* constrainedCount, bool writeFile);
	void makeSdfastSlider(std::ofstream& out, int* dofCount, int* constrainedCount, bool writeFile);
	void makeSdfastPlanar(std::ofstream& out, int* dofCount, int* constrainedCount, bool writeFile);
	void makeSdfastUniversal(std::ofstream& out, int* dofCount, int* constrainedCount, bool writeFile);
	void makeSdfastCylindrical(std::ofstream& out, int* dofCount, int* constrainedCount, bool writeFile);
	void makeSdfastGimbal(std::ofstream& out, int* dofCount, int* constrainedCount, bool writeFile);
	void makeSdfastBushing(std::ofstream& out, int* dofCount, int* constrainedCount, bool writeFile);

//=============================================================================
};	// END of class simmJoint
//=============================================================================
//=============================================================================

typedef rdArray<simmJoint*> SimmJointList;

#endif // __simmJoint_h__


