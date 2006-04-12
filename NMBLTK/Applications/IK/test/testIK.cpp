// testIK.cpp
// Author: Ayman Habib based on Peter Loan's version
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


// INCLUDES
#include <string>
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Tools/rdStorage.h>
#include <NMBLTK/Tools/suScaleSet.h>
#include <NMBLTK/Simulation/SIMM/simmModel.h>
#include <NMBLTK/Simulation/SIMM/simmKinematicsEngine.h>
#include <NMBLTK/Simulation/SIMM/simmMarkerSet.h>
#include <NMBLTK/Simulation/SIMM/simmSubject.h>
#include <NMBLTK/Simulation/SIMM/simmMarkerData.h>
#include <NMBLTK/Simulation/SIMM/simmMotionData.h>
#include <NMBLTK/Applications/IK/simmIKSolverImpl.h>
#include <NMBLTK/Applications/Scale/simmScalerImpl.h>
#include <NMBLTK/Applications/IK/simmInverseKinematicsTarget.h>

using namespace std;

string filesToCompare[] = {
	"walk1.mot"
};
//______________________________________________________________________________
/**
* Test program to read SIMM model elements from an XML file.
*
* @param argc Number of command line arguments (should be 1).
* @param argv Command line arguments:  simmReadXML inFile
*/
int main(int argc,char **argv)
{

	// Construct model and read parameters file
	simmSubject* subject = new simmSubject("CrouchGait.xml");
	simmModel* model = subject->createModel();

	simmScalingParams& params = subject->getScalingParams();
	ScalerInterface *scaler = new simmScalerImpl(*model);

	if (!scaler->scaleModel(params.getScaleSet(*model), params.getPreserveMassDist(), subject->getMass()))
	{
		cout << "===ERROR===: Unable to scale generic model." << endl;
		return 0;
	}
	params.writeOutputFiles(model);

	delete scaler;

	//----------------------- Marker placement section
	{
		simmMarkerPlacementParams& markerPlacementParams = subject->getMarkerPlacementParams();
		// Update markers to correspond to those specified in IKParams block 
		model->updateMarkers(markerPlacementParams.getMarkerSet());

		/* Load the static pose marker file, and average all the
		* frames in the user-specified time range.
		*/
		simmMarkerData staticPose(markerPlacementParams.getStaticPoseFilename());
		// Convert the marker data into the model's units.
		double startTime, endTime;
		markerPlacementParams.getTimeRange(startTime, endTime);
		staticPose.averageFrames(0.01, startTime, endTime);
		staticPose.convertToUnits(model->getLengthUnits());

		/* Delete any markers from the model that are not in the static
		* pose marker file.
		*/
		model->deleteUnusedMarkers(staticPose.getMarkerNames());

		/* Now solve the static pose by making a simmIKTrialParams*/
		simmIKTrialParams options;
		options.setStartTime(startTime);
		options.setEndTime(startTime);
		options.setIncludeMarkers(true);

		// Convert read trc fil into "common" rdStroage format
		rdStorage inputStorage;
		staticPose.makeRdStorage(inputStorage);
		// Create target
		simmInverseKinematicsTarget *target = new simmInverseKinematicsTarget(*model, inputStorage);
		// Create solver
		simmIKSolverImpl *ikSolver = new simmIKSolverImpl(*target, subject->getIKParams());
		// Solve
		rdStorage	outputStorage; outputStorage.setName(staticPose.getFileName());
		ikSolver->solveFrames(options, inputStorage, outputStorage);

		model->moveMarkersToCloud(staticPose);

		markerPlacementParams.writeOutputFiles(model, outputStorage);

		delete ikSolver;
		delete target;
	}
	//--------------------- IK proper section
	{
		try 
		{			// Update markers to correspond to those specified in IKParams block, potentially adding new ones
			model->updateMarkers(subject->getIKParams().getMarkerSet());
			// Initialize coordinates based on user input
			model->updateCoordinates(subject->getIKParams().getCoordinateSet());
			// Get trial params
			simmIKTrialParams& trialParams = subject->getIKParams().getTrialParams(0);
			// Handle coordinates file
			simmMotionData* coordinateValues = trialParams.getCoordinateValues(*model);

			// Setup IK problem for trial
			// We need simmInverseKinematicsTarget, iksolver (simmIKSolverImpl)
			// Create simmMarkerData Object from trc file of experimental motion data
			simmMarkerData motionTrialData(trialParams.getMarkerDataFilename());
			motionTrialData.convertToUnits(model->getLengthUnits());
			rdStorage inputStorage;
			// Convert read trc fil into "common" rdStroage format
			motionTrialData.makeRdStorage(inputStorage);

			if (coordinateValues != 0) {
				/* Adjust the user-defined start and end times to make sure they are in the
				* range of the marker data. This must be done so that you only look in the
				* coordinate data for rows that will actually be solved.
				*/
				double firstStateTime = inputStorage.getFirstTime();
				double lastStateTime = inputStorage.getLastTime();
				double startTime = max<double>(firstStateTime, trialParams.getStartTime());
				double endTime = min<double>(lastStateTime, trialParams.getEndTime());

				/* Add the coordinate data to the marker data. There must be a row of
				* corresponding coordinate data for every row of marker data that will
				* be solved, or it is a fatal error.
				*/
				coordinateValues->addToRdStorage(inputStorage, startTime, endTime);
			}
			// Create target
			simmInverseKinematicsTarget *target = new simmInverseKinematicsTarget(*model, inputStorage);
			// Create solver
			simmIKSolverImpl *ikSolver = new simmIKSolverImpl(*target, subject->getIKParams());
			// Solve
			rdStorage	outputStorage; 
			ikSolver->solveFrames(trialParams, inputStorage, outputStorage);
			outputStorage.setWriteSIMMHeader(true);
			outputStorage.print(trialParams.getOutputMotionFilename().c_str());

			delete coordinateValues;
			delete ikSolver;
			delete target;
		}
		catch (rdException &x)
		{
			x.print(cout);
			cout << "Press Return to continue." << endl;
			cout.flush();
			int c = getc( stdin );
			return 1;
		}
	}
	delete subject;

	/* Compare results with standard*/
	bool success = true;
	for (int i=0; i < 1 && success; i++){
		string command = "cmp "+filesToCompare[i]+" "+"std_"+filesToCompare[i];
		success = success && (system(command.c_str())==0);
	}

	return (success?0:1);
}

