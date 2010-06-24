#ifndef __MarkerData_h__
#define __MarkerData_h__

// MarkerData.h
// Author: Peter Loan
/*
 * Copyright (c)  2006, Stanford University. All rights reserved. 
* Use of the OpenSim software in source form is permitted provided that the following
* conditions are met:
* 	1. The software is used only for non-commercial research and education. It may not
*     be used in relation to any commercial activity.
* 	2. The software is not distributed or redistributed.  Software distribution is allowed 
*     only through https://simtk.org/home/opensim.
* 	3. Use of the OpenSim software or derivatives must be acknowledged in all publications,
*      presentations, or documents describing work in which OpenSim or derivatives are used.
* 	4. Credits to developers may not be removed from executables
*     created from modifications of the source.
* 	5. Modifications of source code must retain the above copyright notice, this list of
*     conditions and the following disclaimer. 
* 
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
*  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
*  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
*  SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
*  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
*  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
*  OR BUSINESS INTERRUPTION) OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
*  WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


// INCLUDE
#include <iostream>
#include <string>
#include "osimCommonDLL.h"
#include "Object.h"
#include "Storage.h"
#include "ArrayPtrs.h"
#include "MarkerFrame.h"
#include "Units.h"

namespace OpenSim {

//=============================================================================
//=============================================================================
/**
 * A class implementing a sequence of marker frames from a TRC/TRB file.
 *
 * @author Peter Loan
 * @version 1.0
 */
class OSIMCOMMON_API MarkerData : public Object
{

//=============================================================================
// DATA
//=============================================================================
private:
	int _numFrames;
	int _numMarkers;
	int _firstFrameNumber;
	double _dataRate;
	double _cameraRate;
	double _originalDataRate;
	int _originalStartFrame;
	int _originalNumFrames;
	std::string _fileName;
	Units _units;
	Array<std::string> _markerNames;
	ArrayPtrs<MarkerFrame> _frames;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	MarkerData();
	MarkerData(const std::string& aFileName) SWIG_DECLARE_EXCEPTION;
	virtual ~MarkerData();
	void findFrameRange(double aStartTime, double aEndTime, int& rStartFrame, int& rEndFrame) const;
	void averageFrames(double aThreshold = -1.0, double aStartTime = -SimTK::Infinity, double aEndTime = SimTK::Infinity);
	const std::string& getFileName() const { return _fileName; }
	void makeRdStorage(Storage& rStorage);
	const MarkerFrame& getFrame(int aIndex) const;
	int getMarkerIndex(const std::string& aName) const;
	const Units& getUnits() const { return _units; }
	void convertToUnits(const Units& aUnits);
	const Array<std::string>& getMarkerNames() const { return _markerNames; }
	int getNumFrames() const { return _numFrames; }
	double getStartFrameTime() const;
	double getLastFrameTime() const;
	double getDataRate() const { return _dataRate; }
	double getCameraRate() const { return _cameraRate; }

private:
	void readTRCFile(const std::string& aFileName, MarkerData& aSMD);
	void readTRCFileHeader(std::ifstream &in, const std::string& aFileName, MarkerData& aSMD);
	void readTRBFile(const std::string& aFileName, MarkerData& aSMD);

//=============================================================================
};	// END of class MarkerData
//=============================================================================
//=============================================================================

} // end of namespace OpenSim

#endif // __MarkerData_h__


