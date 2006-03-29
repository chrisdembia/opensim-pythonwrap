// simmMarkerPlacementParams.cpp
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


//=============================================================================
// INCLUDES
//=============================================================================
#include "simmMarkerPlacementParams.h"
#include "simmMarkerData.h"
#include "simmMotionData.h"

//=============================================================================
// STATICS
//=============================================================================
using namespace std;

//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Default constructor.
 */
simmMarkerPlacementParams::simmMarkerPlacementParams() :
   _markerFileName(_markerFileNameProp.getValueStr()),
	_timeRange(_timeRangeProp.getValueDblArray()),
   _coordinateFileName(_coordinateFileNameProp.getValueStr()),
	_coordinateSet((rdArrayPtrs<simmCoordinate>&)_coordinateSetProp.getValueObjArray()),
	_markerSet((rdArrayPtrs<simmMarker>&)_markerSetProp.getValueObjArray()),
	_outputJointFileName(_outputJointFileNameProp.getValueStr()),
	_outputMuscleFileName(_outputMuscleFileNameProp.getValueStr()),
	_outputModelFileName(_outputModelFileNameProp.getValueStr()),
	_outputMarkerFileName(_outputMarkerFileNameProp.getValueStr()),
	_outputMotionFileName(_outputMotionFileNameProp.getValueStr())
{
	setNull();
}
//_____________________________________________________________________________
/**
 * Constructor from an XML node
 */
simmMarkerPlacementParams::simmMarkerPlacementParams(DOMElement *aElement) :
   rdObject(aElement),
   _markerFileName(_markerFileNameProp.getValueStr()),
	_timeRange(_timeRangeProp.getValueDblArray()),
   _coordinateFileName(_coordinateFileNameProp.getValueStr()),
	_coordinateSet((rdArrayPtrs<simmCoordinate>&)_coordinateSetProp.getValueObjArray()),
	_markerSet((rdArrayPtrs<simmMarker>&)_markerSetProp.getValueObjArray()),
	_outputJointFileName(_outputJointFileNameProp.getValueStr()),
	_outputMuscleFileName(_outputMuscleFileNameProp.getValueStr()),
	_outputModelFileName(_outputModelFileNameProp.getValueStr()),
	_outputMarkerFileName(_outputMarkerFileNameProp.getValueStr()),
	_outputMotionFileName(_outputMotionFileNameProp.getValueStr())
{
	setNull();
	updateFromXMLNode();
}

//_____________________________________________________________________________
/**
 * Destructor.
 */
simmMarkerPlacementParams::~simmMarkerPlacementParams()
{
}

//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aMarkerPlacementParams simmMarkerPlacementParams to be copied.
 */
simmMarkerPlacementParams::simmMarkerPlacementParams(const simmMarkerPlacementParams &aMarkerPlacementParams) :
   rdObject(aMarkerPlacementParams),
   _markerFileName(_markerFileNameProp.getValueStr()),
	_timeRange(_timeRangeProp.getValueDblArray()),
   _coordinateFileName(_coordinateFileNameProp.getValueStr()),
	_coordinateSet((rdArrayPtrs<simmCoordinate>&)_coordinateSetProp.getValueObjArray()),
	_markerSet((rdArrayPtrs<simmMarker>&)_markerSetProp.getValueObjArray()),
	_outputJointFileName(_outputJointFileNameProp.getValueStr()),
	_outputMuscleFileName(_outputMuscleFileNameProp.getValueStr()),
	_outputModelFileName(_outputModelFileNameProp.getValueStr()),
	_outputMarkerFileName(_outputMarkerFileNameProp.getValueStr()),
	_outputMotionFileName(_outputMotionFileNameProp.getValueStr())
{
	setupProperties();
	copyData(aMarkerPlacementParams);
}
//_____________________________________________________________________________
/**
 * Copy this marker placement params and return a pointer to the copy.
 * The copy constructor for this class is used.
 *
 * @return Pointer to a copy of this simmMarkerPlacementParams.
 */
rdObject* simmMarkerPlacementParams::copy() const
{
	simmMarkerPlacementParams *markerPlacementParams = new simmMarkerPlacementParams(*this);
	return(markerPlacementParams);
}
//_____________________________________________________________________________
/**
 * Copy this simmMarkerPlacementParams and modify the copy so that it is consistent
 * with a specified XML element node.
 *
 * The copy is constructed by first using
 * simmMarkerPlacementParams::simmMarkerPlacementParams(DOMElement*) in order to establish the
 * relationship of the simmMarkerPlacementParams object with the XML node. Then, the
 * assignment operator is used to set all data members of the copy to the
 * values of this simmMarkerPlacementParams object. Finally, the data members of the
 * copy are updated using simmMarkerPlacementParams::updateFromXMLNode().
 *
 * @param aElement XML element. 
 * @return Pointer to a copy of this simmMarkerPlacementParams.
 */
rdObject* simmMarkerPlacementParams::copy(DOMElement *aElement) const
{
	simmMarkerPlacementParams *markerPlacementParams = new simmMarkerPlacementParams(aElement);
	*markerPlacementParams = *this;
	markerPlacementParams->updateFromXMLNode();
	return(markerPlacementParams);
}

void simmMarkerPlacementParams::copyData(const simmMarkerPlacementParams &aMarkerPlacementParams)
{
	_markerFileName = aMarkerPlacementParams._markerFileName;
	_timeRange = aMarkerPlacementParams._timeRange;
	_coordinateFileName = aMarkerPlacementParams._coordinateFileName;
	_coordinateSet = aMarkerPlacementParams._coordinateSet;
	_markerSet = aMarkerPlacementParams._markerSet;
	_outputJointFileName = aMarkerPlacementParams._outputJointFileName;
	_outputMuscleFileName = aMarkerPlacementParams._outputMuscleFileName;
	_outputModelFileName = aMarkerPlacementParams._outputModelFileName;
	_outputMarkerFileName = aMarkerPlacementParams._outputMarkerFileName;
	_outputMotionFileName = aMarkerPlacementParams._outputMotionFileName;
}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set the data members of this simmMarkerPlacementParams to their null values.
 */
void simmMarkerPlacementParams::setNull()
{
	setupProperties();
	setType("MarkerPlacementParameters");
	setName("");
}
//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void simmMarkerPlacementParams::setupProperties()
{
	_markerFileNameProp.setName("markerFile");
	_propertySet.append(&_markerFileNameProp);

	const double defaultTimeRange[] = {-1.0, -1.0};
	_timeRangeProp.setName("timeRange");
	_timeRangeProp.setValue(2, defaultTimeRange);
	_propertySet.append(&_timeRangeProp);

	_coordinateFileNameProp.setName("coordinateFile");
	_propertySet.append(&_coordinateFileNameProp);

	_coordinateSetProp.setName("CoordinateSet");
	rdArrayPtrs<rdObject> cs;
	_coordinateSetProp.setValue(cs);
	_propertySet.append(&_coordinateSetProp);

	_markerSetProp.setName("MarkerSet");
	rdArrayPtrs<rdObject> ms;
	_markerSetProp.setValue(ms);
	_propertySet.append(&_markerSetProp);

	_outputJointFileNameProp.setName("outputJointFile");
	_propertySet.append(&_outputJointFileNameProp);

	_outputMuscleFileNameProp.setName("outputMuscleFile");
	_propertySet.append(&_outputMuscleFileNameProp);

	_outputModelFileNameProp.setName("outputModelFile");
	_propertySet.append(&_outputModelFileNameProp);

	_outputMarkerFileNameProp.setName("outputMarkerFile");
	_propertySet.append(&_outputMarkerFileNameProp);

	_outputMotionFileNameProp.setName("outputMotionFile");
	_propertySet.append(&_outputMotionFileNameProp);
}

simmMarkerPlacementParams& simmMarkerPlacementParams::operator=(const simmMarkerPlacementParams &aMarkerPlacementParams)
{
	// BASE CLASS
	rdObject::operator=(aMarkerPlacementParams);

	copyData(aMarkerPlacementParams);

	return(*this);
}

/* This method creates a simmMotionTrial instance with the markerFile and timeRange
parameters. It also creates a simmMotionData instance with the coordinateFile
parameter. Then it calls model->updateCoordinateSet() with the coordinate set
parameters. Then it calls model->updateMarkerSet() with the marker set parameters.
Then it calls model->solveInverseKinematics(simmMotionTrial) to fit the model to
the static pose. Then it calls model->moveMarkers(simmMotionTrial) which uses the
current model pose to relocate all non-fixed markers according to their locations
in the simmMotionTrial. Then it writes the output files selected by the user.
*/
bool simmMarkerPlacementParams::processModel(simmModel* aModel)
{
	cout << endl << "Step 3: Placing markers on model" << endl;

	simmMotionData* solvedStatic = NULL;

	try
	{
		/* Load the coordinate file. */
		if (!_coordinateFileNameProp.getUseDefault())
		{
			simmMotionData coordinateValues(_coordinateFileName);

			/* For each coordinate whose "value" field the user specified
			 * as "fromFile", read the value from the first frame in the
			 * coordinate file (a SIMM motion file) and use it to overwrite
			 * the "fromFile" specification.
			 */
			if (coordinateValues.getNumColumns() > 0)
			{
				for (int i = 0; i < _coordinateSet.getSize(); i++)
				{
					if (_coordinateSet[i]->getValueStr() == "fromFile")
					{
						double newValue = coordinateValues.getValue(_coordinateSet[i]->getName(), 0);
						_coordinateSet[i]->setValue(newValue);
					}
				}

				/* Update the model with the coordinates specified
				 * by the user in the params section.
			    */
				aModel->updateCoordinates(_coordinateSet);
			}
		}

		/* Update the model with the markers specified in the params section. */
		aModel->updateMarkers(_markerSet);

		/* Load the static pose marker file, and average all the
		 * frames in the user-specified time range.
		 */
		simmMarkerData staticPose(_markerFileName);
		staticPose.averageFrames(0.01, _timeRange[0], _timeRange[1]);
		staticPose.convertToUnits(aModel->getLengthUnits());

		/* Delete any markers from the model that are not in the static
		 * pose marker file.
		 */
		aModel->deleteUnusedMarkers(staticPose.getMarkerNames());

		/* Now solve the static pose. */
		simmIKTrialParams options;
		options.setStartTime(_timeRange[0]);
		options.setEndTime(_timeRange[0]);
		options.setIncludeMarkers(true);

		solvedStatic = aModel->solveInverseKinematics(options, staticPose);

		/* Now move the non-fixed markers on the model so that they are coincident
		 * with the measured markers in the static pose. The model is already in
		 * the proper configuration so the coordinates do not need to be changed.
		 */
		aModel->moveMarkersToCloud(staticPose);
	}
	catch (rdException &x)
	{
		x.print(cout);

		if (solvedStatic)
			delete solvedStatic;

		cout << "Press any key to continue.. " << endl;
		cout.flush();
		int c = getc( stdin );
		return false;
	}

	// write output files, if names specified by the user
	if (!_outputJointFileNameProp.getUseDefault())
		aModel->writeSIMMJointFile(_outputJointFileName);

	if (!_outputMuscleFileNameProp.getUseDefault())
		aModel->writeSIMMMuscleFile(_outputMuscleFileName);

	if (!_outputModelFileNameProp.getUseDefault())
	{
		aModel->print(_outputModelFileName);
		cout << "Wrote model file " << _outputModelFileName << " from model " << aModel->getName() << endl;
	}

	if (!_outputMarkerFileNameProp.getUseDefault())
	{
		aModel->writeMarkerFile(_outputMarkerFileName);
		cout << "Wrote marker file " << _outputMarkerFileName << " from model " << aModel->getName() << endl;
	}

	if (!_outputMotionFileNameProp.getUseDefault())
		solvedStatic->writeSIMMMotionFile(_outputMotionFileName, aModel->getName());

	delete solvedStatic;

	return true;
}

void simmMarkerPlacementParams::peteTest() const
{
	int i;

	cout << "   MarkerPlacementParams: " << getName() << endl;
	cout << "      markerFileName: " << _markerFileName << endl;
	cout << "      timeRange: " << _timeRange << endl;
	cout << "      coordinateFileName: " << _coordinateFileName << endl;
	for (i = 0; i < _coordinateSet.getSize(); i++)
		_coordinateSet[i]->peteTest();
	for (i = 0; i < _markerSet.getSize(); i++)
		_markerSet[i]->peteTest();
	cout << "      outputJointFile: " << _outputJointFileName << endl;
	cout << "      outputMuscleFile: " << _outputMuscleFileName << endl;
	cout << "      outputModelFile: " << _outputModelFileName << endl;
	cout << "      outputMarkerFile: " << _outputMarkerFileName << endl;
	cout << "      outputMotionFile: " << _outputMotionFileName << endl;
}
