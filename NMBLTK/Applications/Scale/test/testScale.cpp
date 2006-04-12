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
							"CrouchGaitSP.jnt",
							"CrouchGaitSP.msl",
							"CrouchGaitSP.xml",
							"CrouchGaitScale.xml"

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

	if (!subject->isDefaultMarkerPlacementParams()){
		simmMarkerPlacementParams& markerPlacementParams = subject->getMarkerPlacementParams();
		// Update markers to correspond to those specified in IKParams block
		model->updateMarkers(markerPlacementParams.getMarkerSet());


		/**
		* Load the static pose marker file, and average all the
		* frames in the user-specified time range.
		*/
		simmMarkerData staticPose(markerPlacementParams.getStaticPoseFilename());
		// Convert read trc fil into "common" rdStroage format
		rdStorage inputStorage;
		// Convert read trc fil into "common" rdStroage format
		staticPose.makeRdStorage(inputStorage);
		// Convert the marker data into the model's units.
		double startTime, endTime;
		markerPlacementParams.getTimeRange(startTime, endTime);
		staticPose.averageFrames(0.01, startTime, endTime);
		staticPose.convertToUnits(model->getLengthUnits());

		/* Delete any markers from the model that are not in the static
		* pose marker file.
		*/
		model->deleteUnusedMarkers(staticPose.getMarkerNames());

		/* Now solve the static pose, by faking it as an IKTrial */
		simmIKTrialParams options;
		options.setStartTime(startTime);
		options.setEndTime(startTime);
		options.setIncludeMarkers(true);

		// Create target
		simmInverseKinematicsTarget *target = new simmInverseKinematicsTarget(*model, inputStorage);
		// Create solver
		simmIKSolverImpl *ikSolver = new simmIKSolverImpl(*target, subject->getIKParams());
		// Solve
		rdStorage	outputStorage;
		ikSolver->solveFrames(options, inputStorage, outputStorage);

		delete ikSolver;
		delete target;
	}
	else {
		cout << "Marker placement parameters not set. No markers have been moved." << endl;
	}
	delete subject;

	/* Compare results with standard*/
	bool success = true;
	for (int i=0; i < 4 && success; i++){
		string command = "cmp "+filesToCompare[i]+" "+"std_"+filesToCompare[i];
		success = success && (system(command.c_str())==0);
	}
	cout << "Path used = " << getenv("PATH") << endl;

	return (success?0:1);
}
	
