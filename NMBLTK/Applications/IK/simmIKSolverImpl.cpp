#include <NMBLTK/Tools/rdArray.h>
#include <NMBLTK/Tools/rdStorage.h>
#include <NMBLTK/SQP/rdFSQP.h>
#include <NMBLTK/Simulation/SIMM/simmIKTrialParams.h>
#include <NMBLTK/Simulation/SIMM/simmKinematicsEngine.h>
#include "simmIKSolverImpl.h"
#include "simmInverseKinematicsTarget.h"

using namespace std;

simmIKSolverImpl::simmIKSolverImpl(nmblKinematicsEngine &aKinematicsEngine):
IKSolverInterface(aKinematicsEngine)
{
}

void simmIKSolverImpl::solveFrames(const simmIKTrialParams& aIKOptions, rdStorage& inputData, rdStorage& outputData)
{
	// Here we know we're in SIMM implementation so we may convert to the concrete simmKinematicsEngine class
	simmKinematicsEngine& engine = dynamic_cast<simmKinematicsEngine&> (_theKinematiceEngine);
	// Build optimization target
	simmInverseKinematicsTarget *target = new simmInverseKinematicsTarget(&engine, inputData);

	// Instantiate the optimizer
	rdFSQP *optimizer = new rdFSQP(target);

	// Set optimization convergence criteria/tolerance
	// Enable some Debugging here if needed
	optimizer->setPrintLevel(0);
	optimizer->setConvergenceCriterion(1.0E-4);	// Error in markers of .01
	optimizer->setMaxIterations(1000);

	/* Get names for unconstrained Qs (ones that will be solved). */
	rdArray<const string*> unconstrainedCoordinateNames(NULL);
   target->getUnconstrainedCoordinateNames(unconstrainedCoordinateNames);

	/* Get names for prescribed Qs (specified in input file). */
	rdArray<const string*> prescribedCoordinateNames(NULL);
   target->getPrescribedCoordinateNames(prescribedCoordinateNames);

	/* Get names for markers used for solving. */
	rdArray<const string*> markerNames(NULL);
	target->getOutputMarkerNames(markerNames);

	string resultsHeader = "time\t";
	for (int i = 0; i < unconstrainedCoordinateNames.getSize(); i++)
	{
		resultsHeader += *(unconstrainedCoordinateNames[i]);
		resultsHeader += "\t";
	}

	for (int i = 0; i < prescribedCoordinateNames.getSize(); i++)
	{
		resultsHeader += *(prescribedCoordinateNames[i]);
		resultsHeader += "\t";
	}

	string markerComponentNames[] = {"_px", "_py", "_pz"};
	// Include markers for visual verification in SIMM
	if (aIKOptions.getIncludeMarkers())
	{
		for (int i = 0; i < markerNames.getSize(); i++)
		{
			for (int j = 0; j < 3; j++)
			{
				resultsHeader += *(markerNames[i]);
				resultsHeader += markerComponentNames[j];
				resultsHeader += "\t";
			}
		}
	}
	outputData.setColumnLabels(resultsHeader.c_str());

	// Set the lower and upper bounds on the unconstrained Q array
	// TODO: shouldn't have to search for coordinates by name
	for (int i = 0; i < unconstrainedCoordinateNames.getSize(); i++)
	{
		suCoordinate* coord = _theKinematiceEngine.getCoordinate(*(unconstrainedCoordinateNames[i]));
		optimizer->setLowerBound(i, coord->getRangeMin());
		optimizer->setUpperBound(i, coord->getRangeMax());
	}

	// Main loop to set initial conditions and solve snapshots
	// At every step we use experimental data as a starting guess 
	rdArray<double> unconstrainedQGuess(0.0, unconstrainedCoordinateNames.getSize());	// Initial guess and work array
	rdArray<double> unconstrainedQSol(0.0, unconstrainedCoordinateNames.getSize());	// Solution array
	rdArray<double> experimentalMarkerLocations(0.0, markerNames.getSize() * 3);

	int startFrame = 0, endFrame = 1;
	double currentTime;

	/* Get the indices of the starting frame and the ending frame,
	 * based on the user-defined start/end times stored in
	 * the simmIKTrialOptions.
	 */
	aIKOptions.findFrameRange(inputData, startFrame, endFrame);

	if (endFrame - startFrame > 1)
		cout << "Solving frames " << startFrame + 1 << " to " << endFrame + 1 << " (time = " <<
		aIKOptions.getStartTime() << " to " << aIKOptions.getEndTime() << ")" << endl;

	for (int index = startFrame; index <= endFrame; index++)
	{
		// Get time associated with index
		double timeT = inputData.getStateVector(index)->getTime();

		/* This sets the values of the prescribed coordinates, which
		 * are coordinates that are:
		 *   (a) specified in the input data, and
		 *   (b) locked at that specified value.
		 * These coordinates are not variables in the IK solving.
		 * If a coordinate is specified in the file but not
		 * locked, it is an unconstrained coordinate and it is
		 * variable in the IK solving.
		 */
		target->setPrescribedCoordinates(index);

		// This sets the guess of unconstrained generalized coordinates 
		// and marker data from recordedDataStorage
		target->setIndexToSolve(index, &unconstrainedQGuess[0]);

		// Invoke optimization mechanism to solve for Qs
		int optimizerReturn = optimizer->computeOptimalControls(&unconstrainedQGuess[0], &unconstrainedQSol[0]);

		/* Output variables include unconstrained (solved) Qs... */
		rdArray<double> qsAndMarkersArray = unconstrainedQSol;

		/* ... then prescribed Qs... */
		rdArray<double> prescribedQValues(0.0);
		target->getPrescribedQValues(prescribedQValues);
		qsAndMarkersArray.append(prescribedQValues);

		/* ... then, optionally, computed marker locations. */
		if (aIKOptions.getIncludeMarkers())
		{
			target->getExperimentalMarkerLocations(experimentalMarkerLocations);
			qsAndMarkersArray.append(experimentalMarkerLocations);
		}

		inputData.getTime(index, currentTime);
		cout << "Solved frame " << index + 1 << " at time " << currentTime << ", Optimizer returned = " << optimizerReturn << endl;
		// Allocate new row (rdStateVector) and add it to ikStorage
		rdStateVector *nextDataRow = new rdStateVector();
		nextDataRow->setStates(timeT, qsAndMarkersArray.getSize(), &qsAndMarkersArray[0]);

		outputData.append(*nextDataRow);
	}

	delete optimizer;
	//delete target; //TODO this causes the application to crash as it exits
}