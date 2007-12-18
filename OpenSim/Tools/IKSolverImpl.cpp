#include <OpenSim/Common/rdMath.h>
#include <OpenSim/Common/Array.h>
#include <OpenSim/Common/Storage.h>
#include <OpenSim/Common/IO.h>
#include "IKTrial.h"
#include <OpenSim/Simulation/Model/AbstractDynamicsEngine.h>
#include <OpenSim/Simulation/Model/Model.h>
#include <OpenSim/Simulation/Model/IntegCallbackSet.h>
#include <OpenSim/Simulation/Model/AnalysisSet.h>
#include <SimTKmath.h>
#include <simmath/Optimizer.h>
#include "IKSolverImpl.h"
#include "IKTarget.h"



using namespace OpenSim;
using namespace std;
using SimTK::Optimizer;
using SimTK::Vector;
//______________________________________________________________________________
/**
 * An implementation of the IKSolverInterface specific to simm classes/dynamicsEngine.
 *
 * @param aOptimizationTarget The target that IK will minimize
 * @param aIKTrial Parameters specified in input file to control IK.
 */
IKSolverImpl::
IKSolverImpl(IKTarget& aOptimizationTarget):
IKSolverInterface(aOptimizationTarget)
{
}
//______________________________________________________________________________
/**
 * Initializes the columns of the output storage
 */
void IKSolverImpl::initializeSolver(const IKTrial& aIKOptions, Storage& inputData, Storage& outputData)
{
	/* Get names for unprescribed Qs (ones that will be solved). */
	Array<string> unprescribedCoordinateNames;
   _ikTarget.getUnprescribedCoordinateNames(unprescribedCoordinateNames);

	/* Get names for prescribed Qs (specified in input file). */
	Array<string> prescribedCoordinateNames;
   _ikTarget.getPrescribedCoordinateNames(prescribedCoordinateNames);

	/* Get names for markers used for solving. */
	Array<string> markerNames;
	_ikTarget.getOutputMarkerNames(markerNames);

	Array<string> resultColumnLabels;
	resultColumnLabels.append("time");
	for (int i = 0; i < unprescribedCoordinateNames.getSize(); i++)
		resultColumnLabels.append(unprescribedCoordinateNames[i]);

	for (int i = 0; i < prescribedCoordinateNames.getSize(); i++)
		resultColumnLabels.append(prescribedCoordinateNames[i]);

	// Include markers for visual verification in SIMM
	if (aIKOptions.getIncludeMarkers()) {
		for (int i = 0; i < markerNames.getSize(); i++) {
			resultColumnLabels.append(markerNames[i] + "_px");
			resultColumnLabels.append(markerNames[i] + "_py");
			resultColumnLabels.append(markerNames[i] + "_pz");
		}
	}
	// User data (colummns that are in input storage file but not used by IK,
	// to be passed along for later processing.
	_userDataColumnIndices.setSize(0);
	Array<string> userColumnLabels;
	collectUserData(inputData.getColumnLabels(), resultColumnLabels, userColumnLabels, _userDataColumnIndices);
	resultColumnLabels.append(userColumnLabels);

	outputData.setColumnLabels(resultColumnLabels);
}
//______________________________________________________________________________
/**
 * This is the heart of the IK solver, this method solves a specific motion trial
 * given an input storage object for input, one for output.

 * @param aIKOptions Pass along to the method attributes specified by end-user in input file.
 * @param inputData Set of frames to solve packaged as a storage fle.
 * @param outputData the frames solved by the solver represented as a storage onbject.
 */
void IKSolverImpl::solveFrames(const IKTrial& aIKOptions, Storage& inputData, Storage& outputData)
{
	// Main loop to set initial conditions and solve snapshots
	// At every step we use experimental data as a starting guess 
	int numParameters = _ikTarget.getNumUnprescribedCoordinates();
	Array<double> unprescribedQGuess(0.0, numParameters);	// Initial guess and work array
	Array<double> unprescribedQSol(0.0, numParameters);	// Solution array
	Array<double> experimentalMarkerLocations(0.0, _ikTarget.getNumOutputMarkers() * 3);

	int startFrame = aIKOptions.getStartFrame(), endFrame = aIKOptions.getEndFrame();

	if (endFrame - startFrame > 1)
		cout << "Solving frames " << startFrame + 1 << " to " << endFrame + 1 << " (time = " <<
		aIKOptions.getStartTime() << " to " << aIKOptions.getEndTime() << ")" << endl;

	// Gather lower and upper bounds
	Vector lowerBounds(numParameters), upperBounds(numParameters);
	// Set the lower and upper bounds on the unprescribed Q array
	AbstractDynamicsEngine &eng = _ikTarget.getModel().getDynamicsEngine();
	for (int i = 0; i < numParameters; i++)
	{
		const AbstractCoordinate* coord = _ikTarget.getUnprescribedCoordinate(i);
		lowerBounds[i] = coord->getRangeMin();
		upperBounds[i] = coord->getRangeMax();
	}
	_ikTarget.setParameterLimits(lowerBounds,upperBounds);

	Optimizer *optimizer = createOptimizer(aIKOptions, _ikTarget);

	try {
	Array<double> emptyX(0.0,_ikTarget.getModel().getNumControls());
	Array<double> emptyY(0.0,_ikTarget.getModel().getNumStates());

	// Invoke optimization mechanism to solve for Qs
	//Vector results(numParameters); // initialize with initial guess
	SimTK::Vector results(numParameters); // initialize with initial guess

	//LARGE_INTEGER start;
	//LARGE_INTEGER stop;
	//LARGE_INTEGER frequency;

	//QueryPerformanceFrequency(&frequency);
	//QueryPerformanceCounter(&start);

	for (int index = startFrame; index <= endFrame; index++)
	{
		// Get time associated with index
		double timeT = inputData.getStateVector(index)->getTime();

		// Set value for prescribed coordinates and get initial guess for unprescribed coordinates
		_ikTarget.prepareToSolve(index, &unprescribedQGuess[0]);

		// Invoke optimization mechanism to solve for Qs
		if(index == startFrame) { 
			for(int i=0;i<numParameters;i++) {
				results[i]=unprescribedQGuess[i]; 
			}
		}
		else { 
			for(int i=0;i<numParameters;i++) {
				results[i]=unprescribedQSol[i]; 
			}
		}

		if(optimizer){
			try {
				optimizer->optimize(results);
			}
			catch (const SimTK::Exception::Base &ex) {
				cout << ex.getMessage() << endl;
				cout << "OPTIMIZATION FAILED..." << endl;
			}
		}
		else {
           _ikTarget.iterativeOptimization(results);
		}

		for(int i=0;i<numParameters;i++) unprescribedQSol[i]=results[i];

		/* Output variables include unprescribed (solved) Qs... */
		Array<double> qsAndMarkersArray = unprescribedQSol;

		/* ... then prescribed Qs... */
		Array<double> prescribedCoordinateValues(0.0);
		_ikTarget.getPrescribedCoordinateValues(prescribedCoordinateValues);
		qsAndMarkersArray.append(prescribedCoordinateValues);

		/* ... then, optionally, computed marker locations. */
		if (aIKOptions.getIncludeMarkers())
		{
			_ikTarget.getExperimentalMarkerLocations(experimentalMarkerLocations);
			qsAndMarkersArray.append(experimentalMarkerLocations);
		}

		double currentTime;
		inputData.getTime(index, currentTime);
		cout << "Frame " << index + 1 << " (t=" << currentTime << "):\t";
		_ikTarget.printPerformance(&unprescribedQSol[0]);

		// Append user data to qsAndMarkersArray
		Array<double> dataRow(qsAndMarkersArray);
		appendUserData(dataRow, _userDataColumnIndices, inputData.getStateVector(index));

		// Allocate new row (StateVector) and add it to outputData
		StateVector *nextDataRow = new StateVector();
		nextDataRow->setStates(timeT, dataRow.getSize(), &dataRow[0]);
		outputData.append(*nextDataRow);

		// INTEGRATION CALLBACKS
		// TODO: pass callback a reasonable "dt" value
		IntegCallbackSet *callbackSet = _ikTarget.getModel().getIntegCallbackSet();
		if(callbackSet!=NULL)
			callbackSet->step(&emptyX[0],&emptyY[0],NULL,index-startFrame+1,0,currentTime,&emptyX[0],&emptyY[0]);

		// ANALYSES
		// TODO: pass callback a reasonable "dt" value
		AnalysisSet *analysisSet = _ikTarget.getModel().getAnalysisSet();
		if(analysisSet!=NULL)
			analysisSet->step(&emptyX[0],&emptyY[0],NULL,index-startFrame+1,0,currentTime,&emptyX[0],&emptyY[0]);
	}

	//QueryPerformanceCounter(&stop);
	//double duration = (double)(stop.QuadPart-start.QuadPart)/(double)frequency.QuadPart;
	//cout << "IK solution time = " << (duration*1.0e3) << " milliseconds" << endl;

	} catch (...) { // e.g. may get InterruptedException from the callbackSet
		delete optimizer;
		throw;
	}
	delete optimizer;
}

void IKSolverImpl::interrupt()
{
	_ikTarget.interrupt();
}
//______________________________________________________________________________
/**
 * UserData is the set of columns that are not used directly by the IK problem (for example
 * ground reaction forces). This UserData needs to be carried along in IK.
 */
void IKSolverImpl::collectUserData(const Array<string> &inputColumnLabels,
											  const Array<string> &resultColumnLabels,
											  Array<string> &userColumnLabels,
									   Array<int>& userDataColumnIndices)
{
	// Find columns that are none of the above to append them to the end of the list
	for(int i=0; i< inputColumnLabels.getSize(); i++){
		string nextLabel = inputColumnLabels[i];
		if(resultColumnLabels.findIndex(nextLabel)==-1) {
			// This input column is not already part of our results, so we'll add it as user data
			userColumnLabels.append(nextLabel);
			// Keep track of indices to match data with labels
			userDataColumnIndices.append(i);
		}
	}
}
//______________________________________________________________________________
/**
 * Companion helper function to (collectUserData) responsible for appending user columns 
 * to outputRow.
 */
void IKSolverImpl::appendUserData(Array<double>& outputRow, Array<int>& indices, StateVector* inputRow)
{
	int i;
	for(i=0; i< indices.getSize(); i++){
		double userValue=rdMath::NAN;
		int index = indices[i]-1;
		inputRow->getDataValue(index, userValue);
		outputRow.append(userValue);
	}
}
//______________________________________________________________________________
/**
 */
SimTK::Optimizer *IKSolverImpl::createOptimizer(const IKTrial &aIKOptions, SimTK::OptimizerSystem &aSystem) const
{
	// Pick optimizer algorithm
	SimTK::OptimizerAlgorithm algorithm = SimTK::InteriorPoint;
	if(IO::Uppercase(aIKOptions.getOptimizerAlgorithm()) == "CFSQP") {
		if(!SimTK::Optimizer::isAlgorithmAvailable(SimTK::CFSQP)) {
			std::cout << "CFSQP optimizer algorithm unavailable.  Will try to use IPOPT instead." << std::endl;
			algorithm = SimTK::InteriorPoint;
		} else {
			std::cout << "Using CFSQP optimizer algorithm." << std::endl;
			algorithm = SimTK::CFSQP;
		}
	} else if(IO::Uppercase(aIKOptions.getOptimizerAlgorithm()) == "IPOPT") {
		std::cout << "Using Ipopt optimizer algorithm." << std::endl;
		algorithm = SimTK::InteriorPoint;
	} else if(IO::Uppercase(aIKOptions.getOptimizerAlgorithm()) == "JACOB") {
		std::cout << "Using Jacobian with Linear Least Squares Solver." << std::endl;
		algorithm = SimTK::BestAvailiable;
	} else {
		throw Exception("CMCTool: ERROR- Unrecognized optimizer algorithm: '"+aIKOptions.getOptimizerAlgorithm()+"'",__FILE__,__LINE__);
	}

	SimTK::Optimizer *optimizer = NULL();

	if(algorithm != SimTK::BestAvailiable) {
	
		SimTK::Optimizer *optimizer = new SimTK::Optimizer(aSystem, algorithm);

		optimizer->setDiagnosticsLevel(0);
		optimizer->setConvergenceTolerance(1e-4);
		optimizer->setMaxIterations(1000);
		optimizer->useNumericalGradient(false); // Use our own central difference approximations
		optimizer->useNumericalJacobian(false);

		if(algorithm == SimTK::InteriorPoint) {
			// Some IPOPT-specific settings
			optimizer->setLimitedMemoryHistory(500); // works well for our small systems
			optimizer->setAdvancedBoolOption("warm_start",true);
			optimizer->setAdvancedRealOption("obj_scaling_factor",1);
			optimizer->setAdvancedRealOption("nlp_scaling_max_gradient",1);
		}
	}

	return optimizer;
}
