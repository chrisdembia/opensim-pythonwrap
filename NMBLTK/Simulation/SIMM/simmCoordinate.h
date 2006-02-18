#ifndef __simmCoordinate_h__
#define __simmCoordinate_h__

// simmCoordinate.h
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
#include <NMBLTK/Tools/rdPropertyBool.h>
#include <NMBLTK/Tools/rdPropertyDbl.h>
#include <NMBLTK/Tools/rdPropertyDblArray.h>
#include <NMBLTK/Tools/rdPropertyStr.h>
#include <NMBLTK/Tools/rdPropertyStrArray.h>
#include <NMBLTK/Tools/rdPropertyObjArray.h>
#include <NMBLTK/Tools/rdStorage.h>
#include <NMBLTK/Tools/rdXMLDocument.h>
#include <NMBLTK/Tools/rdFunction.h>
#include "suCoordinate.h"
#include "simmPath.h"

class simmJoint;
class simmKinematicsEngine;

//=============================================================================
//=============================================================================
/**
 * A class implementing a SIMM generalized coordinate.
 *
 * @author Peter Loan
 * @version 1.0
 */
class RDSIMULATION_API simmCoordinate : public suCoordinate  
{
//=============================================================================
// DATA
//=============================================================================
public:
	typedef struct
	{
		int restraintFuncNum;
		int minRestraintFuncNum;
		int maxRestraintFuncNum;
	} sdfastCoordinateInfo;

	sdfastCoordinateInfo _sdfastInfo;

protected:
	rdPropertyDbl _defaultValueProp;
	double &_defaultValue;

	/* value is specified as a string, so the user can specify
	 * options like "fromFile" which means to read the value
	 * from a coordinate file.
	 */
	rdPropertyStr _valueStrProp;
	std::string &_valueStr;
	double _value;

	rdPropertyDbl _toleranceProp;
	double &_tolerance;

	rdPropertyDbl _PDStiffnessProp;
	double &_PDStiffness;

	rdPropertyDbl _IKweightProp;
	double &_IKweight;

	rdPropertyDblArray _rangeProp;
	rdArray<double>& _range;

	rdPropertyStrArray _keysProp;
	rdArray<std::string>& _keys;

	rdPropertyBool _clampedProp;
	bool &_clamped;

	rdPropertyBool _lockedProp;
	bool &_locked;

	rdPropertyObjArray _restraintFunctionProp;
	rdArrayPtrs<rdFunction> &_restraintFunction;

	rdPropertyObjArray _minRestraintFunctionProp;
	rdArrayPtrs<rdFunction> &_minRestraintFunction;

	rdPropertyObjArray _maxRestraintFunctionProp;
	rdArrayPtrs<rdFunction> &_maxRestraintFunction;

	rdPropertyBool _restraintActiveProp;
	bool &_restraintActive;

	rdArray<simmJoint*> _jointList; // list of joints that use this coordinate
	rdArray<simmPath*> _pathList; // list of paths that use this coordinate

	int _RTtype; // rotational or translational (based on the DOFs it's used in)

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	simmCoordinate();
	simmCoordinate(DOMElement *aElement);
	simmCoordinate(const simmCoordinate &aCoordinate);
	virtual ~simmCoordinate();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;

	simmCoordinate& operator=(const simmCoordinate &aCoordinate);
   void simmCoordinate::copyData(const simmCoordinate &aCoordinate);

   void addJointToList(simmJoint* aJoint) { _jointList.append(aJoint); }
   void addPathToList(simmPath* aPath) { _pathList.append(aPath); }
   void setup(simmKinematicsEngine* aEngine);
	bool setValue(double value);
	bool setValue(std::string& aValueStr);
	double getValue() const { return _value; }
	const std::string& getValueStr() const { return _valueStr; }
	double getTolerance() const { return _tolerance; }
	double getDefaultValue() const { return _defaultValue; }
	double getPDStiffness() const { return _PDStiffness; }
	double getIKweight() const { return _IKweight; }
	void getRange(double range[2]) const { range[0] = _range[0]; range[1] = _range[1]; }
	virtual double getRangeMin() const { return _range[0]; }
	virtual double getRangeMax() const { return _range[1]; }
	void getKeys(std::string keys[]) const;
	const rdArray<simmJoint*>& getJointList() const { return _jointList; }
	const rdArray<simmPath*>& getPathList() const { return _pathList; }
	bool isUsedInModel(void) { if (getJointList().getSize() > 0) return true; else return false; }
	bool isClamped(void) const { return _clamped; }
	bool isLocked(void) const { return _locked; }
	void setLocked(bool aState) { _locked = aState; }
	bool isRestraintActive(void) const { return _restraintActive; }
	rdFunction* getRestraintFunction(void) const;
	rdFunction* getMinRestraintFunction(void) const;
	rdFunction* getMaxRestraintFunction(void) const;
	void updateFromCoordinate(const simmCoordinate &aCoordinate);

	void writeSIMM(std::ofstream& out, int& aFunctionIndex) const;

	void peteTest(void) const;

protected:

private:
	void setNull(void);
	void setupProperties(void);
	void determineType(simmKinematicsEngine* aEngine);

//=============================================================================
};	// END of class simmCoordinate
//=============================================================================
//=============================================================================

typedef RDSIMULATION_API rdArrayPtrs<simmCoordinate> simmCoordinateArray;

#endif // __simmCoordinate_h__


