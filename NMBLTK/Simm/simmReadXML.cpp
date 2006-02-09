// simmReadXML.cpp
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


// INCLUDES
#include <string>
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Tools/rdStorage.h>
#include <NMBLTK/Tools/rdIO.h>
#include <NMBLTK/Tools/rdXMLDocument.h>
#include <NMBLTK/Tools/rdVisibleProperties.h>
#include <NMBLTK/Tools/suScaleSet.h>
#include <NMBLTK/Simm/simmModel.h>
#include <NMBLTK/Simm/simmMuscle.h>
#include <NMBLTK/Actuators/rdLinearSetPoint.h>
#include "simmKinematicsEngine.h"
#include "simmMarkerSet.h"
#include "simmSubject.h"
#include "simmMarkerData.h"
#include "simmMotionData.h"

#include <NMBLTK/Simulation/Model/rdAnalysis.h>

using namespace std;

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
	if (argc < 2)
	{
		printf("Usage: subject subject.xml\n");
		exit(-1);
	}
	else
	{
		inName = argv[1];
	}

	rdObject::RegisterType(simmModel());
	rdObject::RegisterType(simmKinematicsEngine());
	rdObject::RegisterType(simmSubject());
	simmModel::registerTypes();
	simmKinematicsEngine::registerTypes();
	simmSubject::registerTypes();

	if (1)
	{
		simmSubject* subject = new simmSubject(argv[1]);
		subject->processModel();
	}

	if (0)
	{
		simmModel* model = new simmModel(inName);
		model->setup();

		if (model->builtOK())
		{
			//for testing deserialization and model creation
			model->peteTest();
			model->print("output.xml");

			//for testing dynamics output
			//model->getSimmKinematicsEngine().saveDynamics("pipeline/dynsim/src/");

			//for testing serialization and use of defaults
			simmModel *modelCopy = (simmModel*)model->copy();
			modelCopy->print("outputCopy.xml");
		}

		delete model;
	}

	return 0;
}

