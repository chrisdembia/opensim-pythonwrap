// testTools.cpp
// Author:  Frank C. Anderson
/*
* Copyright (c)  2005, Stanford University. All rights reserved. 
* Use of the OpenSim software in source form is permitted provided that the following
* conditions are met:
* 	1. The software is used only for non-commercial research and education. It may not
*     be used in relation to any commercial activity.
* 	2. The software is not distributed or redistributed.  Software distribution is allowed 
*     only through https://simtk.org/home/opensim.
* 	3. Use of the OpenSim software or derivatives must be acknowledged in all publications,
*      presentations, or documents describing work in which OpenSim or derivatives are used.
* 	4. Credits to developers may not be removed from executables
*     created from modifications of the source.
* 	5. Modifications of source code must retain the above copyright notice, this list of
*     conditions and the following disclaimer. 
* 
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
*  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
*  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
*  SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
*  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
*  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
*  OR BUSINESS INTERRUPTION) OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
*  WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include <iostream>
#include <string>
#include <math.h>
#include <OpenSim/Common/Exception.h>
#include <OpenSim/Common/Signal.h>
#include <OpenSim/Common/Storage.h>
#include <OpenSim/Common/IO.h>
#include <OpenSim/Common/Object.h>
#include <OpenSim/Common/GCVSplineSet.h>
#include <OpenSim/Common/Array.h>
#include <OpenSim/Common/PropertyBool.h>
#include <OpenSim/Common/PropertyInt.h>
#include <OpenSim/Common/PropertyIntArray.h>
#include <OpenSim/Common/PropertyDbl.h>
#include <OpenSim/Common/PropertyStr.h>
#include <OpenSim/Common/PropertyStrArray.h>
#include <OpenSim/Common/PropertySet.h>
#include <OpenSim/Common/RootSolver.h>
#include <OpenSim/Auxiliary/auxiliaryTestFunctions.h>
#include "ExampleVectorFunctionUncoupledNxN.h"

using namespace OpenSim;
using namespace std;

int main()
{
	try {
		// CONSTRUCT THE UNCOUPLED VECTOR FUNCTION
		int N = 101;
		ExampleVectorFunctionUncoupledNxN function(N);

		// EVALUATE THE FUNCTION
		cout<<"\n\nEvaluate the function:\n";
		Array<double> x(0.0, N), y(0.0, N);
		function.calcValue(&x[0], &y[0], N);
		cout << "x:\n" << x << endl;
		cout << "y:\n" << y << endl;

		// ROOT SOLVE
		Array<double> a(-1.0,N), b(1.0,N), tol(1.0e-6,N);
		Array<double> roots(0.0,N);
		RootSolver solver(&function);
		//roots = solver.solve(a,b,tol);  NOTE: JACKM need to pass in state or change CMC 
		cout<<endl<<endl<<"-------------"<<endl;
		cout<<"roots:\n";
		cout<<roots<<endl<<endl;
		for (int i=0; i <= 100; i++){
			//ASSERT_EQUAL(i*0.01, roots[i], 1e-6);
		}
	}
	catch (const Exception& e) {
        e.print(cerr);
        return 1;
    }
    cout << "Done" << endl;
    return 0;
}
