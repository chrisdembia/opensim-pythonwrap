#ifndef __simmSubject_h__
#define __simmSubject_h__

// simmSubject.h
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
#include <NMBLTK/Tools/rdPropertyObj.h>
#include <NMBLTK/Tools/rdPropertyStr.h>
#include <NMBLTK/Tools/rdPropertyDbl.h>
#include <NMBLTK/Tools/rdStorage.h>
#include <NMBLTK/Tools/rdXMLDocument.h>
#include <NMBLTK/Simulation/rdSimulationDLL.h>
#include <NMBLTK/Simulation/SIMM/simmModel.h>
#include <NMBLTK/Simulation/SIMM/simmGenericModelParams.h>
#include <NMBLTK/Simulation/SIMM/simmScalingParams.h>
#include <NMBLTK/Simulation/SIMM/simmMarkerPlacementParams.h>
#include <NMBLTK/Simulation/SIMM/simmIKParams.h>

//=============================================================================
//=============================================================================
/**
 * A class implementing a set of parameters describing how to scale a model
 * to fit a subject, place markers on it, and do IK on one or more motion
 * trials.
 *
 * @author Peter Loan
 * @version 1.0
 */
class RDSIMULATION_API simmSubject : public rdObject  
{

//=============================================================================
// DATA
//=============================================================================
private:
	// simmModel* _model;

protected:

	rdPropertyDbl _massProp;
	double &_mass;

	rdPropertyDbl _heightProp;
	double &_height;

	rdPropertyDbl _ageProp;
	double &_age;

	rdPropertyStr _notesProp;
	std::string &_notes;

	rdPropertyObj _genericModelParamsProp;
	simmGenericModelParams &_genericModelParams;

	rdPropertyObj _scalingParamsProp;
	simmScalingParams &_scalingParams;

	rdPropertyObj _markerPlacementParamsProp;
	simmMarkerPlacementParams &_markerPlacementParams;

	rdPropertyObj _IKParamsProp;
	simmIKParams &_IKParams;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	simmSubject();
	simmSubject(const std::string &aFileName);
	simmSubject(DOMElement *aElement);
	simmSubject(const simmSubject &aSubject);
	virtual ~simmSubject();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;

#ifndef SWIG
	simmSubject& operator=(const simmSubject &aSubject);
#endif
    void simmSubject::copyData(const simmSubject &aSubject);

	simmModel* createModel();
	/* Query the subject for different parameters */
	simmGenericModelParams& getGenericModelParams()
	{
		return _genericModelParams;
	}

	simmScalingParams& getScalingParams()
	{
		return _scalingParams;
	}

	simmMarkerPlacementParams& getMarkerPlacementParams()
	{
		return _markerPlacementParams;
	}

	simmIKParams& getIKParams()
	{
		return _IKParams;
	}

	double getMass() const { return _mass; }

	bool isDefaultGenericModelParams() { return _genericModelParamsProp.getUseDefault(); }
	bool isDefaultScalingParams() { return _scalingParamsProp.getUseDefault(); }
	bool isDefaultMarkerPlacementParams() { return _markerPlacementParamsProp.getUseDefault(); }
	bool isDefaultIKParams() { return _IKParamsProp.getUseDefault(); }
	/* Register types to be used when reading a simmSubject object from xml file. */
	static void registerTypes();

	void peteTest() const;

protected:

private:
	void setNull();
	void setupProperties();
//=============================================================================
};	// END of class simmSubject
//=============================================================================
//=============================================================================

#endif // __simmSubject_h__


