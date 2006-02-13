#ifndef __simmScalingParams_h__
#define __simmScalingParams_h__

// simmScalingParams.h
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
#include <NMBLTK/Tools/rdPropertyDblArray.h>
#include <NMBLTK/Tools/rdPropertyObjArray.h>
#include <NMBLTK/Tools/rdPropertyBool.h>
#include <NMBLTK/Tools/rdPropertyStr.h>
#include <NMBLTK/Tools/rdPropertyStrArray.h>
#include <NMBLTK/Tools/rdStorage.h>
#include <NMBLTK/Tools/rdXMLDocument.h>
#include <NMBLTK/Tools/suScale.h>

#include "simmModel.h"
#include "simmMeasurement.h"

//=============================================================================
//=============================================================================
/**
 * A class implementing a set of parameters describing how to scale a model
 * to fit a subject.
 *
 * @author Peter Loan
 * @version 1.0
 */
class RDSIMULATION_API simmScalingParams : public rdObject  
{

//=============================================================================
// DATA
//=============================================================================
private:

protected:
	// order of the two scaling components: measurements and manual scaling
	rdPropertyStrArray _scalingOrderProp;
	rdArray<std::string>& _scalingOrder;

	// set of measurements to make on generic model and subject's static pose
	rdPropertyObjArray _measurementSetProp;
	rdArrayPtrs<simmMeasurement> &_measurementSet;

	// set of XYZ scale factors to use for manual scaling
	rdPropertyObjArray _scaleSetProp;
	rdArrayPtrs<suScale> &_scaleSet;

	// name of marker file that contains the static pose
	rdPropertyStr _markerFileNameProp;
	std::string &_markerFileName;

	// range of frames to average in static pose file, specified by time
	rdPropertyDblArray _timeRangeProp;
	rdArray<double> &_timeRange;

	// whether or not to preserve mass distribution in generic model file when scaling
	rdPropertyBool _preserveMassDistProp;
	bool &_preserveMassDist;

	// name of SIMM joint file to write when done scaling
	rdPropertyStr _outputJointFileNameProp;
	std::string &_outputJointFileName;

	// name of SIMM muscle file to write when done scaling
	rdPropertyStr _outputMuscleFileNameProp;
	std::string &_outputMuscleFileName;

	// name of XML model file to write when done scaling
	rdPropertyStr _outputModelFileNameProp;
	std::string &_outputModelFileName;

	// name of scale file to write when done scaling
	rdPropertyStr _outputScaleFileNameProp;
	std::string &_outputScaleFileName;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	simmScalingParams();
	simmScalingParams(DOMElement *aElement);
	simmScalingParams(const simmScalingParams &aScalingParams);
	virtual ~simmScalingParams();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;

	simmScalingParams& operator=(const simmScalingParams &aScalingParams);
   void simmScalingParams::copyData(const simmScalingParams &aScalingParams);

	bool processModel(simmModel* aModel);

	/* Register types to be used when reading a simmScalingParams object from xml file. */
	static void registerTypes();

	void peteTest() const;

protected:

private:
	void setNull();
	void setupProperties();
//=============================================================================
};	// END of class simmScalingParams
//=============================================================================
//=============================================================================

#endif // __simmScalingParams_h__


