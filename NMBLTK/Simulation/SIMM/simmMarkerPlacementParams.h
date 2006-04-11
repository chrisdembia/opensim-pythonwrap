#ifndef __simmMarkerPlacementParams_h__
#define __simmMarkerPlacementParams_h__

// simmMarkerPlacementParams.h
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

#include "simmModel.h"
#include "simmCoordinate.h"
#include "simmMarker.h"

//=============================================================================
//=============================================================================
/**
 * A class implementing a set of parameters describing how to place markers
 * on a model (presumably after it has been scaled to fit a subject).
 *
 * @author Peter Loan
 * @version 1.0
 */
class RDSIMULATION_API simmMarkerPlacementParams : public rdObject  
{

//=============================================================================
// DATA
//=============================================================================
private:

protected:
	// name of marker file that contains marker locations in the static pose
	rdPropertyStr _markerFileNameProp;
	std::string &_markerFileName;

	// range of frames to average in static pose marker file, specified by time
	rdPropertyDblArray _timeRangeProp;
	rdArray<double> &_timeRange;

	// name of SIMM motion file that contains [optional] coordinates for the static pose
	rdPropertyStr _coordinateFileNameProp;
	std::string &_coordinateFileName;

	// coordinate set for updating coordinates in scaled model
	rdPropertyObjArray _coordinateSetProp;
	rdArrayPtrs<simmCoordinate> &_coordinateSet;

	// marker set for updating markers in scaled model
	rdPropertyObjArray _markerSetProp;
	rdArrayPtrs<simmMarker> &_markerSet;

	// name of SIMM joint file to write when done placing markers
	rdPropertyStr _outputJointFileNameProp;
	std::string &_outputJointFileName;

	// name of SIMM muscle file to write when done placing markers
	rdPropertyStr _outputMuscleFileNameProp;
	std::string &_outputMuscleFileName;

	// name of XML model file to write when done placing markers
	rdPropertyStr _outputModelFileNameProp;
	std::string &_outputModelFileName;

	// name of marker file to write when done placing markers
	rdPropertyStr _outputMarkerFileNameProp;
	std::string &_outputMarkerFileName;

	// name of motion file (containing solved static pose) when done placing markers
	rdPropertyStr _outputMotionFileNameProp;
	std::string &_outputMotionFileName;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	simmMarkerPlacementParams();
	simmMarkerPlacementParams(DOMElement *aElement);
	simmMarkerPlacementParams(const simmMarkerPlacementParams &aMarkerPlacementParams);
	virtual ~simmMarkerPlacementParams();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;

#ifndef SWIG
	simmMarkerPlacementParams& operator=(const simmMarkerPlacementParams &aMarkerPlacementParams);
#endif
   void simmMarkerPlacementParams::copyData(const simmMarkerPlacementParams &aMarkerPlacementParams);

	bool processModel(simmModel* aModel);


	void peteTest() const;

	bool isDefault() const;

	rdArrayPtrs<simmMarker> &getMarkerSet() const
	{
		return _markerSet;
	}
	std::string &getStaticPoseFilename() const
	{
		return _markerFileName;
	}
	void getTimeRange(double& startTime, double &endTime) const
	{
		startTime = _timeRange[0];
		endTime = _timeRange[1];
	}
	void writeOutputFiles(simmModel* aModel, rdStorage& aStorage) const;
protected:

private:
	void setNull();
	void setupProperties();
//=============================================================================
};	// END of class simmMarkerPlacementParams
//=============================================================================
//=============================================================================

#endif // __simmMarkerPlacementParams_h__


