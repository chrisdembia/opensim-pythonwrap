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

	simmKinematicsEngine& engine = model->getSimmKinematicsEngine();
	ScalerInterface *scaler = new simmScalerImpl(engine);
	engine.setScaler(scaler);
	if (!subject->getScalingParams().processModel(model, 75.0))
	{
		cout << "===ERROR===: Unable to scale generic model." << endl;
		return 0;
	}
	delete scaler;

	IKSolverInterface *ikSolver = new simmIKSolverImpl(engine);
	engine.setIKSolver(ikSolver);
	if (!subject->getMarkerPlacementParams().processModel(model))
	{
		cout << "===ERROR===: Unable to place markers on model." << endl;
		return 0;
	}
	subject->getIKParams().processModel(model);

	delete subject;
	delete ikSolver;

	/* Compare results with standard*/
	bool success = true;
	for (int i=0; i < 1 && success; i++){
		string command = "cmp "+filesToCompare[i]+" "+"std_"+filesToCompare[i];
		success = success && (system(command.c_str())==0);
	}

	return (success?0:1);
}
	
