// rdSimplifyControls.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// INCLUDES
#include <string>
#include <RD/Tools/rdTools.h>
#include <RD/Tools/rdIO.h>
#include <RD/Tools/rdPropertyDbl.h>
#include <RD/Tools/rdPropertySet.h>
#include <RD/Tools/rdStorage.h>
#include <RD/Simulation/Control/rdControl.h>
#include <RD/Simulation/Control/rdControlConstant.h>
#include <RD/Simulation/Control/rdControlLinear.h>
#include <RD/Simulation/Control/rdControlSet.h>


using namespace std;


//______________________________________________________________________________
/**
 * Simplify a the controls in a controls file.\n\n
 *
 * The user must specify and input file as well as a cutoff frequency and
 * a distance.  The cutoff frequency is used to low-pass filter the
 * original control curves in the input file.  The distance use used
 * to specify the distance error allowed between the simplified curve and
 * the low-pass filtered curve.\n\n
 *
 * The new control set is written to controls_simple.ctr.\n
 * For the purpose of checking the quality of the simplification, the
 * control set is also written to two storage files:  controls_original.sto,
 * which contains the original controls, and controls_simple.sto, which
 * contains the simplified controls.  These .sto files can be plotted
 * using Excel, for example.
 *
 * @param argc Number of command line arguments.
 * @param argv Command line arguments:\n
 * simplifyControls inFile cutoff_frequency distance
 */
int main(int argc,char **argv)
{
	// PARSE COMMAND LINE
	string inName,outName;
	double cutoff,distance;
	if(argc!=4) {
		cout<<"\n\nUsage: simplifyControls ";
		cout<<"inFile cutoff_frequency distance\n\n";
		exit(-1);
	} else {
		inName = argv[1];
		sscanf(argv[2],"%lf",&cutoff);
		sscanf(argv[3],"%lf",&distance);
	}

	// OUTPUT PRECISION
	rdIO::SetPrecision(16);
	rdIO::SetDigitsPad(-1);

	// REGISTER TYPES
	rdObject::RegisterType(rdControlConstant());
	rdObject::RegisterType(rdControlLinear());
	rdObject::RegisterType(rdControlLinearNode());

	// LOAD CONTROL SET
	cout<<"Loading control set "<<inName<<" to be simplified..."<<endl;
	rdControlSet controlSet(inName);

	// EXTRACT INITIAL AND FINAL TIMES
	double ti=0.0,tf=1.0;
	rdArray<int> list(0);
	rdControlLinear *control;
	controlSet.getControlList("rdControlLinear",list);
	if(list.getSize()>0) {
		control = (rdControlLinear*)controlSet.get(list[0]);
		rdArrayPtrs<rdControlLinearNode> &nodes = control->getNodeArray();
		if(nodes.getSize()>0) {
			ti = nodes.get(0)->getTime();
			tf = nodes.getLast()->getTime();
		}
	}

	// CONVERT ALL LINEAR CONTROL NODES NOT TO USE STEPS
	int i,size=list.getSize();
	for(i=0;i<size;i++) {
		control = (rdControlLinear*)controlSet.get(list[i]);
		control->setUseSteps(false);
	}

	// CONSTRUCT STORAGE FILE FOR ORIGINAL
	int n=1000;
	rdStorage *originalStore = controlSet.constructStorage(n,ti,tf,false); 

	// PREPARE ARGUMENTS
	rdPropertySet properties;
	rdPropertyDbl *propCutoff = new rdPropertyDbl("cutoff_frequency",cutoff);
	rdPropertyDbl *propDistance = new rdPropertyDbl("distance",distance);
	properties.append(propCutoff);
	properties.append(propDistance);

	// SIMPLIFY
	controlSet.simplify(properties);

	// CONSTRUCT STORAGE FILE FOR SIMPLE
	rdStorage *simpleStore = controlSet.constructStorage(n,ti,tf,false); 
	originalStore->print("controls_simple.sto");

	// WRITE CONTROL SET TO FILE
	controlSet.print("controls_simple.ctr");
	originalStore->print("controls_original.sto");
	simpleStore->print("controls_simple.sto");

	return(0);
}
