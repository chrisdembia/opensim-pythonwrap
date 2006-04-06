// scale.cpp
// Author: Ayman Habib
/* Copyright (c) 2005, Stanford University and Ayman Habib.
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
#include <NMBLTK/Tools/rdIO.h>
#include <NMBLTK/Tools/rdXMLDocument.h>
#include <NMBLTK/Tools/rdVisibleProperties.h>
#include <NMBLTK/Tools/suScaleSet.h>
#include <NMBLTK/Simulation/SIMM/simmModel.h>
#include <NMBLTK/Simulation/SIMM/simmMuscle.h>
#include <NMBLTK/Actuators/rdLinearSetPoint.h>
#include <NMBLTK/Simulation/SIMM/simmKinematicsEngine.h>
#include <NMBLTK/Simulation/SIMM/simmMarkerSet.h>
#include <NMBLTK/Simulation/SIMM/simmSubject.h>
#include <NMBLTK/Simulation/SIMM/simmMarkerData.h>
#include <NMBLTK/Simulation/SIMM/simmMotionData.h>

#include <NMBLTK/Simulation/Model/rdAnalysis.h>
#include <NMBLTK/Applications/IK/simmIKSolverImpl.h>
#include "simmScalerImpl.h"

using namespace std;


static void PrintUsage(ostream &aOStream);

//______________________________________________________________________________
/**
 * Test program to read SIMM model elements from an XML file.
 *
 * @param argc Number of command line arguments (should be 1).
 * @param argv Command line arguments:  simmReadXML inFile
 */
int main(int argc,char **argv)
{
	// PARSE COMMAND LINE
	string inName;
	string option = "";
	if (argc < 2)
	{
		PrintUsage(cout);
		exit(-1);
	}
	else {		// Don't know maybe user needs help or have special needs
		int i;
		for(i=1;i<=(argc-1);i++) {
			option = argv[i];

			// PRINT THE USAGE OPTIONS
			if((option=="-help")||(option=="-h")||(option=="-Help")||(option=="-H")||
				(option=="-usage")||(option=="-u")||(option=="-Usage")||(option=="-U")) {
					PrintUsage(cout);
					return(0);
					// IDENTIFY SETUP FILE
				} else if((option=="-S")||(option=="-Setup")) {
					if (argv[i+1]==0){
						PrintUsage(cout);
						return(0);
					}
					inName = argv[i+1];
					break;
				}
				else if((option=="-PrintSetup")||(option=="-PS")) {
					simmSubject *subject = new simmSubject();
					subject->setName("default");
					// Add in useful objects that may need to be instantiated
					rdObject::setSerializeAllDefaults(true);
					subject->print("default_subject.xml");
					rdObject::setSerializeAllDefaults(false);
					cout << "Created file default_subject.xml with default setup" << endl;
					return(0); 
				}
				else {
					cout << "Unrecognized option " << option << " on command line... Ignored" << endl;
					PrintUsage(cout);
					return(0);
				}
		}
	}
	try {
		// Construct model and read parameters file
		simmSubject* subject = new simmSubject(inName);
		simmModel* model = subject->createModel();
		simmKinematicsEngine& engine = model->getSimmKinematicsEngine();
		if (!subject->isDefaultScalingParams()){
			ScalerInterface *scaler = new simmScalerImpl(engine);
			engine.setScaler(scaler);
			if (!subject->getScalingParams().processModel(model, subject->getMass()))
			{
				cout << "===ERROR===: Unable to scale generic model." << endl;
				return 0;
			}
			else {
				cout << "Scaled model "<< inName << "Successfully" << endl;
			}
			delete scaler;
		}
		else {
			cout << "Scaling parameters not set. Model is not scaled." << endl;
		}
		if (!subject->isDefaultMarkerPlacementParams()){
			IKSolverInterface *ikSolver = new simmIKSolverImpl(engine);
			engine.setIKSolver(ikSolver);
			if (!subject->getMarkerPlacementParams().processModel(model))
			{
				cout << "===ERROR===: Unable to place markers on model." << endl;
				return 0;
			}
			delete ikSolver;
		}
		else {
			cout << "Marker placement parameters not set. No markers have been moved." << endl;
		}
		delete model;
		delete subject;
	}
	catch(rdException &x) {
		x.print(cout);
	}

}
	
//_____________________________________________________________________________
/**
 * Print the usage for this application
 */
void PrintUsage(ostream &aOStream)
{
	aOStream<<"\n\nscale.exe:\n\n";
	aOStream<<"Option            Argument      Action / Notes\n";
	aOStream<<"------            --------      --------------\n";
	aOStream<<"-Help, -H                       Print the command-line options for scale.exe.\n";
	aOStream<<"-PrintSetup, -PS                Generates a template Setup file to customize scaling\n";
	aOStream<<"-Setup, -S        SetupFile     Specify an xml setup file that specifies an OpenSim model,\n";
	aOStream<<"                                a marker file, and scaling parameters.\n";
}
