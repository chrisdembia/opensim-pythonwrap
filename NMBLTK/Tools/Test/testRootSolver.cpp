// testTools.cpp
// Author:  Frank C. Anderson
#include <iostream>
#include <string>
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Tools/rdException.h>
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Tools/rdSignal.h>
#include <NMBLTK/Tools/rdStorage.h>
#include <NMBLTK/Tools/rdIO.h>
#include <NMBLTK/Tools/rdXMLDocument.h>
#include <NMBLTK/Tools/rdObject.h>
#include <NMBLTK/Tools/rdLine.h>
#include <NMBLTK/Tools/rdPlane.h>
#include <NMBLTK/Tools/rdGCVSplineSet.h>
#include <NMBLTK/Tools/rdSIMMUtilities.h>
#include <NMBLTK/Tools/rdArray.h>
#include <NMBLTK/Tools/rdPropertyBool.h>
#include <NMBLTK/Tools/rdPropertyInt.h>
#include <NMBLTK/Tools/rdPropertyIntArray.h>
#include <NMBLTK/Tools/rdPropertyDbl.h>
#include <NMBLTK/Tools/rdPropertyStr.h>
#include <NMBLTK/Tools/rdPropertyStrArray.h>
#include <NMBLTK/Tools/rdPropertySet.h>
#include <NMBLTK/Tools/RootSolver.h>
#include "ExampleVectorFunctionUncoupledNxN.h"


using namespace std;


// DECLARATIONS

int TestRootSolver();
//_____________________________________________________________________________
/**
 * Test the rdTools library.
 */
int main(int argc, char* argv[])
{
	// PARSE COMMAND LINE

	// STORAGE
	//TestStorage();

	// XML
	//TestXML();

	// GEOMETRY
	//TestGeometry();

	// TEST GCVSplineSet
	//TestGCVSplineSet();

	// TEST SIMM UTILITIES
	//TestSIMMUtilities();

	// EXCEPTIONS
	//TestExceptions();

	// VECTOR
	//TestVector();

	// ARRAY
	//TestArray();

	// PROPERTY
	//TestProperty();

	// PROPERTY SET
	//TestPropertySet();

	// SERIALIZATION
	//TestSerialization();

	// SIGNAL
	//TestSignal();

	// ROOT SOLVER

	return(TestRootSolver());
}


//_____________________________________________________________________________
/**
 * Test the RootSolver class.
 */
int TestRootSolver()
{
	// CONSTRUCT THE UNCOUPLED VECTOR FUNCTION
	int N = 101;
	ExampleVectorFunctionUncoupledNxN function(N);

	// EVALUATE THE FUNCTION
	cout<<"\n\nEvaluate the function:\n";
	rdArray<double> x(0.0,N),y(0.0,N);
	function.evaluate(&x[0],&y[0]);
	cout<<"x:\n";
	cout<<x<<endl;
	cout<<"y:\n";
	cout<<y<<endl;

	// ROOT SOLVE
	rdArray<double> a(-1.0,N),b(1.0,N),tol(1.0e-6,N);
	rdArray<double> roots(0.0,N);
	RootSolver solver(&function);
	roots = solver.solve(a,b,tol);
	cout<<endl<<endl<<"-------------"<<endl;
	cout<<"roots:\n";
	cout<<roots<<endl<<endl;
	bool success = true;
	for (int i=0; i <= 100 && success; i++){
		success = (fabs(i*0.01 - roots[i])<1e-6);
	}
	return(success?0:1);
}

