#ifndef __simmIKTrialParams_h__
#define __simmIKTrialParams_h__

// simmIKTrialParams.h
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
#include <NMBLTK/Tools/rdPropertyDbl.h>
#include <NMBLTK/Tools/rdPropertyDblArray.h>
#include <NMBLTK/Tools/rdPropertyStr.h>
#include <NMBLTK/Tools/rdPropertyBool.h>
#include <NMBLTK/Tools/rdStorage.h>
#include <NMBLTK/Tools/rdXMLDocument.h>

class simmModel;
class simmCoordinate;

//=============================================================================
//=============================================================================
/**
 * A class implementing a set of parameters describing how to perform
 * a single inverse kinematics trial on a model and a marker set.
 *
 * @author Peter Loan
 * @version 1.0
 */
class RDSIMULATION_API simmIKTrialParams : public rdObject  
{

//=============================================================================
// DATA
//=============================================================================
private:

protected:
	// name of marker file that contains marker locations for IK solving
	rdPropertyStr _inputMarkerFileNameProp;
	std::string &_inputMarkerFileName;

	// name of motion file that contains coordinate values for IK solving
	rdPropertyStr _inputCoordinateFileNameProp;
	std::string &_inputCoordinateFileName;

	// name of input analog file that contains ground-reaction and EMG data
	rdPropertyStr _inputAnalogFileNameProp;
	std::string &_inputAnalogFileName;

	// range of frames to solve in marker file, specified by time
	rdPropertyDblArray _timeRangeProp;
	rdArray<double> &_timeRange;

	// cut-off frequency for low-pass smoothing of kinematics data
	rdPropertyDbl _kinematicsSmoothingProp;
	double &_kinematicsSmoothing;

	// cut-off frequency for low-pass smoothing of ground-reaction data
	rdPropertyDbl _groundReactionSmoothingProp;
	double &_groundReactionSmoothing;

	// whether or not to include marker trajectories in the output data
	rdPropertyBool _includeMarkersProp;
	bool &_includeMarkers;

	// name of motion file (containing solved static pose) when done placing markers
	rdPropertyStr _outputMotionFileNameProp;
	std::string &_outputMotionFileName;

	// comment string
	rdPropertyStr _notesProp;
	std::string &_notes;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	simmIKTrialParams();
	simmIKTrialParams(DOMElement *aElement);
	simmIKTrialParams(const simmIKTrialParams &aIKTrialParams);
	virtual ~simmIKTrialParams();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;

#ifndef SWIG
	simmIKTrialParams& operator=(const simmIKTrialParams &aIKTrialParams);
#endif
   void simmIKTrialParams::copyData(const simmIKTrialParams &aIKTrialParams);

	double getStartTime() const { return _timeRange[0]; }
	double getEndTime() const { return _timeRange[1]; }
	double getKinematicsSmoothing() const { return _kinematicsSmoothing; }
	double getGroundReactionSmoothing() const { return _groundReactionSmoothing; }
	bool getIncludeMarkers() const { return _includeMarkers; }

	void setStartTime(double aTime) { _timeRange[0] = aTime; }
	void setEndTime(double aTime) { _timeRange[1] = aTime; }
	void setIncludeMarkers(bool aValue) { _includeMarkers = aValue; }
	void findFrameRange(const rdStorage& aData, int& oStartFrame, int& oEndFrame) const;

	bool processTrial(simmModel& aModel, rdArrayPtrs<simmCoordinate>& aCoordinateSet);

	void peteTest() const;

protected:

private:
	void setNull();
	void setupProperties();

//=============================================================================
};	// END of class simmIKTrialParams
//=============================================================================
//=============================================================================

#endif // __simmIKTrialParams_h__


